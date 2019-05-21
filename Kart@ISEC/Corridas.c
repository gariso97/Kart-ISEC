/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Kart_Structs.h"


/* 
 * File:   Corridas.c
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 * 
 */

pTreino configuracao_corrida_treino(pTreino corrida){
    treino t;
    pTreino nova = NULL;
    system("cls");
    
    printf("\n      Configuracoes da corrida de treino:\n");
    do{
        printf("\nNumero de voltas: ");
        scanf("%d", &t.n_voltas);
        if(t.n_voltas < 5 || t.n_voltas > 10){
            printf("\n[ERRO] Numero de voltas invalido! Tem de ser entre 5 a 10 voltas...");
        }
    }while(t.n_voltas < 5 || t.n_voltas > 10);
    do{
        printf("\nComprimento da pista (m): ");
        scanf("%d", &t.comprimento);
        if(t.comprimento < 500 || t.comprimento > 1000){
            printf("\n[ERRO] Comprimento da pista invalido! Tem de ser entre 500 e 1000 metros...");
        }
    }while(t.comprimento < 500 || t.comprimento > 1000);
    do{
        printf("\nNumero maximo de carros: ");
        scanf("%d", &t.capacidade);
        if(t.capacidade <= 0){
            printf("\n[ERRO] Capacidade da pista invalida! Tem de ser superior a 0 carros...");
        }
    }while(t.capacidade <= 0);
    nova = t;
    return corrida;
}



pTreino treino(pTreino corrida){
    
    corrida = configuracao_corrida_treino(corrida);
    
    
    return corrida;
}