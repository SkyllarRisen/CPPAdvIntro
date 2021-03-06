#include <iostream>
#include <limits>
#include "CelestialBodies.h"
#include <fstream>





void makeFiles()
{
    std::ofstream myfile;
    for (int i = 0; i < CelestialBody::celBodyList.size(); ++i)
    {
        myfile.open(CelestialBody::celBodyList.at(i)->getName() + ".dat");
        myfile << "X Y Z" << std::endl;
        myfile.close();
    }
    myfile.open("Energy.dat");
    myfile << "Energy" << std::endl;
    myfile.close();
}

bool timeStep()
{
    static int steps = 0;
    double potEnergy = 0;
    std::ofstream selFile;
    for (int i = 0; i < CelestialBody::celBodyList.size(); ++i)
    {
        CelestialBody::celBodyList.at(i)->updatePosition();
        for (int j = i + 1; j < CelestialBody::celBodyList.size(); ++j)
        {
            std::array<double, 3> temp;
            temp.at(0) = CelestialBody::celBodyList.at(i)->getCoordinates().at(0) - CelestialBody::celBodyList.at(j)->getCoordinates().at(0);
            temp.at(1) = CelestialBody::celBodyList.at(i)->getCoordinates().at(1) - CelestialBody::celBodyList.at(j)->getCoordinates().at(1);
            temp.at(2) = CelestialBody::celBodyList.at(i)->getCoordinates().at(2) - CelestialBody::celBodyList.at(j)->getCoordinates().at(2);
            potEnergy += (CelestialBody::newtonG*CelestialBody::celBodyList.at(i)->getMass()*CelestialBody::celBodyList.at(j)->getMass()) / (temp.at(0)*temp.at(0) + temp.at(1)*temp.at(1) + temp.at(2)*temp.at(2));
        }
        CelestialBody::m_energy += CelestialBody::celBodyList.at(i)->getKinEnergy();
        selFile.open(CelestialBody::celBodyList.at(i)->getName() +".dat" , std::ios::app);
        selFile << CelestialBody::celBodyList.at(i)->getCoordinates().at(0) << " " << CelestialBody::celBodyList.at(i)->getCoordinates().at(1)  << " " << CelestialBody::celBodyList.at(i)->getCoordinates().at(2)  << std::endl;
        selFile.close();
    }
//    CelestialBody::m_energy /= 1e6;
    CelestialBody::copyTemp();
    CelestialBody::m_energy += (potEnergy/1000);
    selFile.open("Energy.dat", std::ios::app);
    selFile << CelestialBody::m_energy << std::endl;
    selFile.close();
    if (steps > 1e5)
        return false;
    std::cout << (steps/1e5)*100 << std::endl;
    ++steps;
    CelestialBody::m_energy = 0;
    return true;
}

void sun()
{
    std::array<double, 3> coordinates{0,0,0 };
    std::array<double, 3> velocity{ 0,0,0 };
    std::string name{ "Sun1" };
    double mass{ 2e30 };
    new CelestialBody(coordinates, velocity, mass, name);    
}

void sun2()
{
    std::array<double, 3> coordinates{ 150e9,0,0 };
    std::array<double, 3> velocity{ 0,3e4,0 };
    std::string name{ "Sun2" };
    double mass{ 1e30 };
    new CelestialBody(coordinates, velocity, mass, name);
}

void probe1()
{
    std::array<double, 3> coordinates{ 0,-200000000000,0 };
    std::array<double, 3> velocity{ 0.5e4,0.5e4,0 };
    std::string name{ "probe1" };
    double mass{ 1 };
    new CelestialBody(coordinates, velocity, mass, name);
}

void probe2()
{
    std::array<double, 3> coordinates{ 0,-200000000001,0 };
    std::array<double, 3> velocity{ 1e4,1e4,0 };
    std::string name{ "probe2" };
    double mass{ 1 };
    new CelestialBody(coordinates, velocity, mass, name);
}

void probe3()
{
    std::array<double, 3> coordinates{ 0,-200000000002,0 };
    std::array<double, 3> velocity{ 2e4,2e4,0 };
    std::string name{ "probe3" };
    double mass{ 1 };
    new CelestialBody(coordinates, velocity, mass, name);
}

void probe4()
{
    std::array<double, 3> coordinates{ 0,-200000000003,0 };
    std::array<double, 3> velocity{ 3e4,3e4,0 };
    std::string name{ "probe4" };
    double mass{ 1 };
    new CelestialBody(coordinates, velocity, mass, name);
}

void probe5()
{
    std::array<double, 3> coordinates{ 0,150000000000,0 };
    std::array<double, 3> velocity{ -0.5e4,-0.5e4,0 };
    std::string name{ "probe5" };
    double mass{ 1 };
    new CelestialBody(coordinates, velocity, mass, name);
}

void probe6()
{
    std::array<double, 3> coordinates{ 0,150000000001,0 };
    std::array<double, 3> velocity{ -1e4,-1e4,0 };
    std::string name{ "probe6" };
    double mass{ 1 };
    new CelestialBody(coordinates, velocity, mass, name);
}

void probe7()
{
    std::array<double, 3> coordinates{ 0,150000000002,0 };
    std::array<double, 3> velocity{ -2e4,-2e4,0 };
    std::string name{ "probe7" };
    double mass{ 1 };
    new CelestialBody(coordinates, velocity, mass, name);
}

void probe8()
{
    std::array<double, 3> coordinates{ 0,150000000003,0 };
    std::array<double, 3> velocity{ -3e4,-3e4,0 };
    std::string name{ "probe8" };
    double mass{ 1 };
    new CelestialBody(coordinates, velocity, mass, name);
}

void planet()
{
    std::array<double, 3> coordinates{ -150e9,0,0 };
    std::array<double, 3> velocity{ 0, -3e4,0 };
    std::string name{ "planet1" };
    double mass{ 6e24 };
    new CelestialBody(coordinates, velocity, mass, name);
}


int main()
{
    using namespace std;
    sun();
    sun2();
    probe1();       //different speeds
    probe2();       //
    probe3();       //
    probe4();       //
    probe5();       //different distance
    probe6();       //
    probe7();       //
    probe8();       //


    //planet();
    makeFiles();
    while (timeStep())
    {

    }
}