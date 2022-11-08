#include "Memory.hpp"
#include "../Util/XOR.hpp"
#include "../Components/LocalPlayer.hpp"

// Vars to use
DWORD baseAddress = NULL;
DWORD engineAddress = NULL;
DWORD clientState = NULL;

//Vars for process snapshot
HANDLE hProcSnap = NULL;
PROCESSENTRY32 procEntry32;

//Vars for module snapshot
HANDLE hModuleSnap = NULL;
MODULEENTRY32 modEntry32;

//Process ID of attached proc
DWORD pID = NULL;

//Handle to process
HANDLE hProc = NULL;

bool attatchProc(char* procName)
{
	//Defining size of structure so we can populate it
	procEntry32.dwSize = sizeof(PROCESSENTRY32);

	//Taking a snapshot of all processes running
	hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcSnap == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to take snapshot of process list." << std::endl;
		return false;
	}

	//While there is a next process in the snapshot
	while (Process32Next(hProcSnap, &procEntry32))
	{
		std::cout << procEntry32.szExeFile << std::endl;
		//If the process we're looking for matches the current process in snapshot
		if (!strcmp(procName, procEntry32.szExeFile))
		{
			//Outputting proc name and ID then getting all access to process and initialising a handle to the proc to we can read/write it's memory
			std::cout << "Found process " << procEntry32.szExeFile << " with process ID " << procEntry32.th32ProcessID << std::endl;
			hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procEntry32.th32ProcessID);
			pID = procEntry32.th32ProcessID;

			if (hProc == NULL)
			{
				std::cout << "Failed getting handle to process." << std::endl;
			}
			//Close handle to process snapshot then return true
			CloseHandle(hProcSnap);
			return true;
		}
	}

	std::cout << "Couldn't find " << procName << " in the process snapshot." << std::endl;
	CloseHandle(hProcSnap);
	return false;
}

DWORD getModule(LPSTR moduleName)
{
	//Taking snapshot of modules in process
	hModuleSnap = INVALID_HANDLE_VALUE;
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);

	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to take a snapshot of modules." << std::endl;
		CloseHandle(hModuleSnap);
		return 0;
	}

	//Defining structure size
	modEntry32.dwSize = sizeof(MODULEENTRY32);

	//Getting information of first module in snapshot
	if (Module32First(hModuleSnap, &modEntry32))
	{
		//If the module we're looking for matches the module in snapshot
		if (!strcmp(moduleName, modEntry32.szModule))
		{
			//Outputting module name and base address
			std::cout << "Found module " << modEntry32.szModule << " with base address " << std::hex << (DWORD)modEntry32.modBaseAddr << std::endl;

			//Close handle to process snapshot then return base address
			CloseHandle(hModuleSnap);
			return (DWORD)modEntry32.modBaseAddr;
		}
	}

	//While there is a next module in the snapshot
	while (Module32Next(hModuleSnap, &modEntry32))
	{
		//If the module we're looking for matches the module in snapshot
		if (!strcmp(moduleName, modEntry32.szModule))
		{
			//Outputting module name and base address
			std::cout << "Found module " << modEntry32.szModule << " with base address 0x" << std::hex << std::uppercase << (DWORD)modEntry32.modBaseAddr << std::endl;

			//Close handle to process snapshot then return base address
			CloseHandle(hModuleSnap);
			return (DWORD)modEntry32.modBaseAddr;
		}
	}
	std::cout << "Couldn't find " << moduleName << " module in module snapshot of the process." << std::endl;
	CloseHandle(hModuleSnap);
	return false;
}

std::uint32_t find(const char* proc)
{
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);

	if (Process32First(snapshot, &pe)) {
		while (Process32Next(snapshot, &pe))
		{
			if (!strcmp(proc, pe.szExeFile)) {
				CloseHandle(snapshot);
				//mylog << "Found proc!\n";
				return pe.th32ProcessID;
	}
			}
		}
	CloseHandle(snapshot);
	return 0;
}

void init()
{
	//TODO : FIX THIS!!
	start:
	if (attatchProc((LPSTR)XOR("csgo.exe")))
	{
		while (!getModule((LPSTR)XOR("client.dll")))
		{
			goto start;
		}
		baseAddress = getModule((LPSTR)XOR("client.dll"));
		engineAddress = getModule((LPSTR)XOR("engine.dll"));

		LocalPlayer::setLocalPlayer();

		clientState = rpm<DWORD>(engineAddress + hazedumper::signatures::dwClientState);
	}
	else
	{
		goto start;
	}
}