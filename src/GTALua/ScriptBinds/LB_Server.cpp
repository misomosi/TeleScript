// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "Server.h"
#include "lua/Lua.h"
#include "ScriptBinds.h"

// =================================================================================
// Start server
// =================================================================================
static int LB_StartServer()
{
	if (g_pServer)
	{
		g_pServer->SetEnabled(true);
		return 1;
	}
	return 0;
}

// =================================================================================
// Stop server
// =================================================================================
static int LB_StopServer()
{
	if (g_pServer)
	{
		g_pServer->SetEnabled(false);
		return 1;
	}
	return 0;
}

// =================================================================================
// Get server status
// =================================================================================
static const char* LB_ServerStatus()
{
	if (g_pServer == NULL)
	{
		return "Uninitialized";
	}
	else
	{
		return (g_pServer->IsActive()) ? "Running" : "Not running";
	}
	
}

// =================================================================================
// Lua binding
// =================================================================================
void ScriptBinds::Server::Bind()
{
	luabind::module(lua->State(), "server")
	[
		luabind::def("Start", LB_StartServer),
		luabind::def("Stop", LB_StopServer),
		luabind::def("Status", LB_ServerStatus),
		luabind::def("start", LB_StartServer),
		luabind::def("stop", LB_StopServer),
		luabind::def("status", LB_ServerStatus)
	];
}