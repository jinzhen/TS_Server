//
//  common.h
//  TSS
//
//  Created by li haijin on 13-1-9.
//  Copyright (c) 2013年 li haijin. All rights reserved.
//

#ifndef TSS_common_h
#define TSS_common_h

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
#include <netinet/in.h>




#define TS_PORT 8000
#define TS_SERVER_ADDRESS "0.0.0.0"

#define BUF_SIZE 4096
#define BACKLOG 128

#define P_NAME 1024
char path_name[P_NAME];		/* the name of file that server will send  */

#define MESSAGE_HEART_BEAT_TYPE 0

#endif
