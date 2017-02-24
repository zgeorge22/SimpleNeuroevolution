//
//  Controller.h
//  NeuroEvolution
//

#include <vector>
#include <sstream>
#include <string>
#include <fstream>

#include "Creature.h"
#include "GeneticAlgorithm.h"
#include "NeuralNetwork.h"
#include "Util.h"

using namespace std;

class Controller
{
    
private:
    
    vector<Genome> m_vecThePopulation;
    
    vector<Creature> creatures;
    
    GeneticAlgorithm* m_pGA;
    
    int m_NumCreatures;
    
    int m_NumWeightsInNN;
    
    //stores the average fitness per generation for use in graphing
    vector<double> m_vecAvFitness;
    
    //stores the best fitness per generation
    vector<double> m_vecBestFitness;
    
    //cycles per generation
    int m_iTicks;
    
public:
    
    //generation counter
    int m_iGenerations;
    
    Controller();
    
    ~Controller();
    
    bool Update();
    
};

/* Controller_h */
