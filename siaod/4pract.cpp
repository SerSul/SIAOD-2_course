#include <iostream>

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void insert(char value) {
        root = insertRec(root, value);
    }

    void display() {
        displayTree(root, 0);
    }

    int findLevel(char value) {
        return findLevelRec(root, value, 1);
    }
    int getHeightDifference() {
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        return leftHeight - rightHeight;
    }

    void destroy() {
        destroyTree(root);
        root = nullptr;
    }
private:
    Node* root;

    Node* insertRec(Node* node, char value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertRec(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }

        return node;
    }

    void displayTree(Node* node, int indent) {
        if (node != nullptr) {
            displayTree(node->right, indent + 4);
            for (int i = 0; i < indent; i++) {
                std::cout << ' ';
            }
            std::cout << node->data << "\n";
            displayTree(node->left, indent + 4);
        }
    }

    int findLevelRec(Node* node, char value, int level) {
        if (node == nullptr) {
            return -1; // Узел не найден
        }

        if (value == node->data) {
            return level;
        }

        if (value < node->data) {
            return findLevelRec(node->left, value, level + 1);
        }
        else {
            return findLevelRec(node->right, value, level + 1);
        }
    }
    //Определить, какое из поддеревьев выше:
    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return 1 + std::max(leftHeight, rightHeight);
    }

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

};

int main() {
    setlocale(LC_ALL, "ru");
    BinarySearchTree tree;
    char choice;
    char value;
    int level = -1;
    int heightDifference = -1;

    while (true) {
        std::cout << "Меню:\n";
        std::cout << "1. Вставить элемент\n";
        std::cout << "2. Отобразить дерево\n";
        std::cout << "3. Найти уровень узла\n";
        std::cout << "4. Определить, какое поддерево выше\n";
        std::cout << "5. Удалить дерево\n";
        std::cout << "6. Выйти\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;

        switch (choice) {
        case '1':
            std::cout << "Введите значение для вставки: ";
            std::cin >> value;
            tree.insert(value);
            break;
        case '2':
            std::cout << "Дерево:\n";
            tree.display();
            break;
        case '3':
            std::cout << "Введите значение, чтобы найти уровень: ";
            std::cin >> value;
            level = tree.findLevel(value);
            if (level != -1) {
                std::cout << "Уровень узла с значением " << value << " равен " << level << std::endl;
            }
            else {
                std::cout << "Узел с значением " << value << " не найден в дереве." << std::endl;
            }
            break;
        case '4':
            heightDifference = tree.getHeightDifference();
            if (heightDifference > 0) {
                std::cout << "Левое поддерево выше на " << heightDifference << " уровней." << std::endl;
            }
            else if (heightDifference < 0) {
                std::cout << "Правое поддерево выше на " << -heightDifference << " уровней." << std::endl;
            }
            else {
                std::cout << "Левое и правое поддерево равны по высоте." << std::endl;
            }
            break;
        case '5':
            tree.destroy(); // Вызов метода для удаления дерева
            std::cout << "Дерево удалено." << std::endl;
            break;
        case '6':
            return 0;
        default:
            std::cout << "Неверная опция. Попробуйте снова.\n";
        }
    }

    return 0;
}
