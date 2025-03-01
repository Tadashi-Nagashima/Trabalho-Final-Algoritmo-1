## Trabalho-Final-Algoritmo-1

https://docs.google.com/document/d/1MGOmBgcquh6Ak_5VRYc2E7SOOky6H2iv/edit

PROJETO FINAL (Gerenciador de Corridas)

Projeto: Desenvolver um programa em Linguagem C (ANSI C) para gerenciar e analisar dados relacionados ao Circuito Mundial de Corrida de Carrinho de Rolemã Senior. O sistema deve organizar e validar informações sobre atletas, treinamento/classificação, competições e resultados finais das provas. A estrutura de dados será baseada em registros (structs) e vetores/matrizes.

# Data (struct)
dia (int) 	// Ex: 10
mes (int)	// Ex: 08
ano (int)	// Ex: 2000
     
# Atleta (struct)
nome (string[50])    	// Ex: Usain Bolt
pais (string[35])		// Ex: Jamaica
sexo (char);		// Ex: 'M' para masculino ou 'F' para feminino
nascimento (Data)

# Competidor (struct)
atleta (Atleta)
tempo (int[7]) 

# Competicao (struct)
nome (string[50])    		// Ex: Circuito Mundial de Corrida de Carrinho de Rolemã Senior.
data (Data)
corredores (Competidor[8])


Funcionalidades a serem implementadas:

(a) (5%) Definir/criar as estruturas acima.

(b) (5%) Criar uma função de validação para nomes.
A função deve receber o nome (string) como parâmetro e retornar um inteiro que indica se o nome está correto ou não. As regras de validação para o nome são:
ter mais que 2 caracteres; não conter números arábicos; não deve começar com espaços em branco.

(c) (5%) Criar uma função de validação para países.
A função deve receber o país (string) como parâmetro e retornar um inteiro que indica se o nome está correto ou não. As regras de validação para o país são seguem as mesmas do nome além de:
só pode aceitar os seguintes países: Brasil / EUA / Inglaterra / Jamaica / Arabia Saudita.

(d) (5%) Criar uma função de validação para data.
A função deve receber uma data (struct) como parâmetro e retornar um inteiro representando se a data está correta ou não. As regras de validação de data são: 
usar regras do calendário gregoriano. 

(e) (5%) Criar uma função para cadastrar atletas. 
além de ter todos os dados validados, somente atletas com 45 anos ou mais, completados até 31 de julho de 2024, poderão se inscrever nesta competição. 

(f) (5%) Criar uma função que receba um Competidor (struct) e retorne o melhor tempo, seguindo a regra de treinamento (indicada em R1).

(g) (5%) Criar uma função que receba um Competidor (struct) e retorne a somatória dos seus tempos, seguindo a regra da competição (indicada em R2).

(h) (10%) Criar uma função que analise uma competição (recebida por parâmetro) e apresente a lista completa de classificação (do melhor ao pior).
apresentar os dados de uma forma tabular com: Nome do atleta; pais; tempo obtido. 
destacar o Top 3.

(i) (10%) Criar uma função que, com base em uma competição, apresente os seus competidores agrupados por países.

(j) (5%) Criar uma função que liste apenas os competidores de um sexo específico. O sexo escolhido e a competição são passados como parâmetros para a função.

(k) (10%) Criar uma função que exiba os 5 competidores mais velhos da etapa de treinamento. Para cada um deles, apresente todos os dados de cadastro e o melhor tempo registrado.

(l) (10%) Criar uma função que apresente um dado interessante sobre uma competição específica. Utilize sua criatividade para oferecer uma nova perspectiva, evitando repetir análises anteriores. Considere apresentar uma estatística; criar um "pseudo-gráfico" (em texto mesmo) para revelar informações de uma maneira original; etc.

(###) (20%) Estruturação geral do programa e função principal.
A função principal deve apresentar um menu que permita acionar todas as funcionalidades implementadas no Sistema Gerenciador de Corridas. 

Regras:
R1: na fase de treinamento, cada atleta tem até 7 tentativas para obtenção de tempos. Vale a melhor marca para ele avançar para a próxima fase. Só avançam para a próxima fase os 8 melhores atletas.
R2: na fase de competição, cada atleta tem 5 tentativas para obtenção de tempos. A pontuação final é a somatória dos 3 tempos intermediários, descartando o menor e o maior tempo.
R3: todos os tempos apresentados em tela precisam estar no seguinte formato: MM:SS.
R4: na fase de treinamento pode ter até 100 competidores.
R5: haverá apenas uma competição, que incluirá os 8 melhores corredores selecionados durante a fase de treinamento.


Obs: Além da corretude do exercício, também serão avaliados o uso das boas práticas de programação, como:

cabeçalho de identificação dos autores no código.
organização / diagramação do código.
indentação do código.
documentação do código (comentários oportunos, sem excessos).
nomes sugestivos para as variáveis.
uso de estruturas de controle (decisão e repetição) adequadas.
NÃO usar bibliotecas diferentes das que utilizamos em aula (não precisa nada além de stdio.h, string.h, stdlib.h, math.h, limits.h, time.h). Não pode usar ponteiros. Para qualquer biblioteca diferente, preciso comunicar e justificar antecipadamente.

Dica 1: crie funções que preenchem "automaticamente" seus vetores de dados para economizar tempo na digitação a cada execução.
Dica 2: crie funções auxiliares para simplificar atividades que precisam ser realizadas repetidamente.
Dica 3: como podemos ter até 100 competidores na fase de treinamento, sugiro para isto utilizar um vetor de competidores declarado na main() ou até mesmo global.
Dica 4: ###



Plágio é crime! 
Se detectado, acarretará nota 0 (ZERO) para todos os envolvidos. Melhor entregar um código incompleto do que algo plagiado - faça você o seu código.


Obs: 
Trabalho em grupo mas a nota é individual.
Proibido qualquer tipo de gerador automático de código.



Histórico de atualizações
v0.1: 27/08/2024 às 13:50
v0.2: 29/08/2024 às 09:00 
v0.3: 30/08/2024 às 11:00
v0.4: 02/09/2024 às 10:00

