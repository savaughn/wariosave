/**
* Copyright (c) 2024 github/savaughn
* Distributed under the MIT License (MIT)
* (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)
*/

#include "print.h"

void print_player_save(PlayerSave *save) {
    printf("TotalCoins: %u\n", save->TotalCoins);
    printf("Hearts: %d\n", save->Hearts);
    printf("Lives: %d\n", save->Lives);
    printf("GameCompleted: %d\n", save->GameCompleted);
    for (int i = 0; i < LEVELS_COUNT; i++) {
        printf("%s: %d%%\n", defaultLevelData[i].name, save->levels[i].completionRate);
    }
}

void print_save_data(WarioSave *save)
{
    printf("sLevelId: %d\n", save->sLevelId);
    printf("sTotalCoins_High: %02x\n", save->sTotalCoins_High);
    printf("sTotalCoins_Mid: %02x\n", save->sTotalCoins_Mid);
    printf("sTotalCoins_Low: %02x\n", save->sTotalCoins_Low);
    printf("sHearts: %x\n", save->sHearts);
    printf("sLives: %x\n", save->sLives);
    printf("sPlPower: %d\n", save->sPlPower);
    printf("sMapRiceBeachCompletion: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(save->sMapRiceBeachCompletion));
    printf("sMapMtTeapotCompletion: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(save->sMapMtTeapotCompletion));
    printf("sLevelsCleared: %x\n", save->sLevelsCleared);
    printf("save->sTreasures: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",
  BYTE_TO_BINARY(save->sTreasures>>8), BYTE_TO_BINARY(save->sTreasures));
    printf("sMapStoveCanyonCompletion: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(save->sMapStoveCanyonCompletion));
    printf("sMapSSTeacupCompletion: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(save->sMapSSTeacupCompletion));
    printf("sMapParsleyWoodsCompletion: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(save->sMapParsleyWoodsCompletion));
    printf("sMapSherbetLandCompletion: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(save->sMapSherbetLandCompletion));
    printf("sMapSyrupCastleCompletion: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(save->sMapSyrupCastleCompletion));
    printf("sCheckpoint: %d\n", save->sCheckpoint);
    printf("sCheckpointLevelId: %d\n", save->sCheckpointLevelId);
    printf("sGameCompleted: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(save->sGameCompleted));
}
