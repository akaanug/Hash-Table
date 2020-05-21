/**
* Author: Ahmet Kaan Uğuralp
*/

#ifndef CS202_HW4_HASHTABLE_H
#define CS202_HW4_HASHTABLE_H

#include <string>
using namespace std;

class HashNode {

public:
    HashNode( ) {
        this->key = -1;
        this->value = -1;
        this->empty = true;
        this->deleted = false;
    }

    void setNode( int value, int key ) {
        this->key = key;
        this->value = value;
        empty = false;
    }

    void deleteNode() {
        this->key = -1;
        this->value = -1;
        this->empty = true;
        this->deleted = true;
    }

    int getKey() {
        return key;
    }

    int getValue() {
        return value;
    }

    bool isEmpty() {
        return empty;
    }

    bool isDeleted() {
        return deleted;
    }

private:
    int key;
    int value;
    bool empty;
    bool deleted;

};

class HashTable {

public:
    enum CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };
    HashTable( const int tableSize, const CollisionStrategy option );
    ~HashTable();
    bool insert( const int item );
    bool remove( const int item );
    int f( const int i, const int key );
    int hash( int key );
    void display();
    bool search( const int item, int & numProbes );
    int getNumOfItems() { return numOfItems; }
    void analyze( int & numSuccProbes, int & numUnsuccProbes );
    void countUnsucc( const int index, int & numUnsuccProbes );
    void countSucc( const int index, int & numUnsuccProbes );
    void simulateFromFile( string file );

private:
    HashNode * items;
    int numOfItems;
    int tableSize;
    CollisionStrategy option;

};


#endif //CS202_HW4_HASHTABLE_H
