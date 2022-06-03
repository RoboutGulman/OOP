#include "../../headers/stdafx.h"

#include "../../headers/Bodies/Compound.h"

CCompound::CCompound() : CBody("Compound", 0)
{
}

bool CCompound::AddBody(std::shared_ptr<CBody> body)
{
    auto bodyPtr = std::dynamic_pointer_cast<CCompound>(body);
    if (bodyPtr && std::addressof(*bodyPtr) == this)
    {
        return false;
    }
    m_bodies.emplace_back(body);
    return true;
}

double CCompound::GetMass() const
{
    double mass = 0;
    for (auto it = std::begin(m_bodies); it != std::end(m_bodies); ++it)
    {
        mass += (*it)->GetMass();
    }
    return mass;
}

double CCompound::GetDensity() const
{
    double mass = 0, volume = 0;
    for (auto it = std::begin(m_bodies); it != std::end(m_bodies); ++it)
    {
        mass += (*it)->GetMass();
        volume += (*it)->GetVolume();
    }
    if (fabs(volume) <= std::numeric_limits<double>::epsilon() * fabs(volume))
    {
        return volume;
    }
    return (mass / volume);
}

double CCompound::GetVolume() const
{
    double volume = 0;
    for (auto it = std::begin(m_bodies); it != std::end(m_bodies); ++it)
    {
        volume += (*it)->GetVolume();
    }
    return volume;
}

void CCompound::AppendProperties(std::ostream &strm) const
{
    strm << "\tContained bodies:\n";
    int i = 1;
    for (auto it = std::begin(m_bodies); it != std::end(m_bodies); ++it, i++)
    {
        strm << "\t\t" + i + ')' + (*it)->ToString();
    }
}
