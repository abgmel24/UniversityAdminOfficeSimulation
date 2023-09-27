#ifndef CONFIG_H
#define CONFIG_H

#include "TListQueue.h"
#include "TDoublyLinkedList.h"
#include "Customer.h"
#include <fstream>
#include <exception>

using namespace std;

using namespace std;

class Configuration {
    public:
        Configuration(string fileName);
        ~Configuration();

        void printOutputs();

        unsigned int currentTick;

        unsigned int numRegistrars;
        unsigned int numCashiers;
        unsigned int numFinAids;
        unsigned int startingTick;
        unsigned int numCustomersPerTick;

        TListQueue<Customer*> *students;
        TListQueue<Customer*> *exit;

        double meanWaitTimes[3]; //calculated at the end
        unsigned int maxWaitTimes[3]; //calculated in real time
        unsigned int longWaits; //calculated in real time

        double meanIdleTimes[3]; //calculated at the end
        unsigned int maxIdleTimes[3]; //calculated at the end
        unsigned int longIdles; //calculated at the end

        void printBool(bool b);

    private:
        void constructCustomer(string s, int tick);
};

#endif