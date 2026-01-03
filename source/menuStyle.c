/*
 * 	Ce programme a pour raison d'être d'organiser le projet vigenere:
 * 	celui-ci s'occupe de faire la version "Menu" du programme lorsque
 * 	argc == 1 (pas d'arguments entrés).
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <err.h>
#include <string.h>

#include "headers/core.h"
#include "headers/misc.h"
#include "headers/variables.h"
#include "headers/validation.h"
#include "headers/IO.h"

int menuStyle(void);
char * action_chiffrement(void);
char * action_dechiffrement(void);
char * action_generer(void);






// TESTING
/*
int main(void)
{
	//char * message = menuStyle();

	validation_Nom_Fichier("fichier.txt");
	validation_Nom_Fichier("alzieo_'uràéefnjdxnkjhdf.txt");
	validation_Nom_Fichier("hello.txt.");
	//printf("message = %s\n", message);
	//free(message);

	return 0;
}
*/

/*
 * 	Appelée lorsque argc == 1. Ceci est la version menu du programme, appelée
 * 	sans paramètres ou options.
 */
int menuStyle(void)
{
	char action;
	char* outputAddr;
	int status;

	printf("____________________________________________________________________\n"
			"|	ACTION :\n"
			"| Voulez-vous :\n"
			"|	- c : chiffrer un message\n"
			"|	- d : déchiffrer un message\n"
			"|	- g : générer une clé\n"
			"|	- h : afficher le menu d'aide\n"
			"| > ");

	/*	entrée de l'action choisie par l'utilisateur */
	action = getchar();
	printf("| action : %c\n", action);
	getchar();	/*	prend le \n de l'utilisateur pour ne pas géner les entrées futures*/

	if ( action == 'c')
	{
		outputAddr = action_chiffrement();
	}
	else if ( action == 'd')
	{
		outputAddr = action_dechiffrement();
	}
	else if ( action == 'g')
	{
		outputAddr = action_generer();
	}
	else if ( action == 'h' )
	{
		printHelp();
		return 0;
	}
	else if ( action == 'v' )
	{
		printf("Projet Vigenere, Rendu Final\n");
		return 0;
	}
	else
	{
		fprintf(stderr, "usage : option invalide, utilisez l'option -h si vous\n"
				"avez besoin d'aide.\n");
		//exit(EXIT_FAILURE);
		return 1;
	}

	if ( outputAddr == NULL )
	{
		warn("Erreur menuStyle()\n");
		return 1;
	}
	
	//	OUTPUT
	//	si output doit être affichée ou mise dans un fichier
	printf("____________________________________________________________________\n"
			"|	OUTPUT :\n"
			"|	Voulez-vous sauver votre résultat dans un fichier (autrement il\n"
			"|	sera affiché dans le terminal).\n"
			"|	(Y/n) :\n"
			"| > ");
	action = getchar();
	if ( action != '\n' )
	{
		getchar();
	}

	if ( action == 'N' || action == 'n' )
	{
		printf("====================================================================\n"
				"| Résultat :\n|	%s\n", outputAddr);
	}
	else if ( action == 'Y' || action  == 'y' || action == '\n' )
	{
		//printf("Cette option n'est pas encore accessible\n");
		printf("|	Entrez le nom du fichier dans lequel sauvegarder. (Attention,\n"
				"|	si ce fichier existe, le contenu sera effacé) :\n"
				"| > ");
		status = saveToFile(outputAddr);

		if ( status == 1 )
		{
			warn("Erreur : sauvegarde échouée.\n");
			free(outputAddr);
			outputAddr = NULL;
			//exit(EXIT_FAILURE);
			return 1;
		}
	}

	free(outputAddr);
	outputAddr = NULL;

	return 0;
}

/*	ACTION_CHIFFREMENT()
 *
 *	l'utilisateur cherche à chiffrer un message
 *
 *	RETOURNE :
 *		output : message chiffré
 *		NULL : erreur
 */
