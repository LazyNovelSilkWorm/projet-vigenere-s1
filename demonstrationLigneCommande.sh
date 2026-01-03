#! /bin/env bash

./application.sh

echo "Ceci est une série de tests présentant la fonctionnalité 'ligne de commande'
du projet."

printf "\n\n"

echo "______________________________________________________________"
echo "Générer une clé de longueur 79 dans un fichier nommé key.txt :"
printf "\n\n"

echo "	$ ./Vigenere -g 79 -o key.txt"
./Vigenere -g 79 -o key.txt

printf "\n\n"
echo "cat key.txt : "
cat key.txt

sleep 1.5

printf "\n\n"

echo "______________________________________________________________"
echo "Chiffrer le message 'Hello World' avec la clé générée et le stocker dans un
fichier nommé Message-Chiffré.txt"
printf "\n\n"
echo "	$ ./Vigenere -ci \"HelloWorld.\" -K key.txt -o Message-Chiffré.txt"

./Vigenere -ci "Hello World." -K key.txt -o Message-Chiffré.txt

printf "\n\n"
echo "cat Message-Chiffré.txt :"
cat Message-Chiffré.txt


printf "\n\n"

sleep 1.5

echo "______________________________________________________________"
echo "Déchiffrer le message chiffré précédemment avec la même clé sans le stocker :"
printf "\n\n"

echo "	$ ./Vigenere -cI Message-Chiffré.txt -K key.txt"
./Vigenere -cI Message-Chiffré.txt -K key.txt

printf "\n\n"
echo "Si vous avez besoin d'aide pour utiliser la fonctionnalité ligne de commande\n"
"n'hésitez pas à utiliser './Vigenere -h' pour afficher le menu d'aide.\n"

printf "\n\n"

echo "Fin de la démonstration"
exit 0
