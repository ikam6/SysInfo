#!/bin/bash

##########################################################
##########################################################
## INITIALISATION

# Condition 1/5 :
#  Le script prend trois arguments, deux obligatoires et un optionnel
# 1. le répertoire dans lequel se trouvent les images
# 2. le répertoire dans lequel il faut écrire les images
# 3. la résolution de l’image désirée (argument optionnel)
# Réponse 1/5 :
# les 3 arguments sont ecrit directement dans le shell tel que
# bash $0 $1 $2 $3 avec
# $0 le nom du fichier .sh
# $1 le répertoire dans lequel se trouvent les images
# $2 le répertoire dans lequel il faut écrire les images
# $3 la résolution de l’image désirée (argument optionnel)
# pour $3 on suppose que l'utilisateur entre un code correct !


##########################################################
##########################################################
## FUNCTIONS

controle_repertoire() {
  if [ ! -d $1 ] #attention ici $1 = repertoire d'arrivée et non répertoire de départ
  then
    echo -e "\nCréation de $1\n"
    mkdir $1
  else
    echo -e "\n$1 existe déjà!\n"
  fi
}

normaliser_nom() {
  for f in *
  do
    mv "$f" "$(echo $f | tr -d [\ \'\"])"
  done
}

trier_images() {
  liste_images=$(file -I * | egrep "image" | cut -d : -f 1)
  for f in $liste_images
  do
    convert "$f" -resize $2 "${f%.*}.png" #attention $2=résolution et $1=répertoire d'arrivée
    mv -f *.png $1 #-i pour demander si ecrire par dessus, -f ne demande pas
  done
}

affichage_fin() {
  echo -e "\n------------------\n"
  echo -e "\nScript fait par : \nLienhard Alexia\net\nSmiljkovic Marko\n"
  echo -e "\n------------------\n"
}


##########################################################
##########################################################
## EXECUTION (avec commentaires et réponses aux conditions)

# Message de bienvenu :
echo -e "\nBonjour, vous avez lancé $0 et \nvotre path est $1\n"
# echo -e permet les retours à la ligne "\n"

# Condition 3/5 :
# Si le répertoire d’arrivée n’existe pas, il faut le créer
# Réponse 3/5 :
# Fontion pour vérifier le répertoire d'arrivé et sinon créer
controle_repertoire $2

# Condition 2/5 :
# Les images ne seront pas effacées du répertoire de départ.
# Réponse 2/5 :
# Aller dans le répertoire $1 et creation d'un répertoire
# temportaire pour travailler sur les fichiers sans les
# modifier dans le répertoire de départ

cd $1
echo -e "\nVoici le contenu du répertoire de départ AVANT l'exécution : \n"
ls -la # répertoire de départ devrait être le même à la fin
mkdir ./tmp
cp *.* ./tmp
cd ./tmp

# Condition 4/5 :
# Il faudra supprimer les espaces, apostrophes et guillemets des noms de
# fichiers dans l’image d’arrivée
# Réponse 4/5 :
# Fonction normalisant les noms grâce à $(tr)
normaliser_nom

# Condition 5/5 :
# Seules les images seront copiées quel que soit leur format de départ
# (et leur extension).
# Réponse 5/5 :
# Fonction qui trouve les fichiers images grâce à $(file (MIME)) et
# qui les convertient dans la résolution désirée $3,
# puis les envoient dans le répertoire d'arrivée.
trier_images $2 $3

# Nettoyage du répertoire de départ :
cd ..
rm -rf ./tmp # suppression du répertoire temportaire
echo -e "\nVoici le contenu du répertoire de départ APRES l'exécution : \n"
ls -la # vérifier que le répertoire de départ est le même qu'au début

echo -e "\nVoici donc le contenu de votre répertoire d'arrivée : \n"
cd $2
ls -la
echo

affichage_fin
