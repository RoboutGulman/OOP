#pragma once
#include "Body.h"

class CCompound final : public CBody
{
  public:
    CCompound();

    bool IsContains(CCompound* containedBody) const;
    double GetVolume() const override;
    double GetMass() const override;
    double GetDensity() const override;

    bool AddBody(std::shared_ptr<CBody> body);

  private:
    void AppendProperties(std::ostream &strm) const override;
    std::vector<std::shared_ptr<CBody>> m_bodies;
};
