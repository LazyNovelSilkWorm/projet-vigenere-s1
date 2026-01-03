/*
 * 	Ce programme est appelé lorsque argc > 1, la version ligne de commande
 * 	du projet.
 *
 * 	Autrement, la fonction menuStyle (voir menuStyle.c) est appelée.
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
char* cli_Dechiffrement(char* argv[]);
char* cli_Chiffrement(char* argv[]);
char* cli_GenererClef(char* argv[]);




int commandLineStyle(int argc, char* argv[])
{
	int estInvalide;
	char* output;

	//	==== VALIDATION ===
	
	//	vérifie que les options utilisées sont compatibles
	estInvalide = optionValidation(argc, argv);

	//	si invalide
	if ( estInvalide == 1 )
	{
		fprintf(stderr, "Option invalide.\n");
		return estInvalide;
	}
	else if ( estInvalide == 2 )
	{
		fprintf(stderr, "Option manquante.\n");
		return estInvalide;
	}

	//	vérifie que toutes les options nécessaires et leur arguments sont présents
	estInvalide = finalOptionCheck();

	if ( estInvalide >= 1 )
	{
		fprintf(stderr, "options manquantes\n");
		return estInvalide;
	}


	//	==== FONCTIONALITE ====
	//	si l'utilisateur a besoin d'aide
	if ( FLAGS[h] == 1 )
	{
		printHelp();
		return 0;
	}
	//	déchiffrer un message
	else if ( FLAGS[d] == 1 )
	{
		output = cli_Dechiffrement(argv);

		if ( output == NULL )
		{
			err(2, "CommandLineStyle() : ERREUR\n");
		}
	}
	//	chiffrer un message
	else if ( FLAGS[c] == 1 )
	{
		output = cli_Chiffrement(argv);

		if ( output == NULL )
		{
			err(2, "CommandLineStyle() : ERREUR\n");
		}
	}
	//	générer une clé
	else if ( FLAGS[g] == 1 )
	{
		output = cli_GenererClef(argv);

		if ( output == NULL )
		{
			err(2, "CommandLineStyle() : ERREUR\n");
		}
	}
    //  déclarer la version
    else if ( FLAGS[h] == 2 )
    {
        printf(
                "Vigenere v1.5\n"
                "Groupe E13 - CYBER 1\n"
              );
        return 0;
    }
	else
	{
		printf("DEBUG commandLineStyle() : cette option n'existe pas.\n");
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

		//	validation du nom de fichier
		estInvalide = validation_Nom_Fichier(fileName);
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







/*	CLI_DECHIFFREMENT()
 *
 *	Déchiffre le message avec la clé fournis par l'utilisateur. Ceux_ci peuvent-être
 *	dans des fichiers texte.
 *
 *	PARAMETRE :
 *		argv[]
 *
 *	RETOURNE :
 *		output : message déchiffré
 *		NULL : erreur lors de l'exécution
 */
