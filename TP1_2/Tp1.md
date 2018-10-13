# TP 1&2

## 2.2
* La fonction de la commande __'echo'__ est d'écrire l'arguments sur la sortie standard.
* Les paramètres de cette fonction sont __echo [-n] [string]__.
Le paramètres __[-n]__ permets de ne pas afficher le retour à la ligne.
Le paramètre __[string]__ est le texte à afficher.
Exemple : echo "Hello World!"

## 2.3
Pour créer un fichier vide à partir de la ligne de commande, il suffit de faire __> [fileName].txt__

## 2.4
?? Marche pas sur mac ??
--> si equivalent à __open__ permet de lancer la version graphique de notre application. On peut raconter l'histoire de Nautilus et GNOME. @https://www.tecmint.com/nautilus-terminal-an-embedded-terminal-for-nautilus-file-browser-in-gnome/

Si on lance open Documents il va afficher le finder avec notre fichier Documents.

## 2.5
### a)
La commande wc -w permet de compter le nombre de mot qui sont pris d'un fichier et sorties dans la sortie standard.

### b)
La commande head foo.txt -n 6 va afficher la 6ème ligne depuis le début du fichier
Tant que la commande tail foo.txt -n 6 va afficher la 6ème ligne depuis la fin du fichier.

### c)
Oui, le ou1.txt et le ou2.txt ne sera pas les même.
Si foo.txt existe, le out1.txt sera la version trié de foo.txt tandis que out2.txt sera vide
Si foo.txt n'existe pas , le out1.txt sera vide tandis que le out2.txt affichera que sort n'existe pas

### d)
Avec open nomFichier.pdf, le terminal s'execute dans l'application par défaut pour un tel fichier. Il lance l'application en foreground.
Avec open nomFichier.pdf &, le terminal lance l'application demandé mais en background.
