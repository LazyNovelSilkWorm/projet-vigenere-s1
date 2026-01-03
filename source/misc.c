#include <stdio.h>

void printHelp(void){	
	
	char tab[] = 
		"Usage:	./Vigenere [action][option] ...  [argument]\n"
		"	./Vigenere\n"
		"\n"
		"Chiffre ou déchiffre lettre par lettre un message par substitution à l'aide\n"
		"d'une clé de chiffrement\n"
		"Utilisez les options correspondantes si il n'y a pas de tri associé\n\n"
		"Les arguments obligatoires pour les options longues sont également obligatoires\n pour les options courtes\n"

		"\nACTIONS :\n"
		"	-c\n"
		"\tChiffrer le message\n"
		"	-d\n"
		"\tDéchiffrer le message\n"
		"	-g [nombre_de_caractères]\n"
		"\t\tgénère une clé de chiffrement de la longueur donnée\n"

		"\nOPTIONS :\n"
		"Ces options sont nécessaires après les actions -c et -d.\n"
		"Exemple :	./Vigenere -[cd] -i [message] -k [clef]\n"
		"		./Vigenere -[cd] -I [fichier] -K [fichier]\n"
		"		./Vigenere -[cd] -i [message] -K [fichier]\n"
		"		./Vigenere -[cd] -I [fichier] -k [clef]\n"
		"	-i [message]\n"
		"\t\tle message à chiffrer/déchiffrer est mis directement dans l'appel de fonction\n"
		"	-I [nom_du_fichier]\n"
		"\t\tle message à chiffrer/déchiffrer est dans le fichier donné\n"
		"	-k [chaine_clé]\n"
		"\t\tla clé pour chiffrer/déchiffrer mise directement dans l'appel de la fonction\n"
		"	-K [nom_du_fichier]\n"
		"\t\tla clé pour chiffrer/déchiffrer est dans le fichier donné\n"

		"\nSORTIE :\n"
		"	-o [nom_du_fichier]\n"
		"\t\tmets le résultat du chiffrement/déchiffrement dans le fichier texte du nom\n"
		"\t\tdonné\n"
		"	-h\n"
		"\t\taffiche le menu d'aide\n"
		"	-v\n"
		"\t\taffiche la version du programme\n"
		"\n"
		"Si aucune option n'est mise, un menu déroulant permet à l'utilisateur\n"
		"d'intéragir par eux-même avec le programme.\n"
		"\n"
		"VALIDITES:\n"
		"\tUn nom de fichier doit s'écrire sous la forme <nom du fichier>.txt, sinon\n"
		"\til ne sera pas considéré comme valide\n"
		"\n"
		"\n"
		"EXAMPLES :\n"
		"\tLancez l'executable ./demonstrationLigneCommande.sh afin d'avoir un\n"
		"\taperçu des capacités de ce projet.\n"
		"\n"
		"AUTEURS :\n"
		"\t•Henry ROBERT <henry1.robert@epita.fr>\n"
		"\t•Gabriel SICCARDI <gabriel.siccardi@epita.fr>\n"
		"\t•Maeli COQUELLE <maelie.coquelle@epita.fr>\n"
		"\t•Maxime WILT <maxime.wilt@epita.fr>\n";
	printf("%s", tab);
}

//int main(void)
//{
//	printHelp();
//	return 0;
//}
