#include "ChangeRK.h"
#include "spdlog/spdlog.h"

ChangeRK::ChangeRK(size_t time, Network* network_, EventList* event_list, UniformGenerator* generator_t, UniformGenerator* generator_tau) : Event(time, network_), event_list_(event_list)
{
	generator_tau_ = generator_tau;
	generator_t_ = generator_t;
}
void ChangeRK::Execute()
{
	
	if (network_->Return_Flag_Log() > 2)
	{
		network_->Show_RK_After_Update();
	}
	network_->Update_Bitrate();

	int time_for_event_rk_change = (time_ + generator_tau_->RandExp(0.1));

	while (time_for_event_rk_change % 5 != 0)
		time_for_event_rk_change += 1;
	
	event_list_->push(new ChangeRK(time_for_event_rk_change , network_, event_list_, generator_t_, generator_tau_));
}