#ifndef SCHEDULING_ALGORITHMS_H
#define SCHEDULING_ALGORITHMS_H

#include <string>
#include <vector>

using namespace std;

class Process {
public:
    string pid;
    int arrivalTime;
    int burstTime;
    int startTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;

    Process(string pid = "", int at = 0, int bt = 0);
};

class SchedulerSJF {
private:
    vector<Process> processes;

public:
    void addProcess(const Process &p);
    void runSJF();
    vector<Process> getResults() const;
};

#endif