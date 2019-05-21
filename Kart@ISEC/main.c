/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 *
 * Created on 20 de Março de 2019, 10:58
 */

#include "Kart_Structs.h"

//contador de pilotos no ficheiro
int tam_vetor_pilotos(char *fichpilotos){
    
    piloto existe;
    int i = 0;
    
    FILE *fp = fopen(fichpilotos,"rt");
    if(!fp){
        printf("\n[ERRO] Abertura do ficheiro %s falhada!\n",fichpilotos);
        printf("\n#-------------------------------------------#");
        printf("\n\nCarregue no ENTER para continuar...");
        fflush(stdin);
        getchar();
        exit(0);
    }
    while(fscanf(fp,"%99[^\n] %d %d %d %d %d %f %d\n", existe.nome, &existe.id, &existe.data_nasc.dia, &existe.data_nasc.mes, &existe.data_nasc.ano, &existe.peso, &existe.exp, &existe.impedimento) == 8){
        i++;
    }
#ifdef deb
    printf("\nForam carregados %d PILOTOS do ficheiro!!!\n",i);
#endif
    
    fclose(fp);
    return i;
}

//contador de carros no ficheiro
int tam_vetor_carros(char *fichcarros){
    
    carro existe;
    int i = 0;
    
    FILE *fc = fopen(fichcarros,"rt");
    if(!fc){
        printf("\n[ERRO] Abertura do ficheiro %s falhada!\n", fichcarros);
        printf("\n#-------------------------------------------#");
        printf("\n\nCarregue no ENTER para continuar...");
        fflush(stdin);
        getchar();
        exit(0);
    }
    
    while(fscanf(fc,"%d %d %d\n", &existe.id, &existe.pot, &existe.avaria) == 3){
        i++;
    }
    
#ifdef deb
    printf("\nForam carregados %d CARROS do ficheiro!!!\n",i);
#endif
    
    fclose(fc);
    return i;
}

//funcao que importa os pilotos do ficheiro para um vetor dinamico
pPiloto vetor_pilotos(char *nomefich, int *tam){
    
    pPiloto vPiloto = NULL;
    piloto novo;
    
    *tam = tam_vetor_pilotos(nomefich);
    
    FILE *f = fopen(nomefich, "rt");
    if(!f){
        printf("\n[ERRO] Abertura do ficheiro %s falhada!\n",nomefich);
        printf("\n#-------------------------------------------#");
        printf("\n\nCarregue no ENTER para continuar...");
        fflush(stdin);
        getchar();
        exit(0);
    }
    
    for(int i = 0; i < (*tam); i++){
        if(!vPiloto){                                                            //caso nao exista nada no vetor das violas, aloca-se espaço consoante o tamanho do vetor
            vPiloto = malloc(sizeof(piloto)*(*tam));
        }
        if(vPiloto == NULL){
            puts("\n[ERRO] Reserva de memoria falhada!\n");
            fclose(f);
            return vPiloto;
        }
        if(fscanf(f,"%99[^\n] %d %d %d %d %d %f %d\n", novo.nome, &novo.id, &novo.data_nasc.dia, &novo.data_nasc.mes, &novo.data_nasc.ano, &novo.peso, &novo.exp, &novo.impedimento) != 8){     //le o ficheiro
            printf("\n[Erro] Leitura do ficheiro %s falhada! Formato Incorreto!!\n",nomefich);
            fclose(f);
            free(vPiloto);
            exit(0);
        }
        for(int j = 0; j < i; j++){
            if(novo.id == vPiloto[j].id){
                printf("\n[Erro] Parametros do ficheiro %s incorretos! (ID %d repetido)\n",nomefich, novo.id);
                fclose(f);
                free(vPiloto);
                exit(0);
            }
        }
#ifdef deb
        printf("\n%s\n %d %d %d %d %d %.1f %d\n", novo.nome, novo.id, novo.data_nasc.dia, novo.data_nasc.mes, novo.data_nasc.ano, novo.peso, novo.exp, novo.impedimento);
#endif
        vPiloto[i] = novo;
    }
    
    fclose(f);
    return vPiloto;
}

