#ifndef RANDOM_GENERATOR_H_
#define RANDOM_GENERATOR_H_

#include <string>
#include<vector>

class UniformGenerator
{
public:
    UniformGenerator(int kernel);
    virtual ~UniformGenerator();
    int RndZeroOne(double p);
    double Rand();
    double RandExp(double lambda);
    int MinMax(double min, double max); 
    int get_kernel() { return kernel_; };
    
private:
    int kernel_;
    const double kM = 2147483647.0;
    static const int kA = 16807;
    static const int kQ = 127773;
    static const int kR = 2836;
    
};


#endif  