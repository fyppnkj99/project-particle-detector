// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// MuonChamber class implementation

#include "MuonChamber.h"
#include <iostream>
#include <iomanip>

MuonChamber::MuonChamber(const std::string &mat, int num_units, const std::string &type, double eff, double res)
  : material(mat),
    units(num_units),
    chamber_type(type),
    gen(std::random_device{}()),
    dist(0.0, 1.0),
    uniform(0.0, 1.0)
{
  efficiency = eff;
  resolution = res;
}

void MuonChamber::set_characteristics(const std::string &mat, int layers_or_units)
{
  material = mat;
  units = layers_or_units;
}

double MuonChamber::detect_energy(const Particle &particle) const
{
  // Check if the particle is detected (based on efficiency)
  if (uniform(gen) > efficiency)
  {
    return 0.0; // Not detected
  }

  // Muon chambers detect muons
  if (particle.get_type() == "Muon")
  {
    double energy = particle.get_four_momentum().get_energy();
    double sigma = energy * resolution;                 // Standard deviation is energy × resolution
    double measured_energy = energy + dist(gen) * sigma;  // Apply Gaussian noise
    return std::max(0.0, measured_energy);               // Ensure energy is non-negative
  }
  return 0.0; // Other particles not detected
}

void MuonChamber::print_info() const
{
  std::cout << "MuonChamber (" << chamber_type << "): Material = " << material << ", Units = " << units
            << ", Efficiency = " << efficiency << ", Resolution = " << resolution << std::endl;
}