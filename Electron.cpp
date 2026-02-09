// PHYS 30762 Programming in C++
// Final Project
// Student ID: 11069686
// Date: 09/05/2025
// Electron class implementation

#include "Electron.h"

Electron::Electron(int id, double energy)
  : Particle(id, energy)
{
}

double Electron::get_mass() const
{
  return 0.000511;
}
