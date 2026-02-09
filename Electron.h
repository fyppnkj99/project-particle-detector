// PHYS 30762 Programming in C++
// Final Project
// Student ID: 11069686
// Date: 09/05/2025
// Electron.h - Header file for the Electron class

#ifndef ELECTRON_H
#define ELECTRON_H

#include "Particle.h"

class Electron : public Particle
{
public:
  Electron(int id = 0, double energy = 0.0);
  std::string get_type() const override { return "Electron"; }
  double get_charge() const override { return -1.0; }

protected:
  double get_mass() const override;
};

#endif // ELECTRON_H