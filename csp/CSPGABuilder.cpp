
#include <csp/CSPGABuilder.h>
#include <csp/CSPGeneticOperators.h>
#include <csp/CSPChromossomeImprover.h>
#include <csp/CSPGeneticSolverExtraData.h>


//---------------------------------------------------------------------------
CSPGABuilder::CSPGABuilder()
{
	mutationProbability  = 0.01;
	useFitnessScaling    = true;
	fitnessScalingFactor = 2;
	populationSize       = 16;
	useCI                = true;
	useCIQuickLoop       = false;
	useCIStrictFlip      = false;
	useCIPermutation     = true;
	elitist              = false;
}
//---------------------------------------------------------------------------
GeneticSolver *CSPGABuilder::createSolver( const CSPProblem *_problem )
{
	CSPProblem *problem = _problem->clone();
	// store our copy
	CSPGeneticSolverExtraData *extraData = CSPGeneticSolverExtraData::create( problem );

	CSPFitnessEvaluator *fitnessEvaluator = CSPFitnessEvaluator::create();
	CSPGeneticOperators *geneticOperators = CSPGeneticOperators::create();	

	GeneticSolver *solver = GeneticSolver::create();
	solver->setExtraData( extraData );

	solver->setPopulationSize( populationSize );
	solver->setElitist( elitist );
	solver->setMaxFitnessScale( fitnessScalingFactor );
	solver->setScale( useFitnessScaling );

	fitnessEvaluator->setProblem( problem );

	geneticOperators->setMutationProbability( mutationProbability );
	geneticOperators->setProblem( problem );

	solver->setGeneticOperators( geneticOperators );
	solver->setFitnessEvaluator( fitnessEvaluator );

	if ( useCI )
	{	
		CSPChromossomeImprover *improver = CSPChromossomeImprover::create();
		improver->useQuickLoop( useCIQuickLoop );
		improver->changeOnStrictImprove( useCIStrictFlip );
		improver->usePermutation( useCIPermutation );
		improver->setProblem( problem );

		solver->setChromossomeImprover( improver );
	}

	return solver;
}
//---------------------------------------------------------------------------

