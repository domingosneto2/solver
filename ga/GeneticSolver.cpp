#include <stdlib.h>
#include <iostream>

#include <ga/GeneticSolver.h>
#include <util/Random.h>


//-----------------------------------------------------------------------------
/**
 * Constructor.
 */
Population::Population()
{
    // Here we don't initialize the values, we'll do it later.
	cur = NULL;
	next = NULL;
	improver = NULL;
	fitness = NULL;
	fitnessNext = NULL;
	result = NULL;
	overallBestIndividual = NULL;
	elitist = false;
}
//-----------------------------------------------------------------------------
/**
 * Destructor.
 */
Population::~Population()
{
    // Free allocated resources, if needed.
	release();
}
//-----------------------------------------------------------------------------
void Population::setPopulationSize( int _populationSize )
{
	populationSize = _populationSize;
}
//-----------------------------------------------------------------------------
void Population::setId( int _id )
{
	id = _id;
}
//-----------------------------------------------------------------------------
/**
 * Assign a fitness evaluator objet to this population.
 * We only keep a reference to the actual objet that is owned
 * by somebody else.
 */
void Population::setFitnessEvaluator( FitnessEvaluator *_evaluator )
{
    
	evaluator = _evaluator;
}
//-----------------------------------------------------------------------------
/**
 * Assign a chromossome improver objet to this population.
 * We only keep a reference to the actual objet that is owned
 * by somebody else.
 */
void Population::setChromossomeImprover( ChromossomeImprover *_improver )
{

	improver = _improver;
}
//-----------------------------------------------------------------------------
/**
 * Assign the genetic operators object to this population.
 * We only keep a reference to the actual objet that is owned
 * by somebody else.
 */
void Population::setGeneticOperators( GeneticOperators *_operators )
{
	operators = _operators;
}
//-----------------------------------------------------------------------------
/**
 * Informs wether we will use an elitist model.
 */
void Population::setElitist( bool _elitist )
{
	elitist = _elitist;
}
//-----------------------------------------------------------------------------
/**
 * Informs wether the algorithm should use fitness scaling or not.
 */
void Population::setScale( bool scale )
{
	bScale = scale;
}
//-----------------------------------------------------------------------------
/**
 * The max fitness scale tells how much the max fitness will differ
 * from the average fitness.  A value of 2, for instance, tells that
 * after the scaling the max fitness value will be twice the value
 * of the average fitness.
 */ 
void Population::setMaxFitnessScale( double scale )
{
	scaleFactor = scale;
}
//-----------------------------------------------------------------------------
/**
 * Allocates the population.  The actual allocation of each
 * individual is performed by the genetic operators object.
 */
void **Population::allocPopulation()
{
	// initialize the population vector.
	void **population = new void *[populationSize];
	
	// For each individual, asks the operators object to allocate it.
	for ( int i = 0; i < populationSize; i++ )
	{
		population[i] = operators->allocateIndividual();
	}

	return population;
}
//-----------------------------------------------------------------------------
/**
 * Randomly initializes a previously allocated population.
 *
 * The initialization is performed by the genetic operators object.
 */
void Population::initPopulation( void **population )
{
	for ( int i = 0; i < populationSize; i++ )
	{
		operators->initializeRandomIndividual( population[i] );
	}
}
//-----------------------------------------------------------------------------
/**
 * Given a fitness vector and a random value between zero and the sum
 * of all fitness values, this method returns the corresponding individual.
 */
int Population::pickIndividual( double *fitness, double random )
{
    // Variable that will accumulate the fitiness values.
	double sum = 0;

    // For each individual
	for ( int i = 0; i < populationSize; i++ )
	{
	    // Add it's fitness to the accumulator.
	    // It the sum passes the value, then we return
	    // the current index.
		sum += fitness[i];
		if ( sum > random )
		{
			return i;
		}
	}
    
    // We should never get here (really?), but in this case we just return zero.
	return 0;
}
//-----------------------------------------------------------------------------
/**
 * Uses the optional ChromossomeImprover object to perform a local
 * search on a given individual to improve it's fitness.
 */
void Population::improve ( void *individual )
{
	if ( improver != NULL )
	{
		improver->improve( individual );
	}
}
//-----------------------------------------------------------------------------
/**
 * Returns the result object, if any.
 *
 * This object is set when the algorithm finds a result.
 */
void *Population::getResult()
{
	return result;
}
//-----------------------------------------------------------------------------
/**
 * Releases a population.
 */
