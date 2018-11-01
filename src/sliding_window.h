#ifndef SLIDING_WINDOW_H
#define SLIDING_WINDOW_H

typedef struct {
    unsigned int SendingWindowSize;
    unsigned int LastAckReceived;
    unsigned int LastFrameSent;
} SendingWindow;

#define NONE 0

#define SWS(S) (S).SendingWindowSize
#define LAR(S) (S).LastAckReceived
#define LFS(S) (S).LastFrameSent

// Don't know which one is more convenient for the future:
//     function returns SendingWindow or procedure with SendingWindow input
SendingWindow* CreateSendingWindow(unsigned int WindowSize);
SendingWindow* CreateSendingWindow(unsigned int WindowSize, unsigned int LastAckReceived, unsigned int LastFrameSent);
void NewSendingWindow(SendingWindow *s, unsigned int WindowSize);
void NewSendingWindow(SendingWindow *s, unsigned int WindowSize, unsigned int LastAckReceived, unsigned int LastFrameSent);
void ReceiveACK(SendingWindow *s, int ACK);
void SendFrames(SendingWindow s, int FrameCount);

#endif