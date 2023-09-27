#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer {
    public:
        Customer();
        Customer(int arrivalTick, char* officeOrder, int* useTimes);

        int getArrivalTick();

        char* getOfficeOrder();
        int* getUseTimes();

        char getCurrentOffice();
        unsigned int getCurrentIndex();

        unsigned int getTimeSpent();
        void setTimeSpent(unsigned int n);
        unsigned int getTotalWaitTime();

        void startWait(unsigned int n);
        unsigned int getWaitStart();
        void addWaitTime(unsigned int n);

        void nextOffice();
        int findUseTime();
        void spendTime();

    private:
        int arrivalTick;
        char* officeOrder;
        int* useTimes;

        unsigned int waitStartAt;
        unsigned int totalTimeWaited;

        unsigned int timeSpentAtWindow;
        unsigned int currIndex;

        // const static int REGISTRAR_INDEX = 0;
        // const static int CASHIER_INDEX = 1;
        // const static int FINAID_INDEX = 2;
};

#endif