void Population::deletePopulation( void **pop )
{
	for ( int i = 0; i < populationSize; i++ )
	{
		operators->releaseIndividual( pop[i] );
	}
	delete[] pop;
}
//-----------------------------------------------------------------------------
/**
 * This function returns two scaling coefficients, a and b.  These coefficients
 * will apply the following transform to the fitness values:
 * newFitness = a * oldFitness + b
 *
 * Those values are calculated in such a way that when we apply the transformation
 * to the average fitness value it won change;  when we apply the transformation
 * to the maximum fitness value it the result will be scaleFactor * avgFitness,
 * and when we apply the transformation to the mininum fitness value it will never
 * be less than zero.
 */ 
void Population::getScalingCoefficients( double avgFitness, double maxFitness, double minFitness, double &a, double &b )
{
    // First we calculate how much the maximum and the
    // minimum fitness values differ from the average value.
	double updif    = maxFitness - avgFitness;
	double downdif  = avgFitness - minFitness;

    // This is the scaling factor
	double uMax = scaleFactor;

    // Now we will see if this tranformation will make the minimum fitness
    // drop below zero.  If it happen, we adjust the scale to avoid that pitfall.
	double scale = ( uMax - 1 ) * avgFitness / updif;

	if ( downdif * scale >= avgFitness )
	{
		scale = avgFitness / downdif;
		uMax = scale * updif / avgFitness + 1;
	}

    // Now we calculate the values of A and B
	b = ( uMax * avgFitness - maxFitness  ) / ( 1 - maxFitness / avgFitness );
	a = 1 - b / avgFitness;	
}
//-----------------------------------------------------------------------------
/**
 * Initializes the object.
 */
void Population::init()
{
    // Releases any previously allocated data.
    release();
    
	// initialize the populations, cur and next.
	// The cur population is randomly initialized.  We don't need to do that
	// with 'next'.
	cur = allocPopulation();
	initPopulation( cur );

	next = allocPopulation();

    // Allocates a vector for the fitness.
	fitness     = new double[populationSize];
	fitnessNext = new double[populationSize];
	
	curStep = 0;
	maxRawFitness = 0;

	// calculate the fitness of the allocated population and if we have
	// a result we set the indicating flag
	fitnessAcc = 0;
	maxFitness = 0;	

	// in the first generation we still don't have a way to evaluate individuals
	currentBestIndividual = previousBestIndividual = NULL;

	// Allocate space for the best individual
	overallBestIndividual = operators->allocateIndividual();

    // j will iterate through all individuals
	for ( int j = 0; j < populationSize; j++ )
	{
		// if this returs true we found a result
		if ( evaluateIndividualFitness( cur, fitness, j ) )
		{
			return;
		}
		updateStatistics( cur, fitness, j );
	}	
}
//-----------------------------------------------------------------------------
/**
 * Releases all allocated data.
 */
void Population::release()
{
	if ( cur != NULL )
	{
		deletePopulation( cur );
	}
	if ( next != NULL )
	{
		deletePopulation( next );
	}
	cur = next = NULL;
	if ( fitness != NULL )
	{
		delete[] fitness;
		fitness = NULL;
	}
	if ( result != NULL )
	{
	    operators->releaseIndividual( result );
	    result = NULL;
	}	
	if ( overallBestIndividual != NULL )
	{
		operators->releaseIndividual( overallBestIndividual );
		overallBestIndividual = NULL;
	}
}
//-----------------------------------------------------------------------------
bool Population::evaluateIndividualFitness( void **population, double *fitnessVector, int individual )
{
	int j = individual;

	// Evaluate the current individual fitness
	fitnessVector[j] = evaluator->evaluate( population[j] );
	
	// If this guy is the result of the problem, we return, but first
	// let's store the result.
	if ( evaluator->lastIsResult() )
	{
	    // Copy the result to a variable that will keep it after
	    // the function returns.
		result = operators->copyIndividual( population[j] );
		maxRawFitness = fitnessVector[j];
		return true;
	}

	// If we are using an elitist model we update the elitist individual
	// if we found a better one
	if ( elitist )
	{
		if ( currentBestIndividual == NULL )
		{
			currentBestIndividual = population[j];
			currentBestFitness = fitnessVector[j];
		}
		else if ( fitnessVector[j] > currentBestFitness )
		{
			currentBestIndividual = population[j];
			currentBestFitness = fitnessVector[j];
		}
	}	

	// Now we update the overall best individual if we found a better one.
	if ( fitnessVector[j] > overallBestFitness )
	{
		overallBestFitness = fitnessVector[j];
		operators->copyIndividual( population[j], overallBestIndividual );
	}

	return false;
}
//-----------------------------------------------------------------------------
/**
 * Returns a the best individual in the current population.
 *
 * The pointer returned doesn't return a copy but the actual individual,
 * therefore the caller should not release the pointer.
 *
 * Additionaly, the pointer could be no longer valid if the release
 * or step methods are called on this population.
 */
