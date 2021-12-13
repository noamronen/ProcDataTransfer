#include "Server.h"

#pragma comment (lib, "ws2_32.lib") //including the library to the LINKER settings.

using namespace std;
int main()
{
    Server serv = Server();
    serv.openServer();
    serv.closeServer();

    return 0;
}
