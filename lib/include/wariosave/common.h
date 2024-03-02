/**
 * Copyright (c) 2024 github/savaughn
 * Distributed under the MIT License (MIT)
 * (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)
 */

#ifndef WS_COMMON_H
#define WS_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)         \
    ((byte) & 0x80 ? '1' : '0'),     \
        ((byte) & 0x40 ? '1' : '0'), \
        ((byte) & 0x20 ? '1' : '0'), \
        ((byte) & 0x10 ? '1' : '0'), \
        ((byte) & 0x08 ? '1' : '0'), \
        ((byte) & 0x04 ? '1' : '0'), \
        ((byte) & 0x02 ? '1' : '0'), \
        ((byte) & 0x01 ? '1' : '0')

#define WS_SAVE_FILE_A_OFFSET 0x04
#define WS_SAVE_FILE_B_OFFSET 0x44
#define WS_SAVE_FILE_C_OFFSET 0x84
#define WS_SAVE_FILE_OFFSET 0x40
#define WS_SAVE_STRUCT_SIZE 0x14
#define WS_LEVELS_COUNT 7
#define WS_MAX_COURSE_COUNT 8
#define WS_MAX_LVL_NAME_CHAR 14
#define WS_MAX_COURSE_NAME_CHAR 18
#define WS_MAX_COIN_DIGITS_STR 7
#define WS_MAX_TREASURE_COUNT 15
#define WS_MAX_FILE_SLOT_COUNT 3

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

/**
 * WS_Level data structure
 * name: Name of the level
 * course_exit_count: Number of course exits in the level
 * completion_bitmask: 8-bit bitmask of course completion
 * completion_rate: Completion rate of the level in percentage
*/
typedef struct
{
    /**
     * Name of the level
     * Max length of 14 characters
    */
    char name[WS_MAX_LVL_NAME_CHAR];
    /**
     * Number of course exits in the level
    */
    uint8_t course_exit_count;
    /**
     * 8-bit bitmask of course completion
    */
    uint8_t completion_bitmask;
    /**
     * Completion rate of the level in percentage
    */
    uint8_t completion_rate;
} WS_Level;

/**
 * Default level data
 * name: Name of the level
 * course_exit_count: Number of course exits in the level
*/
static const WS_Level WS_default_level_data[WS_LEVELS_COUNT] = {
    {.name = "Rice Beach",
     .course_exit_count = 7,
     .completion_bitmask = 0,
     .completion_rate = 0},
    {.name = "Mt. Teapot",
     .course_exit_count = 7,
     .completion_bitmask = 0,
     .completion_rate = 0},
    {.name = "Stove Canyon", 
    .course_exit_count = 6, 
    .completion_bitmask = 0,
    .completion_rate = 0},
    {.name = "S.S. Teacup",
    .course_exit_count = 5, 
    .completion_bitmask = 0,
    .completion_rate = 0},
    {.name = "Parsley Woods",
    .course_exit_count = 6,
    .completion_bitmask = 0,
    .completion_rate = 0},
    {.name = "Sherbet Land",
    .course_exit_count = 6,
    .completion_bitmask = 0,
    .completion_rate = 0},
    {.name = "Syrup Castle",
    .course_exit_count = 3,
    .completion_bitmask = 0,
    .completion_rate = 0}};

// Native save file structure
typedef struct
{
    uint8_t sLevelId;
    // Values 99xxxx stored in dec format. Use ws_get_decimal_bytes to convert to int
    uint8_t sTotalCoins_High;
    // Values xx99xx stored in dec format. Use ws_get_decimal_bytes to convert to int
    uint8_t sTotalCoins_Mid;
    // Values xxxx99 stored in dec format. Use ws_get_decimal_bytes to convert to int
    uint8_t sTotalCoins_Low;
    // Value stored in memory in dec format. Use ws_get_decimal_byte to convert to int
    uint8_t sHearts;
    // Value stored in memory in dec format. Use ws_get_decimal_byte to convert to int
    uint8_t sLives;
    // Current powerup value
    uint8_t sPlPower;
    // 8-bit bitmask of course completion
    uint8_t sMapRiceBeachCompletion;
    // 8-bit bitmask of course completion
    uint8_t sMapMtTeapotCompletion;
    // 8-bit bitmask of world map level completion
    uint8_t sLevelsCleared;
    /**
     * 16-bit bitmask of treasures obtained
     * byte[0] is unused
    */
    uint16_t sTreasures;
    // 8-bit bitmask of course completion
    uint8_t sMapStoveCanyonCompletion;
    // 8-bit bitmask of course completion
    uint8_t sMapSSTeacupCompletion;
    // 8-bit bitmask of course completion
    uint8_t sMapParsleyWoodsCompletion;
    // 8-bit bitmask of course completion
    uint8_t sMapSherbetLandCompletion;
    // 8-bit bitmask of course completion
    uint8_t sMapSyrupCastleCompletion;
    uint8_t sCheckpoint;
    uint8_t sCheckpointLevelId;
    /**
     * 1-bit flag of game completion
    */
    uint8_t sGameCompleted;
} WS_WarioSave;

/**
 * All three save slots copied into one buffer
*/
typedef struct { WS_WarioSave save[WS_MAX_FILE_SLOT_COUNT]; } WS_WarioGameSave;

static const char WS_treasure_names[WS_MAX_TREASURE_COUNT] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'
};
typedef enum {
    TREASURE_A = 0, 
    TREASURE_B, 
    TREASURE_C, 
    TREASURE_D, 
    TREASURE_E,
    TREASURE_F, 
    TREASURE_G, 
    TREASURE_H, 
    TREASURE_I, 
    TREASURE_J, 
    TREASURE_K, 
    TREASURE_L, 
    TREASURE_M, 
    TREASURE_N, 
    TREASURE_O 
} WS_TreasureNames;

/**
 * WS_Treasure data structure
 * count: count of treasures obtained
 * completion_rate: completion rate of the treasures in percentage
 * obtained: array of bools representing if the treasure was obtained
*/
typedef struct {
    /**
     * count of treasures obtained
    */
    uint8_t count;
    /**
     * completion rate of the treasures in percentage
    */
    uint8_t completion_rate;
    /**
     * array of bools representing if the treasure was obtained
     * accessed with WS_TreasureNames enum
     * EX: treasure.obtained[TREASURE_A]
     */
    WS_TreasureNames obtained[WS_MAX_TREASURE_COUNT];
} WS_Treasure;

// Custom save file structure for useful data
typedef struct
{
    /**
     * Total coins collected
     * 999,999 Max Value
    */
    uint32_t total_coins;
    /**
     * Total hearts collected
     * 99 Max Value
    */
    uint8_t hearts;
    /**
     * Total lives collected
     * 99 Max Value
    */
    uint8_t lives;
    /**
     * Game completion status
    */
    bool game_completed;
    /**
     * Array of level completion rates
    */
    WS_Level levels[WS_LEVELS_COUNT];
    /**
     * WS_Treasure data
    */
    WS_Treasure treasure;
} WS_PlayerSave;

typedef enum
{
    NO_ERROR = 0,
    FILE_ERROR,
    MEMORY_ERROR,
    READ_ERROR
} WS_FileError;

typedef enum
{
    FILE_A = 0,
    FILE_B,
    FILE_C,
    FILE_COUNT
} WS_SaveSlot;

#endif
