
#ifndef _N_QUEENS_CSP_H_
#define _N_QUEENS_CSP_H_

#include <csp/CSPProblem.h>
#include <csp/Constraint.h>

//---------------------------------------------------------------------------
/**
 * This is a constraint of the N-Queens CSP problem.
 */
class NQueensCSPConstraint : public Constraint
{
	public:
	static NQueensCSPConstraint *create( CSPProblem *problem, int var1, int var2 );
	virtual void release();
	virtual Constraint *clone() const;

	virtual bool passes( int var1Value, int var2Value ) const;

	protected:
	NQueensCSPConstraint( CSPProblem *problem, int var1, int var2 );
	virtual ~NQueensCSPConstraint();

};
//---------------------------------------------------------------------------
/**
 * A factory that creates instances of the N-Queens CSP problem.
 * <p>
 * This class exists to hide the complexity of creating the CSP problem
 * and setting it's various initialization parameters.
 */
class NQueensCSPFactory
{
	public:
	static CSPProblem *create( int size, bool virtualConstraints = true );
};
//---------------------------------------------------------------------------

#endif

