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
    
	#define LASO_LOG_PATH enderecoLIBRASOfficeLinux() + "/LASO.log"
	#define DBG_LASO_LOG_PATH enderecoLIBRASOfficeLinux() + "/LASO_DEBUG.log"
#endif

#ifdef _WIN32
    #include <Windows.h>
    wchar_t enderecoLIBRASOffice[MAX_PATH];
    GetModuleFileName(NULL, enderecoLIBRASOffice, MAX_PATH);
    extern std::string endFinalLIBRASOffice = enderecoLIBRASOffice + "\\LASO.log";
    extern std::string endFinalLIBRASOfficeDebug = enderecoLIBRASOffice + "\\LASO_DEBUG.log";
	extern std::string LASO_LOG_PATH endFinalLIBRASOffice;
	extern std:: DBG_LASO_LOG_PATH endFinalLIBRASOfficeDebug;
#endif 
#endif
//END LIBRAS

