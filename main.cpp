/**
* Author: Ahmet Kaan Uğuralp
*/

#include "HashTable.h"

#include <iostream>
#include <sstream>

using namespace std;

static int stringToInt(string s) {

    stringstream convert(s);
    int number = 0;
    convert >> number;
    return number;
}

int main(int argc, char *argv[]) {

    if(argc != 4) {
        cout << "Enter ./<simulatorName> <fileName> <collisionStrategy> <tableSize> " << endl;
        return 0;
    }

    string fileName = argv[1];
    HashTable::CollisionStrategy strategy;
    string str = argv[2];
    int tableSize = stringToInt(argv[3]);

    if( str == "LINEAR" ) {
        strategy = HashTable::LINEAR;
    } else if( str == "QUADRATIC" ) {
        strategy = HashTable::QUADRATIC;
    } else if( str == "DOUBLE" ) {
        strategy = HashTable::DOUBLE;
    }

    HashTable * h = new HashTable(tableSize, strategy);
    h->simulateFromFile(fileName);

    int suc, unsuc;

    h->display();

    h->analyze(suc, unsuc);
    cout << "Successful Probes: " << suc << " | Avg. no of probes: " << (double)suc / h->getNumOfItems() << endl;

    if( unsuc != -1 ) {
        cout << "Unuccessful Probes: " << unsuc << " | Avg. no of probes: " << (double)unsuc / tableSize << endl;
    }



    delete h;

    return 0;
}
