#include "User.h"
#include "Generator.h"
#include <cstdlib>
#include "spdlog/spdlog.h"
User::User(size_t id, UniformGenerator* generator_d_, UniformGenerator* generator_r_k_, UniformGenerator* generator_epsilon_,int Arr_Time) : id(id)
{
	
	Generator_D_User = generator_d_;
	Generator_Epsilon_User = generator_epsilon_;
	Generator_RK_User = generator_r_k_;
	arrival_time = Arr_Time;
	
	downloaded_data = 0;

	d_ = Generator_D_User->MinMax(1, 10) * 250;//generowanie danych uzytkownikowi rozk³adem jednostajnym
	d_info = d_;

	for (int i = 0;i < 25;i++)
	{
		e_v.push_back(Generator_Epsilon_User->RndZeroOne(0.1)); // generowanie wektora epislonow
	}

	for (int i = 0;i < 25;i++)
	{
		int r_k = Generator_RK_User->MinMax(20, 800); //generowanie przeplywnosci
		r_v.push_back(r_k);
	}
	
	for (int i = 0;i < 25;i++) // jesli wystapil blad to wyzeruj przeplywnosc
	{
		if (e_v[i] == 1)
			r_v[i] = 0;
	}

}

User::~User()
{
}

int User::Return_V_E(int x)//zwraca ity eps
{
	return e_v[x];
}
void User::Generate_Epsilon_Vector()
{

	for (int i = 0;i < 25;i++)
	{
		e_v[i] = (Generator_Epsilon_User->RndZeroOne(0.1));
	}
}
void User::Generate_Bitrate_Vector(UniformGenerator* x)
{
	
	for (int i = 0;i < 25;i++)
	{
		if (e_v[i] == 0)
			r_v[i] = (x->MinMax(20, 800));
		else
			r_v[i] = 0;
	}
}

int User::Get_Bitrate_From_User_Vector(int x)
{
	
	return (r_v[x]);
}

void User::Actualize_Data_To_Download(int x)
{	
		d_ = (d_ - (r_v[x] * 5 ));
		downloaded_data = (r_v[x] * 5);
}

int User::Show_Ammount_Of_Data_To_Download()
{
	if (d_ <= 0)
		return 0;
	else
	return d_;
}

