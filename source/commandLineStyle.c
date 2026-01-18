/*=============================================================================
 *                        MODE : LIGNE DE COMMANDE - CLI
 *=============================================================================
 * 	Ce programme est appelé lorsque argc > 1, la version ligne de commande
 * 	du projet.
 *
 *      Est appelé par la fonction main lorsque argc > 1, c'est à dire que
 *  le programme est appelé telle une commande shell. Cela permet d'utiliser
 *  Vigenere au sein d'un programme ou script plus important, et d'automatiser
 *  le processus de chiffrement/déchiffrement.
 */



#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>

#include "headers/core.h"
#include "headers/misc.h"
#include "headers/variables.h"
#include "headers/validation.h"
#include "headers/checkInputs.h"
#include "headers/fichier.h"


int commandLineStyle(int argc, char* argv[]);
char* operation_Dechiffrement_CLI(char* argv[]);
char* operation_Chiffrement_CLI(char* argv[]);
char* operation_GenererClef_CLI(char* argv[]);



/*  COMMANDLINESTYLE()
 *
 *      Est appelé par la fonction main lorsque argc > 1, et gère le projet
 *  dans le mode CLI (ligne de commmande).
 *
 *  PARAMETRES :
 *      - char* argv[] :
 *          Tableau de pointeurs vers chaque option fournies à l'appel du
 *          programme
 *      - int argc :
 *          Nombre de pointeurs dans le tableau argv[]
 *
 *  RETOURNE :
 *      - 0 :
 *          Succès
 *      - 1 :
 *          Échec
 */
int commandLineStyle(int argc, char* argv[])
{
	int estInvalide;
	char* output;

	//	==== VALIDATION ===
	
	//	Vérifie que les options utilisées sont compatibles
	estInvalide = optionValidation(argc, argv);

	//	Si invalide
	if ( estInvalide == 1 )
	{
		fprintf(stderr, "usage : Option invalide détectée.\n");
		return estInvalide;
	}
	else if ( estInvalide == 2 )
	{
		fprintf(stderr, "usage : Option manquante.\n");
		return estInvalide;
	}

	//	Vérifie que toutes les options nécessaires et leur arguments sont présents
	estInvalide = finalOptionCheck();

	if ( estInvalide >= 1 )
	{
		fprintf(stderr, "usage : Options manquantes\n");
		return estInvalide;
	}


	//	==== FONCTIONALITE ====
	//	Si l'utilisateur a besoin d'aide
	if ( FLAGS[h] == 1 )
	{
		printHelp();
		return 0;
	}
	//	Déchiffrer un message
	else if ( FLAGS[d] == 1 )
	{
		output = operation_Dechiffrement_CLI(argv);

		if ( output == NULL )
		{
			err(2, "CommandLineStyle() : Erreur dans l'exécution du programme.\n");
		}
	}
	//	Chiffrer un message
	else if ( FLAGS[c] == 1 )
	{
		output = operation_Chiffrement_CLI(argv);

		if ( output == NULL )
		{
			err(2, "CommandLineStyle() : Erreur dans l'exécution du programme.\n");
		}
	}
	//	Générer une clé
	else if ( FLAGS[g] == 1 )
	{
		output = operation_GenererClef_CLI(argv);

		if ( output == NULL )
		{
			err(2, "CommandLineStyle() : Erreur dans l'exécution du programme.\n");
		}
	}
    //  Déclarer la version
    else if ( FLAGS[h] == 2 )
    {
        /*printf(
                "Vigenere v1.5\n"
                "Groupe E13 - CYBER 1\n"
              );*/
        version();
        return 0;
    }
	else
	{
		printf("commandLineStyle() : cette option n'existe pas.\n");
		return 1;
	}



	//	==== OUTPUT ====
	if ( FLAGS[o] == 0 )
	{
		printf("%s\n", output);
	}
	else
	{
		char* fileName = argv[PARAMS[o]];

        //  calcul longueur du nom de fichier
        int fileNameLength = 0;
        while (fileName[fileNameLength] != '\0' )
        {
            ++fileNameLength;
        }

		//	Validation du nom de fichier
		estInvalide = validation_Nom_Fichier(fileName, fileNameLength);

		if ( estInvalide == 1 )
		{
			warn("Erreur : '%s' est un nom de fichier invalide. Pour rappel,\n"
					"ce fichier doit finir avec l'extension '.txt' et appartenir\n"
					"au répertoire courant.\n", argv[ PARAMS[ o ] ]);
			free(output);
			output = NULL;
			return 1;
		}

		estInvalide = ecrireDansFichier(fileName, output);

		if ( estInvalide == 1 )
		{
			warn("Erreur commandLineStyle() : sauvegarde échouée.\n");
			free(output);
			output = NULL;
			return 1;
		}
	}

	free(output);
	output = NULL;
	return 0;
}







