#define SIZE_BUFFER 64

#include "t_element.h"

FILE *mon_fichier;
char mon_caractere;
char buffer[SIZE_BUFFER];
a_element mon_element;

void init_buffer()
{
    for (int i = 0; i < 64; i++)
    {
        buffer[i] = '\0';
    }
}

void passer_espace()
{
    while (mon_caractere == ' ' || mon_caractere == '\t' || mon_caractere == '\n' || mon_caractere == '\r')
    {
        mon_caractere = fgetc(mon_fichier);
    }
}

void amorcer()
{
    init_buffer();
    mon_fichier = fopen("ex0.xml", "r");
    if (mon_fichier == NULL)
    {
        perror("Fichier introuvable !\n");
        exit(-1);
    }
    mon_caractere = fgetc(mon_fichier);
    passer_espace();
}

void lire(char caractere)
{
    if (mon_caractere == caractere)
    {
        printf("%c", mon_caractere);
        mon_caractere = fgetc(mon_fichier);
    }
    else
    {
        printf("erreur de syntaxe : caractere attendu : %c / caractere trouve %c\n", caractere, mon_caractere);
        exit(-2);
    }
}
/*
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
}*/

int est_mot_simple()
{
    return mon_caractere != ' ' && mon_caractere != '\t' && mon_caractere != '<' && mon_caractere != '\n' && mon_caractere != EOF;
}

int est_tag(char* tag)
{
    int i = 0;
    if (buffer[0] != '\0')
    {
        char old_buffer[SIZE_BUFFER];
        for (int k = 0; k < SIZE_BUFFER; k++)
        {
            old_buffer[k] = '\0';
        }
        while (buffer[i] == tag[i] && i < SIZE_BUFFER)
        {
            old_buffer[i] = buffer[i];
            i++;
        }
        i--;
        init_buffer();
        if (i < 0)
        {
            i = 0;
        }
        for (int j = 0; j < i; j++)
        {
            buffer[j] = old_buffer[j];
        }
    }

    while (1)
    {
        buffer[i] = mon_caractere;
        if (buffer[i] != tag[i])
        {
            return 0;
        }
        else if (strcmp(tag, buffer) == 0)
        {
            mon_caractere = fgetc(mon_fichier);
            return 1;
        }
        mon_caractere = fgetc(mon_fichier);
        i++;
    }
}

void fin_tag(char* tag)
{
    init_buffer();
    int i = 0;
    buffer[i] = mon_caractere;
    while (buffer[i] == tag[i] && tag[i] != '\0')
    {
        i++;
        mon_caractere = fgetc(mon_fichier);
        if (mon_caractere == tag[i] && tag[i] != '\0')
        {
            buffer[i] = mon_caractere;
        }
    }
    if (strcmp(buffer, tag) != 0)
    {
        fprintf(stderr, "Balise incorrecte\n");
        exit(0);
    }
}

void mot_simple()
{
    init_buffer();
    int i = 0;
    while (est_mot_simple())
    {
        buffer[i] = mon_caractere;

        i++;
        mon_caractere = fgetc(mon_fichier);
    }
    char *mot = (char *)malloc(sizeof(char) * SIZE_BUFFER);
    strncpy(mot, buffer, SIZE_BUFFER);
    mon_element = nv_element(mot, "mot_simple");
}
/*
int est_important()
{
    init_buffer();
    char *important = "<important>";
    int i = 0;
    while (1)
    {
        buffer[i] = mon_caractere;
        if (buffer[i] != important[i])
        {
            return 0;
        }
        else if (strcmp(important, buffer) == 0)
        {
            mon_caractere = fgetc(mon_fichier);
            return 1;
        }
        mon_caractere = fgetc(mon_fichier);
        i++;
    }
}

void fin_important()
{
    init_buffer();
    char *important = "</important>";
    int i = 0;
    buffer[i] = mon_caractere;
    while (buffer[i] == important[i] && important[i] != '\0')
    {
        i++;
        mon_caractere = fgetc(mon_fichier);
        if (mon_caractere == important[i] && important[i] != '\0')
        {
            buffer[i] = mon_caractere;
        }
    }
    if (strcmp(buffer, important) != 0)
    {
        fprintf(stderr, "Balise important incorrecte");
    }
}*/

void mot_important()
{
    a_element mot_important = nv_element(NULL, "mot_important");
    passer_espace();
    while (mon_caractere != '<')
    {
        mot_simple();
        ajouter_enfant(mot_important, mon_element);
        passer_espace();
    }
    fin_tag("</important>");
    mon_element = mot_important;
}
/*
int est_br()
{
    int i = 0;
    char *br = "</br>";
    if (buffer[0] != '\0')
    {
        char old_buffer[SIZE_BUFFER];
        for (int k = 0; k < SIZE_BUFFER; k++)
        {
            old_buffer[k] = '\0';
        }
        while (buffer[i] == br[i] && i < SIZE_BUFFER)
        {
            old_buffer[i] = buffer[i];
            i++;
        }
        i--;
        init_buffer();
        if (i < 0)
        {
            i = 0;
        }
        for (int j = 0; j < i; j++)
        {
            buffer[j] = old_buffer[j];
        }
    }

    while (1)
    {
        buffer[i] = mon_caractere;
        if (buffer[i] != br[i])
        {
            return 0;
        }
        else if (strcmp(br, buffer) == 0)
        {
            mon_caractere = fgetc(mon_fichier);
            return 1;
        }
        mon_caractere = fgetc(mon_fichier);
        i++;
    }
}*/

void mot_enrichi()
{
    if (est_tag("<important>"))
    {
        mot_important();
    }
    else if (est_tag("</br>"))
    {
        a_element br = nv_element(NULL, "br");
        mon_element = br;
    }
    else if (est_mot_simple())
    {
        mot_simple();
    }
    else
    {
        fprintf(stderr, "N'est pas un mot enrichi");
    }
    a_element mot_enrichi = nv_element(NULL, "mot_enrichi");
    ajouter_enfant(mot_enrichi, mon_element);
    mon_element = mot_enrichi;
}

void texte()
{
    a_element texte = nv_element(NULL, "texte");
    //Quelle condition d'arrêt mettre ???
    while (est_mot_simple() || mon_caractere == '<')
    {
        mot_enrichi();
        ajouter_enfant(texte, mon_element);
        passer_espace();
    }
    mon_element = texte;
}

void titre(){
    a_element titre = nv_element(NULL, "titre");
    texte();
    ajouter_enfant(titre, mon_element);
    mon_element = titre;
    fin_tag("</titre>");
}

int main()
{
    amorcer();
    texte();/*
    a_element tmp = mon_element;
    passer_espace();
    printf("\n%i\n", est_tag("<titre>"));
    titre();
    ajouter_petit_frere(tmp, mon_element);
    mon_element = tmp;*/
    afficher_element(mon_element, 0);

    /*while (mon_element != NULL)
    {
        printf("%s\n", mon_element->type);
        a_element e = mon_element->aine;
        while (e != NULL)
        {
            printf("\t%s\n", e->type);
            a_element e2 = e->aine;
            while (e2 != NULL)
            {
                printf("\t\t%s\n", e2->type);

                e2 = e2->petit_frere;
            }

            e = e->petit_frere;
        }

        mon_element = mon_element->petit_frere;
    }*/
    return 1;
}