char* cli_Dechiffrement(char* argv[])
{
	int statut;
	char* message = (char*)malloc(sizeof(char));
	char* clef = (char*)malloc(sizeof(char));
	int lenMessage, lenClef;
	char* fileName;

	//	Verification allocation
	if ( message == NULL || clef == NULL )
	{
		warn("Erreur cli_Dechiffrement : échec d'allocation.\n");
		free(message);
		free(clef);
		message = NULL;
		clef = NULL;
		return NULL;
	}

	//	==== MESSAGE ====

	lenMessage = 0;
	//	si le message est entré dans la ligne de commande
	if ( FLAGS[i] == 1 )
	{
		message = validationEntree(message, &lenMessage, argv[ PARAMS[ i ] ]);

		if ( message == NULL )
		{
			warn("Erreur cli_Dechiffrement() : message vide ou invalide.\n");
			free(message);
			free(clef);
			message = NULL;
			clef = NULL;
			return NULL;
		}
	}
	
	//	si le message est dans un fichier
	else if ( FLAGS[I] == 1 )
	{
		lenMessage = 0;
		fileName = argv[ PARAMS[ I ] ];

		statut = validation_Nom_Fichier(fileName);

		//	si nom de fichier invalide
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
		message = lireFichier(fileName, message, &lenMessage);

		//	si erreur
		if ( message == NULL )
		{
			warn("Erreur cli_Dechiffrement() : échec de lecture du fichier%s\n",
					fileName);
			free(message);
			free(clef);
			clef = NULL;
			return NULL;
		}
	}
	else
	{
		warn("Erreur cli_Chiffrement() : ni -i ni -I activés. Revoir checkInputs.c\n"
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
		//	si la clé est dans la ligne de commande
		clef = validationEntree(clef, &lenClef, argv[ PARAMS[ k ] ]);
	}
	else if ( FLAGS[K] == 1 )
	{
		fileName = argv[ PARAMS[ K ] ];

		statut = validation_Nom_Fichier(fileName);

		//	si nom de fichier invalide
		if ( statut == 1 )
		{
			warn("Erreur cli_Dechiffrement() : %s est un nom de fichier\n"
					"invalide. Pour rappel, ce fichier doit finir avec l'extension\n"
					"'.txt' et appartenir au répertoire courant.\n", argv[ PARAMS[ K ] ]);
			free(message);
			free(clef);
			message = NULL;
			clef = NULL;
			return NULL;
		}

		
		clef = lireFichier(fileName, clef, &lenClef);

		if ( clef == NULL )
		{
			warn("Erreur cli_Dechiffrement() : lecture du fichier %s échouée.\n",
					fileName);
			free(clef);
			free(message);
			message = NULL;
			return NULL;
		}
	}
	else
	{
		warn("Erreur cli_Dechiffrement() : ni -k ni -K activés. Revoir checkInputs.c\n"
				"IMPERATIVEMENT\n");
		free(message);
		free(clef);
		message = NULL;
		clef = NULL;
		return NULL;
	}


	//	==== DECHIFFREMENT ====
	char * output = (char *)malloc(sizeof(char) * lenMessage);

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

	//	libération de message et clef s'ils ont été alloués
	free(message);
	message = NULL;
	free(clef);
	clef = NULL;
	
	return output;
}







/*	CLI_CHIFFREMENT()
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
char* cli_Chiffrement(char* argv[])
{
	int statut;
	char* messageVig = (char*)malloc(sizeof(char));
	char* clef = (char*)malloc(sizeof(char));
	int lenMessageVig, lenClef;
	char* fileName;

	//	Verification allocation
	if ( messageVig == NULL || clef == NULL )
	{
		warn("Erreur cli_Chiffrement : échec d'allocation.\n");
		free(messageVig);
		free(clef);
		messageVig = NULL;
		clef = NULL;
		return NULL;
	}

	//	==== messageVig ====

	lenMessageVig = 0;
	//	si le messageVig est entré dans la ligne de commande
	if ( FLAGS[i] == 1 )
	{
		messageVig = validationEntree(messageVig, &lenMessageVig, argv[ PARAMS[ i ] ]);

		if ( messageVig == NULL )
		{
			warn("Erreur cli_Chiffrement() : messageVig vide ou invalide.\n");
			free(messageVig);
			free(clef);
			messageVig = NULL;
			clef = NULL;
			return NULL;
		}
	}
	
	//	si le messageVig est dans un fichier
	else if ( FLAGS[I] == 1 )
	{
		lenMessageVig = 0;
		fileName = argv[ PARAMS[ I ] ];

		statut = validation_Nom_Fichier(fileName);

		//	si nom de fichier invalide
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
		messageVig = lireFichier(fileName, messageVig, &lenMessageVig);

		//	si erreur
		if ( messageVig == NULL )
		{
			warn("Erreur cli_Chiffrement() : échec de lecture du fichier%s\n",
					fileName);
			free(messageVig);
			free(clef);
			clef = NULL;
			return NULL;
		}
	}
	else
	{
		warn("Erreur cli_Chiffrement() : ni -i ni -I activés. Revoir checkInputs.c\n"
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
		//	si la clé est dans la ligne de commande
		clef = validationEntree(clef, &lenClef, argv[ PARAMS[ k ] ]);
	}
	else if ( FLAGS[K] == 1 )
	{
		fileName = argv[ PARAMS[ K ] ];

		statut = validation_Nom_Fichier(fileName);

		//	si nom de fichier invalide
		if ( statut == 1 )
		{
			warn("Erreur cli_Chiffrement() : %s est un nom de fichier\n"
					"invalide. Pour rappel, ce fichier doit finir avec l'extension\n"
					"'.txt' et appartenir au répertoire courant.\n", argv[ PARAMS[ K ] ]);
			free(messageVig);
			free(clef);
			messageVig = NULL;
			clef = NULL;
			return NULL;
		}

		
		clef = lireFichier(fileName, clef, &lenClef);

		if ( clef == NULL )
		{
			warn("Erreur cli_Chiffrement() : lecture du fichier %s échouée.\n",
					fileName);
			free(clef);
			free(messageVig);
			messageVig = NULL;
			return NULL;
		}
	}
	else
	{
		warn("Erreur cli_Chiffrement() : ni -k ni -K activés. Revoir checkInputs.c\n"
				"IMPERATIVEMENT\n");
		free(messageVig);
		free(clef);
		messageVig = NULL;
		clef = NULL;
		return NULL;
	}


	//	==== DECHIFFREMENT ====
	char * output = (char *)malloc(sizeof(char) * lenMessageVig);

	if ( output == NULL )
	{
		free(output);
		free(messageVig);
		messageVig = NULL;
		free(clef);
		clef = NULL;
		return NULL;
	}

	for ( int loop = 0 ; loop < lenMessageVig && messageVig[loop] != '\0' ; ++loop)
	{
		output[loop] = encrypt(messageVig[loop], clef[loop % lenClef]);
	}

	output[lenMessageVig] = '\0';

	//	libération de messageVig et clef s'ils ont été alloués
	free(messageVig);
	messageVig = NULL;
	free(clef);
	clef = NULL;
	
	return output;
}






/*	CLI_GENERERCLEF()
 *
 *	Génère une clé de longueur donnée par l'utilisateur.
 *
 *	PARAMETRE :
 *		argv[]
 *
 *	RETOURNE :
 *		clef : si succès
 *		NULL : si erreur
 */
char* cli_GenererClef(char* argv[])
{
	int lenClef;
	char* entree;

	entree = argv[ PARAMS[ g ] ];

	//	==== VALIDATION ====
	
	if ( (lenClef = estInteger(entree)) == -1 )
	{
		warn("Erreur cli_GenererClef() usage : entrée invalide, le paramètre de -g\n"
				"devrait être un nombre entier positif inférieur à MAXLEN (= %d).\n",
				MAXLEN);
		return NULL;
	}


	//	==== GENERATION ====
	char * clef = genererClef(lenClef);

	//	vérification de succès
	if ( clef == NULL )
	{
		warn("Erreur cli_GenererClef() : génération de clé échouée.\n");
		return NULL;
	}

	return clef;
}
