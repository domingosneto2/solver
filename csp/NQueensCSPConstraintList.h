
#ifndef _VIRTUAL_CSP_CONSTRAINT_LIST_H_
#define _VIRTUAL_CSP_CONSTRAINT_LIST_H_

#include <csp/CSPConstraintList.h>

//---------------------------------------------------------------------------
/**
 * 
 */
class NQueensCSPConstraintList : public CSPConstraintList
{
	public:
	static NQueensCSPConstraintList* create( int n );
	virtual void release();
	virtual CSPConstraintList *clone() const;

	virtual int getNumConstraints() const;	
	
	// Index based access functions
	virtual bool passes( int constraint, int var1Value, int var2Value ) const;
	virtual int  getVar1( int constraint ) const;
	virtual int  getVar2( int constraint ) const;
	virtual bool passes( int constraint, const CSPInterpretation &interpretation ) const;

	// Iterator based access functions	
	virtual void resetIterator();
	virtual bool nextConstraint();
	virtual int  getCurrentConstraint();
	virtual int  getVar1() const;
	virtual int  getVar2() const;
	virtual bool passes( int var1Value, int var2Value ) const;
	virtual bool passes( const CSPInterpretation &interpretation ) const;

	protected:
	NQueensCSPConstraintList( int n );
	int var1, var2, nVars;
	int constraint;

	double getI( int N, double Si ) const;
	double getJ( int N, double Si ) const;

	double getSi( int N, double i ) const;

	bool passes( int var1, int var2, int var1Value, int var2Value ) const;
};
//---------------------------------------------------------------------------

#endif

