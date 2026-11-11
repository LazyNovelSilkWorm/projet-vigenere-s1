===========================================================================================
                                CAHIER DE VALIDATION
===========================================================================================




PRINCIPES FONDAMENTAUX :
------------------------
    Dans le développement de cet outil, plusieurs principes ont été choisis. Ceux-ci ont
déterminé la direction du projet.

    1. La ponctuation, espaces et accents ne sont pas gérés par l'outil. Seuls les
        caractères strictement alphanumériques sont chiffrés. Tous les autres seront
        ignorés sans générer d'erreur. Ainsi :
            - message entré :               Hello World!
            - message avant chiffrement :   HELLOWORLD

    2. Les nombres sont convertis dans leur forme alphabétique (exemple : 2 -> "DEUX").
        Puisqu'ils sont gérés individuellement, 10 deviens "ONEZERO". Cette conversion peut
        étendre la longueur du message au delà des limites autorisées par l'outil. Une
        perte des données dépassant la limite aura alors lieu.

    3. Toute écriture à un fichier effacera le contenu déjà présent dans le fichier.

    4. Tout fichier doit IMPÉRATIVEMENT être terminé par l'extension '.txt', et se trouver
        dans le répertoire courant. La présence d'un slash '/' ou l'absence de l'extension
        demandée génèrera une erreur, arrêtant l'exécution du programme. Ce choix a été
        fait afin d'éviter autant que possible que l'utilisateur efface par erreur un
        fichier erroné.

    5. Le projet permet deux modes d'utilisation différents.
        - TUI (Terminal User Interface) :
            Menu d'options, accompagne étape par étape l'utilisateur dans le processus
            d'utilisation de l'outil.
        - CLI (Command Line Interface) : 
            Agit comme un commande linux. Permet d'automatiser l'outil dans un script.

    6. Toute entrée est limitée par défaut à 1024 caractères. Cette limite est controlée
        par la variable globale MAXLEN, qui peut être modifiée dans 
            'source/headers/variables.h'




I| TUI : TERMINAL USER INTERFACE :
-------------------------------
    Le mode TUI est la fonctionalité basique du projet. L'utilisateur lance l'application
ou l'exécutable 'Vigenere'. Cela lui présente le choix d'opérateur. Est-ce que l'objectif
est de :
    - chiffrer un message?          Entrer 'c'.
    - déchiffrer un message?        Entrer 'd'.
    - générer une clé?              Entrer 'g'.
    - besoin d'aide, d'un manuel?   Entrer 'h'.
    - connaître la version?         Entrer 'v'.
toute autre entrée génèrera une erreur.

Les options 'h' et 'v' affichent leur contenu puis terminent l'exécution du programme.

Si l'un des trois premiers opérateurs est choisi, alors il est nécessaire d'entrer des
informations. Dans le cas de la génération d'une clé, il faut entrer un entier strictement
positif. S'il faut chiffrer ou déchiffrer, alors choisir pour le message puis la clé :
    - l'entrée se trouve-t-elle dans un fichier?
        - oui : 'Y/y/<touche entrée>' :
            Entrer le nom du fichier. Il doit être valide selon les principes énoncés au
            début de ce document.
        - non : 'N/n' :
            Entrer le message ou la clé. 


Enfin, la sortie. L'utilisateur est offert le choix d'afficher dans le terminal, ou
de sauver le résultat dans le fichier de son choix.
    - 'Y/y/<touche entrée>' :
        L'utilisateur entre alors un nom de fichier valide. S'il existe, son contenu sera
        entièrement remplacé par le résultat. Sinon le fichier est créé.
    - 'N/n' :
        Le résultat est affiché dans la sortie standard.

Le programme termine alors son exécution normalement.


EXEMPLE D'EXECUTION NORMALE :

Exemple de génération de clé :

