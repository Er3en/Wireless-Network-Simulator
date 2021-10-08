#ifndef GENERATE_USER_EVENT_H_
#define GENERATE_USER_EVENT_H_
#include "Event.h"
#include "Network.h"
#include <functional>

class GenerateUserEvent :
	public Event
{
public:
	GenerateUserEvent(size_t time, Network* network_, EventList* event_list, UniformGenerator* generator_d, UniformGenerator* generator_r_k, UniformGenerator*generator_epsilon,  UniformGenerator* generator_t);
	void Execute() override;
	UniformGenerator* ReturnGenerator_d(){ return generator_d_; }
	UniformGenerator* ReturnGenerator_r_k() { return generator_r_k_; }
	UniformGenerator* ReturnGenerator_epsilon() { return generator_epsilon_; }
	UniformGenerator* ReturnGenerator_t() { return generator_t_; }
	double Get_lambda(); 
	//int Return_Time_From_Allocate_User() { return time_gen; }

private:
	EventList* event_list_ = nullptr;
	UniformGenerator* generator_d_= nullptr;
	UniformGenerator* generator_r_k_= nullptr;
	UniformGenerator* generator_epsilon_= nullptr;
	UniformGenerator* generator_t_= nullptr;
	double lambda = NULL;;
	int time_gen;
};

#endif

