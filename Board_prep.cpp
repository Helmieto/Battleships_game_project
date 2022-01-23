#include<iostream>
#include<fstream>
#include<iomanip>
#include"Board_prep.h"
#include"Boards_storing_info.h"
#include"Preset_boards.h"

using namespace std;

void place_ship(char** board, int ship_size, char x, int y, char direction) {

	//turn input coordinates into indexes
	int index_x = x - 'A';
	int index_y = y - 1;

	//cases for every direction
	switch (direction) {

	//for horizontal direction row index stays constant
	case 'l':
	{
		for (int length = 0; length < ship_size; length++) {
			board[index_x][index_y] = '#';
			index_y--;
		}
		break;
	}
	case 'r':
	{
		for (int length = 0; length < ship_size; length++) {
			board[index_x][index_y] = '#';
			index_y++;
		}
		break;
	}

	//for vertical direction col index stays constant
	case 'u':
	{
		for (int length = 0; length < ship_size; length++) {
			board[index_x][index_y] = '#';
			index_x--;
		}
		break;
	}
	case 'd':
	{
		for (int length = 0; length < ship_size; length++) {
			board[index_x][index_y] = '#';
			index_x++;
		}
		break;
	}
	default:
		return;
	}
	return;
}


bool ship_is_on_the_board(char x, int y, char direction, int ship_size) {
	const int BOARD_SIZE = 10;
	//turn x coordinate into int
	int x_cord = x - 'A' + 1;

	//make sure u dont go to row index -1
	if (direction == 'l') {
		return (y - ship_size >= 0);
	}
	//make sure u dont go to row index 10
	else if (direction == 'r') {
		return (y + ship_size <= BOARD_SIZE + 1);
	}
	//make sure u dont go to col index 10
	else if (direction == 'd') {
		return (x_cord + ship_size <= BOARD_SIZE + 1);
	}
	//make sure u dont go to col index -1
	else if (direction == 'u') {
		return (x_cord - ship_size >= 0);
	}
	else return 0;

}

//fill another matrix with coordinates around an already placed ship
//on this coordinates u cant place a ship
bool** occupy_places(bool** occupied, char x, int y, char direction, int ship_size) {
	//u have to make sure that the ship is placed on the board
	if (ship_is_on_the_board(x, y, direction, ship_size)) {
		
		//turn to indexes
		int index_x = x - 'A';
		int index_y = y - 1;

		// for horizontal direction fill from the previos to the next row
		if (direction == 'r') {

			for (int i = index_x - 1; i <= index_x + 1; i++) {
				for (int j = index_y - 1; j <= index_y + ship_size; j++) {
					if (i >= 0 && j >= 0 && i < 10 && j < 10) {
						occupied[i][j] = true;
					}
				}
			}
		}

		if (direction == 'l') {

			for (int i = index_x - 1; i <= index_x + 1; i++) {
				for (int j = index_y - ship_size; j <= index_y + 1; j++) {
					if (i >= 0 && j >= 0 && i < 10 && j < 10) {
						occupied[i][j] = true;
					}
				}
			}
		}

		// for vertical direction fill from the previos to the next column
		if (direction == 'd') {

			for (int i = index_x - 1; i <= index_x + ship_size; i++) {
				for (int j = index_y - 1; j <= index_y + 1; j++) {
					if (i >= 0 && j >= 0 && i < 10 && j < 10) {
						occupied[i][j] = true;
					}
				}
			}
		}

		if (direction == 'u') {

			for (int i = index_x - ship_size; i <= index_x + 1; i++) {
				for (int j = index_y - 1; j <= index_y + 1; j++) {
					if (i >= 0 && j >= 0 && i < 10 && j < 10) {
						occupied[i][j] = true;
					}
				}
			}
		}
	}

	return occupied;
}

