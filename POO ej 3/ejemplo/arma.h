#ifndef ARMA_H
#define ARMA_H

typedef struct Arma {
    char nombre[30]; // Nombre del arma
    int dano;        // Da�o que causa
    int alcance;     // Alcance del arma
    void (*mostrar_info)(const struct Arma* this); // Puntero a funci�n para mostrar informaci�n
} Arma;

// Funci�n para crear un arma
Arma* Arma_crear(const char* nombre, int dano, int alcance);

// Funci�n para liberar la memoria de un arma
void Arma_destruir(Arma* this);

// Funci�n para mostrar la informaci�n del arma
void mostrar_info(const Arma* this);

#endif