//funcao que importa os carros do ficheiro para um vetor dinamico
pCarro vetor_carros(char *nomefich, int *tam){
    
    pCarro vCarro = NULL;
    carro novo;
    
    int i;
    
    *tam = tam_vetor_carros(nomefich);
    
    FILE *f = fopen(nomefich, "rt");
    if(!f){
        printf("\n[ERRO] Abertura do ficheiro %s falhada!\n",nomefich);
        printf("\n#-------------------------------------------#");
        printf("\n\nCarregue no ENTER para continuar...");
        fflush(stdin);
        getchar();
        exit(0);
    }
    
    for(i = 0; i < (*tam); i++){
        if(!vCarro){                                                            //caso nao exista nada no vetor das violas, aloca-se espaço consoante o tamanho do vetor
            vCarro = malloc(sizeof(carro)*(*tam));
        }
        if(vCarro == NULL){
            puts("\n[Erro] Reserva de memoria falhada!\n");
            fclose(f);
            return vCarro;
        }
        if(fscanf(f,"%d %d %d\n", &novo.id, &novo.pot, &novo.avaria) != 3){     //le o ficheiro
            printf("[Erro] Leitura do ficheiro %s falhada! Formato Incorreto!!",nomefich);
            fclose(f);
            free(vCarro);
            return vCarro;
        }
#ifdef deb
        printf("\n%d %d %d\n", novo.id, novo.pot, novo.avaria);
#endif
        
        vCarro[i] = novo;
    }
    
    fclose(f);
    return vCarro;
}

//funcao que mostra todos os pilotos ou carros existentes
void mostraVetores(pCarro vCarro, int *tam_Carros, pPiloto vPiloto, int *tam_Pilotos, int op){
    
    int i;
    
    system("cls");
    
    if(op == 0){
        printf("\n              Lista de Carros:\n");
        printf("\n#--------------------------------------------#");
        printf("\n\tID\tPotencia\tAvaria\t\n");
        for(i = 0; i < (*tam_Carros); i++){
            printf("\n\t%d\t%d\t\t%d", vCarro[i].id, vCarro[i].pot, vCarro[i].avaria);
        }
        printf("\n#--------------------------------------------#");
    }else{
        printf("\n                                          Lista de Pilotos:\n");
        printf("\n#---------------------------------------------------------------------------------------------------------#");
        printf("\n\tID\tNome\t\t\tData de nascimento\tPeso\tImpedimento\tExperiencia\n");
        for(i = 0; i < (*tam_Pilotos); i++){
            printf("\n\t%d\t%-25s%d/%d/%d\t\t%d Kg\t%d\t\t%.2f", vPiloto[i].id, vPiloto[i].nome,vPiloto[i].data_nasc.dia, vPiloto[i].data_nasc.mes, vPiloto[i].data_nasc.ano, vPiloto[i].peso, vPiloto[i].impedimento, vPiloto[i].exp);
        }
        printf("\n#---------------------------------------------------------------------------------------------------------#");
    }
    printf("\n\nCarregue no ENTER para continuar...");
    fflush(stdin);
    getchar();
    return;
}

void logotipo(){
    
    printf("\n#-------------------------------------------#");
    printf("\n|             <=| Kart@ISEC |=>             |");
    printf("\n#-------------------------------------------#\n");
    return;
}

void grava_fich_pilotos(char *nomefich, pPiloto vPilotos, int tam){
    
    int i;
    
    FILE *fp = fopen(nomefich,"wt");                                            //abre para escrever e cria se nao existir
    if(!fp){
        printf("\n[ERRO] Abertura do ficheiro %s falhada!\n",nomefich);
        return;
    }
    for(i = 0; i < (tam); i++){                                                 //ciclo que escreve o vetor dos pilotos todos no ficheiro
       if(fprintf(fp, "%s\n%d %d %d %d %d %.2f %d\n\n", vPilotos[i].nome, vPilotos[i].id, vPilotos[i].data_nasc.dia, vPilotos[i].data_nasc.mes, vPilotos[i].data_nasc.ano,vPilotos[i].peso,vPilotos[i].exp,vPilotos[i].impedimento) < 0){
           printf("\n[ERRO] Escrita no ficheiro %s falhada!\n",nomefich);
           fclose(fp);
       }
    }
    fclose(fp);
}

