//
//  data_analysize.c
//  TSServerPro
//
//  Created by li haijin on 13-1-24.
//  Copyright (c) 2013年 li haijin. All rights reserved.
//

#include <stdio.h>
#include "common.h"


PacketStruct* analysize_data (const char *data) {
    PacketStruct *packet = (PacketStruct *)malloc(sizeof(PacketStruct) * 1);
    
    const char *ptr = data;
    packet->type = *ptr;
    
    size_t data_lenth = strlen(data);
    packet->length = data_lenth;
    
    packet->data = (char *)malloc(sizeof(char) * data_lenth);
    strcpy(packet->data, data);
    
    ptr = NULL;

    return packet;
}

PACKET_TYPE analysize_packet (const PacketStruct *packet) {
    
    return packet->type;
}