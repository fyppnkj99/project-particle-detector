// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file implements the Photon class.

#include "Photon.h"

Photon::Photon(int id, double energy)
  : Particle(id, energy)
{
}

double Photon::get_mass() const
{
  return 0.0;
}