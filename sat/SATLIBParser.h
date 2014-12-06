
#ifndef _SATLIB_PARSER_H_
#define _SATLIB_PARSER_H_

#include <sat/CNFFormula.h>
#include <stdio.h>

//---------------------------------------------------------------------------
/**
 * A parser that reads a problem in the DIMACS format.
 * Currently, it only reads CNF files.
 */
class SATLIBParser
{
    public:
    SATLIBParser();
    ~SATLIBParser();
    
    bool open( const char *filename );
	bool readFormula( FILE *fptr );
	bool readPreamble( FILE *fptr );
	bool readPreambleString( char *Buffer );
    
    bool isCNF();
    
    CNFFormula getFormula();

	private:
	CNFFormula formula;
	FILE *fptr;
	void ltrim( char *ptr );
	void rtrim( char *ptr );
	void trim( char *ptr );
	bool isSpace( char c );
	int variables;
	int clauses;
    
};
//---------------------------------------------------------------------------

#endif

