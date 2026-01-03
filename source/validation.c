/*	Regroupe les fonctions de validations d'entrée utilisateur :
 *		-> entrée de message
 *		-> entrée de longueur de clé
 *		-> entrée de nom de fichier
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>

#include "headers/variables.h"




/*	VALIDATION_INTEGER()
 *
 *	Prends l'entrée utilisateur d'un entier et vérifie que c'est bien
 *	un entier positif non nul, inférieur à MAXLEN.
 *
 *	PARAMETRES :
 *	
 *	RETOURNE :
 *		- -1 
 *			si la valeur est invalide
 *		- input 
 *			si la valeur est valide.
 */
int validation_Integer(void)
{
	int input, i;
	char c;

	input = 0;
	i = 0;
	c = getchar();

	while ( c != '\n' && c != '\0' && i < 4 )
	{
		//	Vérifier que le caractère est un chiffre
		if ( c >= 48 && c <= 57 )
		{
			input = input * 10 + (c - 48);
		}
		//	sinon erreur
		else
		{
			input = -1;
			return input;
		}
		c = getchar();
	}

	//	Vérifier que input est dans l'intervalle 0 < input <= MAXLEN
	if (input > MAXLEN || input < 1 )
	{
		input = -1;
	}

	return input;
}



/*	VALIDATION_CARACTERE()
 *
 *	Permet de vérifier la validité du caractère entré en paramètre, et si
 *	nécessaire met en lettres majuscules.
 *
 *	PARAMETRE :
 *		- char c : caractère à vérifier
 *
 *	RETOURNE :
 *		- '\0' :
 *			si le caractère n'appartient pas à l'alphabet
 *		- c :
 *			si le caractère appartient à [A-Z]
 *		- c - 32 :
 *			si le caractère appartient à [a-z]
 */
char validation_Caractere(char c)
{
	//	c inclus dans [a-z]
	if ( c >= 97 && c <= 122 )
	{
		c -= 32;
	}
	//	c inclus dans [A-Z]
	else if ( c >= 65 && c <= 90 )
	{
		;
	}
	//	caractère invalide
	else
	{
		c = '\0';
	}

	return c;
}



/*	VALIDATION_NOM_FICHIER()
 *	
 *	Vérifie que le nom de fichier entré en paramètre est valide et a pour
 *	extension '.txt'.
 *
 *	PARAMETRE :
 *		nomFichier :
 *			Nom du fichier
 *	
 *	RETOURNE :
 *		- 0 :
 *			Le nom est valide
 *		- -1 :
 *			Le nom est invalide
 */
int validation_Nom_Fichier(char* nomFichier)
{
	int loop;
	char * extension = ".txt";
	char * p;

	for ( loop = 0 ; nomFichier[loop] != '\0' ; ++loop )
	{
		p = &nomFichier[loop];

		//	contient un caractère non-valide
		if ( p[0] == ' ' || p[0] == '\n' || p[0] == '\t' )
		{
			break;
		}

		//	finit par l'extension '/txt'
		if ( strcmp(p, extension) == 0 && loop > 0 )
		{
			return 0;
		}
	}
	
	fprintf(stderr, "valdation_Nom_Fichier usage : %s n'est pas un nom de fichier valide.\n", nomFichier);
	return -1;
}



char* validationEntree(char* targetArray, int* targetLengthAddr, char* entree)
{
	char* position;

	position = entree;
	while (*position != '\0' && *targetLengthAddr < MAXLEN)
	{
		//	numAscii()

		if ( validation_Caractere(*position) != '\0' )
		{
			targetArray = realloc(targetArray, *targetLengthAddr + 2);

			targetArray[*targetLengthAddr] = validation_Caractere(*position);
			++(*targetLengthAddr);
		}

		++position;
	}
	targetArray[*targetLengthAddr] = '\0';

	//	vérifier que l'entrée valide n'est pas vide.
	if ( targetArray[0] == '\0' )
	{
		warn("Erreur validationEntree() : Message vide ou invalide.\n");
		return NULL;
	}

	//	si l'entrée est trop grande
	if ( *position != '\0' )
	{
		warn("Warning validationEntree() : longueur de l'entrée est supérieure à\n"
				"MAXLEN (= %d). Une partie du message risque d'être perdue.\n",
				MAXLEN);
	}

	return targetArray;
}



/*	ESTINTEGER()
 *
 *	Vérifie qu'une chaine de charactères est bien un nombre entier positif
 *	inférieur à MAXLEN.
 *
 *	PARAMETRE :
 *		entree :
 *			chaine de caractère à valider
 *
 *	RETOURNE :
 *		longueur :
 *			succès
 *		-1 :
 *			erreur
 */
int estInteger(char* entree)
{
	int loop, longueur = 0;
	char* position;
	char digit;

	position = entree;

	for ( loop = 0 ; *position != '\0' ; ++loop)
	{
		digit = *position;

		//	vérifier que chaque caractère est un integer
		if ( digit >= 48 && digit <= 57 )
		{
			longueur = longueur * 10 + (digit - 48);
		}
		else
		{
			warn("Erreur estInteger() usage : entrer un nombre entier pour générer\n"
					"une clé.\n");
			return 0;
		}
		
		//	vérifier que la longueur est autorisée
		if ( longueur >= MAXLEN )
		{
			warn("Erreur estInteger() usage : longueur de clé (= %d) à générer\n"
				   "supérieure à MAXLEN (= %d).\n", longueur, MAXLEN);
			return -1;
		}

		++position;
	}

	return longueur;
}

