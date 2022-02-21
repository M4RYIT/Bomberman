#include "bomberman.h"
#include <stdio.h>

int net_init(net *n, const char *serv_addr)
{
    WSADATA wsa_data;
    if (WSAStartup(0x0202, &wsa_data)) return 0;

    n->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (n->socket < 0) return 0;

    inet_pton(AF_INET, serv_addr, &(n->server.sin_addr));
    n->server.sin_family = AF_INET;
    n->server.sin_port = htons(9999);

    n->server_size = sizeof(n->server);

    return 1;
}

int net_noblock_mode(net *n, unsigned long nb_mode)
{
    if(ioctlsocket(n->socket, FIONBIO, &nb_mode)) return 0;

    return 1;
}

int net_recv(net *n, int recv_size)
{
    return recvfrom(n->socket, n->recv_buffer, recv_size, 0, (struct sockaddr*)&n->server, &n->server_size)>0?1:0;
}

int net_send(net *n, int send_size)
{
    return sendto(n->socket, n->send_buffer, send_size, 0, (struct sockaddr*)&n->server, n->server_size)>0?1:0;
}

void set_send_buffer(net *n, void *value, size_t sz)
{
    memcpy(n->send_buffer, value, sz);
}

void get_recv_buffer(net *n, void *value, size_t sz)
{
    memcpy(value, n->recv_buffer, sz);
}

int net_update(net *n)
{
    static double timer = 0;
    timer += delta_time();

    if (timer > (double)(n->update_rate))
    {
        timer = 0;
        return 1;
    }

    return 0;
}

void net_free(net *n)
{
    closesocket(n->socket);
    free(n);
}