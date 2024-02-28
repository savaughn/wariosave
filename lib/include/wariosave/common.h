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

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef struct
{
    char name[MAX_LVL_NAME_CHAR];
    uint8_t courseExitCount;
    uint8_t completionBitmask;
    uint8_t completionRate;
} Level;

static const Level defaultLevelData[LEVELS_COUNT] = {
    {.name = "Rice Beach",
     .courseExitCount = 7,
     .completionBitmask = 0},
    {.name = "Mt. Teapot",
     .courseExitCount = 7,
     .completionBitmask = 0},
    {.name = "Stove Canyon", 
    .courseExitCount = 6, 
    .completionBitmask = 0},
    {.name = "S.S. Teacup",
    .courseExitCount = 5, 
    .completionBitmask = 0},
    {.name = "Parsley Woods",
    .courseExitCount = 6,
    .completionBitmask = 0},
    {.name = "Sherbet Land",
    .courseExitCount = 6,
    .completionBitmask = 0},
    {.name = "Syrup Castle",
    .courseExitCount = 3,
    .completionBitmask = 0}};

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
    uint8_t sPlPower;
    uint8_t sMapRiceBeachCompletion;
    uint8_t sMapMtTeapotCompletion;
    uint8_t sLevelsCleared;
    uint16_t sTreasures;
    uint8_t sMapStoveCanyonCompletion;
    uint8_t sMapSSTeacupCompletion;
    uint8_t sMapParsleyWoodsCompletion;
    uint8_t sMapSherbetLandCompletion;
    uint8_t sMapSyrupCastleCompletion;
    uint8_t sCheckpoint;
    uint8_t sCheckpointLevelId;
    uint8_t sGameCompleted;
} WarioSave;

typedef struct { WarioSave save[3]; } WarioGameSave;

// Custom save file structure for useful data
typedef struct
{
    // 999,999 Max Value
    uint32_t TotalCoins;
    uint8_t Hearts;
    uint8_t Lives;
    bool GameCompleted;
    Level levels[LEVELS_COUNT];
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
