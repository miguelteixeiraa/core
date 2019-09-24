//ADD LIBRAS
#ifndef INITLASOLINUX_HXX
#define INITLASOLINUX_HXX

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <string>
#include <fstream>


void linuxCreateProcessJar(const std::string enderecoDoJar){
    int pid = fork(); //Cria processo filho
    if(pid == 0){
        setsid();
        int pid2 = fork(); //Cria processo neto
        if(pid2 == 0){
            close(0); //stdin
            close(1); //stdout
            //close(2); //stderr
            umask(0);
            chdir("/");
            execlp("java", "java", "-jar", enderecoDoJar.c_str(), (char *)NULL); // inicia librasoffice.jar
            printf("Erro execlp %d: %s\n", errno, strerror(errno)); // caso essa linha seja lida, ocorreu algum erro no execlp
            _exit(0);
        }
    }
    else{
        printf("Não foi possível criar um processo filho para librasoffice.jar");
        _exit(0);
    }
}

std::string enderecoLIBRASOfficeJar(){
    char caminhoExe[PATH_MAX];
    /*Espelho que reflete sobre o processo que olha pra ele. Identifica o endereço do programa em execução*/
    bool readLink = readlink("/proc/self/exe", caminhoExe, PATH_MAX);
	std::string caminhoDir = caminhoExe;
	caminhoDir.erase(caminhoDir.begin() + caminhoDir.find("soffice"), caminhoDir.end());
	return caminhoDir + "librasoffice.jar";
}

/*
bool mataProcessoLASOFront(const unsigned int &killPidInfo){
    std::string killProcesso = "kill " + std::to_string(killPidInfo);
    return system(killProcesso.c_str());
}*/

void  mataProcessoLASOFront(){
    system("jps > /tmp/LASOPid.txt"); //Lista pid e nome de processos instanciados pelo Java
    std::fstream LASOPid("/tmp/LASOPid.txt");
    while(!LASOPid.eof()){
        std::string pid{};
        std::string linha{};
        getline(LASOPid, linha);
        if(linha.find("librasoffice.jar") != -1){
            for(auto caractere : linha){
                if((((int)caractere - 48)  < 10) and caractere != ' '){
                    pid += caractere; //Adiciona em pid, caso o caractere seja um número 
                }
            }
            std::string killProcess = "kill " + pid; //comando para matar o processo pelo pid
            system(killProcess.c_str());
        }
    }
    LASOPid.close();
    system("rm /tmp/LASOPid.txt"); // remove o arquivo LASOPid.txt
}

#endif
//END LIBRAS
