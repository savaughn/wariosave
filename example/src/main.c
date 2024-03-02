/**
 * Copyright (c) 2024 github/savaughn
 * Distributed under the MIT License (MIT)
 * (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)
 */

#include <wariosave.h>
#include "print.h"

int main(int argc, char *argv[])
{
    // Complete savefile buffer
    WS_WarioGameSave game_save;
    // Save slot buffer (3 file slots)
    WS_WarioSave save_file[WS_MAX_FILE_SLOT_COUNT];
    // Formatted player save data (3 player saves)
    WS_PlayerSave player_save[WS_MAX_FILE_SLOT_COUNT];

    if (argc != 2)
    {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    WS_FileError error = ws_load_save_to_buffer(&game_save, file_path);
    if (error != NO_ERROR)
    {
        return error;
    }

    for (uint8_t file_slot = FILE_A; file_slot < FILE_COUNT; file_slot++)
    {
        save_file[file_slot] = game_save.save[file_slot];
        ws_initialize_player_save(&save_file[file_slot], &player_save[file_slot]);
        print_player_save(&player_save[file_slot]);
    }

    return 0;
}
