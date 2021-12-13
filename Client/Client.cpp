//
// Created by noam on 07/12/2021.
//

#include "Client.h"
#pragma warning(disable:4996)
using namespace std;

Client::Client()
{
    cout << "enter name: \n";
    cin.getline(client_name, 1024);
    strcat(client_name, ": ");

    //creating the socket
    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket < 0)
    {
        printf("client socket creation failed \n");
    }
    else
    {
        printf("client socket creation successfull \n");
    }

    //define the address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // connects to any IP address used by the computer

    //connect
    if (connect(client_socket, (sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        printf("connecting failed \n");
    }
    else
    {
        printf("connecting successfull \n");
    }
}

void Client::Send()
{
    int option=-1;
    while(true)
    {
        cout<<"to exit press 0"<<endl;
        cout<<"for cpu data press 1"<<endl;
        //rest of options
        cin>>option;
        switch (option)
        {
            case 0: // exit
            {
                closeClient();
                exit(0);
            }
            case 1: //cpu data
            {
                char SendBuffer[1024] = "cpu_data\0";
                send(client_socket, SendBuffer, strlen(SendBuffer) + 1, 0);
                break;

            }
        }
    }
}

void Client::recieve()
{
    char RecvBuffer[1024];

    while (true)
    {
        recv(client_socket, RecvBuffer, strlen(RecvBuffer) + 1, 0);
        //printf("%s ", RecvBuffer);
        cout<<RecvBuffer;
        memset(RecvBuffer, 0, 1024);
    }
}

void Client::openClient()
{
    while (true)
    {
        std::thread sending_thread = thread(&Client::Send,this);
        std::thread recieving_thread = thread(&Client::recieve,this);
        sending_thread.join();
        recieving_thread.join();
    }
}

void Client::closeClient()
{
    //close
    if (close(client_socket) < 0)
    {
        printf("closing failed \n");
    }
    else
    {
        printf("closing successfull \n");
    }
}
