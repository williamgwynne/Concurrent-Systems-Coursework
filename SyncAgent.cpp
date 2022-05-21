#include "SyncAgent.h"



void StartAgent::pause()  {
    // insert code to implement pausing of all athlete threads
    std::unique_lock<std::mutex> StartLock(lock); //the 4 waiting runners share the same mutex
    StartLock_CV.wait(StartLock); //makes calling thread wait for condition variable to wake it
}

void StartAgent::proceed()  {
    // insert code to implement releasing of all athlete threads
    std::cout << "On your marks!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(rand()%5)); //all this is just beautification (along with the random time delay)
    std::cout << "Set!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(rand()%5));
    std::cout << "BANG!" <<std::endl;
    std::cout << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl<<endl;

    StartLock_CV.notify_all(); //notifies all runners on start line
}


void EZAgent::pause() {
    //code very similar to StartAgent::pause
    std::unique_lock<std::mutex> EZLock(lock);
    EZLock_CV.wait(EZLock);
}

void EZAgent::proceed() {
    EZLock_CV.notify_one(); //releases 1 waiting runner
}



FinishAgent::FinishAgent(ThreadMap& t) : tMap(t) { }

void FinishAgent::pause() { } //pause not needed as no threads are waiting, instead proceed released

void FinishAgent::proceed() {
    std::unique_lock<std::mutex> lk(tum);
    r.setPosition(tMap.getCompetitor());

}

Results FinishAgent::returnResults() { return r; }
