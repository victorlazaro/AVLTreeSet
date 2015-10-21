#pragma once
 
#include <iostream>
#include <cstddef>
#include <fstream>
 
using namespace std;
 
template <typename ItemType>
 
class LinkedList {
 
 
    struct Node {
        ItemType item;
        Node *next;
        Node *prev;
 
        Node(const ItemType &_item, Node *_next = NULL, Node *_prev = NULL) :
                item(_item), next(_next), prev(_prev) { }
    };
 
 
    Node *head;
    Node *tail;
    int size = 0;
 
public:
 
    ~LinkedList()
    {
        clear();
    }
    void insert(int index, ItemType& item) {
 
        if (index > size || size < 0)
        {
            return;
        }
 
        Node * newNode = new Node(item);
 
        if (size == 0)
        {
 
            head = newNode;
            tail = newNode;
            newNode->next = NULL;
            newNode->prev = NULL;
            size++;
        }
 
        else if (index == 0)
        {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
            size++;
 
        }
        else if (index == size) //INSERTING AT THE END
        {
            newNode->prev = tail;
            newNode->next = NULL;
            tail->next = newNode;
            tail = newNode;
            size++;
 
        }
        else {
            Node* n = find_node(index);
            newNode->next = n;
            newNode->prev = n->prev;
            n->prev->next = newNode;
            n->prev = newNode;
            size++;
        }
 
 
    }
 
    ItemType remove(int index) {
 
        if (head == NULL || index >= size || index < 0)
        {
           return NULL;
        }
        else {
            Node * n;
            if (size == 1) // REMOVE THE ONLY NODE
            {
                n = head;
                head = NULL;
                tail = NULL;
                size--;
 
            }
            else if (index == 0) //REMOVE THE FIRST NODE WHEN THERE'S MORE THAN ONE IN THE LIST
            {
                n = head;
                head = head->next;
                head->prev = NULL;
                size--;
 
 
            }
            else if (index == size-1) //REMOVE THE LAST WHEN THERE'S MORE THAN ONE NODE IN THE LIST
            {
                n = tail;
                tail = n->prev;
                tail->next = NULL;
                size--;
 
            }
            else
            {
                n = find_node(index);
                n->prev->next = n->next;
                n->next->prev = n->prev;
                size--;
            }
            ItemType temp = n->item;
            delete n;
            return temp;
        }
    }
 
    Node * find_node(int index)
    {
        Node * n = NULL;
 
        if (0 <= index && index <= size/2)
        {
            n = head;
            for (int i = 0; i < index; i++)
            {
                n = n->next;
            }
        }
        else if (size/2 < index && index <= size-1)
        {
            n = tail;
 
            for (unsigned i = size-1; i > index; i--)
            {
                n = n->prev;
            }
        }
        return n;
    }
    int getSize()
    {
        return size;
    }
    void print(ofstream& out, int i)
    {
        if(head == NULL)
        {
            return;
        }
 
        cout << "node " << i << ": " << getItem(i)->item << "\n";
    }
 
    ItemType getItem(const int index)
    {
        if (index > size)
        {
            return NULL;
        }
        Node* temp = head;
 
        for (unsigned i = 0; i < size; i++)
        {
            if (i == index)
            {
                return temp->item;
            }
            temp = temp-> next;
        }
        return temp->item;
 
    }
    void add(ItemType& item)
    {
        insert(size, item);
    }
 
 
/*    int find(const ItemType& item) {
 
        Node * NodeP = head;
 
        for (unsigned i = 0; i < size; i++)
        {
            if (NodeP->item == item)
            {
                return i;
            }
            NodeP = NodeP->next;
        }
        return -1;
 
    }*/
    void clear()
    {
        while (size != 0){
            remove(0);
        }
    }
 
};
