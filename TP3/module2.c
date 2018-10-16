/*--------------------------------------------------------/
    Code fait par :
    Lienhard Alexia
    et
    Smiljkovic Marko
/--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define TAILLE_MAX 1000

// inspiration du code d'exemple dans man EVP_DigestInit :
void calculHash(char* message, char* digest) {

    // initialisation :
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    char text[TAILLE_MAX];
    strcpy(text, message);
    unsigned char md_value[EVP_MAX_MD_SIZE];
    int md_len, i;

    md = EVP_get_digestbyname(digest);

    // controle si le code digest existe
    if(!md) {
        printf("\nDigest non connu : %s\n", digest);
        exit(1);
    }

    // calcul du digest
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, text, strlen(text));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    // Affichage du résultat pour l'utilisateur :
    //printf("\nLe resultat pour le message %s du digest %s est : \n", message, digest);
    for (i = 0; i < md_len; i++)
    printf("%02x", md_value[i]);
    //printf("\n");
}
