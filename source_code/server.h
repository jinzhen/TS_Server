//
//  Server.h
//  TSS
//
//  Created by li haijin on 13-1-9.
//  Copyright (c) 2013年 li haijin. All rights reserved.
//

#ifndef COMMON_H
#define COMMON_H

#include "common.h"

int get_sock_fd();

void bind_addr(int fd, const char *addr, unsigned short port, struct sockaddr_in *my_addr);

void server_listen(int fd, int backlog);

void server_client(int new_fd);

int analysize(char *quest);

void sig_int(int signo);
void sig_chld(int signo);







#endif
