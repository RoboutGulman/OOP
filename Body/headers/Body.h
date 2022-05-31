#pragma once

class CBody
{
  protected:
    CBody(const std::string &type, double density);
    void SetDensity(double density);

  public:
    double GetDensity() const;
    virtual double GetVolume() const = 0;
    double GetMass() const;
    std::string ToString() const;

  private:
    virtual void AppendProperties(std::ostream &strm) const = 0;
    double m_density;
    std::string m_type;
};
