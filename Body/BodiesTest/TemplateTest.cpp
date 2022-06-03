// TemplateTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../Body/headers/stdafx.h"

#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Body/headers/Bodies/Body.h"
#include "../Body/headers/Bodies/Compound.h"
#include "../Body/headers/Bodies/Cone.h"
#include "../Body/headers/Bodies/Cylinder.h"
#include "../Body/headers/Bodies/Parallelepiped.h"
#include "../Body/headers/Bodies/Sphere.h"
#include "../Body/headers/BodiesContainer.h"
#include "../Body/headers/BodiesController.h"
#include <math.h>

SCENARIO("solid bodies")
{
    WHEN("We create cone")
    {
        CCone cone(2, 3.23, 4);
        THEN("it accepts correct values")
        {
            CHECK(cone.GetBaseRadius() == 3.23);
            CHECK(cone.GetDensity() == 2);
            CHECK(cone.GetHeight() == 4);
            CHECK(cone.GetVolume() == (pow(cone.GetBaseRadius(), 2) * M_PI) * 1 / 3);
            CHECK(cone.GetMass() == cone.GetVolume() * cone.GetDensity());
            CHECK(cone.ToString() == "Cone:\n\tdensity = 2\n\tvolume = 10.92530733\n\tmass = 21.85061466\n\tbase "
                                     "radius = 3.23\n\theight = 4\n");
        }
    }
    WHEN("We create cylinder")
    {
        CCylinder cylinder(2, 3, 4.67);
        THEN("it accepts correct values")
        {
            CHECK(cylinder.GetBaseRadius() == 3);
            CHECK(cylinder.GetDensity() == 2);
            CHECK(cylinder.GetHeight() == 4.67);
            CHECK(cylinder.GetVolume() == pow(cylinder.GetBaseRadius(), 2) * M_PI * cylinder.GetHeight());
            CHECK(cylinder.GetMass() == cylinder.GetVolume() * cylinder.GetDensity());
            CHECK(cylinder.ToString() ==
                  "Cylinder:\n\tdensity = 2\n\tvolume = 132.0411392\n\tmass = 264.0822785\n\tbase "
                  "radius = 3\n\theight = 4.67\n");
        }
    }
    WHEN("We create parallelepiped")
    {
        CParallelepiped parallelepiped(4.56, 10, 2, 3);
        THEN("it accepts correct values")
        {
            CHECK(parallelepiped.GetDensity() == 4.56);
            CHECK(parallelepiped.GetWidth() == 10);
            CHECK(parallelepiped.GetLength() == 2);
            CHECK(parallelepiped.GetHeight() == 3);
            CHECK(parallelepiped.GetVolume() ==
                  parallelepiped.GetWidth() * parallelepiped.GetLength() * parallelepiped.GetHeight());
            CHECK(parallelepiped.GetMass() == parallelepiped.GetVolume() * parallelepiped.GetDensity());
            CHECK(parallelepiped.ToString() == "Parallelepiped:\n\tdensity = 4.56\n\tvolume = 60\n\tmass = "
                                               "273.6\n\twidth = 10\n\tlength = 2\n\theight = 3\n");
        }
    }
    WHEN("We create sphere")
    {
        CSphere sphere(4.56, 2);
        THEN("it accepts correct values")
        {
            CHECK(sphere.GetDensity() == 4.56);
            CHECK(sphere.GetRadius() == 2);
            CHECK(sphere.GetVolume() == (pow(sphere.GetRadius(), 3) * M_PI) * 4 / 3);
            CHECK(sphere.GetMass() == sphere.GetVolume() * sphere.GetDensity());
            CHECK(sphere.ToString() == "Sphere:\n\tdensity = 4.56\n\tvolume = 33.51032164\n\tmass = "
                                       "152.8070667\n\tradius = 2\n");
        }
    }
}

