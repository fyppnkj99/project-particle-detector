// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the SubDetector class.

#ifndef SUBDETECTOR_H
#define SUBDETECTOR_H

#include <string>
#include <random>
#include "Particle.h"

class SubDetector
{
public:
  virtual ~SubDetector() = default;

  // Get detector type
  virtual std::string get_type() const = 0;

  // Get material of detector
  virtual std::string get_material() const = 0;

  // Set detector properties
  virtual void set_characteristics(const std::string &material, int layers_or_units) = 0;

  // Detect energy of a particle
  virtual double detect_energy(const Particle &particle) const = 0;

  // Print detector configuration
  virtual void print_info() const = 0;

protected:
  double efficiency = 1.0;                                          // Default detection efficiency (100%)
  double resolution = 0.0;                                          // Default energy resolution (0%)
  mutable std::mt19937 gen{std::random_device{}()};                 // Random number generator
  mutable std::uniform_real_distribution<double> uniform{0.0, 1.0}; // Uniform distribution for efficiency check
  mutable std::normal_distribution<double> dist{0.0, 1.0};          // Normal distribution for energy resolution
};

#endif // SUBDETECTOR_H