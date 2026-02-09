// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// Muon class implementation

#include "Muon.h"

Muon::Muon(int id, double energy)
  : Particle(id, energy)
{
}

double Muon::get_mass() const
{
  return 0.106;
}