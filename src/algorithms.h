#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include "process.h"

// Compare processes by Arrival Time (for FCFS)
bool operator<(const Process& P1, const Process& P2);

// FCFS scheduling algorithm
vector<Process> runFCFS(vector<Process> L);

#endif // ALGORITHMS_H
