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
        selFile << CelestialBody::celBodyList.at(i)->getCoordinates().at(0) << " " << CelestialBody::celBodyList.at(i)->getCoordinates().at(1) << " " << CelestialBody::celBodyList.at(i)->getCoordinates().at(2) << std::endl;
        selFile.close();
    }
    CelestialBody::m_energy += potEnergy;
    selFile.open("Energy.dat", std::ios::app);
    selFile << CelestialBody::m_energy << std::endl;
    selFile.close();
    if (steps > 10)
        return false;
    ++steps;
    CelestialBody::m_energy = 0;
    return true;
}

void sun()
{
    std::array<double, 3> coordinates{ 0,0,0 };
    std::array<double, 3> velocity{ 0,0,0 };
    std::string name{ "Sun" };
    double mass{ 2e30 };
    new CelestialBody(coordinates, velocity, mass, name);    
}

void planet()
{
    std::array<double, 3> coordinates{ 150e9,0,0 };
    std::array<double, 3> velocity{ 0,3e4,0 };
    std::string name{ "planet" };
    double mass{ 6e24 };
    new CelestialBody(coordinates, velocity, mass, name);
}

int main()
{
    using namespace std;
    sun();
    planet();
    makeFiles();
    while (timeStep())
    {

    }
}