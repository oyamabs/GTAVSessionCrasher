#include "pch.h"
#include "console.h"
#include "proc.h"

int main()
{
    SetConsoleOutputCP(65001); // affichage des accents, merci à ce topic developpez.net https://www.developpez.net/forums/d2077938/c-cpp/cpp/utiliser-texte-accents/#post11545772

    std::cout << "GTA V - Session Crasher\n";
    std::cout << "\tPar oyamabs\n";


    // obtenir pid gta v
    DWORD pid = getPid(L"GTA5.exe");

    if (pid == 0) {
        std::cout << "PID de GTA V non trouvé, vérifiez que le jeu est bien lancé" << std::endl;
        presskey();
        exitcode("GTA V non trouvé", 1);
    }

    std::cout << "\n[+] GTA V trouvé !" << std::endl;
    std::cout << "[+] PID: " << pid << std::endl;
    std::cout << "[+] Suspension du jeu..." << std::endl;

    // freezer le jeu
    freeze(pid);

    // attendre 10s
    Sleep(10000);

    // defreezer le jeu
    unfreeze(pid);

    std::cout << "[+] Suspension terminée. La session est vidée." << std::endl;
    
    // appuyer sur une touche pour quitter
    presskey();
    exitcode("", 0);
}
