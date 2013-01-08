#ifndef COMMON_H
#define COMMON_H

int get_sock_fd();

void bind_addr(int fd, const char *addr, unsigned short port, struct sockaddr_in *my_addr);

void server_listen(int fd, int backlog);

void server_client(int new_fd);

int analysize(char *quest);

void send_file(int new_fd);
void get_file(int new_fd);







#endif
