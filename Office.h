#ifndef OFFICE_H
#define OFFICE_H

#include "Configuration.h"
#include "Window.h"

using namespace std;

class Office {
    public:
        Office();
        Office(string type, unsigned int numWindows);
        Office(string type, unsigned int numWindows, Configuration *c);

        bool serviceStudent(Customer *c);
        void holdStudent(Customer *c);

        void processQueue();
        void calculateOutputs();

        TListQueue<Customer*>* getCenterGoers();
        TListQueue<Customer*>* getOfficeQueue();
        string getType();
        unsigned int getNumWindows();

        int getIndexForType();

        void displayOfficeState();
        void moveStudent(Customer* current, int i);

        bool officeIsEmpty();

        void printIdles();

    private:
        string type;
        unsigned int numWindows;
        Window** windows;

        TListQueue<Customer*> *officeQueue;
        TListQueue<Customer*> *toCenter;

        Configuration *config;

        double totalWaitTime;
        unsigned int numStudents;

};

#endif