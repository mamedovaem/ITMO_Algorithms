#pragma once
#include <random>


struct GameParameters
{
	// open parameters:

	int city_population;
	int wheat_amount;
	int city_area;
	int cost_of_acre;
	int wheat_per_acre;

	int deaths_from_hunger;
	int citizens_arrived;
	int wheat_gathered;
	int wheat_eaten_by_rats; 

	bool was_plague;

	double deaths_from_hunger_stat;
	double acres_per_citizen_stat;

	int P = 0; // death statistics
	int L = 0; // land statistics

	//user input:

	int acres_to_buy;
	int acres_to_sell;
	int wheat_to_eat;
	int acres_to_cultivate;

	bool is_input_valid;

	void init();

	void calc_cost_of_acre();
	void calc_wheat_gathered();
	void calc_wheat_eaten_by_rats();
	void calc_deaths_from_hunger();
	void calc_citizens_arrived();
	void calc_was_plague();
	
	void add_turn_stats();
	void calc_final_stats();


	// inner game parameters:

	int wheat_needed = 0;

	const int number_of_turns = 10;

	const int wheat_per_citizen = 20; // how much wheat is eaten by one citizen;
	const int acres_cultivated = 10; // how many acres can be cultivated by one citizen;
	const double wheat_for_seeds = 0.5; // how much wheat is needed for seeds per acre;
	const int death_ratio_max = 45; // percent of population died from hunger leading to losing game;
	
	int death_ratio = 0;

	// ranges for random values:

	const int cost_of_acre_min = 17; // int min range value
	const int cost_of_acre_max = 26; // int min range value

	const int wheat_per_acre_min = 1; // int min range value
	const int wheat_per_acre_max = 6; // int max range value

	const int wheat_eaten_by_rats_min = 0; // int min range value
	const int wheat_eaten_by_rats_max = 7; // int max range value
	
	const int plague_probability = 15; // probability in percents

	int generate_random_number(int min_value, int max_value);
};