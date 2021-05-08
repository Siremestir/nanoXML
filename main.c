#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* mon_fichier;
char mon_caractere;

void passer_espace(){
    while(mon_caractere == ' ' || mon_caractere == '\t' || mon_caractere == '\n' || mon_caractere == '\r'){
        mon_caractere = fgetc(mon_fichier);
    }
}

void amorcer(){
    mon_fichier = fopen("exemples.txt", "r");
    if(mon_fichier == NULL){
        perror("Fichier introuvable !\n");
        exit(-1);
    }
    mon_caractere = fgetc(mon_fichier);
    passer_espace();    
}

void lire(char caractere){
    if(mon_caractere == caractere){
        printf("%c", mon_caractere);
        mon_caractere = fgetc(mon_fichier);
    }else{
        printf("erreur de syntaxe : caractere attendu : %c / caractere trouve %c\n", caractere, mon_caractere);
        exit(-2);
    }
}

void texte_enrichi(){
    document();
    annexes();
}

void document(){
    debut_doc();
    contenu();
    fin_doc();
}

void debut_doc();

void fin_doc();

void annexes(){
    //Doit se répéter
    debut_annexe();
    contenu();
    fin_annexe();
}

void debut_annexe();

void fin_annexe();

void contenu(){
    //Doit se répéter
    section();
    //Ou
    titre();
    //Ou
    mot_enrichi();
    //Ou
    liste();
}

void section(){
    debut_section();
    contenu();
    fin_section();
}

void debut_section();

void fin_section();

void titre(){
    debut_titre();
    texte();
    fin_titre();
}

void debut_titre();

void fin_titre();

void liste(){
    debut_liste();
    //Doit se répéter
    item();

    fin_liste();
}

void debut_liste();

void fin_liste();

void item(){
    debut_item();
    //Doit se répéter
    liste_texte();
    //Ou
    texte_liste();

    fin_item();
}

void debut_item();

void fin_item();

void liste_texte(){
    liste();

    texte_liste();
    //Ou
    epsilon();
}

// Je doute que ce soit une vraie fonction mais on verra
void epsilon();

void texte_liste(){
    texte();

    liste_texte();
    //Ou
    epsilon();
}

void texte(){
    //Doit se répéter
    mot_enrichi();
}

void mot_enrichi(){
    mot_simple();
    //Ou
    mot_important();
    //Ou
    retour_a_la_ligne();
}

void retour_a_la_ligne();

void mot_important(){
    debut_important();
    //Doit se répéter
    mot_simple();

    fin_important();
}

void debut_important();

void fin_important();

void mot_simple();

void lire_mot_simple();