#include <iostream>
#include <fstream>
#include <sstream>
#include "IO.h"

using namespace std;

void IO::readCSV(const string& filename, list_process& L)
{
    ifstream read_file(filename);

    if (!read_file.is_open())
    {
        cout << "Can't Open file name: " << filename << endl;
        return;
    }
    string line;

    // Bỏ dòng header
    getline(read_file, line);

    while (getline(read_file, line))
    {
        stringstream ss(line);
        string pid, at_str, bt_str;

        getline(ss, pid, ',');
        getline(ss, at_str, ',');
        getline(ss, bt_str, ',');

        int at = stoi(at_str);
        int bt = stoi(bt_str);

        //tạo object tương ứng với từng line được đọc
        Process P(pid, at, bt);
        L.addProcess(P);

    }

    read_file.close();
}

void IO::save_to_file(const string& filename, const std::vector<Process>& result_prcs)
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        return; // hoặc throw runtime_error nếu muốn
    }

    out << "PID,Arrival,Burst,Start,Completion,Turnaround,Waiting,Response\n";

    for (const auto& p : result_prcs)
    {
        out << p.get_pid() << ","
            << p.get_arrivalTime() << ","
            << p.get_burstTime() << ","
            << p.get_startTime() << ","
            << p.get_completionTime() << ","
            << p.get_turnaroundTime() << ","
            << p.get_waitingTime() << ","
            << p.get_responseTime() << "\n";
    }

    out.close();
}

vector<Process> IO::load_file(const string& filename)
{
    vector<Process> L;
    ifstream read(filename);

    if(!read.is_open())
    {
        cout << "Can't Open file name: " << filename << endl;
        return L;
    }

    string line;
    getline(read, line);

    while(getline(read, line))
    {
        stringstream ss(line);
        string pid, a, b, s, c, t, w, r;

        getline(ss, pid, ',');
        getline(ss, a, ',');
        getline(ss, b, ',');
        getline(ss, s, ',');
        getline(ss, c, ',');
        getline(ss, t, ',');
        getline(ss, w, ',');
        getline(ss, r, ',');

        Process P(pid, stoi(a), stoi(b), stoi(s), stoi(c), stoi(t), stoi(w), stoi(r));
        L.push_back(P);
    }
    return L;

}
