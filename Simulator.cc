#include "Component.h"
#include <iostream>



int main(int argc, char** argv)
{
  std::cout << "You have entered " << argc
     << " arguments:" << "\n";

     for (int i = 0; i < argc; ++i)
     {
       if(argv[i] < 0)
       {
         //throw exception
       }
       std::cout << argv[i] << "\n";
       //first iterations, outputs, steps, Volt
     }
return 0;
}
