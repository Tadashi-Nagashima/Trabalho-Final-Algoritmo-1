/*
Nomes: Luiz Felipe Costa Camargo e Tadashi Bello Nagashima
Turma: EC41A - Algoritmos 1 - C11
Enunciado: Desenvolver um programa em Linguagem C (ANSI C) para gerenciar e analisar dados relacionados ao Circuito Mundial de Corrida de Carrinho de Rolemã Senior. 
O sistema deve organizar e validar informações sobre atletas, treinamento/classificação, competições e resultados finais das provas.
A estrutura de dados será baseada em registros (structs) e vetores/matrizes.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct data{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct atleta{
    char nome[50];
    char pais[35];
    char sexo;
    Data nascimento;
} Atleta;

typedef struct treinamento{
    Atleta atleta;
    int tempo[7];
} Treinamento;

int validar_data(Data nascimento);
int validar_nome(char nome[]);
int validar_pais(char pais[]);

void menu();
void cadastro();
void treinamento();

int contador = 0;
Atleta atleta[100];

int main(){

    menu();
    
    return 0;
}

void menu(){
    int escolha = 0;
    printf("    _________________________________\n");
    printf("    |*******************************|\n");
    printf("    |Sistema Gerenciador de Corridas|\n");
    printf("    |*******************************|\n");
    printf("    |    1. Cadastrar Atleta        |\n");   
    printf("    |    2. Treinamento             |\n");
    printf("    |    3. Corrida                 |\n");
    printf("    |*******************************|\n\n");
    printf("    Escolha dentre as opções: ");
    
    while(1){
        scanf("%d", &escolha);
        getchar();
        
        switch(escolha){
            case 1:
                cadastro();
                break;
            case 2:
                treinamento();
                break;
            case 3:
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
            fgets(atleta[contador].nome, 50, stdin);
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
        }while(validar_data(atleta[contador].nascimento) != 1);
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
    Treinamento treino[50];
    int i = 0;
    int j = 0;
    char escolha;
    
    for(i = 0; i < contador; i++){
        strcpy(treino[i].atleta.nome, atleta[i].nome);
    }
    while(escolha != 'S'){
        for(i = 0; i < contador; i++){
            printf("\nAtleta %d: %s\n", i + 1, treino[i].atleta.nome);
        }
 
        printf("\nConfimar? S/N \n");
        scanf("%c", &escolha);
    }
    printf("\nConfimado\n");
    
    for(i = 0; i < contador; i++){
        printf("\nAtleta %d: %s\n", i + 1, treino[i].atleta.nome);
        for(j = 0; j < 7; j++){
            treino[i].tempo[j] = rand() % 20;
        }
        for(j = 0; j < 7; j++){
            printf("| %ds ", treino[i].tempo[j]);
        }
        printf("|");
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
    return 1;   
}
int validar_pais(char pais[]){
    int i = 0;
    char paises_aceitos[6][35] = {"Brasil", "EUA", "Inglaterra", "Jamaica", "Arabia Saudita", "Estados Unidos"};
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
    
    for(i = 0; i < 6; i++){
        if(strcasecmp(pais, paises_aceitos[i]) == 0){
            if(strcasecmp(pais, "Estados Unidos") == 0){
                strcpy(pais, "EUA"); 
            }
            return 1;
        }
    }
    return 0;
}
