//
//  Controller.cpp
//  NeuroEvolution
//

#include "Controller.h"
#include "Parameters.h"
#include <iostream>
#include <unistd.h>

Controller::Controller(): m_NumCreatures(Parameters::iNumCreatures),
                          m_pGA(NULL),
                          m_iTicks(0),
                          m_iGenerations(0)
{
    //let's create the mine sweepers
    for (int i=0; i<m_NumCreatures; ++i)
    {
        creatures.push_back(Creature());
    }
    
    //get # of weights to initialize GA
    m_NumWeightsInNN = creatures[0].GetNumberOfWeights();
    
    //initialize the Genetic Algorithm class
    m_pGA = new GeneticAlgorithm(m_NumCreatures,
                                 Parameters::dMutationRate,
                                 Parameters::dCrossoverRate,
                                 m_NumWeightsInNN);
    
    //get the weights from the GA and insert into the sweepers brains
    m_vecThePopulation = m_pGA->GetChromos();
    
    for (int i=0; i<m_NumCreatures; i++)
        
        creatures[i].PutWeights(m_vecThePopulation[i].vecWeights);
}

//destructor
Controller::~Controller()
{
    if(m_pGA)
    {
        delete m_pGA;
    }
}

bool Controller::Update()
{
    
    if (m_iTicks++ < Parameters::iNumTicks)
    {
        for (int i=0; i<m_NumCreatures; ++i)
        {
            //update the NN and position
            if (!creatures[i].Update())
            {
                //error in processing the neural net
                throw std::invalid_argument("Error Processing Network");
                
                return false;
            }
            
            creatures[i].SetFitness(creatures[i].outputTestTotal);
            
            //update the chromos fitness score
            m_vecThePopulation[i].dFitness = creatures[i].Fitness();
            
        }
    }
    
    //another generation has been completed.
    //run the GA and update the creatures with their new NNs
    else
    {
        
        //increment the generation counter
        ++m_iGenerations;
        
        //reset cycles
        m_iTicks = 0;
        
        //run the GA to create a new population
        m_vecThePopulation = m_pGA->Epoch(m_vecThePopulation);
        
        //insert the new (hopefully)improved brains back into the sweepers
        //and reset their positions etc
        for (int i=0; i<m_NumCreatures; ++i)
        {
            creatures[i].PutWeights(m_vecThePopulation[i].vecWeights);
            
            creatures[i].Reset();
        }
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
    try {
        Controller c;
        while (c.m_iGenerations < 10)
        {
            c.Update();
            usleep(100);
        }
        
        cout << c.m_iGenerations << endl;
        
        return 0;
    } catch(runtime_error &e) {
        std::cout << "Length error :/";
    }
}


