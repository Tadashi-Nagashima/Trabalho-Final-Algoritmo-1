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

int contador = 0;

int main(){
    Atleta atleta[20];
    Data nascimento;
    
    for(contador = 0; contador < 20; contador++){
        // leitor de nomes
        do{
            printf("Digite seu nome: ");
            fgets(atleta[contador].nome, 50, stdin);
            atleta[contador].nome[strlen(atleta[contador].nome) - 1] = '\0';
            
            if(validar_nome(atleta[contador].nome) == 0){
               printf("Informação inválida. Tente novamente.\n"); 
            }
        }while(validar_nome(atleta[contador].nome) != 1);
        
        // leitor de datas
        
        do{
            printf("Digite sua data de nascimento (dd/mm/yyyy): ");
            scanf("%d/%d/%d", &atleta[contador].nascimento.dia, &atleta[contador].nascimento.mes, &atleta[contador].nascimento.ano);
            getchar(); // tira o \n do scanf
            
            if(validar_data(atleta[contador].nascimento) == 0){
               printf("Informação inválida. Tente novamente.\n\n"); 
            }
        }while(validar_data(atleta[contador].nascimento) != 1);
    }
    
}

int validar_data(Data nascimento){
    // variáveis
    int maxdias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // processamento
    if(nascimento.mes == 2 && (((nascimento.ano % 4 == 0 && nascimento.ano % 100 != 0)) || nascimento.ano % 400 == 0)){
        maxdias[1] = 29;    // ano bissexto
    }
    if(nascimento.ano < 1900 || nascimento.ano > 2024){
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

int validar_nome(char nome[]){
    int i = 0;
    
    if(nome[0] == ' '){
        return 0;
    } else if(strlen(nome) <= 3){
        return 0;
    }
    for(i = 0; i < strlen(nome); i++){
        if(nome[i] >= '0' && nome[i] <= '9'){
            return 0;
        }
    }
    return 1;
}
