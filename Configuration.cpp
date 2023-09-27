#include "Configuration.h"

Configuration::Configuration(string fileName) {
    students = new TListQueue<Customer*>();
    exit = new TListQueue<Customer*>();

    //cout << "entry and exit created" << endl;

    ifstream inFS;
    string curr;
    inFS.open(fileName);

    if(!inFS.is_open()) {
        throw runtime_error("Could not open file");
    }

    getline(inFS, curr);
    numRegistrars = stoi(curr);
    getline(inFS, curr);
    numCashiers = stoi(curr);
    getline(inFS, curr);
    numFinAids = stoi(curr);
    // getline(inFS, curr);
    // startingTick = stoi(curr);
    // getline(inFS, curr);
    // numCustomersPerTick = stoi(curr);

    // //cout << "initial config done" << endl;

    // while(!inFS.eof()) {
    //     for(int i = 0; i < numCustomersPerTick; ++i) {
    //         getline(inFS, curr);
    //         constructCustomer(curr, startingTick);
    //         //cout << i << endl;
    //     }
    //     getline(inFS, curr);
    //     startingTick = stoi(curr);
    //     getline(inFS, curr);
    //     numCustomersPerTick = stoi(curr);
    // }

    do {
        getline(inFS, curr);
        startingTick = stoi(curr);
        getline(inFS, curr);
        numCustomersPerTick = stoi(curr);
        for(int i = 0; i < numCustomersPerTick; ++i) {
            getline(inFS, curr);
            constructCustomer(curr, startingTick);
            //cout << i << endl;
        }
    } while(!inFS.eof());

    inFS.close();
    cout << "closed file stream" << endl;

    startingTick = students->peek()->getArrivalTick();
    currentTick = startingTick;

    longWaits = 0; 
    longIdles = 0;
    for(int i = 0; i < 3; ++i) {
        meanIdleTimes[i] = 0.0;
        meanWaitTimes[i] = 0.0;
    }
}

void Configuration::printOutputs() {
    cout << "Cashier's Office:" << endl;
    cout << "Mean student wait time: " << meanWaitTimes[1] << " ticks" << endl;
    cout << "Mean window idle time: " << meanIdleTimes[1] << " ticks" << endl;
    cout << "Longest student wait time: " << maxWaitTimes[1] << " ticks" << endl;
    cout << "Longest window idle time: " << maxIdleTimes[1] << " ticks" << endl << endl;

    cout << "Financial Aid Office:" << endl;
    cout << "Mean student wait time: " << meanWaitTimes[2] << " ticks" << endl;
    cout << "Mean window idle time: " << meanIdleTimes[2] << " ticks" << endl;
    cout << "Longest student wait time: " << maxWaitTimes[2] << " ticks" << endl;
    cout << "Longest window idle time: " << maxIdleTimes[2] << " ticks" << endl << endl;

    cout << "Registrar's Office: " << endl;
    cout << "Mean student wait time: " << meanWaitTimes[0] << " ticks" << endl;
    cout << "Mean window idle time: " << meanIdleTimes[0] << " ticks" << endl;
    cout << "Longest student wait time: " << maxWaitTimes[0] << " ticks" << endl;
    cout << "Longest window idle time: " << maxIdleTimes[0] << " ticks" << endl << endl;

    // for(int i = 0; i < exit->size(); ++i) {
    //     if(exit->pop()->getTotalWaitTime() > 10) {
    //         longWaits++;
    //     }
    // } 
    cout << "Number of students waiting for over 10 minutes total across all offices: " << longWaits << endl;    
    cout << "Number of windows idle for over 5 minutes across all offices: " << longIdles << endl << endl;


}

Configuration::~Configuration() {
    delete students;
    delete exit;
}

void Configuration::constructCustomer(string s, int tick) {
    int* timeSpent = new int[3];
    char* order = new char[3];

    //use time array
    string temp;
    int i = 0;
    int x = 0;
    while(x < 3) {
        if(s[i] == ' ') {
            timeSpent[x] = stoi(temp);
            x++;
            s = s.substr(++i);
            i = 0;         
        } else {
            i++;
            temp = s.substr(0, i);
        }
    }

    //office order
    x = 0;
    while(x < 3) {
        if(s[i] == '\0') {
            order[x] = temp[0];
            break;
        }
        if(s[i] == ' ') {
            order[x++] = temp[0];
            s = s.substr(++i);
            i = 0;
        } else {
            temp = s.substr(0, ++i);
        }
    }

    this->students->push(new Customer(tick, order, timeSpent));
}

void Configuration::printBool(bool b) {
    if(b) {
        cout << "true";
    } else {
        cout << "false";
    }
}