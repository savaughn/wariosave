/**
* Copyright (c) 2024 github/savaughn
* Distributed under the MIT License (MIT)
* (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)
*/

#ifndef HELPERS_H
#define HELPERS_H

#include <wariosave/common.h>

/**
 * Get the stored decimal value of a byte
 * @param byte The byte to convert
 * @return The decimal value of the byte
 * @details Some bytes are stored in dec format in memory instead of hex. So we have to convert the literal value to int
*/
int get_decimal_byte(int byte);

/**
 * Get the stored decimal value of 3 bytes
 * @param byte1 The first byte to convert
 * @param byte2 The second byte to convert
 * @param byte3 The third byte to convert
 * @return The decimal value of the 3 bytes
 * @details Some bytes are stored in dec format in memory instead of hex. So we have to convert the literal value to int

*/
uint32_t get_decimal_bytes(int byte1, int byte2, int byte3);

/*
* Load the save data into a buffer
* @param save The WarioSave buffer to load the save data into
* @param file_path The path to the save file
* @return The FileError error code
*/
int load_save_to_buffer(WarioGameSave *save, const char *file_path);

/**
 * Get the completion rate of each level saving the data into the PlayerSave struct
 * @param save The WarioSave struct
 * @param player_save The PlayerSave struct
*/
Level *get_completion_rate(WarioSave *save, PlayerSave *player_save);

/**
 * Initialize the PlayerSave struct with the data from the WarioSave struct
 * @param save The WarioSave struct
 * @param player_save The PlayerSave struct
*/
void initialize_player_save(WarioSave *save, PlayerSave *player_save);

/**
 * Get the completion rate of each level
 * @param save The WarioSave struct
 * @param level_data The array of Level structs
*/
void get_level_completion_rates(WarioSave *save, Level *level_data);

/**
 * Get the player's lives
 * @param save The WarioSave struct
 * @return The player's life count
*/
int get_player_lives(WarioSave *save);

/**
 * Get the player's hearts
 * @param save The WarioSave struct
 * @return The player's heart count
*/
int get_player_hearts(WarioSave *save);

/**
 * Get the player's coins
 * @param save The WarioSave struct
 * @return The player's coin count
*/
int get_player_coins(WarioSave *save);

/**
 * Get the player's game completion status
 * @param save The WarioSave struct
 * @return completed flag
*/
bool get_is_game_completed(WarioSave *save);

/**
 * Get the save slot treasure data
 * @param save The WarioSave struct
 * @return Treasure struct
*/
Treasure get_treasure_data(WarioSave *save);

#endif // HELPERS_H
