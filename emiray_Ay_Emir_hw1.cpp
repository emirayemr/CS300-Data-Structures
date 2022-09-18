/* Emir Ay ( CS 300 - Homework1 )
   I used mostly xCode for this homework
 */
#include <iostream>
#include <string>
#include <fstream>
#include "emiray_Ay_Emir_hw1_Stack.h"
using namespace std;

void getInput(ifstream &input)
{
    do
    {
        string fileName;
        cout << "Please enter the file name: ";
        cin >> fileName; /* get file name */
        input.open(fileName.c_str());
        if (input.fail())
            cout << "File not found." << endl;
    } while(input.fail()); // if fail do it again
}

bool isTraveled(Stack<int> &x_stack, Stack<int> &y_stack, int x_goal, int y_goal)
{
    bool check = false; // to check if the point is visited
    Stack<int> x_hold, y_hold; // to push back if the point is not visited before
    
    if (x_stack.top() >= x_goal && y_stack.top() >= y_goal)
    {
        int count = 0; // counts how many times the stack is popped
        
        while (y_stack.top() != y_goal)
        {
            y_hold.push(y_stack.top());
            y_stack.pop();
            count++;
        }
        for (int i=0; i < count; i++)
        {
            x_hold.push(x_stack.top());
            x_stack.pop();
        }

        if (x_stack.top() == x_goal && y_stack.top() == y_goal) // true if the point is visited
        {
            x_stack.pop();
            y_stack.pop();
            check = true;
        }
        else { // Push back all coordiantes since the point is not visited
            int count_x = 0;
            while (x_stack.top() != x_goal)
            {
                x_hold.push(x_stack.top());
                x_stack.pop();
                count_x++;
            }
            for (int i=0; i < count_x; i++)
            {
                y_hold.push(y_stack.top());
                y_stack.pop();
            }
            
            if (x_stack.top() == x_goal && y_stack.top() == y_goal) // true if the point is visited
                check = true;
            else {
                while (! x_hold.isEmpty())
                {
                    x_stack.push(x_hold.top());
                    x_hold.pop();
                }
                while (! y_hold.isEmpty())
                {
                    y_stack.push(y_hold.top());
                    y_hold.pop();
                }
            }
        }
    }
    return check;
}

void backToZero (Stack<int> x_stack, Stack<int> y_stack)
{
    cout << "Back to (0,0)\n";
    while (! x_stack.isEmpty())
    {
        if ( ! (x_stack.top() == 0 && y_stack.top() == 0)) // to prevent printing (0,0)
            cout << x_stack.top() << "," << y_stack.top() << endl;
        x_stack.pop();
        y_stack.pop();
    }
    cout << "Home sweet home\n";
}

int main() {
    ifstream input;
    getInput(input);
    
    Stack<int> x_stack;
    Stack<int> y_stack;
    
    int x=0, y=0;
    int x_goal, y_goal;
    while (input >> x_goal >> y_goal)
    {
        if (isTraveled(x_stack, y_stack, x_goal, y_goal))
        {
            cout << "Time travel back to (" << x_goal << "," << y_goal << ")\n";
            x = x_goal;
            y = y_goal;
        }
        else {
            int count = 0;
            cout << "Moving to (" << x_goal << "," << y_goal << ")\n";
            if (x_goal >= x)
            {
                for (; x < x_goal; x++)
                {
                    x_stack.push(x);
                    y_stack.push(y);
                    if (count != 0) // to prevent printing starting points
                        cout << "(" << x << "," << y << ")\n";
                    count++;
                }
            }
            else {
                for (; x > x_goal; x--)
                {
                    x_stack.push(x);
                    y_stack.push(y);
                    if (count != 0) // to prevent printing starting points
                        cout << "(" << x << "," << y << ")\n";
                    count++;
                }
            }
            if (y_goal >= y)
            {
                for (; y < y_goal; y++)
                {
                    x_stack.push(x);
                    y_stack.push(y);
                    if (count != 0) // to prevent printing starting points
                        cout << "(" << x << "," << y << ")\n";
                    count++;
                }
            }
            else
            {
                for (; y > y_goal; y--)
                {
                    x_stack.push(x);
                    y_stack.push(y);
                    if (count != 0) // to prevent printing starting points
                        cout << "(" << x << "," << y << ")\n";
                    count++;
                }
            }

            cout << "Arrived to (" << x << "," << y << ")\n";
        }
    }
    
    backToZero(x_stack, y_stack);
    
    return 0;
}
