/*=============================================================================
 *                          COEUR DU PROJET
 *=============================================================================
 *
 *      Ce module contient les fonctions au coeur du projet Vigenère. Celles-ci
 *  permettent de chiffrer ou déchiffrer un caractère, ou de générer une clé de
 *  longueur donnée. Ce sont les fonctionalités principales du projet.
 */




#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/variables.h"





char encrypt(char enMessage, char key);
char decrypt(char deCypher, char key);
char* genererClef(int length);







/* ENCRYPT()
 *
 * Chiffre un caractère avec le caractère de clé fourni.
 *
 *	PARAMETRES :
 * 		- char enMessage :
 * 		    Caractère de message à chiffrer
 * 		- char key :
 * 		    Caractère de la clé associé
 *
 * 	RETOURNE :
 * 		- char enCypher : caractère de message chiffré
 */
char encrypt(char enMessage, char key)
{
	char enCypher;

	/*	On assigne les caractères à leur position dans l'alphabet */
	enMessage -= 65;
	key -= 65;

	enCypher = (key + enMessage) % 26;
	enCypher += 65;

	return enCypher;
}


/* DECRYPT()
 *
 * Déchiffre un caractère avec le caractère de clé fourni.
 *
 * 	PARAMETRES :
 * 		- deCypher :
 * 		    Caractère de message à déchiffrer
 * 		- key :
 * 		    Caractère de la clé associé
 *
 * 	RETOURNE :
 * 		- deMessage : caractère de message déchiffré
 */
char decrypt(char deCypher, char key)
{
	char deMessage;

	// we set the variables to their position in the alphabet
	deCypher -= 65;
	key -= 65;

	deMessage = (deCypher - key + 26) % 26; //we add 26 to always have a positive result
	deMessage += 65;

	return deMessage;
}


/* GENERERCLEF()
 *
 * Génère une clé aléatoire de longueur length.
 *
 * 	PARAMETRE :
 * 		- int length : 
 * 		    Longueur de la clé, integer strictement positif
 * 	
 * 	RETOURNE :
 * 		- char key[] : 
 * 		    Clé générée aléatoirement. Si erreur retourne NULL
 */
char* genererClef(int length)
{
	int i;

	i = 0;
	//	Vérifier que la longueur demandée est valide
	if (length <= 0 || length > MAXLEN)
	{
		return NULL;
	}

	//	Allouer l'espace pour la clé (+1 pour le '\0')
	char *key = malloc((length + 1) * sizeof(char));
	if (!key)
	{
		free(key);
		return NULL;
	}
    srand(time(NULL));

	//	Remplir la clé avec des lettres majuscules aléatoires
	for (i = 0 ; i < length ; i++)
	{
		key[i] = 'A' + (rand() % 26);
	}

	//	Terminer la chaîne
	key[length] = '\0';

	//	Retourner la clé générée
	return key;
}
