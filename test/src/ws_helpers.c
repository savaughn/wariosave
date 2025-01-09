/**
 * Copyright (c) 2025 github/savaughn
 * Distributed under the MIT License (MIT)
 * (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)
 */

#include <CUnit/Basic.h>
#include <wariosave/helpers.h>

void test_get_decimal_byte(void) {
    CU_ASSERT_EQUAL(ws_get_decimal_byte(0x0), 0);
    CU_ASSERT_EQUAL(ws_get_decimal_byte(0x99), 99);
}

void test_get_decimal_bytes(void) {
    CU_ASSERT_EQUAL(ws_get_decimal_bytes(0x00, 0x00, 0x00), 0);
    CU_ASSERT_EQUAL(ws_get_decimal_bytes(0x01, 0x50, 0x43), 15043);
    CU_ASSERT_EQUAL(ws_get_decimal_bytes(0x99, 0x99, 0x99), 999999);
}

void test_load_save_to_buffer(void){
    WS_WarioGameSave game_save;
    WS_WarioSave save_file;
    const char *file_path = "saves/wario.sav";

    WS_FileError error = ws_load_save_to_buffer(&game_save, file_path);
    CU_ASSERT_EQUAL(error, NO_ERROR);
    save_file = game_save.save[FILE_A];

    CU_ASSERT_EQUAL(save_file.sGameCompleted, 1);
}

void test_get_completion_rate(void) {
    WS_WarioSave save = {
        .sMapRiceBeachCompletion = 0b01111111,
        .sMapMtTeapotCompletion = 0b01111111,
        .sMapStoveCanyonCompletion = 0b00111111,
        .sMapSSTeacupCompletion = 0b00011111,
        .sMapParsleyWoodsCompletion = 0b00111111,
        .sMapSherbetLandCompletion = 0b00111111,
        .sMapSyrupCastleCompletion = 0b00000111
    };
    WS_Level level_data[WS_LEVELS_COUNT];
    ws_get_level_completion_rates(&save, level_data);
    for (int i = 0; i < WS_LEVELS_COUNT; i++) {
        CU_ASSERT_EQUAL(level_data[i].completion_rate, 100);
    }
}

void test_get_player_lives(void) {
    WS_WarioSave save = {.sLives = 5};
    CU_ASSERT_EQUAL(ws_get_player_lives(&save), 5);
}

void test_get_player_hearts(void) {
    WS_WarioSave save = {.sHearts = 3};
    CU_ASSERT_EQUAL(ws_get_player_hearts(&save), 3);
}

void test_get_player_coins(void) {
    WS_WarioSave save = {.sTotalCoins_High = 0x01, .sTotalCoins_Mid = 0x50, .sTotalCoins_Low = 0x43};
    CU_ASSERT_EQUAL(ws_get_player_coins(&save), 15043);
}

void test_is_game_completed(void) {
    WS_WarioSave save = {.sGameCompleted = 1};
    CU_ASSERT_EQUAL(ws_is_game_completed(&save), true);
}

void test_get_treasure_data(void) {
    WS_WarioSave save = {.sTreasures = 0b1111111111111110};
    WS_Treasure treasure = ws_get_treasure_data(&save);
    CU_ASSERT_EQUAL(treasure.completion_rate, 100);
}

int main(void) {
    CU_pSuite suite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    suite = CU_add_suite("helpers_test_suite", 0, 0);
    if (NULL == suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(suite, "test_get_decimal_byte", test_get_decimal_byte)) ||
        (NULL == CU_add_test(suite, "test_get_decimal_bytes", test_get_decimal_bytes)) ||
        (NULL == CU_add_test(suite, "test_load_save_to_buffer", test_load_save_to_buffer)) ||
        (NULL == CU_add_test(suite, "test_get_player_lives", test_get_player_lives)) ||
        (NULL == CU_add_test(suite, "test_get_player_hearts", test_get_player_hearts)) ||
        (NULL == CU_add_test(suite, "test_get_player_coins", test_get_player_coins)) ||
        (NULL == CU_add_test(suite, "test_get_completion_rate", test_get_completion_rate)) ||
        (NULL == CU_add_test(suite, "test_is_game_completed", test_is_game_completed)) ||
        (NULL == CU_add_test(suite, "test_get_treasure_data", test_get_treasure_data))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}