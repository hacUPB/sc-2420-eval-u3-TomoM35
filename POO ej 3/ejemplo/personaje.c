#include "Personaje.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void mostrar_estado_impl(const Personaje* this) {
    printf("Personaje: %s | Vida: %d | Nivel: %d\n", this->nombre, this->vida, this->nivel);
}

Personaje* Personaje_crear(const char* nombre, int vida, int nivel) {
    Personaje* nuevo_personaje = (Personaje*)malloc(sizeof(Personaje)); 
    if (!nuevo_personaje) return NULL; 
    strcpy_s(nuevo_personaje->nombre, 30, nombre); 
    nuevo_personaje->vida = vida; 
    nuevo_personaje->nivel = nivel; 
    nuevo_personaje->mostrar_estado = mostrar_estado_impl; 
    return nuevo_personaje; 
}

char* get_name(Personaje* this) {
    return this->nombre; 
}

void Personaje_destruir(Personaje* this) {
    if (this) {
        free(this); 
    }
}
