#ifndef IO_H
#define IO_H
#include <string>
#include "list_process.h"
using namespace std;

class IO
{
    public:
            static void readCSV(const string& filename, list_process& L);
            static void save_to_file(const string& filename, const std::vector<Process>& result_prcs);
            static vector<Process> load_file(const string& filename);
};

#endif // IO_H

