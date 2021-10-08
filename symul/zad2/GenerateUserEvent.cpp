#include "GenerateUserEvent.h"
#include "AllocateUser.h"
#include <iostream>
GenerateUserEvent::GenerateUserEvent(size_t time, Network* network_, EventList* event_list, UniformGenerator* generator_d, UniformGenerator* generator_r_k, UniformGenerator* generator_epsilon, UniformGenerator* generator_t) : Event(time, network_), event_list_(event_list)
{
    generator_d_ = generator_d;
    generator_r_k_ = generator_r_k;
    generator_epsilon_ = generator_epsilon;
    generator_t_ = generator_t;
    time_gen = time;
}

void GenerateUserEvent::Execute()
{
    Get_lambda();
    network_->GenerateUser(generator_d_, generator_r_k_, generator_epsilon_, time_gen);
    event_list_->push(new GenerateUserEvent(time_+ generator_t_->RandExp(lambda), network_, event_list_,generator_d_,generator_r_k_,generator_epsilon_, generator_t_));
}
double GenerateUserEvent::Get_lambda() 
{
    lambda = network_->Get_Lambda();
    return lambda;
}
