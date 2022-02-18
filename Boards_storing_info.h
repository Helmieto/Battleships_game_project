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

#pragma once


char** make_board();

void print_board(char** board);

bool** save_data();

void print_saved_data(bool** occupied);

void clear_screen();

void delete_board(char** board);

void delete_data(bool** data);