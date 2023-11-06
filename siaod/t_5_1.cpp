#include <iostream>
#include <fstream>
#include <string>

#include <chrono>

const std::string dataFileName = "data.dat";

struct TreeNode {
    char groupName[50];
    int studentCount;

    TreeNode* left;
    TreeNode* right;

    TreeNode(const char* group, int count)
        : studentCount(count), left(nullptr), right(nullptr) {
        strncpy(groupName, group, sizeof(groupName) - 1);
        groupName[sizeof(groupName) - 1] = '\0';
    }
};

class BinarySearchTree {
public:
    BinarySearchTree(const std::string& filename) : root(nullptr), dataFile(filename, std::ios::in | std::ios::out | std::ios::binary) {
        if (!dataFile) {
            dataFile.open(filename, std::ios::out | std::ios::binary);
        }
        else {
            root = loadTreeFromBinaryFile();
        }
    }

    TreeNode* loadTreeFromBinaryFile() {
        dataFile.clear();
        dataFile.seekg(0, std::ios::beg);

        TreeNode* node = nullptr;
        while (true) {
            char groupName[50];
            if (!dataFile.read(groupName, sizeof(groupName))) {
                break;
            }

            int studentCount;
            dataFile.read(reinterpret_cast<char*>(&studentCount), sizeof(studentCount));

            node = insertNode(node, groupName, studentCount);
        }

        return node;
    }

    void insert(const char* group, int count) {
        root = insertNode(root, group, count);
        saveTreeToBinaryFile(root);
    }

    TreeNode* search(const char* group, int& comparisons) {
        return searchNode(root, group, comparisons);
    }

    void remove(const char* group) {
        root = removeNode(root, group);
        saveTreeToBinaryFile(root);
    }

    void display() {
        displayTree(root, 0);
    }

    ~BinarySearchTree() {
        if (dataFile.is_open()) {
            dataFile.close();
        }
    }

    void createBinaryFileFromText(const std::string& textFileName) {
        std::ifstream textFile(textFileName);
        if (!textFile.is_open()) {
            std::cout << "Не удалось открыть текстовый файл." << std::endl;
            return;
        }

        if (dataFile.is_open()) {
            dataFile.close();
        }

        dataFile.open(dataFileName, std::ios::out | std::ios::binary);

        char groupName[50];
        int studentCount;
        while (textFile >> groupName >> studentCount) {
            insert(groupName, studentCount);
        }

        dataFile.close();
        dataFile.open(dataFileName, std::ios::in | std::ios::out | std::ios::binary);
    }

private:
    TreeNode* root;
    std::fstream dataFile;

    TreeNode* insertNode(TreeNode* node, const char* group, int count) {
        if (node == nullptr) {
            return new TreeNode(group, count);
        }

        int compareResult = strcmp(group, node->groupName);

        if (compareResult < 0) {
            node->left = insertNode(node->left, group, count);
        }
        else if (compareResult > 0) {
            node->right = insertNode(node->right, group, count);
        }

        return node;
    }

    TreeNode* searchNode(TreeNode* node, const char* group, int& comparisons) {
        if (node == nullptr || strcmp(group, node->groupName) == 0) {
            comparisons++;
            return node;
        }

        int compareResult = strcmp(group, node->groupName);

        comparisons++;

        if (compareResult < 0) {
            return searchNode(node->left, group, comparisons);
        }

        return searchNode(node->right, group, comparisons);
    }

    TreeNode* findMinNode(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode* removeNode(TreeNode* node, const char* group) {
        if (node == nullptr) {
            return node;
        }

        int compareResult = strcmp(group, node->groupName);

        if (compareResult < 0) {
            node->left = removeNode(node->left, group);
        }
        else if (compareResult > 0) {
            node->right = removeNode(node->right, group);
        }
        else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = findMinNode(node->right);
            strncpy(node->groupName, temp->groupName, sizeof(node->groupName) - 1);
            node->groupName[sizeof(node->groupName) - 1] = '\0';
            node->studentCount = temp->studentCount;
            node->right = removeNode(node->right, temp->groupName);
        }
        return node;
    }

