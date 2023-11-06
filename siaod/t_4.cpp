#include <iostream>
#include <fstream>
#include <string>

const std::string dataFileName = "data.dat";


struct TreeNode {
    std::string groupName; // �������� ������
    int studentCount; // ���������� ���������

    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& group, int count)
        : groupName(group), studentCount(count), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree(const std::string& filename) : root(nullptr), dataFile(filename, std::ios::in | std::ios::out | std::ios::binary) {
    if (!dataFile) {
        dataFile.open(filename, std::ios::out | std::ios::binary);
    } else {
        root = loadTreeFromBinaryFile();
    }
}

TreeNode* loadTreeFromBinaryFile() {
    dataFile.clear();
    dataFile.seekg(0, std::ios::beg);

    TreeNode* node = nullptr;
    while (true) {
        std::string groupName;
        if (!std::getline(dataFile, groupName, '\0')) {
            break;
        }

        int studentCount;
        dataFile.read(reinterpret_cast<char*>(&studentCount), sizeof(studentCount));

        node = insertNode(node, groupName, studentCount);
    }

    return node;
}


    void insert(const std::string& group, int count) {
        root = insertNode(root, group, count);
        saveTreeToBinaryFile(root);
    }


    TreeNode* search(const std::string& group) {
        return searchNode(root, group);
    }

    void remove(const std::string& group) {
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
            std::cout << "�� ������� ������� ��������� ����." << std::endl;
            return;
        }

        // ��������� ������������ �������� ����, ���� ������
        if (dataFile.is_open()) {
            dataFile.close();
        }

        // ������� ����� �������� ���� ��� ������
        dataFile.open(dataFileName, std::ios::out | std::ios::binary);

        std::string groupName;
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

    TreeNode* insertNode(TreeNode* node, const std::string& group, int count) {
        if (node == nullptr) {
            return new TreeNode(group, count);
        }

        if (group < node->groupName) {
            node->left = insertNode(node->left, group, count);
        }
        else if (group > node->groupName) {
            node->right = insertNode(node->right, group, count);
        }

        return node;
    }

    TreeNode* searchNode(TreeNode* node, const std::string& group) {
        if (node == nullptr || node->groupName == group) {
            return node;
        }

        if (group < node->groupName) {
            return searchNode(node->left, group);
        }

        return searchNode(node->right, group);
    }

    TreeNode* findMinNode(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode* removeNode(TreeNode* node, const std::string& group) {
        if (node == nullptr) {
            return node;
        }

        if (group < node->groupName) {
            node->left = removeNode(node->left, group);
        }
        else if (group > node->groupName) {
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
            node->groupName = temp->groupName;
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
        dataFile.write(node->groupName.c_str(), node->groupName.size());
        dataFile.write("\0", 1);
        dataFile.write(reinterpret_cast<char*>(&node->studentCount), sizeof(node->studentCount));
        saveNodeToBinaryFile(node->right);
    }
};




int main() {
    setlocale(LC_ALL, "ru");
    BinarySearchTree tree(dataFileName);

    int choice;
    std::string group;
    TreeNode* result;

    do {
        std::cout << "����:" << std::endl;
        std::cout << "1. �������� ������" << std::endl;
        std::cout << "2. ����� ������" << std::endl;
        std::cout << "3. ������� ������" << std::endl;
        std::cout << "4. ���������� ������" << std::endl;
        std::cout << "5. ������� �������� ���� �� ���������� �����" << std::endl;
        std::cout << "6. �����" << std::endl;
        std::cout << "�������� �������� (1/2/3/4/5/6): ";
        std::string textFileName;
        std::cin >> choice;


        switch (choice) {
        case 1:
            std::cout << "������� �������� ������: ";
            std::cin >> group;
            std::cout << "������� ���������� ���������: ";
            int count;
            std::cin >> count;
            tree.insert(group, count);
            std::cout << "������ ���������." << std::endl;
            break;
        case 2:
            std::cout << "������� �������� ������ ��� ������: ";
            std::cin >> group;
            result = tree.search(group);
            if (result) {
                std::cout << "�������: Group: " << result->groupName << " Student Count: " << result->studentCount << std::endl;
            }
            else {
                std::cout << "������ �� �������." << std::endl;
            }
            break;
        case 3:
            std::cout << "������� �������� ������ ��� ��������: ";
            std::cin >> group;
            tree.remove(group);
            std::cout << "������ �������." << std::endl;
            break;
        case 4:
            std::cout << "������:" << std::endl;
            tree.display();
            break;
        case 5:

            std::cout << "������� ��� ���������� �����: ";
            std::cin >> textFileName;
            tree.createBinaryFileFromText(textFileName);
            std::cout << "�������� ���� ������ �� ���������� �����." << std::endl;
            break;
        case 6:
            std::cout << "�����." << std::endl;
            break;
        default:
            std::cout << "�������� �����. ����������, �������� 1, 2, 3, 4 ��� 5." << std::endl;
        }
    } while (choice != 5);

    return 0;
}

