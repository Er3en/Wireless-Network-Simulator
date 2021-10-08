#include "AllocateUser.h"
#include "spdlog/spdlog.h"
#include <iostream>


AllocateUser::AllocateUser(size_t time, Network* network_, EventList* event_list, UniformGenerator* generator_t, UniformGenerator*generator_tau) : Event(time, network_), event_list_(event_list)
{
	generator_t_ = generator_t;
	generator_tau_ = generator_tau;
	
}


void AllocateUser::Execute()
{
	spdlog::set_level(spdlog::level::debug);
	network_->Show_RK_After_Update();
		network_->Actualize_Blocks();
		network_->EndTranssmision();	
		network_->AllocateUsers();

		if (time_ < network_->Return_End_Of_Simulation_Time())
		{
			event_list_->push(new AllocateUser(time_ + network_->Get_Time_S(), network_, event_list_, generator_t_, generator_tau_));
		}
		
}
