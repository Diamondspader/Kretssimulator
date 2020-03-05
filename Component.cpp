//Component.cpp
#include "Component.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>

Component::Component(const std::string& name, double voltage,  Connection & p,  Connection & n) : name{ name }, positive{p}, negative{n}, voltage{voltage}
{

}



Battery::Battery(const std::string & name, double volt, Connection &p, Connection &n)
	: Component{ name, abs(volt), p, n }
{

}

Resistor::Resistor(const std::string & name, double ohm, Connection &p, Connection &n)
	: Component{ name, 0, p, n }, ohm{ohm}
{
	if (ohm<=0){
	throw std::invalid_argument("ohm can't be negative or zero");
	}
}
Capacitor::Capacitor(const std::string & name, double Farad, Connection &p, Connection &n)
	: Component{ name, 0, p, n }, farad{ Farad }, charge{0}
{

}


void Battery::SetConnection(const double & step)
{
	positive.SetPotential(voltage);
	negative.SetPotential(0);
}

void Resistor::SetConnection(const double & step)
{
	double diff = abs(positive.GetPotential()-negative.GetPotential());
	if (ohm == 0) 
	{
		throw std::invalid_argument("Division with zero!");
	}
	diff = (diff / ohm) * step;
	if (positive.GetPotential() >= negative.GetPotential())
	{
		positive.SetPotential(positive.GetPotential() - diff);
		negative.SetPotential(negative.GetPotential() + diff);
	}
	else
	{
		positive.SetPotential(positive.GetPotential() + diff);
		negative.SetPotential(negative.GetPotential() - diff);
	}
	
}

void Capacitor::SetConnection(const double & step) 
{
	double pot = abs(positive.GetPotential() - negative.GetPotential());
	pot = farad * (pot - charge) * step;
	charge += pot;
	if (positive.GetPotential() >= negative.GetPotential())
	{
	positive.SetPotential(positive.GetPotential() - pot);
	negative.SetPotential(negative.GetPotential() + pot);
	}

	else 
	{
	positive.SetPotential(positive.GetPotential() + pot);
	negative.SetPotential(negative.GetPotential() - pot);
	}
}

double Resistor::GetCurrent() const
{
	if(ohm == 0)
	{
		throw std::invalid_argument("Division by zero or invalid resistance!");
	}
	
	return voltage / ohm;
	
}

void Resistor::SetVoltage() 
{
	double diff = abs(positive.GetPotential() - negative.GetPotential());
	voltage = diff;
}

void Resistor::SetCurrent()
{
	if (ohm <= 0)
	{
		throw std::invalid_argument("There is no zero or negative ohm");
	}
	current = voltage / ohm;
}

void Capacitor::SetVoltage()
{
	double diff = abs(positive.GetPotential() - negative.GetPotential());
	voltage = diff;
}

void Capacitor::SetCurrent()
{
	current = farad * (abs(positive.GetPotential() - negative.GetPotential()) - charge);
}

double Capacitor::GetCurrent() const
{
	return farad * (abs(negative.GetPotential() - positive.GetPotential()) - charge);
}



void PrintCircuit(std::vector<Component*>& net)
{
	for (const auto& comps : net) 
	{
		std::cout << std::setw(11) << std::setfill(' ')
			<< comps->GetName() << " ";
	}
	std::cout << '\n';

	for (const auto& comps : net)
	{
		
		std::cout << std::setw(11) << std::setfill(' ')
		<<	" Volt  Curr ";
	}
	std::cout << '\n';
}


void Simulate(std::vector<Component*>& net, const double & loops, const int & outputs, const double & steps)
{
	PrintCircuit(net);
	for (int x{ 0 }; x < outputs; x++) 
	{
		for (int y{ 0 }; y < loops /outputs; y++)
		{
			for (unsigned int z{0}; z < net.size(); ++z )
			{
				net.at(z)->SetConnection(steps);
			}
			for (unsigned int z{ 0 }; z < net.size(); ++z)
			{
				net.at(z)->SetVoltage();
				net.at(z)->SetCurrent();
			}
			
		}
		for (const auto& comps : net) 
		{

			std::cout 	<< std::setw(5) << std::setfill(' ')
				<< std::setprecision(2) << std::fixed << comps->GetVoltage()
				<< "  " << comps->GetCurrent() << " ";
		}
		std::cout << '\n';
	}
}

void ClearMem(const std::vector<Component*>& net) 
{
	for (const auto& comps : net)
	{
		delete comps;
	}
}