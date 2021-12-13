//
// Created by noam on 06/12/2021.
//
#pragma once
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include <pthread.h>


using namespace std;

#pragma warning(disable:4996)
#include "Procfs_Miner.h"

class Server
{
private:
    int server_socket;
    std::vector<int> clients_vec;
    std::vector<std::thread>client_threads;
    struct sockaddr_in server_address;
    int numOfClients = 0;
    Procfs_Miner miner;

public:
    Server();
    void Send(int client_socket, string buffer);
    void recieve(int client_socket);
    void openServer();
    void closeServer();
};
