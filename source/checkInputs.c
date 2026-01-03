#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "headers/variables.h"
#include "headers/validation.h"

//		VARIABLES GLOBALES (tableaux dans "headers/variables.h"
//int FLAGS[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};	//taille 9
//int PARAMS[] = {0, 0, 0, 0, 0, 0};		//taille 6
char LASTOPT;
/*
 * int FLAGS[] :
 * 	Tableau contenant statut de chaque option : { g ; i ; I ; k ; K ; d ; c ; hv }
 * 		- 0 : option inactivée
 * 		- 1 : option activée (sauf pour v)
 * 		- 2 : option secondaire activée, mais pas la principale (seulement pour v)
* 		- -1 : option est incompatible avec celles déjà sélectionnées
 * 			   
 * 			   {g, i, I, k, K, o, d, c, hv}
 */

/*
 * int PARAMS[] :
 * 	Tableau contenant la position en argv[] de chaque argument aux options -g, -i, -k,
 * -K et -o respectivement.
 *
 * 	 PARAMS[] = {g, i, I, k, K, o}
 */
//PARAMS[6] = {0, 0, 0, 0, 0, 0};

/*
 * char LASTOPT :
 * 	Variable indiquant quelle option est la dernière activée. La valeur est un caractère.
 * Permet d'identifier si un argument appartient à l'option -g, -i, -I, -k, -K ou -o.
 * 	Si ce caractère n'est pas une des ces options, peut permettre d'identifier des erreurs
 * d'entrée.
 */



/*
 * ============================================================================
 * DECLARATION DE FONCTIONS
 * ========================
*/
int optionValidation(int argc, char* argv[]);
void checkFlags(char argvV[]);
int finalOptionCheck(void);



/*
 * ============================================================================
 * Main
 * ====
 */
/*
int main(int argc, char* argv[])
{
	//int counter;
	int statusID, i;	// statusID sera l'état d'exécution du programme. Permettra d'activer 
						//   les erreurs dans la fonction future statusError(statusID)

	printf("nom de programme : %s", argv[0]);
	printf("argc = %d\n\n", argc);

	for (i = 0 ; i < argc ; ++i)
	{
		printf("TEST: argv[%d] = %s\n", i, argv[i]);
	}
	
	if (argc < 2)
	{
		printf("ERROR : action non définie, vérifier -h si vous avez besoin d'aide.\n");
		return 1;
	}

	
	statusID = optionValidation(argc, argv);
	if (statusID > 0)
	{
		//statusError(statusID);
		return statusID;
	}

	
	return 0;
}
*/






/*
 * ============================================================================
 * FONCTIONS
 * =========
 */



/*
 * OPTION VALIDATION
 *
 * 		Ici on pose les options déclarées dans la table de compatibilité FLAGS[] avec
 * 	l'aide de la fonction checkFlags(), et leur argument est mis dans PARAMS[] s'ils
 * 	en ont un.
 *
 * 		Cette fonction vérifie aussi que les options nécéssitant des arguments les ont.
 *
 * ARGUMENTS :
 * 		- int argc : nombre d'arguments dans la ligne de commande
 * 		- char* argv : tableau de pointeurs vers les valeurs de chaque argument dans
 * 		la ligne de commande.
 *
 * 	RETOURNE :
 * 		statusID : ---------------------------TBD-------------------------------------
 *
 * PARAMS[] = {g, i, I, k, K, o}
 */
