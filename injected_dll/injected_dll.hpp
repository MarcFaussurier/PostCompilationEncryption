#ifndef PCH_H
#define PCH_H

#include <windows.h>
//hook function
BOOL CheckAddr(LPVOID lpAddr, int dwCheck, int size) {
	int result;

	ReadProcessMemory(GetCurrentProcess(), (LPVOID)lpAddr, (LPVOID)(&result), size, NULL);
	if (result == dwCheck) {
		return true;
	}

	return false;
}

BOOL Hook(void* pAddr, void* pNAddr, int len = 5);
void ExtendedThread();

DWORD desativar = 0x59FBC5;
DWORD saida7 = 0x0043B1DB;
DWORD saida6 = 0x43AB66;
DWORD nameReturn = 0x59FBB4;
DWORD original = 0x914490;
DWORD nameReturn2 = 0x478592;
DWORD return2 = 0x59F965;
DWORD saida8 = 0x439F26;
DWORD saida9 = 0x004394AC;
DWORD saida1 = 0x439F26;
DWORD rev = 0x439F26;
DWORD rev2 = 0x43B676;
DWORD rev3 = 0x43AC7A7;
DWORD saidaaa = 0x43A0CA;
DWORD saida35 = 0x0439F33;
DWORD remover = 0x004394AE;
DWORD retornooo = 0x439F39;
DWORD pet50 = 0x00439F26;
DWORD pet51 = 0x004394BB;

DWORD oculto = 0x0043A0CA;

BYTE AsaAtivada = 0;

BYTE Effect = 0;

BYTE PetAtivado = 0;

int wingoff = 0x087D263;
int Comand_imput = 0x632BD7;
int  Cmd_retorno = 0x4864C6;

DWORD ocultoasa1 = 0x0041F505;
DWORD Asa3return = 0x0041F4DA;
DWORD returnasa4 = 0x0041F5A5;
DWORD returnpet5 = 0x00439F26;

int cmd_jump = 0x04871D2;
DWORD removerasa = 0x0041F76D;
const char* cEnableBuffs = "/rbuff on";
const char* cDisableBuffs = "/rbuff off";
BYTE cBoostPointer = 0;
BYTE cHide = 0;
void RevelationThread();

int mensagem = 0x0422D40;

int intt = 204;

DWORD  retorno = 0x41627D;

DWORD petret1 = 0x04112AB;

DWORD petret2 = 0x004112AB;

DWORD petre1 = 0x04112C0;

DWORD petre2 = 0x00418310;

DWORD returnpet3 = 0x0041814E;

DWORD returnpet4 = 0x00411228;

char pet[128];
char asaini[128];



//DWORD return3 = 0x59F968;
BYTE Titulo = 0;
unsigned char dv[] = "activado";
unsigned char at[] = "desactivado";
const char* comando1 = "/wing on";
const char* comando2 = "/wing off";
const char* comand3 = "/pet on";
const char* comand4 = "/pet off";
const char* comand5 = "/dualquest";
const char* comand6 = "/questpvp";
const char* comand7 = "/questpvp2";
const char* comand8 = "/vet";
const char* comand9 = "/guild";
const char* comand10 = "/bd";
const char* comand11 = "/kanos drop";
const char* comand12 = "/dd1 drop";
const char* comand13 = "/cs drop";
const char* comand14 = "/map0 drop";
const char* comand15 = "/canyon drop";
const char* comand16 = "/isla drop";
const char* comand17 = "/ct2 drop";
const char* comand18 = "/argilla drop";
const char* comand19 = "/ayuda";
const char* comand20 = "/effectos on";
const char* comand21 = "/effectos off";

#endif //PCH_H
