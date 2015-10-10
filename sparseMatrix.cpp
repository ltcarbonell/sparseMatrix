//
//  sparseMatrix.cpp
//  sparseMatrix
//
//  Created by Luis Carbonell on 10/7/15.
//  Copyright © 2015 LT Carbonell. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/* Linked List Declaration */

template<class T>
class LinkedList
{
private:
    int index;
    T value;
    LinkedList *nextindex;
public:
    LinkedList(int index)
    {
        this->index = index;
        nextindex = NULL;
        value = NULL;
    }
    LinkedList()
    {
        index = -1;
        value = NULL;
        nextindex = NULL;
    }
    void store(int index, T value)
    {
        LinkedList *current = this;
        LinkedList *previous = NULL;
        LinkedList *node = new LinkedList(index);
        node->value = value;
        while (current != NULL && current->index < index)
        {
            previous = current;
            current = current->nextindex;
        }
        if (current == NULL)
        {
            previous->nextindex = node;
        }
        else
        {
            if (current->index == index)
            {
                cout<<"DUPLICATE INDEX"<<endl;
                return;
            }
            previous->nextindex = node;
            node->nextindex = current;
        }
        return;
    }
    
    T fetch(int index)
    {
        LinkedList *current = this;
        int value = NULL;
        while (current != NULL && current->index != index)
        {
            current = current->nextindex;
        }
        if (current != NULL)
        {
            value = current->value;
        }
        else
        {
            value = NULL;
        }
        return value;
    }
    
    int elementCount()
    {
        int elementCount = 0;
        LinkedList *current = this->nextindex;
        for ( ; (current != NULL); current = current->nextindex)
        {
            elementCount++;
        }
        return elementCount;
    }
};
/*
 * Class SpareArray Declaration
 */
template<class T>
class SparseArray
{
private:
    LinkedList<T> *start;
    int index;
public:
    SparseArray(int index)
    {
        start = new LinkedList<T>();
        this->index = index;
    }
    void store(int index, T value)
    {
        if (index >= 0 && index < this->index)
        {
            if (value != NULL)
                start->store(index, value);
        }
        else
        {
            cout<<"INDEX OUT OF BOUNDS"<<endl;
        }
    }
    T fetch(int index)
    {
        if (index >= 0 && index < this->index)
            return start->fetch(index);
        else
        {
            cout<<"INDEX OUT OF BOUNDS"<<endl;
            return NULL;
        }
    }
    int elementCount()
    {
        return start->elementCount();
    }
};

/*
 * Class SparseMatrix Declaration
 */
template<class T>
class SparseMatrix
{
private:
    int N;
    SparseArray<T> **sparsearray;
public:
    SparseMatrix(int N)
    {
        this->N = N;
        sparsearray = new SparseArray<T>* [N];
        for (int index = 0; index < N; index++)
        {
            sparsearray[index] = new SparseArray<T>(N);
        }
    }
    void store(int rowindex, int colindex, int value)
    {
        if (rowindex < 0 || rowindex > N)
        {
            cout<<"row index out of bounds"<<endl;
            return;
        }
        if (colindex < 0 || colindex > N)
        {
            cout<<"col index out of bounds"<<endl;
            return;
        }
        sparsearray[rowindex]->store(colindex, value);
    }
    
    int get(int rowindex, int colindex)
    {
        if (rowindex < 0 || colindex > N)
        {
            cout<<"row index out of bounds"<<endl;
            return 0;
        }
        if (rowindex < 0 || colindex > N)
        {
            cout<<"col index out of bounds"<<endl;
            return 0;
        }
        return (sparsearray[rowindex]->fetch(colindex));
    }
    int elementCount()
    {
        int count = 0;
        for (int index = 0; index < N; index++)
        {
            count += sparsearray[index]->elementCount();
        }
        return count;
    }
};
/*
 * Main
 */
int main()
{
    bool iarray[3][3];
    iarray[0][0] = true;
    iarray[0][1] = NULL;
    iarray[0][2] = true;
    iarray[1][0] = NULL;
    iarray[1][1] = false;
    iarray[1][2] = NULL;
    iarray[2][0] = true;
    iarray[2][1] = true;
    iarray[2][2] = NULL;
    SparseMatrix<bool> *sparseMatrix = new SparseMatrix<bool>(3);
    for (int rowindex = 0; rowindex < 3; rowindex++)
    {
        for (int colindex = 0; colindex < 3; colindex++)
        {
            sparseMatrix->store(rowindex, colindex, iarray[rowindex][colindex]);
        }
    }
    
    cout<<"the sparse Matrix is: "<<endl;
    for (int rowindex = 0; rowindex < 3; rowindex++)
    {
        for (int colindex = 0; colindex < 3; colindex++)
        {
            if (sparseMatrix->get(rowindex, colindex) == NULL)
                cout<<"NULL"<< "\t";
            else
                cout<<sparseMatrix->get(rowindex, colindex) << "\t";
        }
        cout<<endl;
    }
    cout<<"The Size of Sparse Matrix is "<<sparseMatrix->elementCount()<<endl;
    
}