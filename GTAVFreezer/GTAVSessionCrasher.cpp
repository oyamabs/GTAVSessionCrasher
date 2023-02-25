#include "pch.h"
#include "console.h"
#include "proc.h"

int main()
{
    std::cout << "GTA V - Session Crasher\n";
    std::cout << "\tPar oyamabs\n";


    // obtenir pid gta v
    DWORD pid = getPid(L"GTA5.exe");

    if (pid == 0) {
        std::cout << "PID de GTA V non trouvé, vérifiez que le jeu est bien lancé" << std::endl;
    }

    std::cout << "\n[+] GTA V trouve !" << std::endl;
    std::cout << "[+] PID: " << pid << std::endl;
    std::cout << "[+] Suspension du jeu..." << std::endl;

    // freezer le jeu
    freeze(pid);

    // attendre 10s
    Sleep(10000);

    // defreezer le jeu
    unfreeze(pid);

    std::cout << "[+] Suspension terminee. La session est vide" << std::endl;
    
    // appuyer sur une touche pour quitter
    presskey();
    exitcode("", 0);
}
