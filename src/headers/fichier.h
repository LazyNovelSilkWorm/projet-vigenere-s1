#ifndef LIRE_FICHIER_H
#define LIRE_FICHIER_H

char* lireFichier(const char* nomFichier, char* contenuFichier, int* lenContenuAddr);
int ecrireDansFichier(const char* nomFichier, const char* contenu);
int saveToFile(char output[]);

#endif
