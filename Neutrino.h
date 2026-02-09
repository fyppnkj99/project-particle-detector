// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the Neutrino class.

#ifndef NEUTRINO_H
#define NEUTRINO_H

#include "Particle.h"

class Neutrino : public Particle
{
public:
  Neutrino(int id = 0, double energy = 0.0);
  std::string get_type() const override { return "Neutrino"; }
  double get_charge() const override { return 0.0; }

protected:
  double get_mass() const override;
};

#endif // NEUTRINO_H