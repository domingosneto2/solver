
#include <iostream>
#include <sat/CNFFormula.h>
#include <sat/SATLIBParser.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------
SATLIBParser::SATLIBParser()
{
}
//---------------------------------------------------------------------------
SATLIBParser::~SATLIBParser()
{
}
//---------------------------------------------------------------------------
bool SATLIBParser::open( const char *filename )
{
	FILE *fptr = fopen( filename, "rb" );
	if ( fptr == NULL )
	{
		cout << "fptr = null" << endl;
		return false;
	}

	formula.init();

	if ( !readPreamble( fptr ) )
	{
		return false;
	}

	if ( !readFormula( fptr ) ) 
	{
		return false;
	}

	fclose( fptr );

	return true;
}
//---------------------------------------------------------------------------
bool SATLIBParser::readPreamble( FILE *fptr )
{
	// A buffer that should be large enough
	char Buffer[2048];
	while ( !feof( fptr ) )
	{
		fgets( Buffer, 2048, fptr );

		trim( Buffer );

		if ( Buffer[0] == 'c' )
		{
			continue;
		}

		if ( Buffer[0] == 'p' )
		{
			return readPreambleString( Buffer );			
		}

	}

	return false;
}
//---------------------------------------------------------------------------
bool SATLIBParser::readFormula( FILE *fptr )
{
	char Buffer[2048];
	const char *seps = " \t\r\n";

	int curClause = 0;
	int curVar = 0;

	if ( clauses == 0 )
	{
		return true;
	}

	formula.initClause( 0 );

	while ( !feof( fptr ) )
	{
		// read the line
		fgets( Buffer, 2048, fptr );
		
		// get the first token
		char *token = strtok( Buffer, seps );

		// Read all variables in this line
		while ( token != NULL )
		{
			// translate the token into an integer
			int variable = atoi( token );

			// if it is zero, we reached the end of this clause
			if ( variable == 0 )
			{
				curClause++;				
				curVar = 0;

				if ( curClause == clauses )
				{
					return true;
				}

				formula.initClause( curClause );
			}
			else
			{
				bool positive = true;
				if ( variable < 0 )
				{
					positive = false;
					variable = -variable;
				}

				// validate the variable index
				if ( variable > variables )
				{
					cout << "variable > variables" << endl;
					return false;
				}

				// in the file the variables are 1-indexed but for us
				// they will be zero-indexed
				variable--;				

				formula.initClauseVar( curClause, curVar, positive, variable );
				curVar++;
			}

			token = strtok( NULL, seps );
		}
		
	}

	// got here? shouldn't
	cout << "got here? shouldn't" << endl;
	return false;
}
//---------------------------------------------------------------------------
bool SATLIBParser::readPreambleString( char *Buffer )
{
	const char *seps = " \t\r\n";
	char *token = strtok( Buffer, seps );

	if ( strcmp( token, "p" ) != 0 )
	{
		cout << "token != p" << endl;
		return false;
	}

	// Read the problem type
	token = strtok( NULL, seps );
	if ( token == NULL )
	{
		cout << "token == NULL 1" << endl;
		return false;
	}

	if ( strcmp( token, "cnf" ) != 0 )
	{
		cout << "token != cnf" << endl;
		return false;
	}

	// Read the number of variables
	token = strtok( NULL, seps );
	if ( token == NULL )
	{
		cout << "token == NULL 2" << endl;
		return false;
	}
	variables = atoi( token );	

	// Read the number o clauses
	token = strtok( NULL, seps );
	if ( token == NULL )
	{
		cout << "token == NULL 3" << endl;
		return false;
	}
	clauses = atoi( token );
	

	return true;
}
//---------------------------------------------------------------------------
bool SATLIBParser::isSpace( char c )
{
	if ( c == ' ' || c == '\t' || c == '\r' || c == '\n' )
	{
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
void SATLIBParser::ltrim( char *ptr )
{
	char *ptr1 = ptr, *ptr2 = ptr;

	while ( isSpace( *ptr1 ) )
	{
		ptr1++;
	}

	while ( *ptr1 != 0 )
	{
		*ptr2 = *ptr1;
		ptr1++;
		ptr2++;
	}
	*ptr2 = 0;
}
//---------------------------------------------------------------------------
void SATLIBParser::rtrim( char *ptr )
{
	int len = strlen( ptr );
	if ( len == 0 )
	{
		return;
	}
	
	char *ptr1 = ptr + len - 1;
	while ( ptr1 >= ptr && isSpace( *ptr1 ) )
	{
		ptr1--;
	}

	ptr1++;
	*ptr1 = 0;

	
}
//---------------------------------------------------------------------------
void SATLIBParser::trim( char *ptr )
{
	ltrim( ptr );
	rtrim( ptr );
}
//---------------------------------------------------------------------------
CNFFormula SATLIBParser::getFormula()
{
	return formula;
}
//---------------------------------------------------------------------------

