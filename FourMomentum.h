// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the FourMomentum class.

#ifndef FOUR_MOMENTUM_H
#define FOUR_MOMENTUM_H

class Four_Momentum
{
private:
  double energy;     // Energy component
  double px, py, pz; // Momentum components

public:
  Four_Momentum(double e = 0.0, double x = 0.0, double y = 0.0, double z = 0.0);
  double get_energy() const;
  double get_px() const;
  double get_py() const;
  double get_pz() const;
  void set_momentum(double e, double x, double y, double z);
};

#endif // FOUR_MOMENTUM_H