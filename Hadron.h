// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the Hadron class.

#ifndef HADRON_H
#define HADRON_H

#include "Particle.h"

class Hadron : public Particle
{
public:
  Hadron(int id = 0, double energy = 0.0);
  std::string get_type() const override { return "Hadron"; }
  double get_charge() const override { return 1.0; }

protected:
  double get_mass() const override;
};

#endif // HADRON_H