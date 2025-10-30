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

bool
has_cycle(Node* head)
{
    if (head == nullptr)
        return false;

    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
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
        Node* node = new Node(x);

        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    if (has_cycle(head))
        std::cout << "Cycle detected\n";
    else
        std::cout << "No cycle\n";

    return 0;
}

