/*=============================================================================
 *                          MODE : MENUSTYLE - TUI
 *=============================================================================
 *
 * 	   Ce module contient les fonctions d'opération principales du projet dans
 * 	le mode TUI (Terminal User Interface), qui intéragit dynamiquement avec
 * 	l'utilisateur.
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
char * operation_Chiffrement_Menu(void);
char * operation_Dechiffrement_Menu(void);
char * operation_generer(void);






/*  MENUSTYLE()
 *
 *      Lance le TUI et intéragit avec l'utilisateur au long de l'exécution
 *  du programme. Il permet à l'utilisateur de choisir l'opération à 
 *  exécuter et si le résultat doit être affiché ou sauvé dans un fichier.
 *
 *  RETOURNE :
 *      - 0 :
 *          Succès
 *      - 1 :
 *          Échec
 */
int menuStyle(void)
{
	char operation;
	char* outputAddr;
	int status;

	printf("____________________________________________________________________\n"
			"|	OPERATEUR :\n"
			"| Voulez-vous :\n"
			"|	- c : chiffrer un message\n"
			"|	- d : déchiffrer un message\n"
			"|	- g : générer une clé\n"
			"|	- h : afficher le menu d'aide\n"
			"| > ");

    // ==== OPERATION ====
	/*	Entrée de l'operation choisie par l'utilisateur */
	operation = getchar();
	printf("| operateur : %c\n", operation);
	getchar();	/*	Prend le \n de l'utilisateur pour ne pas géner les entrées futures*/

	if ( operation == 'c')
	{
		outputAddr = operation_Chiffrement_Menu();
	}
	else if ( operation == 'd')
	{
		outputAddr = operation_Dechiffrement_Menu();
	}
	else if ( operation == 'g')
	{
		outputAddr = operation_generer();
	}
	else if ( operation == 'h' )
	{
		printHelp();
		return 0;
	}
	else if ( operation == 'v' )
	{
		printf("Projet Vigenere, Rendu Final, v2.0\n");
		return 0;
	}
	else
	{
		fprintf(stderr, "usage : opération invalide, utilisez l'option -h si vous\n"
				"avez besoin d'aide.\n");
		return 1;
	}

    //  Vérifie succès de l'opération
	if ( outputAddr == NULL )
	{
		warn("Erreur menuStyle()\n");
		return 1;
	}
	
	//	==== OUTPUT ====
	//	Si output doit être affichée ou mise dans un fichier
	printf("____________________________________________________________________\n"
			"|	OUTPUT :\n"
			"|	Voulez-vous sauver votre résultat dans un fichier (autrement il\n"
			"|	sera affiché dans le terminal).\n"
			"|	(Y/n) :\n"
			"| > ");
	operation = getchar();
	if ( operation != '\n' )
	{
		getchar();
	}

	if ( operation == 'N' || operation == 'n' )
	{
		printf("====================================================================\n"
				"| Résultat :\n|	%s\n", outputAddr);
	}
	else if ( operation == 'Y' || operation  == 'y' || operation == '\n' )
	{
		printf("|	Entrez le nom du fichier dans lequel sauvegarder. (Attention,\n"
				"|	si ce fichier existe, le contenu sera effacé) :\n"
				"| > ");
		status = saveToFile(outputAddr);

		if ( status == 1 )
		{
			warn("Erreur : sauvegarde échouée.\n");
			free(outputAddr);
			outputAddr = NULL;
			return 1;
		}
	}

	free(outputAddr);
	outputAddr = NULL;

	return 0;
}

/*	ACTION_CHIFFREMENT()
 *
 *	    L'utilisateur cherche à chiffrer un message
 *
 *	RETOURNE :
 *		- char output[] :
 *		    Message chiffré
 *		- NULL :
 *		    Erreur / échec
 */
