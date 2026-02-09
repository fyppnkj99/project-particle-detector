// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the Photon class.

#ifndef PHOTON_H
#define PHOTON_H

#include "Particle.h"

class Photon : public Particle
{
public:
  Photon(int id = 0, double energy = 0.0);
  std::string get_type() const override { return "Photon"; }
  double get_charge() const override { return 0.0; }

protected:
  double get_mass() const override;
};

#endif // PHOTON_H