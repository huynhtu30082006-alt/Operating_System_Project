#include "scheduling_algorithms.h"
#include <algorithm>
#include <climits>

Process::Process(string pid, int at, int bt) {
    this->pid = pid;
    this->arrivalTime = at;
    this->burstTime = bt;
    this->startTime = 0;
    this->completionTime = 0;
    this->turnaroundTime = 0;
    this->waitingTime = 0;
    this->responseTime = 0;
}

void SchedulerSJF::addProcess(const Process &p) {
    processes.push_back(p);
}

void SchedulerSJF::runSJF() {
    int n = processes.size();
    int completed = 0;
    int currentTime = 0;
    vector<bool> isCompleted(n, false);

    while (completed != n) {
        int idx = -1;
        int minBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i]) {
                if (processes[i].burstTime < minBurst) {
                    minBurst = processes[i].burstTime;
                    idx = i;
                }
                else if (processes[i].burstTime == minBurst) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            processes[idx].startTime = currentTime;
            processes[idx].completionTime = currentTime + processes[idx].burstTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].startTime - processes[idx].arrivalTime;
            processes[idx].responseTime = processes[idx].waitingTime;

            currentTime = processes[idx].completionTime;
            isCompleted[idx] = true;
            completed++;
        } else {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!isCompleted[i] && processes[i].arrivalTime < nextArrival)
                    nextArrival = processes[i].arrivalTime;
            }
            currentTime = nextArrival;
        }
    }
}

vector<Process> SchedulerSJF::getResults() const {
    return processes;
}