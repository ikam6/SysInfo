#!/bin/bash

##########################################################
##########################################################
## INITIALISATION
# les 3 arguments sont ecrit directement dans le shell tel que
# $0 sera le nom du fichier
# $1 le répertoire dans lequel se trouvent les images
# $2 le répertoire dans lequel il faut écrire les images
# $3 la résolution de l’image désirée (argument optionnel)

# echo -e permet les retours à la ligne "\n"
echo -e "\nBonjour, vous avez lancé $0 et \nvotre path est $1"

if [ ! -d $2 ]
then
  echo -e "\n création de $2"
  mkdir $2
else
  echo -e "\n $2 existe"
fi

##########################################################
##########################################################
## Aller dans le répertoire $1
cd $1
echo $3
echo

# # Affichier ce qu'il y a dans le répertoire:
# echo -e "\n Voici le contenu du répertoire :\n"
# ls -la

##########################################################
##########################################################
# trouver les fichiers images grace à file (MIME)

# if [`file -I * | egrep "image/"`]
# then
#   echo -e "\n C'est une image!"
# else
#   echo -e "\n Ce n'est pas une image!"
# fi

mkdir ./tmp
cp *.* ./tmp
cd ./tmp
#cp * $(echo * | tr -d [\ \"\'])

echo

for f in *
do
  mv -v "$f" "$(echo $f | tr -d [\ \"\'])"
done

# liste_images=$(file -I * | egrep "image/" | cut -d : -f 1)
# echo $liste_images
#
# for image in *
# do
#   if (! $(file -I image | egrep "image/" | cut -d : -f 1))
#   then
#     echo





liste_images=$(file -I * | egrep "image" | cut -d : -f 1)
for f in $liste_images
do
        echo "Convert sur : $f"
        convert "$f" -resize $3 "${f%.*}.png"
        mv -f *.png $2 #-i pour demander si ecrire par dessus, -f ne demande pas
done

cd ..
rm -rfv ./tmp
