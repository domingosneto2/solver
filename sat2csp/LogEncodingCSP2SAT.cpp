
#include <sat2csp/LogEncodingCSP2SAT.h>

//---------------------------------------------------------------------------
LogEncodingCSP2SAT *LogEncodingCSP2SAT::create()
{
	return new LogEncodingCSP2SAT();
}
//---------------------------------------------------------------------------
void LogEncodingCSP2SAT::release()
{
	delete this;
}
//---------------------------------------------------------------------------
void LogEncodingCSP2SAT::setCSP( const CSPProblem *problem )
{
	formula.init();
	cspNumVars = problem->getNumVars();
	cspVariablesStart.resize( cspNumVars );
	cspVariablesSize.resize( cspNumVars );
	cspDomainSizes.resize( cspNumVars );

	int i;
	satNumVars = 0;
	for ( i = 0; i < cspNumVars; i++ )
	{
		cspVariablesStart[i] = satNumVars;
		cspDomainSizes[i] = problem->getDomainList()->getDomainSize( i );
		cspVariablesSize[i]  = getVarRepresentation( problem->getDomainList()->getDomainSize( i ) );
		satNumVars += cspVariablesSize[i];
	}

	formula.setNumVars( satNumVars );
	int clauseCount = 0;

	// for each CSP variable we create clauses that exclude erroneous top values
	for ( i = 0; i < cspNumVars; i++ )
	{
		// get the max value that a variable can assume
		int maxValue = cspDomainSizes[i] - 1;
		// and the max value that the sat variables that represent this variable 
		// can assume
		int maxSatValue = ( 1 << ( cspVariablesSize[i] ) ) - 1;

		// currently we create a clause for each forbidden value.
		// this can be optimized
		for ( int j = maxValue + 1; j <= maxSatValue; j++ )
		{
			formula.initClause( clauseCount );
			int bitCount;
			int mask = 1;
			for ( bitCount = 0; bitCount < cspVariablesSize[i]; bitCount++ )
			{
				bool sign = (( j & mask ) == 0 );

				formula.initClauseVar( clauseCount, bitCount, sign, cspVariablesStart[i] + bitCount );
				mask = mask << 1;
			}

			clauseCount++;
		}
	}

	// for each binary no good we create a clause that excludes the nogood
	CSPConstraintList *constraintList = problem->getConstraintList()->clone();

	constraintList->resetIterator();
	while ( constraintList->nextConstraint() )
	{
		int var1 = constraintList->getVar1();
		int var2 = constraintList->getVar2();

		int var1DomainSize = problem->getDomainList()->getDomainSize( var1 );
		int var2DomainSize = problem->getDomainList()->getDomainSize( var2 );

		for ( int i1 = 0; i1 < var1DomainSize; i1++ )
		{
			for ( int i2 = 0; i2 < var2DomainSize; i2++ )
			{
				if ( !constraintList->passes( i1, i2 ) )
				{
					formula.initClause( clauseCount );

					int varCount = 0;
					int mask = 1;
					int bitCount;
					for ( bitCount = 0; bitCount < cspVariablesSize[var1]; bitCount++ )
					{
						int masked = i1 & mask;
						bool sign = (masked == 0);

						formula.initClauseVar( clauseCount, varCount, sign, cspVariablesStart[var1] + bitCount );
						varCount++;
						mask = mask << 1;
					}

					mask = 1;
					for ( bitCount = 0; bitCount < cspVariablesSize[var2]; bitCount++ )
					{
						int masked = i2 & mask;
						bool sign = (masked == 0);

						formula.initClauseVar( clauseCount, varCount, sign, cspVariablesStart[var2] + bitCount );
						varCount++;
						mask = mask << 1;
					}

					clauseCount++;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
const CNFFormula LogEncodingCSP2SAT::getFormula() const
{
	return formula;
}
//---------------------------------------------------------------------------
bool LogEncodingCSP2SAT::getCSPInterpratation( const Interpretation &interpretation, CSPInterpretation &cspInterpretation )
{
	cspInterpretation.setNumVariables( cspNumVars );

	for ( int i = 0; i < cspNumVars; i++ )
	{
		int start = cspVariablesStart[i];
		int size = cspVariablesSize[i];

		int val = 0;
		int mask = 1;
		for ( int j = 0; j < size; j++ )
		{
			bool value = interpretation.getValue( cspVariablesStart[i] + j );
			if ( value )
			{
				val |= mask;
			}
			mask = mask << 1;
		}

		if ( val >= cspDomainSizes[i] )
		{
			return false;
		}

		cspInterpretation.setVariableValue( i, val );
	}

	return true;
}
//---------------------------------------------------------------------------
int LogEncodingCSP2SAT::getVarRepresentation( int domainSize )
{
	int max = domainSize - 1;
	int size = 0;
	while ( max != 0 )
	{
		size++;
		max = max >> 1;
	}

	return size;
}
//---------------------------------------------------------------------------
LogEncodingCSP2SAT::LogEncodingCSP2SAT()
{
	cspNumVars = satNumVars = 0;
}
//---------------------------------------------------------------------------
LogEncodingCSP2SAT::~LogEncodingCSP2SAT()
{
}
//---------------------------------------------------------------------------

