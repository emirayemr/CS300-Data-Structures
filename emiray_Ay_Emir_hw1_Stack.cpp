// Emir Ay ( CS 300 - Homework1 )
#include <iostream>
#include "emiray_Ay_Emir_hw1_Stack.h"
using namespace std;

template<class Type>
Stack<Type>::Stack() {
    topOfStack = NULL;
}

template<class Type>
void Stack<Type>::push(const Type & coor) {
    topOfStack = new node(coor, topOfStack);
}

template<class Type>
void Stack<Type>::pop() {
    node* oldTop = topOfStack;
    topOfStack = topOfStack->next;
    delete oldTop;
}

template<class Type>
bool Stack<Type>::isEmpty() const {
    return topOfStack == NULL;
}

template<class Type>
Type Stack<Type>::top() const {
    if (isEmpty())
        return noItem;
    return topOfStack->data;
}
