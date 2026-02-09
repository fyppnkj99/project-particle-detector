// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the Particle class.

#ifndef PARTICLE_H
#define PARTICLE_H

#include "FourMomentum.h"
#include <string>

class Particle
{
protected:
  int id;
  Four_Momentum momentum;

public:
  Particle(int id, double energy);
  virtual ~Particle() = default;
  virtual std::string get_type() const = 0;
  virtual int get_id() const { return id; }
  virtual double get_charge() const = 0;
  virtual const Four_Momentum &get_four_momentum() const { return momentum; }
  virtual void set_four_momentum(double energy, double px, double py, double pz);
  virtual void print_info() const;

protected:
  virtual double get_mass() const = 0;
  void validate_energy_momentum() const;
};

#endif // PARTICLE_H