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
}*/

int est_mot_simple()
{
    return mon_caractere != ' ' && mon_caractere != '\t' && mon_caractere != '<' && mon_caractere != '\n' && mon_caractere != EOF
    && mon_caractere != '\r' && mon_caractere != '>';
}

int est_tag(char* tag)
{
    if(strcmp(buffer, tag) == 0)
    {
        return 1;
    }

    int i = 0;
    if (buffer[0] != '\0')
    {
        // cpt = 1;
        // while(buffer[cpt] != '\0')
        // {
        //     cpt++;
        // }
        // int i =0;
        printf("Sauvegarge du buffer %s : ", buffer);
        if (buffer[0] != tag[0]){
            return 0;
        }
        char old_buffer[SIZE_BUFFER];
        for (int k = 0; k < SIZE_BUFFER; k++)
        {
            old_buffer[k] = '\0';
        }
        while (buffer[i] != '\0' && i < SIZE_BUFFER)
        {
            old_buffer[i] = buffer[i];
            i++;
            printf("%c = %c ? ", buffer[i], tag[i]);
        }

        printf("i = %i, old buffer = %s, ", i, old_buffer);
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
        printf("%s\n", buffer);
    }


    while (i < SIZE_BUFFER)
    {
        printf("%c, %s ", mon_caractere, buffer);
        buffer[i] = mon_caractere;
        if (buffer[i] != tag[i])
        {
            printf("pas balise %s\n", tag);
            return 0;
        }
        else if (strcmp(tag, buffer) == 0)
        {
            printf("\n");
            mon_caractere = fgetc(mon_fichier);
            return 1;
        }
        mon_caractere = fgetc(mon_fichier);
        i++;
    }
    return 0;
}

void fin_tag(char* tag)
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
    buffer[i] = mon_caractere;
    while (buffer[i] == tag[i] && tag[i] != '\0')
    {
        mon_caractere = fgetc(mon_fichier);
        i++;
        if (mon_caractere == tag[i] && tag[i] != '\0')
        {
            buffer[i] = mon_caractere;
        }
    }
    if (strcmp(buffer, tag) != 0)
    {
        fprintf(stderr, "Balise %s incorrecte %s, caractère %c\n", tag, buffer, mon_caractere);
        exit(0);
    }
}

int mot_simple()
{
    int i = 0;
    if (buffer[0] != '\0')
    {
        char old_buffer[SIZE_BUFFER];
        for (int k = 0; k < SIZE_BUFFER; k++)
        {
            old_buffer[k] = '\0';
        }
        while (i < SIZE_BUFFER && buffer[i] != 0)
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
    while (est_mot_simple())
    {
        i++;
        buffer[i] = mon_caractere;
        mon_caractere = fgetc(mon_fichier);
    }

    if(mon_caractere == '>')
    {
        return 0;
    }
    char *mot = (char *)malloc(sizeof(char) * SIZE_BUFFER);
    strncpy(mot, buffer, SIZE_BUFFER);
    mon_element = nv_element(mot, "mot_simple");
    return 1;
}

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

int mot_enrichi()
{
    char estBalise = '<' == mon_caractere;
    if (est_tag("<important>"))
    {
        mot_important();
    }
    else if (est_tag("</br>"))
    {
        a_element br = nv_element(NULL, "br");
        mon_element = br;
    }
    // if(estBalise)
    // {
    //     char tmp[SIZE_BUFFER];
    //     tmp[0] = '<';
    //     for (int i = 1;i < SIZE_BUFFER; i ++)
    //     {
    //         tmp[i] = buffer[i-1];
    //     }
    //     strncpy(buffer, tmp, SIZE_BUFFER);
    //     for (int i = 0;i < SIZE_BUFFER; i ++)
    //     {
    //         buffer[i] = tmp[i];
    //     }
    // }
    else if (est_mot_simple() && !estBalise)
    {
        mot_simple();
    }
    else
    {
        fprintf(stderr, "N'est pas un mot enrichi\n");
        return 0;
    }
    a_element mot_enrichi = nv_element(NULL, "mot_enrichi");
    ajouter_enfant(mot_enrichi, mon_element);
    mon_element = mot_enrichi;
    return 1;
}

void texte()
{
    a_element texte = nv_element(NULL, "texte");
    passer_espace();
    //Quelle condition d'arrêt mettre ???
    while (est_mot_simple() || mon_caractere == '<')
    {
        //printf("%s", buffer);
        if(mon_caractere == '<')
        {
            init_buffer();
            buffer[0] = '<';
        }
        if(!mot_enrichi())
        {
            // //le '<' est toujours mangé
            // char tmp[SIZE_BUFFER];
            // tmp[0] = '<';
            // for (int i = 1;i < SIZE_BUFFER; i ++)
            // {
            //     tmp[i] = buffer[i-1];
            // }
            // strncpy(buffer, tmp, SIZE_BUFFER);
            // for (int i = 0;i < SIZE_BUFFER; i ++)
            // {
            //     buffer[i] = tmp[i];
            // }
            break;
        }
        ajouter_enfant(texte, mon_element);
        passer_espace();
    }
    //printf("%s", buffer);
    mon_element = texte;
}

void titre(){
    a_element titre = nv_element(NULL, "titre");
    init_buffer();
    passer_espace();
    texte();
    ajouter_enfant(titre, mon_element);
    mon_element = titre;
    passer_espace();
    fin_tag("</titre>");
}
/*
void texte_liste(){
    texte();

    liste_texte();
}

void liste_texte(){
    liste();

    texte_liste();
}

void item(){
    est_tag("<item>");
    //Doit se répéter
    liste_texte();
    //Ou
    texte_liste();

    fin_tag("</item>");
}

void liste(){
    item();

    fin_tag("</liste>");
}*/

int main()
{
    amorcer();
    texte();
    a_element tmp = mon_element;
    passer_espace();

    // printf("\n%s\n%i\n%s\n", buffer,  est_tag("<titre>"), buffer);
    // titre();
    // ajouter_petit_frere(tmp, mon_element);
    // mon_element = tmp;
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