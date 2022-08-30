//Created by Gunjan Dhanuka on 13th Sept 2021//

//CS204 Lab Assessment 2//

#include <iostream>
using namespace std;


//create the node strucute for a Doubly Linked List
class DllNode
{
public:
    DllNode()
    {
        data = 0;
        next = nullptr;
        prev = nullptr;
    }
    DllNode(int value)
    {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
    virtual ~DllNode()
    {
        //dtor
    }
    int getData()
    {
        return data;
    }
    bool setData(int value)
    {
        data = value;
        return true;
    }
    DllNode *getNextPtr()
    {
        return next;
    }
    DllNode *getPrevPtr()
    {
        return prev;
    }
    bool setNextPtr(DllNode *ptr)
    {
        next = ptr;
        return true;
    }
    bool setPrevPtr(DllNode *ptr)
    {
        prev = ptr;
        return true;
    }

protected:
    int data;
    DllNode *next;
    DllNode *prev;
};


//Doubly Linked List ADT
class DoublyLinkedList
{
public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    virtual ~DoublyLinkedList()
    {
        //dtor
    }

    bool isEmpty()
    {
        if (head == nullptr)
        {
            return true;
        }

        return false;
    }

    //Add an item at the beginning of the list
    void addB(DllNode *nodePtr)
    {
        if (isEmpty())
        {
            head = nodePtr;
            tail = nodePtr;
            tail->setNextPtr(head);
            head->setPrevPtr(tail);
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

    //Add the item after the tail of the list
    void addE(DllNode *nodePtr)
    {
        if (isEmpty())
        {
            addB(nodePtr);
            return;
        }

        tail->setNextPtr(nodePtr);
        nodePtr->setPrevPtr(tail);
        tail = nodePtr;
        tail->setNextPtr(head);
        head->setPrevPtr(tail);
    }

    //Find and print the mirror points according to the question
    void findMirrorPoints()
    {
        int index = 0;

        int mirrorcount = 0;
        int mirrorIndex[100000];
        DllNode *curr = head;

        if (isEmpty())
        {
            cout << "Total mirror points: 0" << endl;
            return;
        }

        //do-while loop to ensure that the body gets executed atleast once
        do
        {
            DllNode *clock = curr->getNextPtr();
            DllNode *anticlock = curr->getPrevPtr();
            int wasMP = 1;
            do
            {
                if (clock->getData() != anticlock->getData())
                {
                    wasMP = 0;
                    break;
                }
                clock = clock->getNextPtr();
                anticlock = anticlock->getPrevPtr();
            } while (clock != anticlock);

            if (wasMP == 1)
            {
                mirrorIndex[mirrorcount] = index;
                mirrorcount++;
            }
            index++;
            curr = curr->getNextPtr();
        } while (curr != head);

        if (mirrorcount == 0)
        {
            cout << "Total mirror points: 0" << endl;
            return;
        }

        cout << "Total mirror points: " << mirrorcount << " Indices: ";
        for (int i = 0; i < mirrorcount; i++)
        {
            cout << mirrorIndex[i] << " ";
        }
        cout << endl;
        return;
    }

protected:
    DllNode *head;
    DllNode *tail;
};

int main()
{
    int input;
    cin >> input;

    DoublyLinkedList dll;

    while (cin >> input)
    {
        switch (input)
        {
        case 1:
        {
            DoublyLinkedList dll;
            break;
        }
        case 2:
        {
            int value;
            cin >> value;
            DllNode *node = new DllNode();
            node->setData(value);
            dll.addB(node);
            break;
        }

        case 3:
        {
            int value;
            cin >> value;
            DllNode *node = new DllNode();
            node->setData(value);
            dll.addE(node);
            break;
        }

        case 4:
        {
            dll.findMirrorPoints();
            break;
        }

        default:
        {
            cout << "Invalid Option." << endl;
            break;
        }
        }
    }
}