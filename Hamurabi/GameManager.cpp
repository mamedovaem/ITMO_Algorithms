#include "GameManager.h"
#include <filesystem>

void GameManager::init()
{
	current_turn = 0;
	is_ended = false;
	parameters.init();
}

void GameManager::start_game()
{
	if (check_for_save())
	{
		char answer;
		bool got_answer = false;

		while (!got_answer)
		{
			std::cout << "���������� ���������� ����? Y/N" << std::endl;
			std::cin >> answer;

			if (answer == 'Y' || answer == 'y')
			{
				load_from_file();
				//print_statistics();
				got_answer = true;
			}
			else if (answer == 'N' || answer == 'n')
			{
				delete_save();
				got_answer = true;
			}
			else
			{
				std::cout << "��������, � �� �������. ����������, ��������� ����." << std::endl;
			}
		}
	}
}

void GameManager::restart_game()
{
	this->init();
}

void GameManager::make_turn()
{
	want_to_save();

	current_turn++;

	print_statistics();
	get_player_input();
	calculate_params();
	check_for_end();

}

void GameManager::end_game(string result)
{
	is_ended = true;

	if (result == "City is instinct")
	{
		std::cout << "����� ��������� �����, � ������ ��� ������ ����� ���������." << std::endl;

	}
	else if (result == "Bad death ratio")
	{
		std::cout << "�� ���� ��� �� ������ ������ ����� �������� ��������� ������, � ��� �������� ������ ������." << std::endl;
	}
	else if (result == "Reign end")
	{
		
		if (parameters.P > 33 || parameters.L < 7) // ������ ���������� ���������
		{
			std::cout << "��-�� ����� ���������������� � ����������, ����� ������� ����, � ������ ��� �� ������." << std::endl;
			std::cout << "������ �� ��������� ������� ������ ������������� � ��������." << std::endl;
		}
		else if (parameters.P > 10 || parameters.L < 9) // ������ ���������� ���������
		{
			std::cout << "�� ������� �������� �����, ������� ������ � ����� ��������. " << std::endl;
			std::cout << "����� �������� � �����������, � ����� ������ �� ������ ������ ��� ����������." << std::endl;
		}
		else if (parameters.P > 3 || parameters.L < 10) // ������ ���������� ���������
		{
			std::cout << "�� ���������� ������ �������, � ���, �������, ���� ���������������, " << std::endl;
			std::cout << "�� ������ ������ �� ������� ��� �� ����� ������ �����." << std::endl;
		}
		else
		{
			std::cout << "����������! ���� �������, �������� � ���������� ������ �� ���������� �� �����." << std::endl;
		}
	}

	delete_save();

}

void GameManager::print_statistics()
{
	

	std::cout << "��� ����������, �������� �������� ����" << std::endl;
	std::cout << "\t� ���� " << current_turn << " ������ ����������� ���������" << std::endl;

	if (current_turn == 1)
	{
		std::cout << "\t��������� ������ ���������� " << parameters.city_population << " �������;" << std::endl;
		std::cout << "\t����� ������ �������� " << parameters.city_area << " �����;" << std::endl;
		std::cout << "\t� ������� ��������� " << parameters.wheat_amount << " ������� �������;" << std::endl;
		std::cout << "\t1 ��� ����� ����� ������ " << parameters.cost_of_acre << " ������." << std::endl;
	}
	else
	{
		std::cout << "\t" << parameters.deaths_from_hunger << "������� ������ � ������, � " << parameters.citizens_arrived << " ������� ������� � ��� �����; " << std::endl;
		
		if (parameters.was_plague)
		{
			std::cout << "\t���� ���������� �������� ���������;" << std::endl;
		}
		
		std::cout << "\t��������� ������ ���������� " << parameters.city_population << " �������;" << std::endl;
		std::cout << "\t�� ������� " << parameters.wheat_gathered << " ������� �������, �� " 
			<< parameters.wheat_per_acre << " ������ � ����;" << std::endl;
		std::cout << "\t����� ��������� " << parameters.wheat_eaten_by_rats << " ������� �������, ������� "
			<< parameters.wheat_amount << " ������� � �������;" << std::endl;
		std::cout << "\t����� ������ �������� " << parameters.city_area << " �����;" << std::endl;
		std::cout << "\t1 ��� ����� ����� ������ " << parameters.cost_of_acre << " ������." << std::endl;
	}
}

void GameManager::get_player_input()
{
	parameters.is_input_valid = false;

	while(!parameters.is_input_valid)
	{
		std::cout << "��� ���������, ����������?";
		std::cout << "\n������� ����� ����� ����������� ������?";
		std::cin >> parameters.acres_to_buy;

		if (!(parameters.acres_to_buy > 0))
		{
			std::cout << "\n������� ����� ����� ����������� �������?";
			std::cin >> parameters.acres_to_sell;
		}
		else
		{
			parameters.acres_to_sell = 0;
		}

		std::cout << "\n������� ������� ������� ����������� ������?";
		std::cin >> parameters.wheat_to_eat;
		std::cout << "\n������� ����� ����� ����������� �������?";
		std::cin >> parameters.acres_to_cultivate;
		std::cout << std::endl;

		check_player_input();
	}
	
	int area_delta = parameters.acres_to_buy - parameters.acres_to_sell;
	parameters.city_area += area_delta;
	parameters.wheat_amount -= parameters.wheat_needed;


}

