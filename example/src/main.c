/**
* Copyright (c) 2024 github/savaughn
* Distributed under the MIT License (MIT)
* (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)
*/

#include <wariosave.h>
#include "print.h"

int main(int argc, char *argv[])
{
    WarioSave save;
    PlayerSave player_save;

    if (argc != 2)
    {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    int error = load_save_to_buffer(&save, file_path);
    if (error != NO_ERROR)
    {
        return error;
    }
    initialize_player_save(&save, &player_save);
    print_player_save(&player_save);

    return 0;
}