    void displayTree(TreeNode* node, int depth) {
        if (node != nullptr) {
            displayTree(node->right, depth + 1);
            for (int i = 0; i < depth; i++) {
                std::cout << "  ";
            }
            std::cout << node->groupName << " " << node->studentCount << std::endl;
            displayTree(node->left, depth + 1);
        }
    }

    void saveTreeToBinaryFile(TreeNode* node) {
        dataFile.clear();
        dataFile.seekp(0, std::ios::beg);

        saveNodeToBinaryFile(node);
        dataFile.flush();
    }

    void saveNodeToBinaryFile(TreeNode* node) {
        if (node == nullptr) {
            return;
        }

        saveNodeToBinaryFile(node->left);
        dataFile.write(node->groupName, sizeof(node->groupName));
        dataFile.write(reinterpret_cast<char*>(&node->studentCount), sizeof(node->studentCount));
        saveNodeToBinaryFile(node->right);
    }
};

void generateTestData(int numRecords) {
    std::ofstream file("test_data.txt");
    if (file.is_open()) {
        srand(static_cast<unsigned>(time(nullptr)));

        for (int i = 0; i < numRecords; ++i) {
            char groupName[50];
            snprintf(groupName, sizeof(groupName), "Group%d", rand()%100+1);
            int studentCount = rand() % 100 + 1;

            file << groupName << " " << studentCount << std::endl;
        }

        file.close();
        std::cout << "Создан файл с тестовыми данными: " << "test_data" << std::endl;
    }
    else {
        std::cerr << "Ошибка при создании файла для тестовых данных." << std::endl;
    }
}
int main() {
    setlocale(LC_ALL, "ru");
    BinarySearchTree tree(dataFileName);
    std::string textFileName;
    int choice;
    char group[50];
    TreeNode* result;
    int numRecords = 0;
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    double executionTime;
    int comparisons;
    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Вставить группу" << std::endl;
        std::cout << "2. Найти группу" << std::endl;
        std::cout << "3. Удалить группу" << std::endl;
        std::cout << "4. Отобразить дерево" << std::endl;
        std::cout << "5. Создать бинарный файл из текстового файла" << std::endl;
        std::cout << "6. Выход" << std::endl;
        std::cout << "Выберите действие (1/2/3/4/5/6): ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите название группы: ";
            std::cin >> group;
            std::cout << "Введите количество студентов: ";
            int count;
            std::cin >> count;
            tree.insert(group, count);
            std::cout << "Группа добавлена." << std::endl;
            break;
        case 2:
            std::cout << "Введите название группы для поиска: ";
            std::cin >> group;
            comparisons = 0;
            startTime = std::chrono::high_resolution_clock::now();
            result = tree.search(group, comparisons);
            endTime = std::chrono::high_resolution_clock::now();
            if (result) {
                std::cout << "Найдено: Group: " << result->groupName << " Student Count: " << result->studentCount << std::endl;
            }
            else {
                std::cout << "Группа не найдена." << std::endl;
            }
            std::cout << "Количество сравнений: " << comparisons << std::endl;
            executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            std::cout << "Время выполнения: " << executionTime << " Микросекунд" << std::endl;
            break;
        case 3:
            std::cout << "Введите название группы для удаления: ";
            std::cin >> group;
            tree.remove(group);
            std::cout << "Группа удалена." << std::endl;
            break;
        case 4:
            std::cout << "Дерево:" << std::endl;
            tree.display();
            break;
        case 5:
            std::cout << "Введите имя текстового файла: ";
            std::cin >> textFileName;
            tree.createBinaryFileFromText(textFileName);
            std::cout << "Бинарный файл создан из текстового файла." << std::endl;
            break;
        case 6:
            std::cout << "Выход." << std::endl;
            break;
        case 7:
            std::cout << "Введите количество записей: ";
            std::cin >> numRecords;
            generateTestData(numRecords);
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, выберите 1, 2, 3, 4 или 5." << std::endl;
        }
    } while (choice != 6);

    return 0;
}