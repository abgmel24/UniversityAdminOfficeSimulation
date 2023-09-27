#ifndef WINDOW_H 
#define WINDOW_H

#include "TListQueue.h"
#include "Configuration.h"
#include "Customer.h"

class Window {
    public:
        Window();
        Window(Configuration *c);

        void takeStudent(Customer *c);
        void closeStudent();

        void processQueue();

        void idle();
        bool isIdle();

        unsigned int getIdleTime();
        unsigned int getTotalIdleTime();
        Customer* getStudent();

        void displayWindowState();

    private:
        Configuration *config;

        bool windowIsIdle;
        Customer *current;

        unsigned int idleTime;
        unsigned int totalIdleTime;
        //bool longIdle;

};

#endif