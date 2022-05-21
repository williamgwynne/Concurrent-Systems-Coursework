#pragma once
#include <iostream>
#include <thread>
#include <map>
#include <string>
#include <mutex>
#include <condition_variable>
#include "Results.h"
#include "ThreadMap.h"

class SyncAgent { //abstract base class
public:
    SyncAgent() {}; //constructor
    // Declare virtual methods to be overridden by derived classes
    virtual void pause() = 0;
    virtual void proceed() = 0;
}; //end abstract class SyncAgent


class StartAgent : public SyncAgent { //concrete class that CAN be instantiated
public:
    StartAgent() {};
    void pause() override;
    void proceed() override;
private:
    // insert any necessary data members including variables, mutexes, locks, cond vars
    std::mutex lock;
    std::condition_variable StartLock_CV;
}; //end class StartAgent


class EZAgent : public SyncAgent { //concrete class that CAN be instantiated
public:
    EZAgent() {}; //constructor
    void pause();
    void proceed ();
private:
    // insert any necessary data members including variables, mutexes, locks, cond vars
    std::mutex lock;
    std::condition_variable EZLock_CV;
}; //end class EZAgent


class FinishAgent : public SyncAgent {
private:
    Results r;
    std::mutex tum;
    ThreadMap& tMap;
public:
    FinishAgent (ThreadMap& t);
    void proceed();
    void pause();
    Results returnResults();
};
