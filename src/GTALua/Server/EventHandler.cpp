#include "Server.h"

// Callback for handling server requests and events
// (This is how we serve dynamic content)
int Server::event_handler(struct mg_connection *conn, enum mg_event ev)
{
	// The server that opened this connection
	Server *server = (Server*)conn->server_param;
    
    switch (ev) {
        // Request authorization
        case MG_AUTH:
            return MG_TRUE; // For now, authorize all events
            break;

		// Client is attempting to establish a websocket
		case MG_WS_CONNECT:
			return OpenWebsocket(conn);
			break;

        // GET or PUT or POST or whatever request
        case MG_REQUEST:
        {
            if (conn->is_websocket) {
                return ServeWebsocketRequest(conn);
            }
            else
            {
                if (ServeRESTRequest(conn))
                {
                    return MG_TRUE;
                }
                else
                {
                    // If all 3 methods of serving dynamic content fails,
                    // return false to fall back to serving static files
                    return ServeTemplateHTMLRequest(conn);
                }
            }
        }
            break;
        // Ignore POLL events
        case MG_POLL:
            return MG_FALSE;
            break;
        // HTTP error event
        case MG_HTTP_ERROR:
            return MG_FALSE;
            break;
        // Connection close event
        case MG_CLOSE:
			if (conn->is_websocket) {
				return CloseWebsocket(conn);
			}
            return MG_FALSE;
            break;
		default:
			return MG_FALSE;
			break;
    }
}