//
//  NeuralNetwork.h
//  NeuroEvolution
//

#ifndef NeuralNetwork_h
#define NeuralNetwork_h

#include <vector>
#include <math.h>

#include "Util.h"

using namespace std;

struct Neuron
{
    int m_NumInputs;
    
    vector<double>	m_vecWeight;
    
    Neuron(int NumInputs);
};

struct NeuronLayer
{
    int m_NumNeurons;
    
    vector<Neuron> m_vecNeurons;
    
    NeuronLayer(int NumNeurons, int NumInputsPerNeuron);
};

class NeuralNetwork
{
    
private:
    
    int m_NumInputs;
    
    int m_NumOutputs;
    
    int m_NumHiddenLayers;
    
    int m_NeuronsPerHiddenLyr;
    
    vector<NeuronLayer> m_vecLayers;
    
public:
    
    NeuralNetwork();
    
    void CreateNet();
    
    vector<double> GetWeights()const;
    
    int GetNumberOfWeights()const;
    
    void PutWeights(vector<double> &weights);
    
    vector<double> Update(vector<double> &inputs);
    
    inline double Sigmoid(double activation);
};

#endif /* NeuralNetwork_h */
