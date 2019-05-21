/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
        int id;
        data data_nasc;
        int peso;
        float exp;
        int impedimento;
    }piloto, *pPiloto;
    
    typedef struct Carros{
        int id;
        int pot;
        int avaria;
    }carro, *pCarro;
    
    typedef struct Treinos treino, *pTreino;
    struct Treinos{
        int n_voltas;
        int comprimento;
        int capacidade;
        pTreino prox;
    };

#ifdef __cplusplus
}
#endif

#endif /* KART_STRUCTS_H */


