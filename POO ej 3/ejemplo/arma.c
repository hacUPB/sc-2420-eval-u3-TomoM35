#include "Arma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void mostrar_info_impl(const Arma* this) {
    printf("Arma: %s | Daño: %d | Alcance: %d\n", this->nombre, this->dano, this->alcance);
}

Arma* Arma_crear(const char* nombre, int dano, int alcance) {
    Arma* nueva_arma = (Arma*)malloc(sizeof(Arma)); 
    if (!nueva_arma) return NULL; 

    strncpy(nueva_arma->nombre, nombre, sizeof(nueva_arma->nombre) - 1);
    nueva_arma->nombre[sizeof(nueva_arma->nombre) - 1] = '\0'; 

    nueva_arma->dano = dano; 
    nueva_arma->alcance = alcance; 

    nueva_arma->mostrar_info = mostrar_info_impl;

    return nueva_arma; 
}

const char* get_wepon(const Arma* this) {
    return this->nombre; 
}


void Arma_destruir(Arma* this) {
    if (this) {
        free(this); 
    }
}

