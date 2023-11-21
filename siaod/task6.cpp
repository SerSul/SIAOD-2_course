#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <stack>
#include <algorithm>

class Graph {
private:
    int vertices;
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    Graph(int v) : vertices(v), adjacencyMatrix(v, std::vector<int>(v, 0)) {}


    void addEdge(int from, int to, int weight) {
        if (from >= 0 && from < vertices && to >= 0 && to < vertices) {
            adjacencyMatrix[from][to] = weight;
            adjacencyMatrix[to][from] = weight;
        }
        else {
            std::cout << "Ошибка: Некорректные индексы вершин.\n";
        }
    }

    void printGraph() const {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

  

    bool isBipartiteUtil(int u, std::vector<int>& color) {
        for (int v = 0; v < vertices; ++v) {
            if (adjacencyMatrix[u][v] != 0) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    if (!isBipartiteUtil(v, color)) {
                        return false;
                    }
                }
                else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
        return true;
    }

    void canDivideIntoTwoGroups() {
        std::vector<int> color(vertices, -1);

        for (int i = 0; i < vertices; ++i) {
            if (color[i] == -1) {
                color[i] = 0;
                if (!isBipartiteUtil(i, color)) {
                    std::cout << "Нельзя разделить людей на 2 группы.\n";
                    return;
                }
            }
        }

        std::cout << "Можно разделить людей на 2 группы.\n";
    }

    void createGramp1var(Graph& graph) {
        graph.addEdge(0, 1, 1);
        graph.addEdge(0, 2, 2);
        graph.addEdge(0, 4, 10); //Из-в-вес
        graph.addEdge(1, 4, 6);
        graph.addEdge(2, 4, 7);
        graph.addEdge(2, 3, 4);
        graph.addEdge(4, 3, 11);
        graph.addEdge(1, 3, 3);
    }

    void findMinWeightCycle(int K) {
        std::vector<bool> visited(vertices, false);
        std::vector<int> path;
        std::vector<int> minPath;
        int minWeight = std::numeric_limits<int>::max();

        for (int i = 0; i < vertices; ++i) {
            if (!visited[i]) {
                path.clear();
                findMinWeightCycleDFS(i, K, 0, visited, path, minWeight, minPath);
            }
        }

        if (minWeight != std::numeric_limits<int>::max()) {
            std::cout << "Цикл с минимальным весом из " << K << " вершин: ";
            for (int vertex : minPath) {
                std::cout << vertex + 1 << " "; // увеличиваем на 1 для вывода индексов вершин с 1
            }
            std::cout << " (вес: " << minWeight << ")\n";
        }
        else {
            std::cout << "Цикл из " << K << " вершин не найден.\n";
        }
    }

    void findMinWeightCycleDFS(int current, int K, int currentWeight, std::vector<bool>& visited,
        std::vector<int>& path, int& minWeight, std::vector<int>& minPath) {
        visited[current] = true;
        path.push_back(current);

        if (path.size() == K) {
            // Проверяем, является ли текущий путь циклом и обновляем минимальный вес и путь
            int cycleWeight = 0;
            for (size_t i = 0; i < path.size() - 1; ++i) {
                cycleWeight += adjacencyMatrix[path[i]][path[i + 1]];
            }
            cycleWeight += adjacencyMatrix[path.back()][path.front()];

            if (cycleWeight < minWeight) {
                minWeight = cycleWeight;
                minPath = path;
            }
        }
        else {
            // Продолжаем DFS для соседних вершин
            for (int neighbor = 0; neighbor < vertices; ++neighbor) {
                if (!visited[neighbor] && adjacencyMatrix[current][neighbor] != 0) {
                    findMinWeightCycleDFS(neighbor, K, currentWeight + adjacencyMatrix[current][neighbor],
                        visited, path, minWeight, minPath);
                }
            }
        }

        // Возвращаемся на предыдущую вершину при завершении DFS
        visited[current] = false;
        path.pop_back();
    }


};

void printMenu() {
    std::cout << "\n1. Добавить ребро\n"
        "2. Вывести граф\n"
        "3. Поиск цикла с наименьшим весом из K вершин\n"
        "4. Проверить, можно ли разбить людей на 2 группы\n"
        "5. Создать граф по 1 графу\n"
        "6. Выход\n";
}



int main() {
    setlocale(LC_ALL, "ru");
    int numVertices;
    std::cout << "Введите количество вершин графа: ";
    std::cin >> numVertices;

    Graph graph(numVertices);

    int choice;
    do {
        printMenu();
        std::cout << "Выберите действие (1-5): ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int from, to, weight;
            std::cout << "Введите ребро (from to weight): ";
            std::cin >> from >> to >> weight;
            graph.addEdge(from - 1, to - 1, weight); // уменьшаем на 1 для работы с индексами от 0
            break;
        }
        case 2: {
            std::cout << "Матрица смежности графа:" << std::endl;
            graph.printGraph();
            break;
        }
        case 3: {
            int K;
            std::cout << "Введите K для поиска цикла: ";
            std::cin >> K;
            graph.findMinWeightCycle(K);
            break;
        }
        case 4: {
            graph.canDivideIntoTwoGroups();
            break;
        }
        case 5:
            graph.createGramp1var(graph);
            break;
        case 6:
            std::cout << "Выход из программы.\n";
            break;


        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }

    } while (choice != 6);

    return 0;
}
