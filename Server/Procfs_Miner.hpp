//
// Created by noam on 06/12/2021.
//

#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct data_type
{
    data_type();
    data_type(int i,string description);
    int position;
    string description;
};

struct proc_type
{
    proc_type();
    proc_type(string type,vector<data_type>);
    string type;
    vector<data_type> vec;
};



class Procfs_Miner
{
private:
    vector<proc_type> procfs_options;//will contain a vector for each /proc/type
public:
    Procfs_Miner();
    Procfs_Miner(vector<proc_type> procfs_options);

    void setProcfs_options( vector<proc_type> procfs_options);
    vector<proc_type> getProcfs_options();

    //void addProcType(proc_type newOption);

    void Mine_proc_stat_cpuDataPrint();
    string  Mine_proc_stat_cpuDataStr();

    void Mine_proc_memoryInfoPrint();
    string Mine_proc_memoryInfoStr();

    void Mine_proc_KernelModulePrint();
    string Mine_proc_KernelModuleStr();

};
