/* 
 * File:   Corridas.c
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 * 
 */

#include "Corridas.h"


//funcao que mostra todos os pilotos e carros não selecionados
void mostra_nao_selecionados(treino t, pPiloto vp, int np, pCarro vc, int nc, int c_disp, int p_disp){
    system("cls");
    
    //mostrar os pilotos que nao vao correr
    printf("\n#--------------------------------------------------#");
    printf("\n      Pilotos nao selecionados para a corrida:");
    printf("\n#--------------------------------------------------#\n");
    int select;
    for(int i=0; i<np; i++){
        select = 0;
        for(int j=0; j < t.capacidade; j++){
            if(t.pares[j].motorista.idP == vp[i].idP){
                select = 1;
            }
        }
        if(select == 0){
            if(vp[i].impedimento != 0){
                printf("\nPiloto (ID = %d): %-20s | Razao: Nao pode correr durante %d partidas!!", vp[i].idP, vp[i].nome, vp[i].impedimento);
            }else if(p_disp > c_disp && c_disp < t.capacidade){
                printf("\nPiloto (ID = %d): %-20s | Razao: Nao existe mais nenhum carro disponivel para a corrida!!", vp[i].idP, vp[i].nome);
            }else{
                printf("\nPiloto (ID = %d): %-20s | Razao: Nao foi selecionado (na escolha aleatoria) para a corrida!!", vp[i].idP, vp[i].nome);
            }
        }
    }
    
    //mostrar os carros que nao vao correr
    printf("\n\n#--------------------------------------------------#");
    printf("\n      Carros nao selecionados para a corrida:");
    printf("\n#--------------------------------------------------#\n");
    for(int i=0; i<nc; i++){
        select = 0;
        for(int j=0; j < t.capacidade; j++){
            if(t.pares[j].kart.idC == vc[i].idC){
                select = 1;
            }
        }
        if(select == 0){
            if(vc[i].avaria != 0){
                printf("\nCarro (ID = %d) | Razao: Nao pode correr durante %d partidas devido a avarias!!", vc[i].idC, vc[i].avaria);
            }else if(c_disp > p_disp && p_disp < t.capacidade){
                printf("\nCarro (ID = %d) | Razao: Nao existe mais nenhum piloto disponivel para a corrida!!", vc[i].idC);
            }else{
                printf("\nCarro (ID = %d) | Razao: Nao foi selecionado (na escolha aleatoria) para a corrida!!", vc[i].idC);
            }
        }
    }
    printf("\n\n#--------------------------------------------------#");
    printf("\n\nPressione ENTER para continuar...");
    fflush(stdin);
    getchar();
}

//funcao que verifica os carros disponiveis
int verifica_carros_disponiveis(pCarro vcarros, int n_carros){
    int carros_disp = 0;
    for(int i=0; i<n_carros; i++){
        if(vcarros[i].avaria == 0)
            carros_disp++;
    }
#ifdef deb
    printf("NC_disp: %d ", carros_disp);
#endif
    return carros_disp;
}

//funcao que verifica os pilotos disponiveis
int verifica_pilotos_disponiveis(pPiloto vpilotos,  int n_pilotos){
    int pilotos_disp = 0;
    for(int i=0; i<n_pilotos; i++){
        if(vpilotos[i].impedimento == 0)
            pilotos_disp++;
    }
#ifdef deb
    printf("NP_disp: %d ", pilotos_disp);
#endif
    return pilotos_disp;
}

