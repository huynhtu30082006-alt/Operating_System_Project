#include "process.h"

// Constructor
Process::Process(string p, int a, int b) {
    this->pid = p;
    this->arrivalTime = a;
    this->burstTime = b;
    this->startTime = 0;
    this->completionTime = 0;
    this->turnaroundTime = 0;
    this->waitingTime = 0;
    this->responseTime = 0;
}

Process::Process(string p, int a, int b, int s, int c, int t, int w, int r)
{
    this->pid = p;
    this->arrivalTime = a;
    this->burstTime = b;
    this->startTime = s;
    this->completionTime = c;
    this->turnaroundTime = t;
    this->waitingTime = w;
    this->responseTime = r;
