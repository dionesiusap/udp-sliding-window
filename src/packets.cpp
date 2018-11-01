#include "packets.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const string CurrentTimestamp() {
    time_t now = time(0);
    struct tm tstruct;
    char str[80];
    tstruct = *localtime(&now);
    strftime(str, sizeof(str), "[%d/%m/%Y - %X] ", &tstruct);

    return str;
}

FramePacket* CreateFramePacket(unsigned int SequenceNumber, unsigned int DataLength, unsigned char Data[], unsigned char Checksum) {
    // size_t size = sizeof(FramePacket) - sizeof(FramePacket.Data);
    size_t size = 10;
    FramePacket* packet = (FramePacket*) malloc(size + DataLength * sizeof(unsigned char));

    packet->SOH = DEFAULT_SOH;
    packet->SequenceNumber = SequenceNumber;
    memcpy(packet->Data, Data, DataLength * sizeof(Data));
    packet->Checksum = Checksum;

    return packet;
}

ACKPacket* CreateACKPacket(unsigned int NextSequenceNumber, unsigned char Checksum) {
    ACKPacket* packet = (ACKPacket*) malloc(sizeof(ACKPacket));

    packet->ACK = DEFAULT_ACK;
    packet->NextSequenceNumber = NextSequenceNumber;
    packet->Checksum = Checksum;

    return packet;
}

unsigned char GeneratePacketChecksum(FramePacket packet) {
    unsigned char checksum = 0;
    checksum += SOH(packet);
    checksum += SequenceNumber(packet) & 0xFF;
    checksum += DataLength(packet);

    for (int i=0; i < DataLength(packet); ++i) {
        checksum += Data(packet)[i];
    }

    return checksum;
}

unsigned char GenerateACKChecksum(ACKPacket packet) {
    unsigned char checksum = 0;
    checksum += ACK(packet);
    checksum += NextSequenceNumber(packet) & 0xFF;
    return checksum;
}