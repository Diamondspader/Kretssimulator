#include "Component.h"
#include <iostream>
#include <string>
#include <vector>

Component::Component() : name{}, positive{}, negative{}
{

}

Component::Component(std::string name, Connection p, Connection n) : name{name}, positive{}, negative{}
{
	positive = &p;
	negative = &n;
}

Battery::Battery(std::string name, double volt, Connection p, Connection n)
	: Component{ name, p, n }, voltage{volt}
{

}

Resistor::Resistor(std::string name, double ohm, Connection p, Connection n)
	: Component{ name, p, n }, ohm{ohm}
{

}


void Battery::SetConnection()
{
	positive->SetPotential(voltage);
	negative->SetPotential(0);
}

void Resistor::SetConnection()
{
	double diff = positive->GetPotential()-negative->GetPotential();
	diff = diff / ohm;
	positive->SetPotential(positive->GetPotential() - diff);
	positive->SetPotential(negative->GetPotential() + diff);

}


void Simulate(std::vector<Component*> net, int loops, int outputs, int steps)
{

}
