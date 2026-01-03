#include <stdio.h>
#include <stdlib.h>

#include "headers/menuStyle.h"
#include "headers/commandLineStyle.h"




int main(int argc, char** argv)
{
	int status;
	if ( argc > 1 )
	{
		status = commandLineStyle(argc, argv);


	}
	else
	{
		printf("Version Menu\n\n");
		status = menuStyle();
		
	}
	if ( status != 0 )
	{
		printf("ECHEC\n");
	}
	
	return 0;
}


