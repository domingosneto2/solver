

#include <iostream>
#include <util/Properties.h>


int testProperties( int argc, char **argv )
{
	Properties properties;
	
	cout << "Abrindo arquivo teste.ini."  << endl <<
		    "Este arquivo deve estar no diretorio corrente" << endl;	
	bool res = properties.read( "teste.ini" );

	if ( res == false )
	{
		cout << "Unable to open teste.ini" << endl;
		return 1;
	}

	string str1 = properties.getPropertyString( "str1" );
	cout << "str1 = " << str1.c_str() << endl;

	string str2 = properties.getPropertyString( "str2" );
	cout << "str2=  " << str2.c_str() << endl;

	vector<string> str3 = properties.getPropertyStringVector( "str3" );
	cout << "str3: " << endl;

	for ( int i = 0; i < str3.size(); i++ )
	{
		cout << "\t" << str3[i].c_str() << endl;
	}

	return 0;
}

