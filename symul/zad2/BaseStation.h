#ifndef BASESTATION_H
#define BASESTATION_H

#include "User.h"
#include "ResourceBlock.h"
#include <list>

using namespace std;

class BaseStation
{
	
public:
	BaseStation();
	size_t Return_time_s() { return s; }
	size_t Return_l() { return l; }
	size_t Return_k() { return k; }
	void Change_state_of_resource_block_on_resources_list(bool y);
	void Insert_id_user_using_resources_list(int y);
	bool Return_state_of_resource_block() { return x->Return_Resource_Block_State(); }
	size_t Return_resources_block_id() { return x->get_resource_block_id(); }
	size_t Retrun_resources_using_user_id() { return x->get_resource_block_using_user_id(); }
	ResourceBlock* Pointer_to_head_of_list();
	ResourceBlock* Iteration_Pointer(int position);
	size_t Get_TAU() { return tau; }
	void Change_Tau(double x) { tau = x; }
	
private:
	list <ResourceBlock*> resources_list; // lista blokow zasobow
	ResourceBlock* x = nullptr ;
	ResourceBlock* head = nullptr;
	double tau;//zmienna losowa τ o rozkładzie wykładniczym o intensywności 1 / 10 ms 
	const int s = 5;//zmienna s która reprezentuje stałe odstępy czasu w których stacja bazowa przydziela bloki zasobów 
	const int k = 25;// liczba bloków k zasobów 
	const int l = 3;//zmienna l reprezentująca ilość bloków zasobów które można przydzielić jednemu użytkownikowi	


};

#endif 
