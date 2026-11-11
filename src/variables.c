/*=============================================================================
 *                           VARIABLES GLOBALES
 *=============================================================================
 *
 * Voir l'explication dans "checkInputs.c"
 */




//	Variables utilisées pour accéder à FLAGS et PARAMS
//	Ces variables sont nommées après l'option qu'elles représentent.
int g = 0;	//	option -g et son paramètre
int i = 1;	//	option -i et le message
int I = 2;	//	option -I et le nom du fichier contenant le message
int k = 3;	//	option -k et la clé
int K = 4;	//	option -K et le nom du fichier contenant la clé
int o = 5;	//	option -o et le nom du fichier où écrire le résultat
int d = 6;	//	option -d (déchiffrement)
int c = 7;	//	option -c (chiffrement)
int h = 8;	//	option -h



//	Tableaux de compatibilité
int FLAGS[9] = {0};	//	options activées, non activées et incompatibles

int PARAMS[6] = {0};	//	position des arguments dans argv, associées aux
						//	options respectives.
