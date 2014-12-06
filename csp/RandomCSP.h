
#ifndef _RANDOM_CSP_H_
#define _RANDOM_CSP_H_

#include <set>
using namespace std;

#include <csp/Constraint.h>

//---------------------------------------------------------------------------
/**
 * 
 */
class RandomCSPConstraint : public Constraint
{
	public:
	static RandomCSPConstraint *create( CSPProblem *problem, int var1, int var2 );
	virtual void release();

	void addPair( int value1, int value2 );
	virtual bool passes( int var1Value, int var2Value ) const;
	virtual Constraint *clone() const;


	private:
	RandomCSPConstraint( CSPProblem *problem, int var1, int var2 );

	set< pair< int, int > >forbidden;
};

//---------------------------------------------------------------------------
/**
 *
 */
class RandomCSPFactory
{
	public:
	static CSPProblem *create( int n, int m, double p1, double p2, bool forceSatisfiable );

	private:
	static RandomCSPConstraint *createConstraint( CSPProblem *problem, int var1, int var2, int m, double p2, CSPInterpretation &interpretation, bool forceSatisfiable );
};
//---------------------------------------------------------------------------

#endif