char * action_chiffrement(void)
{
	char * inputArray = (char *)malloc(sizeof(char));
	char * keyArray = (char *)malloc(sizeof(char));
	int inputLength, keyLength, loop;
	char c;

	//	vérifie allocations
	if ( inputArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		warn("action_chiffrement : inputArray allocation échouée.\n");
		return NULL;
	}
	if ( keyArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		warn("action_chiffrement : keyArray allocation échouée.\n");
		return NULL;
	}

	inputLength = 0;
	keyLength = 0;

	//	====MESSAGE====
	
	//	le message est dans un fichier ou non
	printf("|___________________________________________________________________\n"
			"|	CHIFFREMENT :\n"
			"|	Votre message est-il dans un fichier texte? (format : fichier.txt)\n"
			"|	(Y/n) :\n"
			"| > ");

	c = getchar();
	if ( c != '\n' )
	{
		getchar();
	}

	if ( c == '\n' || c == 'y' || c == 'Y' )
	{
		printf("|	Entrez le nom de votre fichier :\n"
				"| > ");

		//	extraire message du fichier
		inputArray = getFromFile(inputArray, &inputLength);

		//	vérification succès
		if ( inputArray == NULL )
		{
			warn("Warning : action_chiffre : lecture de fichier échouée.\n");
			free(inputArray);
			free(keyArray);
			keyArray = NULL;
			return NULL;
		}
	}
	else if ( c == 'n' || c == 'N' )
	{
		//	entrée du message
		printf("| Entrez votre message à chiffrer :\n"
				"| > ");
		inputArray = getFromUser(inputArray, &inputLength);
	}
	else
	{
		fprintf(stderr, "action_chiffre : entrée invalide.\n");
		inputArray[0] = '\0';
	}

	//	si message vide
	if ( inputArray[0] == '\0' || inputArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		fprintf(stderr, "action_chiffre : message vide, vérifier la validité de l'entrée.\n"
				"	message = %s\n"
				"	longueur message = %d\n", inputArray, inputLength);
		//exit(EXIT_FAILURE);
		return NULL;
	}

	//	====CLEF====
	
	//	clé est dans un fichier ou non
	printf("|	Votre clé est-elle dans un fichier texte? (format : cle.txt)\n"
			"|	(Y/n) :\n"
			"| > ");

	c = getchar();
	if ( c != '\n' )
	{
		getchar();
	}

	if ( c == '\n' || c == 'y' || c == 'Y' )
	{
		printf("|	Entrez le nom du fichier :\n"
				"| > ");

		keyArray = getFromFile(keyArray, &keyLength);

		//	vérification échec
		if ( keyArray == NULL )
		{
			warn("Warning : action_chiffrement : lecture de fichier échouée.\n");
			free(inputArray);
			free(keyArray);
			keyArray = NULL;
			return NULL;
		}
	}
	else if ( c == 'n' || c == 'N' )
	{
		//	entrée de la clé
		printf("| Entrez votre clé de chiffrement :\n"
				"| > ");
		keyArray = getFromUser(keyArray, &keyLength);
	}
	else
	{
		fprintf(stderr, "action_chiffre : entrée invalide.\n");
		keyArray[0] = '\0';
	}

		//	si clé vide
	if ( keyArray[0] == '\0' || keyArray == NULL )
	{
		fprintf(stderr, "usage : clé vide. Vérifier la validité de l'entrée.\n"
				"	clé = %s\n"
				"	longueur clé = %d\n", keyArray, keyLength);
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		//exit(EXIT_FAILURE);
		return NULL;
	}

	//	allocation de mémoire pour l'output, de même longueur que le message
	char * output = (char *)malloc(sizeof(char) * inputLength + 1);

	//	vérification de l'allocation
	if ( output == NULL )
	{
		free(inputArray);
		free(keyArray);
		free(output);
		inputArray = NULL;
		keyArray = NULL;
		output = NULL;
		warn("action_chiffrement : allocation de mémoire de sortie échouée.\n");
		return NULL;
	}

	//	chiffrement du message
	for ( loop = 0 ; loop < inputLength && inputArray[loop] != '\0' ; ++loop )
	{
		output[loop] = encrypt(inputArray[loop], keyArray[loop % keyLength]);
	}

	output[inputLength] = '\0';

	//	libère les tableaux qui n'ont plus d'utilité
	free(inputArray);
	free(keyArray);
	inputArray = NULL;
	keyArray = NULL;

	return output;
}




/*	ACTION_DÉCHIFFREMENT :
 *
 *	L'utilisateur cherche à déchiffrer un message
 *
 *	RETOURNE :
 *		output : message déchiffré
 *		NULL : erreur
 */
