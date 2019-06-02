/* 
 * File:   Campeonato.h
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 * 
 */


#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "Corridas.h"

#ifdef __cplusplus
extern "C" {
#endif

Camp campeonato_corridas(Camp camp, pPiloto vpilotos, int *tam_p, pCarro vcarros, int *tam_c);
Camp carrega_campeonato(char *campeonatoBin);
void grava_fich_campeonato(char *nomefich, Camp campeonato);
void classificacao_final(Camp camp, pPiloto vp, int *tam);
Camp liberta_campeonato(Camp camp);

#ifdef __cplusplus
}
#endif

#endif /* CAMPEONATO_H */

