#include "console.h"

void presskey() {
	system("pause");
}

void exitcode(const char* msg, int exitCode) {
	if (exitCode != 0)
		std::cout << "Message d'erreur: " << msg << std::endl;

	exit(exitCode);
}