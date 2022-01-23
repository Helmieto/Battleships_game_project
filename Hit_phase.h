#pragma once

bool hit(char** board, char** enemy_board, bool** already_hit, char x, int y);

bool valid_hit(char x, int y);

void hit_phase(char** board1, char** board2);
