//
//  new_thread_server.c
//  TSS
//
//  Created by li haijin on 13-1-9.
//  Copyright (c) 2013年 li haijin. All rights reserved.
//

#include <stdio.h>
#include "Server.h"

void send_heart_beat_message(int fd) {
    char buf[BUF_SIZE];
    char *ptr = buf;

    while (1) {
    	printf("It's ok\n");
        memset(buf, '\0', BUF_SIZE);
        write(fd, "HB", BUF_SIZE);
	read(fd, buf, BUF_SIZE); 
	if (ptr == '\0') {
		printf("heart beat death.\n");
		exit(0);
	}
    }
    
}

