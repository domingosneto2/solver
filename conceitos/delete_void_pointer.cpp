

#include <stdio.h>
#include <iostream>

class A
{
    public:
    A()
    {
        cout << "Constructor" << endl;
    }
    
    ~A()
    {
        cout << "Destructor" << endl;
    }    
    
};


void main()
{
    A *a = new A();
    delete a;
    
    void *b = new A();
    delete b;
}
