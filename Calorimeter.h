// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the Calorimeter class, which is a subclass of SubDetector.

#ifndef CALORIMETER_H
#define CALORIMETER_H

#include <string>
#include "SubDetector.h"
#include <random>  // For random number generation

class Calorimeter : public SubDetector
{
private:
  std::string material;
  int crystals;
  double efficiency;                                      // efficiency of energy detection
  double resolution;                                      // energy resolution
  mutable std::mt19937 gen;                               // random number generator
  mutable std::normal_distribution<double> dist;          // normal distribution for energy resolution
  mutable std::uniform_real_distribution<double> uniform; // uniform distribution for efficiency check

public:
  Calorimeter(const std::string &mat = "lead tungstate crystals", int num_crystals = 75000,
              double eff = 0.98, double res = 0.02);
  std::string get_type() const override { return "Calorimeter"; }
  std::string get_material() const override { return material; }
  void set_characteristics(const std::string &material, int layers_or_units) override;
  double detect_energy(const Particle &particle) const override;
  void print_info() const override;
};

#endif // CALORIMETER_H