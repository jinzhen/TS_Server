#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#define BUF_SIZE 4096
#define BACKLOG 128


int
main (int argc, const char *argv[])
{
  int fd;
  unsigned short port;
  port = 8000;
  char *addr = "0.0.0.0";

//step 1:
  fd = get_sock_fd ();

  struct sockaddr_in my_addr;
  memset (&my_addr, 0, sizeof (my_addr));

//step 2:
  bind_addr (fd, addr, port, &my_addr);

//step 3:
  server_listen (fd, BACKLOG);


//step 4:
  int new_fd;
  struct sockaddr_in new_addr;
  memset (&new_addr, 0, sizeof (new_addr));
  socklen_t new_addr_len = 1;
  while (1)
    {
      if ((new_fd =
	   accept (fd, (struct sockaddr *) &new_addr, &new_addr_len)) == -1)
	{
	  perror ("accept error");
	  close (fd);
	}
      else
	{
#if 0
	  printf ("ok, get client :\n");
	  char str[] = "xxx.xxx.xxx.xxx\0";
	  inet_ntop (AF_INET, &new_addr.sin_addr, str, sizeof (str));
	  printf ("addr: %s\n", str);
#endif
	  server_client (new_fd);
	}
    }

  close (fd);

  return 0;
}
