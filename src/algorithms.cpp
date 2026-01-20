#include <algorithm>
#include "algorithms.h"
// Hàm so sánh dùng cho sortconst

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

vector<Process> runSJF(vector<Process> L)
{
    int n = L.size();
    int completed = 0;
    int currentTime = 0;
    vector<bool> isCompleted(n, false);

    while (completed != n)
    {
        int idx = -1;
        int minBurst = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (L[i].get_arrivalTime() <= currentTime && !isCompleted[i])
            {
                if (L[i].get_burstTime() < minBurst)
                {
                    minBurst = L[i].get_burstTime();
                    idx = i;
                }
                else if (L[i].get_burstTime() == minBurst) {
                    if (L[i].get_arrivalTime() < L[idx].get_arrivalTime())
                    {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            L[idx].set_startTime(currentTime);
            L[idx].set_completionTime(currentTime + L[idx].get_burstTime());
            L[idx].set_turnaroundTime(L[idx].get_completionTime() - L[idx].get_arrivalTime());
            L[idx].set_waitingTime(L[idx].get_startTime() - L[idx].get_arrivalTime());
            L[idx].set_responseTime(L[idx].get_waitingTime());

            currentTime = L[idx].get_completionTime();
            isCompleted[idx] = true;
            completed++;
        }
        else
        {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++)
            {
                if (!isCompleted[i] && L[i].get_arrivalTime() < nextArrival)
                {

                    nextArrival = L[i].get_arrivalTime();
                }
            }
            currentTime = nextArrival;
        }
    }
    return L;
}

vector<Process> sort_for_show_table(vector<Process>& L)
{
    vector<Process> SL = L;
    sort(SL.begin(), SL.end(), [](const Process& a, const Process& b){
        return a.get_arrivalTime() < b.get_arrivalTime();
    });
    return SL;
}

vector<Process> sort_for_draw_gantt(vector<Process>& L)
{
    vector<Process> GL = L;
    sort(GL.begin(), GL.end(), [](const Process& a, const Process& b){
        return a.get_startTime() < b.get_startTime();
    });
    return GL;
}


