#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <err.h>

#include "headers/validation.h"
#include "headers/variables.h"





char* lireFichier(const char* nomFichier, char* contenuFichier, int* lenContenuAddr);
int ecrireDansFichier(const char* nomFichier, const char* contenu);





/*	LIREFICHIER()
 *
 *	Extrait le contenu d'un fichier
 *
 *	PARAMETRE :
 *		- nomFichier[]
 *
 *	RETOURNE :
 *		- buffer :
 *			le contenu du fichier
 *		- NULL :
 *			échec
 */
char* lireFichier(const char* nomFichier, char* contenuFichier, int* lenContenuAddr)
{
	char c;
	//char * contenuFichier = (char*)malloc(sizeof(char));
    FILE* f = fopen(nomFichier, "r");
    if (f == NULL)
    {
        warn("Erreur : impossible d'ouvrir %s\n", nomFichier);
		//fclose(f);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = malloc(sizeof(char) *(size + 1));
    if (!buffer)
    {
		warn("Erreur: lireFichier() : lecture du fichier %s échouée.\n", nomFichier);
        fclose(f);
		f = NULL;
        return NULL;
    }

    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);

    for (int i = 0; buffer[i]; i++)
    {
		c = buffer[i];
		/*
		 * ENTRER NUMASCII() ICI
		 */
		/*if ( numAscii(targetArray, targetLengthAddr, &c) == 1 )
		 * {
		 * 		break;
		 * }
		 */
		if ( (c = validation_Caractere(c)) != '\0' )
		{
			contenuFichier[*lenContenuAddr] = c;
			++(*lenContenuAddr);
			contenuFichier = realloc(contenuFichier, *lenContenuAddr + 2);
		}

		if ( *lenContenuAddr >= MAXLEN )
		{
			warn("lireFichier() : Attention, la longueur du fichier excède"
					" la limite MAXLEN (= %d). Une part du texte risque d'être"
					" ignorée.\n", MAXLEN);
			break;
		}
    }
    contenuFichier[*lenContenuAddr + 1] = '\0';

	
	free(buffer);
	buffer = NULL;

    return contenuFichier;
}


/*	ECRIREDANSFICHIER()
 *
 *	Ecrit dans un fichier.
 *
 *	PARAMETRES :
 *		- nomFichier
 *		- contenu
 *			contenu à écrire
 *
 *	RETOURNE :
 *		0	succès
 *		1	échec
 */
int ecrireDansFichier(const char* nomFichier, const char* contenu)
{
	FILE* f = fopen(nomFichier, "w");

	if (!f)
	{
		fclose(f);
		f = NULL;
		fprintf(stderr, "Erreur : impossible d'écrire dans %s\n", nomFichier);
		return 1;
	}

	fprintf(f, "%s", contenu);
	fclose(f);

	return 0;	//	succès
}


