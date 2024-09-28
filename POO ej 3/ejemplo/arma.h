#ifndef ARMA_H
#define ARMA_H

typedef struct Arma {
    char nombre[30]; // Nombre del arma
    int dano;        // Daño que causa
    int alcance;     // Alcance del arma
    void (*mostrar_info)(const struct Arma* this); // Puntero a función para mostrar información
} Arma;

// Función para crear un arma
Arma* Arma_crear(const char* nombre, int dano, int alcance);

// Función para liberar la memoria de un arma
void Arma_destruir(Arma* this);

// Función para mostrar la información del arma
void mostrar_info(const Arma* this);

#endif