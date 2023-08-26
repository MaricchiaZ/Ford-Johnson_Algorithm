#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>

int compare(int x, int y) {
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

typedef std::function<int(int, int)> Comparator;

Comparator fnToComparator(Comparator f) {
    return [f](int x, int y) {
        int r = f(x, y);
        if (std::is_arithmetic<decltype(r)>::value) {
            return r;
        } else {
            if (r) return -1;
            if (f(y, x)) return 1;
            return 0;
        }
    };
}

int jacobsthal(int n) {
    return std::round((std::pow(2, n) + std::pow(-1, n - 1)) / 3);
}

std::vector<int> pendingElementOrder(int n) {
    std::vector<int> result;
    for (int i = 0; jacobsthal(i) > n; ++i) {
        result.push_back(jacobsthal(i));
    }
    result.push_back(n);
    std::vector<int> order;
    for (size_t i = 1; i < result.size(); ++i) {
        int a = result[i - 1];
        int b = result[i];
        for (int j = b - 1; j >= a; --j) {
            order.push_back(j);
        }
    }
    return order;
}

int binarySearchInsertionPoint(Comparator comp, int n, const std::vector<int>& coll, int lowerBound, int upperBound) {
    if (lowerBound > upperBound) {
        return lowerBound;
    } else {
        int midIndex = (lowerBound + upperBound) / 2;
        int compResult = comp(n, coll[midIndex]);
        if (compResult == 1) {
            return binarySearchInsertionPoint(comp, n, coll, midIndex + 1, upperBound);
        } else if (compResult == 0) {
            return midIndex;
        } else {
            return binarySearchInsertionPoint(comp, n, coll, lowerBound, midIndex - 1);
        }
    }
}

std::vector<int> binaryInsert(Comparator comp, int n, const std::vector<int>& coll) {
    std::vector<int> newColl = coll;
    int insertIndex = binarySearchInsertionPoint(comp, n, coll, 0, coll.size() - 1);
    newColl.insert(newColl.begin() + insertIndex, n);
    return newColl;
}

std::vector<int> mergeInsertionSort(Comparator comp, const std::vector<int>& coll) {
    if (coll.size() < 2) {
        return coll;
    } else {
        std::vector<std::pair<int, int>> sortedPairs;
        for (size_t i = 0; i < coll.size(); i += 2) {
            int first = coll[i];
            int second = i + 1 < coll.size() ? coll[i + 1] : coll.back();
            if (comp(first, second) < 0) {
                sortedPairs.push_back(std::make_pair(first, second));
            } else {
                sortedPairs.push_back(std::make_pair(second, first));
            }
        }
        std::sort(sortedPairs.begin(), sortedPairs.end(), [comp](const std::pair<int, int>& x, const std::pair<int, int>& y) {
            return comp(x.first, y.first) < 0;
        });

        std::vector<int> mainChain;
        std::vector<int> pendingElements;
        for (const auto& pair : sortedPairs) {
            mainChain.push_back(pair.first);
            pendingElements.push_back(pair.second);
        }

        if (coll.size() % 2 != 0) {
            pendingElements.push_back(coll.back());
        }

        std::vector<int> aPositions(mainChain.size());
        for (size_t i = 0; i < mainChain.size(); ++i) {
            aPositions[i] = i;
        }

        auto mainChainUntil = [&](int aIndex) -> std::vector<int> {
            int end = aPositions[aIndex];
            return std::vector<int>(mainChain.begin(), mainChain.begin() + end);
        };

        auto binaryInsertLambda = [&](int bIndex) {
            int n = pendingElements[bIndex];
            int insertIndex = binarySearchInsertionPoint(comp, n, mainChain, 0, mainChainUntil(bIndex).size() - 1);
            for (size_t i = 0; i < aPositions.size(); ++i) {
                if (aPositions[i] >= insertIndex) {
                    ++aPositions[i];
                }
            }
            mainChain.insert(mainChain.begin() + insertIndex, n);
        };

        std::vector<int> order = pendingElementOrder(pendingElements.size());
        for (int i : order) {
            binaryInsertLambda(i);
        }

        return mainChain;
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
