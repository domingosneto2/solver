
#include <iostream>
#include <ga/GeneticSolver.h>
#include <csp/CSPProblem.h>
#include <csp/BasicCSP.h>
#include <csp/CSPGABuilder.h>
#include <csp/CrosswordsCSP.h>
#include <csp/NQueensCSP.h>
#include <csp/BasicCSPDomainList.h>
#include <util/Random.h>

//-----------------------------------------------------------------------------
/* Here we test our basic implementation of a Genetic CSP solver.
 */
static char *dictionary[] = { "add", "ado", "age", "aid", "and", "bag", "dau", "dog", "dug", "ear", "eft", "nao", "rat",
							  "lut", "fut", "fag", "fat", "lom", "sit", "dut", "fog", "luk", "sat", "sms", "xml", "rpc"
};
static int dictSize = 26;
static int wordlen = 3;

int testGeneticCSP( int argc, char **argv )
{
	// Initialize the random generator with a random seed
	Random::s_randomize();

	cout << "TestGeneticCSP" << endl;

	// Create the problem
	//CSPProblem *problem = CrosswordCSPFactory::createProblem( (const char **)dictionary, dictSize, wordlen );
	CSPProblem *problem = NQueensCSPFactory::create( 8 );

	cout << "O problema tem " << problem->getNumVars() << " variaveis e " << problem->getConstraintList()->getNumConstraints() << " constraints" << endl;

	// Run arc consistency over it
	if ( problem->arcConsistency() == false )
	{
		cout << "Arc consistency led us to find the problem has no solution" << endl;
		return 1;
	}

	double mutationProbability  = 0.01;
	int    populationSize       = 16;
	bool   useFitnessScaling    = true;
	double fitnessScalingFactor = 3;
	int nGenerations            = 200;
	bool elitist                = true;
	bool useChromossomeImprover = false;
	bool useCIQuickLoop         = false;
	bool useCIStrictFlip        = false;
	bool useCIPermutation       = true;

	// Setup the solver
	GeneticSolver *solver;

	CSPGABuilder builder;

	builder.setMutationProbability( mutationProbability );
	builder.setPopulationSize( populationSize );
	builder.setUseFitnessScaling( useFitnessScaling );
	builder.setFitnessScalingFactor( fitnessScalingFactor );
	builder.setUseCI( useChromossomeImprover );
	builder.setUseCIQuickLoop( useCIQuickLoop );
	builder.setUseCIStrictFlip( useCIStrictFlip );
	builder.setUseCIPermutation( useCIPermutation );

	solver = builder.createSolver( problem );	
	

	if ( solver->solve( nGenerations ) )
	{
		cout << "OK!" << endl;
		CSPInterpretation *interpretation = (CSPInterpretation *)solver->getResult();

		/*
		BasicCSPDomainList *domainList = (BasicCSPDomainList *)problem->getDomainList();

		for ( int i = 0; i < 3; i++ )
		{
			const CSPVariableDomain *domain = domainList->getDomain( i );
			BasicCSPVariableValue *value = (BasicCSPVariableValue *)domain->getValue( interpretation->getVariableValue( i ) );

			cout << dictionary[value->getValue()] << endl;
		}
		*/

		problem->release();
		solver->release();

		return 0;
	}
	else
	{
		cout << "Erro" << endl;
		cout << "MaxRawFitness apos " << nGenerations << " geracoes: " << solver->getMaxRawFitness() << endl;
		problem->release();
		solver->release();
		return 1;
	}
}

