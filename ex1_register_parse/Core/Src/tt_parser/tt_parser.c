#include "tt_parser.h"
#include <string.h>

// define
#define HEADER_HEAD_INDEX 0
#define HEADER_REG_INDEX 1
#define HEADER_WORD_COUNT_INDEX 2
#define HEADER_MAP_ERR_INDEX 3

// typedef
// private variable

// private function declare

void resetTtParser(TtParser *parser);
void resetTtTracker(TtTracker *tracker);
bool verifyHeader(TtParser *parser);
void checkMessageType(TtParser *parser);
bool verifyCheckSum(uint8_t *bytes, uint16_t start_index, uint16_t len);
bool matchChecksum(TtParser *parser);
void addMessageByte(TtParser *parser, uint8_t c);

uint16_t traceForwardIndex(uint16_t index, uint16_t offset);
uint16_t traceBackwardIndex(uint16_t index, uint16_t offset);

// private function implement

void resetTtParser(TtParser *parser)
{
    memset(parser->msg, 0x00, BUFF_SIZE);
    resetTtTracker(&parser->tracker);
}

void resetTtTracker(TtTracker *tracker)
{
    tracker->current_index = 0;
    tracker->next_index = 0;
    tracker->state = VERIFY_HEADER;
}

bool verifyHeader(TtParser *parser)
{
    TtTracker *tracker = &parser->tracker;

    uint16_t header_1st_index = traceBackwardIndex(parser->tracker.current_index, 3);
    uint16_t header_4th_index = parser->tracker.current_index;

    uint8_t head = parser->msg[header_1st_index];
    uint8_t error = parser->msg[header_4th_index] & 0x0F;

    if ((head >> 1) != parser->factory_id)
        return false;
    if (error != 0)
        return false;

    tracker->msg_start_index = header_1st_index;
    return true;
}

void checkMessageType(TtParser *parser)
{
    TtTracker *tracker = &parser->tracker;

    uint16_t header_1st_index = tracker->msg_start_index;
    uint16_t header_3rd_index = traceForwardIndex(header_1st_index, 2);
    uint8_t is_read = (parser->msg[header_1st_index] & 1);
    uint8_t word_count = parser->msg[header_3rd_index];

    if (verifyCheckSum(parser->msg, header_1st_index, 5))
    {
        parser->type = (is_read == 1) ? READ_REQUEST : WRITE_RESPONSE;
        tracker->msg_end_index = traceForwardIndex(header_1st_index, 4);
    }
    else
    {
        parser->type = (is_read == 1) ? READ_RESPONSE : WRITE_REQUEST;
        tracker->msg_end_index = traceForwardIndex(header_1st_index , (word_count + 1) * 4);
    }
}

bool verifyCheckSum(uint8_t *bytes, uint16_t start_index, uint16_t len)
{
    uint8_t checksum = 0x00;
    uint16_t index = start_index;
    for (uint16_t i = 0; i < len; i++)
    {
        checksum += bytes[index];
        index++;
        if (index >= BUFF_SIZE)
        {
            index = 0;
        }
    }
    if (checksum == 0)
    {
        return true;
    }
    return false;
}

bool matchChecksum(TtParser *parser)
{
    TtTracker *tracker = &parser->tracker;
    uint16_t header_1st_index = tracker->msg_start_index;
    uint16_t header_3rd_index = traceForwardIndex(header_1st_index, 2);
    uint8_t word_count = parser->msg[header_3rd_index];

    uint16_t msg_length = ((uint16_t)word_count + 1) * 4 + 1;
    if (tracker->current_index == tracker->msg_end_index)
    {
        if (verifyCheckSum(parser->msg, header_1st_index, msg_length))
        {
            return true;
        }
    }
    return false;
}

void addMessageByte(TtParser *parser, uint8_t c)
{
    parser->msg[parser->tracker.current_index] = c;
    parser->tracker.next_index++;

    if (parser->tracker.next_index >= BUFF_SIZE)
    {
        parser->tracker.next_index = 0;
    }
}

uint16_t traceForwardIndex(uint16_t index, uint16_t offset)
{
    uint16_t forward_index = index + offset;
    if (forward_index >= BUFF_SIZE)
    {
        return forward_index - BUFF_SIZE;
    }
    return forward_index;
}

uint16_t traceBackwardIndex(uint16_t index, uint16_t offset)
{
    uint16_t backward_index = index + BUFF_SIZE - offset;
    if (backward_index >= BUFF_SIZE)
    {
        return backward_index - BUFF_SIZE;
    }
    return backward_index;
}

// public function

void TtParserInit(TtParser *parser, uint8_t factory_id)
{
    parser->factory_id = factory_id;
    resetTtParser(parser);
}

bool TtParserUpdate(TtParser *parser, const uint8_t c)
{
    TtParserState state = parser->tracker.state;
    bool has_checksum = false;

    addMessageByte(parser, c);

    if (state == VERIFY_HEADER)
    {
        if (verifyHeader(parser))
        {
            parser->tracker.state = FIND_MSG_TYPE;
        }
    }
    else if (state == FIND_MSG_TYPE)
    {
        checkMessageType(parser);
        if (parser->type == READ_REQUEST ||
            parser->type == WRITE_RESPONSE)
        {
            has_checksum = true;
        }
        else if (parser->type == WRITE_REQUEST ||
                 parser->type == READ_RESPONSE)
        {
            parser->tracker.state = WAIT_UNTIL_CHECKSUM;
        }
    }
    else if (state == WAIT_UNTIL_CHECKSUM)
    {
        if (matchChecksum(parser))
        {
            has_checksum = true;
        }
    }

    // update index
    parser->tracker.current_index = parser->tracker.next_index;

    if (has_checksum)
    {
        parser->tracker.state = VERIFY_HEADER;
        // resetTtTracker(&parser->tracker);
        return true;
    }
    return false;
}

TtMsgType TtParserGetMsgType(TtParser *parser)
{
    return parser->type;
}

void TtParserGetHeaderInfo(TtParser *parser, uint8_t *map_id, uint8_t *reg_id, uint8_t *word_count)
{
    TtTracker *tracker = &parser->tracker;
    uint16_t header_1st_index = tracker->msg_start_index;
    uint16_t header_2nd_index = traceForwardIndex(header_1st_index, 1);
    uint16_t header_3rd_index = traceForwardIndex(header_1st_index, 2);
    uint16_t header_4th_index = traceForwardIndex(header_1st_index, 3);

    *reg_id = parser->msg[header_2nd_index];
    *word_count = parser->msg[header_3rd_index];
    *map_id = (parser->msg[header_4th_index] & 0xF0) >> 4;
}

void TtParserCopyMsgBody(TtParser *parser, void *dest, uint8_t reg_id, uint16_t word_count)
{
    TtTracker *tracker = &parser->tracker;
    uint16_t residual_length = 0;
    uint16_t body_start_index  = traceForwardIndex(tracker->msg_start_index, 4);
    uint16_t body_end_index = traceBackwardIndex(tracker->msg_end_index, 1);

    if (body_start_index > body_end_index)
    {
        residual_length = BUFF_SIZE - body_start_index;
        memcpy((uint8_t *)(&dest[reg_id]), &parser->msg[body_start_index], residual_length);
        memcpy((uint8_t *)(&dest[reg_id + residual_length]), &parser->msg[0], body_end_index + 1);
    }
    else
    {
        memcpy((uint8_t *)(&dest[reg_id]), &parser->msg[body_start_index], word_count * 4);
    }
}
