// Kretssimulator.cpp
#include "Component.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

int main(int argc, char* argv[])
{
    char *pEnd;
    double digit;
    
    
    if (argc != 5)
    {
        std::cerr << "Invalid amount of arguments" << '\n';
        return 0;
    }

    for (int i{ 1 }; i < argc; i++)
    {

        digit = std::strtod(argv[i], &pEnd);
        if (digit <= 0)
        {
            std::cerr << "Invalid argument ";
            throw std::invalid_argument("Invalid argument");
            return 0;
        }
    }
    
   

    double loops = std::strtod(argv[1], &pEnd);
    std::cout << loops << '\n';
    int outputs = std::strtod(argv[2], &pEnd);
    std::cout << outputs << '\n';
    double steps = std::strtod(argv[3], &pEnd);
    std::cout << steps << '\n';
    double voltage = std::strtod(argv[4], &pEnd);
    std::cout << voltage << '\n';

    Connection p1, n1, Q124, Q23;
    std::vector<Component*> net1;
    net1.push_back(new Battery("bat", voltage, p1, n1));
    net1.push_back(new Resistor("R1", 6.0, p1, Q124));
    net1.push_back(new Resistor("R2", 4.0, Q124, Q23));
    net1.push_back(new Resistor("R3", 8.0, Q23, n1));
    net1.push_back(new Resistor("R4", 12.0, Q124, n1));
    Simulate(net1, loops, outputs, steps);
   
    std::cout << '\n';
    std::cout << '\n';
   
   Connection n2,p2,l2,r2;
    std::vector<Component*> net2;
	net2.push_back(new Battery("Bat", voltage, p2, n2));
    net2.push_back(new Resistor("R1", 150.0, p2, l2));
    net2.push_back(new Resistor("R2", 50.0, p2, r2));
    net2.push_back(new Resistor("R3", 100.0, r2, l2));
    net2.push_back(new Resistor("R4", 300.0, l2, n2));
    net2.push_back(new Resistor("R5", 250.0, r2, n2));
    Simulate(net2, loops, outputs, steps);
    
    std::cout << '\n';
    std::cout << '\n';

	Connection n3,p3,l3,r3;
	std::vector<Component*> net3;
    net3.push_back(new Battery("Bat", voltage, n3, p3));
    net3.push_back(new Resistor("R1", 150.0, p3, l3));
    net3.push_back(new Resistor("R2", 50.0, p3, r3));
    net3.push_back(new Capacitor("C3", 1.0, r3, l3));
    net3.push_back(new Resistor("R4", 300.0, l3, n3));
    net3.push_back(new Capacitor("C5", 0.75, r3, n3));
    Simulate(net3, loops, outputs, steps);
    
    ClearMem(net1);
    ClearMem(net2);
    ClearMem(net3);
    return 0;
}