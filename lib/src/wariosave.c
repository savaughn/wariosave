/**
 * Copyright (c) 2024 github/savaughn
 * Distributed under the MIT License (MIT)
 * (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)
 */

#include <wariosave/helpers.h>

uint8_t ws_get_decimal_byte(const uint8_t byte)
{
    char buffer[4] = {"\0"};
    snprintf(buffer, sizeof(buffer), "%02x", byte);
    return (uint8_t)strtol(buffer, NULL, 10);
}

uint32_t ws_get_decimal_bytes(const uint8_t byte1, const uint8_t byte2, const uint8_t byte3)
{
    char buffer[WS_MAX_COIN_DIGITS_STR];

    // Format the string into the buffer
    // Each byte is already in dec format. Use %x
    // so that the values are not converted "from hex to dec"
    snprintf(buffer, sizeof(buffer), "%02x%02x%02x", byte1, byte2, byte3);
    return (uint32_t)strtol(buffer, NULL, 10);
}

WS_FileError ws_load_save_to_buffer(WS_WarioGameSave *save, const char *file_path)
{
    FILE *file = fopen(file_path, "rb");
    WS_FileError error = NO_ERROR;
    if (file == NULL)
    {
        perror("Error opening file");
        return FILE_ERROR;
    }

    for (int fileSlot = FILE_A, offset = WS_SAVE_FILE_A_OFFSET; fileSlot < FILE_COUNT; fileSlot++, offset += WS_SAVE_FILE_OFFSET)
    {
        if (fseek(file, offset, SEEK_SET) != 0)
        {
            perror("Error seeking to the file c byte");
            fclose(file);
            return MEMORY_ERROR;
        }

        uint8_t byte_array[WS_SAVE_STRUCT_SIZE];
        size_t bytes_read = fread(byte_array, 1, WS_SAVE_STRUCT_SIZE, file);

        // Check if the read operation was successful
        if (bytes_read != WS_SAVE_STRUCT_SIZE)
        {
            perror("Error reading from file");
            fclose(file);
            return READ_ERROR;
        }

        // WS_WarioSave struct is modeled after the byte array
        save->save[fileSlot] = *(WS_WarioSave *)byte_array;
    }

    // Close the file
    fclose(file);

    return error;
}

void ws_get_level_completion_rates(const WS_WarioSave *save, WS_Level *level_data)
{
    uint8_t const level_completion_bitmask[WS_LEVELS_COUNT] = {
        save->sMapRiceBeachCompletion,
        save->sMapMtTeapotCompletion,
        save->sMapStoveCanyonCompletion,
        save->sMapSSTeacupCompletion,
        save->sMapParsleyWoodsCompletion,
        save->sMapSherbetLandCompletion,
        save->sMapSyrupCastleCompletion};
    for (int i = 0; i < WS_LEVELS_COUNT; i++)
    {
        int count = 0;
        uint8_t course_exit_count = WS_default_level_data[i].course_exit_count;
        level_data[i].completion_bitmask = level_completion_bitmask[i];
        for (int j = 0; j < course_exit_count; j++)
        {
            count += (level_completion_bitmask[i] >> j) & 1;
            level_data[i].completion_rate = (int)(count / (course_exit_count * 1.0) * 100);
        }
    }
}

uint8_t ws_get_player_lives(const WS_WarioSave *save)
{
    return ws_get_decimal_byte(save->sLives);
}

uint8_t ws_get_player_hearts(const WS_WarioSave *save)
{
    return ws_get_decimal_byte(save->sHearts);
}

uint32_t ws_get_player_coins(const WS_WarioSave *save)
{
    return ws_get_decimal_bytes(save->sTotalCoins_High, save->sTotalCoins_Mid, save->sTotalCoins_Low);
}

bool ws_is_game_completed(const WS_WarioSave *save)
{
    return (bool)save->sGameCompleted;
}

WS_Treasure ws_get_treasure_data(const WS_WarioSave *save)
{
    WS_Treasure treasure = {
        .obtained = {0},
        .count = 0,
        .completion_rate = 0
    };

    for (int i = 0; i < WS_MAX_TREASURE_COUNT; i++)
    {
        // initial LSB in sTreasures is unused 
        if ((save->sTreasures >> (i + 1)) & 1)
        {
            treasure.obtained[i] = true;
            treasure.count++;
        }
    }

    treasure.completion_rate = (int)(treasure.count / (WS_MAX_TREASURE_COUNT * 1.0) * 100);
    return treasure;
}

void ws_initialize_player_save(const WS_WarioSave *save, WS_PlayerSave *player_save)
{
    player_save->lives = ws_get_player_lives(save);
    player_save->hearts = ws_get_player_hearts(save);
    player_save->total_coins = ws_get_player_coins(save);
    player_save->game_completed = ws_is_game_completed(save);
    player_save->treasure = ws_get_treasure_data(save);
    WS_Level player_level_data[WS_LEVELS_COUNT];
    ws_get_level_completion_rates(save, player_level_data);
    memcpy(player_save->levels, &player_level_data, sizeof(player_save->levels));
}
