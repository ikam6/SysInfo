#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define TAILLE_MAX 1000


// optionFichier : -f = 11 et rien = 10; optionDigest : -t = 21 et rien = 20
// option : -f et -t  = 22, -f et !t = 21, !f et -t = 12, !f et !t = 11
// void choixHash(int option, char* text, char* digest) {
//     switch(option){
//         case 22:
//         calculHash(text, digest);
//         break;
//         case 21:
//         calculHash(text, "sha1");
//         break;
//         case 12:
//         calculHash(text, digest);
//         break;
//         case 11:
//         calculHash(text, "sha1");
//         break;
//         default :
//         printf("Il doit y avoir une erreur dans votre entrée.\n");
//         printf("Merci de relancer le programme.\n");
//         exit(EXIT_FAILURE);
//         break;
//     }
// }


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

    printf("Le resultat pour le message %s du digest %s est : \n", message, digest);
    for (i = 0; i < md_len; i++)
    printf("%02x", md_value[i]);
    printf("\n");
}