void *Population::getBestIndividual()
{
	return overallBestIndividual;
}
//-----------------------------------------------------------------------------
void Population::updateStatistics( void **pop, double *fitnessVector, int individual )
{
	int j = individual;

	// Accumulate the fitness of this individual
	fitnessAcc += fitnessVector[j];
	
	// Now we update the maximum fitness and the minimum fitness
	if ( maxFitness < fitnessVector[j] )
	{
		maxFitness = fitnessVector[j];
	}
	if ( j == 0 )
	{
		minFitness = fitnessVector[j];
	}
	else if ( minFitness > fitnessVector[j] )
	{
		minFitness = fitnessVector[j];
	}

    // The maxRawFitness holds the max fitness ever, while the maxFitness
    // holds the max fitness of this generation.  Let's update maxRawFitness
    // if necessary.
	if ( maxFitness > maxRawFitness )
	{
		maxRawFitness = maxFitness;
	}
}
//-----------------------------------------------------------------------------
/**
 * Here we do one step of the genetic algorithm loop.
 */
bool Population::step()
{
	// If we already have a result we don't perform any more steps
	if ( result != NULL )
	{
		return true;
	}	

    // Calculate the average fitness
	double avgFitness = (fitnessAcc/double(populationSize));
	
	// Print some debugging information
	cout << "Population " << id << endl;
	cout << "Generation " << curStep << endl;
	cout << "avgFitness " << avgFitness << endl;
	cout << "maxFitness " << maxFitness << endl;

    // Here we do the fitness scaling if we were configured to do so.
	if ( bScale )
	{
	    // Calculate the transformation coefficients
		double a;
		double b;
		getScalingCoefficients( avgFitness, maxFitness, minFitness, a, b );

        // Apply the transformation to each previously calculated
        // fitness.
		fitnessAcc = 0;
		for ( int j3 = 0; j3 < populationSize; j3++ )
		{
			fitness[j3] = a * fitness[j3] + b;
			if ( fitness[j3] < 0 )
			{
				fitness[j3] = 0;
			}

			fitnessAcc += fitness[j3];
		}
	}	

	// Perform the crossover.
	// Each individual is picked for crossover with a probability
	// that is proportional to it's fitness
	// j2 will iterate through each individual in the new generation.
	double previousFitnessAcc = fitnessAcc;
	fitnessAcc = 0;
	maxFitness = 0;		
	currentBestIndividual = NULL;
	for ( int j2 = 0; j2 < populationSize; j2 += 2 )
	{	
	    // Two random variables that will chose two parents for this new individual.
		double random1 = ( Random::s_generateUnitUniformVariable() ) * previousFitnessAcc;
		double random2 = ( Random::s_generateUnitUniformVariable() ) * previousFitnessAcc;
		
		// Pick the individuals, based on the probability they have.
		// Individuals with grater fitness are picked with a greater probability.
		int individual1 = pickIndividual( fitness, random1 );
		int individual2 = pickIndividual( fitness, random2 );

		// We perform the crossover operation on the parents and store
		// in the resultin individuals
		operators->crossover( cur[individual1], cur[individual2], next[j2], next[j2 + 1] );

		// Mutate these individuals with a given probability.
		operators->mutate( next[j2] );
		operators->mutate( next[j2+1] );
		
		// Call the improve function, that will perform the local search on this
		// individual IF NEEDED.
		improve( next[j2] );
		improve( next[j2+1] );

		// Update fitness value
		if ( evaluateIndividualFitness( next, fitnessNext, j2 ) )
		{
			return true;
		}
		// Update fitness value
		if ( evaluateIndividualFitness( next, fitnessNext, j2 + 1 ) )
		{
			return true;		
		}

		updateStatistics( next, fitnessNext, j2 );

		// If we are at the last pair of individuals and we choosed to use an elitist model...
		if ( j2 == populationSize - 2 && elitist == true )
		{
			// If this generation doesn't have a better individual than the best
			// of the previous generation... we will copy the previous best here
			if ( previousBestIndividual != NULL )
			{
				if ( previousBestFitness > currentBestFitness )
				{
					operators->copyIndividual( previousBestIndividual, next[j2 + 1] );
					fitnessNext[j2 + 1] = previousBestFitness;
				}			
			}
		}
		
		updateStatistics( next, fitnessNext, j2 + 1 );
	}

    // Swap the populations.  The next population now is the current and the current
    // is no longer needed so it will be used in the next iteration to store the next population.
	void **aux = next;
	next = cur;
	cur = aux;
	curStep++;

	// Swap the fitness vectors
	double*auxf = fitnessNext;
	fitnessNext = fitness;
	fitness = auxf;

	if ( elitist )
	{
		previousBestIndividual = currentBestIndividual;
		previousBestFitness = currentBestFitness;
	}

    // Returns false indicating that we haven't found the results yet.
	return false;
}
//-----------------------------------------------------------------------------
/**
 * Returns the maximum RAW fitness of all iterations.
 * 
 * The maximum raw fitness is the maximum fitness before the
 * scaling is applied.
 */
