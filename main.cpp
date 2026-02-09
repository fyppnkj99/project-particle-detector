// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// Main function for particle detector simulation

#include "Photon.h"
#include "Detector.h"
#include "Tracker.h"
#include "Calorimeter.h"
#include "HadronicCalorimeter.h"
#include "MuonChamber.h"
#include "Muon.h"
#include "Neutrino.h"
#include "Hadron.h"
#include "Electron.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <set>
#include <limits>
#include <algorithm>
#include <cctype>

int main()
{
  Detector cmsDetector("Simple-CMS");

  try
  {
    cmsDetector.add_sub_detector(std::make_unique<Tracker>("silicon", 5, 0.99, 0.01));
    cmsDetector.add_sub_detector(std::make_unique<Calorimeter>("lead tungstate crystals", 75000, 0.98, 0.02));
    cmsDetector.add_sub_detector(std::make_unique<Hadronic_Calorimeter>("copper and scintillator", 5.0, 0.95, 0.10));
    cmsDetector.add_sub_detector(std::make_unique<MuonChamber>("drift tubes", 250, "DT", 0.99, 0.05));
    cmsDetector.add_sub_detector(std::make_unique<MuonChamber>("cathode strip chambers", 540, "CSC", 0.99, 0.05));
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  // Produce a file to store the summary simulation results
  std::ofstream outFile("simulation_results.txt");
  std::cout << "\nDetector Configuration:\n";
  outFile << "Detector Configuration:\n";
  cmsDetector.print_configuration();

  std::vector<std::unique_ptr<Particle>> particles;
  std::set<int> usedIDs;
  // Add interactive input for user
  std::cout << "\nWould you like to input particle parameters manually? (Y/N)(Typing N/n for defalt test cases): ";
  std::string choice;
  std::cin >> choice;

  if (choice == "Y" || choice == "y")
  {
    std::cout << "Enter particle parameters (type id energy px py pz). Supported types: Photon, Neutrino, Hadron, Muon, Electron.\n";
    std::cout << "Type 'done' to finish input.\n";

    while (true)
    {
      std::string particle_type;
      std::cout << "Particle type (or 'done' to finish): ";
      std::cin >> particle_type;

      if (particle_type == "done")
        break;

      try
      {
        std::string particle_type_lower = particle_type;
        std::transform(particle_type_lower.begin(), particle_type_lower.end(),
                       particle_type_lower.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        if (particle_type_lower != "photon" && particle_type_lower != "neutrino" &&
            particle_type_lower != "hadron" && particle_type_lower != "muon" && particle_type_lower != "electron")
        {
          throw std::runtime_error("Invalid particle type. Supported types: Photon, Neutrino, Hadron, Muon, Electron.");
        }

        if (particle_type_lower == "photon")
          particle_type = "Photon";
        else if (particle_type_lower == "neutrino")
          particle_type = "Neutrino";
        else if (particle_type_lower == "hadron")
          particle_type = "Hadron";
        else if (particle_type_lower == "muon")
          particle_type = "Muon";
        else if (particle_type_lower == "electron")
          particle_type = "Electron";

        int id;
        std::cout << "ID (positive integer): ";
        if (!(std::cin >> id) || id <= 0 || std::floor(id) != id)
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          throw std::runtime_error("Invalid ID. Must be a positive integer.");
        }
        if (usedIDs.count(id) > 0)
        {
          throw std::runtime_error("ID " + std::to_string(id) + " already exists. Use a unique ID.");
        }

        double energy, px, py, pz;
        std::cout << "Energy (GeV): "; // Removed "positive" as FourMomentum checks this
        if (!(std::cin >> energy))
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          throw std::runtime_error("Invalid energy. Must be a number.");
        }

        std::cout << "Momentum px (GeV): ";
        if (!(std::cin >> px))
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          throw std::runtime_error("Invalid px. Must be a number.");
        }

        std::cout << "Momentum py (GeV): ";
        if (!(std::cin >> py))
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          throw std::runtime_error("Invalid py. Must be a number.");
        }

        std::cout << "Momentum pz (GeV): ";
        if (!(std::cin >> pz))
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          throw std::runtime_error("Invalid pz. Must be a number.");
        }

        std::unique_ptr<Particle> particle;
        if (particle_type == "Photon")
        {
          particle = std::make_unique<Photon>(id, energy);
        }
        else if (particle_type == "Neutrino")
        {
          particle = std::make_unique<Neutrino>(id, energy);
        }
        else if (particle_type == "Hadron")
        {
          particle = std::make_unique<Hadron>(id, energy);
        }
        else if (particle_type == "Muon")
        {
          particle = std::make_unique<Muon>(id, energy);
        }
        else if (particle_type == "Electron")
        {
          particle = std::make_unique<Electron>(id, energy);
        }

        particle->set_four_momentum(energy, px, py, pz); // Validation handled by Particle
        usedIDs.insert(id);
        particles.push_back(std::move(particle));
        std::cout << "Particle added successfully!\n";
      }
      catch (const std::runtime_error &e)
      {
        std::cerr << "Error: " << e.what() << "\n";
        std::cout << "Please try again.\n";
      }
    }
  }
  else
  {
    try // Default test cases
    {
      // Photon: E = 60 GeV
      particles.push_back(std::make_unique<Photon>(1, 60.0));
      particles.back()->set_four_momentum(60.0, 60.0 / std::sqrt(2), 60.0 / std::sqrt(2), 0.0);
      usedIDs.insert(1);

      // Electron: E = 65 GeV
      particles.push_back(std::make_unique<Electron>(2, 65.0));
      double pElectron = std::sqrt(65.0 * 65.0 - 0.000511 * 0.000511);
      particles.back()->set_four_momentum(65.0, pElectron / std::sqrt(2), pElectron / std::sqrt(2), 0.0);
      usedIDs.insert(2);

      // Neutrino: E = 30 GeV
      particles.push_back(std::make_unique<Neutrino>(3, 30.0));
      particles.back()->set_four_momentum(30.0, 30.0 / std::sqrt(2), 30.0 / std::sqrt(2), 0.0);
      usedIDs.insert(3);

      // Hadron: E = 50 GeV
      particles.push_back(std::make_unique<Hadron>(4, 50.0));
      double pHadron = std::sqrt(50.0 * 50.0 - 1.0 * 1.0);
      particles.back()->set_four_momentum(50.0, pHadron / std::sqrt(2), pHadron / std::sqrt(2), 0.0);
      usedIDs.insert(4);

      // Muon: E = 40 GeV
      particles.push_back(std::make_unique<Muon>(5, 40.0));
      double pMuon = std::sqrt(40.0 * 40.0 - 0.106 * 0.106);
      particles.back()->set_four_momentum(40.0, pMuon / std::sqrt(2), pMuon / std::sqrt(2), 0.0);
      usedIDs.insert(5);
    }
    catch (const std::runtime_error &e)
    {
      std::cerr << "Error in default particles: " << e.what() << std::endl;
      return 1;
    }
  }
  // Print simulation results
  std::cout << "\nSimulating particle interactions:\n";
  outFile << "\nSimulating particle interactions:\n";
  double total_true_energy = 0.0;
  double total_detected_energy = 0.0;
  double pxSum = 0.0, pySum = 0.0;

  for (const auto &particle : particles)
  {
    total_true_energy += particle->get_four_momentum().get_energy();
    double detected_energy = cmsDetector.pass_particle(*particle);
    total_detected_energy += detected_energy;
    pxSum += particle->get_four_momentum().get_px();
    pySum += particle->get_four_momentum().get_py();
  }

  double invisible_energy = total_true_energy - total_detected_energy;
  double met = std::sqrt(pxSum * pxSum + pySum * pySum);

  std::cout << std::fixed << std::setprecision(2);
  outFile << std::fixed << std::setprecision(2);
  std::cout << "\nSummary:\n";
  outFile << "\nSummary:\n";
  std::cout << "Total true energy: " << total_true_energy << " GeV\n";
  outFile << "Total true energy: " << total_true_energy << " GeV\n";
  std::cout << "Total detected energy: " << total_detected_energy << " GeV\n";
  outFile << "Total detected energy: " << total_detected_energy << " GeV\n";
  std::cout << "Invisible energy: " << invisible_energy << " GeV\n";
  outFile << "Invisible energy: " << invisible_energy << " GeV\n";
  std::cout << "Missing Transverse Energy (MET): " << met << " GeV\n";
  outFile << "Missing Transverse Energy (MET): " << met << " GeV\n";

  outFile.close();
  return 0;
}