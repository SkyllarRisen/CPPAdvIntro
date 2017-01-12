#include "CelestialBodies.h"



void vectorAdd(std::array<double, 3>(&result), std::vector<std::array<double, 3>> const& vList)
{

    for (int i = 0; i < vList.size(); ++i)
    {
        result.at(0) += vList.at(i).at(0);
        result.at(1) += vList.at(i).at(1);
        result.at(2) += vList.at(i).at(2);
    }
}



std::vector<CelestialBody*> CelestialBody::celBodyList = {};
const double CelestialBody::newtonG{ 6.67408e-11 };
double CelestialBody::m_energy{ 0 };
CelestialBody::CelestialBody() : m_mass{ 0 }, m_coordinates{}, m_velocity{}
{
    std::cout << "Wrong constructor, you fool." << std::endl;

}

CelestialBody::CelestialBody(std::array<double, 3>(&coordinates), std::array<double, 3>(&velocity), double &mass, std::string &name) : m_mass{ mass }, m_name{name}
{


    for (int i = 0; i < 3; ++i)
    {
        m_coordinates.at(i) = coordinates.at(i);
        m_velocity.at(i) = velocity.at(i);
    }
    celBodyList.push_back(this);
}

CelestialBody::~CelestialBody()
{
    
    for (int i = 0; i < celBodyList.size();)
    {

        if (this == celBodyList.at(i))
        {

            celBodyList.erase(celBodyList.begin()+i);
            continue;
        }
        ++i;
    }
}

void CelestialBody::deleteCelBody(std::string& name)
{
    for (int i = 0; i < celBodyList.size();)
    {
        if (name == celBodyList.at(i)->m_name)
        {
            delete celBodyList.at(i);
            continue;
        }
        ++i;
    }
}

double CelestialBody::getMass()
{
    return m_mass;
}

std::array<double, 3> CelestialBody::getCoordinates()
{
    return m_coordinates;
}

std::array<double, 3> CelestialBody::getVelocity()
{
    return m_velocity;
}

std::string CelestialBody::getName()
{
    return m_name;
}

void CelestialBody::calcForces(std::array<double, 3>(&result))
{
    if (celBodyList.size() < 2)
    {
        result.at(0) = 0.;
        result.at(1) = 0.;
        result.at(2) = 0.;
    }
    else
    {
        std::vector<std::array<double, 3>> temp(0);
        for (int i = 0; i < celBodyList.size(); ++i)
        {
            if (this == celBodyList.at(i))
                continue;
            std::array<double, 3> normVec, temp2, forces;
            double dist, distSquared;
            temp2.at(0) = this->getCoordinates().at(0) - celBodyList.at(i)->getCoordinates().at(0);
            temp2.at(1) = this->getCoordinates().at(1) - celBodyList.at(i)->getCoordinates().at(1);
            temp2.at(2) = this->getCoordinates().at(2) - celBodyList.at(i)->getCoordinates().at(2);
            distSquared = temp2.at(0) * temp2.at(0) + temp2.at(1) * temp2.at(1) + temp2.at(2) * temp2.at(2);
            dist = std::sqrt(distSquared);            
            normVec.at(0) = temp2.at(0) / dist;
            normVec.at(1) = temp2.at(1) / dist;
            normVec.at(2) = temp2.at(2) / dist;           
            double equation = ((-1)*(CelestialBody::newtonG)*(celBodyList.at(i)->getMass()) / distSquared);
            forces.at(0) = equation*normVec.at(0);
            forces.at(1) = equation*normVec.at(1);
            forces.at(2) = equation*normVec.at(2);
            temp.push_back(forces);
        }
        vectorAdd(result, temp);
    }
}

void CelestialBody::updatePosition()
{
    std::array<double, 3> forces{ 0,0,0 };
    this->calcForces(forces);
    this->m_coordinates.at(0) = m_coordinates.at(0) + m_velocity.at(0)*1000 + 0.5*forces.at(0) * 1000 * 1000;
    this->m_coordinates.at(1) = m_coordinates.at(1) + m_velocity.at(1) * 1000 + 0.5*forces.at(1) * 1000 * 1000;
    this->m_coordinates.at(2) = m_coordinates.at(2) + m_velocity.at(2) * 1000 + 0.5*forces.at(2) * 1000 * 1000;
    this->m_velocity.at(0) = m_velocity.at(0) + forces.at(0) * 1000;
    this->m_velocity.at(1) = m_velocity.at(1) + forces.at(1) * 1000;
    this->m_velocity.at(2) = m_velocity.at(2) + forces.at(2) * 1000;
    this->m_kinEnergy = 0.5*this->m_mass*(this->m_velocity.at(0)*this->m_velocity.at(0) + this->m_velocity.at(1)*this->m_velocity.at(1) + this->m_velocity.at(2)*this->m_velocity.at(2));
    CelestialBody::m_energy += m_kinEnergy;
}

double CelestialBody::getKinEnergy()
{
    return m_kinEnergy;
}