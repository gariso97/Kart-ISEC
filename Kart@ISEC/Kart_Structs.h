/* 
 * File:   Kart_Structs.h
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 *
 */

#ifndef KART_STRUCTS_H
#define KART_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ST_TAM 105

//#define deb

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Data{
        int dia;
        int mes;
        int ano;
    }data;
    
    typedef struct Pilotos{
        char nome[ST_TAM];
        int idP;
        data data_nasc;
        int peso;
        float exp;
        int impedimento;
    }piloto, *pPiloto;
    
    typedef struct Carros{
        int idC;
        int pot;
        int avaria;
    }carro, *pCarro;
    
    typedef struct Emparelhamento{
        int id_par;
        piloto motorista;
        carro kart;
    }empar, *pEmpar;
    
    typedef struct Corridas treino, *pTreino;
    struct Corridas{
        int n_voltas;
        int comprimento;
        int capacidade;
        pEmpar pares;
        pTreino prox;
    };

#ifdef __cplusplus
}
#endif

#endif /* KART_STRUCTS_H */