/*	OPERATION_DECHIFFREMENT_CLI() :
 *
 *	Déchiffre le message avec la clé fournis par l'utilisateur. Ceux_ci peuvent-être
 *	dans des fichiers texte.
 *
 *	PARAMETRE :
 *		- char* argv[]
 *
 *	RETOURNE :
 *		- char output[] :
 *		    Message déchiffré
 *		- NULL :
 *		    Erreur lors de l'exécution
 */
char* operation_Dechiffrement_CLI(char* argv[])
{
	int statut;
	char* message = (char*)malloc(sizeof(char));
	char* clef = (char*)malloc(sizeof(char));
	int lenMessage, lenClef;
	char* fileName;

	//	Verification allocation
	if ( message == NULL || clef == NULL )
	{
		warn("Erreur operation_Dechiffrement_CLI : échec d'allocation.\n");
		free(message);
		free(clef);
		message = NULL;
		clef = NULL;
		return NULL;
	}

	//	==== MESSAGE À DECHIFFRER ====

	lenMessage = 0;
	//	Si le message est entré dans la ligne de commande
	if ( FLAGS[i] == 1 )
	{
		char* tmp = validationEntree(message, &lenMessage, argv[ PARAMS[ i ] ]);

		if ( tmp == NULL )
		{
			warn("Erreur operation_Dechiffrement_CLI() : message vide ou invalide.\n");
			free(clef);
			clef = NULL;
			return NULL;
		}

        message = tmp;
	}
	
	//	Si le message est dans un fichier
	else if ( FLAGS[I] == 1 )
	{
		lenMessage = 0;
		fileName = argv[ PARAMS[ I ] ];

        //  calcul longueur du nom de fichier
        int fileNameLength = 0;
        while ( fileName[fileNameLength] != '\0' )
        {
            ++fileNameLength;
        }


		statut = validation_Nom_Fichier(fileName, fileNameLength);

		//	Si nom de fichier invalide
		if ( statut == 1 )
		{
			warn("Erreur : '%s' est un nom de fichier invalide. Pour rappel,\n"
					"ce fichier doit finir avec l'extension '.txt' et appartenir\n"
					"au répertoire courant.\n", argv[ PARAMS[ I ] ]);
			free(message);
			free(clef);
			message = NULL;
			clef = NULL;
			return NULL;
		}

		//	Lecture du fichier
		char* tmp = lireFichier(fileName, message, &lenMessage);

		//	Si erreur
		if ( tmp == NULL )
		{
			warn("Erreur operation_Dechiffrement_CLI() : échec de lecture du fichier %s\n",
					fileName);
			free(message);
			free(clef);
			clef = NULL;
			return NULL;
		}
        message = tmp;
	}
	else
	{
		warn("Erreur operation_Chiffrement_CLI() : ni -i ni -I activés. Revoir checkInputs.c\n"
				"IMPERATIVEMENT\n");
		free(message);
		free(clef);
		message = NULL;
		clef = NULL;
		return NULL;
	}

	
	//	==== CLEF ====
	lenClef = 0;

	if ( FLAGS[k] == 1 )
	{
		//	Si la clé est dans la ligne de commande
		char* tmp = validationEntree(clef, &lenClef, argv[ PARAMS[ k ] ]);

        if ( tmp == NULL )
        {
            warn("Erreur operation_Chiffrement() : La clé entrée est vide ou invalide.\n");
            free(clef);
            free(message);
            clef = NULL;
            message = NULL;
            return NULL;
        }

        clef = tmp;
	}
	else if ( FLAGS[K] == 1 )
	{
		fileName = argv[ PARAMS[ K ] ];

        //  calcul longueur de fileName
        int fileNameLength = 0;
        while (fileName[fileNameLength] != '\0' )
        {
            ++fileNameLength;
        }

		statut = validation_Nom_Fichier(fileName, fileNameLength);

		//	Si nom de fichier invalide
		if ( statut == 1 )
		{
			warn("Erreur operation_Dechiffrement_CLI() : %s est un nom de fichier\n"
					"invalide. Pour rappel, ce fichier doit finir avec l'extension\n"
					"'.txt' et appartenir au répertoire courant.\n", argv[ PARAMS[ K ] ]);
			free(message);
			free(clef);
			message = NULL;
			clef = NULL;
			return NULL;
		}

		
		char* tmp = lireFichier(fileName, clef, &lenClef);

		if ( tmp == NULL )
		{
			warn("Erreur operation_Dechiffrement_CLI() : lecture du fichier %s échouée.\n",
					fileName);
			free(clef);
			free(message);
			message = NULL;
			return NULL;
		}
        clef = tmp;
	}
	else
	{
		warn("Erreur operation_Dechiffrement_CLI() : ni -k ni -K activés. Revoir\n"
                " checkInputs.c\n"
				"IMPERATIVEMENT\n");
		free(message);
		free(clef);
		message = NULL;
		clef = NULL;
		return NULL;
	}


	//	==== DECHIFFREMENT ====
	char * output = (char *)malloc(sizeof(char) * (lenMessage + 1));

	if ( output == NULL )
	{
		free(output);
		free(message);
		message = NULL;
		free(clef);
		clef = NULL;
		return NULL;
	}

	for ( int loop = 0 ; loop < lenMessage && message[loop] != '\0' ; ++loop)
	{
		output[loop] = decrypt(message[loop], clef[loop % lenClef]);
	}

	output[lenMessage] = '\0';

	//	Libération de message et clef s'ils ont été alloués
	free(message);
	message = NULL;
	free(clef);
	clef = NULL;
	
	return output;
}







