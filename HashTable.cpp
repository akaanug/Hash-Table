/**
* Author: Ahmet Kaan Uğuralp
*/

#include "HashTable.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

HashTable::HashTable(const int tableSize, const HashTable::CollisionStrategy option) {
    this->tableSize = tableSize;
    items = new HashNode[tableSize];
    this->option = option;

}

HashTable::~HashTable() {

    delete [] items;

}

static string intToString( int i ) {
    stringstream convert;
    convert << i;
    return convert.str();
}

static int stringToInt(string s) {
    stringstream convert(s);
    int number = 0;
    convert >> number;
    return number;
}

static int reverse( int key ) {

    string s;
    string reversed = "";
    s = intToString(key);

    for( int i = 0; i < s.length(); i++ ) {
        reversed = s.at(i) + reversed;
    }

    return stringToInt(reversed);
}

int HashTable::f( const int i, const int key ) {

    switch(option) {

        case LINEAR: { // f(i) = i
            return i;
        }

        case QUADRATIC: { // f(i) = i^2
            return i * i;
        }

        case DOUBLE: { // f(i) = i * reverse(key)
            return i * reverse(key);
        }

    }

}

int HashTable::hash(int key) {
    return key % tableSize;
}

bool HashTable::insert(const int item) {

    int key = hash(item);
    bool foundSpot = false;
    int count = 0; //to stop infinite loops

    while( !foundSpot && count <= tableSize ) {
        if( items[key].isEmpty() ) {
            items[key].setNode(item, key);
            foundSpot = true;
            numOfItems++;
            cout << item << " inserted" << endl;
            return true;
        } else {
            if( items[key].getValue() == item ) { //prevent insertion with same key
                cout << item << " not inserted" << endl;
                return false;
            }

            count++;
            key = ( hash(item) + f(count, key) ) % tableSize; //update key h_i(key) = 􏰀( hash(key) + f(i)􏰁 ) mod tableSize

        }
    }

    cout << item << " not inserted" << endl;
    return false;

}

bool HashTable::remove(const int item) {

    int key = hash(item);
    bool foundItem = false;
    int count = 0;

    while( !foundItem && (count <= tableSize) ) {

        if( !items[key].isDeleted() && items[key].isEmpty() ) { //if search location is empty
            cout << item << " not removed" << endl;
            return false;
        } else {
            if( items[key].getValue() == item ) { //prevent insertion with same key
                items[key].deleteNode();
                numOfItems--;
                cout << item << " removed" << endl;
                return true;
            } else {
                count++;
                key = ( hash(item) + f(count, key) ) % tableSize; //update key h_i(key) = 􏰀( hash(key) + f(i)􏰁 ) mod tableSize
            }
        }

    }

    cout << item << " not removed" << endl;
    return false;

}

void HashTable::display() {
    for( int i = 0; i < tableSize; i++ ) {

        cout << i << ": ";
        if( !items[i].isEmpty() ) {
            cout << items[i].getValue();
        }

        cout << endl;

    }
}

bool HashTable::search(const int item, int &numProbes) {

    numProbes = 0;
    int key = hash(item);
    bool foundItem = false;
    int count = 0;

    while( !foundItem && (count <= tableSize) ) {
        numProbes++;
        if( !items[key].isDeleted() && items[key].isEmpty() ) { //if search location is empty
            cout << item << " not found after " << numProbes << " probes" << endl;
            return false;
        } else {
            if( items[key].getValue() == item ) { //prevent insertion with same key
                cout << item << " found after " << numProbes << " probes" << endl;
                return true;
            } else {
                count++;
                key = ( hash(item) + f(count, key) ) % tableSize; //update key h_i(key) = 􏰀( hash(key) + f(i)􏰁 ) mod tableSize
            }
        }

    }

    cout << item << " not found after " << numProbes << " probes" << endl;
    return false;

}

void HashTable::countUnsucc( const int index, int &numUnsuccProbes ) {

    int key = hash(index);
    bool foundSpot = false;
    int count = 0; //to stop infinite loops

    while( !foundSpot && count <= tableSize ) {
        numUnsuccProbes++;
        if( items[key].isEmpty() ) {
            return;
        } else {
            count++;
            key = ( hash(index) + f(count, key) ) % tableSize; //update key h_i(key) = 􏰀( hash(key) + f(i)􏰁 ) mod tableSize
        }
    }

}

void HashTable::countSucc(const int index, int &numSuccProbes) { //copy of search without outputs

    int key = hash(index);
    bool foundItem = false;
    int count = 0;

    while( !foundItem && (count <= tableSize) ) {
        numSuccProbes++;
        if( !items[key].isDeleted() && items[key].isEmpty() ) { //if search location is empty
            return;
        } else {
            if( items[key].getValue() == index ) { //prevent insertion with same key
                return;
            } else {
                count++;
                key = ( hash(index) + f(count, key) ) % tableSize; //update key h_i(key) = 􏰀( hash(key) + f(i)􏰁 ) mod tableSize
            }
        }

    }

    return;

}

void HashTable::analyze(int &numSuccProbes, int &numUnsuccProbes) {
    numSuccProbes = 0;
    numUnsuccProbes = 0;
    if(option == DOUBLE) { //only analyze numSuccProbes
        numUnsuccProbes = -1;
        for( int i = 0; i < tableSize; i++ ) {
            if( !items[i].isEmpty() ) {
                countSucc(items[i].getValue(), numSuccProbes ); //count succesful probes
            }
        }
        return;
    } else {
        for( int i = 0; i < tableSize; i++ ) {
            if( !items[i].isEmpty() ) {
                countSucc(items[i].getValue(), numSuccProbes ); //count succesful probes
            }
            countUnsucc(i, numUnsuccProbes); //count unsuccesful probes
        }
    }
}

void extractInts( string s, int arr[] ) {

    stringstream ss;
    ss << s;
    string curr;
    int res;
    int count = 0;

    while(!ss.eof()) {

        ss >> curr;

        if( stringstream(curr) >> res ) {
            arr[count] = res;
            count++;
        }

        curr = " ";
    }

}

void HashTable::simulateFromFile(string file) {

    ifstream inFile;
    inFile.open(file.c_str());

    string line;
    int line_count = 0;

    while( getline(inFile, line) ) {

        stringstream ss(line);
        string value;
        getline(ss, value );

        int probes = 0;
        int num[1];
        string instruction;
        extractInts(value, num);
        instruction = value.at(0);

        if( instruction == "I" ) {
            insert(num[0]);
        } else if( instruction == "R" ) {
            remove(num[0]);
        } else if( instruction == "S" ) {
            search(num[0], probes);
        }

    }

}
