#include "tt_parser.h"
#include <string.h>
#include <stdio.h>

// define
#define HEADER_HEAD_INDEX 0
#define HEADER_REG_INDEX 1
#define HEADER_WORD_COUNT_INDEX 2
#define HEADER_MAP_ERR_INDEX 3
#define MSG_BODY_START_INDEX 4

// typedef
// private variable

// private function declare

void resetTtParser(TtParser *parser);
void resetTtTracker(TtTracker *tracker);
bool verifyHeader(TtParser *parser);
void computeChecksum(TtParser *parser, uint8_t c);
void addMessageByte(TtParser *parser, uint8_t c);
bool matchChecksum(TtParser *parser);
void updateMsgType(TtParser *parser);

// private function implement

void resetTtParser(TtParser *parser)
{
    memset(parser->msg, 0x00, 1029);
    resetTtTracker(&parser->tracker);
}

void resetTtTracker(TtTracker *tracker)
{
    tracker->current_index = 0;
    tracker->next_index = 0;
    tracker->checksum = 0x00;
    tracker->state = VERIFY_HEADER;
}

bool verifyHeader(TtParser *parser)
{
    TtTracker *tracker = &parser->tracker;

    if (tracker->current_index < HEADER_MAP_ERR_INDEX)
    {
        return false;
    }

    uint8_t head = parser->msg[HEADER_HEAD_INDEX];
    uint8_t error = parser->msg[HEADER_MAP_ERR_INDEX] & 0x0F;

    if ((head >> 1) != parser->factory_id)
        return false;
    if (error != 0)
        return false;

    return true;
}

void computeChecksum(TtParser *parser, uint8_t c)
{
    parser->tracker.checksum += c;
}

void addMessageByte(TtParser *parser, uint8_t c)
{
    parser->msg[parser->tracker.current_index] = c;
    parser->tracker.next_index++;
}

bool matchChecksum(TtParser *parser)
{
    if (parser->tracker.checksum == 0)
    {
        return true;
    }
    return false;
}

void updateMsgType(TtParser *parser)
{
    uint8_t is_read = (parser->msg[HEADER_HEAD_INDEX] & 1);
    uint16_t msg_length = parser->tracker.current_index - MSG_BODY_START_INDEX;

    if (msg_length == 0)
    {
        parser->type = (is_read == 1) ? READ_REQUEST : WRITE_RESPONSE;
    }
    else
    {
        parser->type = (is_read == 1) ? READ_RESPONSE : WRITE_REQUEST;
    }
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
    computeChecksum(parser, c);

    if (state == VERIFY_HEADER)
    {
        if (verifyHeader(parser))
        {
            parser->tracker.state = WAIT_UNTIL_CHECKSUM;
        }
    }
    else if (state == WAIT_UNTIL_CHECKSUM)
    {

        has_checksum = matchChecksum(parser);
    }

    if (has_checksum)
    {
        updateMsgType(parser);
        resetTtTracker(&parser->tracker);
        return true;
    }

    // update index
    parser->tracker.current_index = parser->tracker.next_index;
    return false;
}

TtMsgType TtParserGetMsgType(TtParser *parser)
{
    return parser->type;
}

bool TtParserGetRequestInfo(TtParser *parser, uint8_t *map_id, uint8_t *reg_id, uint8_t *word_count)
{
    if (parser->type != READ_REQUEST &&
        parser->type != WRITE_REQUEST)
    {
        return false;
    }

    *reg_id = parser->msg[HEADER_REG_INDEX];
    *word_count = parser->msg[HEADER_WORD_COUNT_INDEX];
    *map_id = (parser->msg[HEADER_MAP_ERR_INDEX] & 0xF0) >> 4;

    return true;
}

bool TtParserGetResponseInfo(TtParser *parser, uint8_t *map_id, uint8_t *reg_id, uint8_t *word_count)
{
    if (parser->type != READ_RESPONSE &&
        parser->type != WRITE_RESPONSE)
    {
        return false;
    }

    *reg_id = parser->msg[HEADER_REG_INDEX];
    *word_count = parser->msg[HEADER_WORD_COUNT_INDEX];
    *map_id = (parser->msg[HEADER_MAP_ERR_INDEX] & 0xF0) >> 4;

    return true;
}

void TtParserCopyMsgBody(TtParser *parser, void *dest)
{
    uint8_t reg_id = 0;
    uint8_t map_id = 0;
    uint8_t word_count = 0;
    TtParserGetResponseInfo(parser, &map_id, &reg_id, &word_count);
    memcpy((uint8_t *)dest + reg_id, parser->msg + 4, word_count * 4);
}