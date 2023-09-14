#include <iostream>
#include "../lib/solver.hpp"
#include "../lib/hungarian.hpp"
#include <stdio.h>
#include <chrono>
#include <string>
#include <algorithm>
#include <fstream>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

int main(int argc, char*argv[]) {
    
    
    vector<string> setting;
    vector<string> setting_log;
    bool is_setting_log = false;

    ifstream infile(argv[3]);
    string line;
    bool execute = false;
    while (getline(infile, line))
    {
        string command;
        for (auto word : line) {
            if (execute && !isspace(word)) command += word;
            if (word == '=') execute = true;
        }
        if (execute) setting.push_back(command);
        execute = false;
        line.clear();
    }
    infile.close();

    infile.open(argv[4]);
    if(infile.is_open()){
        is_setting_log = true;
        while (getline(infile, line))
        {
            string command;
            for (auto word : line) {
                if (execute && !isspace(word)) command += word;
                if (word == '=') execute = true;
            }
            if (execute) setting_log.push_back(command);
            execute = false;
            line.clear();
        }
        infile.close();
    }

    setpriority(PRIO_PROCESS, 0, -20);

    
    solver s;
    if(is_setting_log) s.assign_log_parameter(setting_log);
    s.assign_parameter(setting);
    s.solve(argv[1],atoi(argv[2]));    
    
    
    return 0;
}