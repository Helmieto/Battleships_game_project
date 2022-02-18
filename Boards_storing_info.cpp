/**
*
* Solution to course project # <номер на вариант>
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Milen Temelkov
* @idnumber 2MI0600114
* @compiler VC
*
* Functions to create matrices that store info source file
*
*/

#include<iostream>
#include<iomanip>
#include"Boards_storing_info.h"
using namespace std;

//creates the board
char** make_board() {

	char** board = new char* [10];
	for (int i = 0; i < 10; i++) {
		board[i] = new char[10];
	}

	const int SIZE = 10;

	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			board[row][col] = '-';
		}
	}

	return board;
}

//prints the board
void print_board(char** board) {

	int board_size = 10;
	int symbol_for_rows = 2;
	cout << setw(5);

	for (int i = 0; i < 10; i++) {
		cout << i + 1 << setw(3);
	}

	cout << endl;
	for (int i = 0; i < board_size * 3 + 2; i++) {
		cout << '_';
	}
	cout << endl;

	for (int row = 0; row < 10; row++) {

		cout << char('A' + row) << '|' << setw(3);

		for (int col = 0; col < 10; col++) {
			cout << board[row][col] << setw(3);
		}
		cout << '|' << endl;
	}


	cout << setw(symbol_for_rows) << '|';

	for (int i = 0; i < board_size * 3 + symbol_for_rows; i++) {
		cout << '_';
	}
	cout << '|';
}

//creates boolean matrix to store information for hit spaces or spaces occupied by ships
bool** save_data() {

	bool** occupied = new bool* [10];

	for (int i = 0; i < 10; i++) {
		occupied[i] = new bool[10];
	}

	int SIZE = 10;

	for (int horizontal = 0; horizontal < SIZE; horizontal++) {
		for (int vertical = 0; vertical < SIZE; vertical++) {
			occupied[horizontal][vertical] = false;
		}
	}

	return occupied;
}

//print stored information
void print_saved_data(bool** occupied) {
	for (int row = 0; row < 10; row++) {

		for (int col = 0; col < 10; col++) {
			cout << occupied[row][col] << setw(3);
		}
		cout << endl;
	}
}


void clear_screen() {
	for (int i = 0; i < 40; i++) {
		cout << endl;
	}
}

void delete_board(char** board) {

	for (int i = 0; i < 10; i++) {
		delete[] board[i];
	}
	delete[] board;
}

void delete_data(bool** data) {
	for (int i = 0; i < 10; i++) {
		delete[] data[i];
	}
	delete[] data;
}