```
henry@talos  ~/Documents/[...]/projet-vigenere-s1   main ±  ./Vigenere 
____________________________________________________________________
|	OPERATEUR :
| Voulez-vous :
|	- c : chiffrer un message
|	- d : déchiffrer un message
|	- g : générer une clé
|	- h : afficher le menu d'aide
|  - v : afficher la version
| Entrer une option [c, d, g, h, v] :
| > g
| operateur : g
|___________________________________________________________________
| GENERATION DE CLE :
|	Entrez la longueur de la clé que vous voulez générer. Cette valeur
| doit être un entier strictement supérieur à 0 et inférieur à 80.
| > 80
____________________________________________________________________
|	OUTPUT :
|	Voulez-vous sauver votre résultat dans un fichier (autrement il
|	sera affiché dans le terminal).
|	(Y/n) :
| > n
====================================================================
| Résultat :
|	PINHVAOFIHKSMFANGZCZFJKNAUAFBXJSHYBCYQKIZWALCCZKCDLHNXWPRXUUWFNDDQHBGRLHOMTSQUEU
```



Exemple de chiffrement d'un message entré, avec un clé dans le fichier 'key.txt'. Le
résultat est sauvé dans le fichier 'result.txt' :

```
henry@talos  ~/Documents/[...]/projet-vigenere-s1   main ±  ./Vigenere 
____________________________________________________________________
|	OPERATEUR :
| Voulez-vous :
|	- c : chiffrer un message
|	- d : déchiffrer un message
|	- g : générer une clé
|	- h : afficher le menu d'aide
|  - v : afficher la version
| Entrer une option [c, d, g, h, v] :
| > c
| operateur : c
|___________________________________________________________________
|	CHIFFREMENT :
|	Votre message est-il dans un fichier texte? (format : fichier.txt)
|	(Y/n) :
| > n
| Entrez votre message à chiffrer :
| > Hello World!
|	Votre clé est-elle dans un fichier texte? (format : cle.txt)
|	(Y/n) :
| > 
|	Entrez le nom du fichier :
| > key.txt
____________________________________________________________________
|	OUTPUT :
|	Voulez-vous sauver votre résultat dans un fichier (autrement il
|	sera affiché dans le terminal).
|	(Y/n) :
| > 
|	Entrez le nom du fichier dans lequel sauvegarder. (Attention,
|	si ce fichier existe, le contenu sera effacé) :
| > result.txt
 henry@talos  ~/Documents/[...]/projet-vigenere-s1   main ±  cat result.txt 
UAWCPXAHMK%
```





II| CLI : COMMAND LINE INTERFACE :
----------------------------------
    Le mode CLI ou ligne de commande est la fonctionnalité additionnelle principale du
projet. Elle permet d'exécuter le programme comme une commande linux, facilitant son
automatisation dans un script. Pour démonstration voir 'demonstrationLigneDeCommande.sh'.

Les options et opérateurs sont modulables, selon leur validité des uns avec les autres.
Ainsi, tant que les options nécessaires sont présentes, et qu'elles sont bien suivie par
leur argument, l'ordre importe peu.

Si vous voulez une présentation des opérateurs et options, affichez le menu d'aide.
Cela se fait avec :
    $ ./Vigenere -h | less

