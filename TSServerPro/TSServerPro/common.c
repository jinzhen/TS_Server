//
//  common.c
//  TSServerPro
//
//  Created by li haijin on 13-1-24.
//  Copyright (c) 2013年 li haijin. All rights reserved.
//

#include <stdio.h>
#include "common.h"

PacketStruct *init_packet (PACKET_TYPE type, const char *data) {
    PacketStruct *packet = (PacketStruct *)malloc(sizeof(PacketStruct) * 1);
    
    packet->type = type;
    
    size_t data_lenth = strlen(data) + 5 + 1;
    packet->length = data_lenth;
    
    packet->data = (char *)malloc(sizeof(char) * data_lenth);
    strcpy(packet->data, data);
    
    return packet;
}

ssize_t send_packet (int fd, const PacketStruct *packet) {
    size_t length = packet->length;
    char buf[length];
    char *ptr = buf;
    
    *ptr++ = packet->type;

    sprintf(ptr, "%zd", packet->length);
    ptr += sizeof(size_t);
    
    strcpy(ptr, packet->data);
    ptr += strlen(packet->data);
    
    return send(fd, buf, length, 0);
    
}

PacketStruct *recv_packet (int fd, char *buf, size_t len, int n) {
    recv(fd, buf, len, n);
    return analysize_data(buf);
}

