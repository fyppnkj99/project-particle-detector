[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/jNsaiKCH)

## Compilation Instructions

#### For macOS
Compile the program using the following command:
g++-11 -std=c++14 main.cpp Particle.cpp Electron.cpp Muon.cpp Photon.cpp Neutrino.cpp Hadron.cpp Tracker.cpp Calorimeter.cpp MuonChamber.cpp HadronicCalorimeter.cpp FourMomentum.cpp Detector.cpp -o detectors
#### For Windows
g++ -std=c++14 main.cpp Particle.cpp Electron.cpp Muon.cpp Photon.cpp Neutrino.cpp Hadron.cpp Tracker.cpp Calorimeter.cpp MuonChamber.cpp HadronicCalorimeter.cpp FourMomentum.cpp Detector.cpp -o detectors
#### Final step
./detectors
