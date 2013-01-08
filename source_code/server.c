#include <stdio.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#define BUF_SIZE 4096
#define P_NAME 1024
char path_name[P_NAME];		/* the name of file that server will send  */


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
#ifdef SO_REUSEPORT
  setsockopt (fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof (optval));
#endif
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
send_file (int new_fd)
{
  int fd;
  char buf[BUF_SIZE];


  if ((fd = open (path_name, O_RDONLY)) == -1)
    {
      perror ("send open error");
      exit (1);
    }
  int n = 0;
  while ((n = read (fd, buf, BUF_SIZE)) != 0)
    {
      write (new_fd, buf, n);
    }

}

void
get_file (int new_fd)
{
  int fd;
  char buf[BUF_SIZE];
  if ((fd = open (path_name, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
    {
      perror ("get open error");
    }

  int n = 0;
  while ((n = read (new_fd, buf, BUF_SIZE)) > 0)
    {
      write (fd, buf, n);
    }

}

void
server_client (int new_fd)
{
  int mode = -1;
  char quest_msg[BUF_SIZE];
  memset (quest_msg, '\0', BUF_SIZE);

  read (new_fd, quest_msg, BUF_SIZE);
  printf ("quest_msg:|%s\n", quest_msg);

  mode = analysize (quest_msg);
  switch (mode)
    {
    case 0:
      write (new_fd, "OK\0", 3);
      send_file (new_fd);
      break;
    case 1:
      write (new_fd, "OK\0", 3);
      get_file (new_fd);
      break;
    default:
      printf ("error mode\n");
      break;
    }

  return;

}
