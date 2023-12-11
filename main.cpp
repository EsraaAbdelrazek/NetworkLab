#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Sender
class Sender {
private:
    int windowSize;
    int base;
    int nextSeqNum;
    int totalPackets;
    bool* acks;

public:
    Sender(int wSize, int total) : windowSize(wSize), base(0), nextSeqNum(0), totalPackets(total) {
        acks = new bool[total];
        for (int i = 0; i < total; ++i)
            acks[i] = false;
    }

    void send() {
        while (base < totalPackets) {
            int packetsToSend = min(windowSize, totalPackets - base);
            for (int i = 0; i < packetsToSend; ++i) {
                if (!acks[base + i]) {
                    cout << "Sender: Sending packet " << base + i << endl;
                    acks[base + i] = true;
                }
            }

            int timeout = rand() % 2; // Simulating some processing time before timeout
            if (timeout == 0) {
                cout << "Sender: Timeout occurred, resending window starting from " << base << endl;
                break;
            }

            for (int i = 0; i < packetsToSend; ++i) {
                if (acks[base]) {
                    cout << "Sender: Received ACK for packet " << base << endl;
                    base++;
                } else {
                    cout << "Sender: Waiting for ACK of packet " << base << endl;
                    break;
                }
            }
        }
    }
};

// Receiver
class Receiver {
private:
    int base;
    int totalPackets;
    bool* recvd;

public:
    Receiver(int total) : base(0), totalPackets(total) {
        recvd = new bool[total];
        for (int i = 0; i < total; ++i)
            recvd[i] = false;
    }

    void receive() {
        while (base < totalPackets) {
            int packet = rand() % totalPackets; // Simulating reception of packets
            cout << "Receiver: Received packet " << packet << endl;
            recvd[packet] = true;

            if (packet == base) {
                cout << "Receiver: Sending ACK for packet " << base << endl;
                base++;
            } else {
                cout << "Receiver: Waiting for packet " << base << endl;
            }
        }
    }
};

int main() {
    srand(time(0));

    int totalPackets = 10;
    int windowSize = 3;

    Sender sender(windowSize, totalPackets);
    Receiver receiver(totalPackets);

    cout << "Simulation Start:" << endl;
    sender.send();
    receiver.receive();

    return 0;
}
