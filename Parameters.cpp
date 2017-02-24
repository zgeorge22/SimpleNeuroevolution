//
//  Parameters.cpp
//  NeuroEvolution
//

#include "Parameters.h"

int Parameters::iFramesPerSecond       = 60;

int Parameters::iNumInputs             = 3;
int Parameters::iNumHidden             = 1;
int Parameters::iNeuronsPerHiddenLayer = 5;
int Parameters::iNumOutputs            = 2;
double Parameters::dBias               = -1;

int Parameters::iNumCreatures          = 10;
int Parameters::iNumTicks              = 5000;

double Parameters::dCrossoverRate      = 0.7;
double Parameters::dMutationRate       = 0.1;
double Parameters::dMaxPerturbation    = 0.3;
int Parameters::iNumElite              = 4;
int Parameters::iNumCopiesElite        = 1;
