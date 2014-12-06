
#ifndef _BASIC_CSP_CONSTRAINT_LIST_H_
#define _BASIC_CSP_CONSTRAINT_LIST_H_

#include <csp/CSPConstraintList.h>
#include <csp/Constraint.h>

#include <vector>
using namespace std;


//---------------------------------------------------------------------------
/**
 * Implementation of the CSPConstraintList interface.
 *
 * @see CSPConstraintList
 */
class BasicCSPConstraintList : public CSPConstraintList
{
	public:

	static BasicCSPConstraintList *create();
	virtual void release();	
	virtual CSPConstraintList *clone() const;

	void addConstraint( Constraint *constraint );

	// Methods inherited from CSPConstraintList
	virtual int getNumConstraints() const;	
	
	// Index based access functions	
	virtual int  getVar1( int constraint ) const;
	virtual int  getVar2( int constraint ) const;
	virtual bool passes( int constraint, int var1Value, int var2Value ) const;
	virtual bool passes( int constraint, const CSPInterpretation &interpretation ) const;

	virtual void resetIterator();
	virtual bool nextConstraint();
	virtual int  getCurrentConstraint();
	virtual int  getVar1() const;
	virtual int  getVar2() const;
	virtual bool passes( int var1Value, int var2Value ) const;
	virtual bool passes( const CSPInterpretation &interpretation ) const;


	private:
	BasicCSPConstraintList();
	BasicCSPConstraintList( const BasicCSPConstraintList &other );
	virtual ~BasicCSPConstraintList();
	vector <Constraint *>constraints;
	int numConstraints;

	int curConstraint;
};
//---------------------------------------------------------------------------

#endif

