#ifndef _PACKETS_H_
#define _PACKETS_H_

#include <string>
#include <stdint.h>

using namespace std;

typedef struct
{
    unsigned char SOH;
    unsigned int SequenceNumber;
    unsigned int DataLength;
    unsigned char Data[];
    unsigned char Checksum;
} FramePacket;

typedef struct
{
    unsigned char ACK;
    unsigned int NextSequenceNumber;
    unsigned char Checksum;
} ACKPacket;

#define DEFAULT_SOH 0x1;
#define DEFAULT_ACK 0x3;
#define MAX_DATA_SIZE 1024;

#define SOH(FramePacket) ((FramePacket).SOH)
#define SequenceNumber(FramePacket) ((FramePacket).SequenceNumber)
#define DataLength(FramePacket) ((FramePacket).DataLength)
#define Data(FramePacket) ((FramePacket).Data)
#define Checksum(FramePacket) ((FramePacket).Checksum)
#define ACK(ACKPacket) ((ACKPacket).ACK)
#define NextSequenceNumber(ACKPacket) ((ACKPacket).NextSequenceNumber)
#define Checksum(ACKPacket) ((ACKPacket).Checksum)

const string CurrentTimestamp();
FramePacket* CreateFramePacket(unsigned int SequenceNumber, unsigned int DataLength, unsigned char Data[], unsigned char Checksum);
ACKPacket* CreateACKPacket(unsigned int NextSequenceNumber, unsigned char Checksum);
unsigned char GeneratePacketChecksum(FramePacket packet);
unsigned char GenerateACKChecksum(ACKPacket packet);

#endif