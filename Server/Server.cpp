//
// Created by noam on 06/12/2021.
//
#include "Server.h"
using namespace std;

#pragma warning(disable:4996)



Server::Server()
{
    //initialize the procfs miner
    miner = Procfs_Miner();
    //define the address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    //creating the socket
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket < 0)
    {
        printf("server socket creation failed \n");
    }
    else
    {
        printf("server socket creation successfull \n");
    }

    //bind
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) <0)
    {
        printf("binding failed \n");
    }
    else
    {
        printf("binding successfull \n");
    }

    //listen
    if (listen(server_socket, 5) <0)
        printf("listening failed \n");
    else
        printf("listening successfull \n");

}


void Server::recieve(int client_socket)
{
    char RecvBuffer[1024];
    memset(RecvBuffer,NULL, 1024);
    while (true)
    {

        if (recv(client_socket, RecvBuffer, 1024, 0) >=0)
        {

            cout<<"message received: "<<RecvBuffer<<endl;
            if(strcmp(RecvBuffer,"cpu_data\0")==0)
            {
                string output = miner.Mine_proc_stat_cpuDataStr();
                int size = output.length();
                char SendBuffer[size];
                strcpy(SendBuffer,output.c_str());
                strcat(SendBuffer,"\n \0");
                send(client_socket,SendBuffer, strlen(SendBuffer+1),0);//sending the message
                cout<<"message sent: "<<SendBuffer<<endl;
            }
            if(strcmp(RecvBuffer,"memory_data\0")==0)
            {
                string output = miner.Mine_proc_memoryInfoStr();
                int size = output.length();
                char SendBuffer[size];
                strcpy(SendBuffer,output.c_str());
                strcat(SendBuffer,"\n \0");
                send(client_socket,SendBuffer, strlen(SendBuffer+1),0);//sending the message
                cout<<"message sent: "<<SendBuffer<<endl;
            }
            if(strcmp(RecvBuffer,"kernelModule_data\0")==0)
            {
                string output = miner.Mine_proc_KernelModuleStr();
                int size = output.length();
                char SendBuffer[size];
                strcpy(SendBuffer,output.c_str());
                strcat(SendBuffer,"\n \0");
                send(client_socket,SendBuffer, strlen(SendBuffer+1),0);//sending the message
                cout<<"message sent: "<<SendBuffer<<endl;
            }
            if(strcmp(RecvBuffer,"kernel_messages\0")==0)
            {
                string output = miner.Mine_Kernel_MessagesStr();
                int size = output.length();
                char SendBuffer[size];
                strcpy(SendBuffer,output.c_str());
                strcat(SendBuffer,"\n \0");
                send(client_socket,SendBuffer, strlen(SendBuffer+1),0);//sending the message
                cout<<"message sent: "<<SendBuffer<<endl;
            }




        }


    }
}

void Server::openServer()
{
    struct sockaddr_in client_addr;
    int iclient_addr = sizeof(client_addr);
    while (true)
    {
        int new_client;
        new_client = accept(server_socket, (struct sockaddr *)&client_addr, reinterpret_cast<socklen_t *>(&iclient_addr));//?
        //accept
        if (new_client >=0)
        {
            clients_vec.push_back(new_client);
            client_threads.push_back(thread(&Server::recieve, this, clients_vec.back()));
        }
    }
}

void Server::Send(int client_socket, string buffer)
{
    int size = sizeof (buffer);
    char SendBuffer[size+1];
    strcpy(SendBuffer,buffer.c_str());
    strcat(SendBuffer,"\0");
    send(client_socket,SendBuffer, strlen(SendBuffer),0);//sending the message
    cout<<"message sent: "<<SendBuffer<<endl;
}


void Server::closeServer()
{
    //close
    if (close(server_socket)<0)
    {
        printf("closing failed \n");
    }
    else
    {
        printf("closing successfull \n");
    }
}

