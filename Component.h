#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <string>

Class Connection
{
public:
Connection();

int GetPotential()const { return potential; }
int SetPotential(const int & pot){  potential = pot; }

~Connection(){};
private:
  int potential{};
};


Class Component
{
public:
Component();

~Component(){};
private:



};

Class Battery : public Component
{
public:
Battery();
Battery(std::string name, double voltage, Connection p, Connection n);


private:
  std::string name;
  double voltage;
  double current;
  Connection positive;
  Connection negative;
};

Class Resistor : public Component
{
public:
  resistor();
  resistor(std::string name, double ohm, Connection p, Connection n);

private:
  std::string name;
  double ohm;
  double current;
  Connection positive;
  Connection negative;


};



simulate(std::vector<component*>& net,
          int iteration, int outputs, int steps)
{

}




#endif
