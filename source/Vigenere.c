/*=============================================================================
 *                          PROJET VIGENÈRE - MAIN
 *=============================================================================
 *      
 *      La fonction main du Projet Vigenère par le groupe E13.
 */
#include <stdio.h>
#include <stdlib.h>

#include "headers/menuStyle.h"
#include "headers/commandLineStyle.h"



/*  MAIN()
 *
 *      Détermine quelle branche du projet est choisie : la branche CLI (ligne
 *  de commande) ou la branche TUI (intéraction utilisateur).
 *
 *  PARAMETRES :
 *      - char* argv[] :
 *          Tableau de pointeurs
 *      - int argc :
 *          Nombre d'éléments de argv[]
 *
 *  RETOURNE :
 *      - 0 :
 *          Succès
 *      - 1 :
 *          Échec
 */
int main(int argc, char** argv)
{
	int status;
    //  Mode ligne de commande
	if ( argc > 1 )
	{
		status = commandLineStyle(argc, argv);


	}
    //  Mode menu / intéraction utilisateur
	else
	{
		printf("Version Menu\n\n");
		status = menuStyle();
		
	}
    //  Erreur / Échec
	if ( status != 0 )
	{
		printf("ECHEC\n");
        return 1;
	}
	
	return 0;
}


