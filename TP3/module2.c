#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define TAILLE_MAX 1000


// optionFichier : -f = 11 et rien = 10; optionDigest : -t = 21 et rien = 20
void choixHash(int optionFichier, int optionDigest, char* text, char* digest) {
    switch(optionFichier){
        case 11:
        //
        switch(optionDigest){
            case 21:
            // fichier avec digest specifique
            //char text[] = lectureFichier(fichier);
            // FILE* fichier = NULL;
            // char text[TAILLE_MAX] = "";
            // fichier = fopen(fichier, "r");
            // if (fichier != NULL){
            //     fgets(text, TAILLE_MAX, fichier);
            //     fclose(fichier);
            // }
            calculHash(text, digest);
            break;
            case 20:
            // fichier avec sha1
            //char text[] = lectureFichier(fichier);
            // FILE* fichier = NULL;
            // char text[TAILLE_MAX] = "";
            // fichier = fopen(fichier, "r");
            // if (fichier != NULL){
            //     fgets(text, TAILLE_MAX, fichier);
            //     fclose(fichier);
            // }
            calculHash(text, "sha1");
            break;
        }
        break;
        case 10:
        //
        switch(optionDigest){
            case 21:
            // string avec digest specifique
            calculHash(text, digest);
            break;
            case 20:
            // string avec sha1
            calculHash(text, "sha1");
            break;
        }
        break;
        default :
        printf("Il y a un problème avec votre entrez!\n");
        break;
    }
}


void calculHash(char* message, char* digest) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    char text[TAILLE_MAX];
    strcpy(text, message);
    unsigned char md_value[EVP_MAX_MD_SIZE];
    int md_len, i;

    md = EVP_get_digestbyname(digest);

    if(!md) {
        printf("Digest non connu : %s\n", digest);
        exit(1);
    }

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, text, strlen(text));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    printf("Le resultat du digest est : \n");
    for (i = 0; i < md_len; i++)
    printf("%02x", md_value[i]);
    printf("\n");
}
