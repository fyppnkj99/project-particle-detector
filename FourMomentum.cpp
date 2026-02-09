// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// FourMomentum class implementation

#include "FourMomentum.h"
#include <stdexcept>

Four_Momentum::Four_Momentum(double e, double x, double y, double z)
{
  if (e < 0)
    throw std::invalid_argument("Energy must be non-negative.");
  energy = e;
  px = x;
  py = y;
  pz = z;
}

double Four_Momentum::get_energy() const
{
  return energy;
}

double Four_Momentum::get_px() const
{
  return px;
}

double Four_Momentum::get_py() const
{
  return py;
}

double Four_Momentum::get_pz() const
{
  return pz;
}

void Four_Momentum::set_momentum(double e, double x, double y, double z)
{
  if (e < 0)
    throw std::invalid_argument("Energy must be non-negative.");
  energy = e;
  px = x;
  py = y;
  pz = z;
}