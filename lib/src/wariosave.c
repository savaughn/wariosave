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

void get_completion_rate(WarioSave *save, PlayerSave *player_save)
{
    uint8_t levelCompletions[LEVELS_COUNT] = {
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
        uint8_t courseExitCount = defaultLevelData[i].courseExitCount;
        player_save->levels[i].completionBitmask = levelCompletions[i];
        for (int j = 0; j < courseExitCount; j++)
        {
            count += (levelCompletions[i] >> j) & 1;
            player_save->levels[i].completionRate = (int)(count / (courseExitCount * 1.0) * 100);
        }
    }
}

void initialize_player_save(WarioSave *save, PlayerSave *player_save)
{
    player_save->Lives = get_decimal_byte(save->sLives);
    player_save->Hearts = get_decimal_byte(save->sHearts);
    player_save->TotalCoins = get_decimal_bytes(save->sTotalCoins_High, save->sTotalCoins_Mid, save->sTotalCoins_Low);
    player_save->GameCompleted = (bool)save->sGameCompleted;

    get_completion_rate(save, player_save);
}
