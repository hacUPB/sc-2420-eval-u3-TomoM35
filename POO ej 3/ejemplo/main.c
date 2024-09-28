#include <stdio.h>
#include "personaje.h"
#include "arma.h"
#include "Guerrero.h"
#include "Mago.h"

int main(void)
{
    Mago* Celine;
    Celine = Mago_crear("Celine", 10, 5, 15, 25, 20);
    printf("El mago se llama %s\n", get_name(Celine));

    Guerrero* Ciara;
    Ciara = Guerrero_crear("Ciara", 12, 6, 3);
    printf("El guerrero se llama %s\n", get_name(Ciara));

    Arma* espada;
    espada = Arma_crear("Espada Larga", 40, 5.0);
    printf("El arma de Ciara es un %s\n", get_wepon(espada));

    Mago_destruir(Celine);
    Guerrero_destruir(Ciara);
    Arma_destruir(espada);

    return 0;
}