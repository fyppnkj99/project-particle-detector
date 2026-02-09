// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the HadronicCalorimeter class.

#ifndef HADRONICCALORIMETER_H
#define HADRONICCALORIMETER_H

#include "SubDetector.h"
#include <random>

class Hadronic_Calorimeter : public SubDetector
{
private:
  std::string material;
  double depth;    // Depth of the calorimeter in cm
  double efficiency;    // Detection efficiency
  double resolution;    // Energy resolution
  mutable std::mt19937 gen;    // Random number generator
  mutable std::normal_distribution<double> dist;    // Normal distribution for energy resolution
  mutable std::uniform_real_distribution<double> uniform;    // Uniform distribution for efficiency check

public:
  Hadronic_Calorimeter(const std::string &mat = "copper and scintillator",
                       double d = 5.0,
                       double eff = 0.95,
                       double res = 0.10);
  std::string get_type() const override;
  std::string get_material() const override { return material; }
  void set_characteristics(const std::string &material, int layers_or_units) override;
  double detect_energy(const Particle &particle) const override;
  void print_info() const override;
};

#endif // HADRONICCALORIMETER_H