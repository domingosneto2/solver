
#ifndef _CSP_PROBLEM_H_
#define _CSP_PROBLEM_H_

#pragma warning(disable: 4786)

#include <set>
#include <vector>
using namespace std;

#include <csp/CSPDomainList.h>
#include <csp/CSPConstraintList.h>

//---------------------------------------------------------------------------
/**
 * A placeholder for any extra data that a CSP may carry.
 */
class CSPExtraData
{
	public:
	virtual void release() = 0;
	virtual CSPExtraData * clone() = 0;

	protected:
	CSPExtraData()
	{
	}
	virtual ~CSPExtraData();
};
//---------------------------------------------------------------------------
/**
 * A CSP Instance.
 * <p>
 * This class implements the generic behavior of a CSP problem.
 * In order to use this class to solve specific CSP problems you have to
 * implement both classes <code>CSPVariableValue</code> and <code>Constraint</code>.
 * <p>
 * A CSP problem is made of variables, domains and constraints over the variables.
 * This class implements only binary constraints but this is not a problem since
 * any CSP can be translated into binary CSPs.  This class has methods to set and 
 * get the number of variables, the domain of each variable, the number of constraints 
 * and the value of each constraint.  There is also a method that runs the Arc-Consistency
 * algorithm over the domains of this problem
 * <p>
 * How to use this class:
 * <p>
 * First you have to subclass both the class CSPVariableValue and the class Constraint.
 * Then, you create a CSPProblem object and call setNumVars to set the number of variables
 * of the problem.  For each variable of the problem you call setVarDomain to
 * set the domain of each variable.
 * <p>
 * The next step is to call setNumConstraints to set the number of constraints
 * of the problem, and then, for each constraint, call setConstraint to set the 
 * information specific to this constraint.  If you want, you can then call
 * the arcConsistency method to run the Arc Consistency algorithm on this problem.
 * <p>
 * Now you can call getNumSatisfiedConstraints and isSatisfied methods, passing
 * an interpretation object as a parameter.
 * <p>
 * TODO:  Update this documentation.
 */
class CSPProblem
{
	public:	
	static CSPProblem *create();
	void release();
	
	CSPProblem *clone() const;



	void setNumVars( int numVars );

	/**
	 * Returns the problem's number of variables.
	 */
	int getNumVars() const;	

	/**
	 * Sets the domain list of this problem.
	 *
	 * The object passes as parameter will belong to this class.
	 * You should not maintain a reference to the object.
	 * If you wish to retain the ownership of the domainList
	 * object, you shold call problem->setDomainList( domainList->clone() );.
	 *
	 * Any previously set domain list will be released.
	 */
	void setDomainList( CSPDomainList  *domainList );

	/**
	 * Returns the problem's domain list.
	 */
	const CSPDomainList *getDomainList() const;	

	/**
	 *
	 */
	void setConstraintList( CSPConstraintList *constraintList );

	/**
	 *
	 */
	const CSPConstraintList *getConstraintList() const;

	/**
	 * Runs an arc consistency algorithm over this problem.
	 *
	 * Returns true all domains have at least one value in it,
	 * and false if one of the variables' domains is empty and
	 * therefore the problem has no solution.
	 */
	bool arcConsistency();

	const CSPProblem &operator =( const CSPProblem &other );

	int getNumSatisfiedConstraints( const CSPInterpretation &interpretation ) const;
	bool isSatisfied( const CSPInterpretation &interpretation ) const;

	void setExtraData( CSPExtraData *data );
	const CSPExtraData *getExtraData() const;

	private:
	CSPProblem();
	CSPProblem( const CSPProblem &other );
	~CSPProblem();

	void assign( const CSPProblem &other );
	void clearConstraints();	
	CSPDomainList *domainList;
	CSPConstraintList *constraintList;
	int numVars;
	CSPExtraData *extraData;

	void releaseData();

};
//---------------------------------------------------------------------------

#endif

