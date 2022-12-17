// Emir Ay ( CS 300 - Homework2 )
#include <iostream>
#include <string>
#include "emiray_Ay_Emir_hw2_AVLSearchTree.h"
using namespace std;

template <class Key, class Value>
AVLSearchTree<Key, Value>::AVLSearchTree (const Key& notFound):
    ITEM_NOT_FOUND( notFound ), root( NULL )
{}

template <class Key, class Value>
AVLSearchTree<Key, Value>:: AVLSearchTree(const AVLSearchTree<Key, Value> & rhs):
    ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), root( NULL )
{
    *this = rhs;
}

template <class Key, class Value>
void deleteNonAlpha (Key & x)
{
    for (int i=0; i < x.length(); i++)
    {
        if (65 <= x[i] && x[i] <= 90)
            x[i] += 32;
        else if (! (97 <= x[i] && x[i] <= 122))
            x = x.substr(0,i)+x.substr(i+1);
    }
}

template <class Key, class Value>
bool isWordSame (Key & x, Value* & t)
{
    int count = 0;
    if (x.length() == t->word.length())
    {
        for (int i=0; i < x.length(); i++)
        {
            if (x[i] == t->word[i])
                count++;
        }
    }
    
    if (count == x.length())
        return true;
        
    return false;
}

template <class Key, class Value>
bool isAlphaSmaller (Key & x, Value* & t)
{
    int len;
    x.length() <= t->word.length() ? len = x.length() : len = t->word.length();
    int count = 0;
    bool check = false;
    for (int i=0; count == 0 && i < len; i++)
    {
        if (x[i] < t->word[i])
        {
            check = true;
            count ++;
        }
        else if (x[i] > t->word[i])
            count++;
    }
    return check;
}

template <class Key, class Value>
const Key & AVLSearchTree<Key, Value>::elementAt(Value * t) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->word;
}

template <class Key, class Value>
const Key & AVLSearchTree<Key, Value>::find (Key & x, const int & i, bool & b) const
{
    deleteNonAlpha<string, WordItem>(x);
    return elementAt(find(x, root, i, b));
}

template <class Key, class Value>
Value * AVLSearchTree<Key, Value>::find(Key & x, Value * t, const int & i, bool & b) const
{
    if (t == NULL)
    {
        b = false;
        return NULL;
    }
    else if (isWordSame(x, t))
        return t;
    else if (isAlphaSmaller(x, t))
        return find(x, t->left, i, b);
    else
        return find(x, t->right, i, b);
}

template <class Key, class Value>
const Key & AVLSearchTree<Key, Value>::findAndPrint (Key & x, const int & i) const
{
    deleteNonAlpha<string, WordItem>(x);
    return elementAt(findAndPrint(x, root, i));
}

template <class Key, class Value>
Value * AVLSearchTree<Key, Value>::findAndPrint(Key & x, Value * t, const int & i) const
{
    if (t == NULL)
        return NULL;
    else if (isWordSame(x, t))
    {
        cout << x << " found " <<  t->doc.rep_count[i] << " times";
        return t;
    }
    else if (isAlphaSmaller(x, t))
        return findAndPrint(x, t->left, i);
    else
        return findAndPrint(x, t->right, i);
}

template <class Key, class Value>
Value * AVLSearchTree<Key, Value>::findMin(Value * t) const
{
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return findMin(t->left);
}

template <class Key, class Value>
const Key & AVLSearchTree<Key, Value>::findMin() const
{
    return elementAt (findMin(root));
}

template <class Key, class Value>
Value * AVLSearchTree<Key, Value>::findMax(Value * t) const
{
    if (t == NULL)
        return NULL;
    if (t->right == NULL)
        return t;
    return findMin(t->right);
}

template <class Key, class Value>
const Key & AVLSearchTree<Key, Value>::findMax() const
{
    return elementAt (findMax(root));
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::insert (Key & x, string & d, const int & no, const int & i)
{
    deleteNonAlpha<string, WordItem>(x);
    insert (x, d, root, no, i);
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::insert(Key & x, const string & d, Value* & t, const int & no, const int & i) const
{
    if (t==NULL)
    {
        DocumentItem doc;
        t = new WordItem(x, doc);
        for (int j=0; j < 10; j++)
            t->doc.rep_count[j] = 0;
        t->doc.rep_count[i] = 1;
            
    }
    else if (! isWordSame(x, t))
    {
        if (isAlphaSmaller(x, t)) {
            insert(x, d, t->left, no, i);
            
            if (height(t->left) - height(t->right) == 2)
            {
                if (isAlphaSmaller(x, t->left))
                    rotateWithLeftChild(t);
                else
                    doubleWithLeftChild(t);
            }
        }
        else
        {
            insert(x, d, t->right, no, i);
            if (height(t->right) - height(t->left) == 2)
            {
                if (! isAlphaSmaller(x, t->right))
                    rotateWithRightChild(t);
                else
                    doubleWithRightChild(t);
            }
        }
    }
    else // there is a word at t, and t->word = x (words are same)
    {
        
        t->doc.rep_count[i] ++;
    }
    t->height = max(height(t->left), height(t->right)) + 1;
    t->doc.documentName[i] = d;
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::remove (const Key & x)
{
    remove(x, root);
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::remove (const Key & x, const Value* & t) const
{
    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left != NULL && t->right != NULL)
    {
        t->word = findMin(t->right)->word;
        remove(t->word, t->right);
    }
    else
    {
        WordItem* temp = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete temp;
    }

    if (height(t->left) - height(t->right) > 1)
    {
        if (height(t->left->left) < height(t->left->right))
            doubleWithLeftChild(t);
        else
            rotateWithLeftChild(t);
    }

    else
    {
        if (height(t->right) - height(t->left) > 1)
        {
            if (height(t->right->right) < height(t->right->left))
                doubleWithRightChild(t);
            else
                rotateWithRightChild(t);
        }
    }

    t->height = max(height(t->left), height(t->right)) + 1;
}

template <class Key, class Value>
Value* AVLSearchTree<Key, Value>::clone(Value* t) const
{
    if (t == NULL)
        return NULL;
    else
        return new WordItem(t->word, t->doc);
}


template <class Key, class Value>
void AVLSearchTree<Key, Value>::rotateWithLeftChild(Value * & k2) const
{
    WordItem * k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::rotateWithRightChild(Value * & k1) const
{
    WordItem* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) +1;
    k1 = k2;
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::doubleWithLeftChild(Value * & k3) const
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::doubleWithRightChild(Value * & k1) const
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::makeEmpty()
{
    makeEmpty(root);
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::makeEmpty(Value * & t) const
{
    if (t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = NULL;
}

template <class Key, class Value>
int AVLSearchTree<Key, Value>::height(Value * t) const
{
    if (t == NULL)
        return -1;
    
    return t->height;
}

template <class Key, class Value>
int AVLSearchTree<Key, Value>::max(int lhs, int rhs) const
{
    if (lhs > rhs)
        return lhs;
    
    return rhs;
}

template <class Key, class Value>
AVLSearchTree<Key, Value>::~AVLSearchTree()
{
    makeEmpty();
}
