#include "ServiceCenter.h"

ServiceCenter::ServiceCenter() {}
ServiceCenter::ServiceCenter(int numRegistrars, int numCashiers, int numFinAids, unsigned int tick) {
    config = NULL;
    registrar = new Office("Registrar", numRegistrars);
    cashier = new Office("Cashier", numCashiers);
    finaid = new Office("Finaid", numFinAids);

    inCenter = new TDoublyLinkedList<Customer*>();

}

ServiceCenter::ServiceCenter(Configuration *c) {
    // for(int i = 0; i < 3; ++i) {
    //     cout << "char with c: " << c->students->peek()->getOfficeOrder()[i] << endl;
    // }
    // cout << endl << endl;
    config = c;
    // for(int i = 0; i < 3; ++i) {
    //     cout << "char in ServiceCenter(): " << config->students->peek()->getOfficeOrder()[i] << endl;
    // }

    registrar = new Office("Registrar", config->numRegistrars, config);
    cashier = new Office("Cashier", config->numCashiers, config);
    finaid = new Office("Finaid", config->numFinAids, config);

    inCenter = new TDoublyLinkedList<Customer*>();

    // cout << "service center created" << endl;
}

ServiceCenter::~ServiceCenter() {
    delete config;
    delete registrar;
    delete cashier;
    delete finaid;
}

void ServiceCenter::service() {
    int nextTick = config->startingTick;
    Customer* currStudent;
    Office* currOffice;
    //do

    do { 
        cout << "CURRENT TICK: " << config->currentTick << endl;
        //find num students at tick            //adding students to list
        if(config->currentTick == nextTick) {
            while(!config->students->isEmpty() && config->students->peek()->getArrivalTick() == nextTick) {
                //add them to a list
                currStudent = config->students->pop();
                inCenter->insertBack(currStudent);
                if(config->students->isEmpty()) {
                    // nextTick = INT_MAX;
                    break;
                }
            }
            //find next student's arrival tick
            if(!config->students->isEmpty())
                nextTick = config->students->peek()->getArrivalTick();
        }

        //while loop through the list
        while(!inCenter->isEmpty()) {
        // for(int i = 0 ; i < inCenter->getSize(); ++i) {

            currStudent = inCenter->removeFront();
            //find student's office
            currOffice = findOffice(currStudent->getCurrentOffice());

            //if there is an empty window
            if(currStudent->findUseTime() > 0) {
                if(!currOffice->serviceStudent(currStudent)) { //add student there
                    currStudent->startWait(config->currentTick);
                    currOffice->holdStudent(currStudent); //else add to office queue
                }
                // cout << "put student in office" << endl;
            } else {
                currStudent->nextOffice();
                if(currStudent->getCurrentIndex() < 2) {
                    inCenter->insertBack(currStudent);
                } else {
                    config->exit->push(currStudent);
                }
            }

        }

        finaid->printIdles();

        // registrar->displayOfficeState();
        // cashier->displayOfficeState();
        // finaid->displayOfficeState();

        //call processQueue on each office
        registrar->processQueue();       
        sendBack(registrar);

        cashier->processQueue();
        sendBack(cashier); 

        finaid->processQueue();
        sendBack(finaid);
        
        // registrar->printIdles();
        // cashier->printIdles();

        if(officesAreEmpty() && inCenter->isEmpty() && config->students->isEmpty()) {
            break;
        }

        //increment currentTick
        (config->currentTick)++;
    } while(true); //while there are students in queue

    
    //for each office
        //for each window
            //find longest idle time

    //registrar
    registrar->calculateOutputs();
    //cashier
    cashier->calculateOutputs();
    //finaid
    finaid->calculateOutputs();

    config->printOutputs();
}

bool ServiceCenter::officesAreEmpty() {
    if(!registrar->officeIsEmpty()) {
        return false;
    }
    if(!cashier->officeIsEmpty()) {
        return false;
    }
    if(!finaid->officeIsEmpty()) {
        return false;
    }
    return true;
}

void ServiceCenter::sendBack(Office *o) {
    while(!o->getCenterGoers()->isEmpty()) {
        inCenter->insertBack(o->getCenterGoers()->pop());
    }
}


Office* ServiceCenter::getRegistrar() {
    return registrar;
}
Office* ServiceCenter::getCashier() {
    return cashier;
}
Office* ServiceCenter::getFinAid() {
    return finaid;
}

Office* ServiceCenter::findOffice(char c) {
    if(c == registrar->getType()[0])
        return registrar;
    if(c == cashier->getType()[0])
        return cashier;

    if(c == finaid->getType()[0])
        return finaid;
}

int ServiceCenter::findUseTime(char c, Customer *s) {
    if(c == registrar->getType()[0])
        return s->getUseTimes()[0];
    
    if(c == cashier->getType()[0])
        return s->getUseTimes()[1];

    if(c == finaid->getType()[0])
        return s->getUseTimes()[2];
    
    return 0;
}