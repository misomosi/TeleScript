#ifndef SERVER_H
#define SERVER_H

// =================================================================================
// Server
// =================================================================================
struct Client
{
    
};

// =================================================================================
// Server
// =================================================================================

class Server
{
public:
    Server();
    ~Server()
    
    void LoadServerIni();
private:
    bool m_bActive;
    int m_ConnectedClients
};

#endif