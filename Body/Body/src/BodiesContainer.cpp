#include "../headers/stdafx.h"

#include "../headers/Bodies/Body.h"
#include "../headers/Bodies/Compound.h"
#include "../headers/Bodies/Cone.h"
#include "../headers/Bodies/Cylinder.h"
#include "../headers/Bodies/Parallelepiped.h"
#include "../headers/Bodies/Sphere.h"
#include "../headers/BodiesContainer.h"

void CBodiesContainer::AddCone(double density, double baseRadius, double heigth)
{
    m_bodies.emplace_back(std::move(std::shared_ptr<CCone>(new CCone{density, baseRadius, heigth})));
}

void CBodiesContainer::AddCylinder(double density, double baseRadius, double heigth)
{
    m_bodies.emplace_back(std::move(std::shared_ptr<CCylinder>(new CCylinder{density, baseRadius, heigth})));
}

void CBodiesContainer::AddParallelepiped(double density, double width, double length, double height)
{
    m_bodies.emplace_back(
        std::move(std::shared_ptr<CParallelepiped>(new CParallelepiped{density, width, length, height})));
}

void CBodiesContainer::AddSphere(double density, double radius)
{
    m_bodies.emplace_back(std::move(std::shared_ptr<CSphere>(new CSphere{density, radius})));
}

bool CBodiesContainer::AddCompoundBody(const std::vector<int> &bodyNumbers)
{
    std::vector<std::shared_ptr<CBody>> bodies;
    for (int bodyNumber : bodyNumbers)
    {
        if (m_bodies.empty() || bodyNumber < 0 || bodyNumber > m_bodies.size())
        {
            return false;
        }
        bodies.emplace_back(m_bodies[bodyNumber]);
    }
    m_bodies.emplace_back(std::move(std::shared_ptr<CCompound>(new CCompound{bodies})));
    return true;
}

std::vector<std::shared_ptr<CBody>> CBodiesContainer::GetAllBodies() const
{
    return m_bodies;
}

std::optional<CBodiesContainer::WeightAndBody> CBodiesContainer::FindMaxWeight()
{
    if (m_bodies.empty())
    {
        return std::nullopt;
    }

    WeightAndBody result;
    result.body = m_bodies[0];
    result.weight = m_bodies[0]->GetMass();

    double temp;
    for (auto it = std::begin(m_bodies); it != std::end(m_bodies); ++it)
    {
        if ((temp = (*it)->GetMass()) > result.weight)
        {
            result.body = *it;
            result.weight = temp;
        }
    }
    return result;
}

double CalculateWeightInWater(std::shared_ptr<CBody> body)
{
    return (body->GetDensity() - 1000) * 9.8 * body->GetVolume();
}

std::optional<CBodiesContainer::WeightAndBody> CBodiesContainer::FindMinWeightInWater()
{
    if (m_bodies.empty())
    {
        return std::nullopt;
    }

    WeightAndBody result;
    result.body = m_bodies[0];
    result.weight = CalculateWeightInWater(m_bodies[0]);
    //вынести расчёт формулы в функцию
    double temp;
    for (auto it = std::begin(m_bodies); it != std::end(m_bodies); ++it)
    {
        temp = CalculateWeightInWater(*it);
        if (temp < result.weight)
        {
            result.body = *it;
            result.weight = temp;
        }
    }
    return result;
}
