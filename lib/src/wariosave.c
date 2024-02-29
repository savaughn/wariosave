/**
 * Copyright (c) 2024 github/savaughn
 * Distributed under the MIT License (MIT)
 * (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)
 */

#include <wariosave/helpers.h>

#define BUFFER_PADDING 0x14

int get_decimal_byte(int byte)
{
    char buffer[3];
    snprintf(buffer, sizeof(buffer), "%02x", byte);
    return (int)strtol(buffer, NULL, 10);
}

uint32_t get_decimal_bytes(int byte1, int byte2, int byte3)
{
    char buffer[MAX_COIN_DIGITS_STR];

    // Format the string into the buffer
    // Each byte is already in dec format. Use %x
    // so that the values are not converted "from hex to dec"
    snprintf(buffer, sizeof(buffer), "%x%02x%02x", byte1, byte2, byte3);
    return (uint32_t)strtol(buffer, NULL, 10);
}

int load_save_to_buffer(WarioGameSave *save, const char *file_path)
{
    FILE *file = fopen(file_path, "rb");
    FileError error = NO_ERROR;
    if (file == NULL)
    {
        perror("Error opening file");
        return FILE_ERROR;
    }

    for (int fileSlot = FILE_A, offset = SAVE_FILE_A_OFFSET; fileSlot < FILE_COUNT; fileSlot++, offset += SAVE_FILE_OFFSET)
    {
        if (fseek(file, offset, SEEK_SET) != 0)
        {
            perror("Error seeking to the file c byte");
            fclose(file);
            return MEMORY_ERROR;
        }

        uint8_t byte_array[SAVE_STRUCT_SIZE];
        size_t bytes_read = fread(byte_array, 1, SAVE_STRUCT_SIZE, file);

        // Check if the read operation was successful
        if (bytes_read != SAVE_STRUCT_SIZE)
        {
            perror("Error reading from file");
            fclose(file);
            return READ_ERROR;
        }

        // WarioSave struct is modeled after the byte array
        save->save[fileSlot] = *(WarioSave *)byte_array;
    }

    // Close the file
    fclose(file);

    return error;
}

void get_level_completion_rates(WarioSave *save, Level *level_data)
{
    uint8_t level_completion_bitmask[LEVELS_COUNT] = {
        save->sMapRiceBeachCompletion,
        save->sMapMtTeapotCompletion,
        save->sMapStoveCanyonCompletion,
        save->sMapSSTeacupCompletion,
        save->sMapParsleyWoodsCompletion,
        save->sMapSherbetLandCompletion,
        save->sMapSyrupCastleCompletion};
    for (int i = 0; i < LEVELS_COUNT; i++)
    {
        int count = 0;
        uint8_t course_exit_count = default_level_data[i].course_exit_count;
        level_data[i].completion_bitmask = level_completion_bitmask[i];
        for (int j = 0; j < course_exit_count; j++)
        {
            count += (level_completion_bitmask[i] >> j) & 1;
            level_data[i].completion_rate = (int)(count / (course_exit_count * 1.0) * 100);
        }
    }
}

int get_player_lives(WarioSave *save)
{
    return get_decimal_byte(save->sLives);
}

int get_player_hearts(WarioSave *save)
{
    return get_decimal_byte(save->sHearts);
}

int get_player_coins(WarioSave *save)
{
    return get_decimal_bytes(save->sTotalCoins_High, save->sTotalCoins_Mid, save->sTotalCoins_Low);
}

bool get_is_game_completed(WarioSave *save)
{
    return (bool)save->sGameCompleted;
}

Treasure get_treasure_data(WarioSave *save)
{
    Treasure treasure;
    treasure.count = 0;
    treasure.completion_rate = 0;
    for (int i = 0; i < MAX_TREASURE_COUNT; i++)
    {
        treasure.obtained[i] = 0;
        // first byte in sTreasures is unused 
        if ((save->sTreasures >> (i+1)) & 1)
        {
            treasure.obtained[i] = 1;
            treasure.count++;
        }
    }

    treasure.completion_rate = (int)(treasure.count / (MAX_TREASURE_COUNT * 1.0) * 100);
    return treasure;
}

void initialize_player_save(WarioSave *save, PlayerSave *player_save)
{
    player_save->lives = get_player_lives(save);
    player_save->hearts = get_player_hearts(save);
    player_save->total_coins = get_player_coins(save);
    player_save->game_completed = get_is_game_completed(save);
    player_save->treasure = get_treasure_data(save);
    Level player_level_data[LEVELS_COUNT];
    get_level_completion_rates(save, player_level_data);
    memcpy(player_save->levels, &player_level_data, sizeof(player_save->levels));
}
