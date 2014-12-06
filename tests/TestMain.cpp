
#include <string.h>
#include <iostream>

int testBasicCSP( int argc, char **argv );
int testCrosswordCSP( int argc, char **argv );
int testGeneticCSP( int argc, char **argv );
int testArcConsistency( int argc, char **argv );
int testSATInterpretation(int argc, char **argv );
int testSATLIBParser( int argc, char **argv );
int testGeneticSAT( int argc, char **argv );
int testCNFFormula( int argc, char **argv );
int test2SATSolver( int argc, char **argv );
int testNQueensCSP( int argc, char **argv );
int testCSPToSAT( int argc, char **argv );
int testAntSolver( int argc, char **argv );
int testRandomCSP( int argc, char **argv );
int testBitArray( int argc, char **argv );
int testProperties( int argc, char **argv );
int testDualEncoding( int argc, char **argv );
int testMinConflicts( int, char ** );

/*
int testMain( int argc, char **argv )
{
	//BenchmarkGeneticSAT( argc, argv );
	//char *args[] = { "BenchmarkGeneticSAT", "C:\\Users\\Domingos\\Projeto Final\\satlib\\config1.ini" };
	//BenchmarkGeneticSAT( 2, args );
	//testGeneticCSP( 0, NULL );
	//testNQueensCSP( 0, NULL );
	//testCSPToSAT( 0, NULL );
	//testSATLIBParser( 0, NULL );
	//testAntSolver( 0, NULL );
	return testMinConflicts( 0, NULL );
	//testArcConsistency( 0, NULL );
	//testRandomCSP( 0, NULL );
	//testBitArray( 0, NULL );
}
//*/
//*
int testMain( int argc, char **argv )
{
	if ( argc == 1 )
	{
		std::cout << "Usage:  solver <test> [parameters]" << std::endl;
		return 1;
	}

	char **myargv = argv;
	myargv++;
		 
	int    myargc = argc - 1;
	
	char *command = argv[1];
	
	if ( strcmp( command, "testBasicCSP" ) == 0 )
		return testBasicCSP( myargc, myargv );
	if ( strcmp( command, "testCrosswordCSP" ) == 0 )
		return testCrosswordCSP( myargc, myargv );
	if ( strcmp( command, "testGeneticCSP" ) == 0 )
		return testGeneticCSP( myargc, myargv );
	if ( strcmp( command, "testArcConsistency" ) == 0 )
		return testArcConsistency( myargc, myargv );
	if ( strcmp( command, "testSATInterpretation" ) == 0 )
		return testSATInterpretation( myargc, myargv );
	if ( strcmp( command, "testSATLIBParser" ) == 0 )
		return testSATLIBParser( myargc, myargv );
	if ( strcmp( command, "testGeneticSAT" ) == 0 )
		return testGeneticSAT( myargc, myargv );
	if ( strcmp( command, "testCNFFormula" ) == 0 )
		return testCNFFormula( myargc, myargv );
	if ( strcmp( command, "test2SATSolver" ) == 0 )
		return test2SATSolver( myargc, myargv );
	if ( strcmp( command, "testNQueensCSP" ) == 0 )
		return testNQueensCSP( myargc, myargv );
	if ( strcmp( command, "testCSPToSAT" ) == 0 )
		return testCSPToSAT( myargc, myargv );
	if ( strcmp( command, "testAntSolver" ) == 0 )
		return testAntSolver( myargc, myargv );
	if ( strcmp( command, "testRandomCSP" ) == 0 )
		return testRandomCSP( myargc, myargv );
	if ( strcmp( command, "testProperties" ) == 0 )
		return testProperties( myargc, myargv );
	if ( strcmp( command, "testDualEncoding" ) == 0 )
		return testDualEncoding( myargc, myargv );
	if ( strcmp( command, "testMinConflicts" ) == 0 )
		return testMinConflicts( myargc, myargv );



	std::cout << "Unknown test " << command << std::endl;

	return 1;
}

//*/
