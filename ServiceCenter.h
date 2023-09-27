#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include "Configuration.h"
#include "Office.h"

class ServiceCenter {
    public:
        ServiceCenter();
        ServiceCenter(int numRegistrars, int numCashiers, int numFinAids, unsigned int tick);
        ServiceCenter(Configuration *c);
        ~ServiceCenter();

        void service();

        //helper functions
        void sendBack(Office *o);
        int findUseTime(char c, Customer *s);

        Office* getRegistrar();
        Office* getCashier();
        Office* getFinAid();
    private:
        Configuration *config;

        Office* registrar;
        Office* cashier;
        Office* finaid;

        TDoublyLinkedList<Customer*> *inCenter;

        //unsigned int currentTick;

        Office* findOffice(char c);
        bool officesAreEmpty();
};

#endif