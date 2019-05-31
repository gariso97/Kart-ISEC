/* 
 * File:   main.c
 * Author: Bruno Miguel Gariso Andrade Rodrigues
 * Number: 21250105
 *
 */

#include "Corridas.h"


//funcao que calcula a idade do piloto
int calcula_idade(int P_dia, int P_mes, int P_ano){
    int i = 0, dia, mes, ano, hora, minuto, seg;
    
    obtemData(&dia, &mes, &ano, &hora, &minuto, &seg);
    if (mes <= P_mes)
        if (dia <= P_dia)
            i = ano - P_ano - 1;
        else
            i = ano - P_ano - 1;
    else
        i = ano - P_ano;
    return i;
}

//funcao que valida uma determinada data
int valida_data(int dia, int mes, int ano){
    int bissexto = 0, valida = 1;
 
    if (ano >= 1900 && ano <= 9999){
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)){          // verifica se o ano é bissexto ou não
            bissexto = 1;
        }
        if(mes >= 1 && mes <= 12){                                          // verifica se o mes está entre 1 e 12
            if (mes == 2){                                                  // verifica os dias em Fevereiro
                if (bissexto && dia == 29){
                    valida = 1;
                }else if (dia > 28){
                    valida = 0;
                }
            }else if (mes == 4 || mes == 6 || mes == 9 || mes == 11){       // verifica os meses com 30 dias
                if (dia > 30 || dia <= 0){
                    valida = 0;
                }
            }else if(dia > 31 || dia <= 0){                                 // verifica os meses com 31 dias
                valida = 0;
            }
        }else{
            valida = 0;
        }
    }else{
        valida = 0;
    }
    
    if(valida){
        return 1;
    }else{
        return 0;
    }
}

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
    while(fscanf(fp,"%99[^\n] %d %d %d %d %d %f %d\n", existe.nome, &existe.idP, &existe.data_nasc.dia, &existe.data_nasc.mes, &existe.data_nasc.ano, &existe.peso, &existe.exp, &existe.impedimento) == 8){
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
    
    while(fscanf(fc,"%d %d %d\n", &existe.idC, &existe.pot, &existe.avaria) == 3){
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
        if(fscanf(f,"%99[^\n] %d %d %d %d %d %f %d\n", novo.nome, &novo.idP, &novo.data_nasc.dia, &novo.data_nasc.mes, &novo.data_nasc.ano, &novo.peso, &novo.exp, &novo.impedimento) != 8){     //le o ficheiro
            printf("\n[Erro] Leitura do ficheiro %s falhada! Formato Incorreto!!\n",nomefich);
            fclose(f);
            free(vPiloto);
            exit(0);
        }
        for(int j = 0; j < i; j++){
            if(novo.idP == vPiloto[j].idP){
                printf("\n[Erro] Parametros do ficheiro %s incorretos! (ID %d repetido)\n",nomefich, novo.idP);
                fclose(f);
                free(vPiloto);
                exit(0);
            }
        }
        if(strlen(novo.nome) > 100){
            printf("\n[Erro] Parametros do ficheiro %s incorretos! (Nome %s excede os 100 caracteres no piloto com ID %d)\n", nomefich, novo.nome, novo.idP);
            fclose(f);
            free(vPiloto);
            exit(0);
        }
        if(valida_data(novo.data_nasc.dia, novo.data_nasc.mes, novo.data_nasc.ano) == 0){
            printf("\n[Erro] Parametros do ficheiro %s incorretos! (Data %d/%d/%d invalida no piloto com ID %d)\n", nomefich, novo.data_nasc.dia, novo.data_nasc.mes, novo.data_nasc.ano, novo.idP);
            fclose(f);
            free(vPiloto);
            exit(0);
        }
        if(novo.peso <= 0){
            printf("\n[Erro] Parametros do ficheiro %s incorretos! (Peso %d invalido no piloto com ID %d)\n", nomefich, novo.peso, novo.idP);
            fclose(f);
            free(vPiloto);
            exit(0);
        }
        if(novo.impedimento < 0 || novo.impedimento > 3){
            printf("\n[Erro] Parametros do ficheiro %s incorretos! (Impedimento %d invalido no piloto com ID %d)\n", nomefich, novo.peso, novo.idP);
            fclose(f);
            free(vPiloto);
            exit(0);
        }
        if(novo.exp < 0){
            printf("\n[Erro] Parametros do ficheiro %s incorretos! (Experiencia %.2f invalida no piloto com ID %d)\n", nomefich, novo.exp, novo.idP);
            fclose(f);
            free(vPiloto);
            exit(0);
        }
#ifdef deb
        printf("\n%s\n %d %d %d %d %d %.1f %d\n", novo.nome, novo.idP, novo.data_nasc.dia, novo.data_nasc.mes, novo.data_nasc.ano, novo.peso, novo.exp, novo.impedimento);
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
        if(fscanf(f,"%d %d %d\n", &novo.idC, &novo.pot, &novo.avaria) != 3){     //le o ficheiro
            printf("[Erro] Leitura do ficheiro %s falhada! Formato Incorreto!!",nomefich);
            fclose(f);
            free(vCarro);
            return vCarro;
        }
        
        ///
        for(int j = 0; j < i; j++){
            if(novo.idC == vCarro[j].idC){
                printf("\n[Erro] Parametros do ficheiro %s incorretos! (ID %d repetido)\n",nomefich, novo.idC);
                fclose(f);
                free(vCarro);
                exit(0);
            }
        }
        if(novo.pot <= 0){
            printf("\n[Erro] Parametros do ficheiro %s incorretos! (Potencia %d invalida no carro com ID %d)\n", nomefich, novo.pot, novo.idC);
            fclose(f);
            free(vCarro);
            exit(0);
        }
        if(novo.avaria < 0 || novo.avaria > 1){
            printf("\n[Erro] Parametros do ficheiro %s incorretos! (Avaria %d invalida no carro com ID %d)\n", nomefich, novo.avaria, novo.idC);
            fclose(f);
            free(vCarro);
            exit(0);
        }
#ifdef deb
        printf("\n%d %d %d\n", novo.idC, novo.pot, novo.avaria);
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
            printf("\n\t%d\t%d\t\t%d", vCarro[i].idC, vCarro[i].pot, vCarro[i].avaria);
        }
        printf("\n#--------------------------------------------#");
    }else{
        printf("\n                                          Lista de Pilotos:\n");
        printf("\n#---------------------------------------------------------------------------------------------------------#");
        printf("\n\tID\tNome\t\t\tData de nascimento\tPeso\tImpedimento\tExperiencia\n");
        for(i = 0; i < (*tam_Pilotos); i++){
            printf("\n\t%d\t%-25s%d/%d/%d\t\t%d Kg\t%d\t\t%.2f", vPiloto[i].idP, vPiloto[i].nome,vPiloto[i].data_nasc.dia, vPiloto[i].data_nasc.mes, vPiloto[i].data_nasc.ano, vPiloto[i].peso, vPiloto[i].impedimento, vPiloto[i].exp);
        }
        printf("\n#---------------------------------------------------------------------------------------------------------#");
    }
    printf("\n\nCarregue no ENTER para continuar...");
    fflush(stdin);
    getchar();
    return;
}

