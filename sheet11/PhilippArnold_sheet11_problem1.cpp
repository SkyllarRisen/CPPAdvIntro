#include <iostream>
#include <random>
#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include <math.h>
#include <fstream>








int main()
{
    int seed = std::chrono::system_clock::now().time_since_epoch().count();

    //normal distribution, every number represents a 2% probability
    double normDistZ[49] { -2.053749, -1.750686, -1.554773, -1.405071, -1.281551, -1.174987, -1.080319, -0.994458, -0.915365, -0.841621, -0.772193, -0.706303, -0.643346, -0.582842, -0.524401, -0.467699, -0.412463, -0.358458, -0.305481, -0.253347, -0.201893, -0.150969, -0.100434, -0.050153, 
                           0, 0.050153, 0.100434, 0.150969, 0.201893, 0.253347, 0.305481, 0.358458, 0.412463, 0.467699, 0.524401, 0.582842, 0.643346, 0.706303, 0.772193, 0.841621, 0.915365, 0.994458, 1.080319, 1.174987, 1.281551, 1.405071, 1.554773, 1.750686, 2.053749};
    std::default_random_engine generator(seed);                                                 //setup for rng 
    std::exponential_distribution<double> expDistribution(1.5);                                 //
    std::normal_distribution<double> normDistribution(6.0, 0.5);                                //
    std::vector< std::vector<double> > binContainerExp(50, std::vector<double>(0));             //bin container for rng values
    std::vector< std::vector<double> > binContainerNorm(50, std::vector<double>(0));            //
    std::map<int, int> binRefExp;                                                               //maps index to number of counts
    std::map<int, int> binRefNorm;                                                              //
    for (int N = 0; N < 10000;)
    {
        double number = expDistribution(generator);                                             //generates number
        if (number < 0.0 || number >= 10.0)                                                     //range checking
        {
            continue;
        }

        else
        {
            for (int i = 1; i < 50; ++i)                                                        //loops over 2% steps and stores values
            {
                if (number <= -log(1 - 0.02*i) / 1.5)
                {
                    binContainerExp.at(i - 1).push_back(number);
                    binRefExp.emplace(i - 1, 1);
                    binRefExp.at(i - 1)++;
                    break;
                }
            }
            if (number > -log(0.02) / 1.5)
            {
                binContainerExp.at(49).push_back(number);
                binRefExp.emplace(49, 1);
                binRefExp.at(49)++;
            }
            ++N;
        }
    }
    for (int N = 0; N < 10000;)                                                                 //see above           
    {
        double number = normDistribution(generator);
        if (number < 0.0 || number >= 10.0)
            continue;
        else
        {
            for (int i = 0; i < 49; ++i)
            {
                if (number <= normDistZ[i]*0.5+6)
                {
                    binContainerNorm.at(i).push_back(number);
                    binRefNorm.emplace(i, 1);
                    binRefNorm.at(i)++;
                    break;
                }
            }
            if (number > normDistZ[48] * 0.5 + 6)
            {
                binContainerNorm.at(49).push_back(number);
                binRefNorm.emplace(49, 1);
                binRefNorm.at(49)++;
            }
            ++N;
        }
    }
    
    std::ofstream outf;                                                                         //calculates mean and prints to file
    std::ofstream outf2;
    outf.open("ExpDist.dat");
    outf2.open("NormDist.dat");
    for (int i = 0; i < 50; ++i)
    {
        double meanExp=0, meanNorm=0;
        for (int j = 0; j < binContainerExp.at(i).size(); ++j)
        {
            meanExp += binContainerExp.at(i).at(j);
        }
        for (int j = 0; j < binContainerNorm.at(i).size(); ++j)
        {
            meanNorm += binContainerNorm.at(i).at(j);
        }
        meanExp /= binRefExp.at(i);
        meanNorm /= binRefNorm.at(i);
        outf << meanExp << " " << binRefExp.at(i) << std::endl;
        outf2 << meanNorm << " " << binRefNorm.at(i) << std::endl;
    }
}