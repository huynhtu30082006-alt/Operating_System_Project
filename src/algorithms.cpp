#include <algorithm>
#include "algorithms.h"


// Hàm so sánh dùng cho sort
bool operator<(const Process& P1, const Process& P2)
{
    return P1.get_arrivalTime() < P2.get_arrivalTime();
}

vector<Process> runFCFS(vector<Process> L)
{
    // 1) Sắp xếp theo arrivalTime
    sort(L.begin(), L.end());

    int currentTime = 0;
    for (auto &p : L)
    {
        if (currentTime < p.get_arrivalTime())
        {
            currentTime = p.get_arrivalTime();
        }

        // Start Time
        p.set_startTime(currentTime);

        // Completion Time
        p.set_completionTime(currentTime + p.get_burstTime());

        // Turnaround Time
        p.set_turnaroundTime(p.get_completionTime() - p.get_arrivalTime());

        // Waiting Time
        p.set_waitingTime(p.get_startTime() - p.get_arrivalTime());

        // Response Time = Waiting Time
        p.set_responseTime(p.get_waitingTime());

        currentTime = p.get_completionTime();
    }
    return L;
}
