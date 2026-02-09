// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// Calorimeter class implementation

#include "Calorimeter.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>

// set default values for the calorimeter
Calorimeter::Calorimeter(const std::string &mat, int num_crystals, double eff, double res)
  : material(mat),
    crystals(num_crystals),
    efficiency(eff),
    resolution(res),
    gen(std::random_device{}()),
    dist(0.0, 1.0),
    uniform(0.0, 1.0)
{
}

void Calorimeter::set_characteristics(const std::string &mat, int layers_or_units)
{
  material = mat;
  crystals = layers_or_units;
}

// define the detectEnergy function
double Calorimeter::detect_energy(const Particle &particle) const
{
  // check if the particle is detected based on efficiency
  if (uniform(gen) > efficiency)
  {
    return 0.0; // no detection

    // initial energy
  }
  double energy = 0.0;
  if (particle.get_type() == "Photon" || particle.get_type() == "Electron")
  {
    energy = particle.get_four_momentum().get_energy();
  }
  else if (particle.get_type() == "Hadron")
  {
    energy = particle.get_four_momentum().get_energy() * 0.2; // 20% energy deposition for hadrons
  }

  // add Gaussian noise to the energy measurement
  if (energy > 0.0)
  {
    double sigma = energy * resolution;
    double measuredEnergy = energy + dist(gen) * sigma; // Gaussian noise
    return std::max(0.0, measuredEnergy);               // make sure energy is non-negative
  }
  return 0.0;
}

void Calorimeter::print_info() const
{
  std::cout << "Calorimeter: Material = " << material
            << ", Crystals = " << crystals
            << ", Efficiency = " << efficiency
            << ", Resolution = " << resolution
            << std::endl;
}