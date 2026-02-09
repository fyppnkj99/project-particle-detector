// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the Tracker class.

#ifndef TRACKER_H
#define TRACKER_H

#include <string>
#include <random>
#include "SubDetector.h"

class Tracker : public SubDetector
{
private:
  std::string material;
  int layers;
  mutable std::mt19937 gen;                          // Random number generator
  mutable std::normal_distribution<double> dist;     // Normal distribution for energy resolution
  mutable std::uniform_real_distribution<double> uniform; // Uniform distribution for efficiency check

public:
  Tracker(const std::string &mat = "silicon", int num_layers = 5, double eff = 0.99, double res = 0.01);
  std::string get_type() const override { return "Tracker"; }
  std::string get_material() const override { return material; }
  void set_characteristics(const std::string &material, int layers_or_units) override;
  double detect_energy(const Particle &particle) const override;
  void print_info() const override;
};

#endif // TRACKER_H