//ограничить помещние составного тела в себя само
SCENARIO("compound bodies")
{
    CCone cone(2, 3.23, 4);
    CParallelepiped parallelepiped(4.56, 10, 2, 3);
    CSphere sphere(4.56, 2);
    CCompound compound;
    compound.AddBody(std::move(std::shared_ptr<CSphere>(new CSphere{4.56, 2})));
    compound.AddBody(std::move(std::shared_ptr<CParallelepiped>(new CParallelepiped{4.56, 10, 2, 3})));
    compound.AddBody(std::move(std::shared_ptr<CCone>(new CCone{2, 3.23, 4})));
    WHEN("we check density of compound body")
    {
        double compoundBodyDensity = compound.GetDensity();
        double bodiesMassesToVolumes = (cone.GetMass() + parallelepiped.GetMass() + sphere.GetMass()) /
                                       (cone.GetVolume() + parallelepiped.GetVolume() + sphere.GetVolume());
        THEN("it's density is equal to the ratio of the masses of the constituent bodies to their volumes")
        {
            CHECK(fabs(compoundBodyDensity - bodiesMassesToVolumes) <=
                  std::numeric_limits<double>::epsilon() * fabs(compoundBodyDensity + bodiesMassesToVolumes));
        }
    }
    WHEN("we check mass of compound body")
    {
        double compoundBodyMass = compound.GetMass();
        double sumOfMasses = (cone.GetMass() + parallelepiped.GetMass() + sphere.GetMass());
        THEN("it's mass is equal to the sum of masses of the constituent bodies ")
        {
            CHECK(fabs(compoundBodyMass - sumOfMasses) <=
                  std::numeric_limits<double>::epsilon() * fabs(compoundBodyMass + sumOfMasses));
        }
    }
    WHEN("we check volume of compound body")
    {
        double compoundBodyVolume = compound.GetVolume();
        double sumOfVolumes = (cone.GetVolume() + parallelepiped.GetVolume() + sphere.GetVolume());
        THEN("it's volume is equal to the sum of volumes of the constituent bodies ")
        {
            CHECK(fabs(compoundBodyVolume - sumOfVolumes) <=
                  std::numeric_limits<double>::epsilon() * fabs(compoundBodyVolume + sumOfVolumes));
        }
    }
    WHEN("we create a compund body with a compound child body")
    {
        auto compoundPtr = std::shared_ptr<CCompound>(new CCompound{});
        compoundPtr->AddBody(std::move(std::shared_ptr<CSphere>(new CSphere{4.56, 2})));
        compoundPtr->AddBody(std::move(std::shared_ptr<CParallelepiped>(new CParallelepiped{4.56, 10, 2, 3})));
        compoundPtr->AddBody(std::move(std::shared_ptr<CCone>(new CCone{2, 3.23, 4})));
        CHECK(!compoundPtr->AddBody(compoundPtr));

        CCylinder cylinder(3, 3.23, 2);

        CCompound bigCompound;
        bigCompound.AddBody(std::move(compoundPtr));
        bigCompound.AddBody(std::move(std::shared_ptr<CCylinder>(new CCylinder{3, 3.23, 2})));

        double compoundBodyVolume = bigCompound.GetVolume();
        double compoundBodyMass = bigCompound.GetMass();
        double compoundBodyDensity = bigCompound.GetDensity();
        double sumOfVolumes = (cylinder.GetVolume() + compound.GetVolume());
        double sumOfMasses = (cylinder.GetMass() + compound.GetMass());
        double bodiesMassesToVolumes = sumOfMasses / sumOfVolumes;
        THEN("it's volume is equal to the sum of volumes of the constituent bodies ")
        {
            CHECK(fabs(compoundBodyVolume - sumOfVolumes) <=
                  std::numeric_limits<double>::epsilon() * fabs(compoundBodyVolume + sumOfVolumes));
            CHECK(fabs(compoundBodyMass - sumOfMasses) <=
                  std::numeric_limits<double>::epsilon() * fabs(compoundBodyMass + sumOfMasses));
            CHECK(fabs(compoundBodyDensity - bodiesMassesToVolumes) <=
                  std::numeric_limits<double>::epsilon() * fabs(compoundBodyDensity + bodiesMassesToVolumes));
        }
    }
}

