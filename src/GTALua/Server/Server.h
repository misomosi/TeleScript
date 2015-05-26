#ifndef SERVER_H
#define SERVER_H

#include "Mongoose/mongoose.h"
#include <vector>
#include <time.h>
#include <string>

//typedef char[48] ipAddr_t;

// =================================================================================
// Client descriptor
// =================================================================================
struct Client
{
    char* sName;
    char sSessionID [64];
    char remoteAddress[48];
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
   
    void Init();

	bool IsActive() { return m_bActive; }

	// allow client connections
	void SetEnabled(bool enabled);
	void Open();
    void Close();

	// Handles any outstanding events (perhaps we should do this from a separate thread?)
	void PollThread();
    
    void LoadServerIni();
    ServerConfig* GetConfig() {return &m_sConfig;}
private:
    bool m_bEnabled; // TODO: this might need a mutex
	bool m_bActive; // Is the server actually running?
	int m_ConnectedClients;
    ServerConfig m_sConfig;
    mg_server *m_mgServer;
	void* m_pollThread;
	// function for processing connection requests and events
	static int event_handler(struct mg_connection *conn, enum mg_event ev);
};

// =================================================================================
// Global server instance
// =================================================================================

extern Server* g_pServer;
#endif