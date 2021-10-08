#ifndef NETWORK
#define NETWORK
#include "User.h"
#include "BaseStation.h"
#include "Generator.h"
#include <list>
#include <vector>
class Network
{
public:
	Network();
	void Init();
	void GenerateUser(UniformGenerator* generator_d_, UniformGenerator* generator_r_k_, UniformGenerator* generator_epsilon_,int Arr_Time);
	void Clear_Resources_List();
	void EndTranssmision();
	void AllocateUsers();
	void Block_Info();
	bool IsFree() { return !channel_; }
	bool IsBufferEmpty() { return buffer.empty(); }
	bool Is_Resources_List_Full();
	bool Is_Resources_List_Empty();
	double Get_Lambda() { return lambda; }
	void Get_Real_Time(int x) { real_time = x; }
	void Actualize_Blocks();
	void Get_End_Of_Simulation_Time(int x) { end_of_simulation_time = x; }
	int Return_End_Of_Simulation_Time() { return end_of_simulation_time; }
	size_t Get_Buffer_Size() { return buffer.size(); }
	size_t Get_Time_S() { return base_station_pointer->Return_time_s();}
	size_t Get_Clock_Time() { return Get_Clock_Time(); }
	size_t Get_Tau() { return base_station_pointer->Get_TAU(); }
	ResourceBlock* First_Free_Block();
	void Update_Bitrate();
	double Get_Lambda(double x) { lambda = x; return x; }
	void StartStats(int x) {start_stats_time = x;}
	void Show_RK_After_Update();
	int Average_System_Bitrate();
	int Average_User_Bitrate();
	void Ending();
	void SeedsFromFile();
	void  Show_Buffer();
	void Show_ALL_USERS();
	int Return_Sys_AVR() { return system_average; }
	void Buffer_User_Exit_Time_Change(int x);
	double Average_Wait_Time();
	void Get_Seed_Set(int x) { seed_set = x; }
	int Return_Seed_Set() { return seed_set; }
	int ReturnFromSeedsVector(int x){return seeds[x];}
	void MakeAverageSysFile();
	void Delete_All_Users();
	void Set_Flag_Log(int x){flag = x;}
	int Return_Flag_Log() { return flag; }
	
private:
	BaseStation* base_station_pointer = nullptr;
	ResourceBlock* x = nullptr;
	list<User*> buffer;
	list<User*> all_stats_users;
	list<User*> users_ended_before_phase_time;
	vector<int> seeds;
	vector <int> average_sys_bitrate_S;
	bool channel_ = false; // false -> free true -> busy 
	double lambda =1;
	int system_average = 0;
	int number_of_users = 0;
	int user_average = 0;
	int exit_time = 5;
	int start_stats_time =0;
	int real_time = 0;
	int seed_set = 1;
	int system_average_stats = 0;
	int end_of_simulation_time = 0;
	int flag = 0;
	

};
#endif 

