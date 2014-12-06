
#include <string.h> // for null

#include <csp/CSPInterpretation.h>

//---------------------------------------------------------------------------
CSPInterpretation::CSPInterpretation()
{
	variableValues = NULL;
}
//---------------------------------------------------------------------------
CSPInterpretation::CSPInterpretation( int numVariables )
{
	variableValues = NULL;
	setNumVariables( numVariables );
}
//---------------------------------------------------------------------------
CSPInterpretation::CSPInterpretation( const CSPInterpretation &other )
{
	variableValues = NULL;
	assign( other );
}
//---------------------------------------------------------------------------
CSPInterpretation &CSPInterpretation::operator = ( const CSPInterpretation &other )
{
	assign( other );
	return *this;
}
//---------------------------------------------------------------------------
CSPInterpretation::~CSPInterpretation()
{
	clear();
}
//---------------------------------------------------------------------------
void CSPInterpretation::clear()
{
	if ( variableValues != NULL )
	{
		delete[]variableValues;
		variableValues = NULL;
	}
}
//---------------------------------------------------------------------------
void CSPInterpretation::assign( const CSPInterpretation &other )
{
	if ( &other == this )
	{
		return;
	}

	clear();

	if ( other.variableValues != NULL )
	{
		numVariables = other.numVariables;
		variableValues = new int[numVariables];

		for ( int i = 0; i < numVariables; i++ )
		{
			variableValues[i] = other.variableValues[i];
		}
		
	}
}
//---------------------------------------------------------------------------
void CSPInterpretation::setNumVariables( int _numVariables )
{
	clear();

	numVariables = _numVariables;
	variableValues = new int[numVariables];
}
//---------------------------------------------------------------------------
int CSPInterpretation::getNumVariables() const
{
	return numVariables;
}
//---------------------------------------------------------------------------
void CSPInterpretation::setVariableValue( int variable, int value )
{
	variableValues[variable] = value;
}
//---------------------------------------------------------------------------
const int CSPInterpretation::getVariableValue( int variable ) const
{
	return variableValues[variable];
}
//---------------------------------------------------------------------------

