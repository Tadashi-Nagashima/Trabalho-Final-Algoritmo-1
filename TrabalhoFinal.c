/*
Nomes..: Luiz Felipe Costa Camargo (RA 2677865) e Tadashi Bello Nagashima (RA 2677873)
Turma..: EC41A - Algoritmos 1 - C11
Data..: 05/09/2024
Trabalho Final Grupo 9..: Sistema Gerenciador de Corridas.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAXPAISES 6
#define MAXNOME 50
#define MAXTREINO 7
#define MAXMELHORES 8
#define LIMITEATLETAS 100
#define LIMITEAUTOMATICO 100
#define LIMITEAUTOMATICOTXT "100"

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
    char nome[80];
    Data data;
    Competidor corredores[MAXMELHORES];
} Competicao;

int validar_data(Data nascimento);
int validar_datacompeticao(Data competicao);
int validar_nome(char nome[]);
int validar_sexo(char sexo);
int validar_pais(char pais[]);
void formatar_tempo(int tempo);

int menu();
void precadastro();
void menu_competicao(Atleta a1[], int qtd);
void cadastro(Atleta a1[], int qtd);
void menu_pos_competicao();
void menu_analisar_competicao(Competidor compet[], int qtd, Competicao competi);

void iniciar_competicao(Competidor compet[], int qtd, Competicao competi);
void treinamento(Atleta a1[], int qtd, Competicao competi);
void cadastrar_competicao(Atleta a1[], int qtd);
void agrupar_paises(Competicao competicao);
void agrupar_sexo(Competicao competicao, char sexo);
void mostrar_mais_velhos(Atleta a1[]);
void analisar_competicao(Competidor compet[], int qtd, Competicao competi);


void preencher_atletas(Atleta atleta[], int qtd_cadastro); //função temporária

int contador = 0;
int melhores[LIMITEATLETAS];
int melhores_atletas[LIMITEATLETAS];
Atleta atleta[LIMITEATLETAS];
Competidor treino[LIMITEATLETAS];
Competicao competicao;
Competidor competidores[LIMITEATLETAS];
int soma[MAXMELHORES];
int soma_atletas[MAXMELHORES];

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
    printf("    |    2. Cadastrar Competição    |\n"); 
    printf("    |    3. Gerenciar Competição    |\n");
    printf("    |    4. Encerrar programa       |\n");
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
                cadastrar_competicao(atleta, contador);
                break;
            case 3:
                if(strcmp(competicao.nome, "") == 0){
                    printf("    Não existe competição.\n");
                    printf("    Escolha dentre as opções acima: ");
                } else{
                   menu_competicao(atleta, contador);
                   break;
                }
                break;
            case 4:
                printf("\n    Encerrando...\n");
                return 0;
                break;
            default:
                printf("    Opção inválida. Tente novamente.\n");
                printf("    Escolha dentre as opções acima: ");
        }  
    }
}
void menu_competicao(Atleta a1[], int qtd){
    int escolha = 0;
    Competidor competidores[LIMITEATLETAS];
    
    printf("    _________________________________\n");
    printf("    |*******************************|\n");
    printf("    |     Gerenciar Competição      |\n");
    printf("    |*******************************|\n");
    printf("    |    1. Treinamento             |\n");
    printf("    |    2. Iniciar Competição      |\n");
    printf("    |    3. Voltar                  |\n");
    printf("    |*******************************|\n\n");
    printf("    Escolha dentre as opções: ");
    
    while(1){
        scanf("%d", &escolha);
        getchar();
        
        switch(escolha){
            case 1:
                treinamento(atleta, contador, competicao);
                break;
            case 2:
                iniciar_competicao(competidores, contador, competicao);
                break;
            case 3:
                menu(competidores, contador, competicao);
                break;
            default:
                printf("    Opção inválida. Tente novamente.\n");
                printf("    Escolha dentre as opções acima: ");
        }  
    }
}
void menu_pos_competicao(){
    int escolha = 0;
    Competicao competicao;
    
    printf("    _________________________________\n");
    printf("    |*******************************|\n");
    printf("    |     Gerenciar Competição      |\n");
    printf("    |*******************************|\n");
    printf("    |    1. Treinamento             |\n");
    printf("    |    2. Iniciar Competição      |\n");
    printf("    |    3. Analisar Competição     |\n");
    printf("    |    4. Voltar                  |\n");
    printf("    |*******************************|\n\n");
    printf("    Escolha dentre as opções: ");
    
    while(1){
        scanf("%d", &escolha);
        getchar();
        
        switch(escolha){
            case 1:
                treinamento(atleta, contador, competicao);
                break;
            case 2:
                iniciar_competicao(competidores, contador, competicao);
                break;
            case 3:
                menu_analisar_competicao(competidores, contador, competicao);
                break;
            case 4:
                menu();
                break;
            default:
                printf("    Opção inválida. Tente novamente.\n");
                printf("    Escolha dentre as opções acima: ");
        }  
    }
}
void precadastro(){
    int qtd_cadastro = 0;
    char escolha;
    
    if(contador == 100){
        printf("\nNúmero máximo de atletas atingido.\n");
        menu(); 
    }
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
                if(qtd_cadastro > LIMITEAUTOMATICO && contador < LIMITEAUTOMATICO){
                    printf("Apenas " LIMITEAUTOMATICOTXT " atletas serão completados automaticamente\n");
                    preencher_atletas(atleta, LIMITEAUTOMATICO);
                    cadastro(atleta, qtd_cadastro);
                    break;
                } else if (contador < LIMITEAUTOMATICO){
                    preencher_atletas(atleta, contador + qtd_cadastro);
                    break;
                } else if (contador >= LIMITEAUTOMATICO){
                    printf("Apenas " LIMITEAUTOMATICOTXT " atletas serão completados automaticamente\n");
                    cadastro(atleta, contador + qtd_cadastro);
                    break;
                }
            } else {
                cadastro(atleta, contador + qtd_cadastro);;
                break;
            }
        } else {
            printf("Informação inválida. Tente novamente.\n\n");
            break;
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
void treinamento(Atleta a1[], int qtd, Competicao competi){
    int i = 0;
    int j = 0;
    int temp = 0;
    int temp_atleta = 0;
    char escolha = ' ';
    int escolha_atleta = 101;
    int melhores[qtd];
    int melhores_atletas[qtd];
    
    printf("\n      %s\n", competi.nome);
    printf("\n      Data: %d/%d/%d\n\n", competi.data.dia, competi.data.mes, competi.data.ano);
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
                printf("|  ");
                formatar_tempo(treino[i].tempo[j]);
            }
            printf(" | \n\n");
            continue;
        }
        printf("\nAtleta %d: %s\n", i + 1, treino[i].atleta.nome);
        for(j = 0; j < MAXTREINO; j++){
            treino[i].tempo[j] = 10 + rand() % (101 - 10 + 1);
            printf("|");
            formatar_tempo(treino[i].tempo[j]);
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
        printf("%s: ", treino[melhores_atletas[i]].atleta.nome);
        formatar_tempo(melhores[i]);
        printf("\n");
    }
    
    escolha = ' ';
    while(escolha == ' '){
        printf("\nVoltar ao menu? S/N\n");
        getchar();
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
int validar_datacompeticao(Data competicao){
    // variáveis
    int maxdias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // processamento
    if(competicao.mes == 2 && (((competicao.ano % 4 == 0 && competicao.ano % 100 != 0)) || competicao.ano % 400 == 0)){
        maxdias[1] = 29;    // ano bissexto
    }
    if(competicao.ano < 2024){
        return 1;
    }
    if(competicao.mes < 1 || competicao.mes > 12){
        return 0;
    }
    if (competicao.dia < 1 || competicao.dia > maxdias[competicao.mes - 1]){
        return 0;
    }
    if(competicao.ano == 2024){
        if(competicao.mes < 9){
            return 1;
        } else {
            if(competicao.mes > 9){
                return 2;
            }
            if(competicao.mes == 9){
                if(competicao.dia < 4){
                    return 1;
                } else {
                    return 2;
                }
            }
        }
    }
    return 2;   
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
void cadastrar_competicao(Atleta a1[], int qtd){
    int i = 0;
    char escolha;
    
    printf("\n\nCadastrar Competição:\n\n");
    
    printf("Nome da Competição: ");
    fgets(competicao.nome, 80, stdin);
    competicao.nome[strlen(competicao.nome) - 1] = '\0';
    
    while(1){
        printf("\nData da Competição: ");
        scanf("%d/%d/%d", &competicao.data.dia, &competicao.data.mes, &competicao.data.ano);
    
        if(validar_datacompeticao(competicao.data) == 0){
            printf("Data não existente.\n");
        } else if(validar_datacompeticao(competicao.data) == 1){
            printf("Data inválida. Data passada.\n");
        } else {
            break;
        }
    }
    
    printf("\nOs corredores da competição são: \n");
    
    while(1){
       for(i = 0; i < qtd; i++){
            printf("\nAtleta %d: %s", i + 1, a1[i].nome);
        }
        printf("\n\nGostaria de adicionar mais nomes? S/N \n");
        getchar();
        scanf("%c", &escolha);
        if(escolha == 'S'){
            precadastro();
        }
        else{
            break;
        }
    }
    printf("\nConfimado\n");
    
    escolha = ' ';
    while(1){
        printf("\nDeseja iniciar a competição? S/N\n");
        getchar();
        scanf("%c", &escolha);
        if(escolha == 'S'){
            menu_competicao(atleta, contador);
        } else if(escolha == 'N'){
            menu();
        }
    }
}
void iniciar_competicao(Competidor compet[], int qtd, Competicao competi){
    int i = 0;
    int j = 0;
    int temp = 0;
    int temp_atleta = 0;
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
    printf("\n\n");
    
    if(escolha == 'S'){
        printf("Escolha o atleta: ");
        getchar();
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
            printf("\nSoma: ");
            formatar_tempo(soma[i]);
            printf("\n\n");
            soma_atletas[i] = melhores_atletas[i];
            continue;
        }
        printf("\nAtleta %d: %s\n", i + 1, compet[melhores_atletas[i]].atleta.nome);
        for(j = 0; j < 5; j++){
            compet[melhores_atletas[i]].tempo[j] = 10 + rand() % (101 - 10 + 1);
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
        printf("\nSoma: ");
        formatar_tempo(soma[i]);
        printf("\n\n");
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
    printf("        Classificação \n\n");
    printf("            Pódio: \n\n");
    printf("    ========================\n");
    i = 0;
    printf("        *** Ouro ***\n");
    printf("        %3s  \n", compet[soma_atletas[i]].atleta.nome);
    printf("            %3s\n", atleta[soma_atletas[i]].pais);
    printf("        Tempo: ");
    formatar_tempo(soma[i]);
    printf("\n\n");
    i++;
    printf("        *** Prata ***\n");
    printf("        %3s  \n", compet[soma_atletas[i]].atleta.nome);
    printf("            %3s\n", atleta[soma_atletas[i]].pais);
    printf("        Tempo: ");
    formatar_tempo(soma[i]);
    printf("\n\n");
    i++;
    printf("        *** Bronze ***\n");
    printf("        %3s  \n", compet[soma_atletas[i]].atleta.nome);
    printf("            %3s\n", atleta[soma_atletas[i]].pais);
    printf("        Tempo: ");
    formatar_tempo(soma[i]);
    printf("\n\n");
    i++;
    printf("    ========================\n");
    for(i = 3; i < MAXMELHORES; i++){
       printf("     %3s\n", compet[soma_atletas[i]].atleta.nome);
        printf("        %3s\n", atleta[soma_atletas[i]].pais);
        printf("        Tempo: ");
        formatar_tempo(soma[i]);
        printf("\n\n");
    }
    printf("    ========================\n");
    
    escolha = ' ';
    while(escolha != 'S'){
        printf("\nVoltar ao menu? S/N\n");
        getchar();
        scanf("%c", &escolha);
    }
    menu_pos_competicao(compet, qtd, competi);
}
void menu_analisar_competicao(Competidor compet[], int qtd, Competicao competi){
    int escolha = 0;
    char sexo;
    
    printf("    _____________________________________________\n");
    printf("    |*******************************************|\n");
    printf("    |           Análise da Competição           |\n");
    printf("    |*******************************************|\n");
    printf("    |    1. Atletas de Cada País                |\n");   
    printf("    |    2. Atletas por Sexo                    |\n");
    printf("    |    3. Atletas Mais Velhos                 |\n");
    printf("    |    4. Tempo dos Atletas na Competição     |\n");
    printf("    |    5. Voltar                              |\n");
    printf("    |*******************************************|\n\n");
    printf("    Escolha dentre as opções: ");
    
    while(1){
        scanf("%d", &escolha);
        getchar();
        
        switch(escolha){
            case 1:
                agrupar_paises(competicao);
                break;
            case 2:
                do{
                    printf("Digite o sexo: ");
                    scanf("%c", &sexo);
                    getchar(); 
            
                    if(validar_sexo(sexo) == 0){
                        printf("Informação inválida. Tente novamente.\n\n"); 
                    }   
                }while(validar_sexo(sexo) != 1);
            case 3:
                mostrar_mais_velhos(atleta);
                break;
            case 4:
                analisar_competicao(compet, qtd, competi);
                break;
            case 5:
                menu_pos_competicao();
                break;
            default:
                printf("    Opção inválida. Tente novamente.\n");
                printf("    Escolha dentre as opções acima: ");
        }
    }
}
void agrupar_paises(Competicao competicao){
    int i = 0;
    for(i = 0; i < LIMITEATLETAS; i ++){
        competicao.corredores[i].atleta = atleta[i];
    }
    int controlador[5] = { 0, 0, 0, 0, 0};
    printf("\n   Competidores agrupados por países:\n");
    
    for(i = 0; i < LIMITEATLETAS; i ++){
        if(strcasecmp(competicao.corredores[i].atleta.pais, "Arabia Saudita") == 0){
            controlador[0] ++;
            if(controlador[0] == 1){
                printf("   -= Arabia Saudita =-\n");
            }
            printf("   %s\n", competicao.corredores[i].atleta.nome);
        }
    }
    for(i = 0; i < LIMITEATLETAS; i ++){
        if(strcasecmp(competicao.corredores[i].atleta.pais, "Brasil") == 0){
            controlador[1] ++;
            if(controlador[1] == 1){
                printf("\n  -= Brasil =-\n");
            }
            printf("   %s\n", competicao.corredores[i].atleta.nome);
        }
    }
    for(i = 0; i < LIMITEATLETAS; i ++){
        if(strcasecmp(competicao.corredores[i].atleta.pais, "EUA") == 0){
            controlador[2] ++;
            if(controlador[2] == 1){
                printf("\n   -= Estados Unidos =-\n");
            }
            printf("   %s\n", competicao.corredores[i].atleta.nome);
        }
    }
    for(i = 0; i < LIMITEATLETAS; i ++){
        if(strcasecmp(competicao.corredores[i].atleta.pais, "Inglaterra") == 0){
            controlador[3] ++;
            if(controlador[3] == 1){
                printf("\n   -= Inglaterra =-\n");
            }
            printf("   %s\n", competicao.corredores[i].atleta.nome);
        }
    }
    for(i = 0; i < LIMITEATLETAS; i ++){
        if(strcasecmp(competicao.corredores[i].atleta.pais, "Jamaica") == 0){
            controlador[4] ++;
            if(controlador[4] == 1){
                printf("\n   -= Jamaica =-\n");
            }
            printf("   %s\n", competicao.corredores[i].atleta.nome);
        }
    }
    char escolha;
    while(escolha != 'S') {
        printf("\nVoltar ao menu de análise? S/N\n");
        scanf(" %c", &escolha); 
    }
    menu_analisar_competicao(competidores, contador, competicao);
}
void agrupar_sexo(Competicao competicao, char sexo){
    int i = 0;
    
    for(i = 0; i < LIMITEATLETAS; i ++){
        competicao.corredores[i].atleta = atleta[i];
    }

    printf("\n   -= Competidores do sexo %s =-\n", (sexo == 'F') ? "feminino" : "masculino");
    for(i = 0; i < contador; i++) {
        if(competicao.corredores[i].atleta.sexo == sexo) {
            printf("   %s\n", competicao.corredores[i].atleta.nome);
        }
    }

    char escolha = ' '; 
    while(escolha != 'S') {
        printf("\nVoltar ao menu de análise? S/N\n");
        scanf(" %c", &escolha); 
    }
    menu_analisar_competicao(competidores, contador, competicao);
}
void mostrar_mais_velhos(Atleta a1[]){
    Atleta temp;
    int i, j, melhor;
    
    for (i = 0; i < contador - 1; i++) {
        for (j = i + 1; j < contador; j++) {
            if(a1[i].nascimento.ano > a1[j].nascimento.ano){
                temp = a1[i];
                a1[i] = a1[j];
                a1[j] = temp;
            } else {
                if(a1[i].nascimento.ano == a1[j].nascimento.ano){
                    if(a1[i].nascimento.mes > a1[j].nascimento.mes){
                        temp = a1[i];
                        a1[i] = a1[j];
                        a1[j] = temp;
                    } else {
                        if(a1[i].nascimento.mes == a1[j].nascimento.mes){
                            if(a1[i].nascimento.dia > a1[j].nascimento.dia){
                            temp = a1[i];
                            a1[i] = a1[j];
                            a1[j] = temp;
                            }
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < 5; i++) {
        printf("   Atleta %d:\n", i + 1);
        printf("   Nome: %s\n", a1[i].nome);
        printf("   País: %s\n", a1[i].pais);
        printf("   Sexo: %c\n", a1[i].sexo);
        printf("   Data de Nascimento: %02d/%02d/%04d\n", a1[i].nascimento.dia, a1[i].nascimento.mes, a1[i].nascimento.ano);
        printf("   Melhor tempo: ");
        for(j = 0 ; j < MAXTREINO; j ++){
            if(treino[i].tempo[j] > treino[i].tempo[j + 1]){
                treino[i].tempo[melhor] = treino[i].tempo[j];
            }
        }
        formatar_tempo(treino[i].tempo[melhor]);
        printf("\n\n");
    }
    char escolha = 'N'; 
    while(escolha != 'S') {
        printf("\nVoltar ao menu de análise S/N\n");
        scanf(" %c", &escolha); 
    }
    menu_analisar_competicao(competidores, contador, competicao);
}
void analisar_competicao(Competidor compet[], int qtd, Competicao competi){
    int i = 0;
    int j = 0;
    int tam_grafico[LIMITEATLETAS];
    char escolha;
    
    for(i = 0; i < qtd; i++){
        tam_grafico[i] = melhores[i];
    }
    printf("\n\nAnálise dos tempos na Fase de Treinamento\n\n");
    
    for(i = 0; i < MAXMELHORES; i++){
        printf("\n%s\n", treino[melhores_atletas[i]].atleta.nome);
        for(j = 0; j < tam_grafico[i] + 1; j++){
            printf("--");
        }
        printf("\n");
        for(j = 0; j < tam_grafico[i]; j++){
            printf("  ");
        }
        printf("  |");
        formatar_tempo(tam_grafico[i]);
        printf("\n");
        for(j = 0; j < tam_grafico[i] + 1; j++){
            printf("--");
        }
        printf("\n");
    }
    
    printf("\n\nAnálise dos tempos na Fase de Competição\n\n");
    
    for(i = 0; i < qtd; i++){
        tam_grafico[i] = soma[i];
    }
    
    for(i = 0; i < MAXMELHORES; i++){
        printf("\n%s\n", treino[soma_atletas[i]].atleta.nome);
        for(j = 0; j < tam_grafico[i] / 5; j++){
            printf("--");
        }
        printf("\n");
        for(j = 0; j < tam_grafico[i] / 5; j++){
            printf("  ");
        }
        printf("|");
        formatar_tempo(tam_grafico[i]);
        printf("\n");
        for(j = 0; j < tam_grafico[i] / 5; j++){
            printf("--");
        }
        printf("\n");
    }
    
    while(escolha != 'S'){
        printf("\nVoltar ao menu de análise? S/N\n");
        scanf("%c", &escolha);
    }
    menu_analisar_competicao(competidores, contador, competicao);
    
}
void formatar_tempo(int tempo){
    int minuto = 0;
    int segundo = 0;
    
    minuto = tempo / 60;
    segundo = tempo % 60;
    
    printf("%02d:%02d", minuto, segundo);
}
void preencher_atletas(Atleta atleta[], int qtd_cadastro){
    // variaveis
    char auto_nomes[][MAXNOME] = {"Ana dos Santos",  "John New",  "Helena Silveira",  "Esther J. Sechrist",  "Keith V. Prentiss", 
                                    "John S. McKinnon", "Alisha Marsh",  "Callum Hall", "Niamh Archer", "Abdul Baasid al-Sadri",
                                    "Kaatima el-Nasser", "Sharonda Powell", "João Silva", "Usain Bolt", "Haibaa el-Fayad", 
                                    "Antonio Siqueira", "Inês Leite", "Ethridge Stevens", "Abryann Hopkins", "David Orde", 
                                    "Shantaya Martin", "Faaid al-Bashara", "Tahiyya al-Eid", "Antônio Braga", "Daiana Yamada", 
                                    "Kione Ramsey", "Jordina Wilson", "Kordell Tiffin", "Brooke Doesebexonce", "Hazm el-Baccus", 
                                    "Rifqa al-Hamid",  "Saulo Santos", "Elaine Assis", "Ericson Butler", "Quanshay Williamson", 
                                    "Noah Alvarenga", "Shalesia Elough", "Shakeel al-Qasim", "Hawraa al-Zaher", "Joaquim Araújo", 
                                    "Áurea Rezende", "Keenan Beasley", "Torielle Green", "Clement Doesebexonce", "Lashaunta Minot", 
                                    "Jihaad el-Rashed", "Lubaaba el-Sabir", "Antonio Aguiar", "Fernanda Duarte", "Késhaun Mills", 
                                    "Jemisha Harrison", "Jay Tyrell", "Alicia Pierce", "Ghaamid el-Tariq", "Haaniya al-Faraj", "Mateus Espíndola", 
                                    "Edna Henriques", "Maynard Wilson", "Allacia Sanders", "Kimbel Timberlake", "Dominique Pasco", 
                                    "Saood al-Jafari", "Mawzoona el-Wahba", "Cauê Belluci", "Amanda Fontana", "Qasim Rucker", 
                                    "Leisley Griffin", "Talin Chaplain", "Shandee Montgomery", "Taalib al-Yousif", "Haazima al-Salik", 
                                    "Mário Carmo", "Sílvia Alves", "Debony Ford", "Destini Mcdaniel", "Tremaine Stanbury", "Alisha Richie", 
                                    "Abdul Noor al-Nasrallah", "Lateefa el-Khan", "Alceu Dutra", "Mariana Figueiredo", "Jamaad Douglas", 
                                    "Ricca Hines", "Daevin McGhie", "Tandi Rayner", "Humaidaan el-Nasir", "Najaat al-Salim", "Heitor Siqueira", "Marilsa Quintana", 
                                    "Anderius Harrell", "Teagen Washington", "Clement Hayes", 
                                    "Latoya Battersby", "Jameel el-Asad", "Shameema el-Selim", "Algar Charlie", "Editha Elwell", "Earle Beecham", "Bonnie Barrick", 
                                    "Wilfrid Dale", 	"Mercia Brow", "Page Daggett", "Clover Earnest", "Edwyn Dutt", 	"Odelina Hedge", "Wylie Boggess", "Gwen Baggs", 
                                    "Kenway Chesser"};
                                    
    char auto_pais[][35] = {"Brasil","EUA","Brasil","EUA","EUA","EUA","Inglaterra","Inglaterra","Inglaterra",
                            "Arabia Saudita", "Arabia Saudita", "Jamaica", "Brasil", "Jamaica", "Arabia Saudita", "Brasil",  "Brasil", 
                            "EUA", "EUA", "Jamaica",  "Jamaica", "Arabia Saudita", "Arabia Saudita", "Brasil", "Brasil", "EUA", "EUA",  "Jamaica", "Jamaica", "Arabia Saudita", "Arabia Saudita", 
                            "Brasil","Brasil", "EUA", "EUA",  "Jamaica", "Jamaica", "Arabia Saudita", "Arabia Saudita", 
                            "Brasil", "Brasil", "EUA", "EUA", "Jamaica", "Jamaica", "Arabia Saudita", "Arabia Saudita", 
                            "Brasil", "Brasil", "EUA", "EUA",  "Jamaica", "Jamaica", "Arabia Saudita", "Arabia Saudita", 
                            "Brasil", "Brasil", "EUA", "EUA", "Jamaica", "Jamaica", "Arabia Saudita","Arabia Saudita", 
                            "Brasil", "Brasil", "EUA", "EUA",  "Jamaica","Jamaica", "Arabia Saudita", "Arabia Saudita", 
                            "Brasil", "Brasil", "EUA", "EUA",  "Jamaica", "Jamaica", "Arabia Saudita", "Arabia Saudita", 
                            "Brasil", "Brasil", "EUA", "EUA",  "Jamaica", "Jamaica", "Arabia Saudita", "Arabia Saudita", 
                            "Inglaterra", "Inglaterra", "Inglaterra", "Inglaterra", "Inglaterra", "Inglaterra",  "Inglaterra", 
                            "Inglaterra", "Inglaterra", "Inglaterra", "Inglaterra", "Inglaterra"};

    char auto_sexo[] = {'F', 'M', 'F', 'F', 'F', 'M', 'M', 'M', 'F', 'M', 'F', 'F', 'M', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F',  'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M', 'F', 'M'};

    int autonascimento_dia[] = { 21, 15, 10, 2, 21, 16, 21, 8, 1, 17, 25, 8, 2, 1, 3, 14, 17, 28, 26, 24, 26, 17, 13, 10, 2, 3, 8, 21, 20, 24, 17, 1, 7, 23, 17, 12, 9, 28, 10, 3, 21, 3, 14, 8, 26, 30, 13, 13, 19, 30, 28, 14, 17, 2, 23, 10, 4, 22, 30, 15, 8, 9, 15, 6, 1, 24, 17, 2, 21, 27, 4, 3, 21, 17, 2, 16, 16, 15, 28, 27, 6, 17, 10, 14, 18, 25, 16, 13, 16, 15, 28, 15, 15, 4, 21, 8, 19, 7, 9, 9 };
    int autonascimento_mes[] = { 12, 2, 2, 7, 12, 12, 2, 4, 1, 3, 8, 8, 1, 10, 6, 14, 17, 28, 26, 24, 26, 17, 13, 10, 2, 3, 8, 21, 20, 24, 17, 1, 7, 23, 17, 12, 9, 28, 10, 3, 21, 3, 14, 8, 26, 30, 13, 13, 19, 30, 28, 14, 17, 2, 23, 10, 4, 22, 30, 15, 8, 9, 15, 6, 1, 24, 17, 2, 21, 27, 4, 3, 21, 17, 2, 16, 16, 15, 28, 27, 6, 17, 10, 14, 18, 25, 16, 13, 16, 15, 28, 15, 15, 4, 21, 8, 19, 7, 9, 9};
    int autonascimento_ano[] = { 1979, 1959, 1979, 1970, 1974, 1967, 1962, 1957, 1979, 1969, 1970, 1978, 1979, 1963, 1965, 1915, 1924, 1965, 1945, 1955, 1903, 1966, 1944, 1929, 1909, 1904, 1957, 1928, 1945, 1979, 1942, 1950, 1938, 1912, 1978, 1961, 1910, 1905, 1905, 1970, 1946, 1904, 1957, 1951, 1945, 1937, 1914, 1968, 1950, 1907, 1971, 1951, 1972, 1963, 1978, 1929, 1965, 1905, 1955, 1958, 1933, 1946, 1928, 1919, 1956, 1955, 1978, 1915, 1958, 1904, 1905, 1952, 1934, 1960, 1951, 1977, 1917, 1964, 1965, 1916, 1919, 1906, 1965, 1939, 1967, 1914, 1917, 1902, 1917, 1970, 1959, 1976, 1964, 1935, 1916, 1969, 1938, 1914, 1904, 1916};
    
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
