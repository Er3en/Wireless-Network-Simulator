#include "Network.h"
#include "BaseStation.h"
#include  "User.h"
#include "Generator.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <fstream>






Network::Network()
{
     base_station_pointer = new BaseStation();
	 x = base_station_pointer->Pointer_to_head_of_list();
}

void Network::Init()
{
    while (!buffer.empty())
    {
        buffer.pop_front();
    }
	while (!all_stats_users.empty())
	{
		all_stats_users.pop_front();
	}
	while (!users_ended_before_phase_time.empty())
	{
		users_ended_before_phase_time.pop_front();
	}


}

void Network::GenerateUser(UniformGenerator* generator_d_, UniformGenerator* generator_r_k_, UniformGenerator* generator_epsilon_,int Arr_Time)
{
	static size_t id = 0;
	++id;
	auto user = new User(id, generator_d_, generator_r_k_, generator_epsilon_, Arr_Time);
	buffer.push_back(user);
	if (flag > 1)
	{
		spdlog::info("Generated User id: {},	Data to download: {} [b], [vector_id]:[bitrate]:[epsilon]\n", user->Get_User_Id(), user->Get_Ammount_Of_Data_To_Download());
		spdlog::info("[{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t", 0, user->Get_Bitrate_From_User_Vector(0), user->Return_V_E(0), 5, user->Get_Bitrate_From_User_Vector(5), user->Return_V_E(5), 10, user->Get_Bitrate_From_User_Vector(10), user->Return_V_E(10), 15, user->Get_Bitrate_From_User_Vector(15), user->Return_V_E(15), 20, user->Get_Bitrate_From_User_Vector(20), user->Return_V_E(20));
		spdlog::info("[{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t", 1, user->Get_Bitrate_From_User_Vector(1), user->Return_V_E(1), 6, user->Get_Bitrate_From_User_Vector(6), user->Return_V_E(6), 11, user->Get_Bitrate_From_User_Vector(11), user->Return_V_E(11), 16, user->Get_Bitrate_From_User_Vector(16), user->Return_V_E(16), 21, user->Get_Bitrate_From_User_Vector(21), user->Return_V_E(21));
		spdlog::info("[{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t", 2, user->Get_Bitrate_From_User_Vector(2), user->Return_V_E(2), 7, user->Get_Bitrate_From_User_Vector(7), user->Return_V_E(7), 12, user->Get_Bitrate_From_User_Vector(12), user->Return_V_E(12), 17, user->Get_Bitrate_From_User_Vector(17), user->Return_V_E(17), 22, user->Get_Bitrate_From_User_Vector(22), user->Return_V_E(22));
		spdlog::info("[{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t", 3, user->Get_Bitrate_From_User_Vector(3), user->Return_V_E(3), 8, user->Get_Bitrate_From_User_Vector(8), user->Return_V_E(8), 13, user->Get_Bitrate_From_User_Vector(13), user->Return_V_E(13), 18, user->Get_Bitrate_From_User_Vector(18), user->Return_V_E(18), 23, user->Get_Bitrate_From_User_Vector(23), user->Return_V_E(23));
		spdlog::info("[{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t \n", 4, user->Get_Bitrate_From_User_Vector(4), user->Return_V_E(4), 9, user->Get_Bitrate_From_User_Vector(9), user->Return_V_E(9), 14, user->Get_Bitrate_From_User_Vector(14), user->Return_V_E(14), 19, user->Get_Bitrate_From_User_Vector(19), user->Return_V_E(19), 24, user->Get_Bitrate_From_User_Vector(24), user->Return_V_E(24));
	}
}


