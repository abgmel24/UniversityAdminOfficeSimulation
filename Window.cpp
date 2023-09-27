#include "Window.h"

Window::Window() {
    windowIsIdle = true;
    idleTime = 0;
    totalIdleTime = 0;
}

Window::Window(Configuration *c) {
    config = c;

    windowIsIdle = true;
    idleTime = 0;
    totalIdleTime = 0;
}

void Window::closeStudent() {
    windowIsIdle = true;
    current = NULL;
}

void Window::idle() {
    idleTime++;
}

void Window::takeStudent(Customer *c) {
    if(!windowIsIdle) {
        return;
    }
    current = c;
    windowIsIdle = false;
    totalIdleTime += idleTime;
    idleTime = 0;
}

bool Window::isIdle() {
    return windowIsIdle;
}

Customer* Window::getStudent() {
    return current;
}

unsigned int Window::getIdleTime() {
    return idleTime;
}

void Window::displayWindowState() {
    if(windowIsIdle) {
        cout << "Idle";
    } else {
        cout << "Taken";
    }
}

unsigned int Window::getTotalIdleTime() {
    return totalIdleTime + idleTime;
}