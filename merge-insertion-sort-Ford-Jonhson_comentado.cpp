#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>

// função que compara dois números inteiros e retorna -1 se x for menor que y, 1 se x for maior 
//que y e 0 se x for igual a y
int compare(int x, int y) {
    if (x < y) return -1; // Se x for menor que y, a função retorna -1, indicando que x é menor que y
    if (x > y) return 1; // Se x for maior que y, a função retorna 1, indicando que x é maior que y.
    return 0; // Se os dois números forem iguais, a função retorna 0, indicando que x é igual a y.
}

typedef std::function<int(int, int)> Comparator; // qui, um alias chamado Comparator é definido para a 
// assinatura de uma função que recebe dois argumentos inteiros e retorna um inteiro. Isso permite que 
// você crie objetos do tipo Comparator que podem armazenar funções de comparação.

// Esta função fnToComparator recebe um objeto do tipo Comparator (que é uma função de comparação) 
// como argumento e retorna outro objeto Comparator. Essencialmente, ela converte uma função de comparação
//  em um formato ligeiramente diferente.
Comparator fnToComparator(Comparator f) {
    return [f](int x, int y) { // O retorno da função é uma função anônima (lambda) que também é um objeto do tipo Comparator.
        // ssa função anônima recebe dois inteiros x e y como argumentos e realiza o seguinte:
        int r = f(x, y); // Chama a função original f(x, y) e armazena o resultado em r
        if (std::is_arithmetic<decltype(r)>::value) { // Verifica se r é um valor aritmético
        //  usando std::is_arithmetic<decltype(r)>::value.
            return r; // Se for, retorna r
        } 
        else { //Se r não for um valor aritmético, ela verifica se r é diferente de zero. 
            if (r) return -1;
            if (f(y, x)) return 1; // Caso contrário, verifica se f(y, x) é verdadeiro (ou seja, se y é maior que x).
            return 0; // Caso contrário, retorna 0.
        }
    };
}

// Essa função em questão implementa a fórmula acima para calcular o n-ésimo número de Jacobsthal.
int jacobsthal(int n) { //  Acalcula número de Jacobsthal até a posição n
    return std::round((std::pow(2, n) + std::pow(-1, n - 1)) / 3);
    // std::pow(2, n) calcula 2 elevado à potência de n.
    // std::pow(-1, n - 1) calcula (-1) elevado à potência de n - 1, alternando entre -1 e 1 conforme n aumenta.
    // A soma dos dois termos acima é dividida por 3 para obter o resultado final.
    // std::round arredonda o resultado para o número inteiro mais próximo.
}


// Essa função gera uma sequência de índices que indicam onde inserir um elemento em uma coleção,
// de acordo com a ordem determinada pelo cálculo dos números de Jacobsthal
std::vector<int> pendingElementOrder(int n) { // A função recebe um inteiro n como argumento e retorna um vetor de inteiros, 
// representando a sequência de índices.
    std::vector<int> result; //  Cria um vetor chamado result para armazenar temporariamente os números de Jacobsthal.
    for (int i = 0; jacobsthal(i) > n; ++i) { // : Este loop percorre os números de Jacobsthal enquanto eles 
    // forem maiores que n. Isso garante que apenas os índices relevantes sejam usados.
    // jacobsthal(i) calcula o i-ésimo número de Jacobsthal.
    // Se jacobsthal(i) for maior que n, o índice i é adicionado ao vetor result.
        result.push_back(jacobsthal(i));
    }
    result.push_back(n); // Adicionamos o próprio n ao final do vetor result.


    std::vector<int> order; // Cria um novo vetor chamado order para armazenar a sequência final de índices.
    for (size_t i = 1; i < result.size(); ++i) { //: Este loop percorre os elementos do vetor result, 
    // começando do segundo elemento (índice 1).
        int a = result[i - 1]; // armazenamos os valores consecutivos de result em a e b.
        int b = result[i];
        for (int j = b - 1; j >= a; --j) { //  insere os índices no vetor order em ordem decrescente, de b - 1 até a,
        // indicando onde os elementos devem ser inseridos para manter a sequência ordenada.
            order.push_back(j);
        }
    }
    return order; // A função retorna o vetor order, que contém os índices na ordem em que os elementos devem ser inseridos
    //  para atender às regras determinadas pelo cálculo dos números de Jacobsthal.
}


