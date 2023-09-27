#include "Office.h"

Office::Office() {
    type = "none";
}

Office::Office(string type, unsigned int numWindows) {
    this->type = type;
    this->numWindows = numWindows;
    for(int i = 0; i < numWindows; ++i) {
        windows[i] = new Window();
    }

    officeQueue = new TListQueue<Customer*>();
    toCenter = new TListQueue<Customer*>();

    totalWaitTime = 0;
    numStudents = 0;
}

Office::Office(string type, unsigned int numWindows, Configuration *c) {
    this->type = type;
    this->numWindows = numWindows;
    windows = new Window*[numWindows];
    for(int i = 0; i < numWindows; ++i) {
        windows[i] = new Window(c);
    }

    officeQueue = new TListQueue<Customer*>();
    toCenter = new TListQueue<Customer*>();

    config = c;

    totalWaitTime = 0;
    numStudents = 0;

    // cout << "at office constructor: " << endl;
    // cout << type << " office with " << this->numWindows << " windows " << endl;
}

bool Office::serviceStudent(Customer *c) {
    //cout << numWindows << endl;
    // cout << "Called serviceStudent()" << endl;
    // cout << numWindows << endl;
    for(int i = 0; i < numWindows; ++i) {
        // cout << "i: " << i << endl;
        if(windows[i]->isIdle()) {
            windows[i]->takeStudent(c);
            numStudents++;
            return true;
        }
    }
    return false;
}

void Office::holdStudent(Customer *c) {
    officeQueue->push(c);
}
 
void Office::processQueue() {
    //for each window in office
    Customer* current;
    for(int i = 0; i < numWindows; ++i) {
        //if window is empty
        if(windows[i]->isIdle()) {
            //if there is no one to fill window
            if(officeQueue->isEmpty()) {
                //incrment idleTime
                windows[i]->idle(); //increments window's idle time
            //there is someone to fill window
            } else {
                moveStudent(officeQueue->pop(), i);
            }
        }

        //if window is occupied
        if(!windows[i]->isIdle()) {
            //increment studentTime at window
            current = windows[i]->getStudent();
            current->spendTime();
            //if studentTime == useTime
            if(current->getTimeSpent() == current->findUseTime()) {
                windows[i]->closeStudent();
                //if student has another office to go to
                if(current->getCurrentIndex() < 2) {
                    //set studentTime to 0
                    current->setTimeSpent(0);
                    current->nextOffice();
                    //add student to back of the list
                    toCenter->push(current);
                    if(!officeQueue->isEmpty()) {
                        moveStudent(officeQueue->pop(), i);
                    }
                } else {
                    config->exit->push(current);
                    if(current->getTotalWaitTime() > 10) {
                        (config->longWaits)++;
                    } 
                 }
            }
        }
    }
    current = NULL;
}

TListQueue<Customer*>* Office::getCenterGoers() {
    return toCenter;
}

void Office::moveStudent(Customer* current, int i) {
    windows[i]->takeStudent(current);
    numStudents++;
    //how long did they wait for?
    int waitTime = (config->currentTick) - current->getWaitStart() + 1;
    current->addWaitTime(waitTime);
    totalWaitTime += waitTime;
    //admin
    int globalIndex = getIndexForType();
    if(waitTime > config->maxWaitTimes[globalIndex]) {
        config->maxWaitTimes[globalIndex] = waitTime;
    }
}

void Office::calculateOutputs() {
    cout << type << endl;
    int globalIndex = getIndexForType();
    double totalIdleTime = 0;
    unsigned int curr = 0;
    for(int i = 0; i < numWindows; ++i) {
        curr = windows[i]->getTotalIdleTime();
        totalIdleTime += curr;
        cout << "window idle time " << curr << endl;
        if(curr > 5) { //number of idles over 5 ticks
            (config->longIdles)++;
        }
        if(curr > config->maxIdleTimes[globalIndex]) { //longest idle time
            config->maxIdleTimes[globalIndex] = curr;
        }
    }
    if(numStudents == 0) {
        config->meanWaitTimes[globalIndex] = 0.0;
    } else {
        config->meanWaitTimes[globalIndex] = totalWaitTime / numStudents;
    }
    config->meanIdleTimes[globalIndex] = totalIdleTime / numWindows;
}



string Office::getType() {
    return type;
}

unsigned int Office::getNumWindows() {
    return numWindows;
}

int Office::getIndexForType() {
    if(type == "Registrar")
        return 0;
    if(type == "Cashier")
        return 1;
    if(type == "Finaid")
        return 2;

    return -1;
}

void Office::displayOfficeState() {
    cout << "Type: " << type << endl;
    for(int i = 0; i < numWindows; ++i) {
        cout << "Window " << i + 1 << ": ";
        windows[i]->displayWindowState();
        cout << endl;
    }
    cout << endl;
}

bool Office::officeIsEmpty() {
    for(int i = 0; i < numWindows; ++i) {
        if(!windows[i]->isIdle()) {
            return false;
        }
    }
    return true;
}

void Office::printIdles() {
    // cout << "Type: " << type << endl;
    for(int i = 0; i < numWindows; ++i) {
        cout << "Window " << (i + 1) << ": " << windows[i]->getIdleTime()  << " ticks" << endl;
    }
    // cout << "office is empty now: ";
    // config->printBool(windows[0]->isIdle());
    // cout << endl;
}

TListQueue<Customer*>* Office::getOfficeQueue() {
    return officeQueue;
}