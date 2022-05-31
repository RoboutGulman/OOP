#pragma once
#include "Body.h"

class CCompound final : public CBody
{
  public:
    CCompound(std::vector<std::shared_ptr<CBody>> bodies);

    double GetVolume() const override;
    bool AddBody(std::shared_ptr<CBody> body);

  private:
    void AppendProperties(std::ostream &strm) const override;
    std::vector<std::shared_ptr<CBody>> m_bodies;
    double m_volume;
    std::string m_properties;
};
