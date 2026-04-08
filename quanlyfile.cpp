#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ================== STRUCT ==================
struct File {
    string name;
    int size;   // MB
    int time;   // timestamp
};

struct Node {
    File data;
    Node* next;
};

struct LinkedList {
    Node* head;
};

// ================== INIT ==================
void initList(LinkedList &list) {
    list.head = NULL;
}

// ================== CREATE NODE ==================
Node* createNode(File f) {
    Node* p = new Node;
    p->data = f;
    p->next = NULL;
    return p;
}

// ================== INSERT SORTED BY TIME ==================
void insertSorted(LinkedList &list, File f) {
    Node* p = createNode(f);

    if (list.head == NULL || list.head->data.time > f.time) {
        p->next = list.head;
        list.head = p;
        return;
    }

    Node* cur = list.head;
    while (cur->next != NULL && cur->next->data.time < f.time) {
        cur = cur->next;
    }

    p->next = cur->next;
    cur->next = p;
}

// ================== PRINT LIST ==================
void printList(LinkedList list) {
    Node* cur = list.head;

    cout << "\nDanh sach file:\n";
    while (cur != NULL) {
        cout << "Ten: " << cur->data.name
             << " | Size: " << cur->data.size << " MB"
             << " | Time: " << cur->data.time << endl;
        cur = cur->next;
    }
}

// ================== TOTAL SIZE ==================
int totalSize(LinkedList list) {
    int sum = 0;
    Node* cur = list.head;

    while (cur != NULL) {
        sum += cur->data.size;
        cur = cur->next;
    }

    return sum;
}

// ================== CONVERT LIST TO VECTOR ==================
vector<File> toVector(LinkedList list) {
    vector<File> arr;
    Node* cur = list.head;

    while (cur != NULL) {
        arr.push_back(cur->data);
        cur = cur->next;
    }

    return arr;
}

// ================== REMOVE SMALLEST FILES ==================
void removeSmallestFiles(LinkedList &list, int limitMB) {
    vector<File> files = toVector(list);

    int total = 0;
    for (auto f : files) total += f.size;

    cout << "\nTong ban dau: " << total << " MB\n";

    if (total <= limitMB) {
        cout << "Khong can xoa file.\n";
        return;
    }

    // Sắp xếp tăng dần theo size
    sort(files.begin(), files.end(), [](File a, File b) {
        return a.size < b.size;
    });

    cout << "\nCac file bi xoa:\n";

    int i = 0;
    while (total > limitMB && i < files.size()) {
        cout << "- " << files[i].name 
             << " (" << files[i].size << " MB)\n";

        total -= files[i].size;
        i++;
    }

    cout << "\nTong sau khi xoa: " << total << " MB\n";
}

// ================== MENU ==================
int main() {
    LinkedList list;
    initList(list);

    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Them file\n";
        cout << "2. Hien thi danh sach\n";
        cout << "3. Tong dung luong\n";
        cout << "4. Loai bo file nho nhat (<=32GB)\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        if (choice == 1) {
            File f;
            cout << "Nhap ten file: ";
            cin >> f.name;
            cout << "Nhap size (MB): ";
            cin >> f.size;
            cout << "Nhap time: ";
            cin >> f.time;

            insertSorted(list, f);
        }

        else if (choice == 2) {
            printList(list);
        }

        else if (choice == 3) {
            cout << "Tong dung luong: " << totalSize(list) << " MB\n";
        }

        else if (choice == 4) {
            int limit = 32768; // 32GB
            removeSmallestFiles(list, limit);
        }

    } while (choice != 0);

    return 0;
}