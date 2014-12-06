
#ifndef _CLAUSE_H_
#define _CLAUSE_H_

#include <vector>
using namespace std;

#include <sat/Interpretation.h>

//---------------------------------------------------------------------------
/**
 * A Clause.
 * 
 * This class is used along with the CNFFormula class.
 * It represents a single clause within a formula.  There are methods
 * to initialize the number of variables in the clause as well as methods
 * to initialize the variables themselves.
 * 
 * There is also a method to return the truth value of the clause
 * given an interpretation.
 *
 * @see CNFFormula
 */
class Clause
{
    public:
    Clause();
	Clause( const Clause &other );
    ~Clause();
    
	// Initialization methods
    void init();
    void initVariable( int myIndex, bool sign, int hisIndex );
    
	// Evaluation method
    bool getValue( const Interpretation &interpretation ) const;

	// Information methods
    int getNumVars() const;
	bool isVariablePositive( int index ) const;
	int getVariableIndex( int clauseIndex ) const;

	Clause &operator = ( const Clause &other );
	void assign( const Clause &other );
    
    protected:
    vector<int> indexes;
    vector<bool> signs;
    int numVars;
};
//---------------------------------------------------------------------------

#endif

