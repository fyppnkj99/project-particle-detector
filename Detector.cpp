// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the Detector class functionalities.

#include "Detector.h"
#include <iostream>
#include <iomanip>

Detector::Detector(const std::string &detectorName)
  : name(detectorName)
{
}

// function to add sub-detector with handling for duplicate types
// This function checks if a sub-detector of the same type already exists in the vector
void Detector::add_sub_detector(std::unique_ptr<SubDetector> detector)
{
  for (const auto &existing : subDetectors)
  {
    if (existing->get_type() == detector->get_type())
    {
      throw std::runtime_error("Detector type " + detector->get_type() + " already exists.");
    }
  }
  subDetectors.push_back(std::move(detector));
}

// Function to pass a particle through the detector and calculate detected energy
double Detector::pass_particle(const Particle &particle)
{
  std::cout << "Passing " << particle.get_type() << " (ID: " << particle.get_id()
            << ") through Simple-CMS detector:\n";
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "True Energy: " << particle.get_four_momentum().get_energy() << " GeV\n";

  double total_detected_energy = 0.0;
  bool has_detection = false;

  // Record detection status and energies for each sub-detector type
  bool tracker_hit = false;
  bool calo_hit = false;
  bool hcal_hit = false;
  bool muon_hit = false;
  double tracker_energy = 0.0;
  double calo_energy = 0.0;
  double hcal_energy = 0.0;
  double muon_energy_sum = 0.0;
  int muon_chamber_count = 0;

  // Detect energy from each sub-detector and record measurements
  for (const auto &detector : subDetectors)
  {
    double energy = detector->detect_energy(particle);
    std::cout << detector->get_type() << " detected energy: " << energy << " GeV\n";

    // Determine which type of sub-detector detected energy
    std::string detector_type = detector->get_type();
    if (detector_type == "Tracker" && energy > 0.0)
    {
      tracker_hit = true;
      has_detection = true;
      tracker_energy = energy;
    }
    else if (detector_type == "Calorimeter" && energy > 0.0)
    {
      calo_hit = true;
      has_detection = true;
      calo_energy = energy;
    }
    else if (detector_type == "HadronicCalorimeter" && energy > 0.0)
    {
      hcal_hit = true;
      has_detection = true;
      hcal_energy = energy;
    }
    else if (detector_type.find("MuonChamber") != std::string::npos && energy > 0.0)
    {
      muon_hit = true;
      has_detection = true;
      muon_energy_sum += energy;
      muon_chamber_count++;
    }
  }

  // Infer particle type based on detector hits
  std::string inferredType = "Unknown";
  if (!tracker_hit && !calo_hit && !hcal_hit && !muon_hit)
  {
    inferredType = "Neutrino"; // No hits, assume neutrino
  }
  else if (!tracker_hit && calo_hit && !hcal_hit && !muon_hit)
  {
    inferredType = "Photon"; // Only ECAL detected, assume photon
  }
  else if (tracker_hit && calo_hit && !hcal_hit && !muon_hit)
  {
    inferredType = "Electron"; // Tracker and ECAL detected, assume electron
  }
  else if ((tracker_hit || calo_hit) && hcal_hit && !muon_hit)
  {
    inferredType = "Hadron"; // ECAL and HCAL detected, Tracker optional, assume hadron
  }
  else if (tracker_hit && !calo_hit && !hcal_hit && muon_hit)
  {
    inferredType = "Muon"; // Tracker and MuonChamber detected, assume muon
  }

  // Calculate total detected energy based on inferred particle type
  if (inferredType == "Photon" || inferredType == "Electron")
  {
    total_detected_energy = calo_energy; // Use ECAL energy
  }
  else if (inferredType == "Hadron")
  {
    // Use HCAL energy primarily, add remaining ECAL energy if significant
    total_detected_energy = hcal_energy;
    if (calo_energy > 0.0)
    {
      total_detected_energy += calo_energy * 0.1; // Assume 10% of ECAL energy is not absorbed by HCAL
    }
  }
  else if (inferredType == "Muon")
  {
    // Use average of MuonChamber energies
    if (muon_chamber_count > 0)
    {
      total_detected_energy = muon_energy_sum / muon_chamber_count;
    }
  }
  else if (inferredType == "Neutrino")
  {
    total_detected_energy = 0.0;
  }
  else
  {
    // Fallback: Sum non-zero energies (avoid double-counting by prioritizing specific detectors)
    if (hcal_energy > 0.0)
    {
      total_detected_energy = hcal_energy;
      if (calo_energy > 0.0)
      {
        total_detected_energy += calo_energy * 0.1;
      }
    }
    else if (calo_energy > 0.0)
    {
      total_detected_energy = calo_energy;
    }
    else if (muon_energy_sum > 0.0 && muon_chamber_count > 0)
    {
      total_detected_energy = muon_energy_sum / muon_chamber_count;
    }
    else if (tracker_energy > 0.0)
    {
      total_detected_energy = tracker_energy;
    }
  }

  std::cout << "Inferred particle type: " << inferredType << "\n";
  std::cout << "Total detected energy: " << total_detected_energy << " GeV\n\n";

  return total_detected_energy;
}

void Detector::print_configuration() const
{
  std::cout << "\nDetector: " << name << "\nSub-detectors:\n";
  for (const auto &detector : subDetectors)
  {
    detector->print_info();
  }
}