void Network::Actualize_Blocks() // aktualizuje ilosc danych 
{
	if (real_time > start_stats_time)
	{
		system_average += Average_System_Bitrate();

		system_average_stats += Average_System_Bitrate();
		average_sys_bitrate_S.push_back(system_average_stats / (real_time));
	}
		if (Is_Resources_List_Empty() == false) // jesli ktos jest na blokach
		{
			User* d = nullptr;
			auto iterator_front = buffer.begin();
			for (int j = 0; j < buffer.size(); j++)
			{
				d = *iterator_front;
				x = base_station_pointer->Pointer_to_head_of_list();
				for (int i = 0; i < 25;i++) //aktualizuj
				{
					x = base_station_pointer->Iteration_Pointer(i);
					if (d->Get_User_Id() == x->get_resource_block_using_user_id())
					{
						d->Actualize_Data_To_Download(i);
					}
				}
				iterator_front++;
			}
		}
}
void Network::EndTranssmision() // sprawdza czy uzytkownik w kolejce odebral wszystkie dane
{
	if (Is_Resources_List_Empty() == false) // jesli ktos jest na blokach
	{
		User* d = nullptr;
		auto iterator_front = buffer.begin();
		while (iterator_front != buffer.end())
		{
			d = *iterator_front;
			if (d->Show_Ammount_Of_Data_To_Download() <= 0)
			{
				if (real_time >= start_stats_time) // dodawanie u¿ytkowników którzy nie odebrali wszystich swoich danych przed koñcem fazy pocz.
				{
					number_of_users++;
					all_stats_users.push_back(d); //dodanie do listy uzytkownikow ktorzy maja zostac zliczani do statystyki
				}
				else
					users_ended_before_phase_time.push_back(d); // uzytkownicy ktorzy w czasie fazy pocz. odebrali wszystkie dane
				if (flag > 1)
				{
					spdlog::info("Ended transmission of user: {}\n", d->Get_User_Id());
				}
				x = base_station_pointer->Pointer_to_head_of_list();
				for (int i = 0; i < 25;i++)
				{
					x = base_station_pointer->Iteration_Pointer(i);
					if (d->Get_User_Id() == x->get_resource_block_using_user_id())
					{
						x->Change_Block_State(false);
						x->Change_Block_Bit_Rate(-1);
						x->Change_Block_User_Id(-1);
					}
				}
				iterator_front = buffer.erase(iterator_front);
			}
			else
			{
				iterator_front++;
			}
		}
	}
}
void Network::AllocateUsers() // przydziel bloki uzytkownikom w kolejce wedlug A1b
{
	//Show_Buffer();
	Clear_Resources_List();
	exit_time +=5;
	Buffer_User_Exit_Time_Change(exit_time);

	User* d = nullptr;
	x = base_station_pointer->Pointer_to_head_of_list();
		for (int j = 0;j < base_station_pointer->Return_l();j++) // po wszystkich blokach
		{
			auto iterator_front = buffer.begin();
			for (int i = 0; i < buffer.size(); i++) // po kolejce
			{
				iterator_front = buffer.begin();
				d = *iterator_front;
				int user_id = d->Get_User_Id();

				if (Is_Resources_List_Full() == false)
				{
					x = First_Free_Block(); // znajduje pierwszy wolny blok
					int block_id = x->get_resource_block_id(); 
					int bit_rate = d->Get_Bitrate_From_User_Vector(block_id - 1);
					x->Change_Block_Bit_Rate(bit_rate);
					x->Change_Block_User_Id(user_id);
					x->Change_Block_State(true);
					buffer.pop_front();
					buffer.push_back(d);
				}
			}
		}
	
	Block_Info();
}



void Network::Clear_Resources_List() // czysci listê bloków zmienia stan na wolny 
{
	x = base_station_pointer->Pointer_to_head_of_list();
	for (int i = 0; i < 25;i++)
	{
		x = base_station_pointer->Iteration_Pointer(i);
		x->Change_Block_State(false);
		x->Change_Block_User_Id(-1);
	}
}



bool Network::Is_Resources_List_Full()
{
	bool isFull = true;
	x = base_station_pointer->Pointer_to_head_of_list();
	for (int i = 0; i < 25;i++)
	{
		x = base_station_pointer->Iteration_Pointer(i);
		if (x->get_resource_block_state() == false)
		{
			isFull = false;
		}
		
	}
	return isFull;
}

bool Network::Is_Resources_List_Empty() // jesli lista jest pusta zwroc true
{
	bool isEmpty = true;
	x = base_station_pointer->Pointer_to_head_of_list();
	for (int i = 0; i < 25;i++)
	{
		x = base_station_pointer->Iteration_Pointer(i);
		if (x->get_resource_block_state() == true)
		{
			isEmpty = false;
		}
	}
	return isEmpty;
}

ResourceBlock* Network::First_Free_Block() // wyszukanie pierwszego wolnegso bloku na liscie 
{
	x = base_station_pointer->Pointer_to_head_of_list();
	for (int i = 0;i < 25;i++)
	{
		x = base_station_pointer->Iteration_Pointer(i);
		if(x->get_resource_block_state() == false)
		{	
			return x;
		}
	}
}
		
void Network::Update_Bitrate() //updatowanie wektora przeplywnosci oraz generowanie wektora epsilon
{
	User* d = nullptr;
	auto iterator_front = buffer.begin();
	for (int j = 0; j < buffer.size(); j++)
	{
		d = *iterator_front;
		d->Generate_Epsilon_Vector();
		UniformGenerator* z = d->Get_Generator_RK();
		d->Generate_Bitrate_Vector(z);
		iterator_front++;
	}

}


