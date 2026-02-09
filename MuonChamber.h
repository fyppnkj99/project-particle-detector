// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the MuonChamber class.

#ifndef MUONCHAMBER_H
#define MUONCHAMBER_H

#include <string>
#include <random>
#include "SubDetector.h"

class MuonChamber : public SubDetector
{
private:
  std::string material;
  int units;
  std::string chamber_type; // DT or CSC
  mutable std::mt19937 gen;
  mutable std::normal_distribution<double> dist;
  mutable std::uniform_real_distribution<double> uniform;

public:
  MuonChamber(const std::string &mat = "drift tubes", int num_units = 250, const std::string &type = "DT",
              double eff = 0.99, double res = 0.05);
  std::string get_type() const override { return "MuonChamber_" + chamber_type; }
  std::string get_material() const override { return material; }
  void set_characteristics(const std::string &material, int layers_or_units) override;
  double detect_energy(const Particle &particle) const override;
  void print_info() const override;
};

#endif // MUONCHAMBER_H