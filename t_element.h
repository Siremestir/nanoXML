#ifndef T_ELEMENT_H_INCLUDED
#define T_ELEMENT_H_INCLUDED

/**
 * \file t_element.h
 * \brief fichier contenant les outils sur les éléments de NanoXML.
 *
 * \author Swan Sauvegrain
 * \author Astrid E. Djouhassi D.
 * \version 0.1
 * \date mai 2021
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_element
{
    struct s_element* aine;
    struct s_element* petit_frere;
    char* contenu;
    char* type;
} t_element;

typedef t_element* a_element;

a_element nv_element(char* contenu, char* type);

void ajouter_enfant(a_element ceci, a_element enfant);

void ajouter_petit_frere(a_element ceci, a_element petit_frere);

char* capitales(char* chaine);

void afficher_element(a_element ceci, int capitales);

#endif