//funcao que imprime o logotipo do programa
void logotipo(){
    
    printf("\n#-------------------------------------------#");
    printf("\n|             <=| Kart@ISEC |=>             |");
    printf("\n#-------------------------------------------#\n");
    return;
}

//funcao que grava os pilotos no ficheiro indicado
void grava_fich_pilotos(char *nomefich, pPiloto vPilotos, int tam){
    
    int i;
    
    FILE *fp = fopen(nomefich,"wt");                                            //abre para escrever e cria se nao existir
    if(!fp){
        printf("\n[ERRO] Abertura do ficheiro %s falhada!\n",nomefich);
        return;
    }
    for(i = 0; i < (tam); i++){                                                 //ciclo que escreve o vetor dos pilotos todos no ficheiro
       if(fprintf(fp, "%s\n%d %d %d %d %d %.2f %d\n\n", vPilotos[i].nome, vPilotos[i].idP, vPilotos[i].data_nasc.dia, vPilotos[i].data_nasc.mes, vPilotos[i].data_nasc.ano,vPilotos[i].peso,vPilotos[i].exp,vPilotos[i].impedimento) < 0){
           printf("\n[ERRO] Escrita no ficheiro %s falhada!\n",nomefich);
           fclose(fp);
       }
    }
    fclose(fp);
}

