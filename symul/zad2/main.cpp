#include <iostream>
#include "Simulator.h"
#include  "Network.h"
#include "BaseStation.h"
#include <ctime>
#include <memory>
#include "spdlog/spdlog.h"
#include <fstream>


using namespace std;



int main(int argc, char* argv[])
{
	int ammout_of_simulations=10;
	int simulation_time = 1000;
	double lambda = 1;

	vector<double> lambda_vector;
	vector<double> average_delay_vector;
	vector<int> average_system_vector;
	vector<int> average_user_vector;
	int Average_System_Bitrate = 0;
	int Average_User_Bitrate = 0;
	double Average_Delay = 0;
	int System_Bitrate = 0;
	int User_Bitrate = 0;
	double 	Delay = 0;
	int start_phase_time=0;
	int logs = 1;
	int step_m = 0;
	char mode = 'f';
	
	spdlog::info("Ammount of simulations [1-10]: ");
	cin >> ammout_of_simulations;
	if ( ammout_of_simulations<1 || ammout_of_simulations>10)
	{
		spdlog::error("Bad value! deafault ammount of simulation 1 \n ");
		ammout_of_simulations = 1;
	}
	
	spdlog::info("Set time of simulation: ");
	cin >> simulation_time;
	if (simulation_time <= 0 )
	{
		spdlog::error("Bad value! deafault time of simulation 1000 \n ");
		simulation_time = 1000;
	}


	spdlog::info("Length of start faze:");
	while (1)
	{
		cin >> start_phase_time;
		if (start_phase_time < simulation_time)
			break;
		else
			spdlog::error("Start phase can't be greater or equal simulation time, try again: ");
	}

	spdlog::info("Please give the lambda value: ");
		cin >> lambda;
		if(lambda<0)
		spdlog::error("Bad value! now, lambda = 1 \n ");

	spdlog::info("Advanced logs press 1 ->[off] || 2 ->[info] || 3->[debug] ");
	while (1)
	{
		cin >> logs;
		if (logs == 1)
			break;
		else if (logs == 2)
			break;
		else if (logs == 3)
			break;
		else
		{
			spdlog::error("You didnt set correct logs state, logs are default [info]: ");
			logs = 2;
			break;
		}
	}


	if (logs == 1)
	{
		spdlog::info("You set logs state: [off] \n");
		spdlog::set_level(spdlog::level::off);
		
	}
	else if (logs == 2)
	{
		spdlog::info("You set logs state: [info]\n ");
		spdlog::set_level(spdlog::level::info);
		
	}
	else if (logs == 3)
	{
		spdlog::info("You set logs state: [debug] \n");
		spdlog::set_level(spdlog::level::debug);
		
	}

	if (logs > 1)
	{
		spdlog::info("Simulation in step mode y/n \n ");

		while (mode != 'y' && mode != 'n')
		{
			mode = cin.get();
		}
		if (mode == 'y')
			step_m = 1;
	}

	

 
	
	for (int seed_set = 1; seed_set <= ammout_of_simulations; seed_set++)
	{
		spdlog::set_level(spdlog::level::info);
		{
			spdlog::info("Starting {} simulation", seed_set);
		}
		Network* network_ = new Network();
		Simulator simulator = Simulator(network_);
		Simulator* g = &simulator;
			g->Set_Flag_Log(logs);
			g->Set_Step_Mode(step_m);
		simulator.M2(simulation_time, seed_set, lambda,start_phase_time);
		System_Bitrate += g->Return_Sys_Avr();
		User_Bitrate += g->Return_User_Avr();
		Delay += g->Return_Time_Avr();
		spdlog::info(" \n\n");
	}
	
	//average_delay_vector.push_back(Delay);
	//average_system_vector.push_back(System_Bitrate);
	//average_user_vector.push_back(User_Bitrate);
			
		


	/*
	string s = "AVERAGE_USER_BTRATE_" + to_string( 1) + "_.txt";
	std::ofstream output_file(s);
	std::ostream_iterator<double> output_iterator(output_file, "\n");
	std::copy(average_user_vector.begin(), average_user_vector.end(), output_iterator);

	string s1 = "AVERAGE_System_BTRATE_" + to_string(1) + "_.txt";
	std::ofstream output_file1(s1);
	std::ostream_iterator<double> output_iterator1(output_file1, "\n");
	std::copy(average_system_vector.begin(), average_system_vector.end(), output_iterator1);

	string s2 = "POPRAWA_WYZ_LAMB_" + to_string( 1) + "_.txt";
	std::ofstream output_file2(s2);
	std::ostream_iterator<double> output_iterator2(output_file2, "\n");
	std::copy(average_delay_vector.begin(), average_delay_vector.end(), output_iterator2);
	*/
	
	spdlog::set_level(spdlog::level::info);
	{
		spdlog::info(" Average System Bitrate in  simulations: {} [kb/s]", System_Bitrate / ammout_of_simulations);
		spdlog::info(" Average User Bitrate in  simulations: {} [kb/s]", User_Bitrate / ammout_of_simulations);
		spdlog::info(" Average User Delay:{}  [ms]", Delay / ammout_of_simulations);
	}
}

