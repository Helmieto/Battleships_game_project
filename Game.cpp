#include <iostream>
#include<iomanip>
#include<fstream>
#include"Board_prep.h" 
#include"Boards_storing_info.h"
#include"Hit_phase.h"

using namespace std;

void game() {
	char** board_player_1 = make_board();
	char** board_player_2 = make_board();

	cout << "PLAYER 1" << endl << endl;

	game_preparation(board_player_1);

	print_board(board_player_1);

	cout << "PLAYER 2" << endl << endl;

	game_preparation(board_player_2);

	print_board(board_player_2);

	hit_phase(board_player_1, board_player_2);

	void delete_board(char** board_player_1);
	void delete_board(char** board_player_2);

	return;
}