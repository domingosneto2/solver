

int testMain( int argc, char **argv );
int benchmarkMain(int argc, char **argv );


int main( int argc, char **argv )
{
	return benchmarkMain( argc, argv );
	//return testMain( argc, argv );
}
