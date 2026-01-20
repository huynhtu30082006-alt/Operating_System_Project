#ifndef LIST_PROCESS_H
#define LIST_PROCESS_H
#include <vector>
#include "process.h"
using namespace std;

class list_process
{
    private:
            vector<Process> processes;
    public:
            void clear();
            void addProcess(const Process &p);
            vector<Process>& get_ref_processes(){return processes;}
            vector<Process> get_val_processes(){return processes;}
};


#endif // LIST_PROCESS_H
