#include "../../stdafx.h"

#include "../../headers/Bodies/Body.h"

CBody::CBody(const std::string &type, double density) : m_density(density), m_type(type)
{
}
// default destructor

double CBody::GetDensity() const
{
    return m_density;
}

double CBody::GetMass() const
{
    return GetVolume() * GetDensity();
}

void CBody::SetDensity(double density)
{
    m_density = density;
}

std::string CBody::ToString() const
{
    std::ostringstream strm;
    strm << m_type << ":" << std::endl
         << std::setprecision(10) << "\tdensity = " << GetDensity() << std::endl
         << "\tvolume = " << GetVolume() << std::endl
         << "\tmass = " << GetMass() << std::endl;
    AppendProperties(strm);
    return strm.str();
}
