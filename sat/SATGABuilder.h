
#ifndef _SAT_GA_BUILDER_H_
#define _SAT_GA_BUILDER_H_

#include <sat/CNFFormula.h>
#include <ga/GeneticSolver.h>

//---------------------------------------------------------------------------
/**
 * A class that simplifies the task of creating a SAT GeneticSolver object.
 */
class SATGABuilder
{
	public:
	SATGABuilder();
	

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

	void setImproveFromCache( bool _improveFromCache )
	{
		improveFromCache = _improveFromCache;
	}

	void setElitist( bool _elitist )
	{
		elitist = _elitist;
	}

	GeneticSolver *createSolver( const CNFFormula &formula );

	private:
	double mutationProbability;
	bool   useFitnessScaling;
	double fitnessScalingFactor;
	int    populationSize;
	bool   useCI;
	bool   useCIQuickLoop;
	bool   useCIStrictFlip;
	bool   useCIPermutation;
	bool   improveFromCache;
	bool   elitist;
	
	
};
//---------------------------------------------------------------------------

#endif