double Population::getMaxRawFitness()
{
	return maxRawFitness;
}
//-----------------------------------------------------------------------------
GeneticSolver *GeneticSolver::create()
{
	return new GeneticSolver();
}
//-----------------------------------------------------------------------------
void GeneticSolver::release()
{
	delete this;
}
//-----------------------------------------------------------------------------
/**
 * Creates a generic genetic solver.
 */
GeneticSolver::GeneticSolver()
{
	result         = NULL;
	improver       = NULL;
	evaluator      = NULL;
	operators      = NULL;
	extraData      = NULL;
	bestIndividual = NULL;

	numPopulations = 1;
	elitist = false;
	bScale = false;
}
//-----------------------------------------------------------------------------
/**
 * Releases the generic genetic solver.
 */
GeneticSolver::~GeneticSolver()
{
	if ( result )
	{
		operators->releaseIndividual( result );
	}

	if ( bestIndividual )
	{
		operators->releaseIndividual( bestIndividual );
	}

	if ( improver ) improver->release();
	if ( evaluator ) evaluator->release();
	if ( operators ) operators->release();
	if ( extraData ) extraData->release();

}
//-----------------------------------------------------------------------------
/** 
 * Sets the number of populations.  Usually it's just one,
 * you may set a higher value if you want multiple populations
 * running at the same time.
 *
 */
void GeneticSolver::setNumPopulations( int _numPopulations )
{
	numPopulations = _numPopulations;
}
//-----------------------------------------------------------------------------
/**
 * Sets the size (number of individuals) of each population.
 * 
 */
void GeneticSolver::setPopulationSize( int _populationSize )
{
	populationSize = _populationSize;
	if ( populationSize % 2 != 0 )
	{
		populationSize++;
	}
}
//-----------------------------------------------------------------------------
/**
 * Sets the fitness evaluator object for a specific GA.
 *
 * The ownership of the object passed as parameter will belong to this class,
 * and when the GeneticSolver object is destroyed it will call the delete()
 * method on this object.
 */
void GeneticSolver::setFitnessEvaluator( FitnessEvaluator *_evaluator )
{
	if ( evaluator != NULL )
	{
		evaluator->release();
	}

	evaluator = _evaluator;
}
//-----------------------------------------------------------------------------
/**
 * Sets the chromossome improver object for a specific GA.
 *
 * This object is not required.  If it is not set, the algorithm
 * won't apply the improving method for each individual.
 *
 * The ownership of the object passed as parameter will belong to this class,
 * and when the GeneticSolver object is destroyed it will call the delete()
 * method on this object.
 */
void GeneticSolver::setChromossomeImprover( ChromossomeImprover *_improver )
{
	if ( improver != NULL )
	{
		improver->release();
	}

	improver = _improver;
}
//-----------------------------------------------------------------------------
/**
 * Sets the GeneticOperatos object for a specific GA.
 *
 * The ownership of the object passed as parameter will belong to this class,
 * and when the GeneticSolver object is destroyed it will call the release()
 * method on this object.
 */
