// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// Neutrino class implementation

#include "Neutrino.h"

Neutrino::Neutrino(int id, double energy)
  : Particle(id, energy)
{
}

double Neutrino::get_mass() const
{
  return 0.0001;
}