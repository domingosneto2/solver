
#include <iostream>
#include <string.h>

using namespace std;

int benchmarkAntSolver( int argc, char **argv );
int benchmarkAntSolver2( int argc, char **argv );
int benchmarkGeneticSAT( int argc, char **argv );

int benchmarkMain( int argc, char **argv )
{
	if ( argc == 1 )
	{
		cout << "Error: Usage:  solver <command> [parameters]" << endl;
		return 1;
	}

	char **myargv = argv;
	myargv++;
		 
	int    myargc = argc - 1;
	
	char *command = argv[1];
	
	if ( strcmp( command, "runAntSolver" ) == 0 )
		return benchmarkAntSolver( myargc, myargv );
	if ( strcmp( command, "runAntSolver2" ) == 0 )
		return benchmarkAntSolver2( myargc, myargv );
	if ( strcmp( command, "runSATGA" ) == 0 )
		return benchmarkGeneticSAT( myargc, myargv );

	cout << "Error: Unknown command \"" << command << "\"" << endl;

	return 1;
}

