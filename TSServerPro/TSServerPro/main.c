//
//  main.c
//  TSServerPro
//
//  Created by li haijin on 13-1-24.
//  Copyright (c) 2013年 li haijin. All rights reserved.
//

#include "server.h"
#include <errno.h>

int
main (int argc, const char *argv[])
{
    int fd;
    unsigned short port;
    port = TS_PORT;
    char *addr = TS_SERVER_ADDRESS;
    pid_t child_pid;
    
    //step 1:
    fd = get_sock_fd ();
    
    struct sockaddr_in my_addr;
    memset (&my_addr, 0, sizeof (my_addr));
    
    //step 2:
    bind_addr (fd, addr, port, &my_addr);
    
    //step 3:
    server_listen (fd, BACKLOG);
    
    signal(SIGCHLD, sig_chld);
    
    //step 4:
    int new_fd;
    struct sockaddr_in new_addr;
    memset (&new_addr, 0, sizeof (new_addr));
    socklen_t new_addr_len = 1;
    
    signal(SIGINT, sig_int);
    
    while (1)
    {
        if ((new_fd =
             accept (fd, (struct sockaddr *) &new_addr, &new_addr_len)) == -1)
        {
            if (errno == EINTR) {
                continue;
            }else {
                perror ("accept error");
                close (fd);
            }
        }
        else
        {
            if ((child_pid = fork()) == 0) {
                close(fd);
                server_client (new_fd);
                exit(0);
            }
            close(new_fd);
        }
    }
    
    return 0;
}

