#ifndef USER
#define USER
#include <vector>
#include"Generator.h"
class User
{
public:
	User(size_t id, UniformGenerator* generator_d_, UniformGenerator* generator_r_k_, UniformGenerator* generator_epsilon_,int Arr_Time);
	~User();
	size_t Get_User_Id() const { return id; }
	int Get_Ammount_Of_Data_To_Download()  { return d_; }
	int Get_Bitrate_From_User_Vector(int x);
	void Generate_Bitrate_Vector(UniformGenerator* x);
	void Generate_Epsilon_Vector();
	void Actualize_Data_To_Download(int x);
	int Show_Ammount_Of_Data_To_Download();
	int  Return_V_E(int x);
	UniformGenerator* Get_Generator_RK() { return Generator_RK_User; }
	void ChangeExitTime(int x) { exit_time = x; }
	int Return_Downloaded(){ return downloaded_data; }
	int Return_D_Info() { return d_info; }
	int Return_ArrivalTime() { return arrival_time; }
	int Return_ExitTime() { return exit_time; }


private:
	const size_t id = 0;
	int d_; // zmienna losowa d o rozkładzie jednostajnym w przedziale {1,2…10} x 250 bitów 
	int d_info;	
	int arrival_time;
	int exit_time = 0;
	std::vector<int> r_v;//wektor zmiennych losowych r_k o rozkładzie jednostajnym w przedziale <20, 800> 
	std::vector<int> e_v; // wektor ε  zmiennych losowych o rozkładzie zero - jedynkowym z prawdopodobieństwem błędu transmisji równym 0.
	int downloaded_data;
	UniformGenerator* Generator_RK_User;
	UniformGenerator* Generator_D_User;
	UniformGenerator* Generator_Epsilon_User;
	
};

#endif 