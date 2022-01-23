#pragma once


char** make_board();

void print_board(char** board);

bool** save_data();

void print_saved_data(bool** occupied);

void clear_screen();

void delete_board(char** board);

void delete_data(bool** data);