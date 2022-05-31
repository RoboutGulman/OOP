#pragma once
#include "Body.h"

//выделить контроллер который отвечает за общение с пользователем
//разделить ответственность BodiesContainer

class CBodiesContainer
{
  public:
    struct WeightAndBody
    {
        double weight;
        std::shared_ptr<CBody> body;
    };
    std::optional<WeightAndBody> FindMaxWeight();
    std::optional<WeightAndBody> FindMinWeightInWater();

    void AddCone(double density, double baseRadius, double heigth);
    void AddCylinder(double density, double baseRadius, double heigth);
    void AddParallelepiped(double density, double width, double length, double height);
    void AddSphere(double density, double radius);
    bool AddCompoundBody(const std::vector<int> &bodyNumbers);

    std::vector<std::shared_ptr<CBody>> GetAllBodies() const;

  private:
    std::vector<std::shared_ptr<CBody>> m_bodies;
};
