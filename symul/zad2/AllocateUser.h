#ifndef ALLOCATE_USER_H_
#define ALLOCATE_USER_H_
#include "Event.h"
#include  "Network.h"
#include "Generator.h"

#include <functional>


class AllocateUser :
	public Event
{
public:
	AllocateUser(size_t time, Network* network_, EventList* event_list, UniformGenerator*generator_t, UniformGenerator*generator_tau);
	void Execute() override;
	
private:
	EventList* event_list_ = nullptr;
	const size_t S = 5;
	UniformGenerator * generator_t_;
	UniformGenerator* generator_tau_;
};
#endif