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
    while (1) {
        write(fd, "HB", BUF_SIZE);
    }
    
}

