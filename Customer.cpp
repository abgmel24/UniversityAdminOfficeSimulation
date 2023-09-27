#include "Customer.h"

Customer::Customer() {}
Customer::Customer(int arrivalTick, char* officeOrder, int* useTimes) {
    this->arrivalTick = arrivalTick;
    this->officeOrder = officeOrder;
    this->useTimes = useTimes;

    currIndex = 0;
    timeSpentAtWindow = 0;
    totalTimeWaited = 0;
}

// Customer::~Customer() {
//     delete[] officeOrder;
//     delete[] useTimes;
// }

int Customer::findUseTime() {
    // if(c == 'R')
    //     return useTimes[REGISTRAR_INDEX];
    
    // if(c == 'C')
    //     return useTimes[CASHIER_INDEX];

    // if(c == 'F')
    //     return useTimes[FINAID_INDEX];
    
    // return 0;
    return useTimes[currIndex];
}

void Customer::startWait(unsigned int n) {
    waitStartAt = n;
}

unsigned int Customer::getWaitStart() {
    return waitStartAt;
}

void Customer::addWaitTime(unsigned int n) {
    totalTimeWaited += n;
}

void Customer::spendTime() {
    timeSpentAtWindow++;
}

unsigned int Customer::getTimeSpent() {
    return timeSpentAtWindow;
}

void Customer::setTimeSpent(unsigned int s) {
    timeSpentAtWindow = s;
}

char Customer::getCurrentOffice() {
    return officeOrder[currIndex];
}

unsigned int Customer::getCurrentIndex() {
    return currIndex;
}

void Customer::nextOffice() {
    ++currIndex;
}

int Customer::getArrivalTick() {
    return arrivalTick;
}
char* Customer::getOfficeOrder() {
    return officeOrder;
}
int* Customer::getUseTimes() {
    return useTimes;
}

unsigned int Customer::getTotalWaitTime() {
    return totalTimeWaited;
}