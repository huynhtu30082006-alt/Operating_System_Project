#include "list_process.h"

void list_process::addProcess(const Process &p)
{
    processes.push_back(p);
}

void list_process::clear()
{
    processes.clear();
}
