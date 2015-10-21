#pragma once
#include <fstream>
#include "LinkedList.h"
 
using namespace std;
 
template <typename ItemType>
 
class AVLTreeSet {
 
 
public:
    AVLTreeSet()
    {
        root = NULL;
        size = 0;
    }
    ~AVLTreeSet()
    {
        clear();
    }
    struct AVLNode {
        ItemType item;
        int height;
        AVLNode* left;
        AVLNode* right;
 
    AVLNode(const ItemType& content)
        {
            item = content;
            left = NULL;
            right = NULL;
            height = 1;
        };
    };
 
 
    void add(const ItemType& item) {
        if (root == NULL)
        {
            AVLNode* temp = new AVLNode(item);
            root = temp;
            size++;
            return;
        }
        else {
            addBelowRoot(root, item);
        }
 
    }
    void addBelowRoot(AVLNode *& n, const ItemType& item)
    {
        if (n == NULL)
        {
            n = new AVLNode(item);
            size++;
        }
        else if (item < n->item)
        {
            addBelowRoot(n->left, item);
        }
        else if(item > n->item)
        {
            addBelowRoot(n->right, item);
        }
        else if (item == n->item)
        {
            return;
        }
        balance (n);
    }
        void remove(const ItemType& item) {
 
            RemoveBelowRoot(root, item);
 
        }
 
         void RemoveBelowRoot(AVLNode *& n, const ItemType& item)
        {
            if (n == NULL)
            {
                return;
            }
            else if(item < n->item)
            {
                RemoveBelowRoot(n->left, item);
 
            }
            else if(item > n->item)
            {
                RemoveBelowRoot(n->right, item);
 
            }
            else if (n->left == NULL)
            {
                AVLNode* temp = n;
                n = n->right;
                delete temp;
                size--;
            }
            else if (n->right == NULL)
            {
                AVLNode* temp = n;
                n = n->left;
                delete temp;
                size--;
 
            }
            else
            {
                n->item = findMin(n->right)->item;
                RemoveBelowRoot(n->right, n->item);
            }
            balance(n);
 
        }
    AVLNode * findMin(AVLNode* n)
    {
        while(n->left != NULL)
        {
            n = n->left;
        }
        return n;
    }
    bool find(const ItemType& item)
    {
        return find(item, root);
    }
    bool find(const ItemType& item, AVLNode* n) {
 
        while (n != NULL)
        {
            if (n->item == item)
            {
                return true;
            }
            if (item > n->item)
            {
                n = n->right;
            }
            else
                n = n->left;
        }
        return false;
 
    }
    void clear()
    {
        while(root != NULL) {
            remove(root->item);
        }
    }
 
 
    void first_time(ofstream& out, int& lvl, int& firsttime, int& printed, int& num, LinkedList<AVLNode*>& MyList)
    {
        firsttime++;
        printed = 0;
        num = MyList.getSize();
        out << "level " << lvl << ": ";
        lvl++;
    }
    void not_first_time(ofstream& out, int& printed, int& num, LinkedList<AVLNode*>& MyList, int& lvl)
    {
        out << "\n";
        printed = 0;
        num = MyList.getSize();
        out << "level " << lvl << ": ";
        lvl++;
    }
    void print_different_than_num(int& printed, AVLNode*& n, LinkedList<AVLNode*>& MyList, ofstream& out, int& num, int& lvl)
    {
        if (printed != 0)
        {
            n = MyList.remove(0);
        }
        out << n->item << "(" << n->height << ") ";
        if (n->left != NULL) {
            MyList.insert(MyList.getSize(), n->left);
        }
        if (n->right != NULL) {
            MyList.insert(MyList.getSize(), n->right);
        }
        printed++;
        if (printed % 8 == 0 && printed != num)
        {
            out << "\nlevel " << lvl-1 << ": ";
        }
    }
    void print (ofstream& out)
    {
        if (root == NULL)
        {
            return;
        }
        else {
            LinkedList<AVLNode *> MyList;
            MyList.add(root);
            int printed = 0;
            int num = 0;
            int lvl = 0;
            int firsttime = 0;
            while (MyList.getSize() > 0)
            {
                if (printed == num)
                {
                    if (firsttime == 0) {
 
                        first_time(out, lvl, firsttime, printed, num, MyList);
                    }
                    else {
 
                        not_first_time(out, printed, num, MyList, lvl);
                    }
                }
                    AVLNode *n = MyList.remove(0);
                    if (n != NULL) {
                        while (printed != num) {
                            print_different_than_num(printed, n, MyList, out, num, lvl);
                        }
                    }
            }
        }
        out << "\n";
    }
 
    void balance (AVLNode *&n)
    {
        if (n == NULL)
        {
            return;
        }
        n->height = setHeight(n);
        if (getHeight(n->left) - getHeight(n->right) > 1)
        {
            balanceToRight(n);
        }
        if (getHeight(n->right) - getHeight(n->left) > 1)
        {
            balanceToLeft(n);
        }
        n->height = setHeight(n);
    }
    int getHeight(AVLNode * n)
    {
        if (n == NULL)
        {
            return 0;
        }
        else
        {
            return n->height;
        }
    }
    void balanceToRight(AVLNode *& n)
    {
        if (getHeight(n->left->right) > getHeight(n->left->left))
        {
            rotateLeft(n->left);
        }
        rotateRight(n);
    }
    void rotateRight(AVLNode *&n)
    {
        AVLNode * k = n->left;
        n->left = k->right;
        k->right = n;
        n->height = setHeight(n);
        n = k;
 
    }
    void rotateLeft(AVLNode *& n)
    {
        AVLNode * k = n->right;
        n->right = k->left;
        k->left = n;
        n->height = setHeight(n);
        n = k;
 
    }
    void balanceToLeft(AVLNode *& n)
    {
        if (getHeight(n->right->left) > getHeight(n->right->right))
        {
            rotateRight(n->right);
        }
            rotateLeft(n);
 
    }
    int setHeight(AVLNode *& n)
    {
        if(n == NULL)
        {
            return 0;
        }
        if (getHeight(n->right) > getHeight(n->left))
        {
            return getHeight(n->right) + 1;
        }
        else
        {
            return getHeight(n->left) + 1;
        }
    }
 
private:
    AVLNode * root;
    int size;
 
};