/*SCENARIO("bodies Container")
{
    CBodiesContainer container;
    WHEN("we add bodies to container")
    {
        container.AddCone(3, 4, 5);
        container.AddParallelepiped(7, 8, 9, 10);
        auto containerBodies = container.GetAllBodies();

        std::vector<std::shared_ptr<CBody>> bodies;
        bodies.emplace_back(std::move(std::shared_ptr<CCone>(new CCone{3, 4, 5})));
        bodies.emplace_back(std::move(std::shared_ptr<CParallelepiped>(new CParallelepiped{7, 8, 9, 10})));

        THEN("it correctly contains it")
        {
            for (int i = 0; i < containerBodies.size(); i++)
            {
                CHECK(containerBodies[i]->GetDensity() == bodies[i]->GetDensity());
                CHECK(containerBodies[i]->GetMass() == bodies[i]->GetMass());
                CHECK(containerBodies[i]->GetVolume() == bodies[i]->GetVolume());
            }
        }
    }
    WHEN("we try to add compound body to container")
    {
        container.AddCone(3, 4, 5);
        container.AddParallelepiped(7, 8, 9, 10);
        std::vector<int> numberOfBodies{0, 1};
        container.AddCompoundBody();
        container.AddBodyToCompoundBody(2, 1);
        container.AddBodyToCompoundBody(2, 0);
        std::shared_ptr<CBody> compoundBodyPtr = container.GetAllBodies()[2];

        CCone cone(3, 4, 5);
        CParallelepiped parallelepiped(7, 8, 9, 10);

        THEN("container hold its specifications ")
        {
            CHECK(compoundBodyPtr->GetMass() == cone.GetMass() + parallelepiped.GetMass());
        }
    }
    WHEN("we try to add compound body to empty container")
    {
        std::vector<int> numberOfBodies{0, 1};

        THEN("container drops error and not add compound body ")
        {
            CHECK(!container.AddCompoundBody(numberOfBodies));
        }
    }
    WHEN("we try to add compound body with incorrect numbers")
    {
        container.AddCone(3, 4, 5);
        std::vector<int> numberOfBodies{-5, 5};

        THEN("container drops error and not add compound body")
        {
            CHECK(!container.AddCompoundBody(numberOfBodies));
        }
    }
}

SCENARIO("Find Maximum Weight Function")
{
    CBodiesContainer container;
    WHEN("there are no bodies in container")
    {
        THEN("it returns null")
        {
            CHECK(!container.FindMaxWeight());
        }
    }
    WHEN("there are one body in container")
    {
        container.AddCylinder(3, 3.23, 2);
        auto result = container.FindMaxWeight();

        CCylinder cylinder(3, 3.23, 2);

        THEN("it returns this body and it's mass")
        {
            REQUIRE(result);
            CHECK(result->weight == cylinder.GetMass());
        }
    }
    WHEN("we try to find max weight in container that contains more than one body")
    {
        container.AddParallelepiped(5, 8, 3, 5);
        container.AddSphere(2, 1);
        auto result = container.FindMaxWeight();

        CParallelepiped parallelepiped(5, 8, 3, 5);
        CSphere sphere(2, 1);

        THEN("it returns the body weight with the maximum mass")
        {
            CHECK(sphere.GetMass() < parallelepiped.GetMass());
            REQUIRE(result);
            CHECK(result->weight == parallelepiped.GetMass());
        }
    }
    WHEN("the bodies in container have equal mass")
    {
        container.AddSphere(5, 8);
        container.AddSphere(5, 8);
        auto result = container.FindMaxWeight();

        CSphere sphere(5, 8);

        THEN("will return the weight of one of them")
        {
            REQUIRE(result);
            CHECK(result->weight == sphere.GetMass());
        }
    }
    WHEN("there are compound bodies in contaier")
    {
        container.AddCone(3, 4, 5);
        container.AddParallelepiped(7, 8, 9, 10);
        std::vector<int> numberOfBodies{0, 1};
        container.AddCompoundBody(numberOfBodies);
        auto result = container.FindMaxWeight();

        CCone cone(3, 4, 5);
        CParallelepiped parallelepiped(7, 8, 9, 10);

        THEN("container hold its specifications ")
        {
            CHECK(result->weight == cone.GetMass() + parallelepiped.GetMass());
        }
    }
}

SCENARIO("Find Minimum Weight In Water Function")
{
    CBodiesContainer container;
    WHEN("there are no bodies in container")
    {
        THEN("it returns null")
        {
            CHECK(!container.FindMinWeightInWater());
        }
    }
    WHEN("there are one body in container")
    {
        container.AddCylinder(3, 3.23, 2);
        auto result = container.FindMinWeightInWater();

        CCylinder cylinder(3, 3.23, 2);

        THEN("it returns this body and it's mass")
        {
            REQUIRE(result);
            CHECK(result->weight == (cylinder.GetDensity() - 1000) * 9.8 * cylinder.GetVolume());
        }
    }
    WHEN("we try to find Minimum Weight In Water in container that contains more than one body")
    {
        container.AddParallelepiped(1100, 8, 3, 5);
        container.AddSphere(1001, 1);
        auto result = container.FindMinWeightInWater();

        CParallelepiped parallelepiped(1100, 8, 3, 5);
        CSphere sphere(1001, 1);
        double parallelepipedWeightInWater = (parallelepiped.GetDensity() - 1000) * 9.8 * parallelepiped.GetVolume();
        double sphereWeightInWater = (sphere.GetDensity() - 1000) * 9.8 * sphere.GetVolume();

        THEN("it returns the body weight with the minimum weight in water")
        {
            CHECK(sphereWeightInWater < parallelepipedWeightInWater);
            REQUIRE(result);
            CHECK(result->weight == sphereWeightInWater);
        }
    }
}

SCENARIO("Bodies Controler test 1 (find maximum weight)")
{
    std::string input =
        "newBody Parallelepiped\n10 1 2 3\nnewBody Parallelepiped\n10.00001 1 2 3\nfindMaxWeight\nExit\n";

    std::istringstream strmIn(input);
    std::ostringstream strmOut;
    CBodiesContainer container;
    CBodiesController remoteControl(strmIn, strmOut, container);

    remoteControl.HandleCommands();

    std::string s = strmOut.str();
    REQUIRE(s == "> enter a density, width, length and height: > enter a density, width, length and height: > max "
                 "weight is 60.0001 newtons of body:\nParallelepiped:\n\tdensity = 10.00001\n\tvolume = 6\n\tmass = "
                 "60.00006\n\twidth = 1\n\tlength = 2\n\theight = 3\n> ");
}

SCENARIO("Bodies Controler test 2 (Find Minimum Weight In Water)")
{
    std::string input =
        "newBody Parallelepiped\n1001 1 2 3\nnewBody Parallelepiped\n1000.0001 1 2 3\nfindMinWaterWeight\nExit\n";

    std::istringstream strmIn(input);
    std::ostringstream strmOut;
    CBodiesContainer container;
    CBodiesController remoteControl(strmIn, strmOut, container);

    remoteControl.HandleCommands();

    std::string s = strmOut.str();
    REQUIRE(
        s ==
        "> enter a density, width, length and height: > enter a density, width, length and height: > min "
        "weight in water is 0.00588 newtons of body:\nParallelepiped:\n\tdensity = 1000.0001\n\tvolume = 6\n\tmass = "
        "6000.0006\n\twidth = 1\n\tlength = 2\n\theight = 3\n> ");
}
*/