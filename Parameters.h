//
//  Parameters.h
//  NeuroEvolution
//

#ifndef Parameters_h
#define Parameters_h

class Parameters
{
    
public:
    
    //general parameters
    static int    iFramesPerSecond;
    
    //used for the neural network
    static int    iNumInputs;
    static int    iNumHidden;
    static int    iNeuronsPerHiddenLayer;
    static int    iNumOutputs;
    static double dBias;

    //controller parameters
    static int    iNumCreatures;
    static int    iNumTicks;
    
    //GA parameters
    static double dCrossoverRate;
    static double dMutationRate;
    static double dMaxPerturbation;
    static int    iNumElite;
    static int    iNumCopiesElite;
    
    Parameters()
    {
        //Constructor
    }
};


#endif /* Parameters_h */
