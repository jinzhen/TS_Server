//
//  Server.m
//  TSS
//
//  Created by li haijin on 13-1-9.
//  Copyright (c) 2013年 li haijin. All rights reserved.
//

#include "server.h"

void
pr_cpu_time(void) {
    double user, sys;
    struct rusage myusage, childusage;
    
    if (getrusage(RUSAGE_SELF, &myusage)) {
        printf("getrusage error on myusage");
    }
    if (getrusage(RUSAGE_CHILDREN, &childusage)) {
        printf("getrusage error on childusage");
    }
    
    user = (double)myusage.ru_utime.tv_sec + myusage.ru_utime.tv_usec / 1000000.0;
    user += (double)childusage.ru_utime.tv_sec + childusage.ru_utime.tv_usec / 1000000.0;
    sys = (double)myusage.ru_stime.tv_sec + myusage.ru_stime.tv_usec / 1000000.0;
    sys += (double)childusage.ru_stime.tv_sec + childusage.ru_stime.tv_usec / 1000000.0;
    printf("\nuser time : %g, sys time : %g", user, sys);
}


void
sig_int(int signo) {
    void pr_cpu_time(void);
    pr_cpu_time();
    exit(0);
}

void
sig_chld(int signo) {
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, 0)) > 0);
}

/* get the fd of the socket */
int
get_sock_fd ()
{
    int fd;
    if ((fd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror ("socket error");
        exit (1);
    }
    return fd;
}

/* bind server addr and deal with the I/O, address reused */
void
bind_addr (int fd, const char *addr, unsigned short port,
           struct sockaddr_in *my_addr)
{
#if 0
    int optval = 1;
    if (setsockopt (fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (optval)) ==
        -1)
    {
        perror ("setsockopt error");
        exit (1);
    }
#endif
    my_addr->sin_family = AF_INET;
    my_addr->sin_port = htons (port);
    inet_pton (PF_INET, addr, (void *) &my_addr->sin_addr);
    
    if ((bind (fd, (struct sockaddr *) my_addr, sizeof (*my_addr))) < 0)
    {
        perror ("bind error");
        exit (1);
    }
}

/* server listen  */
void
server_listen (int fd, int backlog)
{
    if (listen (fd, backlog) < 0)
    {
        perror ("listen error");
        exit (1);
    }
}

int
analysize (char *quest)
{
    char *ptr = NULL;
    ptr = quest;
    memset (path_name, '\0', P_NAME);
    if (*ptr == '0')
    {
        strtok (quest, " ");
        char *name = strtok (NULL, "\0");
        strcpy (path_name, name);
        
        return 0;
    }
    else if (*ptr == '1')
    {
        strtok (quest, " ");
        char *name = strtok (NULL, "\0");
        strcpy (path_name, name);
        
        return 1;
    }
    else
    {
        return -1;
    }
}


void
server_client (int new_fd)
{
    char quest_msg[BUF_SIZE];
    while(1) {
	    memset (quest_msg, '\0', BUF_SIZE);
	    ssize_t n = recv (new_fd, quest_msg, BUF_SIZE, 0);
	    printf ("read quest_msg:|%zd, %s|\n", n, quest_msg);
	    send (new_fd, quest_msg, n, 0);

	//    send_heart_beat_message(new_fd);
    }

    return;
    
}
