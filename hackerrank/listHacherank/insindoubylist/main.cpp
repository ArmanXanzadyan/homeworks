#include <iostream>

struct Node
{
    int data;
    Node* next;
    Node* prev;

    Node(int value)
    {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

void
print(Node* head)
{
    while (head != nullptr) {
        std::cout << head->data << ' ';
        head = head->next;
    }
    std::cout << '\n';
}

Node*
insert(Node* head, int data)
{
    Node* newnode = new Node(data);

    if (head == nullptr || head->data > data) {
        newnode->next = head;
        if (head != nullptr)
            head->prev = newnode;
        return newnode;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data < data) {
        current = current->next;
    }

    newnode->next = current->next;
    newnode->prev = current;

    if (current->next != nullptr)
        current->next->prev = newnode;

    current->next = newnode;
    return head;
}

int
main()
{
    int data;
    std::cin >> data;

    int n;
    std::cin >> n;

    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        Node* newnode = new Node(x);

        if (head == nullptr) {
            head = newnode;
            tail = newnode;
        } else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
    }

    head = insert(head, data);
    print(head);

    return 0;
}