//funcao que grava os carros no ficheiro indicado
void grava_fich_carros(char *nomefich, pCarro vCarros, int tam){
    
    int i;
    
    FILE *fc = fopen(nomefich,"wt");                                            //abre para escrever e cria se nao existir
    if(!fc){
        printf("\n[ERRO] Abertura do ficheiro %s falhada!\n",nomefich);
        return;
    }
    for(i = 0; i < (tam); i++){                                                 //ciclo que escreve o vetor dos carros todos no ficheiro
       if(fprintf(fc, "%d %d %d\n\n", vCarros[i].idC, vCarros[i].pot, vCarros[i].avaria) < 0){
           printf("\n[ERRO] Escrita no ficheiro %s falhada!\n",nomefich);
           fclose(fc);
       }
    }
    fclose(fc);
}

//funcao que marca o inicio do campeonato
int certeza_campeonato(){
    int op;
    system("cls");
    printf("\n#---------------------------------------------#");
    printf("\n           =$|| Modo campeonato ||$=");
    printf("\n#---------------------------------------------#\n");
    printf("\nNao podera efetuar corridas de treino!!\n"
            "Tem de acabar OBRIGATORIAMENTE toda a temporada!!\n"
            "Tem a certeza que deseja comecar o MODO CAMPEONATO?\n\n"
            "Opcao (Sim - 1 | Nao - 2): ");
    do {
        scanf("%d", &op);
        if (op == 2) {
            return 0;
        }else if(op == 1){
            do{
                printf("Numero total de corridas no campeonato [3-8]: ");
                scanf("%d", &op);
                if(op < 3 || op > 8){
                    printf("[ERRO] O numero de corridas no campeonato deve ser entre 3 e 8...\n");
                }
            }while(op < 3 || op > 8);
            return op;
        }else{
            printf("[ERRO] Opcao incorreta...\n");
        }
    }while(1);
}

//funcao que da a escolher ao utilizador se pretende terminar o programa ou nao
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

//funcao principal, onde comeca o programa e e' apresentado o menu principal
int main(int argc, char** argv) {
/*
    testes();
    exit(0);
*/
    int op, partidas, camp = 0, tam_pilotos = 0, tam_carros = 0;
    pPiloto vPilotos = NULL;
    pCarro vCarros = NULL;
    pTreino corrida = NULL;
    pCamp campeonato = NULL;
    char *pilotosTxt = "Pilotos.txt";
    char *carrosTxt = "Carros.txt";
    
    logotipo();
    printf("\n\n       Pressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    
    initRandom();
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
        logotipo();
        printf("\n               Menu Principal:\n");
        printf("#-------------------------------------------#\n");
        printf("\n           1 - Lista de Pilotos");
        printf("\n           2 - Lista de Carros");
        if(camp != 1){
            printf("\n           3 - Modo Individual");
        }else{
            printf("\n           3 - Modo Individual (NA)");
        }
        printf("\n           4 - Modo Campeonato");
        printf("\n           5 - Sair");

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
                if(camp != 1)
                    corrida = realizar_corrida(corrida, vPilotos, &tam_pilotos, vCarros, &tam_carros);
                break;
            case 4:
                if(camp != 1){
                    campeonato->corridas_total = certeza_campeonato();
                    if(campeonato->corridas_total != 0)
                        camp = 1;
                }else{
                    //campeonato = campeonato(campeonato, vPilotos, &tam_pilotos, vCarros, &tam_carros);
                    if(campeonato->corridas_total <= 1)
                        camp = 0;
                }
                break;
            case 5:
                terminaProg(pilotosTxt, carrosTxt, vPilotos, &tam_pilotos, vCarros, &tam_carros);
                break;
        }
    } while (1);
    
    return (EXIT_SUCCESS);
}


