#include <iostream>
#include <sat/CNFFormula.h>

int testSATInterpretation(int argc, char **argv )
{
	Interpretation i( 32 );

	for ( int i1 = 0; i1 < 32; i1++ )
	{
		i.setValue( i1, false );
	}

	for ( int i2= 0; i2 < 32; i2++ )
	{
		i.setValue( i2, true );
		if ( i.getValue( i2 ) != true )
		{
			cout << "Erro em " << i2 << endl;
			return 1;
		}

		for ( int i3 = 0; i3 < 32; i3++ )
		{
			if ( i3 != i2 )
			{
				if ( i.getValue( i3 ) != false )
				{
					cout << "Erro em " << i2 << " " << i3 << endl;
					return 1;
				}
			}
		}

		i.setValue( i2, false );
	}

	cout << "OK" << endl;

	return 0;
}

