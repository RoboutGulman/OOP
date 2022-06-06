#include "../stdafx.h"

#include "../headers/Bodies/Parallelepiped.h"
#include "../headers/Bodies/Sphere.h"
#include "../headers/BodiesContainer.h"
#include "../headers/BodiesController.h"

int main()
{
   
   CBodiesContainer container;
   CBodiesController remoteControl(std::cin, std::cout, container);

    remoteControl.HandleCommands(); 
    return 0;
}
