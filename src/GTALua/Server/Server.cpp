#include "Server.h"
#include "Includes.h"

static void ThreadInit(LPVOID param)
{
	Server* server = (Server*)param;
	server->PollThread();
}

// ctor
Server::Server()
{
    
}

// dtor
Server::~Server()
{
	if (m_bEnabled)
	{
		Close();
	}
}

// Function that handles server lifecycle and events
void Server::PollThread()
{
	// Initialize the server. Server::event_handler handles dynamic requests
	m_mgServer = mg_create_server(this, Server::event_handler);
	if (m_mgServer == NULL)
	{
		printf("[Server] Failed to initialize! Out of memory.\n");
		return;
	}

	// Serve content only from docroot
	const char* err = mg_set_option(m_mgServer, "document_root", "GTALua/docroot/");
	if (err)
	{
		printf("[Server] Error setting document_root: %s\n", err);
		mg_destroy_server(&m_mgServer);
		return;
	}

	// mg_set_option only takes string value arguments, so convert port to string
	char portStr[6];
	_itoa_s<sizeof(portStr)>(m_sConfig.iPort, portStr, 10);
	err = mg_set_option(m_mgServer, "listening_port", portStr);
	if (err)
	{
		printf("[Server] Error setting listening_port: %s\n", err);
		mg_destroy_server(&m_mgServer);
		return;
	}
	// Optionally set what IPs can access the server
	// see http://cesanta.com/docs/Options.shtml#access_control_list for more info
	if (!m_sConfig.sACL.empty())
	{
		mg_set_option(m_mgServer, "access_control_list", m_sConfig.sACL.c_str());
	}

	printf("[Server] initialized.\n");

	// Polling loop. Server can be disabled here, or from another thread provided we've syncronized on m_bEnabled.
	m_bActive = true;
	while (m_bEnabled)
	{
		mg_poll_server(m_mgServer, 1000);
	}
	
	// Teardown phase
	m_bActive = false;
	if (m_mgServer)
	{
		mg_destroy_server(&m_mgServer);
	}
}

void Server::Init()
{
	// Server config section from GTALua.ini
	LoadServerIni();

	SetEnabled(m_sConfig.bEnabled);
}

void Server::SetEnabled(bool enabled)
{
	if (enabled == m_bEnabled)
		return;
	if (enabled)
		Open();
	else
		Close();
}

void Server::Open()
{
	printf("Starting server on port %d\n", m_sConfig.iPort);

	m_bEnabled = true;

	// Start the server update thread
	m_pollThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadInit, this, 0, 0);
}

void Server::Close()
{
	printf("[Server] Shutting down the server.\n");
	m_bEnabled = false;
	
	// Wait until the server thread exits cleanly...
	long rval = WaitForSingleObject(m_pollThread, 2000);
	switch (rval)
	{
	case WAIT_OBJECT_0:
		printf("[Server] Successfully shut down.\n"); break;
	case WAIT_TIMEOUT:
		printf("[Server] Timed out waiting for server shutdown.\n"); break;
	case WAIT_FAILED:
	default:
		printf("[Server] Error shutting down the server. (Error 0x%x)\n", GetLastError()); break;
	}
}
