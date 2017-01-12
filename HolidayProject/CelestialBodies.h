#pragma once
#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <math.h>
#include <array>



class CelestialBody
{
private:
    std::array<double, 3> m_coordinates, m_velocity, m_tempcoordinates, m_tempvelocity;
    double const m_mass;

    double m_kinEnergy;
    std::string m_name;
    void calcForces(std::array<double, 3> (&result));
public:
    static void copyTemp();
    double getKinEnergy();
    static double m_energy;
    static std::vector<CelestialBody*> celBodyList;
    CelestialBody();
    CelestialBody(std::array<double, 3>(&coordinates), std::array<double, 3>(&velocity), double &mass, std::string &name);
    ~CelestialBody();
    static const double newtonG;
    void updatePosition();
    double getMass();
    std::array<double, 3> getCoordinates();
    std::array<double, 3> getVelocity();
    std::string getName();
    static void deleteCelBody(std::string &name);


};

