
#include <iostream>
#pragma warning(disable: 4786)

#include <aco/AntSolverGraph.h>

//---------------------------------------------------------------------------
AntSolverGraph::AntSolverGraph()
{
}
//---------------------------------------------------------------------------
AntSolverGraph::~AntSolverGraph()
{
}
//---------------------------------------------------------------------------
void AntSolverGraph::init( double _minPheromone, double _maxPheromone, double _ro, const CSPProblem *problem )
{
	minPheromone = _minPheromone;
	maxPheromone = _maxPheromone;
	ro = _ro;

	numValues = 0;
	int numVars = problem->getNumVars();
	variableStart.resize( 0 );
	for ( int i = 0; i < numVars; i++ )
	{
		variableStart.push_back( numValues );
		numValues += problem->getDomainList()->getDomainSize( i );
	}

	pheromones.resize( numValues * numValues );
	for ( int j = 0; j < numValues * numValues; j++ )
	{
		pheromones[j] = maxPheromone;
	}
}
//---------------------------------------------------------------------------
double AntSolverGraph::getPheromone( int var1, int value1, int var2, int value2 )
{	
	// We always store the smaller variable first
	if ( var1 > var2 )
	{
		int aux = var1;
		var1 = var2;
		var2 = aux;

		aux = value1;
		value1 = value2;
		value2 = aux;
	}
	
	int x = variableStart[var1] + value1;
	int y = variableStart[var2] + value2;

	return pheromones[x * numValues + y];
}
//---------------------------------------------------------------------------
void AntSolverGraph::evaporate()
{
	for ( int i = 0; i < numValues * numValues; i++ )
	{
		pheromones[i] *= ro;		
		if ( pheromones[i] < minPheromone )
		{
			pheromones[i] = minPheromone;
		}
	}
	
}
//---------------------------------------------------------------------------
void AntSolverGraph::addPheromone( int var1, int value1, int var2, int value2, double pheromone )
{
	// If it is already in the graph we update.
	// Otherwise we insert
	// We always store the smaller variable first
	if ( var1 > var2 )
	{
		int aux = var1;
		var1 = var2;
		var2 = aux;

		aux = value1;
		value1 = value2;
		value2 = aux;
	}
	
	int x = variableStart[var1] + value1;
	int y = variableStart[var2] + value2;
	int index = x * numValues + y;

	pheromones[index] += pheromone;
	if ( pheromones[index] > maxPheromone )
	{
		pheromones[index] = maxPheromone;
	}
}
//---------------------------------------------------------------------------
void AntSolverGraph::getPheromoneMap( map< pair<int, int>, double> &pheromones )
{	
	/*
	AntSolverGraphMap::iterator it;
	it = theMap.begin();
	while ( it != theMap.end() )
	{
		double pheromone = it->second;
		double delta = pheromone - curCommonPheromone;

		int var1 = it->first.var1;
		int value1 = it->first.value1;

		int var2 = it->first.var2;
		int value2 = it->first.value2;

		pheromones[ make_pair( var1, value1 ) ] += delta;		
		pheromones[ make_pair( var2, value2 ) ] += delta;		

		it++;
	}
	*/
}
//---------------------------------------------------------------------------