/*	OPERATION_CHIFFREMENT_CLI()
 *
 *	Chiffre le message avec la clé fournis par l'utilisateur. Ceux_ci peuvent-être
 *	dans des fichiers texte.
 *
 *	PARAMETRE :
 *		argv[]
 *
 *	RETOURNE :
 *		output : message chiffré
 *		NULL : erreur lors de l'exécution
 */
char* operation_Chiffrement_CLI(char* argv[])
{
	int statut;
	char* messageVig = (char*)malloc(sizeof(char));
	char* clef = (char*)malloc(sizeof(char));
	int lenMessageVig, lenClef;
	char* fileName;

	//	Verification allocation
	if ( messageVig == NULL || clef == NULL )
	{
		warn("Erreur operation_Chiffrement_CLI : échec d'allocation.\n");
		free(messageVig);
		free(clef);
		messageVig = NULL;
		clef = NULL;
		return NULL;
	}

	//	==== MESSAGE À CHIFFRER ====

	lenMessageVig = 0;
	//	Si le messageVig est entré dans la ligne de commande
	if ( FLAGS[i] == 1 )
	{
		char* tmp = validationEntree(messageVig, &lenMessageVig, argv[ PARAMS[ i ] ]);

		if ( messageVig == NULL )
		{
			warn("Erreur operation_Chiffrement_CLI() : messageVig vide ou invalide.\n");
			free(clef);
			clef = NULL;
			return NULL;
		}

        messageVig = tmp;
	}
	
	//	Si le messageVig est dans un fichier
	else if ( FLAGS[I] == 1 )
	{
		lenMessageVig = 0;
		fileName = argv[ PARAMS[ I ] ];

        //  calcul de la longueur de fileName
        int fileNameLength = 0;
        while (fileName[fileNameLength] != '\0')
        {
            ++fileNameLength;
        }

		statut = validation_Nom_Fichier(fileName, fileNameLength);

		//	Si nom de fichier invalide
		if ( statut == 1 )
		{
			warn("Erreur : '%s' est un nom de fichier invalide. Pour rappel,\n"
					"ce fichier doit finir avec l'extension '.txt' et appartenir\n"
					"au répertoire courant.\n", argv[ PARAMS[ I ] ]);
			free(messageVig);
			free(clef);
			messageVig = NULL;
			clef = NULL;
			return NULL;
		}

		//	Lecture du fichier
		char* tmp = lireFichier(fileName, messageVig, &lenMessageVig);

		//	Si erreur
		if ( tmp == NULL )
		{
			warn("Erreur operation_Chiffrement_CLI() : échec de lecture du fichier %s\n",
					fileName);
			free(messageVig);
			free(clef);
			clef = NULL;
			return NULL;
		}
        messageVig = tmp;
	}
	else
	{
		warn("Erreur operation_Chiffrement_CLI() : ni -i ni -I activés. Revoir checkInputs.c\n"
				"IMPERATIVEMENT\n");
		free(messageVig);
		free(clef);
		messageVig = NULL;
		clef = NULL;
		return NULL;
	}

	
	//	==== CLEF ====
	lenClef = 0;

	if ( FLAGS[k] == 1 )
	{
		//	Si la clé est dans la ligne de commande
		char* tmp = validationEntree(clef, &lenClef, argv[ PARAMS[ k ] ]);

        if ( tmp == NULL )
        {
            warn("Erreur operation_Chiffrement() : La clé entrée est invalide.\n");
            free(messageVig);
            messageVig = NULL;
            return NULL;
        }

        clef = tmp;
	}
	else if ( FLAGS[K] == 1 )
	{
		fileName = argv[ PARAMS[ K ] ];

        int fileNameLength = 0;
        while (fileName[fileNameLength] != '\0' )
        {
            ++fileNameLength;
        }

		statut = validation_Nom_Fichier(fileName, fileNameLength);

		//	Si nom de fichier invalide
		if ( statut == 1 )
		{
			warn("Erreur operation_Chiffrement_CLI() : %s est un nom de fichier\n"
					"invalide. Pour rappel, ce fichier doit finir avec l'extension\n"
					"'.txt' et appartenir au répertoire courant.\n", argv[ PARAMS[ K ] ]);
			free(messageVig);
			free(clef);
			messageVig = NULL;
			clef = NULL;
			return NULL;
		}

		
		char* tmp = lireFichier(fileName, clef, &lenClef);

		if ( tmp == NULL )
		{
			warn("Erreur operation_Chiffrement_CLI() : lecture du fichier %s échouée.\n",
					fileName);
			free(clef);
			free(messageVig);
			messageVig = NULL;
			return NULL;
		}

        clef = tmp;
	}
	else
	{
		warn("Erreur operation_Chiffrement_CLI() : ni -k ni -K activés. Revoir\n"
                " checkInputs.c\n"
				"IMPERATIVEMENT\n");
		free(messageVig);
		free(clef);
		messageVig = NULL;
		clef = NULL;
		return NULL;
	}


	//	==== CHIFFREMENT ====
	char * output = (char *)malloc(sizeof(char) * (lenMessageVig + 1));

	if ( output == NULL )
	{
		free(output);
		free(messageVig);
		free(clef);
		messageVig = NULL;
		clef = NULL;
		return NULL;
	}

	for ( int loop = 0 ; loop < lenMessageVig && messageVig[loop] != '\0' ; ++loop)
	{
		output[loop] = encrypt(messageVig[loop], clef[loop % lenClef]);
	}

	output[lenMessageVig] = '\0';

	//	Libération de messageVig et clef s'ils ont été alloués
	free(messageVig);
	messageVig = NULL;
	free(clef);
	clef = NULL;
	
	return output;
}






/*	OPERATION_GENERERCLEF_CLI()
 *
 *	Génère une clé de longueur donnée par l'utilisateur.
 *
 *	PARAMETRE :
 *		- char* argv[]
 *
 *	RETOURNE :
 *		- char clef[] :
 *		    Clef générée de la longueur demandée par l'utilisateur.
 *		- NULL :
 *		    Erreur
 */
char* operation_GenererClef_CLI(char* argv[])
{
	int lenClef;
	char* entree;

	entree = argv[ PARAMS[ g ] ];

	//	==== VALIDATION ====
	
	if ( (lenClef = estInteger(entree)) == -1 )
	{
		warn("Erreur operation_GenererClef_CLI() usage : entrée invalide, le paramètre \n"
                "de -g devrait être un nombre entier positif inférieur à MAXLEN (= %d).\n",
				MAXLEN);
		return NULL;
	}


	//	==== GÉNÉRATION ====
	char * clef = genererClef(lenClef);

	//	Vérification de succès
	if ( clef == NULL )
	{
		warn("Erreur operation_GenererClef_CLI() : génération de clé échouée.\n");
		return NULL;
	}

	return clef;
}
