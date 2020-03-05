//Component.h
#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include <vector>
#include <iostream>


class Connection 
{
public:
	
	const double GetPotential() { return potential; }
	void SetPotential(const double & pot) { potential = pot; }

private:
	double potential{0};
};

class Component
{
public:
	Component(const std::string & name, double voltage , Connection &p, Connection &n);
	virtual void SetConnection(const double & step) = 0;
	std::string GetName() const { return name; }
	
	virtual double GetVoltage() const { return voltage; }
	virtual double GetCurrent() const { return current; }
	virtual void SetVoltage() {}
	virtual void SetCurrent() {}
	
	virtual ~Component() {}
protected:
	std::string name;
	double voltage{};
	double current{};
	Connection& positive;
	Connection& negative;
};

class Battery : public Component
{
public:
	Battery(const std::string & name, double volt, Connection &p, Connection &n);
	void SetConnection(const double & step) override;
private:
	
};

class Resistor : public Component
{
public:
	Resistor(const std::string & name, double ohm, Connection &p, Connection &n);
	void SetConnection(const double & step) override;
	double GetCurrent()const override;
	void SetVoltage() override;
	void SetCurrent() override;
private:
	double ohm;
};

class Capacitor : public Component
{
public:
	Capacitor(const std::string & name, double Farad, Connection &p, Connection &n);
	void SetConnection(const double & step) override;
	double GetCurrent()const override;
	void SetVoltage() override;
	void SetCurrent() override;
private:
	double charge;
	double farad;
};

void Simulate(std::vector<Component*>& net, const double & loops, const int & outputs, const double & steps);
void ClearMem(const std::vector<Component*>& net);

#endif