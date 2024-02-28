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
    WarioGameSave game_save;
    // Save slot buffer (3 file slots)
    WarioSave save_file[FILE_COUNT];
    // Formatted player save data (3 player saves)
    PlayerSave player_save[FILE_COUNT];

    if (argc != 2)
    {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    int error = load_save_to_buffer(&game_save, file_path);
    if (error != NO_ERROR)
    {
        return error;
    }

    for (int fileSlot = FILE_A; fileSlot < FILE_COUNT; fileSlot++)
    {
        save_file[fileSlot] = game_save.save[fileSlot];
        initialize_player_save(&save_file[fileSlot], &player_save[fileSlot]);
        print_player_save(&player_save[fileSlot]);
    }

    return 0;
}
