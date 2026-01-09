/*=============================================================================
 *                              MISCELLANEOUS
 *=============================================================================
 *
 *      Contient le menu d'aide pour le projet, qui se présente de façon simil-
 *  -aire à un $man, et la version du programme.
 */




#include <stdio.h>

void printHelp(void){	
	
	char tab[] = 
        "NAME :\n"
        "\tVigenere - outil cryptographique du chiffrement Vigenère\n"
        "\n"
        "SYNOPSIS :\n"
		"\t./Vigenere <operation> [option] ...  [argument]\n"
		"\t./Vigenere\n"
		"\n"
        "DESCRIPTION :\n"
		"\tChiffre ou déchiffre lettre par lettre un message par substitution à l'aide\n"
		"\td'une clé de chiffrement. Le décalage est décidé par le caractère\n"
        "\trespectif de la clé de chiffrement.\n"
        "\n"
        "\tCe projet se divise en deux parties fonctionnelles. Lors du premier rendu\n"
        "\tseule la version du menu était implémentée. Celle-ci est utilisée en\n"
        "\tn'ajoutant aucune option après l'appel de l'outil, et est la version\n"
        "\tla plus simple à utiliser si l'utilisateur n'est pas habitué à la ligne\n"
        "\tde commande.\n"
        "\n"
        "\tAvec la version du rendu final, il est maintenant possible d'utiliser\n"
        "\tl'outil en ligne de commande, afin d'automatiser le processus au sein d'un\n"
        "\tscript ou programme.\n"
        "\n"
        "\tLes chiffres ne sont plus ignorés et oubliés. chaque chiffre est converti\n"
        "\ten leur forme alphabétique. Par exemple, '2' deviens 'DEUX', et '31' deviens\n"
        "\t'TROISUN'.\n"
        "\n"
		"OPERATIONS :\n"
		"\t-c <option message> <option clé>\n"
		"\t\tChiffrer le message avec la clé donnés en option.\n"
        "\n"
		"\t-d <option message> <option clé>\n"
		"\t\tDéchiffrer le message avec la clé donnés en option.\n"
        "\n"
		"\t-g <nombre_de_caractères>\n"
		"\t\tGénèrer une clé de chiffrement de la longueur donnée.\n"
        "\n"
		"OPTIONS D'ENTRÉE (APPLIQUER À -c ET -d) :\n"
		"\tCes options sont nécessaires après les actions -c et -d.\n"
		"\tExemple :\t./Vigenere -[cd] -i <message> -k <clef>\n"
		"\t\t\t./Vigenere -[cd] -I <fichier> -K <fichier>\n"
		"\t\t\t./Vigenere -[cd] -i <message> -K <fichier>\n"
		"\t\t\t./Vigenere -[cd] -I <fichier> -k <clef>\n"
        "\n"
		"\t-i <message>\n"
		"\t\tLe message à chiffrer/déchiffrer est mis directement dans l'appel de\n"
        "\t\tla fonction entre guillemets.\n"
        "\n"
		"\t-I <nom_du_fichier>\n"
		"\t\tLe message à chiffrer/déchiffrer est dans le fichier donné en\n"
        "\t\toption.\n"
        "\n"
		"\t-k <chaine_clé>\n"
		"\t\tLa clé pour chiffrer/déchiffrer mise directement dans l'appel de la\n"
        "\t\tfonction entre guillemets.\n"
        "\n"
		"\t-K <nom_du_fichier>\n"
		"\t\tLa clé pour chiffrer/déchiffrer est dans le fichier donné en\n"
        "\t\toption.\n"
        "\n"
        "OPTION SORTIE :\n"
		"\t-o <nom_du_fichier>\n"
		"\t\tMets le résultat du chiffrement/déchiffrement dans le fichier texte du nom\n"
		"\t\tdonné en option.\n"
        "\n"
		"\t-h\n"
		"\t\taffiche le menu d'aide.\n"
        "\n"
		"\t-v\n"
		"\t\taffiche la version du programme. (Marche le mieux en plein écran).\n"
		"\n"
		"\tSi aucune option n'est mise, un menu déroulant permet à l'utilisateur\n"
		"\td'intéragir par eux-même avec le programme.\n"
		"\n"
		"VALIDITES:\n"
		"\tUn nom de fichier doit s'écrire sous la forme <nom du fichier>.txt, sinon\n"
		"\til ne sera pas considéré comme valide.\n"
		"\n"
		"\n"
		"EXEMPLES :\n"
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





void version(void) {

	printf("             NPPPPPPPP\n");
	printf("           POPPPI CNPPPP\n");
	printf("          PPPL        PQPL\n");
	printf("         OPP           PPQ\n");
	printf("         OOO            PPQ\n");
	printf("        JPOK            PPP\n");
	printf("        GPPL            PPP         KQQQ\n");
	printf("    OOOOPPPPPPPPPPPPPPPPPPPPQQPPQQQQQ  PRQ               RRRRRS              \033[38;5;202mvigenere-tool\033[0m\n");
	printf("    OOOOOPPPPPPPPPPPPPPPPPPPPQQQQQQQQ  NQP      PRRRRRRRRRL  QR             --------------------------------\n");
	printf("    OOOOPPPPPPPPPPPPPPPPPPQI        PQQQM     QRQRP      RRRRRR              \033[34mAlgorithm:\033[0m Vigenere Cipher\n");
	printf("    OOOOPPPPPPPPPPPPPPPPPPPQ               QQRQR  O                          \033[34mVersion:\033[0m 1.0.0\n");
	printf("    OOOOPPPPPPPPPPPPPPPPPPPPQQQQQQQQQQN NQQQQH  HOOPM         PRRSRQ         \033[34mPlatform:\033[0m Linux\n");
	printf("    OOOOPPPPPPPPPPPPPPPO              QQQQQQK     MPPPPQQQQQRRRO  SR         \033[34mLanguage:\033[0m C\n");
	printf("    OOOOPPPPPPPP   NPPP            QQQQQ  NRRQ                RRRRSS         \033[34mPublication date:\033[0m January 2025\n");
	printf("    MOOOPPPPPPPF    PPPPQQPPPQQQQQQQQN      QQRQ                PO           \033[34mAuthors:\033[0m Henry\n");
	printf("     OOOPPPPPPPPN  PPPPPPPPLLLMMMMM           RQRQ                            	     Gabriel\n");
	printf("     NOOOPPPPPPPP GPPPPPPQP          QQQQQR     QRRR              SSSSRO      	     Maxime\n");
	printf("       POPPPPPPPPPPPPPPPPPPQPQQQQQQQQQP  MQ       RRRRRRRRRRRRRRSRS   SS      	     Maelie\n");
	printf("        GPPOPPPPPPPPPPPPPPQ          QQRQQQ                       SSSSRS     \033[34mUsage:\033[0m Encrypt / Decrypt\n");
	printf("             MOOOOOOOOI     \033[38;5;202m__      ___                   __\033[0m\n");
	printf("                		  \033[38;5;202m\\ \\    / (_)                  \\_\\ \033[0m         \033[34mvigenere -h for more information\033[0m\n");
	printf(" 		   \033[38;5;202m\\ \\  / / _  __ _  ___ _ __   ___ _ __ ___\033[0m\n");
	printf(" 		    \033[38;5;202m\\ \\/ / | |/ _` |/ _ \\ '_ \\ / _ \\ '__/ _ \\\033[0m\n");
	printf(" 		     \033[38;5;202m\\  /  | | (_| |  __/ | | |  __/ | |  __/\033[0m\n");
	printf(" 		      \033[38;5;202m\\/   |_|\\__, |\\___|_| |_|\\___|_|  \\___|\033[0m\n");
	printf("      			               \033[38;5;202m__/ |               \033[34mENCRYPTED●\033[0m\n");
	printf("    				      \033[38;5;202m|____/\033[0m\n");




}

// \033[34m pour bleu
// \033[0m pour reset couleur
// \033[38;5;202m pour orange
