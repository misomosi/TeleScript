#include "Server.h"

// Callback for handling server requests and events
// (This is how we serve dynamic content)
int Server::event_handler(struct mg_connection *conn, enum mg_event ev)
{
	// The server that opened this connection
	Server *server = (Server*)conn->server_param;

	if (ev == MG_AUTH)
	{
		return MG_TRUE;   // Authorize all requests
	}
	else 
	{
		return MG_FALSE;
	}
}