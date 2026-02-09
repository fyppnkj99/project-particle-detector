// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file implements the Tracker class.

#include "Tracker.h"
#include <iostream>
#include <iomanip>

Tracker::Tracker(const std::string &mat, int num_layers, double eff, double res)
  : material(mat), layers(num_layers), gen(std::random_device{}()), dist(0.0, 1.0), uniform(0.0, 1.0)
{
  efficiency = eff;
  resolution = res;
}

void Tracker::set_characteristics(const std::string &mat, int layers_or_units)
{
  material = mat;
  layers = layers_or_units;
}

double Tracker::detect_energy(const Particle &particle) const
{
  // Tracker detects charged particles (electrons, muons, hadrons)
  if (uniform(gen) > efficiency)
  {
    return 0.0; // No detection
  }

  if (particle.get_charge() != 0.0)
  {
    double energy = particle.get_four_momentum().get_energy();
    double sigma = energy * resolution;
    double measured_energy = energy + dist(gen) * sigma; // Gaussian noise
    return std::max(0.0, measured_energy);               // Ensure energy is non-negative
  }
  return 0.0; // Neutral particles (e.g., photons) not detected
}

void Tracker::print_info() const
{
  std::cout << "Tracker: Material = " << material << ", Layers = " << layers
            << ", Efficiency = " << efficiency << ", Resolution = " << resolution << std::endl;
}