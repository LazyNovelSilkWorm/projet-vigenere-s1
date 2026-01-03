#ifndef VALIDATION_H
#define VALIDATION_H


int validation_Integer(void);
char validation_Caractere(char c);
int validation_Nom_Fichier(char* nomFichier);
char* validationEntree(char* targetArray, int* targetLengthAddr, char* entree);
int estInteger(char* entree);


#endif
