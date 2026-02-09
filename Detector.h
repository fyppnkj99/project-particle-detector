// PHYS 30762 Programming in C++
// Final Project
// Student ID: [11069686]
// Date: [09/05/2025]
// This file defines the Detector class and its functionalities.

#ifndef DETECTOR_H
#define DETECTOR_H

#include <string>
#include <vector>
#include <memory>
#include "SubDetector.h"
#include "Particle.h"

class Detector
{
private:
  std::string name;
  std::vector<std::unique_ptr<SubDetector>> subDetectors;

public:
  Detector(const std::string &detectorName);
  void add_sub_detector(std::unique_ptr<SubDetector> detector);
  double pass_particle(const Particle &particle);
  void print_configuration() const;

  // Template method to process particles
  template <typename particle_container>
  void process_particles(const particle_container &particles)
  {
    for (const auto &particle : particles)
    {
      pass_particle(*particle);
    }
  }
};

#endif // DETECTOR_H