#include <iostream>

struct Node
{
    int data;
    Node* next;
    Node(int value)
    {
        data = value;
        next = nullptr;
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
insert(Node* head, int data, int position)
{
    Node* newnode = new Node(data);

    if (position == 0) {
        newnode->next = head;
        head = newnode;
        return head;
    }

    Node* current = head;
    for (int i = 0; i < position - 1; ++i) {
        if (current != nullptr)
            current = current->next;
    }

    if (current != nullptr) {
        newnode->next = current->next;
        current->next = newnode;
    }

    return head;
}

int
main()
{
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
            tail = newnode;
        }
    }

    int data;
    int position;
    std::cin >> data >> position;

    head = insert(head, data, position);
    print(head);

    return 0;
}

