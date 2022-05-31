#include "stdafx.h"

#include "Cone.h"

CCone::CCone(double density, double baseRadius, double height)
    : CBody("Cone", density), m_baseRadius(baseRadius), m_height(height)
{
}

double CCone::GetBaseRadius() const
{
    return m_baseRadius;
}

double CCone::GetHeight() const
{
    return m_height;
}

double CCone::GetVolume() const
{
    return (pow(m_baseRadius, 2) * M_PI) * 1 / 3;
}

void CCone::AppendProperties(std::ostream &strm) const
{
    strm << "\tbase radius = " << std::setprecision(10) << GetBaseRadius() << std::endl
         << "\theight = " << GetHeight() << std::endl;
}
