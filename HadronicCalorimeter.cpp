// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// HadronicCalorimeter class implementation

#include "HadronicCalorimeter.h"
#include <iostream>
#include <iomanip>

Hadronic_Calorimeter::Hadronic_Calorimeter(const std::string &mat, double d, double eff, double res)
  : material(mat),
    depth(d),
    efficiency(eff),
    resolution(res),
    gen(std::random_device{}()),
    dist(0.0, 1.0),
    uniform(0.0, 1.0)
{
}

void Hadronic_Calorimeter::set_characteristics(const std::string &mat, int layers_or_units)
{
  material = mat;
  depth = layers_or_units; // Assuming layers_or_units is depth in cm
}

std::string Hadronic_Calorimeter::get_type() const
{
  return "HadronicCalorimeter";
}

double Hadronic_Calorimeter::detect_energy(const Particle &particle) const
{
  // Check if the particle is detected based on efficiency
  if (uniform(gen) > efficiency)
  {
    return 0.0; // No detection
  }

  // Initial energy
  double energy = 0.0;
  if (particle.get_type() == "Hadron")
  {
    energy = particle.get_four_momentum().get_energy() * 0.8; // 80% energy deposition
  }

  // Add Gaussian noise to the energy measurement
  if (energy > 0.0)
  {
    double sigma = energy * resolution;
    double measured_energy = energy + dist(gen) * sigma; // Gaussian noise
    return std::max(0.0, measured_energy); // Make sure energy is non-negative
  }
  return 0.0;
}

void Hadronic_Calorimeter::print_info() const
{
  std::cout << "HadronicCalorimeter: Material = " << material << ", Depth = " << depth
            << ", Efficiency = " << efficiency << ", Resolution = " << resolution << std::endl;
}
