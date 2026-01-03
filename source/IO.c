#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "headers/validation.h"
#include "headers/fichier.h"
#include "headers/variables.h"



char * getFileName(char* inputFileName);
char * getFromFile(char targetArray[], int* targetLengthAddr);
char * getFromUser(char targetArray[], int* targetLengthAddr);
int saveToFile(char outputArray[]);
/*
int main(int)
{
	char* message = (char *)malloc(sizeof(char));
	int mesLen = 0;
	
	if (message == NULL)
	{
		err(2, "DEBUG : allocation mémoire 'message' echouée.\n");
	}
	getFromFile(message, &mesLen);
	printf("message = %s\n", message);
	printf("mesLen = %d\n", mesLen);

	free(message);
	message = NULL;

	return 0;
}
*/



/*	GETFILENAME()
 *
 *	Cette fonction prend de l'utilisateur un nom de fichier valide.
 *
 *	RETOURNE :
 *		- inputFileName[] :
 *			Nom du fichier à remplir. 
 *		- NULL
 *			échec
 */
char * getFileName(char* inputFileName)
{
	int lengthFileName;
	//char * inputFileName = (char *)malloc(sizeof(char));
	char c;

	if ( inputFileName == NULL )
	{
		warn("Erreur : allocation d'inputFileName échouée.\n");
		return NULL;
	}

	//	limitation de la longueur du filename à 80 caractères.
	for ( lengthFileName = 0 ; lengthFileName <= 80 ; ++lengthFileName )
	{
		c = getchar();

		if ( c == '\n' || c == '\0' )
		{
			break;
		}
		//	on n'autorise pas accès à des fichiers en dehors du répertoire courant
		if ( c == '/' )
		{
			fprintf(stderr, "usage : Ce programme ne prend pas de fichier en dehors du"
					"répertoire courant.\n");
			//exit(EXIT_FAILURE);
			return NULL;
		}

		inputFileName = realloc(inputFileName, lengthFileName + 2);

		inputFileName[lengthFileName] = c;
	}

	inputFileName[lengthFileName + 1] = '\0';

	//	validation
	if ( validation_Nom_Fichier(inputFileName) == -1 )
	{
		fprintf(stderr, "usage : nom de fichier entré invalide.\n");
		//exit(EXIT_FAILURE);
		return NULL;
	}

	return inputFileName;
}





/*	GETFROMFILE()
 *
 *	Option où le message ou la clé sont dans un fichier.txt
 *
 *	PARAMETRES :
 *		- char* targetArray
 *		- int* targetLengthAddr
 *
 *	RETOURNE :
 *		0	échec
 *		1	succès
 */
char* getFromFile(char targetArray[], int* targetLengthAddr)
{
	char * fileNameP = (char*)malloc(sizeof(char));
	//char c;
	//char* position;


	if ( fileNameP == NULL )
	{
		warn("Erreur : getFromFile() : allocation fileNameP échouée.\n");
		free(fileNameP);
		free(targetArray);
		fileNameP = NULL;
		targetArray = NULL;
		return NULL;
	}
	if ( targetArray == NULL )
	{
		warn("Erreur : getFromFile() : allocation targetArray échouée.\n");
		free(fileNameP);
		free(targetArray);
		fileNameP = NULL;
		targetArray = NULL;
		return NULL;
	}
	
	fileNameP = getFileName(fileNameP);

	if ( fileNameP == NULL )
	{
		warn("Warning : getFromFile() : entrée du nom de fichier échouée.\n");
		free(fileNameP);
		free(targetArray);
		fileNameP = NULL;
		targetArray = NULL;
		return NULL;
	}

	//	Extraire contenu du fichier
	targetArray = lireFichier(fileNameP, targetArray, targetLengthAddr);


	
	if ( targetArray == NULL )
	{
		warn("Warning : getFromFile() : Extraction du contenu"
			   " du fichier %s echouée.\n", fileNameP);
		free(fileNameP);
		fileNameP = NULL;
		//free(targetArray);
		//targetArray = NULL;
		return NULL;
	}
	
	// libération mémoire de inputFileName
	free(fileNameP);
	fileNameP = NULL;

	// libération des pointeurs
	//free(targetArray);
	//targetArray = NULL;

	return targetArray;
}




/*	GETFROMUSER()
 *
 *	Prend l'entrée de l'utilisateur. Ignore tout caractère
 *	n'appartenant pas à l'alphabet.
 *
 * 	PARAMETRES
 *		- targetArray[] :
 *			le tableau keyArray[] ou inputArray[]
 *		- targetLengthAddr :
 *			pointeur vers la longueur du tableau indiqué
 *
 *	RETOURNE
 *		- targetArray[]
 */
char * getFromUser(char targetArray[], int* targetLengthAddr)
{
	int loop;
	char c;

	for ( loop = 0 ; *targetLengthAddr <= MAXLEN ; ++loop )
	{
		c = getchar();

		/*
		 * ENTRER NUMASCII() ICI
		 */
		/*if (numAscii(targetArray, targetLengthAddr, &c) == 1)
		 * {
		 * 		break;
		 * }
		 */


		if ( c == '\n' || c == '\0' )
		{
			break;
		}

		//	Validation de l'entrée, mise en majuscule
		c = validation_Caractere(c);

		if ( c == '\0' )
		{
			//	On diminue le loop car on ignore ce caractère
			loop--;
			continue;
		}

		//	Réallocation de la mémoire, incrémentation par un
		++(*targetLengthAddr);
		targetArray = realloc(targetArray, *targetLengthAddr + 2);

		targetArray[loop] = c;
	}

	targetArray[*targetLengthAddr + 1] = '\0';

	return targetArray;
}






/*	SAVETOFILE()
 *
 *	Sauve le résultat du programme à un fichier nommé par l'utilisateur. La
 *	fonction demande le nom du fichier.
 *
 *	PARAMETRES :
 *		- outputArray[]
 *
 *	RETOURNE :
 *		0	succès
 *		1	échec
 */
int saveToFile(char outputArray[])
{
	char* fileNameP = (char*)malloc(sizeof(char));
	int status;
	
	//	nom du fichier
	fileNameP = getFileName(fileNameP);

	if ( fileNameP == NULL )
	{
		warn("Erreur : entrée du nom de fichier échouée.\n");
		free(fileNameP);
		fileNameP = NULL;
		return 1;
	}

	//	écriture dans le fichier
	status = ecrireDansFichier(fileNameP, outputArray);

	if ( status == 1 )
	{
		warn("Erreur : écriture dans le fichier %s échouée.\n", fileNameP);
		free(fileNameP);
		fileNameP = NULL;
		return 1;
	}

	free(fileNameP);
	fileNameP = NULL;

	return 0;
}

	
