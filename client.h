#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <string>
#include <mutex>

class Client
{
private:
    std::string user_name;
    // Socket descriptor
    int soc_var;
    sockaddr_in peer;
public:
    Client();
    Client(std::string name, int socket, sockaddr_in peer_info);
    ~Client();

    Client(const Client&) = delete;
    const Client& operator=(const Client&) = delete;

    inline void setName(const std::string& _name) { user_name = _name; }
    inline void setSocket(int descriptor) { soc_var = descriptor; }
    inline void setSocketDefinition(const sockaddr_in& _peer) { peer = _peer; }

    inline const std::string& getName() { return user_name; }
    inline int getSocket() { return soc_var; }
    inline const sockaddr_in& getSocketDefinition() { return peer; }


    // Receive Message from server (other users)
    void ReceiveMessage();

    // Send Message to server (other users)
    void SendMessage();

    // Variable for exit
    bool do_exit = false;
    std::mutex do_exit_mutex;
};












 #endif // CLIENT_H_INCLUDED