//check if you are boing to place a ship over another one already placed
bool ships_are_overlapping(bool** occupied, char x, int y, char direction, int ship_size) {

	//turn to indexes
	int index_x = x - 'A';
	int index_y = y - 1;

	//check if you are placing the ship on the board
	if (ship_is_on_the_board(x, y, direction, ship_size)) {

		//check if one part of the ship is going to be placed on an "occupied" place with cases for every direction
		if (direction == 'r') {

			for (int i = index_y; i < index_y + ship_size - 1; i++) {
				if (i >= 0 && i < 10) {
					if (occupied[index_x][i]) {
						return true;
					}
				}
			}
		}

		if (direction == 'l') {
			for (int i = index_y; i > index_y - ship_size + 1; i--) {
				if (i >= 0 && i < 10) {
					if (occupied[index_x][i]) {
						return true;
					}
				}
			}
		}

		if (direction == 'd') {
			for (int i = index_x; i < index_x + ship_size - 1; i++) {
				if (i >= 0 && i < 10) {
					if (occupied[i][index_y]) {
						return true;
					}
				}
			}
		}

		if (direction == 'u') {
			for (int i = index_x; i > index_x - ship_size + 1; i--) {
				if (i >= 0 && i < 10) {
					if (occupied[i][index_y]) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

//used to check if you are selecting a ship
bool is_a_ship(char** board, int ship_size, char x, int y, char direction) {

	int index_x = x - 'A';
	int index_y = y - 1;

	if (direction == 'r') {

		for (int i = index_y; i < index_y + ship_size - 1; i++) {
			if (i >= 0 && i < 10) {
				if (board[index_x][i] != '#') {
					return false;
				}
			}
		}
	}

	if (direction == 'l') {
		for (int i = index_y; i > index_y - ship_size + 1; i--) {
			if (i >= 0 && i < 10) {
				if (board[index_x][i] != '#') {
					return false;
				}
			}
		}
	}

	if (direction == 'd') {
		for (int i = index_x; i < index_x + ship_size - 1; i++) {
			if (i >= 0 && i < 10) {
				if (board[i][index_y] != '#') {
					return false;
				}
			}
		}
	}

	if (direction == 'u') {
		for (int i = index_x; i > index_x - ship_size + 1; i--) {
			if (i >= 0 && i < 10) {
				if (board[i][index_y] != '#') {
					return false;
				}
			}
		}
	}

	return true;
}

//deletes a ship and lets you relocate it whenever you want
void delete_ship(char** board, bool** occupied, int ship_size, int& ships_left, int& all_ships) {


	char x, direction;
	int y;
	//makes sure you are inputing coordinates of an existing ship
	do {
		cout << "Enter the starting location of the ship, and direction." << endl;
		cin >> x >> y >> direction;

		if (!is_a_ship(board, ship_size, x, y, direction)) {
			cout << "There is no such ship at these coordinates. Please try again." << endl;
		}


	} while (!is_a_ship(board, ship_size, x, y, direction));

	int index_x = x - 'A';
	int index_y = y - 1;

		switch (direction) {
		case 'l':
		{
			//temporary variale only for this cicle
			int increment_y = index_y;
			for (int length = 0; length < ship_size; length++) {
				board[index_x][increment_y] = '-';
				increment_y--;
			}

			for (int i = index_x - 1; i <= index_x + 1; i++) {
				for (int j = index_y - ship_size; j <= index_y + 1; j++) {
					if (i >= 0 && j >= 0 && i < 10 && j < 10) {
						occupied[i][j] = 0;
					}
				}
			}
			break;
		}

		case 'r':
		{
			//temporary variale only for this cicle
			int increment_y = index_y;

			//removes the ship
			for (int length = 0; length < ship_size; length++) {
				board[index_x][increment_y] = '-';
				increment_y++;
			}

			//frees the "occupied" places
			for (int i = index_x - 1; i <= index_x + 1; i++) {
				for (int j = index_y - 1; j <= index_y + ship_size; j++) {
					if (i >= 0 && j >= 0 && i < 10 && j < 10) {
						occupied[i][j] = 0;
					}
				}
			}
			break;
		}

		case 'u':
		{
			//temporary variale only for this cicle
			int increment_x = index_x;
			for (int length = 0; length < ship_size; length++) {
				board[increment_x][index_y] = '-';
				increment_x--;
			}

			for (int i = index_x - ship_size; i <= index_x + 1; i++) {
				for (int j = index_y - 1; j <= index_y + 1; j++) {
					if (i >= 0 && j >= 0 && i < 10 && j < 10) {
						occupied[i][j] = 0;
					}
				}
			}
			break;
		}

		case 'd':
		{
			//temporary variale only for this cicle
			int increment_x = index_x;
			for (int length = 0; length < ship_size; length++) {
				board[increment_x][index_y] = '-';
				increment_x++;
			}

			for (int i = index_x - 1; i <= index_x + ship_size; i++) {
				for (int j = index_y - 1; j <= index_y + 1; j++) {
					if (i >= 0 && j >= 0 && i < 10 && j < 10) {
						occupied[i][j] = false;
					}
				}
			}
			break;
		}

		default:
			return;
		}
		ships_left++;
		all_ships++;

	return;
}



void arraging_ship_process(char** board, bool** occupied, int ship_size, int& ships_left, int& all_ships) {

	if (ships_left > 0) {

		char direction;
		char x;
		int y = 0;

	    //input valid coordinates and direction
		do {

			cout << "Input starting location coordinates: x-> capital letter from A to J, y->number from 1 to 10 and direction(l, r, u, d" << endl;
			cin >> x >> y >> direction;

			if (!ship_is_on_the_board(x, y, direction, ship_size)) {
				cout << "Ships cannot be placed outside the board. Please try again." << endl;
			}


			if (ships_are_overlapping(occupied, x, y, direction, ship_size)) {
				cout << "Ships cannot overlap. Please try again." << endl;
			}

		} while (!ship_is_on_the_board(x, y, direction, ship_size) ||
			ships_are_overlapping(occupied, x, y, direction, ship_size));

		
		place_ship(board, ship_size, x, y, direction);
		occupy_places(occupied, x, y, direction, ship_size);
		ships_left--;
		all_ships--;

	}
	else {
		cout << "No more ships of this type left left" << endl;
	}
}




void game_preparation(char** board) {

	//char option;
	//cout << "Do you want to chose a preset board? y/n" << endl; cin >> option;
		
	//if (option == 'y') {
	//	set_preset_boards(board); }
	
	//else {}

		char ship_type;

		int ship_size = 0;

		//number of ships from every type
		int all_ships_left = 10;
		int small_ships = 4;
		int medium_ships = 3;
		int large_ships = 2;
		int cruisers = 1;

		//create matrix to store the places you cannot place a ship on
		bool** occupied = save_data();

		//place ships until you have none
		while (all_ships_left) {

			//validation could be added in case user cant read instructions
			cout << "Input type of the ship. s-small, m-medium, l-large, c-cruiser" << endl;
			cin >> ship_type;

			//cases for every ship type
			switch (ship_type) {
			case 's':
			{
				//set the ship size according to the type of the ship
				ship_size = 2;
				arraging_ship_process(board, occupied, ship_size, small_ships, all_ships_left);

				break;
			}
			case 'm':
			{
				ship_size = 3;
				arraging_ship_process(board, occupied, ship_size, medium_ships, all_ships_left);

				break;

			}
			case 'l':
			{
				ship_size = 4;
				arraging_ship_process(board, occupied, ship_size, large_ships, all_ships_left);

				break;

			}
			case 'c':
			{
				ship_size = 6;
				arraging_ship_process(board, occupied, ship_size, cruisers, all_ships_left);

				break;
			}
			}
			char yes_or_no;

			cout << "Do you want to see your board? y/n" << endl; cin >> yes_or_no;

			if (yes_or_no == 'y') {
				print_board(board);
			}

			//give option to delete a ship
			cout << endl << "Do you want to delete a ship? y/n" << endl;
			cin >> yes_or_no;

			if (yes_or_no == 'y') {

				//show board to make it easy to chose the ship
				print_board(board);
				cout << endl;

				//validation could be added in case user cant read instructions
				cout << "See the board and decide exactly which ship you want to delete and input its type:s - small, m - medium, l - large, c - cruiser" << endl;
				cin >> ship_type;

				//cases for every ship type
				switch (ship_type) {
				case 's':
				{

					ship_size = 2;
					delete_ship(board, occupied, ship_size, small_ships, all_ships_left);

					break;
				}
				case 'm':
				{
					ship_size = 3;
					delete_ship(board, occupied, ship_size, medium_ships, all_ships_left);

					break;

				}
				case 'l':
				{
					ship_size = 4;
					delete_ship(board, occupied, ship_size, large_ships, all_ships_left);

					break;

				}
				case 'c':
				{
					ship_size = 6;
					delete_ship(board, occupied, ship_size, cruisers, all_ships_left);

					break;
				}
				}
			}


			//option to see the board
			cout << "Do you want to see your board? y/n" << endl;
			cin >> yes_or_no;

			if (yes_or_no == 'y') {
				print_board(board);
				cout << endl;
			}
		}
		//delete stored data for this part of the game
		void delete_data(bool** occupied);
}
