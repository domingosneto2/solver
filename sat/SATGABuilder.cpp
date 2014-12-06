
#include <sat/SATGABuilder.h>
#include <sat/CNFFitnessEvaluator.h>
#include <sat/CNFGeneticOperators.h>
#include <sat/CNFChromossomeImprover.h>


//---------------------------------------------------------------------------
SATGABuilder::SATGABuilder()
{
	mutationProbability  = 0.01;
	useFitnessScaling    = true;
	fitnessScalingFactor = 2;
	populationSize       = 16;
	useCI                = true;
	useCIQuickLoop       = false;
	useCIStrictFlip      = false;
	useCIPermutation     = true;
	improveFromCache     = false;
	elitist              = false;
}
//---------------------------------------------------------------------------
GeneticSolver *SATGABuilder::createSolver( const CNFFormula &formula )
{
	CNFFitnessEvaluator *fitnessEvaluator = CNFFitnessEvaluator::create();
	CNFGeneticOperators *geneticOperators = CNFGeneticOperators::create();	

	GeneticSolver *solver = GeneticSolver::create();

	solver->setPopulationSize( populationSize );
	solver->setElitist( elitist );
	solver->setMaxFitnessScale( fitnessScalingFactor );
	solver->setScale( useFitnessScaling );

	fitnessEvaluator->setFormula( formula );

	geneticOperators->setMutationProbability( mutationProbability );
	geneticOperators->setStringSize( formula.getNumVars() );

	solver->setGeneticOperators( geneticOperators );
	solver->setFitnessEvaluator( fitnessEvaluator );

	if ( useCI )
	{	
		CNFChromossomeImprover *improver = CNFChromossomeImprover::create();
		improver->useQuickLoop( useCIQuickLoop );
		improver->flipOnStrictImprove( useCIStrictFlip );
		improver->usePermutation( useCIPermutation );
		improver->setFormula( formula );
		improver->useCache( improveFromCache );

		solver->setChromossomeImprover( improver );
	}

	return solver;
}
//---------------------------------------------------------------------------

