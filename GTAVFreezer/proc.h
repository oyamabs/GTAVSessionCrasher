#pragma once
#include "pch.h"

DWORD getPid(const wchar_t* processname);

void freeze(DWORD pid);
void unfreeze(DWORD pid);