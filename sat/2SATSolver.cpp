
#include <iostream>
#include <stdlib.h>
#include <sat/2SATSolver.h>
#include <util/Random.h>
#include <list>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------
TwoSATSolver::TwoSATSolver( CNFFormula _formula )
{
    // Guardamos num membro a fórmula que iremos resolver
	formula = _formula;
}
//---------------------------------------------------------------------------	
bool TwoSATSolver::solve( Interpretation &param )
{
    // Criamos uma interpretação para esta fórmula.
    // Inicialmente, a interpretação não tem valores definidos.
	Interpretation values( formula.getNumVars() );

	// Inicializamos aleatoriamente os valores das vari�veis
	// na interpreta��o que criamos
	for ( int k = 0; k < values.getSize(); k++ )
	{
		values.setValue( k, ( Random::s_urand() % 2 ) == 0 ? false : true );
	}

	// Aqui temos algumas estruturas �teis para melhorar a performance.
	// Um vetor de inteiros com os �ndices das clausulas satisfeitas
	// e um vetor com os �ndices das clausulas n�o satisfeitas.
	vector< int > satisfied;   // satisfied clauses
	vector< int > unsatisfied; // unsatisfied clauses

    // Aqui temos um vetor com o valor de cada clausula, assim n�o precisamos
    // reinterpreta-las sempre que mudamos uma vari�vel
	vector< bool > clauseValue; // the value of each clause
	vector< int  > clauseIndex; // index of the clause in the vectors above

	// each entry is a vector that tells in wich clauses the variable appears
	vector < vector< int > > variableClauses; 

	// each entry is a vector that tells the sign of the variable in the clause
	// if false the variable is negated; if true, the variable is non-negated.
	vector< vector< bool > > variableSigns;

	variableClauses.resize( formula.getNumVars() );
	variableSigns.resize( formula.getNumVars() );

	// Initialize the vectors above
	for ( int m = 0; m < formula.getNumClauses(); m++ )
	{
		const Clause *clause = formula.getClause( m );
		if ( clause->getValue( values ) )
		{
			clauseValue.push_back( true );
			clauseIndex.push_back( satisfied.size() );
			satisfied.push_back( m );
		}
		else
		{
			clauseValue.push_back( false );
			clauseIndex.push_back( unsatisfied.size() );
			unsatisfied.push_back( m );
		}

		for ( int j = 0; j < clause->getNumVars(); j++ )
		{
			variableClauses[clause->getVariableIndex(j)].push_back( m );
			variableSigns[clause->getVariableIndex(j)].push_back( clause->isVariablePositive(j) );
		}

	}

	// if we have a solution already, we are goddamn lucky
	if ( unsatisfied.size() == 0 )
	{
		param = values;
		return true;
	}

	// Now, we do at most N^2 flips
	int max = formula.getNumVars();
	max *= max * 100;

	for ( int i = 0; i < max; i++ )
	{
		// pick a random unsatisfied clause
		int pick = Random::s_urand() % unsatisfied.size();
		int i_clause = unsatisfied[pick];
		const Clause *clause = formula.getClause( i_clause );

		// pick a random variable in this clause
		int pick2 = Random::s_urand() % clause->getNumVars();
		int variable = clause->getVariableIndex( pick2 );

		// flip this variable
		values.setValue( variable, !values.getValue( variable ) );

		// Now, we must look at all clauses this variable
		// belongs to, and if it's value changes we have to
		// mve it from one vector to another
		for ( int j = 0; j < variableClauses[variable].size(); j++ )
		{
			int i_clause2 = variableClauses[variable][j];
			const Clause *clause2 = formula.getClause( i_clause2 );

			bool value = clause2->getValue( values );
			if ( value != clauseValue[i_clause2] )
			{
				clauseValue[i_clause2] = value;

				if ( value == true )
				{
					// We must remove this clause from the unsatisfied
					// vector and add to the satisfied vector
					int vectorIndex = clauseIndex[i_clause2];
					clauseIndex[i_clause2] = satisfied.size();
					satisfied.push_back( i_clause2 );

					if ( vectorIndex == unsatisfied.size() - 1 )
					{
						unsatisfied.pop_back();
					}
					else
					{
						unsatisfied[vectorIndex] = unsatisfied[unsatisfied.size() - 1];
						unsatisfied.pop_back();
						clauseIndex[unsatisfied[vectorIndex]] = vectorIndex;
					}
				}
				else
				{
					// We must remove this clause from the satisfied
					// vector and add to the unsatisfied vector
					int vectorIndex = clauseIndex[i_clause2];
					clauseIndex[i_clause2] = unsatisfied.size();
					unsatisfied.push_back( i_clause2 );

					if ( vectorIndex == satisfied.size() - 1 )
					{
						satisfied.pop_back();
					}
					else
					{
						satisfied[vectorIndex] = satisfied[satisfied.size() - 1];
						satisfied.pop_back();
						clauseIndex[satisfied[vectorIndex]] = vectorIndex;
					}
				}
			}

		}

		if ( unsatisfied.size() == 0 )
		{
			cout << "Solved in " << i << " steps" << endl;
			param = values;
			return true;
		}

		
		
	}

	cout << "Sorry, took too long, I'm giving up" << endl;

	return false;
}
//---------------------------------------------------------------------------	

