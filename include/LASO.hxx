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
    char caminhoExe[PATH_MAX];
    bool readLink = readlink("/proc/self/exe", caminhoExe, PATH_MAX);
    std::string caminhoDir = caminhoExe;
    caminhoDir.erase(caminhoDir.begin() + caminhoDir.find("soffice"), caminhoDir.end());
    std::string LASO_LOG = caminhoDir + "/LASO.log"
    std::string LASO_DEBUG = caminhoDir + "/LASO_DEBUG.log"
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

