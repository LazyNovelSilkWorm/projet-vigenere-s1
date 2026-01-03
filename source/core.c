#include <stdio.h>
#include <stdlib.h>

#include "headers/variables.h"




/*
 * 		Ici sont définies et créées les fonctions au coeur du projet :
 * 		chiffrer, déchiffrer et générer. Ces fonctionnalités sont les
 * 		actions principales que doit exécuter le projet.
 */

char encrypt(char enMessage, char key);
char decrypt(char deCypher, char key);
char* genererClef(int length);


//int main(int argc, char* argv[])
//{
	//char result, origin;

//	++argc;
//	if (argv[1][0] == 'e')
//	{
//		printf("%c\n", encrypt(argv[2][0], argv[3][0]));
//	}
//	else if (argv[1][0] == 'd')
//	{
//		printf("%c\n", decrypt(argv[2][0], argv[3][0]));
//	}
//
	/*
	printf("message = %c, key = %c\n", TESTMES, TESTKEY);
	//test encrypt()
	result = encrypt(TESTMES, TESTKEY);
	printf("result = %c\n", result);

	origin = decrypt(result, TESTKEY);
	printf("original = %c\n", origin);
	*/
//	return 1;
//}





/* encrypt()
 *
 * Chiffre un caractère avec le caractère de clé fourni.
 *
 *	PARAMETRES :
 * 		- enMessage : caractère de message à chiffrer
 * 		- key : caractère de la clé associé
 *
 * 	RETOURNE :
 * 		- enCypher : caractère de message chiffré
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


/* decrypt()
 *
 * Déchiffre un caractère avec le caractère de clé fourni.
 *
 * 	PARAMETRES :
 * 		- deCypher : caractère de message à déchiffrer
 * 		- key : caractère de la clé associé
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


/* genererClef()
 *
 * Génère une clé aléatoire de longueur length.
 *
 * 	PARAMETRE :
 * 		- length : longueur de la clé, integer strictement positif
 * 	
 * 	RETOURNE :
 * 		- key : clé générée aléatoirement. Si erreur retourne NULL
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
