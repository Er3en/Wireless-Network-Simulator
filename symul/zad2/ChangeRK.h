#ifndef CHANGE_RK_H_
#define CHANGE_RK_H_
#include "Event.h"
#include  "Network.h"
#include "Generator.h"
#include <functional>

class ChangeRK :
	public Event
{
public:
	ChangeRK(size_t time_, Network* network_, EventList* event_list_, UniformGenerator* generator_t_, UniformGenerator* generator_tau_);
	void Execute() override;

private:
	EventList* event_list_ = nullptr;
	UniformGenerator* generator_tau_ = nullptr;;
	UniformGenerator* generator_t_ = nullptr;;
};
#endif