//funcao onde e realizado o emparelhamento de carros com pilotos antes de cada corrida
void emparelhamento_pre_corrida(treino *t, pPiloto vpilotos,  int n_pilotos, pCarro vcarros, int n_carros){
    pEmpar vPares = NULL;
    int p_disp, c_disp;
    int n_vetor, valid;
    
#ifdef deb
    printf("NP: %d  | NC: %d \nn_voltas: %d | capacidade: %d | comp: %d\n", n_pilotos, n_carros, t->n_voltas, t->capacidade, t->comprimento);
#endif
    
    //verificacoes para emparelhar os pilotos com os carros de modo a que nao ultrapassem a capacidade da pista
    p_disp = verifica_pilotos_disponiveis(vpilotos, n_pilotos);
    c_disp = verifica_carros_disponiveis(vcarros, n_carros);
    if (p_disp >= c_disp){
        t->max_pares = c_disp;
    }else{
        t->max_pares = p_disp;
    }
    if(t->max_pares >= t->capacidade){
        t->max_pares = t->capacidade;
    }
    
    //Alocacao de memoria para o vetor de pares
    vPares = malloc(sizeof(empar) * (t->max_pares));
    if(vPares == NULL){
        puts("\n[ERRO] Reserva de memoria falhada!\n");
        return;
    }
    
    //emparelhamento aleatorio dos pilotos com os carros
    for (int i=0; i < t->max_pares; i++){
        do{
            valid = 1;
            n_vetor = intUniformRnd(0, n_pilotos-1);
            
            for(int j = 0; j < i; j++){
                if(vpilotos[n_vetor].idP == vPares[j].motorista.idP){
                    valid = 0;
                }
            }
            if(vpilotos[n_vetor].impedimento != 0){
                valid = 0;
            }
        }while(valid == 0);
        
        vPares[i].id_par = i;
        vPares[i].motorista = vpilotos[n_vetor];
        
        do{
            valid = 1;
            n_vetor = intUniformRnd(0, n_carros-1);
            
            for(int j = 0; j < i; j++){
                if(vcarros[n_vetor].idC == vPares[j].kart.idC){
                    valid = 0;
                }
            }
            if(vcarros[n_vetor].avaria != 0){
                valid = 0;
            }
        }while(valid == 0);
        vPares[i].kart = vcarros[n_vetor];
        vPares[i].tempo = 0;
    }
    
    t->pares = vPares;
    
    //Mostragem de todos os emparelhamentos criados
    printf("\n#---------------------------------------------------------#");
    printf("\n      Pares (aleatorios) selecionados para a corrida:");
    printf("\n#---------------------------------------------------------#\n");
    for(int i=0; i<t->max_pares; i++){
        printf("\nPar (ID): %d | Piloto(%d): %s | Kart: %d", t->pares[i].id_par, t->pares[i].motorista.idP, t->pares[i].motorista.nome, t->pares[i].kart.idC);
    }
    printf("\n\n#---------------------------------------------------------#");
    printf("\n\nPressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    
    mostra_nao_selecionados(*t, vpilotos,  n_pilotos, vcarros, n_carros, c_disp, p_disp);
}

//funcao onde e exigida uma configuracao inicial para cada corrida
pTreino configuracao_corrida(pTreino corrida, pPiloto vp, int *t_p, pCarro vc, int *t_c){
    treino t;
    pTreino nova, aux;
    system("cls");
    
    nova = malloc(sizeof(treino));
    if(nova == NULL){
        printf("[Erro] Alocacao de memoria...\n");
        return corrida;
    }
    printf("\n#---------------------------------------------#");
    printf("\n           Configuracoes da corrida:");
    printf("\n#---------------------------------------------#\n");
    do{
        printf("\nNumero de voltas: ");
        scanf("%d", &t.n_voltas);
        if(t.n_voltas < 5 || t.n_voltas > 10){
            printf("\n[ERRO] Numero de voltas invalido! Tem de ser entre 5 a 10 voltas...");
        }
    }while(t.n_voltas < 5 || t.n_voltas > 10);
    do{
        printf("Comprimento da pista (m): ");
        scanf("%d", &t.comprimento);
        if(t.comprimento < 500 || t.comprimento > 1000){
            printf("\n[ERRO] Comprimento da pista invalido! Tem de ser entre 500 e 1000 metros...");
        }
    }while(t.comprimento < 500 || t.comprimento > 1000);
    do{
        printf("Numero maximo de carros: ");
        scanf("%d", &t.capacidade);
        if(t.capacidade <= 0){
            printf("\n[ERRO] Capacidade da pista invalida! Tem de ser superior a 0 carros...");
        }
    }while(t.capacidade <= 0);
    
    emparelhamento_pre_corrida(&t, vp, *t_p, vc, *t_c);
    
    nova->capacidade = t.capacidade;
    nova->comprimento = t.comprimento;
    nova->n_voltas = t.n_voltas;
    nova->max_pares = t.max_pares;
    nova->pares = t.pares;
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

//funcao onde e executada uma corrida
pTreino corrida_ativa(pTreino corrida, pPiloto vpilotos, int *tam_p, pCarro vcarros, int *tam_c){
    pTreino nova, aux;
    int idade;
    system("cls");
    
    nova = malloc(sizeof(treino));
    if(nova == NULL){
        printf("[Erro] Alocacao de memoria...\n");
        return corrida;
    }
    
    for(int i = 0; i < corrida->n_voltas; i++){
        nova->capacidade = corrida->capacidade;
        nova->comprimento = corrida->comprimento;
        nova->max_pares = corrida->max_pares;
        nova->n_voltas = corrida->n_voltas;
        nova->prox = NULL;
        nova->pares = corrida->pares;
        
        printf("\n\n#---------------------------------------------#");
        printf("\n           Classificacao da volta %d:", i);
        printf("\n#---------------------------------------------#\n");
        
        for(int j = 0; j < corrida->max_pares; j++){
            idade = calcula_idade(corrida->pares[j].motorista.data_nasc.dia, corrida->pares[j].motorista.data_nasc.mes, corrida->pares[j].motorista.data_nasc.ano);
            nova->pares[j].tempo = calculaSegundos(idade, corrida->pares[j].motorista.peso, corrida->pares[j].motorista.exp, corrida->pares[j].kart.pot, corrida->comprimento);
            printf("\n-> %d <- %s (ID: %d) | Kart: %d - %d segundos", j, corrida->pares[j].motorista.nome, corrida->pares[j].motorista.idP, corrida->pares[j].kart.idC, nova->pares[j].tempo);
        }
        aux = corrida;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = nova;
        if(i % 2 == 0){
            espera(5);
        }
    }
    return corrida;
}

//funcao onde e chamada a configuracao e executada uma corrida individual (treino)
pTreino corrida_individual(pTreino corrida, pPiloto vpilotos, int *tam_p, pCarro vcarros, int *tam_c){
    pTreino corrida_treino = NULL;
    
    corrida_treino = configuracao_corrida(corrida_treino, vpilotos, tam_p, vcarros, tam_c);
    corrida_treino = corrida_ativa(corrida_treino, vpilotos, tam_p, vcarros, tam_c);
    
    printf("\n\n       Pressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    
    return corrida;
}