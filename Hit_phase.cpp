#include <iostream>
#include<iomanip>
//#include"Board_prep.h" 
#include"Boards_storing_info.h"

using namespace std;


bool hit(char** board, char** enemy_board, bool** already_hit, char x, int y) {

	int index_x = (x - 'A');
	int index_y = y - 1;

	//if you hit a ship
	if (board[index_x][index_y] == '#') {

		enemy_board[index_x][index_y] = 'H';
		already_hit[index_x][index_y] = true;

		return true;
	}

	//if you miss
	else {
		enemy_board[index_x][index_y] = 'M';
		already_hit[index_x][index_y] = true;

		return false;
	}

}

//check if u hit on the board
bool valid_hit(char x, int y) {

	return (x >= 'A' && y >= 0 && x <= 'J' && y <= 10);
}


void hit_phase(char** board_pl1, char** board_pl2) {

	//create boards that the opponent can see
	char** player_1_board = make_board();
	char** player_2_board = make_board();
	
	//store places that are occupied by ship
	//in a later update could be added function to tracks sunken ships
	int player_1_ships = 31;
	int player_2_ships = 31;

	//stores already hit positions
	bool** already_hit_pl1 = save_data();
	bool** already_hit_pl2 = save_data();
	
	char x = 0;
	int y = 0;
	int index_x = 0;
	int index_y = 0;

	char yes_or_no = 0;

	bool is_a_hit;


	//Game starts

	//play until there are ships left
	while (player_1_ships && player_2_ships) {

		is_a_hit = true;

		//PLAYER 1

		//play until u miss or sink all enemy ships
		while (is_a_hit && player_2_ships) {

			cout << "Player 1 turn." << endl << endl;

			//option to see where he has hit
			cout << "Do you want to see the enemy board? y/n" << endl;
			cin >> yes_or_no;

			cout << endl;

			if (yes_or_no == 'y') {
				print_board(player_2_board);
			}

			cout << endl;

			cout << "Input coordinates that you want to attack." << endl;

			//input valid coordinates
			do {
				cin >> x >> y;

				index_x = x - 'A';
				index_y = y - 1;

				if (already_hit_pl2[index_x][index_y]) {
					cout << "You have already taken a shot here. Please try again." << endl;
				}
				if (!valid_hit(x, y)) {
					cout << "You cant score a hit outside the board. Please try again." << endl;
				}

			} while (already_hit_pl2[index_x][index_y] || !valid_hit(x, y));

			//if you miss
			if (!hit(board_pl2, player_2_board, already_hit_pl2, x, y)) {
				is_a_hit = false;
				cout << "You missed!" << endl;
			}

			//if you hit
			else {
				cout << "You have scored a hit!" << endl;
				player_2_ships--;
			}
		}
		//set it to be true again so that the second player can play his turn
		is_a_hit = true;

		//PLAYER 2

		//play until you score a hit, sink all enemy ships or lose your own
		while (is_a_hit && player_1_ships && player_2_ships) {

			cout << "Player 2 turn." << endl << endl;

			cout << "Do you want to see the enemy board? y/n" << endl;
			cin >> yes_or_no;

			cout << endl;

			if (yes_or_no == 'y') {
				print_board(player_1_board);
			}

			cout << endl;

			cout << "Input coordinates that you want to attack." << endl;

			do {
				cin >> x >> y;

				index_x = x - 'A';
				index_y = y - 1;

				if (already_hit_pl1[index_x][index_y]) {
					cout << "You have already taken a shot here. Please try again." << endl;
				}
				if (!valid_hit(x, y)) {
					cout << "You cant score a hit outside the board. Please try again." << endl;
				}

			} while (already_hit_pl1[index_x][index_y] || !valid_hit(x, y));

			if (!hit(board_pl1, player_1_board, already_hit_pl1, x, y)) {
				is_a_hit = false;
				cout << "You missed!" << endl;
			}
			else {
				cout << "You have scored a hit!" << endl;
				player_1_ships--;
			}

		}
	}

	if (player_1_ships > player_2_ships) {
		cout << "Player 1 wins!!!" << endl;
	}
	else {
		cout << "Player 2 wins!!!" << endl;
	}

	//delete stored data for this part of the game
	void delete_data(bool** already_hit_pl1);
	void delete_data(bool** already_hit_pl2);
	void delete_board(char** player_1_board);
	void delete_board(char** player_2_board);
}