#pragma once
#include "Body.h"

class CParallelepiped final : public CBody
{
  public:
    CParallelepiped(double density, double width, double length, double height);

    double GetWidth() const;
    double GetLength() const;
    double GetHeight() const;
    double GetVolume() const override;

  private:
    void AppendProperties(std::ostream &strm) const override;
    double m_width;
    double m_length;
    double m_height;
};
