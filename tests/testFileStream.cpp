#include <iostream>
#include <fstream>

using namespace std;

int main(int arc, char **argv) {
    unsigned int currentTick;
    unsigned int numRegistrars;
    unsigned int numCashiers;
    unsigned int numFinAids;
    unsigned int startingTick;
    unsigned int numCustomersPerTick;

    ifstream inFS;
    string curr;
    inFS.open("input.txt");

    if(!inFS.is_open()) {
        throw runtime_error("Could not open file");
    }

    getline(inFS, curr);
    numRegistrars = stoi(curr);
    getline(inFS, curr);
    numCashiers = stoi(curr);
    getline(inFS, curr);
    numFinAids = stoi(curr);
    getline(inFS, curr);
    startingTick = stoi(curr);
    getline(inFS, curr);
    numCustomersPerTick = stoi(curr);

    while(!inFS.eof()) {
        cout << "startingTick: " << startingTick << endl;
        cout << "numCustomersPerTick: " << numCustomersPerTick << endl;
        for(int i = 0; i < numCustomersPerTick; ++i) {
            getline(inFS, curr);
            //constructCustomer(curr, startingTick);
        }
        getline(inFS, curr);
        startingTick = stoi(curr);
        getline(inFS, curr);
        numCustomersPerTick = stoi(curr);
    }

    //startingTick = students->peek()->getArrivalTick();
    currentTick = startingTick;

    inFS.close();

    cout << "registrars: " << numRegistrars << endl;
    cout << "cashiers: " << numCashiers << endl;
    cout << "finaids: " << numFinAids << endl;
    //cout << "startingTick: " << startingTick << endl;

}