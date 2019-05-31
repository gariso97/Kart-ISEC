/* 
 * File:   Corridas.h
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 * 
 */


#ifndef CORRIDAS_H
#define CORRIDAS_H

#include "Kart_Structs.h"
#include "Campeonato.h"
#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif
    int calcula_idade(int P_dia, int P_mes, int P_ano);
    void reduz_falhas(pPiloto vpilotos, int *tam_p, pCarro vcarros, int *tam_c);
    pTreino configuracao_corrida(pTreino corrida, pPiloto vp, int *t_p, pCarro vc, int *t_c);
    void mostra_classificacao_volta(pTreino corrida, int n);
    void mostra_lista(pTreino corr);
    pTreino corrida_ativa(pTreino corrida, pPiloto vpilotos, int *tam_p, pCarro vcarros, int *tam_c, int volta);
    void modifica_exp(pTreino corrida, pPiloto vp, int *t_p);
    void penalizacao(pTreino corrida, pPiloto vp, int *t_p);
    void mostra_classificacao_final(pTreino corrida);
    pTreino liberta_lista_corrida(pTreino c);
    pTreino realizar_corrida(pTreino corrida_treino, pPiloto vpilotos, int *tam_p, pCarro vcarros, int *tam_c);
    
#ifdef __cplusplus
}
#endif

#endif /* CORRIDAS_H */

