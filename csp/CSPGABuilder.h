
#ifndef _CSP_GA_BUILDER_H_	
#define _CSP_GA_BUILDER_H_	

#include <csp/CSPProblem.h>
#include <ga/GeneticSolver.h>

//---------------------------------------------------------------------------
/**
 * A class that simplifies the task of creating a CSP GeneticSolver object.
 */
class CSPGABuilder
{
	public:
	CSPGABuilder();
	

	void setMutationProbability( double probability )
	{
		mutationProbability = probability;
	}

	void setUseFitnessScaling( bool use )
	{
		useFitnessScaling = use;
	}

	void setFitnessScalingFactor( double factor )
	{
		fitnessScalingFactor = factor;
	}

	void setPopulationSize( int _populationSize )
	{
		populationSize = _populationSize;
	}

	void setUseCI( bool use )
	{
		useCI = use;
	}

	void setUseCIQuickLoop( bool use )
	{
		useCIQuickLoop = use;
	}

	void setUseCIStrictFlip( bool use )
	{
		useCIStrictFlip = use;
	}

	void setUseCIPermutation( bool use )
	{
		useCIPermutation = use;
	}	

	void setElitist( bool _elitist )
	{
		elitist = _elitist;
	}

	GeneticSolver *createSolver( const CSPProblem *problem );

	private:
	double mutationProbability;
	bool   useFitnessScaling;
	double fitnessScalingFactor;
	int    populationSize;
	bool   useCI;
	bool   useCIQuickLoop;
	bool   useCIStrictFlip;
	bool   useCIPermutation;
	bool   elitist;
	
	
};
//---------------------------------------------------------------------------

#endif

