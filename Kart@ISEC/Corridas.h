/* 
 * File:   Corridas.h
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 * 
 */


#ifndef CORRIDAS_H
#define CORRIDAS_H

#include "Kart_Structs.h"
#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif
    int calcula_idade(int P_dia, int P_mes, int P_ano);
    pTreino realizar_corrida(pTreino corrida, pPiloto vpilotos, int *tam_p, pCarro vcarros, int *tam_c);
    
#ifdef __cplusplus
}
#endif

#endif /* CORRIDAS_H */

