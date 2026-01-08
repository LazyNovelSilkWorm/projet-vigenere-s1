/*  ===========================================================================
 *  VARIABLES
 *  ===========================================================================
 *      Ce fichier contient les variables globales utilisées par le
 *  projet. Certaines, comme MAXLEN et MAXLENKEY peuvent être modifiées afin
 *  d'adapter le programme aux limitations de hardware ou software.
 *
 *      Les suivantes, par contre, sont définies dans ../variables.c et ne
 *  doivent pas être modifiées. Elles permettent au programme d'identifier les
 *  options choisies en mode ligne de commande, de les sauver et de retrouver
 *  éventuel paramètre associé lors de l'exécution.
 */



#ifndef VARIABLES_H
#define VARIABLES_H

// MODIFIABLE
//  Ici sont définies les variables pour les limites de taille. À modifier ici.
#define MAXLEN 1024     //  Longueur de message maximale
#define MAXLENKEY 80    //  Longueur de clé maximale

//  NE PAS MODIFIER
//	Variables utilisées pour accéder à FLAGS et PARAMS
extern int g;
extern int i;
extern int I;
extern int k;
extern int K;
extern int o;
extern int d;
extern int c;
extern int h;

//	Tableaux de compatibilité
extern int FLAGS[];
extern int PARAMS[];

#endif
