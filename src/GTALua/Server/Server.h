#ifndef SERVER_H
#define SERVER_H

#include "Mongoose/mongoose.h"
#include <vector>
#include <time.h>
#include <string>

typedef char[48] ipAddr_t;

// =================================================================================
// Client descriptor
// =================================================================================
struct Client
{
    char* sName;
    char[64] sSessionID;
    ipAddr_t remoteAddress;
    time_t tLastMessage;
};

// =================================================================================
// Server configuration
// =================================================================================
struct ServerConfig
{
    bool bEnabled;
    int iPort;
    bool bUsePassword;
    std::string sPassword;
    std::string sACL;
};

// =================================================================================
// Server
// =================================================================================
class Server
{
public:
    Server();
    ~Server();
    
    // Allow connections
    void Init();
    void Close();
    
    void LoadServerIni();
    ServerConfig* GetConfig() {return &m_sConfig;}
private:
    bool m_bActive;
    int m_ConnectedClients
    ServerConfig m_sConfig;
    mg_server *m_mgServer;
};

// =================================================================================
// Global server instance
// =================================================================================

extern Server* g_pServer;
#endif