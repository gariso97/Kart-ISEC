/* 
 * File:   Campeonato.c
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 *
 */

#include "Campeonato.h"


//funcao que mostra a classificacao no final do campeonato
void classificacao_final(Camp camp, pPiloto vp, int *tam){
    pClass_c c = camp.classif;
    class_c vencedor;
    int i = 1, flag = 0;
    printf("\n#--------------------------------------------------#");
    printf("\n   ==$|| Classificacao FINAL do Campeonato: ||$==");
    printf("\n#--------------------------------------------------#\n");
    
     while (c->prox != NULL) {
         if (flag == 0) {
            vencedor.jogador = c->jogador;
            vencedor.n_corridas = c->n_corridas;
            vencedor.pontuacao = c->pontuacao;
            flag = 1;
        }
         printf("\n-> %d <- (ID: %d) %-20s\t| Corridas: %d | Pontos: %.2f", i, c->jogador.idP, c->jogador.nome, c->n_corridas, c->pontuacao);
         i++;
         c = c->prox;
    }
    printf("\n\n#--------------------------------------------------#\n");
    printf("\n       Pressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    system("cls");
    
    for(int j=0; j<(*tam); j++){
        if(vencedor.jogador.idP == vp[j].idP){
            vp[j].exp = vp[j].exp + 10;
        }
    }
    printf("\n#--------------------------------------------------#");
    printf("\n        ==$|| Vencedor do Campeonato: ||$==");
    printf("\n#--------------------------------------------------#\n");
    printf("\n(ID: %d) %-20s\t| Corridas: %d | Pontos: %.2f", vencedor.jogador.idP, vencedor.jogador.nome, vencedor.n_corridas, vencedor.pontuacao);
    printf("\n\n#--------------------------------------------------#\n");
    printf("\n       Pressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    system("cls");
}

//funcao que volta a criar a lista ligada ja ordenada e atualizada com as pontuacoes
pClass_c recria_classificacao_ordenada(pClass_c classif, pClass_c vetor, int n){
    pClass_c nova, aux;
    
    nova = malloc(sizeof(class_c));
    if (nova == NULL) {
        printf("[ERRO] Alocacao de memoria...\n");
        return classif;
    }
    
    nova->jogador = vetor[n].jogador;
    nova->n_corridas = vetor[n].n_corridas;
    nova->pontuacao = vetor[n].pontuacao;
    nova->prox = NULL;
    
    if (classif == NULL) {
        classif = nova;
    } else {
        aux = classif;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = nova;
    }
    
    return classif;
}

//funcao que liberta a lista da classificacao
pClass_c liberta_lista_classif(pClass_c c) {
    pClass_c aux;
    while (c != NULL) {
        aux = c;
        c = c->prox;
        free(aux);
    }
    return c;
}

//funcao que organiza a classificacao por pontuacao
pClass_c organiza_pela_pontuacao(pClass_c vetor, int tam) {
    class_c temp;
    for (int j = 0; j < tam - 1; j++)
        for (int i = 0; i < tam - j - 1; i++) {
            if (vetor[i].pontuacao < vetor[i + 1].pontuacao) {
                temp = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = temp;
            } else if (vetor[i].pontuacao == vetor[i + 1].pontuacao) {
                if (vetor[i].n_corridas < vetor[i + 1].n_corridas) {
                    temp = vetor[i];
                    vetor[i] = vetor[i + 1];
                    vetor[i + 1] = temp;
                } else if (vetor[i].n_corridas == vetor[i + 1].n_corridas){
                    int idade1 = calcula_idade(vetor[i].jogador.data_nasc.dia, vetor[i].jogador.data_nasc.mes, vetor[i].jogador.data_nasc.ano);
                    int idade2 = calcula_idade(vetor[i + 1].jogador.data_nasc.dia, vetor[i + 1].jogador.data_nasc.mes, vetor[i + 1].jogador.data_nasc.ano);
                    if(idade1 < idade2){
                        temp = vetor[i];
                        vetor[i] = vetor[i + 1];
                        vetor[i + 1] = temp;
                    }
                }
            }
        }
    return vetor;
}

//funcao que adiciona pontos aos pilotos
Camp modifica_pontos_final_corrida(Camp cam, int *t_p) {
    int pontos, i = 0;
    float vetor_pontos[(*t_p)];
    pClass_c c = cam.classif;
    pTreino voltas = cam.ultima_partida;
    pClass_c vetor_temp = NULL;
    
    for (int i = 0; i < (*t_p); i++)
        vetor_pontos[i] = 0;
    
    //criacao de um vetor para armazenar modificar e ordenar a classificacao
    vetor_temp = malloc(sizeof(class_c) * (*t_p));
    if (vetor_temp == NULL) {
        puts("\n[ERRO] Reserva de memoria falhada!\n");
        return cam;
    }
    //ultima volta da ultima corrida
    while(voltas->prox != NULL)
        voltas = voltas->prox;
    
    //passagem dos jogadores da classificacao para um vetor
    while (c != NULL) {
        vetor_temp[i].jogador = c->jogador;
        vetor_temp[i].n_corridas = c->n_corridas;
        vetor_temp[i].pontuacao = c->pontuacao;
        for (int j = 0; j < voltas->max_pares; j++) {
            if(c->jogador.idP == voltas->classif[j].motorista.idP){
                pontos = 5 - j;
                if(pontos < 0){
                    pontos = 0;
                }
                vetor_pontos[i] = vetor_pontos[i] + pontos;
                vetor_temp[i].n_corridas++;
            }
        }
        vetor_temp[i].prox = NULL;
        i++;
        c = c->prox;
    }
    
    voltas = cam.ultima_partida;
    while(voltas->prox != NULL){
        voltas = voltas->prox;
        for (int j = 0; j < (*t_p); j++) {
            if (vetor_temp[j].jogador.idP == voltas->classif[0].motorista.idP) {
                vetor_pontos[j] = vetor_pontos[j] + 0.5;
            }else if (vetor_temp[j].jogador.idP == voltas->classif[0].motorista.idP && voltas->classif[0].abandono != 0) {
                    vetor_pontos[j] = 0;
                }
        }
    }

    for (int j = 0; j < (*t_p); j++) {
        vetor_temp[j].pontuacao = vetor_temp[j].pontuacao + vetor_pontos[j];
    }
    
    vetor_temp = organiza_pela_pontuacao(vetor_temp, *t_p);
    
    cam.classif = liberta_lista_classif(cam.classif);
    while(cam.classif != NULL){
        cam.classif = cam.classif->prox;
    }
    
    for(int i=0; i<(*t_p); i++){
        cam.classif = recria_classificacao_ordenada(cam.classif, vetor_temp, i);
    }
    
    free(vetor_temp);
    return cam;
}

//funcao que preenche a classificacao com os pilotos existentes no programa
pClass_c preenche_class(pClass_c classif, pPiloto vp, int p){
    pClass_c nova, aux;
    
    nova = malloc(sizeof(class_c));
    if (nova == NULL) {
        printf("[ERRO] Alocacao de memoria...\n");
        return classif;
    }
    
    //preenchimento da estrutura para a lista
    nova->jogador = vp[p];
    nova->pontuacao = 0;
    nova->n_corridas = 0;
    nova->prox = NULL;
    
    if (classif == NULL) {
        classif = nova;
    } else {
        aux = classif;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = nova;
    }
    return classif;
}

//funcao que mostra a classificacao geral do campeonato
void mostra_classificacao_campeonato(pClass_c classif){
    pClass_c c = classif;
    int i = 1;
    printf("\n#--------------------------------------------------#");
    printf("\n   ==$|| Classificacao Geral do Campeonato: ||$==");
    printf("\n#--------------------------------------------------#\n");
     while (c->prox != NULL) {
         printf("\n-> %d <- (ID: %d) %-20s\t| Corridas: %d | Pontos: %.2f", i, c->jogador.idP, c->jogador.nome, c->n_corridas, c->pontuacao);
         i++;
         c = c->prox;
    }
    printf("\n\n#--------------------------------------------------#\n");
    printf("\n       Pressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    system("cls");
}

//funcao que carrega do ficheiro binario o campeonato para a lista ligada
Camp carrega_campeonato(char *campeonatoBin){
    Camp camp;
    pClass_c novo, classif = NULL;
    pTreino nova, corrida = NULL;
    int i, total;
    
    FILE *f = fopen(campeonatoBin, "rb");
    if (f == NULL) {
        printf("\n[ERRO] Abertura do ficheiro...\n");
        return camp;
    }
    
    //ler o numero de corridas que ainda falta
    fread(&camp.corridas_total, sizeof (int), 1, f);
    
    //ler a ultima lista ligada (ultima corrida)
    fseek(f, -sizeof (int), SEEK_END);
    fread(&total, sizeof (int), 1, f);
    for (i = total - 1; i >= 0; i--) {
        fseek(f, -(sizeof (treino) * i), SEEK_CUR);
        nova = malloc(sizeof (treino));
        if (nova == NULL) {
            printf("\n[ERRO] Alocacao de memoria...\n");
            fclose(f);
            return camp;
        }
        fread(nova, sizeof (treino), 1, f);
        nova->prox = corrida;
        corrida = nova;
    }
    camp.ultima_partida = corrida;
    
    //ler a classificacao do campeonato
    fread(&total, -sizeof (int), 1, f);
    for (i = total - 1; i >= 1; i--) {
        fseek(f, -(sizeof (class_c) * i), SEEK_CUR);
        novo = malloc(sizeof (class_c));
        if (novo == NULL) {
            printf("\n[ERRO] Alocacao de memoria...\n");
            fclose(f);
            return camp;
        }
        fread(novo, sizeof (class_c), 1, f);
        novo->prox = classif;
        classif = novo;
    }
    camp.classif = classif;
    
    fclose(f);
    return camp;
}

//funcao que grava a lista ligada do campeonato no ficheiro binario
void grava_fich_campeonato(char *nomefich, Camp c){
    int conta = 0;
    
    FILE *f = fopen(nomefich, "wb");
    if (f == NULL) {
        printf("\n[ERRO] Criacao do ficheiro...\n");
        return;
    }
    
    fwrite(&c.corridas_total, sizeof(int), 1, f);
    
    while (c.classif != NULL) {
        fwrite(c.classif, sizeof(class_c), 1, f);
        c.classif = c.classif->prox;
        conta++;
    }
    conta = 0;
    fwrite(&conta, sizeof(int), 1, f);
    while (c.ultima_partida != NULL) {
        fwrite(c.ultima_partida, sizeof(treino), 1, f);
        c.ultima_partida = c.ultima_partida->prox;
        conta++;
    }
    fwrite(&conta, sizeof(int), 1, f);
    
    fclose(f);
}

//funcao que liberta o campeonato que acabou
Camp liberta_campeonato(Camp camp){
    camp.classif = liberta_lista_classif(camp.classif);
    camp.ultima_partida = liberta_lista_corrida(camp.ultima_partida);
    return camp;
}

//funcao onde e chamada a configuracao e executada uma corrida para o campeonato
Camp campeonato_corridas(Camp camp, pPiloto vpilotos, int *tam_p, pCarro vcarros, int *tam_c) {
    pTreino corrida_treino = NULL;
    if(camp.classif == NULL){
        for(int i=0; i<(*tam_p);i++){
            camp.classif = preenche_class(camp.classif, vpilotos, i);
        }
    }
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
                mostra_classificacao_campeonato(camp.classif);
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
    
    pTreino corrida = corrida_treino;
    camp.ultima_partida = corrida;
    camp = modifica_pontos_final_corrida(camp, tam_p);
    
    printf("\n\n       Pressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    system("cls");
    penalizacao(corrida_treino, vpilotos, tam_p);
    
    camp.corridas_total--;
    return camp;
}