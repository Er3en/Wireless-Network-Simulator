#include "BaseStation.h"
#include "User.h"
#include "ResourceBlock.h"

BaseStation::BaseStation() 
{
	
	for (int i = 0;i < k;++i)
	{
		ResourceBlock *x = new ResourceBlock();
		x->change_block_id(i);
		resources_list.push_back(x);
	}
	tau = 0;
}

void BaseStation::Change_state_of_resource_block_on_resources_list(bool y)
{ 
	x->Change_Block_State(y);
}

void BaseStation::Insert_id_user_using_resources_list(int y)
{
	x->Change_Block_User_Id(y);
}

ResourceBlock* BaseStation::Pointer_to_head_of_list()//zwraca  wskaznik na poczatek listy 
{
	return resources_list.front();
}

ResourceBlock* BaseStation::Iteration_Pointer(int position) // zwraca ity wskaznik
{
	ResourceBlock* head = nullptr;
	auto iterator_front = resources_list.begin();
	advance(iterator_front, position);
	head = *iterator_front;
	return head;
}