(l'affichage en less est plus efficace, et est plus consistent avec son formattage comme
un manuel de commande, mais n'est pas nécessaire).


EXEMPLE D'EXÉCUTION NORMALE :

générer une clé de 10 caractères:
```
$ ./Vigenere -g 10
NWLRBBMQBH
```

générer une clé de 10 caractères et la sauver dans le fichier key.txt :
```
$ ./Vigenere -g 10 -o key.txt
$ cat key.txt
EYUWYRUXZS%
```

chiffrer un message avec key.txt et le sauver dans le fichier secret.txt :
```
$ ./Vigenere -ci "hello World! the answer is 42" -K key.txt -o secret.txt
$ cat secret.txt
LCFHMNIOKVXFYWLJQBQAWDIQPKQL%
```

déchiffrer le secret dans secret.txt :
```
$ ./Vigenere -dK key.txt -I secret.txt
HELLOWORLDTHEANSWERISFOURTWO
```






III| TESTS :
------------
Après le test 1.2, les tests concernant le chiffrement s'appliquent aussi au déchiffrement.


Tests 1 : Concerne les entrées du message (chiffré ou non) et de la clé, que ce soit en 
            TUI ou CLI.
Tests 2 : Concerne la validité d'un message entré. S'applique au message, la clé ou la
            sortie, en TUI ou CLI.
Tests 3 : Concerne la génération d'une clé, en TUI ou CLI.
Tests 4 : Concerne spécifiquement CLI et ses spécifications.
Tests 5 : Concerne spécifiquement TUI et ses spécifications.
Tests 6 : Concerne l'affichage de l'aide et de la version.


| Numéro de |     But du test      |    Entrée    | Sortie Attendue | Résultat |
|   test    |                      |              |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    1.1    | Test nominal         | msg :        | Affichage dans  |          |
|           | msg et clé sans char | "chaussettes"| le terminal :   |    OK    |
|           | spéciaux chiffrement | clé :        | "ULCBWKWXVLW"   |          |
|           |                      | "seches"     |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    1.2    | Test nominal         | msg :        | Affichage dans  |          |
|           | déchiffrement du     | "ULCBWKWXVLW"| le terminal :   |    OK    |
|           | test 1.1             | clé :        | "CHAUSSETTES"   |          |
|           |                      | "seches"     |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    1.3    | Test nominal         | msg :        | Affichage dans  |          |
|           | caractères spéciaux  | "Hermès."    | le terminal :   |    OK    |
|           | msg et clé           | clé :        |   "ZGYQK"       |          |
|           |                      | "Sèches?"    |                 |          |
|           |                      |              |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    1.4    | Test nominal, le     | msg :        | Affichage dans  |          |
|           | msg ou la clé dépas- | "Lorem ...   | le terminal :   |          |
|           | -se la longueur      | semper..."   | "Warning :      |    OK    |
|           | autorisée par défaut | clé :        | longueur de     |          |
|           | (= 1024 caractères)  | "ANSIF...EJ" | l'entrée ...    |          |
|           | Message d'avertis-   |              | risque d'être   |          |
|           | -sement généré.      |              | perdue."        |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    1.5    | Test d'erreur, le    | msg = ""     | Affichage dans  |          |
|           | message ou la clé    |   et / ou    | le terminal :   |    OK    |
|           | est vide.            | clé = ""     | "<entree> vide, |          |
|           |                      |              | vérifiez la     |          |
|           |                      |              | validité de     |          |
|           |                      |              | l'entrée"       |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    1.6    | Test d'erreur, le    | msg = "éèà.É"| Affichage dans  |          |
|           | message ou la clé    |     ou       | le terminal :   |    OK    |
|           | ne contient que des  | clé = ",;:&" | "<entree> vide, |          |
|           | caractères invalides.|              | vérifiez la     |          |
|           |                      |              | validité de     |          |
|           |                      |              | l'entrée"       |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    1.7    | Test nominal :       | msg = "42"   | Le msg devient  |          |
|           | un chiffre est dans  |              | "FOURTWO"       |          |
|           | l'entrée             |              |                 |          |
|           |                      |              |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|           |                      |              |                 |          |
|    2.1    | Test nominal :       | fileName =   | Affichage dans  |          |
|           | Le message est       | "msg.txt"    | le terminal :   |    OK    |
|           | contenu dans un      | clé =        | "ULCBWKWXVL"    |          |
|           | fichier texte valide.| "seches"     |                 |          |
|           |                      |              |                 |          |
|           |                      | $cat msg.txt |                 |          |
|           |                      | -> chaussette|                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    2.2    | Test nominal :       | msg =        | Affichage dans  |          |
|           | La clé est contenue  | "chaussettes"| le terminal :   |    OK    |
|           | dans un fichier texte| fileName =   | "ULCBWKWXVL"    |          |
|           | valide.              | "key.txt"    |                 |          |
|           |                      |              |                 |          |
|           |                      | $cat key.txt |                 |          |
|           |                      | -> seches    |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    2.3    | Test avertissement : | taille de    | Affichage dans  |          |
|           | contenu du fichier   | fichier >    | le terminal :   |    OK    |
|           | supérieur à MAXLEN   | MAXLEN       | "Attention :    |          |
|           |                      |              | longueur du[...]|          |
|           |                      |              | d'être ignorée."|          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|           |                      |              |                 |          |
|    2.4    | Test d'erreur :      | fileName =   | Affichage dans  |          |
|           | le nom de fichier    | "txtfile"    | le terminal :   |          |
|           | entré n'a pas        |              | "usage : txtfile|    OK    |
|           | l'extension '.txt'   |              | n'est pas un    |          |
|           |                      |              | nom de fichier  |          |
|           | message, clé ou      |              | valide. Vérifiez|          |
|           | sortie               |              | qu'il a bien    |          |
|           |                      |              | l'extension     |          |
|           |                      |              | '.txt'          |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    2.5    | Test d'erreur :      | fileName =   | Affichage dans  |          |
|           | le fichier texte ne  | "../txtfile" | le terminal :   |          |
|           | se trouve pas dans   |              | "usage :        |    OK    |
|           | le répertoire        |              | ../txtfile      |          |
|           | courant.             |              | n'est pas un    |          |
|           | Message, clé ou      |              | nom de fichier  |          |
|           | sortie.              |              | valide [...]    |          |
|           |                      |              | courant."       |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    2.6    | Test particulier :   | fileName =   | Éxécution       |          |
|           | le fichier est un    | ".file.txt"  | normale, pas    |    OK    |
|           | fichier caché dans   |              | d'erreur.       |          |
|           | le répertoire        |              |                 |          |
|           | courant.             |              |                 |          |
|           | Message, clé ou      |              |                 |          |
|           | sortie.              |              |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    2.7    | Test d'erreur :      | fileName =   | Affichage dans  |          |
|           | le fichier n'existe  | "locked.txt" | le terminal :   |          |
|           | pas ou ne peut pas   |              | "Erreur :       |    OK    |
|           | être ouvert.         |              | Impossible      |          |
|           | Message ou clé.      |              | d'ouvrir        |          |
|           |                      |              | locked.txt"     |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    2.8    | Test d'erreur :      | fileName =   | Affichage dans  |          |
|           | le fichier ouvert    | "empty.txt"  | le terminal :   |          |
|           | est vide.            |              | "Erreur : le    |    OK    |
|           | Message ou clé.      |              | fichier         |          |
|           |                      |              | empty.txt est   |          |
|           |                      |              | vide."          |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    3.0    | Test nominal :       | taille =     | Clé générée     |          |
|           | générer une clé      | 1 à 1024     | sans erreur     |    OK    |
|           |                      | inclus       |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    3.1    | Test d'erreur :      | taille = 0   | Affichage dans  |          |
|           | l'entrée de la       |              | le terminal :   |          |
|           | taille est 0         |              | "Erreur usage : |    OK    |
|           |                      |              | la longueur de  |          |
|           |                      |              | la clé doit être|          |
|           |                      |              | strictement     |          |
|           |                      |              | supérieure à    |          |
|           |                      |              | zéro."          |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    3.2    | Test d'erreur :      | taille = 1025| Affichage dans  |          |
|           | l'entrée de la taille|              | le terminal :   |          |
|           | est supérieure à la  |              | "Erreur usage : |    OK    |
|           | limite établie par   |              | longueur de la  |          |
|           | MAXLEN (par défaut   |              | clé à générer   |          |
|           | 1024).               |              | 1025 supérieure |          |
|           |                      |              | à MAXLEN..."    |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    4.0    | Test nominal :       |$./Vigenere   | Exécution       |          |
|           | options CLI          | -c ou -d     | normale de      |    OK    |
|           | chiffrement ou       | -i "message" | l'outil.        |          |
|           | déchiffrement        | -k "clé"     |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    4.1    | Test nominal :       |$./Vigenere   | Génération      |          |
|           | options CLI          | -g 20        | d'une clé de    |    OK    |
|           | génération d'une     |              | 20 caractères,  |          |
|           | clé                  |              | affichée dans   |          |
|           |                      |              | le terminal.    |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    4.3    | Test nominal :       |$./Vigenere   | cat result.txt  |          |
|           | options CLI          | <opération>  | -> affiche      |    OK    |
|           | sauver le résultat   | -o result.txt| résultat de     |          |
|           | dans un fichier      |              | l'opération     |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    4.4    | Test d'erreur :      |$./Vigenere   | Affichage dans  |          |
|           | options CLI          | -h ou -v     | le terminal :   |    OK    |
|           | ajouter une option   | <option non  | "checkFlags() : |          |
|           | non valide en        | valide>      | ERROR : option  |          |
|           | cherchant à afficher |              | <option entrée> |          |
|           | le manuel ou la      |              | invalide."      |          |
|           | version (ils ne      |              |                 |          |
|           | prennent pas         |              |                 |          |
|           | d'option).           |              |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    4.5    | Test d'erreur :      |$./Vigenere   | Affichage dans  |          |
|           | opérateur manquant   | -i "message" | le terminal :   |    OK    |
|           | en version CLI, ou   | -K key.txt   | "Erreur :       |          |
|           | invalide.            |              | opérateur       |          |
|           |                      |              | manquant ou     |          |
|           |                      |              | invalide"       |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    4.6    | Test d'erreur :      |$./Vigenere   | Erreur générée  |          |
|           | l'argument néces-    | -cIK msg.txt | arrêt de        |    OK    |
|           | saire à une option   | key.txt      | l'exécution.    |          |
|           | ne la suit pas       |              |                 |          |
|           | dans l'ordre         |              |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    4.7    | Test d'erreur :      |$./Vigenere   | Erreur générée :|          |
|           | option manquante     | -ci message  | "Erreur :       |    OK    |
|           | nécessaire à un      |              | clé ou message  |          |
|           | opérateur            |              | manquants"      |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    4.8    | Test d'erreur :      |$./Vigenere   | Erreur générée :|          |
|           | argument manquant    | -c -i        | "Erreur :       |    OK    |
|           | à un option qui      | -K key.txt   | l'option 2      |          |
|           | en nécessite une     |              | manque un       |          |
|           | [i, I, k, K, o]      |              | argument..."    |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    4.9    | Test particulier :   |$./Vigenere   | Exécution       |          |
|           | tant que une option  | -o result.txt| normale de      |    OK    |
|           | nécessitant un       | -ck seches   | l'outil         |          |
|           | argument en est      | -I msg.txt   |                 |          |
|           | suivie, l'ordre      |              |                 |          |
|           | des options et       |              |                 |          |
|           | opérateurs importe   |              |                 |          |
|           | peu                  |              |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    4.10   | Test particulier :   |$./Vigenere   | Exécution       |          |
|           | les opérateurs -c    | -cI msg.txt  | normale de      |    OK    |
|           | et -d peuvent être   | -k "seches"  | l'outil         |          |
|           | accolés à une option |              |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    4.11   | Test particulier :   | $./Vigenere  | Le dernier mot  |          |
|           | une chaine de        | -ci Ceci est | sera chiffré,   |    OK    |
|           | caractères de plus   | un message   | les autres      |          |
|           | d'un mot n'est pas   | invalide -K  | sont ignorés.   |          |
|           | délimitée par des    | key.txt      | Donc 'message'  |          |
|           | guillemets           |              | sera chiffré.   |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    5.0    | Test d'erreur :      | "[g, c, d, h,| Erreur, arrêt   |          |
|           | Sur une étape du TUI,| v]?"         | d'exécution     |    OK    |
|           | l'utilisateur entre  | > r          |                 |          |
|           | une option invalide  |              |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    6.0    | Test nominal :       |$./Vigenere -v| Affichage dans  |          |
|           | l'utilisateur veut   |              | le terminal de  |    OK    |
|           | afficher la version  |              | la version      |          |
|           | du projet.           |              |                 |          |
|===========|======================|==============|=================|==========|
|           |                      |              |                 |          |
|    6.1    | Test nominal :       |$./Vigenere -h| Affichage dans  |          |
|           | l'utilisateur veut   |              | le terminal du  |    OK    |
|           | afficher un menu     |              | manuel d'aide   |          |
|           | d'aide.              |              | du projet, sous |          |
|           |                      |              | format de man.  |          |
|===========|======================|==============|=================|==========|


    Ces tests ont été lancés avec l'outil Valgrind afin de retirer toutes les fuites et
erreurs de mémoire. Cet objectif est rempli. Autant qu'on a testé, aucune erreur n'est
plus détectée.
