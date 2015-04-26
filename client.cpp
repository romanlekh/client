#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

#include "client.h"

using std::cout;
using std::endl;
using std::cerr;
using std::cin;
using std::string;


Client::Client(): user_name(""), soc_var(0)
{
    // Set socket type
    peer.sin_family = AF_INET;
    // Set port
    peer.sin_port = htons(7500);
    // Set address of server
    peer.sin_addr.s_addr = inet_addr( "127.0.0.1" );
}

Client::Client(string name, int socket_descriptor, sockaddr_in peer_info):
    user_name(name), soc_var(socket_descriptor), peer(peer_info)
{}

Client::~Client()
{
    close(soc_var);
}

void Client::ReceiveMessage()
{
    // Temp result of function
    int res_soc;
    for(;!do_exit;)
    {
        char buffer[1024] = {'\0'};
        res_soc = recv(soc_var, buffer, sizeof(buffer), 0);
        if( res_soc > 0 )
        {
            cout << "\033[1;32m" << buffer << "\033[0m" << endl;
        }
    }
}

void Client::SendMessage()
{
    for(;;)
    {
        char message[1024] = {'\0'};
        cin.getline( message, 1024 );

        int res_soc = send(soc_var, message, sizeof(message), 0);
        if( res_soc < 0 )
        {
            cerr << "Error with r send";
        }
        if( strcmp( message, "<< exit" ) == 0 )
        {
            cout << endl << "By by" << endl;
            do_exit_mutex.lock();
            do_exit = true;
            do_exit_mutex.unlock();
            return;
        }
    }
}




