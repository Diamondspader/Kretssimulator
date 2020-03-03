#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include <vector>


class Connection 
{
public:
	Connection() {};
	const double GetPotential() { return potential; }
	void SetPotential(const double & pot) { potential = pot; }

private:
	double potential{};
};

class Component
{
public:
	Component();
	Component(std::string name, Connection p, Connection n);
	virtual void SetConnection() = 0;
protected:
	std::string name;
	Connection* positive;
	Connection* negative;
};

class Battery : public Component
{
public:
	Battery(std::string name, double volt, Connection p, Connection n);
	void SetConnection();
private:
	double voltage;
};

class Resistor : public Component
{
public:
	Resistor(std::string name, double ohm, Connection p, Connection n);
	void SetConnection();
private:
	double ohm;
};


void Simulate(std::vector<Component*> net, int loops, int outputs, int steps);


#endif