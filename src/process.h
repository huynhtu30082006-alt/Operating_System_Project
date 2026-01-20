#ifndef PROCESS_H
#define PROCESS_H
#include <string>
using namespace std;

class Process
{
    private:
            string pid;
            int arrivalTime;
            int burstTime;
            int startTime;
            int completionTime;
            int turnaroundTime;
            int waitingTime;
            int responseTime;
    public:
            Process(string p, int a, int b);
            Process(string p, int a, int b, int s, int c, int t, int w, int r);
            string get_pid()const {return pid;}
            int get_arrivalTime()const {return arrivalTime;}
            int get_startTime()const {return startTime;}
            void set_startTime(int s){startTime = s;}
            int get_completionTime()const {return completionTime;}
            void set_completionTime(int c) { completionTime = c; }
            int get_burstTime()const {return burstTime;}
            int get_turnaroundTime()const {return turnaroundTime;}
            void set_turnaroundTime(int t) {turnaroundTime = t;}
            int get_waitingTime()const {return waitingTime;}
            void set_waitingTime(int w){waitingTime = w;}
            void set_responseTime(int s){responseTime = s;}
            int get_responseTime()const {return responseTime;}

};

#endif
