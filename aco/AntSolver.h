
#ifndef _ANT_SOLVER_H_
#define _ANT_SOLVER_H_

#include <csp/CSPProblem.h>
#include <aco/AntSolverGraph.h>

//---------------------------------------------------------------------------
class AntSolver
{
	public:
	AntSolver();
	~AntSolver();

	void setProblem( CSPProblem *problem );

	void setNumAnts( int numAnts );
	void setAlpha( double alpha );
	void setBeta( double beta );
	void setRo( double ro );
	void setUseLocalSearch( bool useLocalSearch );

	void setMinPheromone( double minPheromone );
	void setMaxPheromone( double maxPheromone );

	const CSPInterpretation &getResult();
	int getNumSteps();

	bool solve( int numSteps );

	private:
	int pickUninstantiatedVariable( const CSPInterpretation &interpretation, vector<int> &instantiatedVariables, vector<int> &consistentValues );
	int pickValue( const CSPInterpretation &interpretation, int variable, vector<int> &instantiatedVariables  );
	void layPheromone( const CSPInterpretation &interpretation );

	double getTrailFactor( int variable, int value, const CSPInterpretation &interpretation, vector<int> &instantiatedVariables );
	double getQualityFactor( int variable, int value, const CSPInterpretation &interpretation, vector<int> &instantiatedVariables );

	bool isConsistentValue( int variable, int value, const CSPInterpretation &interpretation, vector<int> &instantiatedVariables );
	void updateConsistentValuesVector( int lastInstantiatedVar, const CSPInterpretation &interpretation, vector<int> &consistentValues, vector <int> &instantiatedVariables );

	void init();

	void printPheromones( int step, int maxSatisfiedConstraints );

	CSPInterpretation result;

	CSPProblem *problem;
	int numAnts;
	double alpha;
	double beta;
	double ro;
	double minPheromone;
	double maxPheromone;
	bool   useLocalSearch;
	int stepsPerformed;

	AntSolverGraph graph;
	vector< vector< int > >variableConstraints;	
};
//---------------------------------------------------------------------------

#endif

