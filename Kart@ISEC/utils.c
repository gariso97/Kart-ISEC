// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2018-2019

#include <time.h>
#include <limits.h>

#include "Corridas.h"

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

void espera(unsigned int seg){
    unsigned int goal = seg + clock()/CLOCKS_PER_SEC;
    while (goal > clock()/CLOCKS_PER_SEC);
}

void obtemData(int *dia, int *mes, int *ano, int *h, int *m, int *s){
    time_t a;
    struct tm* b;

    time(&a);
    b = localtime(&a);
    *dia = b->tm_mday;
    *mes = b->tm_mon;
    *ano = b->tm_year + 1900;
    *h = b->tm_hour;
    *m = b->tm_min;
    *s = b->tm_sec;
}

int calculaSegundos(int idadeP, int pesoP, float expP, int PotC, int metros){
    return metros/20 + min(3, max(1, 20-expP))*intUniformRnd(1,3)
            + (float)pesoP/idadeP*intUniformRnd(1,2) + 500.0*(intUniformRnd(1,2))/PotC;
}

// Função com alguns exemplos simples de utilizacao das funcoes
void testes(){
    int i, dia, mes, ano, hora, minuto, seg;

    initRandom();

    obtemData(&dia, &mes, &ano, &hora, &minuto, &seg);
    printf("%2.2d/%2.2d/%d: %2.2d:%2.2d:%2.2d\n", dia, mes, ano, hora, minuto, seg);

    espera(3);

    obtemData(&dia, &mes, &ano, &hora, &minuto, &seg);
    printf("%2.2d/%2.2d/%d: %2.2d:%2.2d:%2.2d\n", dia, mes, ano, hora, minuto, seg);

    printf("10 valores aleatorios uniformes entre [4, 10]:\n");
    for(i=0; i<10; i++)
        printf("%d\n", intUniformRnd(4, 10));

    printf(" Probabilidade 0.25 de suceder: \n");
    for(i=0; i<10; i++)
        printf("%d\n", probEvento(0.25));

    printf("Calculo de 10 tempos por volta: \n");
    for(i=0; i<10; i++)
        printf("%d\n", calculaSegundos(30, 80, 20.0, 160, 1000));
}