// Essa função implementa uma busca binária modificada para encontrar o ponto de inserção de um elemento em uma 
// coleção ordenada, de acordo com uma função de comparação personalizada. 
// A função recebe os seguintes argumentos:
// comp: A função de comparação.
// n: O elemento a ser inserido.
// coll: O vetor ordenado no qual o elemento será inserido.
// lowerBound e upperBound: Os índices delimitando a faixa de pesquisa.
int binarySearchInsertionPoint(Comparator comp, int n, const std::vector<int>& coll, int lowerBound, int upperBound) {
    if (lowerBound > upperBound) { //  verificamos se a faixa de pesquisa é válida (ou seja, lowerBound não excede upperBound).
        return lowerBound;
    } 
    else {
        int midIndex = (lowerBound + upperBound) / 2; // Calcula o índice do meio da faixa de pesquisa.
        int compResult = comp(n, coll[midIndex]);  // Usa a função de comparação comp para comparar o elemento n com o 
        // elemento na posição midIndex do vetor coll. O resultado compResult é -1, 0 ou 1
        if (compResult == 1) { // isso significa que o elemento n é maior que o elemento em midIndex
            return binarySearchInsertionPoint(comp, n, coll, midIndex + 1, upperBound); // portanto a busca continua na
            //  metade direita da faixa, chamando recursivamente binarySearchInsertionPoint com um novo
            //  lowerBound igual a midIndex + 1 e mantendo o mesmo upperBound.
        } else if (compResult == 0) { //  isso indica que o elemento n é igual ao elemento em midIndex, então midIndex
        //  é retornado como o ponto de inserção.
            return midIndex;
        } else { // o elemento n é menor que o elemento em midIndex
            return binarySearchInsertionPoint(comp, n, coll, lowerBound, midIndex - 1); // a busca continua na metade
            //  esquerda da faixa, chamando recursivamente binarySearchInsertionPoint com um novo upperBound igual a 
            // midIndex - 1 e mantendo o mesmo lowerBound.
        }
    }
    // A função continua a recursão até que a faixa de pesquisa seja reduzida a um único elemento (caso base) ou 
    // até que o ponto de inserção seja encontrado.

    // O ponto de inserção é retornado como o índice onde o elemento n deve ser inserido para manter a ordenação da coleção.
}


// Aqui inserimos um elemento em uma coleção ordenada usando o método de inserção binária, considerando uma função de
// comparação personalizada.
// A função recebe os seguintes argumentos:
// comp: A função de comparação.
// n: O elemento a ser inserido.
// coll: O vetor ordenado no qual o elemento será inserido.
std::vector<int> binaryInsert(Comparator comp, int n, const std::vector<int>& coll) {
    std::vector<int> newColl = coll; // Cria uma cópia do vetor coll chamada newColl. Isso evita modificar diretamente o vetor original.
    int insertIndex = binarySearchInsertionPoint(comp, n, coll, 0, coll.size() - 1); // Calcula o índice onde o elemento n deve ser inserido 
    // na coleção ordenada usando a função binarySearchInsertionPoint.
    newColl.insert(newColl.begin() + insertIndex, n); //  Insere o elemento n na posição determinada pelo insertIndex calculado 
    // anteriormente usando std::vector::insert.
    return newColl; //  Retorna o novo vetor newColl, que é uma cópia do vetor original com o elemento n inserido na
    //  posição correta para manter a ordenação.
}