int optionValidation(int argc, char* argv[])
{
	extern int FLAGS[], PARAMS[];
	extern char LASTOPT;
	int count, vector, reserved;	//, g, i, I, k, K, o;

	//g = 0;
	//i = 1;
	//I = 2;
	//k = 3;
	//K = 4;
	//o = 5;
	LASTOPT = '\0';
	reserved = -1;


	for (vector = 1 ; vector < argc ; ++vector)
	{

		/* Vérifie si la dernière position finissait avec une option nécessitant un argument */	
		for (count = 0 ; count < 5 ; ++count)
		{
			if (PARAMS[count] == vector)
			{
				reserved = vector;
				break;
			}
		}

		if (reserved == vector - 1)
		{
			reserved = 0;
			continue;
		}
		/* Vérifie si argv[vector] est un block d'options (sous la forme : -<options>) */
		else if (argv[vector][0] == '-')
		{
			reserved = 0;
			checkFlags(argv[vector]);
		}
		/* Vérifie si la variable reserved est active. Si c'est le cas, elle ajoute la 
		 * position de cet argument dans PARAMS, à l'index attribué à cette option.
		 */
		else if (LASTOPT == 'g') 
		{
			PARAMS[g] = vector;
		}
		else if (LASTOPT == 'i')
		{
			PARAMS[i] = vector;
		}
		else if (LASTOPT == 'I')
		{
			PARAMS[I] = vector;
		}
		else if (LASTOPT == 'k')
		{
			PARAMS[k] = vector;
		}
		else if (LASTOPT == 'K')
		{
			PARAMS[K] = vector;
		}
		else if (LASTOPT == 'o')
		{
			PARAMS[o] = vector;
		}
		else
		{
			fprintf(stderr, "Erreur optionValidation() : entrée invalide => %s\n", argv[vector]);

			return 1;	//remplacer avec le statusID de l'erreur. à décider
			//statusError(<error ID>);
		}

	}

	/* Vérifie si les options d, c, g ou hv on été activées. Si ce n'est pas le cas,
	 * le programme ne peut pas savoir que faire. Alors il doit retourner une erreur.*/

	if (FLAGS[0] == 0)	/* Si une de ces options est activée, alors toutes auront soit
						   la valeur 1, 2 out -1. On ne doit que vérifier une valeur.
						   la valeur g est à l'index 0 donc elle a été choisie*/
	{
		fprintf(stderr, "Erreur optionValidation() : action non définie. Vérifier -h si\n"
				"si besoin.\n");
		return 2;
	}

	return 0;
}


/*
 * CHECK FLAGS :

 * 		Modifie le tableau de compatibilité FLAGS[]. Pour chaque option déclarée,
 * 		checkFlags(), vérifie si cette option est bien non-activée, et n'a pas
 * 		été invalidée par une option précédente.
 *
 *	- option valide :
 *		--> option est activée (1 ou 2)
 *		--> options incompatibles sont donné la valeur -1
 *	- option invalide :
 *		--> erreur via statusError(<statusID>) (TBD)
 *
 * 	(EXEMPLE : -d est incompatible avec -g, car on ne veut pas générer une
 * 	clé en même temps de	déchiffrer un message. Par contre, -d est compatible
 * 	avec -o qui indique si le messagedéchiffrer doit être mis dans un fichier texte.)
 *
 * 	ARGUMENTS :
 * 		- char argvV[] : un argument de la ligne de commande que la fonction optionValidation() a
 * 		déterminé d'être un bloc d'options.
 */
