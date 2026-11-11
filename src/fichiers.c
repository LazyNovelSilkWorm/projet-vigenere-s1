/*=============================================================================
 *                          INTERACTIONS FICHIERS
 *=============================================================================
 *
 *      Dans ce module se trouvent les fonctions qui, comme indiqué, intéragis-
 *  -sent avec les fichiers. Cela est pour les lire ou y écrire.
 */






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
 *		- char nomFichier[]
 *		    Nom du fichier à lire
 *
 *	RETOURNE :
 *		- char buffer[] :
 *			Le contenu du fichier
 *		- NULL :
 *			Échec
 */
char* lireFichier(const char* nomFichier, char* contenuFichier, int* lenContenuAddr)
{
	char c;

    //  Ouverture du fichier
    FILE* f = fopen(nomFichier, "r");
    if (f == NULL)
    {
        warn("Erreur : impossible d'ouvrir %s\n", nomFichier);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    //  si le fichier est vide
    if ( size == 0 )
    {
        warn("Erreur : le fichier %s est vide.\n", nomFichier);
        fclose(f);
        f = NULL;
        return NULL;
    }

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

    //  Validation du contenu
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
        if ( c >= '0' && c <= '9' )
        {
            contenuFichier = numEnAscii(contenuFichier, lenContenuAddr, c);
            if ( contenuFichier == NULL )
            {
                return NULL;
            }
        }
        
		if ( (c = validation_Caractere(c)) != '\0' )
		{
			contenuFichier[*lenContenuAddr] = c;
			++(*lenContenuAddr);

			char* tmp = realloc(contenuFichier, *lenContenuAddr + 2);

            if ( tmp == NULL )
            {
                return NULL;
            }

            contenuFichier = tmp;
		}

		if ( *lenContenuAddr >= MAXLEN )
		{
			warn("lireFichier() : Attention, la longueur du fichier %s excède"
					" la limite MAXLEN (= %d). Une part du texte risque d'être"
					" ignorée.\n", nomFichier, MAXLEN);
			break;
		}
    }
    contenuFichier[*lenContenuAddr] = '\0';

	
    //  Libération du buffer
	free(buffer);
	buffer = NULL;

    return contenuFichier;
}


/*	ECRIREDANSFICHIER()
 *
 *	Écrit dans un fichier.
 *  
 *  PARAMETRES :
 *		- char nomFichier[]
 *		    Nom du fichier où écrire
 *		- Contenu
 *			Contenu à écrire
 *
 *	RETOURNE :
 *		- 0 :
 *		    Succès
 *		- 1 :
 *	    	Échec
 */
int ecrireDansFichier(const char* nomFichier, const char* contenu)
{
	FILE* f = fopen(nomFichier, "w");

    //  Vérifier l'ouverture correcte
	if (!f)
	{
		fclose(f);
		f = NULL;
		fprintf(stderr, "Erreur : impossible d'écrire dans %s\n", nomFichier);
		return 1;
	}

	fprintf(f, "%s", contenu);
	fclose(f);

	return 0;	//	Succès
}


