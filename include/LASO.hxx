//ADD LIBRAS
#ifndef INCLUDED_LASO_HXX
#define INCLUDED_LASO_HXX

#include <fstream>
#include <string>

#ifdef __linux__
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <limits.h>

    std::string enderecoLIBRASOfficeLinux(){
        char caminhoExe[PATH_MAX];
        /*Espelho que reflete sobre o processo que olha pra ele. Identifica o endereço do programa em execução*/
        bool readLink = readlink("/proc/self/exe", caminhoExe, PATH_MAX);
	    std::string caminhoDir = caminhoExe;
	    caminhoDir.erase(caminhoDir.begin() + caminhoDir.find("soffice"), caminhoDir.end());
	    return caminhoDir;
    }
    
    std::string enderecoLIBRASOfficeLinuxVar = enderecoLIBRASOfficeLinux();
    std::string LASO_LOG = enderecoLIBRASOfficeLinuxVar + "/LASO.log";
    std::string LASO_DEBUG = enderecoLIBRASOfficeLinuxVar + "/LASO_DEBUG.log";
	#define LASO_LOG_PATH LASO_LOG
	#define DBG_LASO_LOG_PATH LASO_DEBUG
#endif

#ifdef _WIN32
    #include <Windows.h>
    wchar_t enderecoLIBRASOffice[MAX_PATH];
    GetModuleFileName(NULL, enderecoLIBRASOffice, MAX_PATH);
    std::string endFinalLIBRASOffice = enderecoLIBRASOffice + "\\LASO.log";
    std::string endFinalLIBRASOfficeDebug = enderecoLIBRASOffice + "\\LASO_DEBUG.log";
	#define LASO_LOG_PATH endFinalLIBRASOffice
	#define DBG_LASO_LOG_PATH endFinalLIBRASOfficeDebug
#endif 
#endif
//END LIBRAS