void checkFlags(char argvV[])
{
	int f;
	extern char LASTOPT;
	extern int FLAGS[];
	//extern int g, i, I, k, K, o, d, c, h;
	
	/*
	 * Position pour chaque option dans FLAGS[]
	 */
	//g = 0;	// -g : générer une clé 
	//i = 1;	// -i : entrée du message dans une chaine de caractères <input string> 
	//I = 2;	// -I : entrée du message dans un fichier texte <message_filename> 
	//k = 3;	// -k : entrée de la clé dans une chaine de caractères <key string> 
	//K = 4;	// -K : entrée de la clé dans un fichier texte : <key_filename> 
	//o = 5;	// -o : sortie affichée dans un fichier texte : <output_filename> 
	//d = 6;	// -d : déchiffrer le message 
	//c = 7;	// -c : chiffrer le message 
	//h = 8;	// -h or -v : afficher la liste d'aide ou la version 

	for (f = 1 ; argvV[f] != '\0' ; ++f)
	{
		if (argvV[f] == 'd' && FLAGS[d] == 0)
		{
			FLAGS[g] = -1;
			FLAGS[d] = 1;
			FLAGS[c] = -1;
			FLAGS[h] = -1;	//-h ou -v
		}
		else if (argvV[f] == 'c' && FLAGS[c] == 0)
		{
			FLAGS[d] = -1;
			FLAGS[c] = 1;
			FLAGS[g] = -1;
			FLAGS[h] = -1;
		}
		/* Pour les prochains flags, soit ils ont besoin d'un paramètre (g, i, I, k, K, o)
		 * ou ils sont incompatibles avec tout autre flag. Donc ils sont à la fin de leur
		 * block d'arguments. On vérifie que c'est le cas.
		 * On vérifie aussi que l'option n'est pas déjà activée, ou incompatible avec
		 * un flag précédent. */
		else if (argvV[f] == 'g' && FLAGS[g] == 0 && argvV[f+1] == '\0')
		{
			FLAGS[d] = -1;
			FLAGS[c] = -1;
			FLAGS[g] = 1;
			FLAGS[i] = -1;
			FLAGS[I] = -1;
			FLAGS[k] = -1;
			FLAGS[k] = -1;
			FLAGS[h] = -1;
		}
		else if (argvV[f] == 'i' && FLAGS[i] == 0 && argvV[f+1] == '\0')
		{
			FLAGS[g] = -1;
			FLAGS[i] = 1;
			FLAGS[I] = -1;
			FLAGS[h] = -1;
		}
		else if (argvV[f] == 'I' && FLAGS[I] == 0 && argvV[f+1] == '\0')
		{
			FLAGS[g] = -1;
			FLAGS[i] = -1;
			FLAGS[I] = 1;
			FLAGS[h] = -1;
		}
		else if (argvV[f] == 'k' && FLAGS[k] == 0 && argvV[f+1] == '\0')
		{
			FLAGS[g] = -1;
			FLAGS[k] = 1;
			FLAGS[K] = -1;
			FLAGS[h] = -1;
		}
		else if (argvV[f] == 'K' && FLAGS[K] == 0 && argvV[f+1] == '\0')
		{
			FLAGS[g] = -1;
			FLAGS[k] = -1;
			FLAGS[K] = 1;
			FLAGS[h] = -1;
		}
		else if (argvV[f] == 'o' && FLAGS[o] == 0 && argvV[f+1] == '\0')
		{
			FLAGS[o] = 1;
			FLAGS[h] = -1;
		}
		else if (argvV[f] == 'h' && FLAGS[h] == 0 && argvV[f+1] == '\0')
		{
			FLAGS[d] = -1;
			FLAGS[c] = -1;
			FLAGS[g] = -1;
			FLAGS[i] = -1;
			FLAGS[I] = -1;
			FLAGS[k] = -1;
			FLAGS[K] = -1;
			FLAGS[o] = -1;
			FLAGS[h] = 1;
		}
		else if (argvV[f] == 'v' && FLAGS[h] == 0 && argvV[f+1] == '\0')
		{
			FLAGS[d] = -1;
			FLAGS[c] = -1;
			FLAGS[g] = -1;
			FLAGS[i] = -1;
			FLAGS[I] = -1;
			FLAGS[k] = -1;
			FLAGS[K] = -1;
			FLAGS[o] = -1;
			FLAGS[h] = 2;
		}
		else
		{
			printf("ERROR : option invalide\n");
			//statusError(<error ID>);
		}
	}
	LASTOPT = argvV[f - 1];
}
			


int finalOptionCheck(void)
{
	//extern int FLAGS[];
	extern int PARAMS[];
	//int statusID;
	int numParam;

	/* Vérifie que les options activées nécéssitant un argument ont bien un assigné. 
	 * Sinon, cela déclenche une erreur d'entrée */
	//counter = 0;
	for (numParam = 0 ; numParam < 6 ; ++numParam)
	{
		if (FLAGS[numParam] == 1 && PARAMS[numParam] == 0)
		{
			printf("Erreur finalOptionCheck() : l'option %d manque un argument."
					" Vérifier -h si nécessaire.\n", numParam);
			//statusError(<statusID>);
			return 1;
		}
	}

	/* Vérifie que si -d ou -c, alors -iI et -kK. */
	if ((FLAGS[d] == 1 || FLAGS[c] == 1) &&	// seulement si c ou d activé
			((FLAGS[i] < 1 && FLAGS[I] < 1) ||	// si i et I non activés ou
			(FLAGS[k] < 1 && FLAGS[K] < 1))		// si k et K non activés
	   )
	{
		fprintf(stderr, "Erreur finalOptionCheck() : clé ou message manquants\n");
		//exit(EXIT_FAILURE);
		return 1;
	}

/*
	printf("\n\n______________________\n");
	printf("option validation :\n");
	printf("FLAGS = {-g,-i,-I,-k,-K,-o,-d,-c,-hv}\n");
	printf("FLAGS = { %d", FLAGS[0]);
	for (int loop = 1 ; loop <= 8 ; ++loop)
	{
		printf(", %d", FLAGS[loop]);
	}
	printf("}\n");

	printf("\nPARAM = {-g,-i,-I,-k,-K,-o}\n");
	printf("PARAM = { %d", PARAMS[0]);
	for (int loop = 1 ; loop <= 5 ; ++loop)
	{
		printf(", %d", PARAMS[loop]);
	}
	printf("}\n");
*/
	return 0;
}






