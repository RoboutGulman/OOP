#include "../../headers/stdafx.h"

#include "../../headers/Bodies/Parallelepiped.h"

CParallelepiped::CParallelepiped(double density, double width, double length, double height)
    : CBody("Parallelepiped", density), m_width(width), m_length(length), m_height(height)
{
}

double CParallelepiped::GetHeight() const
{
    return m_height;
}

double CParallelepiped::GetLength() const
{
    return m_length;
}

double CParallelepiped::GetWidth() const
{
    return m_width;
}

double CParallelepiped::GetVolume() const
{
    return m_width * m_length * m_height;
}

void CParallelepiped::AppendProperties(std::ostream &strm) const
{
    strm << "\twidth = " << std::setprecision(10) << GetWidth() << std::endl
         << "\tlength = " << GetLength() << std::endl
         << "\theight = " << GetHeight() << std::endl;
}
