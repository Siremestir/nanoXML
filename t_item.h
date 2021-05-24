#ifndef T_ITEM_H_INCLUDED
#define T_ITEM_H_INCLUDED

/**
 * \file t_item.h
 * \brief fichier contenant les outils sur les items de NanoXML.
 *
 * \author Swan Sauvegrain
 * \author Astrid E. Djouhassi D.
 * \version 0.1
 * \date mai 2021
*/

#include "t_element.h"

//struct s_element;

typedef struct s_item
{
    struct s_item* suivant;
    struct s_element* element;
} t_item;

typedef t_item* a_item;




a_item nv_item(a_element element);

#endif