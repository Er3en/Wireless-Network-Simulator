#include "Simulator.h"
#include "Event.h"
#include "GenerateUserEvent.h"
#include "AllocateUser.h"
#include "ChangeRK.h"
#include "spdlog/spdlog.h"
#include "Generator.h"
#include <iostream>
#include <fstream>
#include <iterator>

Simulator::Simulator(Network* network_) : network_(network_)
{
}


void Simulator::M2(int time, int zestaw_,double lambda_,int start_phase_time_) 
{
    zestaw = zestaw_;
    lambda = lambda_;
    start_phase_length = start_phase_time_;
    end_time = time;
    int number_of_rands = 100000;
    int seed = 24;
    auto generator = UniformGenerator(seed);
    std::vector<double> numbers;
    spdlog::info("Started Simulation method M2 A1b: \n\n");
    network_->Get_Lambda(lambda);
    network_->StartStats(start_phase_length);
    network_->Set_Flag_Log(flag);
    network_->SeedsFromFile();
    network_->Get_Seed_Set(zestaw);
    network_->Get_End_Of_Simulation_Time(Return_End_Of_Simulation_Time());

   
    auto generator_t = new UniformGenerator(network_->ReturnFromSeedsVector(zestaw * 5 - 5));
    auto generator_d = new UniformGenerator(network_->ReturnFromSeedsVector(zestaw * 5 - 4));
    auto generator_r_k = new UniformGenerator(network_->ReturnFromSeedsVector(zestaw * 5 - 3));
    auto generator_tau = new UniformGenerator(network_->ReturnFromSeedsVector(zestaw * 5 - 2));
    auto generator_epsilon = new UniformGenerator(network_->ReturnFromSeedsVector(zestaw * 5 - 1));

   

    clock_ = 0;
    network_->Init(); // czysci kolejkê, 
   

    auto cmp = [](Event* left, Event* right) { return left->get_time() > right->get_time(); };
    Event::EventList event_list(cmp); 
       
    int time_of_first_user = generator_t->RandExp(lambda);
    event_list.push(new GenerateUserEvent(/*time_of_first_user*/1, network_, &event_list,  generator_d,  generator_r_k,  generator_epsilon,  generator_t));
    event_list.push(new AllocateUser(/*network_->Get_Time_S()*/5, network_, &event_list,  generator_t,  generator_tau));
    event_list.push(new ChangeRK(5, network_, &event_list, generator_t, generator_tau));
    while (clock_ < static_cast<size_t>(time))
    {
     

        Event* event = event_list.top();
        event_list.pop();
        clock_ = event->get_time();  
           
        if (flag > 1)
        {
            spdlog::info("Simulation Time: {}[ms]", clock_);
        }

        network_->Get_Real_Time(clock_);
            event->Execute();
            if (step_mode == 1)
            {
                system("pause");
            }
    
    }
    network_->Ending();


    spdlog::set_level(spdlog::level::info);
    {
        spdlog::info("Lambda: {} Seeds set:{}", lambda, zestaw);

        sys_avr = (network_->Return_Sys_AVR() / (clock_ - start_phase_length));
        spdlog::info("System Average Bitrate:{} [kb/s]", sys_avr);

        user_avr = network_->Average_User_Bitrate();
        spdlog::info("System User Bitrate:{} [kb/s]", user_avr);

        time_avr = network_->Average_Wait_Time();
        spdlog::info("Average time:{:.2f} [ms]", time_avr);


    }
   // network_->MakeAverageSysFile();
    network_->Delete_All_Users();
  
}



int Simulator::Return_Sys_Avr() // 
{
    
    return sys_avr;
}
int Simulator::Return_User_Avr()
{

    return user_avr;
}
double Simulator::Return_Time_Avr()
{

    return time_avr;
}
void Simulator::Set_Flag_Log(int x)
{
    flag = x;
}
void Simulator::Set_Step_Mode(int x)
{
    step_mode = x;
}