void GameManager::check_player_input()
{
	bool is_input_correct = true;
	parameters.wheat_needed = 0;
	
	if (parameters.acres_to_sell < 0 || parameters.acres_to_buy < 0 ||
		parameters.wheat_to_eat < 0 || parameters.acres_cultivated < 0)
	{
		is_input_correct = false;
	}
	// buying land
	parameters.wheat_needed += parameters.acres_to_buy * parameters.cost_of_acre;
	
	//selling land
	if (parameters.acres_to_sell >= parameters.city_area)
	{
		is_input_correct = false;
	}
	parameters.wheat_needed -= parameters.acres_to_sell * parameters.cost_of_acre;
	
	//food
	parameters.wheat_to_eat = std::min(parameters.wheat_to_eat, parameters.city_population * parameters.wheat_per_citizen);
	parameters.wheat_needed += parameters.wheat_to_eat;
	
	//cultivate

	if (parameters.acres_to_cultivate > (parameters.city_area + parameters.acres_to_buy - parameters.acres_to_sell))
	{
		is_input_correct = false;
	}

	parameters.acres_to_cultivate = std::min(parameters.acres_to_cultivate, parameters.city_population * 10);
	parameters.wheat_needed += (parameters.acres_to_cultivate * parameters.wheat_for_seeds + 0.5);

	if (parameters.wheat_needed > parameters.wheat_amount)
	{
		is_input_correct = false;
	}

	if (!is_input_correct)
	{
		std::cout << "\n�, ����������, ������ ���! � ��� ������ " << parameters.city_population << " �������, "
			<< parameters.wheat_amount << "������� ������� � " << parameters.city_area << " ����� �����!" << std::endl;
	}

	parameters.is_input_valid = is_input_correct;
}

void GameManager::calculate_params()
{
	
	parameters.calc_wheat_gathered();
	parameters.calc_wheat_eaten_by_rats();
	parameters.calc_deaths_from_hunger();
	parameters.calc_citizens_arrived();
	parameters.calc_was_plague();
	parameters.calc_cost_of_acre();

	parameters.add_turn_stats();

}

void GameManager::check_for_end()
{
	if (parameters.city_population <= 0)
	{
		end_game("City is extinct");
	}
	else if (parameters.death_ratio > parameters.death_ratio_max)
	{
		end_game("Bad death ratio");
	}
	else if (current_turn == parameters.number_of_turns)
	{
		parameters.calc_final_stats();
		end_game("Reign end");
	}
}

void GameManager::want_to_save()
{
	char answer;
	bool got_answer = false;

	while (!got_answer)
	{
		std::cout << "��������� � ��������� ����? Y/N" << std::endl;
		std::cin >> answer;

		if (answer == 'Y' || answer == 'y')
		{
			save_to_file();
			got_answer = true;

			exit(EXIT_SUCCESS);
		}
		else if (answer == 'N' || answer == 'n')
		{
			std::cout << "�������, ����������..." << std::endl;
			got_answer = true;
		}
		else
		{
			std::cout << "��������, � �� �������. ����������, ��������� ����." << std::endl;
		}
	}
}

bool GameManager::check_for_save()
{
	bool save_exist = false;
	std::ifstream fin;
	fin.open(save_file_path);

	if (fin.is_open())
	{
		string val_name;
		fin >> val_name >> save_exist;

		if (val_name != "save_exist")
		{
			save_exist = false;
		}
		
	}
	else
	{
		save_exist = false;
	}
	
	fin.close();

	return save_exist;
}

void GameManager::save_to_file()
{
	std::ofstream fout;
	fout.open(save_file_path, std::ios_base::trunc);
	if (!fout.is_open())
	{
		std::cout << "������ ��� �������� �����!" << std::endl;
	}
	else
	{
		fout << "save_exist" << ' ' << 1 << std::endl;
		fout << current_turn << std::endl;
		fout << parameters.city_population << std::endl;
		fout << parameters.wheat_amount << std::endl;
		fout << parameters.city_area << std::endl;
		fout << parameters.cost_of_acre << std::endl;
		fout << parameters.wheat_per_acre << std::endl;

		fout << parameters.deaths_from_hunger << std::endl;
		fout << parameters.citizens_arrived << std::endl;
		fout << parameters.wheat_gathered << std::endl;
		fout << parameters.wheat_eaten_by_rats << std::endl;

		fout << parameters.was_plague << std::endl;

		fout << parameters.deaths_from_hunger_stat << std::endl;
		fout << parameters.acres_per_citizen_stat << std::endl;

		
		fout.close();
	}
}

void GameManager::load_from_file()
{
	std::ifstream fin;
	fin.open(save_file_path);
	string to_skip;
	fin >> to_skip;
	fin >> to_skip;

	fin >> current_turn;
	fin >> parameters.city_population;
	fin >> parameters.wheat_amount;
	fin >> parameters.city_area;
	fin >> parameters.cost_of_acre;
	fin >> parameters.wheat_per_acre;

	fin >> parameters.deaths_from_hunger;
	fin >> parameters.citizens_arrived;
	fin >> parameters.wheat_gathered;
	fin >> parameters.wheat_eaten_by_rats;

	fin >> parameters.was_plague;

	fin >> parameters.deaths_from_hunger_stat;
	fin >> parameters.acres_per_citizen_stat;

	fin.close();
}

void GameManager::delete_save()
{
	std::ofstream fout;
	fout.open(save_file_path, std::ios_base::trunc);
	if (!fout.is_open())
	{
		std::cout << "������ ��� �������� �����!" << std::endl;
	}
	else
	{
		fout << "save_exist" << ' ' << 0;
		fout.close();
	}
}