void GeneticSolver::setGeneticOperators( GeneticOperators *_operators )
{
	if ( operators != NULL )
	{
		operators->release();
	}
	operators = _operators;
}
//-----------------------------------------------------------------------------
void GeneticSolver::setExtraData( GeneticSolverExtraData *_extraData )
{
	if ( extraData != NULL )
	{
		extraData->release();
	}

	extraData = _extraData;
}
//-----------------------------------------------------------------------------
GeneticSolverExtraData *GeneticSolver::getExtraData()
{
	return extraData;
}
//-----------------------------------------------------------------------------
/**
 * This is the main function of the genetic algorithm.  It returns
 * true if we found a solution and false otherwise.
 */
bool GeneticSolver::solve( int maxGenerations )
{
    // Create the required number of populations.
	int k;
	Population *pop = new Population[numPopulations];

    // If the algorithm was run before, there may be a result
    // individual.  Let's delete it.
	if ( result )
	{
		operators->releaseIndividual( result );
		result = NULL;
	}

	// There may also be already a 'best individual'.  Delete it.
	if ( bestIndividual )
	{
		operators->releaseIndividual( bestIndividual );
		bestIndividual = NULL;
	}

    // Now we initialize the populations, setting various
    // required properties.
	for ( int i = 0; i < numPopulations; i++ )
	{
		pop[i].setId( i );
		pop[i].setPopulationSize( populationSize );
		pop[i].setFitnessEvaluator( evaluator );
		pop[i].setChromossomeImprover( improver );
		pop[i].setGeneticOperators( operators );
		pop[i].setScale( bScale );
		pop[i].setMaxFitnessScale( scaleFactor );
		pop[i].setElitist( elitist );

		pop[i].init();
	}

    // For each generation, we perform the genetic algorithm iteration.
	for ( k = 0; k < maxGenerations; k++ )
	{
	    // Run it separetely on each population.
		for ( int j = 0; j < numPopulations; j++ )
		{
		    // Do a step on this population.
		    // If this function returns true we found
		    // the result
			if ( pop[j].step() )
			{
			    // Cool, we found the result!
				result = operators->copyIndividual( pop[j].getResult() );
				numSteps = k;
				bestIndividual = operators->copyIndividual( pop[j].getResult() );
				maxRawFitness = pop[j].getMaxRawFitness();
				delete[] pop;
				return true;
			}
		}
	}
	
	// Too bad we couldn't find the result, let's tell that to the user.
	// But first let's calculate the best fitness we could find.
	retrieveOverallBestIndividual( pop );
	

	numSteps = k;
	delete[] pop;
	return false;
}
//-----------------------------------------------------------------------------
/**
 * Retrieves and stores the overall best individual.
 *
 * Additionaly, this function also retrieves the max raw fitness.
 */
void GeneticSolver::retrieveOverallBestIndividual( Population *pop )
{
	maxRawFitness = 0;		
	for ( int j = 0; j < numPopulations; j++ )
	{
		double populationMaxFitness = pop[j].getMaxRawFitness();

		if ( populationMaxFitness > maxRawFitness )
		{
			maxRawFitness = populationMaxFitness;
			bestIndividual = operators->copyIndividual( pop[j].getBestIndividual() );
		}
	}
}
//-----------------------------------------------------------------------------
/**
 * Returns the result if the run was successfull.
 */
void *GeneticSolver::getResult()
{
	return result;
}
//-----------------------------------------------------------------------------
/**
 * Sets a flag that indicates wether you want to use fitness scaling.
 */
void GeneticSolver::setScale( bool scale )
{
	bScale = scale;
}
//-----------------------------------------------------------------------------
/**
 * The max fitness scale tells how much the max fitness will differ
 * from the average fitness.  A value of 2, for instance, indicates that
 * after the scaling the max fitness value will be twice as big as the value
 * of the average fitness.
 */ 
void GeneticSolver::setMaxFitnessScale( double scale )
{
	scaleFactor = scale;
}
//-----------------------------------------------------------------------------
/**
 * The number of executed steps.
 */
int GeneticSolver::getNumSteps()
{
	return numSteps;
}
//-----------------------------------------------------------------------------
/**
 * The maximum raw fitness.
 *
 * The maximum raw fitness is the maximum fitness before the
 * scaling is applied.
 */
double GeneticSolver::getMaxRawFitness()
{
	return maxRawFitness;
}
//-----------------------------------------------------------------------------
/**
 * If true, this is going to be an elitist GA, that is, a GA that always
 * keeps one copy of the best individual.
 */
void GeneticSolver::setElitist( bool _elitist )
{
	elitist = _elitist;
}
//-----------------------------------------------------------------------------
void *GeneticSolver::getBestIndividual()
{
	return bestIndividual;
}
//-----------------------------------------------------------------------------
