#include "Mago.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void mostrar_estado_impl(const Personaje* this) {
    Mago* mago = (Mago*)this;
    printf("Mago: %s | Vida: %d | Nivel: %d | Mana: %d\\n", this->nombre, this->vida, this->nivel, mago->mana);
}

Mago* Mago_crear(const char* nombre, int vida, int nivel, int mana) {
    Mago* nuevo_mago = (Mago*)malloc(sizeof(Mago));
    if (!nuevo_mago) return NULL;
    nuevo_mago->base.nombre = strdup(nombre);
    nuevo_mago->base.vida = vida;
    nuevo_mago->base.nivel = nivel;
    nuevo_mago->mana = mana;
    nuevo_mago->base.mostrar_estado = mostrar_estado_impl;
    return nuevo_mago;
}

void Mago_destruir(Mago* this) {
    if (this) {
        free(this->base.nombre);
        free(this);
    }
}