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
void menu_competicao();
void cadastro();
void treinamento();
void cadastrar_competicao();

void preencher_atletas (); //função temporária

int contador = 0; // Se for usar a função preencher_atletas() alterar a variável para o número de atletas
Atleta atleta[100];

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
                cadastro();
                //preencher_atletas(); // Se for usar a função preencher_atletas() alterar a variável int contador para o número de atletas e quais atletas usar na função no final do programa
                break;
            case 2:
                menu_competicao();
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
void menu_competicao(){
    int escolha = 0;
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
                cadastrar_competicao();
                break;
            case 2:
                treinamento();
                break;
            case 3:
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
void cadastro(){
    int qtd_cadastro = 0;
    
    printf("\nDigite quantos cadastros gostaria de fazer: ");
    scanf("%d", &qtd_cadastro);
    getchar();
    
    for(; contador < qtd_cadastro; contador++){
        printf("\nCadastro do atleta número %d: ", (contador + 1));
        // leitor de nomes
        do{
            printf("\nDigite o nome: ");
            fgets(atleta[contador].nome, MAXNOME, stdin);
            atleta[contador].nome[strlen(atleta[contador].nome) - 1] = '\0';
            
            if(validar_nome(atleta[contador].nome) == 0){
               printf("Informação inválida. Tente novamente."); 
            }
        }while(validar_nome(atleta[contador].nome) != 1);
        // leitor de datas
        do{
            printf("Digite a data de nascimento (dd/mm/yyyy): ");
            scanf("%d/%d/%d", &atleta[contador].nascimento.dia, &atleta[contador].nascimento.mes, &atleta[contador].nascimento.ano);
            getchar(); // tira o \n do scanf
            
            if(validar_data(atleta[contador].nascimento) == 0){
               printf("Informação inválida. Tente novamente.\n\n"); 
            }
            if(validar_data(atleta[contador].nascimento) == 2){
                printf("O atleta possuí menos de 45 anos\n");
                printf("Informação inválida. Tente novamente.\n\n");
            }
        }while(validar_data(atleta[contador].nascimento) != 1);
        // leitor de sexo
        do{
            printf("Digite o sexo: ");
            scanf("%c", &atleta[contador].sexo);
            getchar(); // tira o \n do scanf
            
            if(validar_sexo(atleta[contador].sexo) == 0){
               printf("Informação inválida. Tente novamente.\n\n"); 
            }
        }while(validar_sexo(atleta[contador].sexo) != 1);
        // leitor de países
        do{
            printf("Digite o país: ");
            fgets(atleta[contador].pais, 35, stdin);
            atleta[contador].pais[strlen(atleta[contador].pais) - 1] = '\0';
            
            if(validar_pais(atleta[contador].pais) == 0){
               printf("Informação inválida. Tente novamente.\n"); 
            }
        }while(validar_pais(atleta[contador].pais) != 1);
    }
    
    printf("\nCadastro(s) finalizado(s)\n\n");
    menu();
}
void treinamento(){
    Competidor treino[50];
    int i = 0;
    int j = 0;
    int temp = 0;
    int temp_atleta = 0;
    char escolha;
    int melhores[contador];
    int melhores_atletas[contador];
    
    printf("\nFase de Treinamento:\n\n");
    for(i = 0; i < contador; i++){
        strcpy(treino[i].atleta.nome, atleta[i].nome);
    }
    while(escolha != 'S'){
        for(i = 0; i < contador; i++){
            printf("\nAtleta %d: %s\n", i + 1, treino[i].atleta.nome);
        }

        printf("\nConfimar? S/N \n");
        scanf("%c", &escolha);
        getchar();
    }
    printf("\nConfimado\n");
    
    for(i = 0; i < contador; i++){
        printf("\nAtleta %d: %s\n", i + 1, treino[i].atleta.nome);
        for(j = 0; j < MAXTREINO; j++){
            treino[i].tempo[j] = rand() % 101;
            printf("| %ds ", treino[i].tempo[j]);
        }
        printf("|\n\n");
    }
    
    for (i = 0; i < contador; i++){
        melhores[i] = INT_MAX;
        for (j = 0; j < MAXTREINO; j++){
            if (treino[i].tempo[j] < melhores[i]){
                melhores[i] = treino[i].tempo[j];
                
            }
        }
        melhores_atletas[i] = i;
    }
    
    for (i = 0; i < contador; i++){
        for (j = i + 1; j < contador; j++){
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
void cadastrar_competicao(){
    Competicao competicao;
    
    printf("\n\nCadastrar Competição:\n\n");
    
    printf("Nome da Competição: ");
    fgets(competicao.nome, MAXNOME, stdin);
    competicao.nome[strlen(competicao.nome) - 1] = '\0';
    
    printf("Data da Competição: ");
    scanf("%d/%d/%d", &competicao.data.dia, &competicao.data.mes, &competicao.data.ano);
    
    
    
}
void preencher_atletas(){
    strcpy(atleta[0].nome, "Ana dos Santos");
    strcpy(atleta[0].pais, "Brasil");
    atleta[0].sexo = 'F';
    atleta[0].nascimento.dia = 21;
    atleta[0].nascimento.dia = 12;
    atleta[0].nascimento.dia = 1979;
    
    strcpy(atleta[1].nome, "John New");
    strcpy(atleta[1].pais, "EUA");
    atleta[1].sexo = 'M';
    atleta[1].nascimento.dia = 15;
    atleta[1].nascimento.dia = 2;
    atleta[1].nascimento.dia = 1959;
    
    strcpy(atleta[2].nome, "Helena Silveira");
    strcpy(atleta[2].pais, "Brasil");
    atleta[2].sexo = 'F';
    atleta[2].nascimento.dia = 10;
    atleta[2].nascimento.dia = 2;
    atleta[2].nascimento.dia = 1979;
    
    strcpy(atleta[3].nome, "Esther J. Sechrist");
    strcpy(atleta[3].pais, "EUA");
    atleta[3].sexo = 'F';
    atleta[3].nascimento.dia = 2;
    atleta[3].nascimento.dia = 7;
    atleta[3].nascimento.dia = 1970;
    
    strcpy(atleta[4].nome, "Keith V. Prentiss");
    strcpy(atleta[4].pais, "EUA");
    atleta[4].sexo = 'F';
    atleta[4].nascimento.dia = 21;
    atleta[4].nascimento.dia = 12;
    atleta[4].nascimento.dia = 1974;
    
    strcpy(atleta[5].nome, "John S. McKinnon");
    strcpy(atleta[5].pais, "EUA");
    atleta[5].sexo = 'M';
    atleta[5].nascimento.dia = 16;
    atleta[5].nascimento.dia = 12;
    atleta[5].nascimento.dia = 1967;
    
    strcpy(atleta[6].nome, "Alisha Marsh");
    strcpy(atleta[6].pais, "Inglaterra");
    atleta[6].sexo = 'M';
    atleta[6].nascimento.dia = 21;
    atleta[6].nascimento.dia = 2;
    atleta[6].nascimento.dia = 1962;
    
    strcpy(atleta[7].nome, "Callum Hall");
    strcpy(atleta[7].pais, "Inglaterra");
    atleta[7].sexo = 'M';
    atleta[7].nascimento.dia = 8;
    atleta[7].nascimento.dia = 4;
    atleta[7].nascimento.dia = 1957;
    
    strcpy(atleta[8].nome, "Niamh Archer");
    strcpy(atleta[8].pais, "Inglaterra");
    atleta[8].sexo = 'F';
    atleta[8].nascimento.dia = 1;
    atleta[8].nascimento.dia = 1;
    atleta[8].nascimento.dia = 1979;
    
    strcpy(atleta[9].nome, "Abdul Baasid al-Sadri");
    strcpy(atleta[9].pais, "Arabia Saudita");
    atleta[9].sexo = 'M';
    atleta[9].nascimento.dia = 17;
    atleta[9].nascimento.dia = 3;
    atleta[9].nascimento.dia = 1969;
    
    strcpy(atleta[10].nome, "Kaatima el-Nasser");
    strcpy(atleta[10].pais, "Arabia Sauditat");
    atleta[10].sexo = 'F';
    atleta[10].nascimento.dia = 25;
    atleta[10].nascimento.dia = 8;
    atleta[10].nascimento.dia = 1970;
    
    strcpy(atleta[11].nome, "Sharonda Powell ");
    strcpy(atleta[11].pais, "Jamaica");
    atleta[11].sexo = 'F';
    atleta[11].nascimento.dia = 8;
    atleta[11].nascimento.dia = 8;
    atleta[11].nascimento.dia = 1978;
    
    strcpy(atleta[12].nome, "João Silva");
    strcpy(atleta[12].pais, "Brasil");
    atleta[12].sexo = 'M';
    atleta[12].nascimento.dia = 2;
    atleta[12].nascimento.dia = 1;
    atleta[12].nascimento.dia = 1979;
    
    strcpy(atleta[13].nome, "Usain Bolt");
    strcpy(atleta[13].pais, "Jamaica");
    atleta[13].sexo = 'M';
    atleta[13].nascimento.dia = 1;
    atleta[13].nascimento.dia = 10;
    atleta[13].nascimento.dia = 1963;
    
    strcpy(atleta[14].nome, "Haibaa el-Fayad");
    strcpy(atleta[14].pais, "Arabia Sauditat");
    atleta[14].sexo = 'F';
    atleta[14].nascimento.dia = 3;
    atleta[14].nascimento.dia = 6;
    atleta[14].nascimento.dia = 1965;
    
    contador = 15;
    
    printf("\nCadastro(s) finalizado(s)\n\n");
    menu();
}
