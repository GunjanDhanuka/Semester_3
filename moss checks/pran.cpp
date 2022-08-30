#include <iostream>

using namespace std;

class dllNode
{
public:
    dllNode();

    virtual ~dllNode();
    int getData();
    bool setData(int);
    dllNode *getNextPtr();
    dllNode *getPrevPtr();
    bool setNextPtr(dllNode *);
    bool setPrevPtr(dllNode *);

protected:
private:
    int data;
    dllNode *next;
    dllNode *prev;
};

dllNode::dllNode()
{
    data = 0;
    next = nullptr;
    prev = nullptr;
}

int dllNode::getData()
{
    return (data);
}

bool dllNode::setData(int val)
{
    data = val;
    return (true);
}

dllNode *dllNode::getNextPtr()
{
    return (next);
}
dllNode *dllNode::getPrevPtr()
{
    return (prev);
}

bool dllNode::setNextPtr(dllNode *nodePtr)
{
    next = nodePtr;
    return (true);
}
bool dllNode::setPrevPtr(dllNode *nodePtr)
{
    prev = nodePtr;
    return (true);
}
dllNode::~dllNode()
{
    //dtor
}

class DoublyLinkedList
{
public:
    DoublyLinkedList();
    virtual ~DoublyLinkedList();
    void addB(dllNode *nodePtr);
    void addE(dllNode *nodePtr);
    dllNode *getLastNodeAddress();
    dllNode *getHead();
    void printlist();
    dllNode *deleteB();
    dllNode *deleteE();
    bool isEmpty();
    void FindMirror();

protected:
private:
    dllNode *head;
    dllNode *tail;
};

DoublyLinkedList::DoublyLinkedList()
{
    head = nullptr;
    tail = nullptr;
}

void DoublyLinkedList::addB(dllNode *nodePtr)

{
    if (isEmpty())
    {
        head = nodePtr;
        tail = nodePtr;
        head->setPrevPtr(tail);
        tail->setNextPtr(head);
        return;
    }
    else
    {
        nodePtr->setNextPtr(head);
        head->setPrevPtr(nodePtr);
        head = nodePtr;
        head->setPrevPtr(tail);
        tail->setNextPtr(head);
    }
}

void DoublyLinkedList::addE(dllNode *nodePtr)
{
    if (isEmpty())
    {
        addB(nodePtr);
        return;
    }
    else
    {
        tail->setNextPtr(nodePtr);
        nodePtr->setPrevPtr(tail);
        tail = nodePtr;
        head->setPrevPtr(tail);
        tail->setNextPtr(head);
    }
}

void DoublyLinkedList::printlist()
{
    dllNode *curr;
    curr = head;
    cout << "the doubly linked list is" << endl;
    do
    {
        cout << " " << curr->getData() << " ";
        curr = curr->getNextPtr();
    } while (curr != head);
    cout << endl;
}

void DoublyLinkedList::FindMirror()
{
    dllNode *curr;
    curr = head;
    int count = 0, index = 0;
    int ar[1000000];

    if (!isEmpty())
    {
        do
        {
            dllNode *cl;
            dllNode *acl;
            cl = curr->getNextPtr();
            acl = curr->getPrevPtr();
            bool flag = true;
            while (cl != acl)
            {
                if (cl->getData() != acl->getData())
                {
                    flag = false;
                    break;
                }
                cl = cl->getNextPtr();
                acl = acl->getPrevPtr();
            }
            if (flag)
            {
                ar[count] = index;
                count++;
            }
            index++;
            curr = curr->getNextPtr();
        } while (curr != head);
        cout << "Total Mirror points: " << count << " "
             << "Indices: ";
        for (int i = 0; i < count; i++)
        {
            cout << ar[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Total Mirror points: 0" << endl; 
    }
}

bool DoublyLinkedList::isEmpty()
{
    if (head == nullptr)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

DoublyLinkedList::~DoublyLinkedList()
{
    //dtor
}

int main()
{
    int n;
    cin >> n;
    DoublyLinkedList l1;
    dllNode *n1;
    while (cin >> n)
    {
        if (n == 2)
        {
            cin >> n;
            n1 = new dllNode();
            n1->setData(n);
            l1.addB(n1);
        }
        else if (n == 3)
        {
            cin >> n;
            n1 = new dllNode();
            n1->setData(n);
            l1.addE(n1);
        }
        else if (n == 4)
        {
            l1.FindMirror();
        }
    }
}