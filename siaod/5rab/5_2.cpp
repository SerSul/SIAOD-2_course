#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>

struct Node {
    char groupName[50];
    int studentCount;
    Node* left;
    Node* right;
};

class SplayTree {
public:
    int totalRotations = 0;
    int totalInsertions = 0;
    int totalComparisons = 0; // Добавляем счетчик сравнений.
    SplayTree() : root(nullptr) {}

    void insert(const char groupName[50], int studentCount);
    Node* search(const char groupName[50]);
    void remove(const char groupName[50]);
    void printTree();
    Node* minValueNode(Node* node);

    void saveToFile(const char* filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            saveTreeRec(file, root);
            file.close();
            std::cout << "Дерево сохранено в файле " << filename << std::endl;
        }
        else {
            std::cerr << "Ошибка при открытии файла для сохранения." << std::endl;
        }
    }

    void loadFromFile(const char* filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            char groupName[50];
            int studentCount;
            while (file >> groupName >> studentCount) {
                insert(groupName, studentCount);
            }
            file.close();
            std::cout << "Дерево загружено из файла " << filename << std::endl;
        }
        else {
            std::cerr << "Ошибка при открытии файла для загрузки." << std::endl;
        }
    }

private:
    Node* root;

    void saveTreeRec(std::ofstream& file, Node* node) {
        if (node != nullptr) {
            file << node->groupName << " " << node->studentCount << std::endl;
            saveTreeRec(file, node->left);
            saveTreeRec(file, node->right);
        }
    }

    Node* insertRec(Node* node, const char groupName[50], int studentCount);
    Node* deleteRec(Node* node, const char groupName[50]);
    Node* splay(Node* node, const char groupName[50]);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* newNode(const char groupName[50], int studentCount);
    void printTreeRec(Node* node, int depth);
};

void SplayTree::insert(const char groupName[50], int studentCount) {
    root = insertRec(root, groupName, studentCount);
    root = splay(root, groupName); // Балансировка после вставки.
}

Node* SplayTree::search(const char groupName[50]) {
    auto start = std::chrono::high_resolution_clock::now(); // Засекаем начальное время.

    root = splay(root, groupName);
     // Увеличиваем счетчик сравнений при каждом сравнении.

    auto end = std::chrono::high_resolution_clock::now(); // Засекаем конечное время.
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Время поиска: " << duration.count() << " микросекунд" << std::endl;
    std::cout << "Количество сравнений: " << totalComparisons << std::endl;
    totalComparisons = 0;
    if (strcmp(root->groupName, groupName) == 0) {
        return root;
    }
    else {
        return nullptr;
    }
}

void SplayTree::remove(const char groupName[50]) {
    root = deleteRec(root, groupName);
    if (root != nullptr) {
        root = splay(root, groupName); // Балансировка после удаления.
    }
}

Node* SplayTree::insertRec(Node* node, const char groupName[50], int studentCount) {
    if (node == nullptr) {
        return newNode(groupName, studentCount);
    }

    if (strcmp(groupName, node->groupName) < 0) {
        node->left = insertRec(node->left, groupName, studentCount);
        totalRotations++; // Count rotations when rotating left.
    }
    else if (strcmp(groupName, node->groupName) > 0) {
        node->right = insertRec(node->right, groupName, studentCount);
        totalRotations++; // Count rotations when rotating right.
    }

    totalInsertions++;

    return node;
}

Node* SplayTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* SplayTree::deleteRec(Node* node, const char groupName[50]) {
    if (node == nullptr) {
        return node;
    }

    if (strcmp(groupName, node->groupName) < 0) {
        node->left = deleteRec(node->left, groupName);
    }
    else if (strcmp(groupName, node->groupName) > 0) {
        node->right = deleteRec(node->right, groupName);
    }
    else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = minValueNode(node->right);
        strcpy(node->groupName, temp->groupName);
        node->studentCount = temp->studentCount;
        node->right = deleteRec(node->right, temp->groupName);
    }

    return node;
}

Node* SplayTree::splay(Node* node, const char groupName[50]) {
    if (node == nullptr || strcmp(node->groupName, groupName) == 0) {
        return node;
    }

    if (strcmp(groupName, node->groupName) < 0) {
        totalComparisons++; // Увеличиваем счетчик сравнений при каждом сравнении.
        if (node->left == nullptr) {
            return node;
        }

        if (strcmp(groupName, node->left->groupName) < 0) {
            node->left->left = splay(node->left->left, groupName);
            totalComparisons++; // Увеличиваем счетчик сравнений при каждом сравнении.
            node = rightRotate(node);
        }
        else if (strcmp(groupName, node->left->groupName) > 0) {
            node->left->right = splay(node->left->right, groupName);
            totalComparisons++; // Увеличиваем счетчик сравнений при каждом сравнении.
            if (node->left->right != nullptr) {
                node->left = leftRotate(node->left);
            }
        }

        return (node->left == nullptr) ? node : rightRotate(node);
    }
    else {
        totalComparisons++; // Увеличиваем счетчик сравнений при каждом сравнении.
        if (node->right == nullptr) {
            return node;
        }

        if (strcmp(groupName, node->right->groupName) < 0) {
            node->right->left = splay(node->right->left, groupName);
            totalComparisons++; // Увеличиваем счетчик сравнений при каждом сравнении.
            if (node->right->left != nullptr) {
                node->right = rightRotate(node->right);
            }
        }
        else if (strcmp(groupName, node->right->groupName) > 0) {
            node->right->right = splay(node->right->right, groupName);
            totalComparisons++; // Увеличиваем счетчик сравнений при каждом сравнении.
            node = leftRotate(node);
        }

        return (node->right == nullptr) ? node : leftRotate(node);
    }
}


