#include <iostream>

struct DoublyLinkedListNode
{
    int data;
    DoublyLinkedListNode* next;
    DoublyLinkedListNode* prev;

    DoublyLinkedListNode(int value)
    {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

DoublyLinkedListNode*
reverse(DoublyLinkedListNode* head)
{
    if (head == nullptr)
        return head;

    DoublyLinkedListNode* current = head;
    DoublyLinkedListNode* pointer = nullptr;

    while (current != nullptr) {
        pointer = current->prev;
        current->prev = current->next;
        current->next = pointer;
        current = current->prev;
    }

    if (pointer != nullptr)
        head = pointer->prev;

    return head;
}

void
printList(DoublyLinkedListNode* head)
{
    while (head != nullptr) {
        std::cout << head->data << ' ';
        head = head->next;
    }
    std::cout << '\n';
}

int
main()
{
    int n;
    std::cin >> n;

    DoublyLinkedListNode* head = nullptr;
    DoublyLinkedListNode* tail = nullptr;

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        DoublyLinkedListNode* node = new DoublyLinkedListNode(x);

        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    std::cout << "Original list: ";
    printList(head);

    head = reverse(head);

    std::cout << "Reversed list: ";
    printList(head);

    return 0;
}

