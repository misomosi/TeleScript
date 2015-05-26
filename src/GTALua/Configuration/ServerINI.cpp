// =================================================================================
// Includes
// =================================================================================
#include "Includes.h"
#include "Server.h"
#include "UTIL/UTIL.h"

// =================================================================================
// Parser
// =================================================================================
int ini_server_parser(void* pCustom, const char* sSection, const char* sName, const char* sValue)
{
    // Server
    if (strcasecmp(sSection, "Server") == 0)
    {
        ServerConfig *config = (ServerConfig*) pCustom;
        // Enabled
        if (strcasecmp(sName, "Enabled") == 0)
        {
            config->bEnabled = strcasecmp(sValue, "true") == 0;
        }
        
        // Port
        if (strcasecmp(sName, "Port") == 0)
        {
            config->iPort = atoi(sValue);
        }
        // Password
        if (strcasecmp(sName, "PasswordProtected") == 0)
        {
            config->bUsePassword = strcasecmp(sValue, "true") == 0;
        }
        if (strcasecmp(sName, "Password") == 0)
        {
            config->sPassword = std::string(sValue);
        }
        
        // IP whitelist
        // (use access_control_list for mongoose)
        if (strcasecmp(sName, "AccessControlList") == 0)
        {
            config->sACL = std::string(sValue);
        }
    }
}

// =================================================================================
// Load
// =================================================================================
void Server::LoadServerIni()
{
    *GetConfig() = {0}; // Shorthand for memset(0)
    IniFile file("GTALua/gtalua.ini", ini_server_parser, GetConfig());
}