char * operation_Chiffrement_Menu(void)
{
	char * inputArray = (char *)malloc(sizeof(char));
	char * keyArray = (char *)malloc(sizeof(char));
	int inputLength, keyLength, loop;
	char c;

	//  Vérifie allocations
	if ( inputArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		warn("operation_Chiffrement_Menu() : inputArray allocation échouée.\n");
		return NULL;
	}
	if ( keyArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		warn("operation_Chiffrement_Menu() : keyArray allocation échouée.\n");
		return NULL;
	}

	inputLength = 0;
	keyLength = 0;

	//	==== MESSAGE ====
	
	//	Le message est dans un fichier ou non
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

		//	Extraire message du fichier
		inputArray = getFromFile(inputArray, &inputLength);

		//	Vérification succès
		if ( inputArray == NULL )
		{
			warn("Warning : operation_Chiffrement_Menu() : lecture de fichier échouée.\n");
			free(inputArray);
			free(keyArray);
			keyArray = NULL;
			return NULL;
		}
	}
	else if ( c == 'n' || c == 'N' )
	{
		//	Entrée du message
		printf("| Entrez votre message à chiffrer :\n"
				"| > ");
		inputArray = getFromUser(inputArray, &inputLength);
	}
	else
	{
		fprintf(stderr, "operation_Chiffrement_Menu() : entrée invalide.\n");
		inputArray[0] = '\0';
	}

	//	Si message vide
	if ( inputArray[0] == '\0' || inputArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		fprintf(stderr, "operation_Chiffrement_Menu() : message vide, vérifier la\n"
                " validité de l'entrée.\n"
				"	message = %s\n"
				"	longueur message = %d\n", inputArray, inputLength);
		return NULL;
	}

	//	==== CLEF ====
	
	//	Clé est dans un fichier ou non
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

		//	Vérification échec
		if ( keyArray == NULL )
		{
			warn("Warning : operation_Chiffrement_Menu() : lecture de fichier échouée.\n");
			free(inputArray);
			free(keyArray);
			keyArray = NULL;
			return NULL;
		}
	}
	else if ( c == 'n' || c == 'N' )
	{
		//	Entrée de la clé
		printf("| Entrez votre clé de chiffrement :\n"
				"| > ");
		keyArray = getFromUser(keyArray, &keyLength);
	}
	else
	{
		fprintf(stderr, "operation_chiffre : entrée invalide.\n");
		keyArray[0] = '\0';
	}

		//	Si clé vide
	if ( keyArray[0] == '\0' || keyArray == NULL )
	{
		fprintf(stderr, "usage : clé vide. Vérifier la validité de l'entrée.\n"
				"	clé = %s\n"
				"	longueur clé = %d\n", keyArray, keyLength);
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		return NULL;
	}

	//	Allocation de mémoire pour l'output, de même longueur que le message
	char * output = (char *)malloc(sizeof(char) * inputLength + 1);

	//	Vérification de l'allocation
	if ( output == NULL )
	{
		free(inputArray);
		free(keyArray);
		free(output);
		inputArray = NULL;
		keyArray = NULL;
		output = NULL;
		warn("operation_Chiffrement_Menu() : allocation de mémoire de sortie échouée.\n");
		return NULL;
	}

	//	Chiffrement du message
	for ( loop = 0 ; loop < inputLength && inputArray[loop] != '\0' ; ++loop )
	{
		output[loop] = encrypt(inputArray[loop], keyArray[loop % keyLength]);
	}

	output[inputLength] = '\0';

	//	Libère les tableaux qui n'ont plus d'utilité
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
char * operation_Dechiffrement_Menu(void)
{
	char * inputArray = (char *)malloc(sizeof(char));
	char * keyArray = (char *)malloc(sizeof(char));
	int inputLength, keyLength, loop;
	char c;

	//	Vérifie allocations
	if ( inputArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		warn("operation_Dechiffrement_Menu() : inputArray allocation échouée.\n");
		return NULL;
	}
	if ( keyArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		warn("operation_Dechiffrement_Menu() : keyArray allocation échouée.\n");
		return NULL;
	}

	inputLength = 0;
	keyLength = 0;

	//	==== MESSAGE ====
	
	//	Le message est dans un fichier ou non
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
		
		//	Extraire message du fichier
		inputArray = getFromFile(inputArray, &inputLength);
		//	Vérification succès
		if ( inputArray == NULL )
		{
			warn("Warning : operation_Dechiffrement_Menu() : lecture de fichier échouée.\n");
			free(inputArray);
			free(keyArray);
			keyArray = NULL;
			return NULL;
		}
	}
	else if ( c == 'n' || c == 'N' )
	{
		//	Entrée du message
		printf("| Entrez votre message à déchiffrer :\n"
				"| > ");
		inputArray = getFromUser(inputArray, &inputLength);
	}
	else
	{
		fprintf(stderr, "operation_Dechiffrement_Menu() : entrée message : option \n"
                "invalide.\n");
		inputArray[0] = '\0';
	}

	//	ERREUR si message vide
	if ( inputArray[0] == '\0' || inputArray == NULL )
	{
		fprintf(stderr, "operation_Dechiffrement_Menu() : entrer un message en \n"
                "caractères alphabétiques\n"
				"	message = %s\n"
				"	longueur message = %d\n", inputArray, inputLength);
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		return NULL;
	}

	//	==== CLEF ====
	
	//	La clé est dans un fichier ou non
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

		//	Extraire la clé du fichier
		keyArray = getFromFile(keyArray, &keyLength);

		//	Vérification succès
		if ( keyArray == NULL )
		{
			warn("Warning : operation_Dechiffrement_Menu() : lecture de fichier échouée.\n");
			free(inputArray);
			free(keyArray);
			keyArray = NULL;
			return NULL;
		}
	}
	else if ( c == 'n' || c == 'N' )
	{
		//	Entrée de la clé
		printf("| Entrez votre clé de chiffrement :\n"
				"| > ");
		keyArray = getFromUser(keyArray, &keyLength);
	}
	else
	{
		fprintf(stderr, "operation_Dechiffrement_Menu() : usage : option invalide.\n");
		keyArray[0] = '\0';
	}

	//	ERREUR si clé vide
	if ( keyArray[0] == '\0' || keyArray == NULL )
	{
		free(inputArray);
		free(keyArray);
		inputArray = NULL;
		keyArray = NULL;
		fprintf(stderr, "operation_Dechiffrement_Menu() : entrer une clé en caractères\n"
                " alphabétiques\n"
				"	clé = %s\n"
				"	longueur clé = %d\n", keyArray, keyLength);
		return NULL;
	}

	//	Allocation de mémoire pour l'output, de même longueur que le message
	char * output = (char *)malloc(sizeof(char) * inputLength + 1);

	//	Vérification de l'allocation
	if ( output == NULL )
	{
		free(inputArray);
		free(keyArray);
		free(output);
		inputArray = NULL;
		keyArray = NULL;
		output = NULL;
		warn("operation_Dechiffrement_Menu() : output allocation échouée.\n");
		return NULL;
	}

	//	Déchiffrement du message
	for ( loop = 0 ; loop < inputLength && inputArray[loop] != '\0' ; ++loop )
	{
		output[loop] = decrypt(inputArray[loop], keyArray[loop % keyLength]);
	}

	output[inputLength] = '\0';
	//	Libère les tableaux qui n'ont plus d'utilité
	free(inputArray);
	free(keyArray);
	inputArray = NULL;
	keyArray = NULL;

	return output;
}


/*	ACTION_GENERER()
 *
 *	L'utilisateur cherche à générer une clé de chiffrement.
 *
 *	RETOURNE :
 *	    - char output[] :
 *	        Clé générée de la longueur choisie
 *	    - NULL :
 *	        Échec
 */
char * operation_generer(void)
{
	int keyLength;
	char *output;

	srand(time(NULL));

	printf("|___________________________________________________________________\n"
			"| GENERATION DE CLE :\n"
			"|	Entrez la longueur de la clé que vous voulez générer. Cette valeur\n"
			"| doit être un entier strictement supérieur à 0 et inférieur à %d.\n"
			"| > ", MAXLENKEY);

    //  Demande un integer et vérifie sa validité
	keyLength = validation_Integer();

	if ( keyLength == -1 )
	{
		fprintf(stderr, "operation_generer : usage : valeur entrée invalide\n");
		return NULL;
	}

	output = genererClef(keyLength);

	//	Vérification de succès
	if ( output == NULL )
	{
		warn("Erreur : génération de la clé échouée.\n");
        return NULL;
	}


	return output;
}

