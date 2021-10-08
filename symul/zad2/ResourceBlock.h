#ifndef RESOURCEBLOCK_H
#define RESOURCEBLOCK_H

class ResourceBlock
{
public:
	size_t get_resource_block_id() { return resource_block_id; }
	size_t get_resource_block_state() { return state; }
	size_t get_resource_block_using_user_id() { return using_user_id; }
	size_t get_resource_block_bitrate() { return (block_bit_rate); }
	void change_block_id(int x) { resource_block_id = resource_block_id + x; }
	void Change_Block_User_Id(int x) { using_user_id = x; }
	void Change_Block_State(bool x) {state = x; }
	void Change_Block_Bit_Rate(double x) { block_bit_rate = x; }
	bool Return_Resource_Block_State() { return state; }
private:
	size_t resource_block_id=1;
	bool state = false; // false ->free , true->busy
	size_t using_user_id=-1;
	size_t block_bit_rate= 0;
	size_t error = -1;
};

#endif 