#include "Generator.h"
#include <cmath>
#include <vector>

UniformGenerator::UniformGenerator(int kernel) : kernel_(kernel)
{
    
}

UniformGenerator::~UniformGenerator()
{

}

double UniformGenerator::Rand()
{
    int h = kernel_ / kQ;
    kernel_ = kA * (kernel_ - kQ * h) - kR * h;
    if (kernel_ < 0)
        kernel_ = kernel_ + static_cast<int>(kM); // generator rozkladu rownomiernego
    return kernel_ / kM;
}

double UniformGenerator::RandExp(double lambda)
{
   
    int h = kernel_ / kQ;
    kernel_ = kA * (kernel_ - kQ * h) - kR * h;
    if (kernel_ < 0)
        kernel_ = kernel_ + static_cast<int>(kM); //generator  rozkladu wykladmiczego
    double k = kernel_ / kM;
    return (-(1.0 / lambda) * log(k));
}

int UniformGenerator::MinMax(double min, double max)
{
    
   return(Rand() * (max - min) + min);  // generator rozkladu jednostajnego
}

int UniformGenerator::RndZeroOne(double p)
{
    double k = Rand();
    if (k < p) return 1; //generator rozkladu zero jedynkowego
    else return 0;
}