char * action_dechiffrement(void)
{
	char * inputArray = (char *)malloc(sizeof(char));
	char * keyArray = (char *)malloc(sizeof(char));
	int inputLength, keyLength, loop;
	char c;

	//	vérifie allocations
	if ( inputArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		warn("action_déchiffrement : inputArray allocation échouée.\n");
		return NULL;
	}
	if ( keyArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		warn("action_déchiffrement : keyArray allocation échouée.\n");
		return NULL;
	}

	inputLength = 0;
	keyLength = 0;

	//	====MESSAGE====
	
	//	le message est dans un fichier ou non
	printf("|___________________________________________________________________\n"
			"|	DÉCHIFFREMENT :\n"
			"|	Votre message est-il dans un fichier texte? (format : fichier.txt)\n"
		  	"|	(Y/n) :\n"
			"| > ");

	c = getchar();
	if ( c != '\n' )
	{
		getchar();
	}

	if ( c == '\n' || c == 'y' || c == 'Y' )
	{
		printf("|	Entrez le nom de votre fichier :\n"
				"| > ");
		
		//	extraire message du fichier
		inputArray = getFromFile(inputArray, &inputLength);
		//	vérification succès
		if ( inputArray == NULL )
		{
			warn("Warning : action_dechiffre lecture de fichier échouée.\n");
			free(inputArray);
			free(keyArray);
			keyArray = NULL;
			return NULL;
		}
	}
	else if ( c == 'n' || c == 'N' )
	{
		//	entrée du message
		printf("| Entrez votre message à déchiffrer :\n"
				"| > ");
		inputArray = getFromUser(inputArray, &inputLength);
	}
	else
	{
		fprintf(stderr, "action_dechiffre : entrée message : option invalide.\n");
		inputArray[0] = '\0';
	}

	//	ERREUR si message vide
	if ( inputArray[0] == '\0' || inputArray == NULL )
	{
		fprintf(stderr, "action_dechiffre : entrer un message en caractères alphabétiques\n"
				"	message = %s\n"
				"	longueur message = %d\n", inputArray, inputLength);
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		//exit(EXIT_FAILURE);
		return NULL;
	}

	//	====CLEF====
	
	//	la clé est dans un fichier ou non
	printf("|	Votre clé est-elle dans un fichier texte? (format : clef.txt)\n"
			"|	(Y/n) :\n"
			"| > ");

	c = getchar();
	if ( c != '\n' )
	{
		getchar();
	}

	if (c == '\n' || c == 'y' || c == 'Y' )
	{
		printf("|	Entrez le nom de votre fichier :\n"
				"| > ");

		//	extraire la clé du fichier
		keyArray = getFromFile(keyArray, &keyLength);

		//	vérification succès
		if ( keyArray == NULL )
		{
			warn("Warning : action_déchiffre : lecture de fichier échouée.\n");
			free(inputArray);
			free(keyArray);
			keyArray = NULL;
			return NULL;
		}
	}
	else if ( c == 'n' || c == 'N' )
	{
		//	entrée de la clé
		printf("| Entrez votre clé de chiffrement :\n"
				"| > ");
		keyArray = getFromUser(keyArray, &keyLength);
	}
	else
	{
		fprintf(stderr, "action_déchiffre : usage : option invalide.\n");
		keyArray[0] = '\0';
	}

	//	ERREUR si clé vide
	if ( keyArray[0] == '\0' || keyArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		fprintf(stderr, "action_déchiffre : entrer une clé en caractères alphabétiques\n"
				"	clé = %s\n"
				"	longueur clé = %d\n", keyArray, keyLength);
		//exit(EXIT_FAILURE);
		return NULL;
	}

	//	allocation de mémoire pour l'output, de même longueur que le message
	char * output = (char *)malloc(sizeof(char) * inputLength + 1);

	//	vérification de l'allocation
	if ( output == NULL )
	{
		free(inputArray);
		free(keyArray);
		free(output);
		inputArray = NULL;
		keyArray = NULL;
		output = NULL;
		warn("action_déchiffre: output allocation échouée.\n");
		return NULL;
	}

	//	déchiffrement du message
	for ( loop = 0 ; loop < inputLength && inputArray[loop] != '\0' ; ++loop )
	{
		output[loop] = decrypt(inputArray[loop], keyArray[loop % keyLength]);
	}

	output[inputLength] = '\0';
	//	libère les tableaux qui n'ont plus d'utilité
	free(inputArray);
	free(keyArray);
	inputArray = NULL;
	keyArray = NULL;

	return output;
}


/*	ACTION_GENERER()
 *
 *	L'utilisateur cherche à générer une clé de chiffrement.
 */
char * action_generer(void)
{
	int keyLength;
	char *output;

	srand(time(NULL));

	printf("|___________________________________________________________________\n"
			"| GENERATION DE CLE :\n"
			"|	Entrez la longueur de la clé que vous voulez générer. Cette valeur\n"
			"| doit être un entier strictement supérieur à 0 et inférieur à %d.\n"
			"| > ", MAXLEN);

	keyLength = validation_Integer();

	if ( keyLength == -1 )
	{
		fprintf(stderr, "action_generer : usage : valeur entrée invalide\n");
		exit(EXIT_FAILURE);
	}

	output = genererClef(keyLength);

	//	vérification de succès
	if ( output == NULL )
	{
		err(2, "Erreur : génération de la clé échouée.\n");
	}


	return output;
}

