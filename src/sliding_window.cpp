#include "sliding_window.h"
#include <stdlib.h>

SendingWindow* CreateSendingWindow(unsigned int WindowSize) {
    SendingWindow* s = (SendingWindow*) malloc(sizeof(SendingWindow));

    s->SendingWindowSize = WindowSize;
    s->LastAckReceived = NONE;
    s->LastFrameSent = NONE;
}

SendingWindow* CreateSendingWindow(unsigned int WindowSize, unsigned int LastAckReceived, unsigned int LastFrameSent) {
    SendingWindow* s = (SendingWindow*) malloc(sizeof(SendingWindow));

    s->SendingWindowSize = WindowSize;
    s->LastAckReceived = LastAckReceived;
    s->LastFrameSent = LastFrameSent;
}

void createNew(SendingWindow *s, unsigned int windowSize) {
    s->SendingWindowSize = windowSize;
    s->LastAckReceived = NONE;
    s->LastFrameSent = NONE;
}

void createNewSendingWindow(SendingWindow *s, unsigned int windowSize, unsigned int lastAckReceived, unsigned int lastFrameSent) {
    s->SendingWindowSize = windowSize;
    s->LastAckReceived = lastAckReceived;
    s->LastFrameSent = lastFrameSent;
}

void ReceiveACK(SendingWindow *s, int ACK) {
    if (s->LastAckReceived < ACK) {
        s->LastAckReceived = ACK;
    }
}

void SendFrames(SendingWindow s, int FrameCount) {
    if (FrameCount > SWS(s)) {
        FrameCount = SWS(s);
    }

    if (LFS(s) + FrameCount > SWS(s) + LAR(s)) {
        FrameCount = SWS(s) + LAR(s) - LFS(s);
    }

    LFS(s) += FrameCount;
}