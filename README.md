# Trabalho-Final-Algoritmo-1

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

# Treinamento (struct)

atleta (Atleta)				
tempo (int[7]) 		// Ex: 78 segundos


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
Além de ter todos os dados validados, somente atletas com 45 anos ou mais, completados até 31 de julho de 2024, poderão se inscrever nesta competição. 



(###) (#%) Estruturação geral do programa e função principal.
A função principal deve apresentar um menu que permita acionar todas as funcionalidades implementadas no Sistema Gerenciador de Corridas. 
Na fase de treinamento, cada atleta tem até 7 tentativas para obtenção de tempos. Vale a melhor marca para ele avançar para a próxima fase. Só avançam para a próxima fase os 8 melhores atletas.



Obs: Além da corretude do exercício, também serão avaliados o uso das boas práticas de programação, como:

cabeçalho de identificação dos autores no código.
organização / diagramação do código.
indentação do código.
documentação do código (comentários oportunos, sem excessos).
nomes sugestivos para as variáveis.
uso de estruturas de controle (decisão e repetição) adequadas.
NÃO usar bibliotecas diferentes das que utilizamos em aula (não precisa nada além de stdio.h, string.h, stdlib.h, math.h, limits.h). Não pode usar ponteiros. Para qualquer biblioteca diferente, preciso comunicar e justificar antecipadamente.

Dica 1: Crie funções que preenchem "automaticamente" seus vetores de dados para economizar tempo na digitação a cada execução.
Dica 2: ???.

Plágio é crime! 
Se detectado, acarretará nota 0 (ZERO) para todos os envolvidos. Melhor entregar um código incompleto do que algo plagiado - faça você o seu código.


Obs: 
Trabalho em grupo mas a nota é individual.
Proibido qualquer tipo de gerador automático de código.



Histórico de atualizações
v0.1: 27/08/2024 às 13:50 
