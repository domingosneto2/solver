
#ifndef _CONSTRAINT_H_
#define _CONSTRAINT_H_

#include <csp/CSPInterpretation.h>

class CSPProblem;
//---------------------------------------------------------------------------
/**
 * A Constraint of a CSP.
 *
 * This is an abstract class that implements a constraint of a CSP problem.
 *
 * In order to solve specific CSP problems you have to subclass this class,
 * implementing the virtual methods <code>passes()</code> and <code>clone</code>.
 */
class Constraint
{
	public:
	virtual void release()=0;

	virtual bool passes( int var1Value, int var2Value ) const = 0;

	bool passes( const CSPInterpretation &interpretation ) const
	{
		return passes( interpretation.getVariableValue( var1 ), interpretation.getVariableValue( var2 ) );
	}
	virtual Constraint *clone() const = 0;

	int getVar1() const
	{
		return var1;
	}

	int getVar2() const
	{
		return var2;
	}

	protected:
	Constraint( CSPProblem *problem, int var1, int var2 );
	virtual ~Constraint();

	CSPProblem *problem;
	int var1;
	int var2;
};
//---------------------------------------------------------------------------

#endif

