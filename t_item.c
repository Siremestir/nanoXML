#include "t_item.h"

a_item nv_item(a_element element) {
    a_item nv_item = (a_item)malloc(sizeof(t_item));
    nv_item->element = element;
    return nv_item;
}

void ajouter_item(a_item ceci, a_item quoi){
    if(ceci == NULL){
        ceci = quoi;
    } else {
        ajouter_item(ceci->suivant, quoi);
    }
}