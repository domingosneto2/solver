#include <iostream>
#include <sat/CNFFormula.h>
#include <sat/SATLIBParser.h>

static void printClause( const Clause *clause )
{
	cout << "(";
	for ( int i = 0; i < clause->getNumVars(); i++ )
	{
		if ( i > 0 )
		{
			cout << " | ";
		}
		bool sign = clause->isVariablePositive( i );
		if ( sign == false )
		{
			cout << "-";
		}
		cout << clause->getVariableIndex( i );
	}

	cout << ")";
}

static void printFormula( CNFFormula &formula )
{
	for ( int i = 0; i < formula.getNumClauses(); i++ )
	{
		if ( i > 0 )
		{
			cout << " & ";
		}
		printClause( formula.getClause( i ) );
	}
}


int testSATLIBParser( int argc, char **argv )
{
	SATLIBParser parser;

	bool res = parser.open( "tests\\satlib.txt" );
	if ( res == false )
	{
		cout << "Mal, sap�o" << endl;
		return 1;;
	}

	CNFFormula formula = parser.getFormula();
	printFormula( formula );

	return 0;
}
