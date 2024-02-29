/**
 * Copyright (c) 2024 github/savaughn
 * Distributed under the MIT License (MIT)
 * (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)
 */

#ifndef COMMON_H
#define COMMON_H

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

#define SAVE_FILE_A_OFFSET 0x04
#define SAVE_FILE_B_OFFSET 0x44
#define SAVE_FILE_C_OFFSET 0x84
#define SAVE_FILE_OFFSET 0x40
#define SAVE_STRUCT_SIZE 0x14
#define LEVELS_COUNT 7
#define MAX_COURSE_COUNT 8
#define MAX_LVL_NAME_CHAR 14
#define MAX_COURSE_NAME_CHAR 18
#define MAX_COIN_DIGITS_STR 7
#define MAX_TREASURE_COUNT 15

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef struct
{
    /**
     * Name of the level
     * Max length of 14 characters
    */
    char name[MAX_LVL_NAME_CHAR];
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
} Level;

/**
 * Default level data
 * name: Name of the level
 * course_exit_count: Number of course exits in the level
*/
static const Level default_level_data[LEVELS_COUNT] = {
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
    // Values 99xxxx stored in dec format. Use get_decimal_bytes to convert to int
    uint8_t sTotalCoins_High;
    // Values xx99xx stored in dec format. Use get_decimal_bytes to convert to int
    uint8_t sTotalCoins_Mid;
    // Values xxxx99 stored in dec format. Use get_decimal_bytes to convert to int
    uint8_t sTotalCoins_Low;
    // Value stored in memory in dec format. Use get_decimal_byte to convert to int
    uint8_t sHearts;
    // Value stored in memory in dec format. Use get_decimal_byte to convert to int
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
} WarioSave;

typedef struct { WarioSave save[3]; } WarioGameSave;

static const char treasure_names[MAX_TREASURE_COUNT] = {
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
} TreasureNames;

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
     * accessed with TreasureNames enum
     * EX: treasure.obtained[TREASURE_A]
     */
    TreasureNames obtained[MAX_TREASURE_COUNT];
} Treasure;

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
    Level levels[LEVELS_COUNT];
    /**
     * Treasure data
    */
    Treasure treasure;
} PlayerSave;

typedef enum
{
    NO_ERROR = 0,
    FILE_ERROR,
    MEMORY_ERROR,
    READ_ERROR
} FileError;

typedef enum
{
    FILE_A = 0,
    FILE_B,
    FILE_C,
    FILE_COUNT
} SaveSlot;

#endif