void grava_fich_carros(char *nomefich, pCarro vCarros, int tam){
    
    int i;
    
    FILE *fc = fopen(nomefich,"wt");                                            //abre para escrever e cria se nao existir
    if(!fc){
        printf("\n[ERRO] Abertura do ficheiro %s falhada!\n",nomefich);
        return;
    }
    for(i = 0; i < (tam); i++){                                                 //ciclo que escreve o vetor dos carros todos no ficheiro
       if(fprintf(fc, "%d %d %d\n\n", vCarros[i].id, vCarros[i].pot, vCarros[i].avaria) < 0){
           printf("\n[ERRO] Escrita no ficheiro %s falhada!\n",nomefich);
           fclose(fc);
       }
    }
    fclose(fc);
}

int terminaProg(char *fichpilotos, char *fichcarros, pPiloto vpilotos, int *tam_pilotos, pCarro vcarros, int *tam_carros) {

    int sair;
    
    do {
        system("cls");
        printf("\n#-------------------------------------------#");
        printf("\n|           <=|  Kart@ISEC  |=>             |");
        printf("\n|-------------------------------------------|");
        printf("\n|    Tem a certeza de que deseja sair?      |");
        printf("\n|                                           |");
        printf("\n|                 1 - Nao                   |");
        printf("\n|                 2 - Sim                   |");
        printf("\n|                                           |");
        printf("\n#-------------------------------------------#");

        printf("\nOpcao: ");
        sair = 0;
        scanf("%d", &sair);

        switch (sair) {
            case 1:
                return 0;
            case 2:
                grava_fich_pilotos(fichpilotos, vpilotos, *tam_pilotos);                 //guarda as informacoes dos cliente no ficheiro BaseDados.txt
                grava_fich_carros(fichcarros,vcarros,*tam_carros);                       //guarda as informacoes das violas no ficheiro Stock.txt
                exit(0);
        }
    } while (sair != 1 || sair != 2);
}

int main(int argc, char** argv) {

    int op, tam_pilotos = 0, tam_carros = 0;

    pPiloto vPilotos = NULL;
    pCarro vCarros = NULL;

    char *pilotosTxt = "Pilotos.txt";
    char *carrosTxt = "Carros.txt";

    logotipo();
    printf("\n\n     Pressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    
    //Carregar pilotos e carros dos ficheiros txt
    vPilotos = vetor_pilotos(pilotosTxt, &tam_pilotos);
    vCarros = vetor_carros(carrosTxt, &tam_carros);
    
#ifdef deb
    printf("\n\nPressione ENTER para continuar...");
    fflush(stdin);
    getchar();
#endif
    
    do {
        system("cls");

        printf("\n             Menu Principal:\n");
        printf("\n         1 - Lista de Pilotos");
        printf("\n         2 - Lista de Carros");
        printf("\n         3 - Modo Treino");
        printf("\n         4 - Modo Campeonato");
        printf("\n         5 - Sair");

        printf("\n\nOpcao: ");
        op = 0;
        scanf("%d", &op);

        switch (op) {
            case 1:
                mostraVetores(NULL, NULL, vPilotos, &tam_pilotos, 1);
                break;
            case 2:
                mostraVetores(vCarros, &tam_carros, NULL, NULL, 0);
                break;
            case 3:
                //treino();
                break;
            case 4:
                //campeonato();
                break;
            case 5:
                terminaProg(pilotosTxt, carrosTxt, vPilotos, &tam_pilotos, vCarros, &tam_carros);
                break;
        }
    } while (1);
    
    return (EXIT_SUCCESS);
}