void Network::Block_Info() // pokazuje stan blokow
{
	x = base_station_pointer->Pointer_to_head_of_list();
	if (flag > 1)
	spdlog::info("Status of blocks: [id bloku] : [id usera] : [rk]");

	for (int i = 0; i < base_station_pointer->Return_k(); ++i)
	{
		x = base_station_pointer->Iteration_Pointer(i);
		if (x->get_resource_block_state() == false)
		{
			if (flag > 1)
			{
				spdlog::info("Block [{}]:[-1]:[-1] [kb/s] \t", (i));
			}
		}
		else
		{
			if (flag > 1)
			{
				spdlog::info("Block [{}]:[{}]:[{}] [kb/s]", (i), x->get_resource_block_using_user_id(), x->get_resource_block_bitrate());
			}
		}
		if (flag > 1)
		{
			if ((i + 1) % 5 == 0) spdlog::info("--------------------------- \n");
		}
	}
}

void Network::Show_RK_After_Update() // pokazuje R_K po zmianie usera
{
	if (flag > 2)
	{
		User* user = nullptr;
		auto iterator_front = buffer.begin();
		for (int j = 0; j < buffer.size(); j++)
		{
			user = *iterator_front;
			spdlog::debug("RK after update!  User id: {},	DATA TO DOWNLOAD: {} [b],	, [vector_id]:[bitrate]:[epsilon]", user->Get_User_Id(), user->Get_Ammount_Of_Data_To_Download());
			spdlog::debug("[{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t", 0, user->Get_Bitrate_From_User_Vector(0), user->Return_V_E(0), 5, user->Get_Bitrate_From_User_Vector(5), user->Return_V_E(5), 10, user->Get_Bitrate_From_User_Vector(10), user->Return_V_E(10), 15, user->Get_Bitrate_From_User_Vector(15), user->Return_V_E(15), 20, user->Get_Bitrate_From_User_Vector(20), user->Return_V_E(20));
			spdlog::debug("[{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t", 1, user->Get_Bitrate_From_User_Vector(1), user->Return_V_E(1), 6, user->Get_Bitrate_From_User_Vector(6), user->Return_V_E(6), 11, user->Get_Bitrate_From_User_Vector(11), user->Return_V_E(11), 16, user->Get_Bitrate_From_User_Vector(16), user->Return_V_E(16), 21, user->Get_Bitrate_From_User_Vector(21), user->Return_V_E(21));
			spdlog::debug("[{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t", 2, user->Get_Bitrate_From_User_Vector(2), user->Return_V_E(2), 7, user->Get_Bitrate_From_User_Vector(7), user->Return_V_E(7), 12, user->Get_Bitrate_From_User_Vector(12), user->Return_V_E(12), 17, user->Get_Bitrate_From_User_Vector(17), user->Return_V_E(17), 22, user->Get_Bitrate_From_User_Vector(22), user->Return_V_E(22));
			spdlog::debug("[{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t", 3, user->Get_Bitrate_From_User_Vector(3), user->Return_V_E(3), 8, user->Get_Bitrate_From_User_Vector(8), user->Return_V_E(8), 13, user->Get_Bitrate_From_User_Vector(13), user->Return_V_E(13), 18, user->Get_Bitrate_From_User_Vector(18), user->Return_V_E(18), 23, user->Get_Bitrate_From_User_Vector(23), user->Return_V_E(23));
			spdlog::debug("[{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t [{}]:[{}]:[{}]\t ", 4, user->Get_Bitrate_From_User_Vector(4), user->Return_V_E(4), 9, user->Get_Bitrate_From_User_Vector(9), user->Return_V_E(9), 14, user->Get_Bitrate_From_User_Vector(14), user->Return_V_E(14), 19, user->Get_Bitrate_From_User_Vector(19), user->Return_V_E(19), 24, user->Get_Bitrate_From_User_Vector(24), user->Return_V_E(24));
			spdlog::debug(" --------------------------------------------------------------------------------------\n\n");
			iterator_front++;
		}
	}
}


void Network::Show_Buffer()// funkcja debugujaca
{
	if (flag > 2)
	{
		User* user = nullptr;
		auto iterator_front = buffer.begin();
		for (int j = 0; j < buffer.size(); j++)
		{
			user = *iterator_front;
			spdlog::warn("BUFFER USER ID {}, DATA TO DOWNLOAD {}", user->Get_User_Id(), user->Get_Ammount_Of_Data_To_Download());
			iterator_front++;
		}
		spdlog::info(" --------------------------------------------------------------------------------------\n\n");
	}
}

void Network::Show_ALL_USERS()// funkcja debugujaca
{
	if (flag > 2)
	{
		User* user = nullptr;
		auto iterator_front = all_stats_users.begin();
		for (int j = 0; j < all_stats_users.size(); j++)
		{
			user = *iterator_front;
			spdlog::warn("BUFFER USER ID {}, DATA TO DOWNLOAD {}", user->Get_User_Id(), user->Get_Ammount_Of_Data_To_Download());
			iterator_front++;
		}
		spdlog::info(" --------------------------------------------------------------------------------------\n\n");
	}
}




