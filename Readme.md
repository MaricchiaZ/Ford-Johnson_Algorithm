# Algoritmo Ford-Johnson

O algoritmo Ford-Johnson é um algoritmo de ordenação que combina a estratégia de inserção binária com a fusão de pares ordenados. Ele foi projetado para ordenar eficientemente uma sequência de elementos usando a inserção binária para manter a ordenação parcial e, em seguida, mesclando os pares ordenados para obter o resultado final.

## Como Funciona

O algoritmo Ford-Johnson segue estes passos:

1. Divisão em Pares: A sequência de elementos é dividida em pares consecutivos, e os elementos de cada par são comparados usando uma função de comparação personalizada.

2. Ordenação dos Pares: Os pares são ordenados de acordo com a primeira componente do par, mantendo a ordenação parcial.

3. Fusão de Pares Ordenados: Os pares ordenados são fundidos para formar uma "cadeia principal" de elementos.

4. Inserção Binária: Elementos pendentes são inseridos na cadeia principal usando a estratégia de inserção binária, que mantém a ordenação da cadeia.

## Exemplos

Vamos considerar a seguinte sequência de elementos a serem ordenados: `[9, 2, 5, 7, 3, 1, 8, 4, 6, 0]`. Usando o algoritmo Ford-Johnson com a função de comparação padrão (`std::less`), o processo seria o seguinte:

1. Divisão em Pares: Os pares seriam: `(9, 2), (5, 7), (3, 1), (8, 4), (6, 0)`.

2. Ordenação dos Pares: Os pares ordenados seriam: `(2, 9), (5, 7), (1, 3), (4, 8), (0, 6)`.

3. Fusão de Pares Ordenados: A cadeia principal resultante seria: `[2, 5, 1, 4, 0]`.

4. Inserção Binária: Os elementos pendentes seriam inseridos na cadeia principal usando a estratégia de inserção binária, resultando em: `[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]`.

## Inclusão da Sequência de Jacobsthal

O algoritmo utiliza a sequência de Jacobsthal para determinar os pontos de inserção. A sequência de Jacobsthal é uma sequência de inteiros em que cada elemento é a soma do dobro do elemento anterior e do elemento antes desse.

## Uso

O algoritmo Ford-Johnson é útil quando você deseja ordenar eficientemente uma sequência de elementos usando uma combinação de inserção binária e fusão. Ele pode ser particularmente eficaz quando a sequência está parcialmente ordenada, já que a estratégia de inserção binária mantém a ordenação parcial durante todo o processo.

## Conclusão

O algoritmo Ford-Johnson oferece uma abordagem interessante para ordenar eficientemente elementos, aproveitando tanto a inserção binária quanto a fusão de pares ordenados. Sua estratégia de divisão, ordenação e fusão leva a uma solução eficaz para problemas de ordenação em várias situações.

## Referências

Ford, Lester R. e Selmer M. Johnson. “Um problema de torneio.” The American Mathematical Monthly, vol. 66, nº. 5, 1959, pp. 387–389. JSTOR, www.jstor.org/stable/2308750 

Knuth, Donald E. A arte da programação de computadores: Volume 3: Classificando e pesquisando. Profissional Addison-Wesley; 2 edição (4 de maio de 1998). (pág 184)
