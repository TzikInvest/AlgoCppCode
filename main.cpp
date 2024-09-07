#include <iostream>
#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EClientSocket.h"

class MyClient : public EWrapper {
private:
    EReaderOSSignal m_osSignal;
    EClientSocket *m_pClient;

public:
    MyClient() : m_osSignal(2000)  // 2-second timeout
    {
        m_pClient = new EClientSocket(this, &m_osSignal);
    }

    ~MyClient() {
        if (m_pClient) {
            delete m_pClient;
        }
    }

    bool connect(const char *host, int port, int clientId) {
        bool bRes = m_pClient->eConnect(host, port, clientId, false);
        if (bRes) {
            std::cout << "Connected to TWS" << std::endl;
            return true;
        }
        else {
            std::cout << "Failed to connect to TWS" << std::endl;
            return false;
        }
    }

    void disconnect() const {
        m_pClient->eDisconnect();
        std::cout << "Disconnected from TWS" << std::endl;
    }

    EClient* client() {
        return m_pClient;
    }

    // Implement necessary EWrapper virtual functions
    void error(int id, int errorCode, const std::string& errorString) override {
        std::cout << "Error: " << id << " " << errorCode << " " << errorString << std::endl;
    }

    void connectionClosed() override {
        std::cout << "Connection closed" << std::endl;
    }

    // Implement other necessary EWrapper functions...
};

int main() {
    MyClient client;

    // Connect to IB Gateway or TWS
    // Replace with your connection details
    const char* host = "127.0.0.1";  // localhost
    int port = 7496;  // TWS port (use 7497 for IB Gateway)
    int clientId = 0;

    if (client.connect(host, port, clientId)) {
        // Connection successful, you can now make API calls

        // For example, to request account updates:
        client.client()->reqAccountUpdates(true, "");

        // Keep the connection alive for a while
        std::this_thread::sleep_for(std::chrono::seconds(10));

        // Disconnect
        client.disconnect();
    }

    return 0;
}