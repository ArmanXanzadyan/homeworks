#include <iostream>
#include <cmath>

struct SinglyLinkedListNode
{
    int data;
    SinglyLinkedListNode* next;

    SinglyLinkedListNode(int value)
    {
        data = value;
        next = nullptr;
    }
};

int
length(SinglyLinkedListNode* head)
{
    int count = 0;
    while (head != nullptr) {
        ++count;
        head = head->next;
    }
    return count;
}

int
findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2)
{
    const int len1 = length(head1);
    const int len2 = length(head2);

    int diff = std::abs(len1 - len2);

    if (len1 > len2) {
        for (int i = 0; i < diff; ++i)
            head1 = head1->next;
    } else {
        for (int i = 0; i < diff; ++i)
            head2 = head2->next;
    }

    while (head1 != nullptr && head2 != nullptr) {
        if (head1 == head2)
            return head1->data;
        head1 = head1->next;
        head2 = head2->next;
    }

    return -1;
}

int
main()
{
    int n1, n2;
    std::cin >> n1 >> n2;

    SinglyLinkedListNode* head1 = nullptr;
    SinglyLinkedListNode* tail1 = nullptr;
    for (int i = 0; i < n1; ++i) {
        int x;
        std::cin >> x;
        SinglyLinkedListNode* node = new SinglyLinkedListNode(x);
        if (head1 == nullptr) {
            head1 = node;
            tail1 = node;
        } else {
            tail1->next = node;
            tail1 = node;
        }
    }

    SinglyLinkedListNode* head2 = nullptr;
    SinglyLinkedListNode* tail2 = nullptr;
    for (int i = 0; i < n2; ++i) {
        int x;
        std::cin >> x;
        SinglyLinkedListNode* node = new SinglyLinkedListNode(x);
        if (head2 == nullptr) {
            head2 = node;
            tail2 = node;
        } else {
            tail2->next = node;
            tail2 = node;
        }
    }

    std::cout << findMergeNode(head1, head2) << '\n';

    return 0;
}

