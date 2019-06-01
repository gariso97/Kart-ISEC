/* 
 * File:   Campeonato.c
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 *
 */

#include "Campeonato.h"


//funcao que adiciona / retira experiencia aos pilotos
/*
void modifica_pontos(pTreino corrida, pPiloto vp, int *t_p) {
    pTreino c = corrida;
    float vetor_exp[(*t_p)];

    for (int i = 0; i < (*t_p); i++)
        vetor_exp[i] = 0;

    //retirar experiencia aos pilotos que tiveram um acidente
    while (c->prox != NULL) {
        c = c->prox;

        for (int j = 0; j < c->max_pares; j++) {
            for (int i = 0; i < (*t_p); i++) {
                if (vp[i].idP == c->classif[j].motorista.idP && j == 0) {
                    vetor_exp[i] = vetor_exp[i] + 0.5;
                } else if (vp[i].idP == c->classif[j].motorista.idP && c->classif[j].abandono != 0) {
                    vetor_exp[i] = 0;
                }
            }
        }
    }

    for (int j = 0; j < c->max_pares; j++) {
        for (int i = 0; i < (*t_p); i++) {
            if (vp[i].idP == c->classif[j].motorista.idP && c->classif[j].abandono != 0) {
                if (vp[i].exp < 1) {
                    vp[i].exp = 0;
                } else {
                    vp[i].exp = vp[i].exp - 1;
                }
            }
        }
    }
    for (int j = 0; j < c->max_pares; j++) {
        for (int i = 0; i < (*t_p); i++) {
            if (vp[i].idP == c->classif[j].motorista.idP) {
                vp[i].exp = vp[i].exp + vetor_exp[i];
            }
        }
    }
}
*/

//funcao que preenche a classificacao dos pilotos por pontos
Camp preenche_class(Camp camp, pTreino corrida){
    pTreino c = corrida;
    pClass_c novo, aux;
/*
    
    while (c->prox != NULL) {
        c = c->prox;
    }
    for (int j = 0; j < c->max_pares; j++) {
        if (c->classif[j].abandono != 0) {
            printf("\n-> D <- %-20s (ID: %d) | Kart: %d - Acidente (volta %d)", c->classif[j].motorista.nome, c->classif[j].motorista.idP, c->classif[j].kart.idC, c->classif[j].abandono);
        } else {
            //soma_de_tempos(str, corrida, c->classif[j].id_par, c->n_voltas);
            //printf("\n-> %d <- %-20s (ID: %d) | Kart: %d", j + 1, c->classif[j].motorista.nome, c->classif[j].motorista.idP);
        }
    }
*/

    novo = malloc(sizeof (Camp));
    if (novo == NULL) {
        printf("[ERRO] Alocacao de memoria\n");
        return camp;
    }
    
    //preenche(novo);
    
    if (camp.classif == NULL || novo->pontuacao > camp.classif->pontuacao) {
        novo->prox = camp.classif;
        camp.classif = novo;
    } else {
        aux = camp.classif;
        while (aux->prox != NULL && novo->pontuacao > aux->prox->pontuacao)
            aux = aux->prox;
        novo->prox = aux->prox;
        aux->prox = novo;
    }
    return camp;
}

//funcao que mostra a classificacao geral do campeonato
/*
void mostra_classificacao_campeonato(Camp c){
    
    /*
    printf("\n#--------------------------------------------------#");
    printf("\n   ==$|| Classificacao Geral do Campeonato: ||$==");
    printf("\n#--------------------------------------------------#\n");
*/
   /* while (c->prox != NULL) {
        c = c->prox;
    }
    
    for (int j = 0; j < c->max_pares; j++) {
        if (c->classif[j].abandono != 0) {
            printf("\n-> D <- %-20s (ID: %d) | Kart: %d - Acidente (volta %d)", c->classif[j].motorista.nome, c->classif[j].motorista.idP, c->classif[j].kart.idC, c->classif[j].abandono);
        } else {
            //soma_de_tempos(str, corrida, c->classif[j].id_par, c->n_voltas);
            printf("\n-> %d <- %-20s (ID: %d) | Kart: %d", j + 1, c->classif[j].motorista.nome, c->classif[j].motorista.idP);
        }
    }
}
*/

//funcao que carrega do ficheiro binario o campeonato para a lista ligada
Camp carrega_campeonato(char *campeonatoBin){
    
}

//funcao que grava a lista ligada do campeonato no ficheiro binario
void grava_fich_campeonato(Camp campeonato){
    
}

//funcao onde e chamada a configuracao e executada uma corrida para o campeonato
Camp campeonato_corridas(Camp camp, pPiloto vpilotos, int *tam_p, pCarro vcarros, int *tam_c) {
    pTreino corrida_treino = NULL;
    
    int op;
    system("cls");
    do {
        printf("\n#---------------------------------------------#");
        printf("\n           =$|| Menu Campeonato ||$=");
        printf("\n#---------------------------------------------#\n");
        printf("\n           1 - Partida (Prova -> %d)", camp.corridas_total);
        printf("\n           2 - Classif. da Ultima Corrida");
        printf("\n           3 - Classificacao Geral");
        printf("\n           4 - Voltar");

        printf("\n\nOpcao: ");
        scanf("%d", &op);
        switch(op){
            case 2:
                system("cls");
                mostra_classificacao_final(camp.ultima_partida);
                break;
            case 3:
                system("cls");
                //mostra_classificacao_campeonato(camp);
                break;
            case 4:
                return camp;
        }
    } while (op != 1);

    liberta_lista_corrida(camp.ultima_partida);
    corrida_treino = configuracao_corrida(corrida_treino, vpilotos, tam_p, vcarros, tam_c);
    reduz_falhas(vpilotos, tam_p, vcarros, tam_c);
    
    system("cls");
    for (int i = 1; i <= corrida_treino->n_voltas; i++) {
        corrida_treino = corrida_ativa(corrida_treino, vpilotos, tam_p, vcarros, tam_c, i);
#ifdef deb
        mostra_lista(corrida_treino); //mostra tudo o q existe na lista ligada
#endif
        if (i <= corrida_treino->n_voltas) {
            mostra_classificacao_volta(corrida_treino, i);
            if (i % 2 == 0) {
                espera(5);
            }
        }
        if (i == corrida_treino->n_voltas) {
            mostra_classificacao_volta(corrida_treino, i + 1);
        }
    }
    modifica_exp(corrida_treino, vpilotos, tam_p);
/*
    for (int j = 0; j < (*tam_p); j++) {
        preenche_class(camp, corrida_treino);
    }
*/
    printf("\n\n       Pressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    system("cls");
    penalizacao(corrida_treino, vpilotos, tam_p);
    pTreino corrida = corrida_treino;
    camp.ultima_partida = corrida;
    camp.corridas_total--;
    return camp;
}