void Network::Buffer_User_Exit_Time_Change(int x) //zmiana czasu opuszczenia systemu przez usera
{
	User* user = nullptr;
	auto iterator_front = buffer.begin();
	for (int j = 0; j < buffer.size(); j++)
	{
		user = *iterator_front;
		user->ChangeExitTime(exit_time);
		iterator_front++;
	}
	
}

int Network::Average_System_Bitrate()//srednia przeplywnosc systemu
{
	int avr = 0;
	x = base_station_pointer->Pointer_to_head_of_list();
	for (int i = 0;i < 25;i++)
	{
		x = base_station_pointer->Iteration_Pointer(i);
		if (x->get_resource_block_state() == true)
		{
			avr += (5 * (x->get_resource_block_bitrate()));
		}
	}
	return avr;
}

double Network::Average_Wait_Time()//sredni czas oczekiwania
{
	double avr_time = 0;
	User* x = nullptr;
	int ALL_USERS = all_stats_users.size();
	auto iterator_front = all_stats_users.begin();
	for (int j = 0; j < all_stats_users.size(); j++)
	{
		x = *iterator_front;
		if (x->Return_ExitTime() - x->Return_ArrivalTime()>= 0)	
		avr_time += (x->Return_ExitTime() - x->Return_ArrivalTime());
		iterator_front++;
	}
	if (number_of_users > 0)
	return (avr_time / number_of_users);
	else
	return 0;

}


int Network::Average_User_Bitrate() // srednia przeplywnosc uzytkownika
{
	int user;
	vector<int> hist_avr_usr;
	User* x = nullptr;
	auto iterator_front = all_stats_users.begin();
	for (int j = 0; j < all_stats_users.size(); j++)
	{
		user = 0;
		x = *iterator_front;
		if (x->Get_Ammount_Of_Data_To_Download() <= 0)
		{
			if (x->Return_ExitTime() - x->Return_ArrivalTime() >= 0)
			{	user = (x->Return_D_Info() / (x->Return_ExitTime() - x->Return_ArrivalTime()));
				user_average += user;
			}
		}
		else
		{
			if (x->Return_ExitTime() - x->Return_ArrivalTime() >= 0)
			{
				user = (x->Return_Downloaded()) / (x->Return_ExitTime() - x->Return_ArrivalTime());
				user_average += user;
			}
		}
	
		//hist_avr_usr.push_back(user);
		iterator_front++;
	}

	/*
	string s = "ŒREDNI_HIS_U¯" + to_string(seed_set) + "_.txt";
	std::ofstream output_file(s);
	std::ostream_iterator<double> output_iterator(output_file, "\n");
	std::copy(hist_avr_usr.begin(), hist_avr_usr.end(), output_iterator);
	*/
	
	spdlog::set_level(spdlog::level::info);
	{
		spdlog::info("Number of users {}", number_of_users);
	}
		if (number_of_users > 0)
			return (user_average / number_of_users);
		else
			return 0;
}

void Network::Ending() // pod koniec laduje wszystkich z kolejki do pobierania statystyk 
{
	User* user = nullptr;
	auto iterator_front = buffer.begin();
	for (int j = 0; j < buffer.size(); j++)
	{
		user = *iterator_front;
		all_stats_users.push_back(user);
		number_of_users++;
		iterator_front++;
	}
}

void Network::SeedsFromFile()//wczytuje seedy z pliku
{
	std::ifstream input("./ziarna.txt", std::ios::in);
	std::string line;

	while (!input.eof())
	{
		std::getline(input, line);
		seeds.push_back(atof(line.c_str()));
	}
	input.close();
}



void Network::MakeAverageSysFile()
{
	string s = "AVERAGE_SYSTEM_BITRATE_" + to_string(seed_set)+"_.txt";
	std::ofstream output_file(s);
	std::ostream_iterator<double> output_iterator(output_file, "\n");
	std::copy(average_sys_bitrate_S.begin(), average_sys_bitrate_S.end(), output_iterator);
}

void Network::Delete_All_Users() //usuwa wszystkie wskazniki na userow utworzonych 
{
	
	User* x = nullptr;
	auto iterator_front = users_ended_before_phase_time.begin();
	while (iterator_front != users_ended_before_phase_time.end())
	{
		x = *iterator_front;
		x->~User();
		iterator_front++;
	}

	 x = nullptr;
	  iterator_front = all_stats_users.begin();
		while (iterator_front != all_stats_users.end())
		{ 
		x = *iterator_front;
		
		x->~User();
		iterator_front++;
		}
}