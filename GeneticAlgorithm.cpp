//
//  GeneticAlgorithm.cpp
//  NeuroEvolution
//

#include "GeneticAlgorithm.h"
#include "Parameters.h"

GeneticAlgorithm::GeneticAlgorithm(int popsize,
                                   double MutRat,
                                   double CrossRat,
                                   int numweights) : m_iPopSize(popsize),
                                                     m_dMutationRate(MutRat),
                                                     m_dCrossoverRate(CrossRat),
                                                     m_iChromoLength(numweights),
                                                     m_dTotalFitness(0),
                                                     m_cGeneration(0),
                                                     m_iFittestGenome(0),
                                                     m_dBestFitness(0),
                                                     m_dWorstFitness(99999999),
                                                     m_dAverageFitness(0)
{
    for (int i=0; i<m_iPopSize; ++i)
    {
        m_vecPop.push_back(Genome());
        
        for (int j=0; j<m_iChromoLength; ++j)
        {
            m_vecPop[i].vecWeights.push_back(RandomClamped());
        }
    }
}

void GeneticAlgorithm::Mutate(vector<double> &chromo)
{
    for (int i=0; i<chromo.size(); ++i)
    {
        if (RandFloat() < m_dMutationRate)
        {
            chromo[i] += (RandomClamped() * Parameters::dMaxPerturbation);
        }
    }
}

Genome GeneticAlgorithm::GetChromoRoulette()
{
    double Slice = (double)(RandFloat() * m_dTotalFitness);
    
    Genome TheChosenOne;
    
    double FitnessSoFar = 0;
    
    for (int i=0; i<m_iPopSize; ++i)
    {
        FitnessSoFar += m_vecPop[i].dFitness;
        
        if (FitnessSoFar >= Slice)
        {
            TheChosenOne = m_vecPop[i];
            
            break;
        }
        
    }
    
    return TheChosenOne; // <---HarryPotter
}

void GeneticAlgorithm::Crossover(const vector<double> &mum,
                                 const vector<double> &dad,
                                 vector<double>       &baby1,
                                 vector<double>       &baby2)
{
    //just return parents as offspring dependent on the rate
    //or if parents are the same
    if ( (RandFloat() > m_dCrossoverRate) || (mum == dad))
    {
        baby1 = mum;
        baby2 = dad;
        
        return;
    }
    
    //determine a crossover point
    int cp = RandInt(0, m_iChromoLength - 1);
    
    //create the offspring
    for (int i=0; i<cp; ++i)
    {
        baby1.push_back(mum[i]);
        baby2.push_back(dad[i]);
    }
    
    for (int i=cp; i<mum.size(); ++i)
    {
        baby1.push_back(dad[i]);
        baby2.push_back(mum[i]);
    }
    
    
    return;
}

vector<Genome> GeneticAlgorithm::Epoch(vector<Genome> &old_pop)
{
    //assign the given population to the classes population
    m_vecPop = old_pop;
    
    //reset the appropriate variables
    Reset();
    
    //sort the population (for scaling and elitism)
    sort(m_vecPop.begin(), m_vecPop.end());
    
    //calculate best, worst, average and total fitness
    CalculateFitnessStats();
    
    //create a temporary vector to store new chromosones
    vector <Genome> vecNewPop;
    
    //Now to add a little elitism we shall add in some copies of the
    //fittest genomes. Make sure we add an EVEN number or the roulette
    //wheel sampling will crash
    if (!(Parameters::iNumCopiesElite * Parameters::iNumElite % 2))
    {
        GrabNBest(Parameters::iNumElite, Parameters::iNumCopiesElite, vecNewPop);
    }
    
    
    //now we enter the GA loop
    
    //repeat until a new population is generated
    while (vecNewPop.size() < m_iPopSize)
    {
        //grab two chromosones
        Genome mum = GetChromoRoulette();
        Genome dad = GetChromoRoulette();
        
        //create some offspring via crossover
        vector<double> baby1, baby2;
        
        Crossover(mum.vecWeights, dad.vecWeights, baby1, baby2);
        
        //now we mutate
        Mutate(baby1);
        Mutate(baby2);
        
        //now copy into vecNewPop population
        vecNewPop.push_back(Genome(baby1, 0));
        vecNewPop.push_back(Genome(baby2, 0));
    }
    
    //finished so assign new pop back into m_vecPop
    m_vecPop = vecNewPop;
    
    return m_vecPop;
}

//Eliteism: inserting NumCopies copies of the NBest most fittest genomes into a population vector
void GeneticAlgorithm::GrabNBest(int NBest,
                                 const int NumCopies,
                                 vector<Genome>	&Pop)
{
    //add the required amount of copies of the n most fittest
    //to the supplied vector
    while(NBest--)
    {
        for (int i=0; i<NumCopies; ++i)
        {
            Pop.push_back(m_vecPop[(m_iPopSize - 1) - NBest]);
        }
    }
}

//	calculates the fittest and weakest genome and the average/total fitness scores
void GeneticAlgorithm::CalculateFitnessStats()
{
    m_dTotalFitness = 0;
    
    double HighestSoFar = 0;
    double LowestSoFar  = 9999999;
    
    for (int i=0; i<m_iPopSize; ++i)
    {
        //update fittest if necessary
        if (m_vecPop[i].dFitness > HighestSoFar)
        {
            HighestSoFar = m_vecPop[i].dFitness;
            
            m_iFittestGenome = i;
            
            m_dBestFitness = HighestSoFar;
        }
        
        //update worst if necessary
        if (m_vecPop[i].dFitness < LowestSoFar)
        {
            LowestSoFar = m_vecPop[i].dFitness;
            
            m_dWorstFitness = LowestSoFar;
        }
        
        m_dTotalFitness	+= m_vecPop[i].dFitness;
        
        
    }//next chromo
    
    m_dAverageFitness = m_dTotalFitness / m_iPopSize;
}

//	resets all the relevant variables ready for a new generation
void GeneticAlgorithm::Reset()
{
    m_dTotalFitness		= 0;
    m_dBestFitness		= 0;
    m_dWorstFitness		= 9999999;
    m_dAverageFitness	= 0;
}
