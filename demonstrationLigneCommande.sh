#! /bin/env bash

./application.sh

echo "Ceci est une démonstration présentant la fonctionnalité 'ligne de commande'
ou 'CLI' du projet."

printf "\n\n"
sleep 2.5

echo "______________________________________________________________"
echo "Générer une clé de longueur 42"
printf "\n\n"

echo "	$ ./Vigenere -g 42 -o keyDemo.txt"
./Vigenere -g 42 -o keyDemo.txt

printf "\n\n"
echo "$ cat keyDemo.txt"
cat keyDemo.txt

sleep 3.5

printf "\n\n"

echo "______________________________________________________________"
echo "Message \"The Answer to the Ultimate Question of Life, the Universe, and Everything is 42\""
printf "\n\n"
echo "	$ ./Vigenere -ci \"The Answer to the Ultimate Question of Life, the Universe, and Everything is 42\" -K keyDemo.txt -o Message-Chiffré_Demo.txt"

./Vigenere -ci "The Answer to the Ultimate Question of Life, the Universe, and Everything is 42." -K keyDemo.txt -o Message-Chiffré_Demo.txt

printf "\n\n"
echo "cat Message-Chiffré_Demo.txt :"
cat Message-Chiffré_Demo.txt


printf "\n\n"

sleep 3.5

echo"\n"
echo "______________________________________________________________"
echo "Déchiffrer le message chiffré précédemment avec la même clé sans le stocker :"
printf "\n\n"

echo "	$ ./Vigenere -dI Message-Chiffré_Demo.txt -K keyDemo.txt"
./Vigenere -dI Message-Chiffré_Demo.txt -K keyDemo.txt -o Message-Déchiffré_Demo.txt

printf "\n\n"
echo "résultat :"
cat Message-Déchiffré_Demo.txt

printf "\n\n"
echo "Si vous avez besoin d'aide pour utiliser la fonctionnalité ligne de commande\n"
"n'hésitez pas à utiliser './Vigenere -h' pour afficher le menu d'aide.\n"

printf "\n\n"

echo "Fin de la démonstration"
exit 0
