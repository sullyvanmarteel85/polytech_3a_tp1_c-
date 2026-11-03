#include "socket.h"

#include <iostream>
#include <cstring>
#include <cerrno>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

Socket_TCP::Socket_TCP()
    : m_socket(-1),
      m_is_open(false)
{
}

Socket_TCP::~Socket_TCP()
{
    close();
}

void Socket_TCP::open(std::string ip, int port)
{
    // Si un socket est déjà ouvert, on le ferme
    if (m_is_open)
    {
        close();
    }

    // Création du socket TCP
    m_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (m_socket < 0)
    {
        std::cerr << "Erreur socket() : "
                  << strerror(errno) << std::endl;
        return;
    }

    // Configuration de l'adresse distante
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &server_address.sin_addr) <= 0)
    {
        std::cerr << "Adresse IP invalide : "
                  << ip << std::endl;

        ::close(m_socket);
        m_socket = -1;
        return;
    }

    // Connexion au serveur
    if (connect(m_socket,
                reinterpret_cast<sockaddr*>(&server_address),
                sizeof(server_address)) < 0)
    {
        std::cerr << "Erreur connect() : "
                  << strerror(errno) << std::endl;

        ::close(m_socket);
        m_socket = -1;
        return;
    }

    m_is_open = true;

    std::cout << "Connexion TCP établie avec "
              << ip << ":" << port << std::endl;
}

void Socket_TCP::close()
{
    if (m_socket >= 0)
    {
        ::close(m_socket);
        m_socket = -1;
    }

    m_is_open = false;
}

bool Socket_TCP::is_open()
{
    return m_is_open;
}

void Socket_TCP::send(unsigned char* p_data, int size)
{
    if (!m_is_open)
    {
        std::cerr << "Socket TCP non ouverte" << std::endl;
        return;
    }

    if (p_data == nullptr || size <= 0)
    {
        std::cerr << "Données invalides" << std::endl;
        return;
    }

    int total_sent = 0;

    while (total_sent < size)
    {
        ssize_t result = ::send(
            m_socket,
            p_data + total_sent,
            size - total_sent,
            MSG_NOSIGNAL
        );

        if (result < 0)
        {
            std::cerr << "Erreur send() : "
                      << strerror(errno) << std::endl;

            // Le serveur distant a probablement fermé la connexion
            if (errno == EPIPE || errno == ECONNRESET)
            {
                m_is_open = false;
            }

            return;
        }

        if (result == 0)
        {
            std::cerr << "Connexion TCP fermée par le correspondant"
                      << std::endl;

            m_is_open = false;
            return;
        }

        total_sent += result;
    }
}

void Socket_TCP::send(std::string str_data)
{
    if (str_data.empty())
    {
        return;
    }

    send(
        reinterpret_cast<unsigned char*>(
            const_cast<char*>(str_data.data())
        ),
        static_cast<int>(str_data.size())
    );
}