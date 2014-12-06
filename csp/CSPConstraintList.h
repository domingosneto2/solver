
#ifndef _CSP_CONSTRAINT_LIST_H_
#define _CSP_CONSTRAINT_LIST_H_

#include <csp/CSPInterpretation.h>

//---------------------------------------------------------------------------
/**
 * An abstract class that represents a CSP constraint list.
 *
 * There are two subclasses:  BasicConstraintList, that implements an actual
 * list of Constraint objects, and VirtualConstraintList, that must be used
 * when the number of constraints in the problem is so high that it would be
 * impossible to allocate all of them in memory.  This is true, for exemple,
 * in the n-queens problem, for large values of n.
 */
class CSPConstraintList
{
	public:
	virtual void release() = 0;
	virtual CSPConstraintList *clone() const = 0;

	virtual int getNumConstraints() const = 0;	
	
	// Index based access functions
	virtual bool passes( int constraint, int var1Value, int var2Value ) const = 0;
	virtual int  getVar1( int constraint ) const = 0;
	virtual int  getVar2( int constraint ) const = 0;
	virtual bool passes( int constraint, const CSPInterpretation &interpretation ) const = 0;

	// Iterator based access functions	
	virtual void resetIterator() = 0;
	virtual bool nextConstraint() = 0;
	virtual int  getCurrentConstraint() = 0;
	virtual int  getVar1() const = 0;
	virtual int  getVar2() const = 0;
	virtual bool passes( int var1Value, int var2Value ) const = 0;
	virtual bool passes( const CSPInterpretation &interpretation ) const = 0;
	

};
//---------------------------------------------------------------------------

#endif

