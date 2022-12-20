#include "GameParameters.h"

void GameParameters::init() 
{
	city_population = 100;
	wheat_amount = 2800;
	city_area = 1000;

	acres_to_buy = 0;
	acres_to_sell = 0;
	wheat_to_eat = 0;
	acres_to_cultivate = 0;

	is_input_valid = false;

	// calculated parameters:
	cost_of_acre = 0;
	calc_cost_of_acre();
	wheat_per_acre = 0;

	deaths_from_hunger = 0;
	citizens_arrived = 0;
	wheat_gathered = 0;
	wheat_eaten_by_rats = 0;

	deaths_from_hunger_stat = 0;
	acres_per_citizen_stat = 0;

	was_plague = false;

}

void GameParameters::add_turn_stats()
{
	double curr_deaths_from_hunger = deaths_from_hunger * 100 / (double)city_population;
	deaths_from_hunger_stat += curr_deaths_from_hunger;
	death_ratio = (int)(curr_deaths_from_hunger);

	acres_per_citizen_stat += city_area / (double)city_population;
}

void GameParameters::calc_final_stats()
{
	
	P = (int) deaths_from_hunger_stat / number_of_turns;
	L = (int) acres_per_citizen_stat / number_of_turns;
}

void GameParameters::calc_cost_of_acre()
{
	cost_of_acre = generate_random_number(cost_of_acre_min, cost_of_acre_max);
}

void GameParameters::calc_wheat_gathered()
{

	wheat_per_acre = generate_random_number(wheat_per_acre_min, wheat_per_acre_max);

	wheat_gathered = wheat_per_acre * acres_to_cultivate;
	wheat_amount += wheat_gathered;

}

void GameParameters::calc_wheat_eaten_by_rats()
{
	int rand_val = generate_random_number(wheat_eaten_by_rats_min, wheat_eaten_by_rats_max);

	wheat_eaten_by_rats = (wheat_amount / 100.0) * rand_val;

	wheat_amount -= wheat_eaten_by_rats;

}

void GameParameters::calc_deaths_from_hunger()
{ 

	int people_with_food = wheat_to_eat / wheat_per_citizen;

	if (people_with_food < city_population)
	{
		deaths_from_hunger = city_population - people_with_food;
	}
	else
	{
		deaths_from_hunger = 0;
	}

	city_population -= deaths_from_hunger;
}

void GameParameters::calc_citizens_arrived()
{
	citizens_arrived = (deaths_from_hunger / 2) + (5 - wheat_per_acre) * wheat_amount / 600 + 1;

	if (citizens_arrived < 0)
	{
		citizens_arrived = 0;
	}
	else if (citizens_arrived > 50)
	{
		citizens_arrived = 50;
	}
	
	city_population += citizens_arrived;
}

void GameParameters::calc_was_plague()
{
	int min_val = 0;
	int max_val = 100;

	int rand_val = generate_random_number(min_val, max_val);

	if (rand_val < plague_probability)
	{
		was_plague = true;
		city_population /= 2;
	}
	else
	{
		was_plague = false;
	}
}

// got this function from cppreference, have no idea how it works

int GameParameters::generate_random_number(int min_value, int max_value)
{
	std::random_device r;

	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(min_value, max_value);
	int mean = uniform_dist(e1);

	return mean;
}