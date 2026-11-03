#ifndef SOCKET_TCP_H
#define SOCKET_TCP_H

#include <string>

class Socket_TCP
{
public:
    Socket_TCP();
    ~Socket_TCP();

    void open(std::string ip, int port);
    void close();

    bool is_open();

    void send(unsigned char* p_data, int size);
    void send(std::string str_data);

private:
    int m_socket;
    bool m_is_open;
};

#endif // SOCKET_TCP_H