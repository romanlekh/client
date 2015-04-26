// CLIENT
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <thread>
#include "client.h"
#include <fcntl.h>

using namespace std;

int main()
{
    sockaddr_in peer;

    // socket descriptor
    int soc_var;
    // temp result of some functions
    int res_soc;

    // Set info socket type
    peer.sin_family = AF_INET;
    // Set port
    peer.sin_port = htons(7500);
    // Set address of server
    peer.sin_addr.s_addr = inet_addr( "127.0.0.1" );

    // Set socket descriptor
    soc_var = socket(AF_INET, SOCK_STREAM, 0);
    if( soc_var < 0 )
    {
        cerr << "Error with s";
        exit(1);
    }

    // Connection with server
    res_soc = connect(soc_var, (sockaddr*)&peer, sizeof(peer));
    if( res_soc < 0 )
    {
        cerr << "Error with connect";
        exit(1);
    }

    char user_name[16] = {'\0'};
    cout << "\033[1;31m" << "\nEnter user name " << "\033[0m";
    cin.getline(user_name, sizeof(user_name));

    // Initialization of Client
    Client client(user_name, soc_var, peer);

    res_soc = send(client.getSocket(), client.getName().c_str(), sizeof(user_name), 0);
    if( res_soc < 0 )
    {
        cerr << "Error with r send";
        exit(1);
    }

    // Get confirmation from server
    char info[30] = {'\0'};
    res_soc = recv(client.getSocket(), info, sizeof(info), 0);
    if( res_soc < 0 )
    {
        cerr << "Error with r get";
        exit(1);
    }
    else
        cout << "\033[1;31m" << info << "\033[0m" << endl;


    // No compulsory waiting data inr recv fucntion
    fcntl(client.getSocket(), F_SETFL, O_NONBLOCK);
    // Threads for receive/send messages
    thread th1(&Client::SendMessage, &client);
    thread th2(&Client::ReceiveMessage, &client);
    th1.join();
    th2.join();

    return 0;
}
