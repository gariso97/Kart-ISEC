/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BD.h
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 *
 * Created on 1 de Abril de 2019, 18:24
 */

#ifndef KART_STRUCTS_H
#define KART_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ST_TAM 100

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

#ifdef __cplusplus
}
#endif

#endif /* KART_STRUCTS_H */


