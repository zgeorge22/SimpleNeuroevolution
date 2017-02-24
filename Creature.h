//
//  Creature.h
//  NeuroEvolution
//

#include <vector>
#include <math.h>

#include "NeuralNetwork.h"

using namespace std;


class Creature
{
    
private:
    
    NeuralNetwork net;
    
    double m_dFitness;

public:
    
    int outputTestTotal;
    
    Creature();
    
    //updates the ANN with information from the sweepers enviroment
    bool Update();

    void Reset();
    
    //-------------------accessor functions
    void SetFitness(double x){m_dFitness = x;}
    
    double Fitness()const{return m_dFitness;}
    
    void PutWeights(vector<double> &w){net.PutWeights(w);}
    
    int GetNumberOfWeights()const{return net.GetNumberOfWeights();}
};

/* Creature_h */
