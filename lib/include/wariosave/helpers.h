/**
* Copyright (c) 2025 github/savaughn
* Distributed under the MIT License (MIT)
* (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)
*/

#ifndef WS_HELPERS_H
#define WS_HELPERS_H

#include <wariosave/common.h>

/**
 * Get the stored decimal value of a byte
 * @param byte The byte to convert
 * @return The decimal value of the byte
 * @details Some bytes are stored in dec format in memory instead of hex. So we have to convert the literal value to int
*/
uint8_t ws_get_decimal_byte(const uint8_t byte);

/**
 * Get the stored decimal value of 3 bytes
 * @param byte1 The first byte to convert
 * @param byte2 The second byte to convert
 * @param byte3 The third byte to convert
 * @return The decimal value of the 3 bytes
 * @details Some bytes are stored in dec format in memory instead of hex. So we have to convert the literal value to int

*/
uint32_t ws_get_decimal_bytes(const uint8_t byte1, const uint8_t byte2, const uint8_t byte3);

/*
* Load the save data into a buffer
* @param save The WS_WarioSave buffer to load the save data into
* @param file_path The path to the save file
* @return The WS_FileError error code
*/
WS_FileError ws_load_save_to_buffer(WS_WarioGameSave *save, const char *file_path);

/**
 * Get the completion rate of each level saving the data into the WS_PlayerSave struct
 * @param save The WS_WarioSave struct
 * @param player_save The WS_PlayerSave struct
*/
WS_Level *get_completion_rate(const WS_WarioSave *save, WS_PlayerSave *player_save);

/**
 * Initialize the WS_PlayerSave struct with the data from the WS_WarioSave struct
 * @param save The WS_WarioSave struct
 * @param player_save The WS_PlayerSave struct
*/
void ws_initialize_player_save(const WS_WarioSave *save, WS_PlayerSave *player_save);

/**
 * Get the completion rate of each level
 * @param save The WS_WarioSave struct
 * @param level_data The array of WS_Level structs
*/
void ws_get_level_completion_rates(const WS_WarioSave *save, WS_Level *level_data);

/**
 * Get the player's lives
 * @param save The WS_WarioSave struct
 * @return The player's life count
*/
uint8_t ws_get_player_lives(const WS_WarioSave *save);

/**
 * Get the player's hearts
 * @param save The WS_WarioSave struct
 * @return The player's heart count
*/
uint8_t ws_get_player_hearts(const WS_WarioSave *save);

/**
 * Get the player's coins
 * @param save The WS_WarioSave struct
 * @return The player's coin count
*/
uint32_t ws_get_player_coins(const WS_WarioSave *save);

/**
 * Get the player's game completion status
 * @param save The WS_WarioSave struct
 * @return completed flag
*/
bool ws_is_game_completed(const WS_WarioSave *save);

/**
 * Get the save slot treasure data
 * @param save The WS_WarioSave struct
 * @return WS_Treasure struct
*/
WS_Treasure ws_get_treasure_data(const WS_WarioSave *save);

#endif // WS_HELPERS_H
