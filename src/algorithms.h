#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <vector>
#include "process.h"

bool operator<(const Process& P1, const Process& P2);
vector<Process> runFCFS(vector<Process> L);                     // Chạy thuật toán FCFS (có Response Time)
vector<Process> runSJF(vector<Process> L);
vector<Process> sort_for_show_table(vector<Process>& L);
vector<Process> sort_for_draw_gantt(vector<Process>& L);

#endif // ALGORITHMS_H
