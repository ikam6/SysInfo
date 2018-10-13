#!/bin/bash

# # demander les 3 arguments
# echo "Bonjour, "
# echo "Veuillez indiquer dans quel répertoire se trouvent les images : "
# read pathFrom
# echo "Veuillez indiquer dans quel répertoire il faut écrire les images : "
# read pathTo
# read -p "Veuillez indiquer la résoluation de l'image désirée (4 caractère max): " -n 4 resolutionImage
# # pour tester :
# # echo -e "Les deux paths sont : \n$pathFrom \net \n$pathTo"

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

# test -d $2
# echo $?

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

# # Affichier ce qu'il y a dans le répertoire:
# echo -e "\n Voici le contenu du répertoire :\n"
# ls -la

##########################################################
##########################################################
# trouver les fichiers images grace à file (MIME)

# if [ file -i = MIME ]
# then
#   echo -e "\n C'est une image!"
# else
#   echo -e "\n Ce n'est pas une image!"
# fi

# file -I * | egrep "image"
#
# for f in liste_images
# do
#   convert ./"$f" ./"${f%.*}.gif"
# done

liste_images=`file -I * | egrep "image/" | cut -d : -f 1`

for f in $liste_images
do
        echo "Image trouvé : $f"
        convert "$f" -resize $3 "${f%.*}.png"
        mv -f *.png $2 #-i pour demander si ecrire par decu, -f ne demande pas
done
