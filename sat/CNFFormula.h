
#ifndef _FORMULA_H_
#define _FORMULA_H_

#include <vector>
using namespace std;

#include <sat/Interpretation.h>
#include <sat/Clause.h>



//---------------------------------------------------------------------------
/**
 * A CNF Formula.
 *
 * This is a class that represents a CNF Formula.  This object holds only
 * data about the formula;  it doesn't have any information about variable
 * values.  These values are store in Interpretation objects.
 *
 * To create a CNFFormula object, fist you have to inform the object how many clauses
 * and how many variables the formula has.  That's acomplished with the 
 * method init(). Each clause and each variable is identified by an index;  
 * there are no names associate to such entities.  When you look a a
 * formula in a book, it has variables named 'a', 'b', 'c', and so on; here,
 * variables are identified by indexes, starting by zero, so the first
 * variable is 'called' 0, the second 1, and so on.
 * 
 * After you called init, and informed how many clauses and how many variables the
 * variable has, you need to initialize each clause.  For each clause, you have to:
 * 1 - Tell how many variables the clause references;
 * 2 - For each variable in the clause, you have to inform the index of that
 *     variable, and the sign it has in the clause.
 * The task 1 and 2 are accomplished by calls to setClauseNumVars and
 * setClauseVar, respectively.
 *
 * You can evaluate the formula given an interpretation;  it's done
 * with the method getValue.  You can also evaluate a single clause,
 * with the method getClauseValue.  There is also the possibility to
 * count how many clauses are satisfied by an interpretation, using the
 * method getNumSatisfiedClauses.
 *
 * An example:
 * Suppose you have the following formula you want to represent as a
 * CNFFormula object:  (a | !b) ( b | c ) ( !c | a ), where | stants for
 * a logical OR and ! is a negation.  There are 3 different variables, a, b, and c,
 * and 3 clauses.  Let's say that a is the first variable, b is the second and c
 * is the third.  Then you would have to do the following calls to
 * initialize the object:
 *
 * CNFFormula f;
 *
 * // Initialize the number of clauses and variables
 * f.init( 3, 3 );
 *
 * // Initialize the first clause.
 * // First we tell how many variables (2) the first clause (index 0) has
 * f.seClauseNumVars( 0, 2 );
 *
 * // In 0-th clause, the first variable(index 0) appears non negated and
 * // is the a, the first variable of the formula (index 0)
 * f.setClauseVar( 0, 0, true, 0 );
 *
 * // In 0-th clause, the second variable(index 1) appears negated and
 * // is the b, the second variable of the formula (index 1)
 * f.setClauseVar( 0, 1, false, 1 );
 *
 *
 * // Now we do the same for the other clauses
 * f.seClauseNumVars( 1, 2 );
 * f.setClauseVar( 1, 0, true, 1 );
 * f.setClauseVar( 1, 1, true, 2 );
 *
 * f.seClauseNumVars( 2, 2 );
 * f.setClauseVar( 2, 0, false, 2 );
 * f.setClauseVar( 2, 1, true, 0 );
 *
 */
class CNFFormula
{
	public:
	CNFFormula();
	CNFFormula( const CNFFormula &other );
	~CNFFormula();

	// Formula building methods
	void init();
	void setNumVars( int i );
	void initClause( int clause );
	void initClauseVar( int clause, int clauseIndex, bool sign, int varIndex );

	// Value querying methods
	bool getClauseValue( int index,  const Interpretation &interpretation  );
	bool getValue( const Interpretation &interpretation );

	// Information methods
	int getNumVars() const;
	int getNumClauses() const;

	int getNumSatisfiedClauses( const Interpretation &interpretation ) const;

	// Assignment
	CNFFormula &operator=( const CNFFormula &other );

	const Clause *getClause( int index ) const;

	private:
	void assign( const CNFFormula &other );

	vector< Clause >clauses;

	int numClauses;
	int numVariables;
};
//---------------------------------------------------------------------------

#endif

