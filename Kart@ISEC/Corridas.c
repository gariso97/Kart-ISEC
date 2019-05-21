/* 
 * File:   Corridas.c
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 * 
 */

#include "Corridas.h"


//funcao onde e realizado o emparelhamento de carros com pilotos antes de cada corrida
void emparelhamento_pre_corrida(treino *t, pPiloto vpilotos,  int n_pilotos, pCarro vcarros, int n_carros){
#ifdef deb
    printf("NP: %d  | NC: %d \nn_voltas: %d | capacidade: %d | comp: %d\n", n_pilotos, n_carros, t->n_voltas, t->capacidade, t->comprimento);
#endif
    if(t->n_voltas >
}

//funcao onde e exigida uma configuracao inicial para cada corrida
pTreino configuracao_corrida_treino(pTreino corrida, pPiloto vp, int *t_p, pCarro vc, int *t_c){
    treino t;
    pTreino nova, aux;
    system("cls");
    
    nova = malloc(sizeof(treino));
    if(nova == NULL){
        printf("[Erro] Alocacao de memoria...\n");
        return corrida;
    }
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
    
    emparelhamento_pre_corrida(&t, vp, *t_p, vc, *t_c);
    
    exit(0);
    nova->capacidade = t.capacidade;
    nova->comprimento = t.comprimento;
    nova->n_voltas = t.n_voltas;
    nova->prox = NULL;
    
    if(corrida == NULL){
        corrida = nova;
    }else{
        aux = corrida;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = nova;
    }
    return corrida;
}

//funcao onde e executada uma corrida individual (treino)
pTreino corrida_individual(pTreino corrida, pPiloto vpilotos, int *tam_p, pCarro vcarros, int *tam_c){
    
    printf("NP: %d  | NC: %d \n", *tam_p, *tam_c);
    corrida = configuracao_corrida_treino(corrida, vpilotos, tam_p, vcarros, tam_c);
    return corrida;
}