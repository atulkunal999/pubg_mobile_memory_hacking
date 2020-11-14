#include "pch.h"


MemoryManager* g_pMemoryManager = new MemoryManager();


MemoryManager::MemoryManager(){}


MemoryManager::~MemoryManager(){}

FTTransform2_t MemoryManager::ReadFTransform2(DWORD vAddv) {
	return Driver.ReadVirtualMemory<FTTransform2_t>(processId,vAddv,sizeof(FTTransform2_t));
}
void MemoryManager::init(int pid, bool debug){

	// Find AOW Process Id
	int threadCount = 0;
	processId = pid;
	if(!processId){
		if(debug){
			std::cout << termcolor::red << "SmartGaga Process Id Not Found. Searching For Process... \n" << termcolor::reset;
		}
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		Process32First(hSnap, &pe);
		while(Process32Next(hSnap, &pe)){
			if(_tcsicmp(pe.szExeFile, _T("aow_exe.exe")) == 0){
				if(pe.cntThreads > threadCount){
					threadCount = pe.cntThreads; pid = pe.th32ProcessID;
				}
			}
		}
		processId = pid;
	}
	if(debug){
		std::cout << termcolor::blue << "PID : " << termcolor::green << pid << " \n" << termcolor::reset;
	}
	DriverLoaded = Driver.hDriver > 0 ? true : false;
	
	if(processId){
		// Get process handle
		processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
		if(debug){
			std::cout << termcolor::blue << "HWND : " << termcolor::green << std::hex << (int)processHandle << std::dec << " \n" << termcolor::reset;
		}
		if(processHandle){
			allIsWell = true;
		}
	} else{
		if(debug){
			std::cout << termcolor::red << "Gameloop Process Id Not Found. Make Shoure gameloop is Open and game is Running.\n" << termcolor::reset;
		}
	}

}

void MemoryManager::readMemory(PVOID BaseAddress, PVOID Buffer, SIZE_T BufferSize) {

	Driver.ReadSpecial(processId, (DWORD)BaseAddress, Buffer, BufferSize);
}

bool MemoryManager::search(BYTE* bSearchData, int nSearchSize, DWORD_PTR dwStartAddr, DWORD_PTR dwEndAddr, BOOL bIsCurrProcess, int iSearchMode, std::vector<DWORD_PTR>& vRet) {

	MEMORY_BASIC_INFORMATION	mbi;
	std::vector<MEMORY_REGION> m_vMemoryRegion;
	mbi.RegionSize = 0x400;
	DWORD dwAddress = dwStartAddr;

	MEMORY_REGION memSectorList[1000];

	int memSectorIndex = 0;
	while (VirtualQueryEx(processHandle, (LPCVOID)dwAddress, &mbi, sizeof(mbi)) && (dwAddress < dwEndAddr) && ((dwAddress + mbi.RegionSize) > dwAddress)) {
		if (
			(mbi.State == MEM_COMMIT) &&
			((mbi.Protect & PAGE_GUARD) == 0) &&
			(mbi.Protect != PAGE_NOACCESS) &&
			((mbi.AllocationProtect & PAGE_NOCACHE) != PAGE_NOCACHE)
			) {
			MEMORY_REGION mData = { 0 };
			try {
				mData.dwBaseAddr = (DWORD_PTR)mbi.BaseAddress;
				mData.dwMemorySize = mbi.RegionSize;
				m_vMemoryRegion.push_back(mData);
				memSectorList[memSectorIndex] = mData;
			}
			catch(std::exception ex)
			{ }
			memSectorIndex++;
		}
		dwAddress = (DWORD)mbi.BaseAddress + mbi.RegionSize;
	}

	std::vector<MEMORY_REGION>::iterator it;
	//for(it = m_vMemoryRegion.begin(); it != m_vMemoryRegion.end(); it++){
	int memSectorCount = memSectorIndex;
	memSectorIndex = 0;
	DWORD_PTR curAddr = dwStartAddr;
	while (curAddr < dwEndAddr) {
		VirtualQueryEx(processHandle, (LPCVOID)curAddr, &mbi, sizeof(mbi));
		long regionSizeOrg = mbi.RegionSize;
		long regionSize = mbi.RegionSize;
		if (regionSize > 10) {
			BYTE* pCurrMemoryData = new BYTE[regionSize];
			//Driver.ReadSpecial(processId, curAddr, &pCurrMemoryData, regionSize);
			//readMemory((PVOID)curAddr, (PVOID*)pCurrMemoryData, regionSize);
			/*for (long p = 0; p < regionSize; p++)
			{
				pCurrMemoryData[p] = Driver.ReadVirtualMemory<BYTE>(processId, curAddr + p, sizeof(BYTE));
			}*/
			Driver.RVM(processId, curAddr, *pCurrMemoryData, regionSize);
			DWORD_PTR dwOffset = 0;
			int iOffset = find(pCurrMemoryData, regionSize, bSearchData, nSearchSize);
			while (iOffset != -1) {
				dwOffset += iOffset;
				vRet.push_back(dwOffset + curAddr);
				dwOffset += nSearchSize;
				iOffset = find(pCurrMemoryData + dwOffset, regionSize - dwOffset - nSearchSize, bSearchData, nSearchSize);
			}
			delete[] pCurrMemoryData;
		}
		memSectorIndex++;
		curAddr = curAddr + (DWORD_PTR)regionSizeOrg;
		continue;
	}
	return TRUE;
}


int MemoryManager::find(BYTE* buffer, int dwBufferSize, BYTE* bstr, DWORD dwStrLen) {
	if (dwBufferSize < 0) {
		return -1;
	}
	DWORD  i, j;
	for (i = 0; i < dwBufferSize; i++) {
		for (j = 0; j < dwStrLen; j++) {
			if (buffer[i + j] != bstr[j])
				if(bstr[j] != '?')
					break;
		}
		if (j == dwStrLen)
			return i;
	}
	return -1;
}


DWORD MemoryManager::dRead(DWORD base){
	return Driver.ReadVirtualMemory<DWORD>(processId, base, sizeof(int));
}

float MemoryManager::fRead(DWORD base){
	return Driver.ReadVirtualMemory<float>(processId, base, sizeof(float));
}
int MemoryManager::iRead(DWORD base){
	return Driver.ReadVirtualMemory<int>(processId, base, sizeof(int));
}