// =================================================================================
// Includes
// =================================================================================
#include "Includes.h"
#include "Server.h"
#include "UTIL/UTIL.h"
#include <string.h>

// =================================================================================
// Parser
// =================================================================================
int ini_server_parser(void* pCustom, const char* sSection, const char* sName, const char* sValue)
{
    // Server
	if (_stricmp(sSection, "Server") == 0)
    {
        ServerConfig *config = (ServerConfig*) pCustom;
        // Enabled
		if (_stricmp(sName, "Enabled") == 0)
        {
			config->bEnabled = _stricmp(sValue, "true") == 0;
        }
        
        // Port
		if (_stricmp(sName, "Port") == 0)
        {
            config->iPort = atoi(sValue);
        }
        // Password
		if (_stricmp(sName, "PasswordProtected") == 0)
        {
			config->bUsePassword = _stricmp(sValue, "true") == 0;
        }
		if (_stricmp(sName, "Password") == 0)
        {
            config->sPassword = std::string(sValue);
        }
        
        // IP whitelist
        // (use access_control_list for mongoose)
		if (_stricmp(sName, "AccessControlList") == 0)
        {
            config->sACL = std::string(sValue);
        }
    }
	return 1;
}

// =================================================================================
// Load
// =================================================================================
void Server::LoadServerIni()
{
    *GetConfig() = {0}; // Shorthand for memset(0)
    IniFile file("GTALua/gtalua.ini", ini_server_parser, GetConfig());
}