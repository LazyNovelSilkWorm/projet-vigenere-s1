/*=============================================================================
 *                            CLI : CHECK INPUTS
 *=============================================================================
 * 
 *      Ce fichier contient les fonctions permettant de vérifier la 
 *  validité et compatibilité des arguments entrés par l'utilisateur dans la
 *  ligne de commande.
 *
 *      Pour ce faire, checkInputs.c utilise plusieurs variables globales.
 *  Particulièrement :
 *      - int FLAGS[9] :
 *          Les options et opérations entrées et leur statut. Chaque élément
 *          contient une à deux options
 *                g, i, I, k, K, o, d, c, hv 
 *              { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
 *          qui par défaut ont toutes la valeur 0. Si une option est détectée,
 *          on vérifie d'abord que son statut est "inactif" (0). Elle est alors
 *          activée (on change de 0 à 1, ou 2 dans le cas de l'option v).
 *          Ensuite, toutes les options incompatibles reçoivent la valeur -1,
 *          soit "incompatibles".
 *
 *          Si l'option détectée est incompatible avec une option précédente,
 *          alors on annonce une erreur d'usage et on ne continue pas plus
 *          loin.
 *          
 *          Par exemple : si on veut générer une clé,
 *          alors on n'a pas besoin d'entrer un message. Donc si "-g" est
 *          détectée, l'option d'entrer un message "-i" est incompatible. Si on
 *          fait cela avec toutes les options, on trouve, à l'activation de
 *          l'option g :
 *               -g, -i, -I, -k, -K,-o,-c,-d,-hv
 *              { 1, -1, -1, -1, -1, 0, 0, 0, -1 }  
 *          Avec FLAGS, on peut ainsi facilement vérifier que la commande entrée
 *          est valide.
 *      
 *      - int PARAMS[6] :
 *          Ceci contient la position dans argv des paramètres associés à chaque
 *          option qui en nécessite une. En gardant le même ordre que FLAGS par
 *          clarté, on a :
 *               -g, -i, -I, -k, -K, -o
 *             { %d, %d, %d, %d, %d, %d }
 *      
 *      - int g, i, I, k, K, o, c, d, h :
 *          Chaque variable contient la position de l'option respective dans
 *          FLAGS[] et PARAMS[]
 *              g = 0
 *              i = 1
 *              I = 2
 *              k = 3
 *              ...
 *              h = 8
 *
 *      g = 0;	// -g : générer une clé 
 *      i = 1;	// -i : entrée du message dans une chaine de caractères <input string> 
 *      I = 2;	// -I : entrée du message dans un fichier texte <message_filename> 
 *      k = 3;	// -k : entrée de la clé dans une chaine de caractères <key string> 
 *      K = 4;	// -K : entrée de la clé dans un fichier texte : <key_filename> 
 *      o = 5;	// -o : sortie affichée dans un fichier texte : <output_filename> 
 *      d = 6;	// -d : déchiffrer le message 
 *      c = 7;	// -c : chiffrer le message 
 *      h = 8;	// -h or -v : afficher la liste d'aide ou la version 
 *
 *
 *
 *  Toutes ces variables sont définies dans "variables.c"
 */





#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "headers/variables.h"
#include "headers/validation.h"

//		VARIABLE GLOBALE
char LASTOPT;   //  la dernière option enregistrée. permet d'associer un paramètre
                //  à son option respective.

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
int checkFlags(char argvV[]);
int finalOptionCheck(void);








/*
 * ============================================================================
 * FONCTIONS
 * =========
 */



/*
 * OPTIONVALIDATION()
 *
 * 		Ici on pose les options déclarées dans la table de compatibilité FLAGS[] avec
 * 	l'aide de la fonction checkFlags(), et leur argument est mis dans PARAMS[] s'ils
 * 	en ont un.
 *
 * 		Cette fonction vérifie aussi que les options nécéssitant des arguments les ont.
 *
 * ARGUMENTS :
 * 		- int argc :
 * 		    Nombre d'arguments dans la ligne de commande
 * 		- char* argv[] :
 * 		    Tableau de pointeurs vers les valeurs de chaque argument dans
 * 		    la ligne de commande.
 *
 * 	RETOURNE :
 * 		- 0 :
 * 		    Succès
 * 		- 1 :
 * 		    Échec
 *
 */
int optionValidation(int argc, char* argv[])
{
	extern int FLAGS[], PARAMS[];
	extern char LASTOPT;
	int count, vector, reserved, isInvalid;	

	LASTOPT = '\0';
	reserved = -1;


	for (vector = 1 ; vector < argc ; ++vector)
	{

		/* Vérifie si la dernière position finissait avec une option nécessitant
         * un argument */	
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
			isInvalid = checkFlags(argv[vector]);
            
            //  L'option est incompatible
            if ( isInvalid == 1 )
            {
                fprintf(stderr, "optionValidation() : une option incompatible a été"
                        " détectée.\n");
                return 1;
            }
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
			fprintf(stderr, "Erreur optionValidation() : entrée invalide => %s\n",
                    argv[vector]);

			return 1;
		}

	}

	/* Vérifie si les options d, c, g ou hv on été activées. Si ce n'est pas le cas,
	 * le programme ne peut pas savoir que faire. Alors il doit retourner une erreur.*/

	if (FLAGS[0] == 0)	/* Si une de ces options est activée, alors toutes auront soit
						   la valeur 1, 2 out -1. On ne doit que vérifier une valeur.
						   la valeur g est à l'index 0 donc elle a été choisie*/
	{
		fprintf(stderr, "Erreur optionValidation() : action non définie. Vérifier -h "
				"si besoin.\n");
		return 1;
	}

	return 0;
}







/*
 * CHECK FLAGS :

 * 		Modifie le tableau de compatibilité FLAGS[]. Pour chaque option déclarée,
 *  checkFlags(), vérifie si cette option est bien non-activée, et n'a pas été 
 *  invalidée par une option précédente.
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
 *
 * 	ARGUMENTS :
 * 		- char argvV[] :
 * 		    Un argument de la ligne de commande que la fonction optionValidation() a
 * 		    déterminé d'être un bloc d'options.
 *  
 *  RETOURNE :
 *      - 0 :
 *          Valide
 *      - 1 :
 *          Invalide
 */
int checkFlags(char argvV[])
{
	int f;
	extern char LASTOPT;
	extern int FLAGS[];

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
			fprintf(stderr, "checkFlags() : ERROR : option %c invalide\n", argvV[f]);
		}
	}
	LASTOPT = argvV[f - 1];

    return 0;
}
			

/*  FINALOPTIONCHECK()
 *
 *      Dernière vérification, cette fois-ci globale. Vérifie que les options
 *  et les paramètres nécessaires ont bien été entrées par l'utilisateur.
 *
 *  Par exemple : si l'utilisateur cherche à chiffrer un message, il faut bien
 *  qu'il aie entré un message.
 *
 *  RETOURNE :
 *      - 0 :
 *          Succès
 *      - 1 :
 *          Échec
 */
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
		return 1;
	}

	return 0;
}






