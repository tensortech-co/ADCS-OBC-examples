#ifndef TT_PARSER_H_
#define TT_PARSER_H_

#include <stdint.h>
#include <stdbool.h>

#define BUFF_SIZE 1029

typedef enum
{
    VERIFY_HEADER,
    FIND_MSG_TYPE,
    WAIT_UNTIL_CHECKSUM,
} TtParserState;

typedef enum
{
    WRITE_REQUEST,
    READ_REQUEST,
    WRITE_RESPONSE,
    READ_RESPONSE
} TtMsgType;

typedef struct 
{
    TtParserState state;
    uint16_t current_index;
    uint16_t next_index;
    uint16_t msg_start_index;
    uint16_t msg_end_index;
}TtTracker;

typedef struct 
{
    uint8_t factory_id;
    TtMsgType type;
    uint8_t msg[BUFF_SIZE];
    TtTracker tracker;
} TtParser;


void TtParserInit(TtParser* parser, uint8_t factory_id);
bool TtParserUpdate(TtParser *parser, const uint8_t c);
TtMsgType TtParserGetMsgType(TtParser *parser);
void TtParserGetHeaderInfo(TtParser *parser, uint8_t* map_id, uint8_t* reg_id, uint8_t* word_count);
void TtParserCopyMsgBody(TtParser *parser, void *dest, uint8_t reg_id, uint16_t word_count);

#endif // TT_PARSER_H_