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

/********** Linked List **********/
template<class T>
class LinkedList {
private:
    int index;
    T value;
    LinkedList *next;
public:
    LinkedList(int index) {
        this->index = index;
        next = NULL;
        value = NULL;
    }
    LinkedList() {
        index = -1;
        value = NULL;
        next = NULL;
    }
    void insert(int index, T value) {
        LinkedList *current = this;
        LinkedList *previous = NULL;
        LinkedList *node = new LinkedList(index);
        node->value = value;
        while (current != NULL && current->index < index) {
            previous = current;
            current = current->next;
        }
        if (current == NULL) {
            previous->next = node;
        }
        else {
            previous->next = node;
            node->next = current;
        }
        return;
    }
    
    T get(int index) {
        LinkedList *current = this;
        T value = NULL;
        while (current != NULL && current->index != index) {
            current = current->next;
        }
        if (current != NULL) {
            value = current->value;
        }
        else {
            value = NULL;
        }
        return value;
    }
};


/********** SparseArray **********/
template<class T>
class SparseArray {
private:
    LinkedList<T> *start;
    int index;
public:
    SparseArray(int index) {
        start = new LinkedList<T>();
        this->index = index;
    }
    void insert(int index, T value) {
        if (index >= 0 && index < this->index) {
            if (value != NULL)
                start->insert(index, value);
        }
    }
    T get(int index) {
        if (index >= 0 && index < this->index) {
            return start->get(index);
        }
        else {
            return NULL;
        }
    }
};


/********** SparseMatrix **********/
template<class T>
class SparseMatrix {
private:
    int rows, columns;
    SparseArray<T> **sparsearray;
    // set as a 10X10 matrix by default
    int maxRows = 10;
public:
    SparseMatrix() {
        sparsearray = new SparseArray<T>* [maxRows];
        for (int index = 0; index < maxRows; index++) {
            sparsearray[index] = new SparseArray<T>(maxRows);
        }
    }
    void resize() {
        int newSize = maxRows * 2;
        SparseArray<T> **newArr = new SparseArray<T>* [newSize];
        for (int index = 0; index < newSize; index++) {
            sparsearray[index] = new SparseArray<T>(newSize);
        }
        memcpy(newArr, sparsearray, maxRows * sizeof(SparseArray<T>));
        this->maxRows = newSize;
        delete [] sparsearray;
        sparsearray = newArr;
        
    }
    void insert(int rowIndex, int colIndex, T value) {
        if (rowIndex < 0 || rowIndex > rows) {
            cout<<" storing " << rowIndex <<" row index out of bounds " << rows <<endl;
            return;
        }
        if (colIndex < 0 || colIndex > columns) {
            cout<<" storing " << colIndex <<" col index out of bounds"<< columns << endl;
            return;
        }
        sparsearray[rowIndex]->insert(colIndex, value);
    }
    
    T get(int rowIndex, int colIndex) {
        if (rowIndex < 0 || rowIndex > rows) {
            cout<<"getting row index out of bounds"<<endl;
            return 0;
        }
        if (colIndex < 0 || colIndex > columns) {
            cout<<"getting col index out of bounds"<<endl;
            return 0;
        }
        return (sparsearray[rowIndex]->get(colIndex));
    }
    
/*************************** Required methods *************************************/
    void read() {
        cout << "Enter number of rows, columns: " << endl;
        int terms, index;
        T value;
        cin >> this->rows;
        cin >> this->columns;
        while (rows > maxRows) {
            resize();
        }
        for (int i = 0; i < rows; i++) {
            cout << "Enter number of terms in row " << i+1 << endl;
            cin >> terms;
            if (terms != 0) {
                cout << "Enter element's column, and value of each term in row " << i+1 << endl;
            }
            for (int j = 0; j < terms; j++) {
                cin >> index;
                index -= 1;
                cin >> value;
                this->insert(i, index, value);
                
            }
        }
        cout << endl;
    }
    
    void print() {
        int colCount = this->columns;
        int rowCount = this->rows;
        cout << "rows = " << rowCount << " columns = " << colCount << endl;
        for (int i = 0; i < rowCount; i++) {
            cout << "row " << i+1 << "[";
            for (int j = 0; j < colCount; j++) {
                if (this->get(i, j) != NULL) {
                    cout << " col:" << j+1 << " val= " << this->get(i, j) << " ";
                }
            }
            cout << "]" << endl;
        }
        cout << endl;
    }
    
    void mask(SparseMatrix<bool> boolMatrix, SparseMatrix<int> &resultMatrix) {
        resultMatrix.rows = this->rows;
        resultMatrix.columns = this-> columns;
        while (resultMatrix.rows > maxRows) {
            resultMatrix.resize();
        }
        for (int rowIndex = 0; rowIndex < rows; rowIndex++) {
            for (int colIndex = 0; colIndex < columns; colIndex++) {
                T value = get(rowIndex, colIndex);
                if (boolMatrix.get(rowIndex, colIndex) == true) {
                    resultMatrix.insert(rowIndex, colIndex, value);
                }
            }
        }
    }
    
    
};


/********** Main **********/
int main() {
    
    SparseMatrix<int> *a = new SparseMatrix<int>();
    SparseMatrix<bool> *b = new SparseMatrix<bool>();
    SparseMatrix<int> *c = new SparseMatrix<int>();
    
    
    
    cout << "Reading Matrix A" << endl;
    a->read();
    cout << "Matrix A:" << endl;
    a->print();
    cout << "Reading Matrix B" << endl;
    b->read();
    cout << "Matrix B, the boolean mask matrix:" << endl;
    b->print();
    a->mask(*b,*c);
    cout << "Matrix C, result:" << endl;
    c->print();
    
}