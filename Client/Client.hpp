//
// Created by noam on 07/12/2021.
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

class Client
{
private:
    int client_socket;
    struct sockaddr_in server_address;
    char client_name[1024];

public:
    Client();
    void openClient();
    void Send();
    void recieve();
    void closeClient();

};
