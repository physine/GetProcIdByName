#include <tchar.h>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>

DWORD getProcIdByName(std::string procName){
    const char* processName = procName.c_str();
    PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(snapshot, &entry) == TRUE){
		while (Process32Next(snapshot, &entry) == TRUE){
			if (_stricmp(entry.szExeFile, processName) == 0){
				CloseHandle(snapshot);
				return entry.th32ProcessID;
			}
		}
	}

	CloseHandle(snapshot);
	return 0;    
}

// DWORD getModuleBase(std::string modName, DWORD ProcessId) {

//     //string username = "whatever";
//     std::wstring wideModName;
//     for(int i = 0; i < modName.length(); ++i)
//         wideModName += wchar_t( modName[i] );

//     const wchar_t* ModuleName = wideModName.c_str();


//     //std::wstring wsModuleName = std::wstring(modName.begin(), modName.end());
//     //const wchar_t* ModuleName = wsModuleName.c_str();

//     // This structure contains lots of goodies about a module
//     MODULEENTRY32 ModuleEntry = { 0 };
//     // Grab a snapshot of all the modules in the specified process
//     HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);

//     if (!SnapShot)
//         return NULL;

//     // You have to initialize the size, otherwise it will not work
//     ModuleEntry.dwSize = sizeof(ModuleEntry);

//     // Get the first module in the process
//     if (!Module32First(SnapShot, &ModuleEntry))
//         return NULL;

//     do {
//         // Check if the module name matches the one we're looking for
//         if (!wcscmp(ModuleEntry.szModule, ModuleName)) {
//             // If it does, close the snapshot handle and return the base address
//             CloseHandle(SnapShot);
//             return (DWORD)ModuleEntry.modBaseAddr;
//         }
//         // Grab the next module in the snapshot
//     } while (Module32Next(SnapShot, &ModuleEntry));

//     // We couldn't find the specified module, so return NULL
//     CloseHandle(SnapShot);
//     return NULL;
// }

int main(){
    std::string procName = ""; // editMyMemory.exe
    std::string moduleName = procName;    

    DWORD pId = getProcIdByName(procName);
    if(!pId){
        std::cout << "\nCan't get Process ID of " << procName << "\n";
        std::cout << "Exiting Program...";
        goto exit;
    }
    std::cout << "\n" << procName << " PID: " << pId;
    
    HANDLE pHandle = OpenProcess(PROCESS_VM_READ, FALSE, pId);
    
    //DWORD baseAddr = getModuleBase(moduleName, pId);
    //std::cout << "\n" << moduleName << " Base Address: " << baseAddr << "\n";

    exit:
    CloseHandle(pHandle);  
    return 0;
}