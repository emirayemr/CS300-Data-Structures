// Emir Ay ( CS 300 - Homework2 )
#ifndef emiray_Ay_Emir_hw2_AVLSearchTree_h
#define emiray_Ay_Emir_hw2_AVLSearchTree_h

#include <string>
using namespace std;

struct DocumentItem {
    string documentName[10];
    int rep_count[10];
};

struct WordItem {
    string word;
    WordItem* left;
    WordItem* right;
    int height;
    DocumentItem doc;
    
    WordItem(const string & w, const DocumentItem & d)
        : word(w), doc(d), left(NULL), right(NULL)
    {}
};

template <class Key, class Value>
class AVLSearchTree {
public:
    explicit AVLSearchTree(const Key & notFound);
    AVLSearchTree(const AVLSearchTree & rhs);
    ~AVLSearchTree();
    
    const Key & findMin() const;
    const Key & findMax() const;
    const Key & find (Key & x, const int & i, bool & b) const;
    const Key & findAndPrint (Key & x, const int & i) const;
    
    bool isEmpty() const;
    void printTree() const;
    
    void makeEmpty();
    void insert (Key & x, string & d, const int & no, const int & i);
    void remove (const Key & x);
    
    const AVLSearchTree & operator = (const AVLSearchTree & rhs);
    
private:
    Value* root;
    Key ITEM_NOT_FOUND;
    
    const Key & elementAt (Value* t) const;
    
    void insert (Key & x, const string & d, Value* & t, const int & no, const int & i) const;
    void remove (const Key & x, const Value* & t) const;
    
    Value * findMin (Value * t) const;
    Value * findMax (Value * t) const;
    Value * find (Key & x, Value * t, const int & i, bool & b) const;
    Value * findAndPrint (Key & x, Value * t, const int & i) const;
    
    void makeEmpty(Value* & t) const;
    void printTree(Value* t) const;
    Value * clone (Value * t) const;
    
    int height(Value* t) const;
    int max(int lhs, int rhs) const;
    void rotateWithLeftChild(Value * & k2) const;
    void rotateWithRightChild(Value * & k1) const;
    void doubleWithLeftChild(Value * & k3) const;
    void doubleWithRightChild(Value * & k1) const;
};

#include "emiray_Ay_Emir_hw2_AVLSearchTree.cpp"

#endif
