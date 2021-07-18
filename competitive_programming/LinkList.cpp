#include <iostream>

typedef struct Node
{
    int data;
    struct Node *next;
    Node(int value = 0) : data(value), next(nullptr) {};
} Node_t;


class LinkList
{
    Node_t *first;
    Node_t *last;
    uint32_t number_of_nodes;

public:
    LinkList() : first(nullptr), last(nullptr), number_of_nodes(0) {}
    ~LinkList() = default;
    void PushBack(int value);
    void PushFront(int value);
    bool IsEmpty();
    int PopFront();
    void Reverse();
    void Display();
};

bool LinkList::IsEmpty()
{
    if (number_of_nodes == 0)
        return true;
    return false;
}
void LinkList::PushBack(int value)
{
    Node_t *p = new Node_t(value);
    if (first == nullptr)
    {
        first = p;
        last = p;
    }
    else
    {
        last->next = p;
        last = p;
    }
    number_of_nodes++;
}
void LinkList::PushFront(int value)
{
    Node_t *p = new Node_t(value);
    if (first == nullptr)
    {
        first = p;
        last = p;
    }
    else
    {
        p->next = first;
        first = p;
    }

    number_of_nodes++;
}

void LinkList::Reverse()
{
}

int LinkList::PopFront()
{
    int lRet = 0;
    Node_t *p = first;

    if (!IsEmpty())
    {
        first = first->next;
        lRet = p->data;
        delete p;
        number_of_nodes--;
        return lRet;
    }
    std::cout << "LinkList is empty." << std::endl;

    return 0;
}

void LinkList::Display()
{
    Node_t *p = first;
    std::cout << "Display LinkList: " << std::endl;
    while(p != nullptr)
    {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
    std::cout << "Number of nodes: " << number_of_nodes << std::endl;
}

int main()
{
    LinkList aList;

    aList.PushFront(55);
    aList.PushBack(10);
    aList.PushBack(20);
    aList.PushBack(30);
    aList.PushFront(89);
    aList.PushFront(9);
    aList.Display();

    std::cout << "Pop front from a List: " << aList.PopFront() << std::endl;
    std::cout << "Pop front from a List: " << aList.PopFront() << std::endl;
    std::cout << "Pop front from a List: " << aList.PopFront() << std::endl;
    std::cout << "Pop front from a List: " << aList.PopFront() << std::endl;
    std::cout << "Pop front from a List: " << aList.PopFront() << std::endl;

    aList.Display();

    return 0;
}