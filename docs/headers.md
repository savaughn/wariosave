# WarioSave Library API Documentation

This document provides a detailed description of the functions provided by the WarioSave library.

## Function Definitions

### `uint8_t ws_get_decimal_byte(const uint8_t byte)`

Converts a byte stored in decimal format in memory to an integer.

- `byte`: The byte to convert.
- Returns: The decimal value of the byte.

### `uint32_t ws_get_decimal_bytes(const uint8_t byte1, const uint8_t byte2, const uint8_t byte3)`

Converts three bytes stored in decimal format in memory to an integer.

- `byte1`: The first byte to convert.
- `byte2`: The second byte to convert.
- `byte3`: The third byte to convert.
- Returns: The decimal value of the three bytes.

### `WS_FileError ws_load_save_to_buffer(WS_WarioGameSave *save, const char *file_path)`

Loads the save data into a WarioGameSave buffer.

- `save`: The WarioGameSave buffer to load the save data into.
- `file_path`: The path to the save file.
- Returns: The WS_FileError error code.

### `WS_Level *ws_get_completion_rate(const WS_WarioSave *save, WS_PlayerSave *player_save)`

Calculates the completion rate of each level and saves the data into a PlayerSave struct.

- `save`: The WarioSave struct.
- `player_save`: The PlayerSave struct.
- Returns: A pointer to the Level struct.

### `void ws_initialize_player_save(const WS_WarioSave *save, WS_PlayerSave *player_save)`

Initializes the PlayerSave struct with the data from the WarioSave struct.

- `save`: The WarioSave struct.
- `player_save`: The PlayerSave struct.

### `void ws_get_level_completion_rates(const WS_WarioSave *save, WS_Level *level_data)`

Calculates the completion rate of each level.

- `save`: The WarioSave struct.
- `level_data`: The array of Level structs.

### `uint8_t ws_get_player_lives(const WS_WarioSave *save)`

Gets the player's life count.

- `save`: The WarioSave struct.
- Returns: The player's life count.

### `uint8_t ws_get_player_hearts(const WS_WarioSave *save)`

Gets the player's heart count.

- `save`: The WarioSave struct.
- Returns: The player's heart count.

### `uint32_t ws_get_player_coins(const WS_WarioSave *save)`

Gets the player's coin count.

- `save`: The WarioSave struct.
- Returns: The player's coin count.

### `bool ws_is_game_completed(const WS_WarioSave *save)`

Checks if the game is completed.

- `save`: The WarioSave struct.
- Returns: A boolean indicating whether the game is completed.

### `WS_Treasure ws_get_treasure_data(const WS_WarioSave *save)`

Gets the save slot treasure data.

- `save`: The WarioSave struct.
- Returns: A Treasure struct.