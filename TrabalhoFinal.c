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
void formatar_tempo(int tempo);

int menu();
void precadastro();
void menu_competicao(Atleta a1[], int qtd);
void cadastro(Atleta a1[], int qtd);
void iniciar_competicao(Competidor compet[], int qtd);

void treinamento(Atleta a1[], int qtd);
Competicao cadastrar_competicao(Atleta a1[], int qtd);

void preencher_atletas(Atleta atleta[], int qtd_cadastro); //função temporária

int contador = 0;
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
                precadastro();
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
void precadastro(){
    int qtd_cadastro = 0;
    char escolha;

    printf("\nDigite quantos cadastros gostaria de fazer: ");
    scanf("%d", &qtd_cadastro);
    getchar();
    printf("\nVocê deseja fazer os cadastros automaticamente?\n");
    printf("Digite 'S' para sim ou 'N' para não\n");
    scanf("%c", &escolha);
    getchar();
    while(1){
        if(escolha == 's'||escolha == 'S'|| escolha == 'n'||escolha == 'N'){
            if(escolha == 's'||escolha == 'S'){
                if(qtd_cadastro > 15 && contador < 15){
                    printf("Apenas os ultimos 15 atletas serão completados automaticamente\n");
                    preencher_atletas(atleta, 15);
                    cadastro(atleta, qtd_cadastro);
                    break;
                } else if (contador < 15){
                    preencher_atletas(atleta, contador + qtd_cadastro);
                    break;
                }
            } else {
                cadastro(atleta, contador + qtd_cadastro);
                menu();
                break;
            }
        } else {
            printf("Informação inválida. Tente novamente.");
        }
    }
    menu();
}
void cadastro(Atleta a1[], int qtd){
    int qtd_cadastro = 0;
    
    for(qtd_cadastro = contador; qtd_cadastro < qtd; qtd_cadastro++){
        printf("\nCadastro do atleta número %d: ", (qtd_cadastro + 1));
        // leitor de nomes
        do{
            printf("\nDigite o nome: ");
            fgets(a1[qtd_cadastro].nome, MAXNOME, stdin);
            a1[qtd_cadastro].nome[strlen(a1[qtd_cadastro].nome) - 1] = '\0';
            
            if(validar_nome(a1[qtd_cadastro].nome) == 0){
               printf("Informação inválida. Tente novamente."); 
            }
        }while(validar_nome(a1[qtd_cadastro].nome) != 1);
        // leitor de datas
        do{
            printf("Digite a data de nascimento (dd/mm/yyyy): ");
            scanf("%d/%d/%d", &a1[qtd_cadastro].nascimento.dia, &a1[qtd_cadastro].nascimento.mes, &a1[qtd_cadastro].nascimento.ano);
            getchar(); // tira o \n do scanf
            
            if(validar_data(a1[qtd_cadastro].nascimento) == 0){
               printf("Informação inválida. Tente novamente.\n\n"); 
            }
            if(validar_data(a1[qtd_cadastro].nascimento) == 2){
                printf("O atleta possuí menos de 45 anos\n");
                printf("Informação inválida. Tente novamente.\n\n");
            }
        }while(validar_data(a1[qtd_cadastro].nascimento) != 1);
        // leitor de sexo
        do{
            printf("Digite o sexo: ");
            scanf("%c", &a1[qtd_cadastro].sexo);
            getchar(); // tira o \n do scanf
            
            if(validar_sexo(a1[qtd_cadastro].sexo) == 0){
               printf("Informação inválida. Tente novamente.\n\n"); 
            }
        }while(validar_sexo(a1[qtd_cadastro].sexo) != 1);
        // leitor de países
        do{
            printf("Digite o país: ");
            fgets(a1[qtd_cadastro].pais, 35, stdin);
            a1[qtd_cadastro].pais[strlen(a1[qtd_cadastro].pais) - 1] = '\0';
            
            if(validar_pais(a1[qtd_cadastro].pais) == 0){
               printf("Informação inválida. Tente novamente.\n"); 
            }
        }while(validar_pais(a1[qtd_cadastro].pais) != 1);
    }
    contador++;
    printf("\nCadastro(s) finalizado(s)\n\n");
    
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
    char escolha = ' ';
    int escolha_atleta = 101;
    int melhores[qtd];
    int melhores_atletas[qtd];
    
    printf("\nFase de Treinamento:\n\n");
    for(i = 0; i < qtd; i++){
        strcpy(treino[i].atleta.nome, a1[i].nome);
    }
    while(escolha == ' '){
        for(i = 0; i < qtd; i++){
            printf("\nAtleta %d: %s\n", i + 1, treino[i].atleta.nome);
        }
        
        printf("\nGostaria de digitar o tempo de algum atleta? S/N \n");
        scanf("%c", &escolha);
        getchar();
    }
    if(escolha == 'S'){
        printf("\nEscolha o atleta: ");
        scanf("%d", &escolha_atleta);
        escolha_atleta--;
        printf("%s", treino[escolha_atleta].atleta.nome);
        printf("\nDigite os tempos: \n");
        for(i = 0; i < MAXTREINO; i++){
            printf("\nTempo %d: ", i + 1);
            scanf("%d", &treino[escolha_atleta].tempo[i]);
        }
    }
    
    for(i = 0; i < qtd; i++){
        if(i == escolha_atleta){
            printf("\nAtleta %d: %s\n", i + 1, treino[i].atleta.nome);
            for(j = 0; j < MAXTREINO; j++){
                printf("| %ds ", treino[i].tempo[j]);
            }
            printf("|\n\n");
            continue;
        }
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
    char escolha;
    int escolha_atleta = 101;
    for(i = 0; i < qtd; i++){
        strcpy(compet[i].atleta.nome, treino[i].atleta.nome);
    }
    
    ordenar_treino(treino, qtd);

    printf("\nAtletas Classificados:\n");
    
    for(i = 0; i < MAXMELHORES; i++){
        printf("\nAtleta %d: %s\n", i + 1, compet[melhores_atletas[i]].atleta.nome);
    }
        printf("\nGostaria de digitar o tempo de algum atleta? S/N \n");
        scanf("%c", &escolha);
        getchar();
    printf("\n\n");
    
    if(escolha == 'S'){
        printf("Escolha o atleta: ");
        scanf("%d", &escolha_atleta);
        escolha_atleta--;
        printf("%s\n", compet[melhores_atletas[escolha_atleta]].atleta.nome);
        for(i = 0; i < 5; i++){
            printf("\nTempo %d: ", i + 1);
            scanf("%d", &compet[melhores_atletas[escolha_atleta]].tempo[i]);
        }
    }
    for(i = 0; i < MAXMELHORES; i++){
        int maior = INT_MIN;
        int menor = INT_MAX;
        soma[i] = 0;
        if(i == escolha_atleta){
            printf("\nAtleta %d: %s\n", i + 1, compet[melhores_atletas[i]].atleta.nome);
            for(j = 0; j < 5; j++){
            
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
            continue;
        }
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
    printf("    Classificação \n\n");
    printf("        Pódio: \n\n");
    printf("========================\n");
    i = 0;
    printf("    *** Ouro ***\n");
    printf("    %3s  \n", compet[soma_atletas[i]].atleta.nome);
    printf("        %3s\n", atleta[soma_atletas[i]].pais);
    printf("    Tempo: %d\n\n", soma[i]);
    i++;
    printf("    *** Prata ***\n");
    printf("    %3s  \n", compet[soma_atletas[i]].atleta.nome);
    printf("        %3s\n", atleta[soma_atletas[i]].pais);
    printf("    Tempo: %d\n\n", soma[i]);
    i++;
    printf("    *** Bronze ***\n");
    printf("    %3s  \n", compet[soma_atletas[i]].atleta.nome);
    printf("        %3s\n", atleta[soma_atletas[i]].pais);
    printf("    Tempo: %d\n\n", soma[i]);
    i++;
    printf("========================\n");
    for(i = 3; i < MAXMELHORES; i++){
       printf(" %3s\n", compet[soma_atletas[i]].atleta.nome);
        printf("    %3s\n", atleta[soma_atletas[i]].pais);
        printf("    Tempo: %d\n\n", soma[i]);
    }
    
}
void preencher_atletas(Atleta atleta[], int qtd_cadastro){
    // variaveis
    char auto_nomes[15][MAXNOME] = {"Ana dos Santos", "John New", "Helena Silveira", "Esther J. Sechrist", "Keith V. Prentiss", 
                                    "John S. McKinnon","Alisha Marsh", "Callum Hall", "Niamh Archer", "Abdul Baasid al-Sadri",
                                    "Kaatima el-Nasser","Sharonda Powell", "João Silva", "Usain Bolt", "Haibaa el-Fayad"};
                                    
    char auto_pais[15][20] = {"Brasil","EUA","Brasil","EUA","EUA","EUA","Inglaterra","Inglaterra","Inglaterra",
                              "Arabia Saudita","Arabia Saudita","Jamaica","Brasil","Jamaica","Arabia Sauditat"};
                                     
    char auto_sexo[15] = { 'F', 'M', 'F', 'F', 'F', 'M', 'M', 'M', 'F', 'M', 'F', 'F', 'M', 'M', 'F'};
    int autonascimento_dia[15] = { 21, 15, 10, 2, 21, 16, 21, 8, 1, 17, 25, 8, 2, 1, 3 };
    int autonascimento_mes[15] = { 12, 2, 2, 7, 12, 12, 2, 4, 1, 3, 8, 8, 1, 10, 6 };
    int autonascimento_ano[15] = { 1979, 1959, 1979, 1970, 1974, 1967, 1962, 1957, 1979, 1969, 1970, 1978, 1979, 1963, 1965 };
    
    // processamento
    for(int i = contador; i < qtd_cadastro; i++){
        strcpy(atleta[contador].nome, auto_nomes[i]);
        strcpy(atleta[contador].pais, auto_pais[i]);
        atleta[contador].sexo = auto_sexo[i];
        atleta[contador].nascimento.dia = autonascimento_dia[i];
        atleta[contador].nascimento.mes = autonascimento_mes[i];
        atleta[contador].nascimento.ano = autonascimento_ano[i];
        contador++;
    }
	// saída
	printf("\nCadastro(s) finalizado(s)\n\n");
}
