
#ifndef _ANT_SOLVER_GRAPH_H_
#define _ANT_SOLVER_GRAPH_H_

#include <vector>
#include <map>
using namespace std;

#include <csp/CSPProblem.h>


//---------------------------------------------------------------------------
/**
 * A class that represents the ant solver graph.
 *
 */
class AntSolverGraph
{
	public:
	AntSolverGraph();
	~AntSolverGraph();

	void init( double minPheromone, double maxPheromone, double ro, const CSPProblem *problem );
	double getPheromone( int var1, int value1, int var2, int value2 );

	void addPheromone( int var1, int value1, int var2, int value2, double pheromone );

	void evaporate();

	void getPheromoneMap( map< pair<int, int>, double> &pheromones );

	private:
	double minPheromone;
	double maxPheromone;


	double ro;
	
	// the matrix with all pheromone values
	vector< double > pheromones;
	int numValues;
	vector< int > variableStart;
};
//---------------------------------------------------------------------------

#endif