Node* SplayTree::rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

Node* SplayTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

void SplayTree::printTree() {
    printTreeRec(root, 0);
}

Node* SplayTree::newNode(const char groupName[50], int studentCount) {
    Node* node = new Node;
    strcpy(node->groupName, groupName);
    node->studentCount = studentCount;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void SplayTree::printTreeRec(Node* node, int depth) {
    if (node != nullptr) {
        printTreeRec(node->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            std::cout << "  ";
        }
        std::cout << node->groupName << " (" << node->studentCount << ")\n";
        printTreeRec(node->left, depth + 1);
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    SplayTree tree;
    bool exitMenu = false;

    do {
        std::cout << "Выберите операцию:" << std::endl;
        std::cout << "1. Вставить элемент" << std::endl;
        std::cout << "2. Найти элемент" << std::endl;
        std::cout << "3. Удалить элемент" << std::endl;
        std::cout << "4. Вывести дерево" << std::endl;
        std::cout << "5. Сохранить дерево в файл" << std::endl;
        std::cout << "6. Загрузить дерево из файл" << std::endl;
        std::cout << "7. Создать файл с тестовыми данными" << std::endl;
        std::cout << "8. Выйти" << std::endl;

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Очистить буфер ввода.

        switch (choice) {
        case 1: {
            char groupName[50];
            int studentCount;
            std::cout << "Введите название группы: ";
            std::cin.getline(groupName, 50);
            std::cout << "Введите количество студентов: ";
            std::cin >> studentCount;
            tree.insert(groupName, studentCount);
            std::cout << "Элемент вставлен в дерево." << std::endl;
            break;
        }
        case 2: {
            char groupName[50];
            std::cout << "Введите название группы для поиска: ";
            std::cin.getline(groupName, 50);
            Node* searchResult = tree.search(groupName);
            if (searchResult != nullptr) {
                std::cout << "Группа " << groupName << ": Количество студентов - " << searchResult->studentCount << std::endl;
            }
            else {
                std::cout << "Группа " << groupName << " не найдена в дереве." << std::endl;
            }
            break;
        }
        case 3: {
            char groupName[50];
            std::cout << "Введите название группы для удаления: ";
            std::cin.getline(groupName, 50);
            tree.remove(groupName);
            std::cout << "Группа " << groupName << " удалена из дерева." << std::endl;
            break;
        }
        case 4:
            std::cout << "Дерево:\n";
            tree.printTree();
            break;
        case 5: {
            char filename[100];
            std::cout << "Введите имя файла для сохранения: ";
            std::cin.getline(filename, 100);
            tree.saveToFile(filename);
            break;
        }
        case 6: {
            char filename[100];
            std::cout << "Введите имя файла для загрузки: ";
            std::cin.getline(filename, 100);
            tree.loadFromFile(filename);
            if (tree.totalInsertions > 0) {
                std::cout << "Количество поворотов: " << tree.totalRotations << "\n" << "Кол-во добавленных записей: " << tree.totalInsertions << "\n";
                double averageRotations = static_cast<double>(tree.totalRotations) / tree.totalInsertions;
                std::cout << "Среднее число выполненных поворотов: " << averageRotations << std::endl;
            }
            break;
        }
        case 7: {
            int numRecords =0;
            std::cin >> numRecords;
            const char* filename = "test_data.dat";

            std::ofstream file(filename);
            if (file.is_open()) {
                srand(static_cast<unsigned>(time(nullptr)));

                for (int i = 0; i < numRecords; ++i) {
                    char groupName[50];
                    int studentCount = rand() % 100 + 1; // Random student count between 1 and 100
                    snprintf(groupName, sizeof(groupName), "Group%d", rand()%10000+1);

                    file << groupName << " " << studentCount << std::endl;
                }

                file.close();
                std::cout << "Создан файл с тестовыми данными: " << filename << std::endl;
            }
            else {
                std::cerr << "Ошибка при создании файла для тестовых данных." << std::endl;
            }
            break;
        }
        case 8:
            exitMenu = true;
            break;
        default:
            std::cout << "Некорректный выбор. Пожалуйста, выберите операцию снова." << std::endl;
        }
    } while (!exitMenu);

    return 0;
}
