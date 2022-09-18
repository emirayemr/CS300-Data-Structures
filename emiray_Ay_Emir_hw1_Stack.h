// Emir Ay ( CS 300 - Homework1 )
#ifndef Emiray_Ay_Emir_Hw1_Stack_h
#define Emiray_Ay_Emir_Hw1_Stack_h

template <class Type>
class Stack {
    private:
        struct node {
            Type data;
            node* next;
            
            node(const Type& d, node* n = NULL)
            : data(d), next(n) {}
        };
    
        node* topOfStack;
    
    public:
        Stack();
        void push (const Type & coor);
        void pop();
        Type top() const;
        bool isEmpty() const;
        
        const static Type noItem = 0;
};

#include "emiray_Ay_Emir_hw1_Stack.cpp"

#endif
