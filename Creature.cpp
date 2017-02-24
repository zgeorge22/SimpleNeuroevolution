//
//  Creature.cpp
//  NeuroEvolution
//

#include "Creature.h"
#include "Parameters.h"
#include "Util.h"
#include <iostream>

Creature::Creature() : m_dFitness(0)
{
   //Constructor
}

void Creature::Reset()
{
    m_dFitness = 0;
    return;
}

bool Creature::Update()
{
    outputTestTotal = 0;
    
    //this will store all the inputs for the NN
    vector<double> inputs;
    
    //***CREATE INPUTS***
    inputs.push_back(0.6);
    inputs.push_back(0.7);
    inputs.push_back(0.8);
    
    //update the network and get feedback
    vector<double> output = net.Update(inputs);
    
//    for (int i = 0; i < output.size(); i++)
//        cout << output[i] << endl;
    
    //make sure there were no errors in calculating the output
    if (output.size() != Parameters::iNumOutputs)
    {
        return false;
    }
    
    //***USE OUTPUTS***

    
    
    return true;
}
