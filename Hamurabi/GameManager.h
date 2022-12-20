#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "GameParameters.h"

using std::string;

struct GameManager
{
	GameParameters parameters;
	int current_turn;
	bool is_ended;
	string save_file_path = "SaveFile.txt";
	
	void init();

	void start_game();
	void make_turn();
	void end_game(string result);
	void restart_game();

	void print_statistics();
	void get_player_input();
	void check_player_input();
	void calculate_params();
	void check_for_end();

	void want_to_save();
	bool check_for_save();
	void save_to_file();
	void load_from_file();
	void delete_save();

};