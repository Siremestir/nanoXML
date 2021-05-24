#include "t_element.h"

void ajouter_petit_frere(a_element ceci, a_element petit_frere)
{
    if (ceci->petit_frere == NULL)
    {
        ceci->petit_frere = petit_frere;
    }
    else
    {
        ajouter_petit_frere(ceci->petit_frere, petit_frere);
    }
}

void ajouter_enfant(a_element ceci, a_element enfant)
{
    if (ceci->aine == NULL)
    {
        ceci->aine = enfant;
    }
    else
    {
        ajouter_petit_frere(ceci->aine, enfant);
    }
}

a_element nv_element(char *contenu, char *type)
{
    a_element nv_element = (a_element)malloc(sizeof(t_element));
    nv_element->contenu = contenu;
    nv_element->type = type;
}

char* capitales(char* chaine){
    for (int i = 0; chaine[i]!='\0'; i++) {
        if(chaine[i] >= 'a' && chaine[i] <= 'z') {
            chaine[i] = chaine[i] -32;
        }
    }
    return chaine;
}

void afficher_element(a_element ceci, int capitales)
{
    if (ceci == NULL)
        return;
    if (strcmp(ceci->type, "mot_important") == 0)
    {
        printf("\"");
        afficher_element(ceci->aine, capitales);
        printf("\"");
    }
    else if (strcmp(ceci->type, "texte") == 0)
    {
        afficher_element(ceci->aine, capitales);
    }
    else if (strcmp(ceci->type, "mot_enrichi") == 0)
    {
        afficher_element(ceci->aine, capitales);
    }
    else if (strcmp(ceci->type, "titre") == 0)
    {
        afficher_element(ceci->aine, 1);
        printf("\n");
    }
    
    else if (strcmp(ceci->type, "br") == 0)
    {
        printf("\n");
    }
    if (ceci->contenu != NULL)
    {
        if (capitales)
        {
            for (int i = 0; ceci->contenu[i]!='\0'; i++)
            {
                if(ceci->contenu[i] >= 'a' && ceci->contenu[i] <= 'z')
                {
                    ceci->contenu[i] = ceci->contenu[i] -32;
                }
            }
        }
        printf("%s ", ceci->contenu);
    }
    if (ceci->petit_frere != NULL)
    {
        if(strcmp(ceci->type, "titre") == 0)
        {
            afficher_element(ceci->petit_frere, 0);
        }
        else 
        {
            afficher_element(ceci->petit_frere, capitales);
        }
    }
}