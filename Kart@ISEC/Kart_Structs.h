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
    
    typedef struct Emparelhamento{      //vetor de estruturas onde max_pares e o tamanho do vetor
        int id_par;
        int melhor_tempo_final;
        int tempo_volta;
        int abandono;
        piloto motorista;
        carro kart;
    }empar, *pEmpar;
    
    typedef struct Corridas treino, *pTreino;
    struct Corridas{                    //lista ligada
        int n_voltas;
        int comprimento;
        int capacidade;
        int max_pares;
        pEmpar classif;                 //vetor de estruturas onde max_pares e o tamanho do vetor
        pTreino prox;
    };
    
    typedef struct Classificacao_campeonato class_c, *pClass_c;
    struct Classificacao_campeonato{    //lista ligada com n_voltas estruturas
        float pontuacao;
        int n_corridas;
        piloto jogador;
        pClass_c prox;
    };
    
    typedef struct Campeonato{          //estrutura que armazena a lista ligada da classificacao, a ultima partida e o numero de corridas que ainda faltam para terminar
        int corridas_total;
        pClass_c classif;
        pTreino ultima_partida;
    }Camp;
    
#ifdef __cplusplus
}
#endif

#endif /* KART_STRUCTS_H */


