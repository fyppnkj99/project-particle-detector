// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// Hadron class implementation

#include "Hadron.h"

Hadron::Hadron(int id, double energy)
  : Particle(id, energy)
{
}

double Hadron::get_mass() const
{
  return 1.0;
}