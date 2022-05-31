#include "stdafx.h"

#include "Compound.h"

CCompound::CCompound(std::vector<std::shared_ptr<CBody>> bodies)
    : CBody("Compound", 0), m_bodies(bodies), m_volume(0), m_properties("\tComposite bodies:\n")
{
    //сделать отложенную инициализация родителя, убрать метод SetDensity(посмотреть, можно ли)
    double mass = 0;
    int i = 1;
    for (auto it = std::begin(m_bodies); it != std::end(m_bodies); ++it, i++)
    {
        mass += (*it)->GetMass();
        m_volume += (*it)->GetVolume();
        m_properties += "\t\t" + i + ')' + (*it)->ToString();
    }
    SetDensity(mass / m_volume);
}

/*bool CCompound::AddBody(std::shared_ptr<CBody> body)
{
    if (std::addressof(dynamic_cast<CCompound&>(*body)) == this)
    {
        std::cout<<"it equal!!"<<std::endl;
    }

}*/
//если тело не может измениться, рассчитывать характеристики при инициаизации
double CCompound::GetVolume() const
{

    return m_volume;
}

void CCompound::AppendProperties(std::ostream &strm) const
{
    strm << m_properties;
}
