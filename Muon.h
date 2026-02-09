// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the Muon class.

#ifndef MUON_H
#define MUON_H

#include "Particle.h"

class Muon : public Particle
{
public:
  Muon(int id = 0, double energy = 0.0);
  std::string get_type() const override { return "Muon"; }
  double get_charge() const override { return -1.0; }

protected:
  double get_mass() const override;
};

#endif // MUON_H