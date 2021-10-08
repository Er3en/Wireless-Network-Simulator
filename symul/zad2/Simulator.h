#ifndef SIMULATOR_H_
#define SIMULATOR_H
#include "Network.h"

class Simulator
{
public:

	explicit Simulator(Network* network);
	void M2(int time,int zestaw_,double lambda_,int start_phase_time);
	int Return_Sys_Avr();
	int Return_User_Avr();
	double Return_Time_Avr();
	void Set_Flag_Log(int x);
	void Set_Step_Mode(int x);
	int Return_End_Of_Simulation_Time() { return end_time; }
	size_t get_clock_time() { return clock_; }
private:
	size_t clock_ = 0;
	Network* network_ = nullptr;
	double lambda = 1;
	size_t start_phase_length = 0;
	int system_average = 0;
	int zestaw=0;
	int end_time=0;
	int sys_avr = 0;
	int user_avr = 0;
	double time_avr = 0;
	int flag = 0;
	int step_mode = 0;
};

#endif

