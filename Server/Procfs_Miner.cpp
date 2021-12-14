//
// Created by noam on 06/12/2021.
//
#include "Procfs_Miner.h"

data_type::data_type()
{
    position=0;
    description="";
}
data_type::data_type(int i,string description)
{
    this->position=i;
    this->description=description;
}

proc_type::proc_type()
{
    type="";
    vec;
}
proc_type::proc_type(string type, vector<data_type> vec)
{
    this->type=type;
    this->vec=vec;
}

Procfs_Miner::Procfs_Miner()
{
    //adding the /proc/stat to the miner
    vector<data_type> dataVec;
    data_type new_data;
    new_data = data_type(1, "Time spent in user mode: ");
    dataVec.push_back(new_data);
    new_data =  data_type(3,"Time spent in system mode: ");
    dataVec.push_back(new_data);
    new_data = data_type(6,"Time servicing interrupts: ");
    dataVec.push_back(new_data);
    proc_type newProcType=proc_type("/proc/stat",dataVec);
    procfs_options.push_back(newProcType);
    //-----------------------------------
}

Procfs_Miner::Procfs_Miner(vector<proc_type> procfs_options)
{
    this->procfs_options=procfs_options;
}

void Procfs_Miner::setProcfs_options(vector<proc_type> procfs_options)
{
    this->procfs_options=procfs_options;
}

vector<proc_type> Procfs_Miner::getProcfs_options()
{
    return procfs_options;
}

void Procfs_Miner::Mine_proc_stat_cpuDataPrint()
{
    for(proc_type i : procfs_options)
    {
        if(i.type=="/proc/stat")
        {
            std::ifstream filestat(i.type);
            std::string line;
            int counter=-1;

            while(std::getline(filestat,line))
            {
                if(line.at(0)=='c'&&line.at(1)=='p'&&line.at(2)=='u') //cpu details
                {
                    if(counter==-1)//printing the currect cpu number
                    {
                        cout<<"cpu: "<<endl;
                        counter++;
                    }
                    else
                    {
                        cout<<"cpu"<<counter<<": "<<endl;
                        counter++;
                    }

                    for(data_type j: i.vec)//we print all the data we want for each cpu
                    {
                        string temp_line=line,token;
                        int count_start=0;

                        count_start=temp_line.find(' ');
                        count_start++;

                        for(int i=0;i<j.position;i++)
                        {

                            while(temp_line.at(count_start)!=' ')
                            {
                                count_start++;
                            }
                            count_start++;

                        }//now we know where the relevant number begins
                        int count_end=count_start;
                        while(temp_line.at(count_end)!=' ')
                        {
                            count_end++;
                        }
                        count_end--;
                        //now we know where the relevant number ends
                        int sizeOfToken=count_end-count_start+1;
                        token=temp_line.substr(count_start,sizeOfToken);
                        cout<<j.description<<token<<endl;//printing the relevant number


                    }

                }
                else
                {
                    break;

                }
            }
        }
    }
}

string Procfs_Miner::Mine_proc_stat_cpuDataStr()//returning the output as a string
{
    string returnBuffer="";
    for(proc_type i : procfs_options)
    {
        if(i.type=="/proc/stat")
        {
            std::ifstream filestat(i.type);
            std::string line;
            int counter=-1;

            while(std::getline(filestat,line))
            {
                if(line.at(0)=='c'&&line.at(1)=='p'&&line.at(2)=='u') //cpu details
                {
                    if(counter==-1)//printing the currect cpu number
                    {
                        returnBuffer.append("cpu: \n");
                        counter++;
                    }
                    else
                    {
                        returnBuffer.append("cpu"+ to_string(counter)+": \n");
                        counter++;
                    }

                    for(data_type j: i.vec)//we append all the data we want for each cpu
                    {
                        string temp_line=line,token;
                        int count_start=0;

                        count_start=temp_line.find(' ');
                        count_start++;

                        for(int i=0;i<j.position;i++)
                        {

                            while(temp_line.at(count_start)!=' ')
                            {
                                count_start++;
                            }
                            count_start++;

                        }//now we know where the relevant number begins
                        int count_end=count_start;
                        while(temp_line.at(count_end)!=' ')
                        {
                            count_end++;
                        }
                        count_end--;
                        //now we know where the relevant number ends
                        int sizeOfToken=count_end-count_start+1;
                        token=temp_line.substr(count_start,sizeOfToken);
                        returnBuffer.append(j.description+token+"\n");


                    }

                }
                else
                {
                    break;

                }
            }
        }
    }
    return returnBuffer;
}
void Procfs_Miner::Mine_proc_memoryInfoPrint()
{
    //prints line by line the memory data received from /proc/meminfo file
    std::ifstream filestat("/proc/meminfo");
    std::string line;
    while(std::getline(filestat,line))
    {
        cout<<line<<endl;
    }
}
string Procfs_Miner::Mine_proc_memoryInfoStr()
{
    string returnBuffer="";
    //appends line by line the memory data received from /proc/meminfo file
    std::ifstream filestat("/proc/meminfo");
    std::string line;
    while(std::getline(filestat,line))
    {
        returnBuffer.append(line+"\n");
    }
    return returnBuffer;
}
void Procfs_Miner::Mine_proc_KernelModulePrint()
{
    //prints line by line the kernel modules data received from /proc/kcore file
    std::ifstream filestat("/proc/modules");
    std::string line;
    while(std::getline(filestat,line))
    {
        cout<<line<<endl;
    }
}
string Procfs_Miner::Mine_proc_KernelModuleStr()
{
    string returnBuffer="";
    //appends line by line the kernel modules data received from /proc/kcore file
    std::ifstream filestat("/proc/modules");
    std::string line;
    while(std::getline(filestat,line))
    {
        returnBuffer.append(line+"\n");
    }
    return returnBuffer;
}

void Procfs_Miner::Mine_Kernel_MessagesPrint()
{
    std::ifstream filestat("/var/log/syslog");
    std::string line;
    while(std::getline(filestat,line))
    {
        cout<<line<<endl;
    }
}

string Procfs_Miner::Mine_Kernel_MessagesStr()
{
    string returnBuffer="";
    std::ifstream filestat("/var/log/syslog");
    std::string line;
    while(std::getline(filestat,line))
    {
       returnBuffer.append(line+"\n");
    }
    return returnBuffer;
}

void Procfs_Miner::Mine_open_portsPrint()
{
    std::ifstream filestat("/proc/net/tcp");
    std::string line;
    while(std::getline(filestat,line))
    {
        cout<<line<<endl;
    }
}
/*
void Procfs_Miner::addProcType(proc_type newOption)
{
    bool flag=false;
    for(proc_type i : procfs_options)
    {
        if(i.type==newOption.type)
        {
            flag=true;
        }
    }
    if(flag=true)
        cout<<"proc type: "<<newOption.type<<" already exists whithin the procfs miner"<<endl;
    else
        procfs_options.push_back(newOption);
}
 */



