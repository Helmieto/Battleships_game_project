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
* Functions to create preset board source file(failed)
*
*/

#include <iostream>
#include<fstream>
#include"Boards_storing_info.h"

using namespace std;

void print_board(char** board);

void set_preset_boards(char** board){

	int size = 10;
	ifstream Preset_boards;
	int option = 0;

	cout << "Chose preset board 1 or 2." << endl;
	cin >> option;

	if (Preset_boards.fail()) {
		cerr << "error" << endl;
		return;
	}
	
	if(option == 1){ 

		
		Preset_boards.open("Preset_board_1.txt"); 

		for (int m = 0; m < size; m++) {

			cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << endl;

			for (int n = 0; n < size; n++) {

				Preset_boards >> board[m][n];
			}
			
			print_board(board);
		}
		
		for (int m = 0; m < size; m++) {

			for (int n = 0; n < size; n++) {
				cout << board[m][n] << " ";
			}
			cout << endl;
			
		}
		Preset_boards.close();
	}

	else {
		Preset_boards.open("Preset_board_2.txt");
		
		for (int m = 0; m < size; m++) {
			for (int n = 0; n < size; n++) {
				Preset_boards >> board[m][n];
			}
		}
		for (int m = 0; m < size; m++) {
			for (int n = 0; n < size; n++) {
				cout << board[m][n] << " ";
			}
			cout << endl;
		}
		Preset_boards.close();
	}
	
}
