//
//  NeuralNetwork.cpp
//  NeuroEvolution
//

#include "NeuralNetwork.h"
#include "Parameters.h"
#include <iostream>

Neuron::Neuron(int NumInputs) : m_NumInputs(NumInputs+1)
{
    for (int i=0; i<NumInputs+1; ++i)
    {
        m_vecWeight.push_back(RandomClamped());
    }
}

NeuronLayer::NeuronLayer(int NumNeurons, int NumInputsPerNeuron) : m_NumNeurons(NumNeurons)
{
    for (int i=0; i<NumNeurons; ++i)
        
        m_vecNeurons.push_back(Neuron(NumInputsPerNeuron));
}

NeuralNetwork::NeuralNetwork()
{
    m_NumInputs	= Parameters::iNumInputs;
    m_NumOutputs = Parameters::iNumOutputs;
    m_NumHiddenLayers =	Parameters::iNumHidden;
    m_NeuronsPerHiddenLyr = Parameters::iNeuronsPerHiddenLayer;
    
    CreateNet();
}

void NeuralNetwork::CreateNet()
{
    //create the layers of the network
    if (m_NumHiddenLayers > 0)
    {
        //create first hidden layer
        m_vecLayers.push_back(NeuronLayer(m_NeuronsPerHiddenLyr, m_NumInputs));
        
        for (int i=0; i<m_NumHiddenLayers-1; ++i)
        {
            
            m_vecLayers.push_back(NeuronLayer(m_NeuronsPerHiddenLyr, m_NeuronsPerHiddenLyr));
        }
        
        //create output layer
        m_vecLayers.push_back(NeuronLayer(m_NumOutputs, m_NeuronsPerHiddenLyr));
    }
    
    else
    {
        //create output layer
        m_vecLayers.push_back(NeuronLayer(m_NumOutputs, m_NumInputs));
    }
}

vector<double> NeuralNetwork::GetWeights() const
{
    //this will hold the weights
    vector<double> weights;
    
    //for each layer
    for (int i=0; i<m_NumHiddenLayers + 1; ++i)
    {
        
        //for each neuron
        for (int j=0; j<m_vecLayers[i].m_NumNeurons; ++j)
        {
            //for each weight
            for (int k=0; k<m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k)
            {
                weights.push_back(m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k]);
            }
        }
    }
    
    return weights;
}

void NeuralNetwork::PutWeights(vector<double> &weights)
{
    int cWeight = 0;
    
    //for each layer
    for (int i=0; i<m_NumHiddenLayers + 1; ++i)
    {
        
        //for each neuron
        for (int j=0; j<m_vecLayers[i].m_NumNeurons; ++j)
        {
            //for each weight
            for (int k=0; k<m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k)
            {
                m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k] = weights[cWeight++];
            }
        }
    }
    
    return;
}

int NeuralNetwork::GetNumberOfWeights() const
{
    
    int weights = 0;
    
    //for each layer
    for (int i=0; i<m_NumHiddenLayers + 1; ++i)
    {
        
        //for each neuron
        for (int j=0; j<m_vecLayers[i].m_NumNeurons; ++j)
        {
            //for each weight
            for (int k=0; k<m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k)
                
                weights++;
            
        }
    }
    
    return weights;
}

vector<double> NeuralNetwork::Update(vector<double> &inputs)
{
    //stores the resultant outputs from each layer
    vector<double> outputs;
    
    int cWeight = 0;
    
    //first check that we have the correct amount of inputs
    if (inputs.size() != m_NumInputs)
    {
        //just return an empty vector if incorrect.
        throw std::invalid_argument("Incorrect # of Input Data");
        return outputs;
    }
    
    //For each layer....
    for (int i=0; i<m_NumHiddenLayers + 1; ++i)
    {
        if ( i > 0 )
        {
            inputs = outputs;
        }
        
        outputs.clear();
        
        cWeight = 0;
        
        //for each neuron sum the (inputs * corresponding weights).Throw
        //the total at our sigmoid function to get the output.
        for (int j=0; j<m_vecLayers[i].m_NumNeurons; ++j)
        {
            double netinput = 0;
            
            int	NumInputs = m_vecLayers[i].m_vecNeurons[j].m_NumInputs;
            
            //for each weight
            for (int k=0; k<NumInputs - 1; ++k)
            {
                //sum the weights x inputs
                netinput += m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k] * inputs[cWeight++];
                cout << "Weight: " << m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k] << endl;
            }
            
            netinput += m_vecLayers[i].m_vecNeurons[j].m_vecWeight[NumInputs-1] * (Parameters::dBias);
            cout << "Bias: "<<m_vecLayers[i].m_vecNeurons[j].m_vecWeight[NumInputs - 1] << endl;
            
            //activation function
            outputs.push_back(Sigmoid(netinput));
            
            cWeight = 0;
        }
    }
    
    for (int i = 0; i < outputs.size(); i++)
               cout << "OUTPUT: " << outputs[i] << endl;
    
    return outputs;
}

double NeuralNetwork::Sigmoid(double netinput)
{
    return ( 1 / ( 1 + exp(-netinput)));
}
