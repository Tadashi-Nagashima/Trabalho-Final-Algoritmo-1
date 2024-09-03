/*
Nomes: Luiz Felipe Costa Camargo e Tadashi Bello Nagashima
Turma: EC41A - Algoritmos 1 - C11
Data: 
Enunciado: Desenvolver um programa em Linguagem C (ANSI C) para gerenciar e analisar dados relacionados ao Circuito Mundial de Corrida de Carrinho de Rolemã Senior. 
O sistema deve organizar e validar informações sobre atletas, treinamento/classificação, competições e resultados finais das provas.
A estrutura de dados será baseada em registros (structs) e vetores/matrizes.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAXPAISES 6
#define MAXNOME 50
#define MAXTREINO 7
#define MAXMELHORES 8

typedef struct data{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct atleta{
    char nome[MAXNOME];
    char pais[35];
    char sexo;
    Data nascimento;
} Atleta;

typedef struct competidor{
    Atleta atleta;
    int tempo[MAXTREINO];
} Competidor;

typedef struct competicao{
    char nome[MAXNOME];
    Data data;
    Competidor corredores[MAXMELHORES];
} Competicao;

int validar_data(Data nascimento);
int validar_nome(char nome[]);
int validar_sexo(char sexo);
int validar_pais(char pais[]);

int menu();
void menu_competicao(Atleta a1[], int qtd);
void cadastro(Atleta a1[], int qtd);
void iniciar_competicao(Competidor compet[], int qtd);

void treinamento(Atleta a1[], int qtd);
Competicao cadastrar_competicao(Atleta a1[], int qtd);

void preencher_atletas(Atleta a1[], int qtd); //função temporária

int contador = 15; // Se for usar a função preencher_atletas() alterar a variável para o número de atletas
int melhores[15];
int melhores_atletas[15];
Atleta atleta[100];
Competidor treino[100];

int main(){
    menu();
    
    return 0;
}

int menu(){
    int escolha = 0;
    
    
    printf("    _________________________________\n");
    printf("    |*******************************|\n");
    printf("    |Sistema Gerenciador de Corridas|\n");
    printf("    |*******************************|\n");
    printf("    |    1. Cadastrar Atleta        |\n");   
    printf("    |    2. Competição              |\n");
    printf("    |    3. Encerrar programa       |\n");
    printf("    |*******************************|\n\n");
    printf("    Escolha dentre as opções: ");
    
    while(1){
        scanf("%d", &escolha);
        getchar();
        
        switch(escolha){
            case 1:
                //cadastro(atleta, contador);
                preencher_atletas(atleta, contador); // Se for usar a função preencher_atletas() alterar a variável int contador para o número de atletas e quais atletas usar na função no final do programa
                break;
            case 2:
                menu_competicao(atleta, contador);
                break;
            case 3:
                printf("\n    Encerrando...\n");
                return 0;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                printf("Escolha dentre as opções acima: ");
        }  
    }
}
void menu_competicao(Atleta a1[], int qtd){
    int escolha = 0;
    Competicao competicao;
    Competidor competidores[100];
    
    printf("    _________________________________\n");
    printf("    |*******************************|\n");
    printf("    |     Gerenciar Competição      |\n");
    printf("    |*******************************|\n");
    printf("    |    1. Cadastrar Competição    |\n");   
    printf("    |    2. Treinamento             |\n");
    printf("    |    3. Iniciar Competição      |\n");
    printf("    |    4. Voltar                  |\n");
    printf("    |*******************************|\n\n");
    printf("    Escolha dentre as opções: ");
    
    while(1){
        scanf("%d", &escolha);
        getchar();
        
        switch(escolha){
            case 1:
                competicao = cadastrar_competicao(atleta, contador);
                break;
            case 2:
                treinamento(atleta, contador);
                break;
            case 3:
                iniciar_competicao(competidores, contador);
                break;
            case 4:
                menu();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                printf("Escolha dentre as opções acima: ");
        }  
    }
}
void cadastro(Atleta a1[], int qtd){
    int qtd_cadastro = 0;
    
    printf("\nDigite quantos cadastros gostaria de fazer: ");
    scanf("%d", &qtd_cadastro);
    getchar();
    
    for(; qtd < qtd_cadastro; qtd++){
        printf("\nCadastro do atleta número %d: ", (qtd + 1));
        // leitor de nomes
        do{
            printf("\nDigite o nome: ");
            fgets(a1[qtd].nome, MAXNOME, stdin);
            a1[qtd].nome[strlen(a1[qtd].nome) - 1] = '\0';
            
            if(validar_nome(a1[qtd].nome) == 0){
               printf("Informação inválida. Tente novamente."); 
            }
        }while(validar_nome(a1[qtd].nome) != 1);
        // leitor de datas
        do{
            printf("Digite a data de nascimento (dd/mm/yyyy): ");
            scanf("%d/%d/%d", &a1[qtd].nascimento.dia, &a1[qtd].nascimento.mes, &a1[qtd].nascimento.ano);
            getchar(); // tira o \n do scanf
            
            if(validar_data(a1[qtd].nascimento) == 0){
               printf("Informação inválida. Tente novamente.\n\n"); 
            }
            if(validar_data(a1[qtd].nascimento) == 2){
                printf("O atleta possuí menos de 45 anos\n");
                printf("Informação inválida. Tente novamente.\n\n");
            }
        }while(validar_data(a1[qtd].nascimento) != 1);
        // leitor de sexo
        do{
            printf("Digite o sexo: ");
            scanf("%c", &a1[qtd].sexo);
            getchar(); // tira o \n do scanf
            
            if(validar_sexo(a1[qtd].sexo) == 0){
               printf("Informação inválida. Tente novamente.\n\n"); 
            }
        }while(validar_sexo(a1[qtd].sexo) != 1);
        // leitor de países
        do{
            printf("Digite o país: ");
            fgets(a1[qtd].pais, 35, stdin);
            a1[qtd].pais[strlen(a1[qtd].pais) - 1] = '\0';
            
            if(validar_pais(a1[qtd].pais) == 0){
               printf("Informação inválida. Tente novamente.\n"); 
            }
        }while(validar_pais(a1[qtd].pais) != 1);
    }
    
    printf("\nCadastro(s) finalizado(s)\n\n");
    menu();
}

void ordenar_treino(Competidor t[], int qtd){
    int i = 0;
    int j = 0;
    int temp = 0;
    int temp_atleta = 0;
    //int melhores[qtd];
    //int melhores_atletas[qtd];
    
    for (i = 0; i < qtd; i++){
        melhores[i] = INT_MAX;
        for (j = 0; j < MAXTREINO; j++){
            if (t[i].tempo[j] < melhores[i]){
                melhores[i] = t[i].tempo[j];
                
            }
        }
        melhores_atletas[i] = i;
    }
    
    for (i = 0; i < qtd; i++){
        for (j = i + 1; j < qtd; j++){
            if (melhores[i] > melhores[j]){
                temp = melhores[i];
                melhores[i] = melhores[j];
                melhores[j] = temp;

                temp_atleta = melhores_atletas[i];
                melhores_atletas[i] = melhores_atletas[j];
                melhores_atletas[j] = temp_atleta;
            }
        }
    }
}
void treinamento(Atleta a1[], int qtd){
    
    int i = 0;
    int j = 0;
    int temp = 0;
    int temp_atleta = 0;
    char escolha;
    int melhores[qtd];
    int melhores_atletas[qtd];
    
    printf("\nFase de Treinamento:\n\n");
    for(i = 0; i < qtd; i++){
        strcpy(treino[i].atleta.nome, a1[i].nome);
    }
    while(escolha != 'S'){
        for(i = 0; i < qtd; i++){
            printf("\nAtleta %d: %s\n", i + 1, treino[i].atleta.nome);
        }

        printf("\nConfimar? S/N \n");
        scanf("%c", &escolha);
        getchar();
    }
    printf("\nConfimado\n");
    
    for(i = 0; i < qtd; i++){
        printf("\nAtleta %d: %s\n", i + 1, treino[i].atleta.nome);
        for(j = 0; j < MAXTREINO; j++){
            treino[i].tempo[j] = rand() % 101;
            printf("| %ds ", treino[i].tempo[j]);
        }
        printf("|\n\n");
    }
    
    for (i = 0; i < qtd; i++){
        melhores[i] = INT_MAX;
        for (j = 0; j < MAXTREINO; j++){
            if (treino[i].tempo[j] < melhores[i]){
                melhores[i] = treino[i].tempo[j];
                
            }
        }
        melhores_atletas[i] = i;
    }
    
    for (i = 0; i < qtd; i++){
        for (j = i + 1; j < qtd; j++){
            if (melhores[i] > melhores[j]){
                temp = melhores[i];
                melhores[i] = melhores[j];
                melhores[j] = temp;

                temp_atleta = melhores_atletas[i];
                melhores_atletas[i] = melhores_atletas[j];
                melhores_atletas[j] = temp_atleta;
            }
        }
    }
    
    printf("\nMelhores Tempos:\n");
    for(i = 0; i < MAXMELHORES; i++){
        printf("%s: %ds\n", treino[melhores_atletas[i]].atleta.nome, melhores[i]);
    }
    
    escolha = ' ';
    while(escolha != 'S'){
        printf("\nVoltar ao menu? S/N\n");
        scanf("%c", &escolha);
        getchar();
    }
    
    menu_competicao(atleta, contador);
}
int validar_nome(char nome[]){
    int i = 0;
    
    if(nome[0] == ' '){
        return 0;
    } else if(strlen(nome) <= 2){
        return 0;
    }
    for(i = 0; i < strlen(nome); i++){
        if(nome[i] >= '0' && nome[i] <= '9'){
            return 0;
        }
    }
    return 1;
}
int validar_sexo(char sexo){
    if(sexo != 'M' && sexo != 'F'){
        return 0;    
    } else{
        return 1;
    }
}
int validar_data(Data nascimento){
    // variáveis
    int maxdias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // processamento
    if(nascimento.mes == 2 && (((nascimento.ano % 4 == 0 && nascimento.ano % 100 != 0)) || nascimento.ano % 400 == 0)){
        maxdias[1] = 29;    // ano bissexto
    }
    if(nascimento.ano < 1900 || nascimento.ano > 1979){
        return 0;
    }
    if(nascimento.mes < 1 || nascimento.mes > 12){
        return 0;
    }
    if (nascimento.dia < 1 || nascimento.dia > maxdias[nascimento.mes - 1]){
        return 0;
    }
    if(nascimento.ano >= 1979 && nascimento.mes > 7){
        return 2;
    }
    return 1;   
}
int validar_pais(char pais[]){
    int i = 0;
    char paises_aceitos[MAXPAISES][35] = {"Brasil", "EUA", "Inglaterra", "Jamaica", "Arabia Saudita", "Estados Unidos"};
    if(pais[0] == ' '){
        return 0;
    } else if(strlen(pais) <= 2){
        return 0;
    }
    for(i = 0; i < strlen(pais); i++){
        if(pais[i] >= '0' && pais[i] <= '9'){
            return 0;
        }
    }
    
    for(i = 0; i < MAXPAISES; i++){
        if(strcasecmp(pais, paises_aceitos[i]) == 0){
            if(strcasecmp(pais, "Estados Unidos") == 0){
                strcpy(pais, "EUA"); 
            }
            return 1;
        }
    }
    return 0;
}
Competicao cadastrar_competicao(Atleta a1[], int qtd){
    Competicao competicao;
    int i = 0;
    char escolha;
    
    printf("\n\nCadastrar Competição:\n\n");
    
    printf("Nome da Competição: ");
    fgets(competicao.nome, MAXNOME, stdin);
    competicao.nome[strlen(competicao.nome) - 1] = '\0';
    
    printf("Data da Competição: ");
    scanf("%d/%d/%d", &competicao.data.dia, &competicao.data.mes, &competicao.data.ano);
    
    printf("Os corredores da competição são: ");
    
    while(escolha != 'S'){
       for(i = 0; i < qtd; i++){
            printf("\nAtleta %d: %s", i + 1, a1[i].nome);
        }
        getchar();
        printf("\nConfimar? S/N \n");
        scanf("%c", &escolha);
        
    }
    printf("\nConfimado\n");
    
    menu_competicao(atleta, contador);
    return competicao;
}
void iniciar_competicao(Competidor compet[], int qtd){
    int i = 0;
    int j = 0;
    int temp = 0;
    int temp_atleta = 0;
    int soma[MAXMELHORES];
    int soma_atletas[MAXMELHORES];
    int maior = 0;
    int menor = 0;
    for(i = 0; i < qtd; i++){
        strcpy(compet[i].atleta.nome, treino[i].atleta.nome);
    }
    
    ordenar_treino(treino, qtd);

    printf("\nAtletas Classificados:\n");
    
    for(i = 0; i < MAXMELHORES; i++){
        printf("\nAtleta %d: %s\n", i + 1, compet[melhores_atletas[i]].atleta.nome);
    }
    printf("\n\n");
    for(i = 0; i < MAXMELHORES; i++){
        int maior = INT_MIN;
        int menor = INT_MAX;
        soma[i] = 0;
        printf("\nAtleta %d: %s\n", i + 1, compet[melhores_atletas[i]].atleta.nome);
        for(j = 0; j < 5; j++){
            compet[melhores_atletas[i]].tempo[j] = rand() % 101;
            printf("| %ds ", compet[melhores_atletas[i]].tempo[j]);
            if (maior < compet[melhores_atletas[i]].tempo[j]){
                maior = compet[melhores_atletas[i]].tempo[j];
            }
            if (menor > compet[melhores_atletas[i]].tempo[j]){
                menor = compet[melhores_atletas[i]].tempo[j];
            }
            soma[i] += compet[melhores_atletas[i]].tempo[j];
        }
        printf("|\n\n");
        soma[i] = soma[i] - (maior + menor);
        printf("\nSoma: %d\n\n", soma[i]);
        soma_atletas[i] = melhores_atletas[i];
    }
    
    
    for (i = 0; i < MAXMELHORES; i++){
        
        for (j = i + 1; j < MAXMELHORES; j++){
            if (soma[i] > soma[j]){
                temp = soma[i];
                soma[i] = soma[j];
                soma[j] = temp;
                
                temp_atleta = soma_atletas[i];
                soma_atletas[i] = soma_atletas[j];
                soma_atletas[j] = temp_atleta;
            }
        }
    }
    printf("As 5 melhores somatórias dos tempos: \n\n");
    for(i = 0; i < 5; i++){
        printf("%s: %d\n", compet[soma_atletas[i]].atleta.nome,soma[i]);
    }
    
}
void preencher_atletas(Atleta a1[], int qtd){
    strcpy(a1[0].nome, "Ana dos Santos");
    strcpy(a1[0].pais, "Brasil");
    a1[0].sexo = 'F';https://www.onlinegdb.com/edit/jVlElyRwB#tab-stdin
    a1[0].nascimento.dia = 21;
    a1[0].nascimento.dia = 12;
    a1[0].nascimento.dia = 1979;
    
    strcpy(a1[1].nome, "John New");
    strcpy(a1[1].pais, "EUA");
    a1[1].sexo = 'M';
    a1[1].nascimento.dia = 15;
    a1[1].nascimento.dia = 2;
    a1[1].nascimento.dia = 1959;
    
    strcpy(a1[2].nome, "Helena Silveira");
    strcpy(a1[2].pais, "Brasil");
    a1[2].sexo = 'F';
    a1[2].nascimento.dia = 10;
    a1[2].nascimento.dia = 2;
    a1[2].nascimento.dia = 1979;
    
    strcpy(a1[3].nome, "Esther J. Sechrist");
    strcpy(a1[3].pais, "EUA");
    a1[3].sexo = 'F';
    a1[3].nascimento.dia = 2;
    a1[3].nascimento.dia = 7;
    a1[3].nascimento.dia = 1970;
    
    strcpy(a1[4].nome, "Keith V. Prentiss");
    strcpy(a1[4].pais, "EUA");
    a1[4].sexo = 'F';
    a1[4].nascimento.dia = 21;
    a1[4].nascimento.dia = 12;
    a1[4].nascimento.dia = 1974;
    
    strcpy(a1[5].nome, "John S. McKinnon");
    strcpy(a1[5].pais, "EUA");
    a1[5].sexo = 'M';
    a1[5].nascimento.dia = 16;
    a1[5].nascimento.dia = 12;
    a1[5].nascimento.dia = 1967;
    
    strcpy(a1[6].nome, "Alisha Marsh");
    strcpy(a1[6].pais, "Inglaterra");
    a1[6].sexo = 'M';
    a1[6].nascimento.dia = 21;
    a1[6].nascimento.dia = 2;
    a1[6].nascimento.dia = 1962;
    
    strcpy(a1[7].nome, "Callum Hall");
    strcpy(a1[7].pais, "Inglaterra");
    a1[7].sexo = 'M';
    a1[7].nascimento.dia = 8;
    a1[7].nascimento.dia = 4;
    a1[7].nascimento.dia = 1957;
    
    strcpy(a1[8].nome, "Niamh Archer");
    strcpy(a1[8].pais, "Inglaterra");
    a1[8].sexo = 'F';
    a1[8].nascimento.dia = 1;
    a1[8].nascimento.dia = 1;
    a1[8].nascimento.dia = 1979;
    
    strcpy(a1[9].nome, "Abdul Baasid al-Sadri");
    strcpy(a1[9].pais, "Arabia Saudita");
    a1[9].sexo = 'M';
    a1[9].nascimento.dia = 17;
    a1[9].nascimento.dia = 3;
    a1[9].nascimento.dia = 1969;
    
    strcpy(a1[10].nome, "Kaatima el-Nasser");
    strcpy(a1[10].pais, "Arabia Sauditat");
    a1[10].sexo = 'F';
    a1[10].nascimento.dia = 25;
    a1[10].nascimento.dia = 8;
    a1[10].nascimento.dia = 1970;
    
    strcpy(a1[11].nome, "Sharonda Powell ");
    strcpy(a1[11].pais, "Jamaica");
    a1[11].sexo = 'F';
    a1[11].nascimento.dia = 8;
    a1[11].nascimento.dia = 8;
    a1[11].nascimento.dia = 1978;
    
    strcpy(a1[12].nome, "João Silva");
    strcpy(a1[12].pais, "Brasil");
    a1[12].sexo = 'M';
    a1[12].nascimento.dia = 2;
    a1[12].nascimento.dia = 1;
    a1[12].nascimento.dia = 1979;
    
    strcpy(a1[13].nome, "Usain Bolt");
    strcpy(a1[13].pais, "Jamaica");
    a1[13].sexo = 'M';
    a1[13].nascimento.dia = 1;
    a1[13].nascimento.dia = 10;
    a1[13].nascimento.dia = 1963;
    
    strcpy(a1[14].nome, "Haibaa el-Fayad");
    strcpy(a1[14].pais, "Arabia Sauditat");
    a1[14].sexo = 'F';
    a1[14].nascimento.dia = 3;
    a1[14].nascimento.dia = 6;
    a1[14].nascimento.dia = 1965;
    
    qtd = 15;
    
    printf("\nCadastro(s) finalizado(s)\n\n");
    menu();
}
