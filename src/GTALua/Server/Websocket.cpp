#include "Server.h"

int Server::ServeWebsocketRequest(struct mg_connection *conn)
{
	// Most browsers send an empty "heartbeat" to keep the connection open
	if (conn->content_len == 0)
		return MG_TRUE;
	// Echo
	printf("Websocket %p request %s of len %d\n", conn, conn->content, conn->content_len);
	mg_websocket_write(conn, 1, conn->content, conn->content_len);
    return MG_TRUE;
}

int Server::OpenWebsocket(struct mg_connection *conn)
{
	printf("Opening websocket\n");
	return MG_FALSE;
}

int Server::CloseWebsocket(struct mg_connection *conn)
{
	printf("Closing websocket\n");
	return MG_TRUE;
}