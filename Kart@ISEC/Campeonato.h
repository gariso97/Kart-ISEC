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

Camp *campeonato(Camp *camp, pPiloto vpilotos, int *tam_p, pCarro vcarros, int *tam_c);


#ifdef __cplusplus
}
#endif

#endif /* CAMPEONATO_H */