// Essa função é a nossa FUNçÃO MAIS IMPORTANTE, implementa o algoritmo de ordenação "Merge-Insertion Sort", que mescla
// a estratégia de ordenação por inserção com a mesclagem de pares ordenados. 
//  A função recebe uma função de comparação comp e um vetor coll a ser ordenado.
std::vector<int> mergeInsertionSort(Comparator comp, const std::vector<int>& coll) {
    if (coll.size() < 2) { // Verifica se o vetor coll contém 1 ou menos elementos. .
        return coll; // e sim, ele já está ordenado, e o vetor é retornado imediatamente
    } else {
        std::vector<std::pair<int, int>> sortedPairs; //  Cria um vetor para armazenar pares de elementos ordenados.
        for (size_t i = 0; i < coll.size(); i += 2) {  // itera através do vetor coll em passos de 2. Para cada par 
        // de elementos adjacentes (ou o último elemento se houver um número ímpar de elementos), 
        // um par ordenado é criado e adicionado a sortedPairs.
            int first = coll[i]; // Obtém o primeiro elemento do par, que é o elemento atual na posição i do vetor coll.
            int second = i + 1 < coll.size() ? coll[i + 1] : coll.back(); // Obtém o segundo elemento do par. Se ainda 
            // houver pelo menos um elemento na posição i + 1, ele pega esse elemento. Caso contrário, pega o último 
            // elemento do vetor coll.
            if (comp(first, second) < 0) { // Compara os dois elementos do par usando a função de comparação comp.
            // Se o resultado da comparação for menor que 0 (ou seja, first é considerado menor que second), 
                sortedPairs.push_back(std::make_pair(first, second)); // então o par (first, second) é adicionado ao vetor sortedPairs.
            } else { // Caso contrário, o par (second, first) é adicionado, garantindo que os elementos no par estejam ordenados.
                sortedPairs.push_back(std::make_pair(second, first));
            }
        }
        std::sort(sortedPairs.begin(), sortedPairs.end(), [comp](const std::pair<int, int>& x, const std::pair<int, int>& y) { // 
        //  Ordena os pares no vetor sortedPairs com base na primeira componente do par, usando a função de comparação comp.
            return comp(x.first, y.first) < 0;
        });

        // Vetores para armazenar a cadeia principal e os elementos pendentes.
        std::vector<int> mainChain;
        std::vector<int> pendingElements;


        for (const auto& pair : sortedPairs) {
            mainChain.push_back(pair.first); // preenche mainChain com os primeiros componentes dos pares
            pendingElements.push_back(pair.second); // //  preenche pendingElements com os segundos componentes.
        }

        if (coll.size() % 2 != 0) { // Se o tamanho de coll for ímpar
            pendingElements.push_back(coll.back()); // o último elemento é adicionado a pendingElements.
        }

        std::vector<int> aPositions(mainChain.size()); // Cria um vetor de posições para rastrear a 
        //posição de cada elemento em mainChain.

        for (size_t i = 0; i < mainChain.size(); ++i) { // Inicializa a posição de cada elemento em mainChain.
            aPositions[i] = i;
        }

        auto mainChainUntil = [&](int aIndex) -> std::vector<int> { // O lambda mainChainUntil retorna uma 
        // subparte de mainChain até o índice aIndex.
            int end = aPositions[aIndex];
            return std::vector<int>(mainChain.begin(), mainChain.begin() + end);
        };

        // O lambda binaryInsertLambda insere um elemento em mainChain seguindo a estratégia de inserção binária.
        //  Define uma função lambda chamada binaryInsertLambda que recebe um índice bIndex como argumento.
        //  A captura & inclui as variáveis externas por referência para que possam ser acessadas e modificadas dentro da função lambda.
        auto binaryInsertLambda = [&](int bIndex) {
            int n = pendingElements[bIndex]; // Obtém o valor do elemento pendente que será inserido. 
            // O índice bIndex é usado para obter o elemento correspondente no vetor pendingElements.
            int insertIndex = binarySearchInsertionPoint(comp, n, mainChain, 0, mainChainUntil(bIndex).size() - 1); // Calcula o 
            // índice onde o elemento n deve ser inserido na cadeia principal (mainChain) usando a função binarySearchInsertionPoint.
            for (size_t i = 0; i < aPositions.size(); ++i) { // Este loop itera através do vetor de posições aPositions.
                if (aPositions[i] >= insertIndex) { // Se a posição de um elemento (aPositions[i]) for maior ou igual ao insertIndex, 
                // significa que após a inserção do elemento n, a posição desse elemento na cadeia principal mudará. 
                //  Portanto, incrementamos a posição aPositions[i] para acomodar essa mudança.
                    ++aPositions[i];
                }
            }
            mainChain.insert(mainChain.begin() + insertIndex, n); // Insere o elemento n na posição determinada pelo insertIndex
            //  calculado anteriormente usando a função std::vector::insert. Isso modifica a cadeia principal mainChain de 
            // acordo com a estratégia de inserção binária.
        };

        // é criado usando a função pendingElementOrder
        std::vector<int> order = pendingElementOrder(pendingElements.size());
        for (int i : order) { // inserimos os elementos pendentes em mainChain seguindo a estratégia de inserção binária.
            binaryInsertLambda(i);
        }

        return mainChain; // A função retorna o vetor mainChain ordenado.
    }
}

int main() {
    std::vector<int> unsorted = {3279, 3064, 3679, 3150, 2406, 3050, 2608, 2332, 48, 4901, 245, 3891, 2523, 2250, 573, 2884, 4465, 2117, 267, 3497, 633, 2816, 4568, 4770, 1056, 3581, 2727, 4707, 205, 4898, 4824, 3484, 2961, 3502, 2397, 1129, 2314, 767, 4225, 3126, 1431, 232, 2016, 3954, 2482, 3352, 1837, 1946, 1231, 2867, 1205, 1865, 1445, 773, 1634, 2502, 116, 124, 2971, 1084, 21, 2794, 4569, 3745, 2058, 2728, 636, 4372, 4258, 4861, 2497, 688, 92, 275, 4642, 3337, 4390, 2241, 1046, 621, 870, 2251, 2486, 3079, 3787, 4883, 580, 4667, 6, 4314, 750, 790, 2107, 1081, 4535, 4928, 3809, 934, 61, 3067};
    Comparator comp = compare;
    std::vector<int> sorted = mergeInsertionSort(comp, unsorted);

    std::cout << "Sorted array:";
    for (int num : sorted) {
        std::cout << " " << num;
    }
    std::cout << std::endl;

    for (size_t i = 0; i < sorted.size() - 1; i++){
        
        if (sorted[i] > sorted[i + 1]){
            std::cout << "incorret order" << std::endl;
            std::cout << sorted[i] << "   " << sorted[i + 1] << std::endl;
            break;
        }
    }

    return 0;
}
