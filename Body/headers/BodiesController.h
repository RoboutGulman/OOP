#pragma once
#include "BodiesContainer.h"
class CBodiesController
{
  public:
    CBodiesController(std::istream &input, std::ostream &output, CBodiesContainer &container);
    enum class BodyType
    {
        Sphere,
        Parallelepiped,
        Cone,
        Cylinder,
        Compound
    };
    void HandleCommands();

  private:
    bool HandleCommand();

    std::istream &m_input;
    std::ostream &m_output;

    bool ReadBody(std::istream &args);
    bool ReadCone();
    bool ReadCylinder();
    bool ReadParallelepiped();
    bool ReadSphere();
    bool ReadCompoundBody();

    bool FindMaxWeight(std::istream &args);
    bool FindMinWeightInWater(std::istream &args);

    bool PrintAllBodies(std::istream &args);

    CBodiesContainer &m_container;

    using Handler = std::function<bool(std::istream &args)>;
    // Отображает название команды на её обработчик
    using ActionMap = std::map<std::string, Handler>;
    const ActionMap m_actionMap;
    inline static const std::map<std::string, BodyType> m_bodyTypeNames = {{"Compound", BodyType::Compound},
                                                                           {"Cone", BodyType::Cone},
                                                                           {"Cylinder", BodyType::Cylinder},
                                                                           {
                                                                               "Parallelepiped",
                                                                               BodyType::Parallelepiped,
                                                                           },
                                                                           {
                                                                               "Sphere",
                                                                               BodyType::Sphere,
                                                                           }};
};
