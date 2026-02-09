// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file implements the Particle class.

#include "Particle.h"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>

Particle::Particle(int id, double energy)
  : id(id), momentum(energy, 0.0, 0.0, 0.0)
{
}

void Particle::set_four_momentum(double energy, double px, double py, double pz)
{
  momentum.set_momentum(energy, px, py, pz);
  validate_energy_momentum();
}

void Particle::validate_energy_momentum() const
{
  double e = momentum.get_energy();
  double px = momentum.get_px(), py = momentum.get_py(), pz = momentum.get_pz();
  double p = std::sqrt(px * px + py * py + pz * pz);
  double mass = get_mass();
  double expected_energy = std::sqrt(p * p + mass * mass);
  double tolerance = 1e-6;

  if (std::abs(expected_energy - e) > tolerance)
  {
    throw std::runtime_error("Energy does not match momentum and mass for particle ID " +
                             std::to_string(id) + " (" + get_type() + "). Expected energy: " +
                             std::to_string(expected_energy) + " GeV, got: " + std::to_string(e) + " GeV.");
  }
}

void Particle::print_info() const
{
  std::cout << get_type() << ": ID = " << id << ", Charge = " << get_charge()
            << ", Energy = " << momentum.get_energy() << " GeV" << std::endl;
}