// pch.cpp: arquivo de origem correspondente ao cabe�alho pr�-compilado

#include "injected_dll.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <WinUser.h>
#include "../utils/hook.hpp"
#include "../encrypt_const/encrypt_const.hpp"
#include "stdlib.h"

using namespace std;

float MovInvGold_01 = 461.00f;
float MovInvGold_02 = 235.00f;
BYTE InvetoryBytes_01[] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
BYTE InvetoryBytes_02[] = { 0x2D };


DWORD InvetoryExit_01 = 0x0051AAD5;
__declspec(naked) void Invetory_01()//Mov Gold
{
	_asm
	{
		push eax
		mov eax, MovInvGold_01
		mov dword ptr ds : [esi + 0x00000848] , eax
		mov eax, MovInvGold_02
		mov dword ptr ds : [esi + 0x00000844] , eax
		pop eax

		fld dword ptr ds : [esi + 0x00000848]
		JMP InvetoryExit_01
	}
}

DWORD InvetoryExit_02 = 0x0051A5C1;
DWORD CallNB_01 = 0x0057BC50;
__declspec(naked) void Invetory_02()//New Buttons
{
	_asm
	{
		mov ecx, dword ptr ds : [esi + 0x08]
		mov edx, dword ptr ds : [esi + 0x04]
		jne NB_01
		add ecx, 280//posy
		push ecx
		sub edx, 30//posx
		push edx
		lea ecx, dword ptr ds : [esi + 0x00000118]
		call CallNB_01
		JMP InvetoryExit_02

		NB_01 :
		mov ecx, dword ptr ds : [esi + 0x08]
			mov edx, dword ptr ds : [esi + 0x04]
			jne NB_02
			add ecx, 315//posy
			push ecx
			sub edx, 30//posx
			push edx
			lea ecx, dword ptr ds : [esi + 0x00000118]
			call CallNB_01
			JMP InvetoryExit_02

			NB_02 :
		mov ecx, dword ptr ds : [esi + 0x08]
			mov edx, dword ptr ds : [esi + 0x04]
			jne NB_02
			add ecx, 350//posy
			push ecx
			sub edx, 30//posx
			push edx
			lea ecx, dword ptr ds : [esi + 0x00000118]
			call CallNB_01
			JMP InvetoryExit_02
	}
}

DWORD InvetoryExit_03 = 0x00519642;
DWORD JMPNB_NPCID_01 = 0x00519667;
DWORD JMPNB_NPCID_02 = 0x0051A503;
DWORD CallNB_02 = 0x00422D40;
__declspec(naked) void Invetory_03()//NPC_ID
{
	_asm
	{

		mov ecx, dword ptr ds : [0x009144E4]
		cmp ecx, 0x75
		je NB_NPCJMP01
		mov eax, dword ptr ds : [esi + 0x04]
		mov edx, dword ptr ds : [0x007C3C0C]
		lea edi, dword ptr ds : [eax - 0x10]
		add edi, 94//TM para o lado <
		cmp edx, edi
		jl JMP_NB_01

		//TM para o lado >
		add eax, 110
		cmp edx, eax
		jg JMP_NB_01

		mov eax, dword ptr ds : [esi + 0x08]
		mov ebp, dword ptr ds : [0x007C3C10]
		lea edi, dword ptr ds : [eax + 0x000000B2]
		add edi, 298//TM para cima
		cmp ebp, edi
		jl JMP_NB_02

		add eax, 507//TM para baixo
		cmp ebp, eax
		jg JMP_NB_02

		cmp dword ptr ds : [0x022B24C4] , 00
		jne JMP_NB_02

		cmp dword ptr ds : [0x022B24C0] , 01
		jne JMP_NB_02

		test ecx, ecx
		je JMP_NB_03

		push 0x0C
		push 0x00000326
		push 0x1F
		call CallNB_02
		add esp, 0x0C
		mov eax, 1
		jmp NB_NPCJMP02

		JMP_NB_03 :
		cmp byte ptr ds : [esi + 0x00000138] , 00
			push eax
			mov eax, 0x0091AD44
			mov dword ptr ds : [eax] , 0//NPC Type
			mov eax, 0x009144E8
			mov dword ptr ds : [eax] , 0//unk
			mov eax, 0x009144EC
			mov dword ptr ds : [eax] , 0//unk
			mov eax, 0x0091AD40
			mov dword ptr ds : [eax] , 0//NPC TypeID
			mov eax, 0x009144F0
			mov dword ptr ds : [eax] , 6//NPC Face
			mov eax, 0x022AB7B8
			mov dword ptr ds : [eax] , 0//NPC Name
			mov eax, 0x009144E4
			mov byte ptr ds : [eax] , 101//NPC ID
			pop eax
			jmp JMP_NB_01

			sete al
			mov byte ptr ds : [esi + 0x00000138] , al
			mov edx, dword ptr ds : [0x007C3C0C]
			movzx eax, al
			neg eax
			sbb eax, eax
			and eax, 0x18
			mov dword ptr ds : [0x009144E4] , eax

			JMP_NB_01 :
		mov ebp, dword ptr ds : [0x007C3C10]

			JMP_NB_02 :
			mov eax, dword ptr ds : [esi + 0x04]
			jne NB_NPCID_01
			JMP InvetoryExit_03

			/// <summary>
			/// 
			/// </summary>
		NB_NPCID_01:
		mov ecx, dword ptr ds : [0x009144E4]
			cmp ecx, 0x75
			je NB_NPCJMP01
			mov eax, dword ptr ds : [esi + 0x04]
			mov edx, dword ptr ds : [0x007C3C0C]
			lea edi, dword ptr ds : [eax - 0x10]
			add edi, 31//TM para o lado <
			cmp edx, edi
			jl JMP_NB_04

			//TM para o lado >
			add eax, 45
			cmp edx, eax
			jg JMP_NB_04

			mov eax, dword ptr ds : [esi + 0x08]
			mov ebp, dword ptr ds : [0x007C3C10]
			lea edi, dword ptr ds : [eax + 0x000000B2]
			add edi, 298//TM para cima
			cmp ebp, edi
			jl JMP_NB_05

			add eax, 507//TM para baixo
			cmp ebp, eax
			jg JMP_NB_05

			cmp dword ptr ds : [0x022B24C4] , 00
			jne JMP_NB_05

			cmp dword ptr ds : [0x022B24C0] , 01
			jne JMP_NB_05

			test ecx, ecx
			je JMP_NB_06

			push 0x0C
			push 0x00000326
			push 0x1F
			call CallNB_02
			add esp, 0x0C
			mov eax, 1
			jmp NB_NPCJMP02

			JMP_NB_06 :
		cmp byte ptr ds : [esi + 0x00000138] , 00
			push eax
			mov eax, 0x0091AD44
			mov dword ptr ds : [eax] , 0//NPC Type
			mov eax, 0x009144E8
			mov dword ptr ds : [eax] , 0//unk
			mov eax, 0x009144EC
			mov dword ptr ds : [eax] , 0//unk
			mov eax, 0x0091AD40
			mov dword ptr ds : [eax] , 0//NPC TypeID
			mov eax, 0x009144F0
			mov dword ptr ds : [eax] , 13//NPC Face
			mov eax, 0x022AB7B8
			mov dword ptr ds : [eax] , 0//NPC Name
			mov eax, 0x009144E4
			mov byte ptr ds : [eax] , 102//NPC ID
			pop eax
			jmp JMP_NB_04

			sete al
			mov byte ptr ds : [esi + 0x00000138] , al
			mov edx, dword ptr ds : [0x007C3C0C]
			movzx eax, al
			neg eax
			sbb eax, eax
			and eax, 0x18
			mov dword ptr ds : [0x009144E4] , eax

			JMP_NB_04 :
		mov ebp, dword ptr ds : [0x007C3C10]

			JMP_NB_05 :
			mov eax, dword ptr ds : [esi + 0x04]
			jne NB_NPCID_02
			JMP InvetoryExit_03

			/// <summary>
			/// 
			/// </summary>
		NB_NPCID_02:
		mov ecx, dword ptr ds : [0x009144E4]
			cmp ecx, 0x75
			je NB_NPCJMP01
			mov eax, dword ptr ds : [esi + 0x04]
			mov edx, dword ptr ds : [0x007C3C0C]
			lea edi, dword ptr ds : [eax - 0x10]
			add edi, 55//TM para o lado <
			cmp edx, edi
			jl JMP_NB_07

			//TM para o lado >
			add eax, 75
			cmp edx, eax
			jg JMP_NB_07

			mov eax, dword ptr ds : [esi + 0x08]
			mov ebp, dword ptr ds : [0x007C3C10]
			lea edi, dword ptr ds : [eax + 0x000000B2]
			add edi, 298//TM para cima
			cmp ebp, edi
			jl JMP_NB_08

			add eax, 507//TM para baixo
			cmp ebp, eax
			jg JMP_NB_08

			cmp dword ptr ds : [0x022B24C4] , 00
			jne JMP_NB_08

			cmp dword ptr ds : [0x022B24C0] , 01
			jne JMP_NB_08

			test ecx, ecx
			je JMP_NB_09

			push 0x0C
			push 0x00000326
			push 0x1F
			call CallNB_02
			add esp, 0x0C
			mov eax, 1
			jmp NB_NPCJMP02

			JMP_NB_09 :
		cmp byte ptr ds : [esi + 0x00000138] , 00
			push eax
			mov eax, 0x0091AD44
			mov dword ptr ds : [eax] , 0//NPC Type
			mov eax, 0x009144E8
			mov dword ptr ds : [eax] , 0//unk
			mov eax, 0x009144EC
			mov dword ptr ds : [eax] , 0//unk
			mov eax, 0x0091AD40
			mov dword ptr ds : [eax] , 0//NPC TypeID
			mov eax, 0x009144F0
			mov dword ptr ds : [eax] , 27//NPC Face
			mov eax, 0x022AB7B8
			mov dword ptr ds : [eax] , 0//NPC Name
			mov eax, 0x009144E4
			mov byte ptr ds : [eax] , 121//NPC ID
			pop eax
			jmp JMP_NB_07

			sete al
			mov byte ptr ds : [esi + 0x00000138] , al
			mov edx, dword ptr ds : [0x007C3C0C]
			movzx eax, al
			neg eax
			sbb eax, eax
			and eax, 0x18
			mov dword ptr ds : [0x009144E4] , eax

			JMP_NB_07 :
		mov ebp, dword ptr ds : [0x007C3C10]

			JMP_NB_08 :
			mov eax, dword ptr ds : [esi + 0x04]
			jne NB_NPCID_03
			JMP InvetoryExit_03

			/// <summary>
			/// 
			/// </summary>

		NB_NPCID_03:
		mov ecx, dword ptr ds : [0x009144E4]
			cmp ecx, 0x75
			je NB_NPCJMP01
			mov eax, dword ptr ds : [esi + 0x04]
			mov edx, dword ptr ds : [0x007C3C0C]
			lea edi, dword ptr ds : [eax - 0x10]
			add edi, 130//TM para o lado <
			cmp edx, edi
			jl JMP_NB_10

			//TM para o lado >
			add eax, 145
			cmp edx, eax
			jg JMP_NB_10

			mov eax, dword ptr ds : [esi + 0x08]
			mov ebp, dword ptr ds : [0x007C3C10]
			lea edi, dword ptr ds : [eax + 0x000000B2]
			add edi, 298//TM para cima
			cmp ebp, edi
			jl JMP_NB_11

			add eax, 507//TM para baixo
			cmp ebp, eax
			jg JMP_NB_11

			cmp dword ptr ds : [0x022B24C4] , 00
			jne JMP_NB_11

			cmp dword ptr ds : [0x022B24C0] , 01
			jne JMP_NB_11

			test ecx, ecx
			je JMP_NB_12

			push 0x0C
			push 0x00000326
			push 0x1F
			call CallNB_02
			add esp, 0x0C
			mov eax, 1
			jmp NB_NPCJMP02

			JMP_NB_12 :
		cmp byte ptr ds : [esi + 0x00000138] , 00
			push eax
			mov eax, 0x0091AD44
			mov dword ptr ds : [eax] , 0//NPC Type
			mov eax, 0x009144E8
			mov dword ptr ds : [eax] , 0//unk
			mov eax, 0x009144EC
			mov dword ptr ds : [eax] , 0//unk
			mov eax, 0x0091AD40
			mov dword ptr ds : [eax] , 0//NPC TypeID
			mov eax, 0x009144F0
			mov dword ptr ds : [eax] , 27//NPC Face
			mov eax, 0x022AB7B8
			mov dword ptr ds : [eax] , 0//NPC Name
			mov eax, 0x009144E4
			mov byte ptr ds : [eax] , 122//NPC ID
			pop eax
			jmp JMP_NB_10

			sete al
			mov byte ptr ds : [esi + 0x00000138] , al
			mov edx, dword ptr ds : [0x007C3C0C]
			movzx eax, al
			neg eax
			sbb eax, eax
			and eax, 0x18
			mov dword ptr ds : [0x009144E4] , eax

			JMP_NB_10 :
		mov ebp, dword ptr ds : [0x007C3C10]

			JMP_NB_11 :
			mov eax, dword ptr ds : [esi + 0x04]
			JMP InvetoryExit_03

			NB_NPCJMP01 :
		JMP JMPNB_NPCID_01
			NB_NPCJMP02 :
		JMP JMPNB_NPCID_02
	}
}



BYTE cSmall = 0;
int skilleffect = 0;
int skillbarlock_cmd = 0;
int fpsboost_cmd = 0;



const char* othereff = "OTHEREFF";
char _othereff[255];
string szTrue = "TRUE";
string szFalse = "FALSE";





void fpsboost_save() {
	GetPrivateProfileStringA("VIDEO", "FPSBOOST", "", _othereff, 255, ".\\CONFIG.ini");
	if (_othereff == szTrue)
	{
		_asm {

			mov byte ptr[cBoostPointer], 0x1
		}
	}
	else if (_othereff == szFalse)
	{
		_asm {

			mov byte ptr[cBoostPointer], 0x0
		}
	}
}



void Effects_Save() {
	GetPrivateProfileStringA("VIDEO", "EFFECTS_ALL", "", _othereff, 255, ".\\CONFIG.ini");
	if (_othereff == szTrue)
	{
		_asm {
			mov byte ptr ds : [Effect] , 0x1
		}
	}
	else if (_othereff == szFalse)
	{
		_asm {
			mov byte ptr ds : [Effect] , 0x0
		}
	}
}


void Titulos_Save() {
	GetPrivateProfileStringA("VIDEO", "TITULOS", "", _othereff, 255, ".\\CONFIG.ini");
	if (_othereff == szTrue)
	{
		_asm {
			mov byte ptr ds : [Titulo] , 0x1
		}
	}
	else if (_othereff == szFalse)
	{
		_asm {
			mov byte ptr ds : [Titulo] , 0x0
		}
	}
}

BYTE Traje_Pointer = 0;
void Small_Icon_Save() {
	GetPrivateProfileStringA("VIDEO", "ICONOS_DE_BUFF_PEQUENO", "", _othereff, 255, ".\\CONFIG.ini");
	if (_othereff == szTrue)
	{
		_asm {
			mov byte ptr ds : [cSmall] , 0x1
		}
	}
	else if (_othereff == szFalse)
	{
		_asm {
			mov byte ptr ds : [cSmall] , 0x0
		}
	}
}


void Traje_Save() {
	GetPrivateProfileStringA("VIDEO", "TRAJES", "", _othereff, 255, ".\\CONFIG.ini");
	if (_othereff == szTrue)
	{
		_asm {
			mov byte ptr ds : [Traje_Pointer] , 0x1
		}
	}
	else if (_othereff == szFalse)
	{
		_asm {
			mov byte ptr ds : [Traje_Pointer] , 0x0
		}
	}
}


void Alas_Save() {
	GetPrivateProfileStringA("VIDEO", "ALAS", "", _othereff, 255, ".\\CONFIG.ini");
	if (_othereff == szTrue)
	{
		_asm {
			mov byte ptr ds : [AsaAtivada] , 0x1
		}
	}
	else if (_othereff == szFalse)
	{
		_asm {
			mov byte ptr ds : [AsaAtivada] , 0x0
		}
	}
}

void Pet_Save() {
	GetPrivateProfileStringA("VIDEO", "PETS", "", _othereff, 255, ".\\CONFIG.ini");
	if (_othereff == szTrue)
	{
		_asm {
			mov byte ptr ds : [PetAtivado] , 0x1
		}
	}
	else if (_othereff == szFalse)
	{
		_asm {
			mov byte ptr ds : [PetAtivado] , 0x0
		}
	}
}

BYTE Dark_Pointer = 0;
BYTE Light_Pointer = 0;
void HP_Dark_Save() {
	GetPrivateProfileStringA("VIDEO", "DARK_HP", "", _othereff, 255, ".\\CONFIG.ini");
	if (_othereff == szTrue)
	{
		_asm {
			mov byte ptr ds : [Dark_Pointer] , 0x1
		}
	}
	else if (_othereff == szFalse)
	{
		_asm {
			mov byte ptr ds : [Dark_Pointer] , 0x0
		}
	}
}

void HP_Light_Save() {
	GetPrivateProfileStringA("VIDEO", "LIGHT_HP", "", _othereff, 255, ".\\CONFIG.ini");
	if (_othereff == szTrue)
	{
		_asm {
			mov byte ptr ds : [Light_Pointer] , 0x1
		}
	}
	else if (_othereff == szFalse)
	{
		_asm {
			mov byte ptr ds : [Light_Pointer] , 0x0
		}
	}
}

BYTE Traje_Effect = 0;

void Traje_Effect_Save() {
	GetPrivateProfileStringA("VIDEO", "TRAJE_EFFECT", "", _othereff, 255, ".\\CONFIG.ini");
	if (_othereff == szTrue)
	{
		_asm {
			mov byte ptr ds : [Traje_Effect] , 0x1
		}
	}
	else if (_othereff == szFalse)
	{
		_asm {
			mov byte ptr ds : [Traje_Effect] , 0x0
		}
	}
}







DWORD opensettingjmp = 0x0051BA91; //51AFA1;



void __declspec(naked) opensetting() {
	__asm {


		cmp byte ptr ds : [cSmall] , 00
		setne dl
		mov[esi + 0xDF03], dl

		cmp byte ptr ds : [Traje_Pointer] , 00
		setne dl
		mov[esi + 0xE4DB], dl

		cmp byte ptr[cBoostPointer], 00
		setne dl
		mov[esi + 0xEAB3], dl

		cmp byte ptr ds : [Effect] , 00
		setne dl
		mov[esi + 0xF08B], dl

		cmp byte ptr ds : [Titulo] , 00
		setne dl
		mov[esi + 0xF663], dl

		cmp byte ptr ds : [AsaAtivada] , 00
		setne dl
		mov[esi + 0xFC3B], dl


		cmp byte ptr ds : [PetAtivado] , 00
		setne dl
		mov[esi + 0x10213], dl

		cmp byte ptr ds : [Dark_Pointer] , 00
		setne dl
		mov[esi + 0x107EB], dl

		cmp byte ptr ds : [Light_Pointer] , 00
		setne dl
		mov[esi + 0x10DC3], dl

		cmp byte ptr ds : [Traje_Effect] , 00
		setne dl
		mov[esi + 0x1139B], dl


		// original code
		pop esi
		mov ecx, [esp]
		xor ecx, esp
		jmp opensettingjmp

	}
}



DWORD renderjmp = 0x0051F5A2;//51EAB2;

DWORD renderpacketall = 0x00552520;//551B40;

void __declspec(naked) render() {
	__asm {

		call renderpacketall
		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xF5C0]
		call renderpacketall

		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xDE60]
		call renderpacketall
		/*
		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xE438]
		call renderpacketall
		*/
		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xEA10]
		call renderpacketall

		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xEFE8]
		call renderpacketall


		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xE438]
		call renderpacketall

		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xFB98]
		call renderpacketall

		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0x10170]
		call renderpacketall


		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0x10748]
		call renderpacketall

		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0x10D20]
		call renderpacketall

		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0x112F8]
		call renderpacketall



		jmp renderjmp




	}
}



DWORD clickjmp = 0x00521C3B; //52114B;

DWORD clickjnejmp = 0x00521D31;//521241;

DWORD clickpacketcall = 0x00550B00;//550120;

void __declspec(naked) click() {
	__asm {

		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xF5C0]
		call clickpacketcall
		test eax, eax
		jne clickjness

		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xDE60]
		call clickpacketcall
		test eax, eax
		jne clickjness
		/*
		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xE438]
		call clickpacketcall
		test eax, eax
		jne clickjness
		*/
		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xEA10]
		call clickpacketcall
		test eax, eax
		jne clickjness

		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xEFE8]
		call clickpacketcall
		test eax, eax
		jne clickjness


		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xE438]
		call clickpacketcall
		test eax, eax
		jne clickjness


		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0xFB98]
		call clickpacketcall
		test eax, eax
		jne clickjness


		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0x10170]
		call clickpacketcall
		test eax, eax
		jne clickjness

		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0x10748]
		call clickpacketcall
		test eax, eax
		jne clickjness


		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0x10D20]
		call clickpacketcall
		test eax, eax
		jne clickjness


		mov eax, [esi + 0xBF4]
		mov ecx, [esi + 0xBF0]
		push eax
		push ecx
		lea ecx, [esi + 0x112F8]
		call clickpacketcall
		test eax, eax
		jne clickjness






		mov eax, [esi + 0xBF4]


		jmp clickjmp

		clickjness :
		jmp clickjnejmp

	}
}


DWORD savejmp = 0x0051BDE6;//51B2F6;

DWORD saveinj = 0x007C0E14;

DWORD saveinj2 = 0x007C0E1C;

LPCSTR SKILLEFFECT_call = "SKILLEFFECT";
LPCSTR SKILLBARLCK_call = "SKILLWNDLOCK";
LPCSTR FPSBOOST_call = "FPSBOOST";
LPCSTR EFFECTS_ALL_CALL = "EFFECTS_ALL";
LPCSTR TITULOS_CALL = "TITULOS";
LPCSTR ICONO_DE_BUFF = "ICONOS_DE_BUFF_PEQUENO";
LPCSTR TRAJES_CALL = "TRAJES";
LPCSTR ALAS_CALL = "ALAS";
LPCSTR DARK_CALL = "DARK_HP";
LPCSTR LIGHT_CALL = "LIGHT_HP";
LPCSTR PETS_CALL = "PETS";
LPCSTR TRAJE_CALL = "TRAJE_EFFECT";




LPCSTR FALSE_call = "FALSE";
LPCSTR TRUE_call = "TRUE";

DWORD savewrite = 0x7462EC;

void __declspec(naked) save() {
	__asm {

		mov edx, [saveinj]
		mov[edx], ecx



		cmp byte ptr[esi + 0xDF03], bl
		sete cl
		mov byte ptr ds : [cSmall] , cl



		cmp byte ptr ds : [esi + 0xE4DB] , bl
		sete cl
		mov byte ptr ds : [Traje_Pointer] , cl




		cmp byte ptr[esi + 0xEAB3], bl
		sete cl
		mov byte ptr ds : [cBoostPointer] , cl


		cmp byte ptr[esi + 0xF08B], bl
		sete cl
		mov byte ptr ds : [Effect] , cl

		cmp byte ptr[esi + 0xF663], bl
		sete cl
		mov byte ptr ds : [Titulo] , cl


		cmp byte ptr[esi + 0xFC3B], bl
		sete cl
		mov byte ptr ds : [AsaAtivada] , cl


		cmp byte ptr[esi + 0x10213], bl
		sete cl
		mov byte ptr ds : [PetAtivado] , cl

		cmp byte ptr[esi + 0x107EB], bl
		sete cl
		mov byte ptr ds : [Dark_Pointer] , cl

		cmp byte ptr[esi + 0x10DC3], bl
		sete cl
		mov byte ptr ds : [Light_Pointer] , cl

		cmp byte ptr[esi + 0x1139B], bl
		sete cl
		mov byte ptr ds : [Traje_Effect] , cl


		pushad
		cmp byte ptr ds : [Traje_Effect] , 00
		push 0x007C0720
		mov esi, [savewrite]
		mov esi, [esi]
		je SET_FALSE_TRAJE_EFFECT
		push TRUE_call //{ ["TRUE"] }
		push TRAJE_CALL //{ ["SKILLEFFECT"] }
		push 0x00746E38 // { ["VIDEO"] }

		jmp Save_Exit_Traje_Effect


		SET_FALSE_TRAJE_EFFECT :
		push FALSE_call // { ["FALSE"] }
			push TRAJE_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 //{ ["VIDEO"] }
			Save_Exit_Traje_Effect :
			call esi
			popad



			pushad
			cmp byte ptr ds : [Dark_Pointer] , 00
			push 0x007C0720
			mov esi, [savewrite]
			mov esi, [esi]
			je SET_FALSE_DARK
			push TRUE_call //{ ["TRUE"] }
			push DARK_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 // { ["VIDEO"] }

			jmp Save_Exit_Dark


			SET_FALSE_DARK :
		push FALSE_call // { ["FALSE"] }
			push DARK_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 //{ ["VIDEO"] }
			Save_Exit_Dark :
			call esi
			popad


			pushad
			cmp byte ptr ds : [Light_Pointer] , 00
			push 0x007C0720
			mov esi, [savewrite]
			mov esi, [esi]
			je SET_FALSE_LIGHT
			push TRUE_call //{ ["TRUE"] }
			push LIGHT_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 // { ["VIDEO"] }

			jmp Save_Exit_Light


			SET_FALSE_LIGHT :
		push FALSE_call // { ["FALSE"] }
			push LIGHT_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 //{ ["VIDEO"] }
			Save_Exit_Light :
			call esi
			popad




			pushad
			cmp byte ptr ds : [PetAtivado] , 00
			push 0x007C0720
			mov esi, [savewrite]
			mov esi, [esi]
			je SET_FALSE_PET
			push TRUE_call //{ ["TRUE"] }
			push PETS_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 // { ["VIDEO"] }

			jmp Save_Exit_Pets


			SET_FALSE_PET :
		push FALSE_call // { ["FALSE"] }
			push PETS_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 //{ ["VIDEO"] }
			Save_Exit_Pets :
			call esi
			popad






			pushad
			cmp byte ptr ds : [AsaAtivada] , 00
			push 0x007C0720
			mov esi, [savewrite]
			mov esi, [esi]
			je SET_FALSE_ALA
			push TRUE_call //{ ["TRUE"] }
			push ALAS_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 // { ["VIDEO"] }

			jmp Save_Exit_Alas


			SET_FALSE_ALA :
		push FALSE_call // { ["FALSE"] }
			push ALAS_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 //{ ["VIDEO"] }
			Save_Exit_Alas :
			call esi
			popad



			pushad
			cmp byte ptr ds : [Traje_Pointer] , 00
			push 0x007C0720
			mov esi, [savewrite]
			mov esi, [esi]
			je SET_FALSE_TRAJE
			push TRUE_call //{ ["TRUE"] }
			push TRAJES_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 // { ["VIDEO"] }

			jmp Save_Exit_Trajes


			SET_FALSE_TRAJE :
		push FALSE_call // { ["FALSE"] }
			push TRAJES_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 //{ ["VIDEO"] }
			Save_Exit_Trajes :
			call esi
			popad







			pushad
			cmp byte ptr ds : [Titulo] , 00
			push 0x007C0720
			mov esi, [savewrite]
			mov esi, [esi]
			je SET_FALSE_TITULOS
			push TRUE_call //{ ["TRUE"] }
			push TITULOS_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 // { ["VIDEO"] }

			jmp Save_Exit_Titulos


			SET_FALSE_TITULOS :
		push FALSE_call // { ["FALSE"] }
			push TITULOS_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 //{ ["VIDEO"] }
			Save_Exit_Titulos :
			call esi
			popad




			pushad
			cmp byte ptr ds : [Effect] , 00
			push 0x007C0720
			mov esi, [savewrite]
			mov esi, [esi]
			je SET_FALSE_EFFECT
			push TRUE_call //{ ["TRUE"] }
			push EFFECTS_ALL_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 // { ["VIDEO"] }

			jmp Save_Exit_Effect


			SET_FALSE_EFFECT :
		push FALSE_call // { ["FALSE"] }
			push EFFECTS_ALL_CALL //{ ["SKILLEFFECT"] }
			push 0x00746E38 //{ ["VIDEO"] }
			Save_Exit_Effect :
			call esi
			popad


			pushad
			cmp byte ptr ds : [cSmall] , 00
			push 0x007C0720 //{ ["D:\Games\Shaiya\CONFIG.INI"] }
			mov esi, [savewrite]
			mov esi, [esi]
			je disabled4
			push TRUE_call //{ ["TRUE"] }
			push ICONO_DE_BUFF //{ ["SKILLEFFECT"] }
			push 0x00746E38 // { ["VIDEO"] }

			jmp savesssexit4

			disabled4 :
		push FALSE_call // { ["FALSE"] }
			push ICONO_DE_BUFF //{ ["SKILLEFFECT"] }
			push 0x00746E38 //{ ["VIDEO"] }
			savesssexit4 :
			call esi
			popad







			pushad
			cmp byte ptr[cBoostPointer], 00
			push 0x007C0720 //{ ["D:\Games\Shaiya\CONFIG.INI"] }
			mov esi, [savewrite]
			mov esi, [esi]
			je disabled6
			push TRUE_call //{ ["TRUE"] }
			push FPSBOOST_call //{ ["FPSBOOST"] }
			push 0x00746E38 // { ["VIDEO"] }

			jmp savesssexit6


			disabled6 :
		push FALSE_call // { ["FALSE"] }
			push FPSBOOST_call //{ ["FPSBOOST"] }
			push 0x00746E38 //{ ["VIDEO"] }
			savesssexit6 :
			call esi
			popad


			xor edx, edx
			jmp savejmp

	}
}


DWORD bindbuttonpositionjmp = 0x0051ED40;//51E250;

DWORD bindbuttonpositionpacketall = 0x00550950;//54FF70;
void __declspec(naked) bindbuttonposition() {
	__asm {

		// Skill bar lock
		call bindbuttonpositionpacketall
		push 0x1C3 // Y
		push 0x9C // X
		lea ecx, [esi + 0xF5C0]
		// Pet
		call bindbuttonpositionpacketall
		push 0x1DA // Y
		push 0x23 // X
		lea ecx, [esi + 0xDE60]
		call bindbuttonpositionpacketall
		/*
		 // Kanat
		 push 0x1DA // Y
		 push 0x9C // X
		 lea ecx, [esi + 0xE438]
		 call bindbuttonpositionpacketall
		 */
		 // Skill effect
		 push 0x1DA // Y
		 push 0x9C // X
		 lea ecx, [esi + 0xEA10]
		 call bindbuttonpositionpacketall

		 push 0x1EE // Y
		 push 0x9C // X
		 lea ecx, [esi + 0xEFE8]
		 // Pet
		 call bindbuttonpositionpacketall

		 push 498 // Y
		 push 35 // X
		 lea ecx, [esi + 0xE438]
		 // Pet
		 call bindbuttonpositionpacketall


		 push 380 // Y
		 push 35 // X
		 lea ecx, [esi + 0xFB98]
		 // Pet
		 call bindbuttonpositionpacketall


		 push 358 // Y
		 push 35 // X
		 lea ecx, [esi + 0x10170]
		 // Pet
		 call bindbuttonpositionpacketall

		 push 380 // Y
		 push 0x9C // X
		 lea ecx, [esi + 0x10748]
		 // Pet
		 call bindbuttonpositionpacketall


		 push 380 // Y
		 push 225 // X
		 lea ecx, [esi + 0x10D20]
		 // Pet
		 call bindbuttonpositionpacketall

		 push 358 // Y
		 push 0x9C // X
		 lea ecx, [esi + 0x112F8]
		 // Pet
		 call bindbuttonpositionpacketall




		 jmp bindbuttonpositionjmp

	}
}


DWORD cReturn1 = 0x477EF7;
DWORD cReturn2 = 0x477F69;
_declspec(naked) void dwCharacterScreen()
{

	_asm
	{
		add eax, -0x140
		sar eax, 0x02
		jmp cReturn1
	}
}


_declspec(naked) void dwCharacterScreen2()
{
	_asm
	{

		add eax, -0x140
		sar eax, 0x02
		jmp cReturn2


	}

}

DWORD cReturn3 = 0x477FF1;
_declspec(naked) void dwCharacterScreen3()
{
	_asm
	{

		add eax, -0x200
		sar eax, 0x02
		jmp cReturn3


	}

}



DWORD cReturn4 = 0x47807D;
_declspec(naked) void dwCharacterScreen4()
{
	_asm
	{

		add eax, -0x300
		sar eax, 0x02
		jmp cReturn4


	}

}



DWORD cReturn5 = 0x478109;
_declspec(naked) void dwCharacterScreen5()
{
	_asm
	{

		add eax, -0x440
		sar eax, 0x02
		jmp cReturn5


	}

}


DWORD cReturn7 = 0x4759B8;
_declspec(naked) void dwCharacterScreen7()
{
	_asm
	{

		add eax, -0x480
		sar eax, 0x02
		jmp cReturn7


	}

}


DWORD cReturn8 = 0x475A0A;
int cPosx = 0x631AB0;

_declspec(naked) void dwCharacterScreen8()
{
	_asm
	{
		pushad
		movzx ecx, word ptr ds : [0x07AB0D8]
		cmp ecx, 0x384
		popad
		jbe dwRes800
		pushad
		movzx ecx, word ptr ds : [0x07AB0D8]
		cmp ecx, 0x47F
		popad
		jbe dwRes1024
		pushad
		movzx ecx, word ptr ds : [0x07AB0D8]
		cmp ecx, 0x4AF
		popad
		jbe dwRes1152


		pushad
		movzx ecx, word ptr ds : [0x07AB0D8]
		cmp ecx, 0x513
		popad
		jbe originalcode10

		pushad
		movzx ecx, word ptr ds : [0x07AB0D8]
		cmp ecx, 0x577
		popad
		jbe dwRes1360

		pushad
		movzx ecx, word ptr ds : [0x07AB0D8]
		cmp ecx, 0x68F
		popad
		jbe dwRes1600


		pushad
		movzx ecx, word ptr ds : [0x07AB0D8]
		cmp ecx, 0x6A3
		popad
		jbe dwRes1680

		pushad
		movzx ecx, word ptr ds : [0x07AB0D8]
		cmp ecx, 1929
		popad
		jbe dwRes1920


		pushad
		movzx ecx, word ptr ds : [0x07AB0D8]
		cmp ecx, 0x7BB
		popad
		jbe dwRes1920

		originalcode10 :
		mov esi, 0x25
			fadd dword ptr ds : [ebx]
			call cPosx
			jmp cReturn8




		dwRes800:
		mov esi, -0x14
			fadd dword ptr ds : [ebx]
			call cPosx
			jmp cReturn8


			dwRes1024 :
		mov esi, -0x0A
			fadd dword ptr ds : [ebx]
			call cPosx
			jmp cReturn8
			// tudo ok atÃ© agora , pode entrar no jogo

			dwRes1152 :
		mov esi, 0x0A
			fadd dword ptr ds : [ebx]
			call cPosx
			jmp cReturn8

			dwRes1360 :
		mov esi, 0x3C
			fadd dword ptr ds : [ebx]
			call cPosx
			jmp cReturn8

			dwRes1600 :
		mov esi, 0x7D
			fadd dword ptr ds : [ebx]
			call cPosx
			jmp cReturn8

			dwRes1680 :
		mov esi, 0x8C
			fadd dword ptr ds : [ebx]
			call cPosx
			jmp cReturn8


			dwRes1920 :
		mov esi, 0x63
			fadd dword ptr ds : [ebx]
			call cPosx
			jmp cReturn8



	}

}


DWORD cReturn9 = 0x47599E;
_declspec(naked) void dwCharacterScreen9()
{
	_asm
	{

		sub eax, -0x20
		sar eax, 0x1
		mov[esp + 0x10], eax
		jmp cReturn9


	}

}






__declspec(naked) void wwconf() // funÃ§Æ¡es de acordo com se tÃ¡ ativado ou desativado!
{
	_asm
	{

		cmp byte ptr ds : [Traje_Pointer] , 1
		je exit2

		mov byte ptr ds : [original] , 0x0000
		mov[ebx + 0x0914484], al
		cmp[ebx + 0x0914484], 0x96 // se o equipamento for de type 150 
		je remove2 // entÄƒo remova e adicione 0
		jmp nameReturn // retorne para a funÃ§Äƒo


		remove2 :
		push ebx
			mov ebx, 0x0000
			mov byte ptr[ebx + 0x0914493], 0x0000
			pop ebx
			jmp nameReturn


			exit2 :
		mov[ebx + 0x0914484], al
			jmp nameReturn


	}
}




__declspec(naked) void wwwconf()
{
	_asm
	{
		cmp byte ptr ds : [Traje_Pointer] , 1
		je Exit3

		push ebx
		mov ebx, 0x0000
		mov[ebx + 0x0914490], 0x000
		pop ebx
		jmp nameReturn2

		exit3 :
		push ebx
			mov ebx, 0x0000
			mov[ebx + 0x0914490], edx
			pop ebx
			jmp nameReturn2







	}
}

_declspec(naked) void onff()
{
	_asm
	{
		cmp byte ptr ds : [Traje_Pointer] , 1
		jne tirar

		mov[esi + 0x00000AC], 00000001 // 01 = EQUIPOU FANTASIA
		jmp retorno

		tirar :
		mov[esi + 0x00000AC], 0x0000000 // 00 = SEM FANTASIA
			jmp retorno

	}
}

__declspec(naked) void conff()
{
	_asm
	{
		cmp byte ptr ds : [Traje_Pointer] , 1
		je exitt

		desativar2 :
		nop
			jmp return2

			exitt :
		movzx ax, byte ptr[eax + 0x000A]
			jmp return2

	}
}


void anticheat() {

	if (*(BYTE*)0x0044A61F == 0x70) {
		ExitProcess(0);
	}

	if (*(BYTE*)0x005B4A02 == 0x00) {
		ExitProcess(0);
	}

	if (*(BYTE*)0x00414F31 == 0x00) {
		ExitProcess(0);
	}

	if (*(BYTE*)0x005B5475 == 0x00) {
		ExitProcess(0);
	}

	if (*(BYTE*)0x005B74F2 == 0x00) {
		ExitProcess(0);
	}

	if (*(BYTE*)0x005957A5 == 0xB3) {
		ExitProcess(0);
	}

	if (*(BYTE*)0x004EA005 == 0x02) {
		ExitProcess(0);
	}

	if (*(BYTE*)0x0044C1CE == 0x81) {
		ExitProcess(0);
	}

	if (*(BYTE*)0x004B785B == 0x80) {
		ExitProcess(0);
	}

	if (*(BYTE*)0x005B546F == 0x90) {
		ExitProcess(0);
	}

	if (*(BYTE*)0x005B3F81 == 0x90) {
		ExitProcess(0);
	}

	if (*(BYTE*)0x00414F2B == 0x90) {
		ExitProcess(0);
	}


}


BOOL CheckIp(string ip)
{
	char ipGame[20];
	DWORD dwOldProtect;
	::VirtualProtect((void*)0x007C0DD0, sizeof(ipGame), PAGE_READWRITE, &dwOldProtect);
	::ReadProcessMemory(GetCurrentProcess(), (void*)0x007C0DD0, &ipGame, sizeof(ipGame), 0);
	::VirtualProtect((void*)0x007C0DD0, sizeof(ipGame), dwOldProtect, &dwOldProtect);

	//return true;
	if (strcmp(ipGame, decrypt_const(ip, globalEncryptKey).c_str()) != 0)
	{
		return false;
	}

	return true;
}


BOOL CheckStringWindow(string ip)
{
	char ipGame[20];
	
	DWORD dwOldProtect;
	::VirtualProtect((void*)0x00747094, sizeof(ipGame), PAGE_READWRITE, &dwOldProtect);
	::ReadProcessMemory(GetCurrentProcess(), (void*)0x00747094, &ipGame, sizeof(ipGame), 0);
	::VirtualProtect((void*)0x00747094, sizeof(ipGame), dwOldProtect, &dwOldProtect);

	//return true;
	if (strcmp(ipGame, decrypt_const(ip, globalEncryptKey).c_str()) != 0)
	{
		return false;
	}

	return true;
}





void TxtCheckWindow() {
	POINT p;
	HWND DebugerFound = 0;
	for (int qy = 0; qy < 100; qy++) {
		for (int qx = 0; qx < 100; qx++) {
			p.x = qx * 20;
			p.y = qy * 20;
			DebugerFound = WindowFromPoint(p);
			char t[255];
			GetWindowTextA(DebugerFound, t, 225);


			if (strstr(t, "Spam Trade") ||
				strstr(t, "WallClimb") ||
				strstr(t, "See Item ID") ||
				strstr(t, "Skill Cut") ||
				strstr(t, "Spam Trade") ||
				strstr(t, "No Swin") ||
				strstr(t, "Jack") ||
				strstr(t, "Shaiya Hacker Ep 6") ||
				strstr(t, "Hit On Safe Zone") ||
				strstr(t, "Wall Jack") ||
				strstr(t, "Range jack") ||
				strstr(t, "Speed Jack (Anti-Debuff") ||
				strstr(t, "See Ranger/Assasin on Stealth") ||
				strstr(t, "Mount in Dungeon") ||
				strstr(t, "No Land Obstacle") ||
				strstr(t, "HACK") ||
				strstr(t, "debugger") ||
				strstr(t, "Debugger") ||
				strstr(t, "DEBUGGER") ||
				strstr(t, "Attach") ||
				strstr(t, "Hack") ||
				strstr(t, "hack") ||
				strstr(t, "HACKER") ||
				strstr(t, "Hacker") ||
				strstr(t, "hacker") ||
				strstr(t, "INJECT") ||
				strstr(t, "Inject") ||
				strstr(t, "inject") ||
				strstr(t, "Delite") ||
				strstr(t, "fck stop") ||
				strstr(t, "The HounD") ||
				strstr(t, "See Item ID") ||
				strstr(t, "Cam Limit") ||
				strstr(t, "Hit On Safe Zone") ||
				strstr(t, "Add Address Manually") ||
				strstr(t, "Memory View") ||
				strstr(t, "Process List") ||
				//strstr(t, "Not") ||
				strstr(t, "debug")) {

				unsigned char* Detect = (unsigned char*)GetProcAddress(GetModuleHandleA("kernel32.dll"), "OpenProcess");
				if (*(Detect + 6) == 0xEA) {
					Sleep(1);
				}
				ExitProcess(0);
			}
		}
	}
}



void H_Scan() {
	while (true) {
		TxtCheckWindow();
		//anticheat();
		Sleep(4000);
	}
}



// Quando voc� estiver usando cabe�alhos pr�-compilados, esse arquivo de origem ser� necess�rio para que a compila��o seja bem-sucedida.


LPCSTR cTitulo220 = "title220.tga"; // relic of mystra
LPCSTR cTitulo221 = "title221.tga"; // gs title
LPCSTR cTitulo222 = "title222.tga"; // gm title
LPCSTR cTitulo223 = "title223.tga"; // adm title
LPCSTR cTitulo224 = "title224.tga"; // dev title 
LPCSTR cTitulo225 = "title225.tga"; // mvp title
LPCSTR cTitulo226 = "title226.tga";
LPCSTR cTitulo227 = "title227.png";
LPCSTR cTitulo228 = "title228.png";
LPCSTR cTitulo229 = "title229.png";
LPCSTR cTitulo230 = "title230.png";
LPCSTR cTitulo231 = "title231.png";
LPCSTR cTitulo232 = "title232.png";
LPCSTR cTitulo233 = "title233.png";
LPCSTR cTitulo234 = "title234.png";
LPCSTR cTitulo235 = "title235.png";
LPCSTR cTitulo236 = "title236.png";
LPCSTR cTitulo237 = "title237.png";
LPCSTR cTitulo238 = "title238.png";
LPCSTR cTitulo239 = "title239.png";
LPCSTR cTitulo240 = "title240.png";
LPCSTR cTitulo241 = "title241.png";
LPCSTR cTitulo242 = "title242.png";
LPCSTR cTitulo243 = "title243.png";
LPCSTR cTitulo244 = "title244.png";
LPCSTR cTitulo245 = "title245.png";
LPCSTR cTitulo246 = "title246.png";
LPCSTR cTitulo247 = "title247.png";
LPCSTR cTitulo248 = "title248.png";
LPCSTR cTitulo249 = "title249.png";
LPCSTR cTitulo250 = "title250.png";
LPCSTR HP_Bar_New = "player_hpbar.tga";
LPCSTR HP_Bar_Bg = "monster_hpbar_bg.tga";
DWORD cGetCall = 0x0057B950;
DWORD cAllocReturn = 0x0044F5D9;
_declspec(naked) void cAllocTitle()
{
	_asm {


		push 0x08
		push 0x80
		push HP_Bar_New
		push 0x00748194
		lea ecx, [esi + 0x00142050]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo220
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141000]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo221
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141020]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo222
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141040]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo223
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141060]
		call cGetCall


		push 0x40
		push 0x100
		push cTitulo224
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141080]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo225
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141100]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo226
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141120]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo227
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141140]
		call cGetCall


		push 0x40
		push 0x100
		push cTitulo228
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141160]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo229
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141180]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo230
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141200]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo231
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141220]
		call cGetCall


		push 0x40
		push 0x100
		push cTitulo232
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141240]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo233
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141260]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo234
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141280]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo235
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141300]
		call cGetCall


		push 0x40
		push 0x100
		push cTitulo236
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141320]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo237
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141340]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo238
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141360]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo239
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141380]
		call cGetCall


		push 0x40
		push 0x100
		push cTitulo240
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141400]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo241
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141420]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo242
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141440]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo243
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141460]
		call cGetCall


		push 0x40
		push 0x100
		push cTitulo244
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141480]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo245
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141500]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo246
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141520]
		call cGetCall

		push 0x40
		push 0x100
		push cTitulo247
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141540]
		call cGetCall


		push 0x40
		push 0x100
		push cTitulo248
		push 0x00748194 // interface
		lea ecx, [esi + 0x00141560]
		call cGetCall


		push 0x20
		push 0x20
		PUSH 0x0074AA34; // | Arg2 = 0074AA34 ASCII "mon_fire_ex.tga"

		jmp cAllocReturn

	}
}


DWORD Porcentage = 0;
DWORD Display_HP_Bar = 0x0057C3F0;
DWORD Send_Pos = 0x00631AB0;
DWORD Return_HP_Bar = 0x0045385A;
_declspec(naked) void HP_Bar_Main() {
	_asm {

		cmp byte ptr ds : [Dark_Pointer] , 01
		je Check_Country_Dark
		cmp byte ptr ds : [Light_Pointer] , 01
		je Check_Country_Light
		jmp originalcode


		Check_Country_Light :

		cmp byte ptr ds : [esi + 0x000002B7] , 0x00
			je Render_HP
			cmp byte ptr ds : [Dark_Pointer] , 01
			je Render_HP

			jmp originalcode


			Check_Country_Dark :
		cmp byte ptr ds : [esi + 0x000002B7] , 0x01
			je Render_HP
			cmp byte ptr ds : [Light_Pointer] , 01
			je Render_HP

			jmp originalcode

			Render_HP :
		cmp dword ptr ds : [esi + 0x0000015C] , 00  // current hp
			je originalcode
			sub dword ptr ds : [esp + 0x10] , 06
			fld dword ptr ds : [esp + 0x1C]
			push eax
			push ecx
			fstp dword ptr ds : [esp]
			fld dword ptr ds : [esp + 0x20]
			mov eax, 0x00748498
			fld qword ptr ss : [eax]
			fsub st(1), st(0)
			fxch st(1)
			call Send_Pos
			fild dword ptr ds : [esi + 0x318]
			fisub dword ptr ds : [esi + 0x00000318]
			add eax, 0x12
			push eax
			fadd dword ptr ds : [esp + 0x20]
			fiadd[esp + 0x1C]
			FADDP ST(1), ST
			mov eax, 0x00748428
			fsub qword ptr ss : [eax]
			call Send_Pos
			sub eax, 0x1C
			mov ecx, [esp + 0x2C]
			push eax
			call Function_Crack_1
			fld dword ptr ds : [esp + 0x1C]
			push eax
			push ecx
			fstp dword ptr ds : [esp]
			fld dword ptr ds : [esp + 0x20]
			mov eax, 0x00748498
			fld qword ptr ss : [eax]
			fsub st(1), st(0)
			fxch st(1)
			call Send_Pos
			fild dword ptr ds : [esi + 0x318]
			fisub[esi + 0x00000318]
			add eax, 0x13
			push eax
			fadd dword ptr ds : [esp + 0x20]
			fiadd[esp + 0x1C]
			FADDP ST(1), ST
			mov eax, 0x00748428
			fsub qword ptr ss : [eax]
			call Send_Pos
			sub eax, 0x1C
			mov ecx, [esp + 0x2C]
			push eax
			call Function_Crack_2
			add dword ptr ds : [esp + 0x10] , 06


			originalcode :
			cmp dword ptr ds : [0x913464] , 0x02
			jmp Return_HP_Bar

			Function_Crack_1 :
		sub esp, 0x08
			fldz
			push ebx
			push esi
			fstp dword ptr ds : [esp + 0x08]
			mov esi, ecx
			mov ecx, [esp + 0x20]
			xor bl, bl
			mov eax, 0x0000001E
			lea ebx, [ebx]
			cmp ecx, [eax * 4 + 0x007AEE08]
			sub eax, 0x01
			cmp eax, 0x0F
			mov bl, al
			mov eax, dword ptr ds : [0x022B6998]
			mov ecx, [eax]
			mov edx, [ecx + 0x00000114]
			push 02
			push 05
			push 00
			push eax
			call edx
			mov eax, dword ptr ds : [0x022B6998]
			mov ecx, [eax]
			mov edx, [ecx + 0x00000114] // qword = doble
			push 02
			push 06
			push 00
			push eax
			call edx
			movzx eax, bl
			mov[esp + 0x0C], eax
			inc eax
			mov[esp + 0x20], eax
			sub esp, 0x10
			mov eax, [esp + 0x28]
			fild dword ptr ds : [esp + 0x30]
			fld qword ptr ss : [0x00748258] // doble 1.00
			fmul st(1), st(0)
			fxch st(1)
			fstp dword ptr ds : [esp + 0x30]
			fld dword ptr ds : [esp + 0x30]
			fstp dword ptr ds : [esp + 0x0C]
			fimul[esp + 0x1C]
			fstp dword ptr ds : [esp + 0x30]
			fld dword ptr ds : [esp + 0x30]
			fstp dword ptr ds : [esp + 0x08]
			fld dword ptr ds : [esp + 0x18]
			fld qword ptr ss : [0x00748258] // doble 1.00
			fadd st(0), st(1)
			fstp dword ptr ds : [esp + 0x30]
			fld dword ptr ds : [esp + 0x30]
			fstp dword ptr ds : [esp + 0x04]
			fadd qword ptr ss : [0x00748260] // doble 0
			fstp dword ptr ds : [esp + 0x30]
			fld dword ptr ds : [esp + 0x30]
			fstp dword ptr ds : [esp]
			push 0x08
			fld dword ptr ds : [esp + 0x30]
			push 0x64
			push ecx
			mov ecx, [esp + 0x30]
			fstp dword ptr ds : [esp]
			push eax
			push ecx
			push - 0x01
			lea ecx, dword ptr ds : [0x007C4A68 + 0x00142000]
			call Display_HP_Bar
			pop esi
			pop ebx
			add esp, 0x08
			ret 0x0010


			Function_Crack_2 :
			pushad
			pushfd
			mov eax, [esi + 0x0000015C]
			mov ebx, [esi + 0x00000158]
			sub eax, ebx
			imul eax, eax, 0x64
			cdq
			mov ebx, [esi + 0x0000015C]
			idiv ebx
			mov ebx, 0x00000064
			sub ebx, eax
			mov eax, ebx
			mov[Porcentage], eax
			popfd
			popad

			sub esp, 0x08
			fldz
			push ebx
			push esi
			fstp dword ptr ds : [esp + 0x08]
			mov esi, ecx
			mov ecx, [esp + 0x20]
			xor bl, bl
			mov eax, 0x0000001E
			lea ebx, [ebx]
			cmp ecx, [eax * 0x4 + 0x007AEE08]
			sub eax, 0x01
			cmp eax, 0x0F
			mov bl, al
			mov eax, dword ptr ds : [0x022B6998]
			mov ecx, [eax]
			mov edx, [ecx + 0x00000114]
			push 02
			push 05
			push 00
			push eax
			call edx
			mov eax, dword ptr ds : [0x022B6998]
			mov ecx, [eax]
			mov edx, [ecx + 0x00000114]
			push 02
			push 06
			push 00
			push eax
			call edx
			movzx eax, bl
			mov eax, 0x00000001
			mov[esp + 0x0C], eax
			add eax, 0x01
			mov[esp + 0x20], eax
			sub esp, 0x10
			mov eax, [esp + 0x28]
			fild dword ptr ds : [esp + 0x30]
			fld qword ptr ss : [0x00748258]
			fmul st(1), st(0)
			fxch st(1)
			fstp dword ptr ds : [esp + 0x30]
			fld dword ptr ds : [esp + 0x30]
			fstp dword ptr ds : [esp + 0x0C]
			fimul[esp + 0x1C]
			fstp dword ptr ds : [esp + 0x30]
			fld dword ptr ds : [esp + 0x30]
			fstp dword ptr ds : [esp + 0x08]
			fld dword ptr ds : [esp + 0x18]
			fld qword ptr ss : [0x00748258]
			fadd st(0), st(1)
			fstp dword ptr ds : [esp + 0x30]
			fld dword ptr ds : [esp + 0x30]
			fstp dword ptr ds : [esp + 0x04]
			fadd qword ptr ss : [0x00748260]
			fstp dword ptr ds : [esp + 0x30]
			fld dword ptr ds : [esp + 0x30]
			fstp dword ptr ds : [esp]
			push ebx
			mov ebx, [Porcentage]
			mov[esp + 0x04], ebx
			pop ebx
			mov[esp + 0x04], 0x3F800000
			push 0x08
			fld dword ptr ds : [esp + 0x30]
			push[Porcentage]
			push ecx
			mov ecx, [esp + 0x30]
			fstp dword ptr ds : [esp]
			push eax
			push ecx
			push - 0x01
			lea ecx, dword ptr ds : [0x007C4A68 + 0x00142050]// monster hp bar
			call Display_HP_Bar
			pop esi
			pop ebx
			add esp, 0x08
			ret 0x0010

	}
}

DWORD dwIconRender = 0x04B7170;
DWORD dwBagRetn = 0x51A6A7;
_declspec(naked) void Bag()
{

	_asm
	{

		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xB5
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xB5
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xB5
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xB5
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xB5
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xB5
		je bFireLv2
		// WATER NOW
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xB6
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xB6
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xB6
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xB6
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xB6
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xB6
		je bWaterLv2
		// EARTH NOW
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xB7
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xB7
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xB7
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xB7
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xB7
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xB7
		je bEarthLv2
		//WIND
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xB8
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xB8
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xB8
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xB8
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xB8
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xB8
		je bWindLv2
		//FIRE
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xB9
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xB9
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xB9
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xB9
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xB9
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xB9
		je bFireLv2
		// WATER NOW
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xBA
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xBA
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xBA
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xBA
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xBA
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xBA
		je bWaterLv2
		// EARTH NOW
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xBB
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xBB
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xBB
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xBB
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xBB
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xBB
		je bEarthLv2
		//WIND NOW
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xBC
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xBC
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xBC
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xBC
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xBC
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xBC
		je bWindLv2
		// NOVOS ELEMENTOS AGORA 
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0x92
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0x92
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0x92
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0x92
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0x92
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0x92
		je bFireLv2
		// WATER NOW
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0x93
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0x93
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0x93
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0x93
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0x93
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0x93
		je bWaterLv2
		// EARTH NOW
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0x94
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0x94
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0x94
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0x94
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0x94
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0x94
		je bEarthLv2
		//WIND
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0x95
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0x95
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0x95
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0x95
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0x95
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0x95
		je bWindLv2
		//FIRE
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xB1
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xB1
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xB1
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xB1
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xB1
		je bFireLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xB1
		je bFireLv2
		// WATER NOW
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xB2
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xB2
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xB2
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xB2
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xB2
		je bWaterLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xB2
		je bWaterLv2
		// EARTH NOW
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xB3
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xB3
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xB3
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xB3
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xB3
		je bEarthLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xB3
		je bEarthLv2
		//WIND NOW
		cmp byte ptr ds : [eax + 0x0090E2FE] , 0xB4
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x1] , 0xB4
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x2] , 0xB4
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x3] , 0xB4
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x4] , 0xB4
		je bWindLv2
		cmp byte ptr ds : [eax + 0x0090E2FE + 0x5] , 0xB4
		jne originalcode
		jmp bWindLv2

		originalcode :
		mov edx, [esp + 0x1C]
			mov eax, [esp + 0x10]
			push 0x01
			push 0x00
			push edx
			push ebx
			push edi
			push eax
			push ebp
			push ecx
			lea ecx, [esi + 0x30]
			call dwIconRender
			jmp dwBagRetn


			bWindLv2 :
		mov edx, [esp + 0x1C]
			mov eax, [esp + 0x10]
			push 0x01
			push 0x00
			push edx
			push ebx
			push edi
			push eax
			push ebp
			push ecx
			lea ecx, [esi + 0x30]
			call dwIconRender
			jmp bWindShow

			bEarthLv2 :
		mov edx, [esp + 0x1C]
			mov eax, [esp + 0x10]
			push 0x01
			push 0x00
			push edx
			push ebx
			push edi
			push eax
			push ebp
			push ecx
			lea ecx, [esi + 0x30]
			call dwIconRender
			jmp bEarthShow

			bWaterLv2 :
		mov edx, [esp + 0x1C]
			mov eax, [esp + 0x10]
			push 0x01
			push 0x00
			push edx
			push ebx
			push edi
			push eax
			push ebp
			push ecx
			lea ecx, [esi + 0x30]
			call dwIconRender
			jmp bWaterShow

			bFireLv2 :
		mov edx, [esp + 0x1C]
			mov eax, [esp + 0x10]
			push 0x01
			push 0x00
			push edx
			push ebx
			push edi
			push eax
			push ebp
			push ecx
			lea ecx, [esi + 0x30]
			call dwIconRender
			jmp bFireShow

			bWindShow :
		mov edx, [esp + 0x1C]
			mov eax, [esp + 0x10]
			push 0x01
			push 0x01
			push edx
			push 0xB8
			push 0x1E
			jmp cShow

			bEarthShow :
		mov edx, [esp + 0x1C]
			mov eax, [esp + 0x10]
			push 01
			push 01
			push edx
			push 0xB7
			push 0x1E
			jmp cShow

			bWaterShow :
		mov edx, [esp + 0x1C]
			mov eax, [esp + 0x10]
			push 0x01
			push 0x01
			push edx
			push 0xB6
			push 0x1E
			jmp cShow

			bFireShow :
		mov edx, [esp + 0x1C]
			mov eax, [esp + 0x10]
			push 0x01
			push 0x01
			push edx
			push 0xB5
			push 0x1E
			jmp cShow



		cShow:
		add eax, 0x0E
			push eax
			push ebp
			push - 0x01
			call dwIconRender
			jmp dwBagRetn
	}



}

DWORD dwBarRtn = 0x0501317;
_declspec(naked) void Bar()
{

	_asm {

		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xB5
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xB5
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xB5
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xB5
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xB5
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xB5
		je aFireLv2
		// WATER NOW
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xB6
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xB6
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xB6
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xB6
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xB6
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xB6
		je aWaterLv2
		// EARTH NOW
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xB7
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xB7
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xB7
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xB7
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xB7
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xB7
		je aEarthLv2
		//WIND
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xB8
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xB8
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xB8
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xB8
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xB8
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xB8
		je aWindLv2
		//FIRE
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xB9
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xB9
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xB9
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xB9
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xB9
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xB9
		je aFireLv2
		// WATER NOW
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xBA
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xBA
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xBA
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xBA
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xBA
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xBA
		je aWaterLv2
		// EARTH NOW
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xBB
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xBB
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xBB
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xBB
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xBB
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xBB
		je aEarthLv2
		//WIND NOW
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xBC
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xBC
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xBC
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xBC
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xBC
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xBC
		je aWindLV2




		// NEW ELEMENTS 
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0x92
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0x92
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0x92
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0x92
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0x92
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0x92
		je aFireLv2
		// WATER NOW
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0x93
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0x93
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0x93
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0x93
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0x93
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0x93
		je aWaterLv2
		// EARTH NOW
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0x94
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0x94
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0x94
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0x94
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0x94
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0x94
		je aEarthLv2
		//WIND
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0x95
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0x95
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0x95
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0x95
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0x95
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0x95
		je aWindLv2
		//FIRE
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xB1
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xB1
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xB1
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xB1
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xB1
		je aFireLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xB1
		je aFireLv2
		// WATER NOW
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xB2
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xB2
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xB2
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xB2
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xB2
		je aWaterLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xB2
		je aWaterLv2
		// EARTH NOW
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xB3
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xB3
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xB3
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xB3
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xB3
		je aEarthLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xB3
		je aEarthLv2
		//WIND NOW
		cmp byte ptr ds : [esi + 0x0090E2FE] , 0xB4
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x1] , 0xB4
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x2] , 0xB4
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x3] , 0xB4
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x4] , 0xB4
		je aWindLv2
		cmp byte ptr ds : [esi + 0x0090E2FE + 0x5] , 0xB4
		jne originalcode7
		jmp aWindLv2

		originalcode7 :
		push 0x01
			push 0x00
			push eax
			push ebx
			push ebp
			push ecx
			mov ecx, [esp + 0x28]
			push edx
			push - 0x01
			call dwIconRender
			jmp dwBarRtn


			aWaterLv2 :
		push 0x01
			push 0x00
			push eax
			push ebx
			push ebp
			push ecx
			mov ecx, [esp + 0x28]
			push edx
			push - 0x01
			call dwIconRender
			jmp aWaterShow



		aWindLv2:
		push 0x01
			push 0x00
			push eax
			push ebx
			push ebp
			push ecx
			mov ecx, [esp + 0x28]
			push edx
			push - 0x01
			call dwIconRender
			jmp aWindShow


			aFireLv2 :
		push 0x01
			push 0x00
			push eax
			push ebx
			push ebp
			push ecx
			mov ecx, [esp + 0x28]
			push edx
			push - 0x01
			call dwIconRender
			jmp aFireShow


			aEarthLv2 :
		push 0x01
			push 0x00
			push eax
			push ebx
			push ebp
			push ecx
			mov ecx, [esp + 0x28]
			push edx
			push - 0x01
			call dwIconRender
			jmp aEarthShow


			aWindShow :
		mov ecx, [esp + 0x18]
			mov edx, [esp + 0x1C]
			push 0x1
			push 0x1
			push 0x1
			push 0xB8
			push 0x1E
			jmp aIconShow


			aEarthShow :
		mov ecx, [esp + 0x18]
			mov edx, [esp + 0x1C]
			push 0x1
			push 0x1
			push 0x1
			push 0xB7
			push 0x1E
			jmp aIconShow

			aWaterShow :
		mov ecx, [esp + 0x18]
			mov edx, [esp + 0x1C]
			push 0x1
			push 0x1
			push 0x1
			push 0xB6
			push 0x1E
			jmp aIconShow


			aFireShow :
		mov ecx, [esp + 0x18]
			mov edx, [esp + 0x1C]
			push 0x1
			push 0x1
			push 0x1
			push 0xB5
			push 0x1E
			jmp aIconShow

			aIconShow :
		add ecx, 0x0F
			push ecx
			push edx
			push - 0x1
			call dwIconRender
			jmp dwBarRtn





	}



}











DWORD dwEquipRetn = 0x0051A8BA;
_declspec(naked) void Equip()
{

	_asm
	{
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xB5
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xB5
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xB5
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xB5
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xB5
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xB5
		je cFireLv2
		// WATER NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xB6
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xB6
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xB6
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xB6
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xB6
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xB6
		je cWaterLv2
		// EATH NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xB7
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xB7
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xB7
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xB7
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xB7
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xB7
		je cEarthLv2
		//WIND NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xB8
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xB8
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xB8
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xB8
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xB8
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xB8
		je cWindLv2
		//TOPS NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xB9
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xB9
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xB9
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xB9
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xB9
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xB9
		je cFireLv2
		// WATER NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xBA
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xBA
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xBA
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xBA
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xBA
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xBA
		je cWaterLv2
		// EATH NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xBB
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xBB
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xBB
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xBB
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xBB
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xBB
		je cEarthLv2
		//WIND NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xBC
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xBC
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xBC
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xBC
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xBC
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xBC
		je cWindLv2



		// NEW ELEMENTS NOW


		cmp byte ptr ds : [edi + 0x090E2FE] , 0x92
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0x92
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0x92
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0x92
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0x92
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0x92
		je cFireLv2
		// WATER NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0x93
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0x93
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0x93
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0x93
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0x93
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0x93
		je cWaterLv2
		// EATH NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0x94
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0x94
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0x94
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0x94
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0x94
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0x94
		je cEarthLv2
		//WIND NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0x95
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0x95
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0x95
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0x95
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0x95
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0x95
		je cWindLv2
		//TOPS NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xB1
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xB1
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xB1
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xB1
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xB1
		je cFireLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xB1
		je cFireLv2
		// WATER NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xB2
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xB2
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xB2
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xB2
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xB2
		je cWaterLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xB2
		je cWaterLv2
		// EATH NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xB3
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xB3
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xB3
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xB3
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xB3
		je cEarthLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xB3
		je cEarthLv2
		//WIND NOW
		cmp byte ptr ds : [edi + 0x090E2FE] , 0xB4
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x1] , 0xB4
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x2] , 0xB4
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x3] , 0xB4
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x4] , 0xB4
		je cWindLv2
		cmp byte ptr ds : [edi + 0x090E2FE + 0x5] , 0xB4
		jne originalcode5
		jmp cWindLv2


		originalcode5 :
		push 0x00
			push 0x01
			push eax
			mov eax, [esp + 0x24]
			push ebp
			push eax
			push ecx
			lea ebp, [esi + 0x30]
			push edx
			mov ecx, ebp
			call dwIconRender
			jmp dwEquipRetn

			cEarthLv2 :
		push 0x00
			push 0x01
			push eax
			mov eax, [esp + 0x24]
			push ebp
			push eax
			push ecx
			lea ebp, [esi + 0x30]
			push edx
			mov ecx, ebp
			call dwIconRender
			jmp cEarthShow


			cWindLv2 :
		push 0x00
			push 0x01
			push eax
			mov eax, [esp + 0x24]
			push ebp
			push eax
			push ecx
			lea ebp, [esi + 0x30]
			push edx
			mov ecx, ebp
			call dwIconRender
			jmp cWindShow

			cWaterLv2 :
		push 0x00
			push 0x01
			push eax
			mov eax, [esp + 0x24]
			push ebp
			push eax
			push ecx
			lea ebp, [esi + 0x30]
			push edx
			mov ecx, ebp
			call dwIconRender
			jmp cWaterShow

			cFireLv2 :
		push 0x00
			push 0x01
			push eax
			mov eax, [esp + 0x24]
			push ebp
			push eax
			push ecx
			lea ebp, [esi + 0x30]
			push edx
			mov ecx, ebp
			call dwIconRender
			jmp cFireShow

			cWindShow :
		mov ecx, [esp + 0x10]
			push 0x01
			push 0x01
			push 0x01
			push 0xB8
			mov eax, [esp + 0x24]
			push 0x1E
			jmp cEleShow

			cEarthShow :
		mov ecx, [esp + 0x10]
			push 0x01
			push 0x01
			push 0x01
			push 0xB7
			mov eax, [esp + 0x24]
			push 0x1E
			jmp cEleShow

			cWaterShow :
		mov ecx, [esp + 0x10]
			push 0x01
			push 0x01
			push 0x01
			push 0xB6
			mov eax, [esp + 0x24]
			push 0x1E
			jmp cEleShow

			cFireShow :
		mov ecx, [esp + 0x10]
			push 0x01
			push 0x01
			push 0x01
			push 0xB5
			mov eax, [esp + 0x24]
			push 0x1E

			cEleShow:
		add eax, 0x0F
			push eax
			push ecx
			lea ebp, [esi + 0x30]
			push - 0x01
			call dwIconRender
			jmp dwEquipRetn

	}



}


DWORD x10Return = 0x005298A0;
_declspec(naked) void x10stats()

{
	_asm {
		pushad
		push 0x10
		call GetAsyncKeyState
		shr ax, 0xF
		cmp ax, 0x1
		popad
		jne x10original
		add dword ptr ds : [esi + 0x4C] , 0x0A
		jmp x10Return


		x10original :
		inc[esi + 0x4C]
			mov ecx, 0x0000FFFF
			jmp x10Return





	}


}



DWORD x10Return2 = 0x00529896;

DWORD x10Block = 0x005298AF;
_declspec(naked) void x10stats2()

{
	_asm {
		pushad
		push 0x10
		call GetAsyncKeyState
		shr ax, 0xF
		cmp ax, 0x1
		popad
		jne x10original2
		cmp word ptr ds : [esi + eax * 0x2 + 0x34] , 0x0A
		jna block

		x10original2 :
		cmp word ptr ds : [esi + eax * 0x2 + 0x34] , 0x0
			jmp x10Return2


			block :
		jmp x10Block


	}


}



DWORD x10Return3 = 0x005298A5;

_declspec(naked) void x10stats3()

{
	_asm {
		pushad
		push 0x10
		call GetAsyncKeyState
		shr ax, 0xF
		cmp ax, 0x1
		popad
		jne x10Originalcode3
		sub dword ptr ds : [esi + eax * 0x2 + 0x34] , 0x0A
		jmp x10Return3

		x10Originalcode3 :
		add[esi + eax * 0x2 + 0x34], cx
			jmp x10Return3


	}


}


DWORD x10block2 = 0x5298AF;
DWORD dwx10return = 0x00529886;
_declspec(naked) void dwX10Stat()

{

	_asm
	{

		pushad
		push 0x10
		call GetAsyncKeyState
		shr ax, 0xF
		cmp ax, 0x1
		popad
		jne originalcode22
		mov ecx, [esi + 0x4C]
		sub ecx, 0x0A
		test ecx, ecx
		jle x10block22
		add word ptr ds : [esi + eax * 0x2 + 0x40] , 0x0A
		jmp originalcode22


		originalcode22 :
		dec ecx
			mov[esi + 0x4C], ecx
			inc word ptr ds : [esi + eax * 0x2 + 0x40]
			jmp dwx10return

			x10block22 :
		jmp x10block2




	}



}


int skillbar_pointer1 = 0;
// 
DWORD skillbarnew6jmp = 0x0042B4FB;

DWORD skillbarnew6call1 = 0x006306C3;

DWORD skillbarnew6call2 = 0x004FFBC0;

__declspec(naked) void skillbar_main()
{

	_asm
	{
		push 0x12C
		call skillbarnew6call1
		add esp, 0x04
		mov[esp + 0x18], eax
		mov byte ptr[esp + 0x24], 0x21
		cmp eax, edi
		je packetmnsje
		push 0x02
		mov ecx, eax
		call skillbarnew6call2
		mov[skillbar_pointer1], eax
		mov byte ptr[eax + 0x04], 0x00
		mov byte ptr[eax + 0x08], 0x78
		jmp packetmnsjejmp
		packetmnsje :
		xor eax, eax
			packetmnsjejmp :
		mov[esp + 0x24], bl
			mov[esi + 0x298], eax
			mov eax, [skillbar_pointer1]
			mov bl, 0x00
			mov[eax + 0x20], bl
			mov eax, 0x022AAB3A
			mov byte ptr ds : [eax] , 0x02
			mov eax, dword ptr ds : [esi + 0x174]
			lea edx, dword ptr ds : [esi + 0x1CC]
			originalcode :
			jmp skillbarnew6jmp



	}
}












DWORD skillbar_add1jmp = 0x004A3E28;

DWORD skillbar_add1jnejmp = 0x004A3E04;
DWORD skillbar_add1call = 0x004FF6C0;
void __declspec(naked) skillbar_add1() {
	__asm {

		movzx ecx, byte ptr ds : [edi + 0xF4]
		movzx edx, byte ptr ds : [edi + 0xF5]
		push ecx
		push edx
		mov ecx, [skillbar_pointer1]
		call skillbar_add1call
		test eax, eax
		jne skillbar_addjnes
		movzx ecx, byte ptr ds : [edi + 0xF4]
		jmp skillbar_add1jmp

		skillbar_addjnes :
		jmp skillbar_add1jnejmp



	}
}


DWORD skillbar_add2jmp = 0x004A3F0B;

DWORD skillbar_add2call = 0x004FF6C0;

void __declspec(naked) skillbar_add2() {
	__asm {



		movzx eax, byte ptr ds : [edi + 0xFB]
		mov ecx, [skillbar_pointer1]
		push eax
		push 0x64
		call skillbar_add2call
		test eax, eax
		je skillbar_add2jes
		mov byte ptr ds : [edi + 0xFB] , -01
		skillbar_add2jes :
		movzx eax, byte ptr ds : [edi + 0xFB]
		push eax
		originalcode :
		jmp skillbar_add2jmp



	}
}



DWORD skillbar_add3jmp = 0x004FFCA2; //4FE582

DWORD skillbar_add3jejmp = 0x004FFCB7;


void __declspec(naked) skillbar_add3() {
	__asm {
		mov al, [esp + 0x28]
		cmp byte ptr ds : [esp + 0x28] , 0x02
		jnl skillbar_add3exits
		cmp byte ptr ds : [esp + 0x28] , 0x00
		je skillbar_add3jes
		jmp skillbar_add3jes

		skillbar_add3exits :
		jmp skillbar_add3jmp

			skillbar_add3jes :
		jmp skillbar_add3jejmp

			originalcode :
		jmp skillbar_add3jejmp



	}
}


DWORD skillbar_add4jmp = 0x005008C0;

DWORD skillbar_add4jejmp = 0x00500A6D;

void __declspec(naked) skillbar_add4() {
	__asm {
		cmp byte ptr ds : [esi + 0x11C] , 0x02
		je skillbar_add4jes
		mov eax, 0x007C0E8C
		mov eax, [eax]
		jmp skillbar_add4jmp

		skillbar_add4jes :
		jmp skillbar_add4jejmp

			originalcode :
		jmp skillbar_add4jejmp

	}
}



// 
DWORD skillbar_add5jmp = 0x00500F79;

DWORD skillbar_add5jajmp = 0x00500FC5;


void __declspec(naked) skillbar_add5() {
	__asm {
		cmp byte ptr ds : [esi + 0x11C] , 01
		ja skillbar_add5jajmps
		jmp skillbar_add5jmp

		skillbar_add5jajmps :
		jmp skillbar_add5jajmp

			originalcode :
		jmp skillbar_add5jajmp

	}
}




DWORD skillbar_add6jmp = 0x00500FBB;

void __declspec(naked) skillbar_add6() {
	__asm {

		mov byte ptr ds : [esi + 0x119] , 01
		cmp byte ptr ds : [esi + 0x119 + 0x3] , 01
		jne skillbar_add6jnejmps
		cmp byte ptr ds : [esi + 0x119 - 0x8] , 00
		sete al
		mov esi, [skillbar_pointer1]
		mov[esi + 0x20], al

		skillbar_add6jnejmps :
		jmp skillbar_add6jmp

			originalcode :
		jmp skillbar_add6jmp


	}
}

DWORD skillbar_add7jmp = 0x00501497;

DWORD skillbar_add7jejmp = 0x050155C;
DWORD skillbar_add7jnejmp = 0x005015AE;

void __declspec(naked) skillbar_add7() {
	__asm {

		cmp byte ptr ds : [edi + 0x11C] , 02
		je skillbar_add7jes
		cmp byte ptr ds : [edi + 0x11C] , 00
		jmp skillbar_add7jmp

		skillbar_add7jes :
		jmp skillbar_add7jmps
			mov edx, [esp + 0x14]
			jmp skillbar_add7jejmp //je

			skillbar_add7jmps :
		jmp skillbar_add7jnejmp //jne

			originalcode :
		jmp skillbar_add7jnejmp

	}
}


BYTE xz[] = "\x00\xCA\x9A\x3B\x00\xE1\xF5\x05\x80\x96\x98\x00\x40\x42\x0F\x00\xA0\x86\x01\x00\x10\x27\x00\x00\xE8\x03\x00\x00\x64\x00\x00\x00\x0A\x00\x00\x00\x01\x00\x00\x00";
DWORD* xzadr = (DWORD*)&xz; // 




void __declspec(naked) Members()
{
	__asm
	{
		push eax
		push ebx
		push edx
		push edi
		xor edi, edi
		mov ebx, xzadr
		m1 :
		xor edx, edx
			div dword ptr[ebx]
			cmp eax, 0x00
			jne m2
			cmp edi, 0x01
			jne m3
			m2 :
		add eax, 0x30
			mov byte ptr[ecx], al
			mov edi, 0x00000001
			inc ecx
			m3 :
		mov eax, edx
			add ebx, 0x04
			cmp dword ptr[ebx], 0x00
			jne m1
			pop edi
			pop edx
			pop ebx
			pop eax
			ret
	}
}



// All
//DWORD raidsysinj = 0x0227E334;

int raid_pointer = 0;
int raid_pointer_lead = 5;


// RaidInj1 hepsi
DWORD RaidInj1jmp = 0x53F229;

void __declspec(naked) RaidInj1()

{
	__asm
	{
		push ecx
		mov ecx, [raid_pointer]
		imul ecx, ecx, 0x1E
		add esi, ecx
		pop ecx
		push esi
		mov ecx, 0x022AA748
		mov[ecx], esi
		mov ecx, 0x022AA71C
		jmp RaidInj1jmp
	}
}

// RaidInj2 hepsi
DWORD RaidInj2jmp = 0x53FEDD;

void __declspec(naked) RaidInj2()

{
	__asm
	{
		mov ecx, [raid_pointer]
		imul ecx, ecx, 0x1E
		add esi, ecx
		push esi
		mov ecx, 0x022AA71C
		jmp RaidInj2jmp
	}
}


// RaidInj4 hepsi
DWORD RaidInj4jmp = 0x5410EB;

DWORD RaidInj4call = 0x451840;

void __declspec(naked) RaidInj4()

{
	__asm
	{
		mov eax, [raid_pointer]
		imul eax, eax, 0x1E
		add ebx, eax
		mov dword ptr[esp + 0x30], ebx
		call RaidInj4call
		jmp RaidInj4jmp

	}
}


// RaidInj5 hepsi
DWORD RaidInj5jmp = 0x54000F;

DWORD RaidInj5call = 0x451840;

void __declspec(naked) RaidInj5()

{
	__asm
	{
		mov eax, [raid_pointer]
		imul eax, eax, 0x1E
		add ebx, eax
		mov dword ptr[esp + 0x30], ebx
		call RaidInj5call
		jmp RaidInj5jmp

	}
}


// RaidInj6 hepsi


DWORD RaidInj6jmp = 0x4A42E0;

//-------------------
DWORD RaidInj6exjmp = 0x4A4949;

DWORD RaidInj6jgc = 0x4A470F;

void __declspec(naked) RaidInj6()

{
	__asm
	{
		cmp ebx, 0x00002AF9
		je pt1
		cmp ebx, 0x00002AFA
		je pt2
		cmp ebx, 0x00002AFB
		je pt3
		cmp ebx, 0x00002AFC
		je pt4
		cmp ebx, 0x00002AFD
		je pt5
		cmp ebx, 0x00001964
		jg RaidInj6jgs
		jmp RaidInj6jmp
		RaidInj6jgs :
		jmp RaidInj6jgc

			pt1 :
		mov[raid_pointer], 0x0
			jmp RaidInj6exjmp

			pt2 :
		mov[raid_pointer], 0x1
			jmp RaidInj6exjmp

			pt3 :
		mov[raid_pointer], 0x2
			jmp RaidInj6exjmp

			pt4 :
		mov[raid_pointer], 0x3
			jmp RaidInj6exjmp

			pt5 :
		mov[raid_pointer], 0x4
			jmp RaidInj6exjmp


	}
}


// RaidInj7 hepsi
DWORD RaidInj7jmp = 0x48D9A3;

DWORD RaidInj7call = 0x48D4A0;


void __declspec(naked) RaidInj7()

{
	__asm
	{

		cmp dword ptr[esp + 0x20], 0x00
		je leaderfirstje
		lea ecx, [esp + 0x20]
		push ecx
		mov dword ptr[esp + 0x24], 0x00001969
		mov ecx, edi
		jmp leaderfirstjmp
		leaderfirstje :
		mov dword ptr[esp + 0x20], 0x00001968
			mov ecx, edi
			lea edx, [esp + 0x20]
			push edx
			leaderfirstjmp :
		call RaidInj7call
			cmp dword ptr[raid_pointer_lead], 01
			jb RaidInj7jb
			lea ecx, [esp + 0x20]
			push ecx
			mov ecx, edi
			mov dword ptr[esp + 0x24], 0x00002AF9
			call RaidInj7call

			cmp dword ptr[raid_pointer_lead], 02
			jb RaidInj7jb
			lea ecx, [esp + 0x20]
			push ecx
			mov ecx, edi
			mov dword ptr[esp + 0x24], 0x00002AFA
			call RaidInj7call

			cmp dword ptr[raid_pointer_lead], 03
			jb RaidInj7jb
			lea ecx, [esp + 0x20]
			push ecx
			mov ecx, edi
			mov dword ptr[esp + 0x24], 0x00002AFB
			call RaidInj7call

			cmp dword ptr[raid_pointer_lead], 04
			jb RaidInj7jb
			lea ecx, [esp + 0x20]
			push ecx
			mov ecx, edi
			mov dword ptr[esp + 0x24], 0x00002AFC
			call RaidInj7call

			cmp dword ptr[raid_pointer_lead], 05
			jb RaidInj7jb
			lea ecx, [esp + 0x20]
			push ecx
			mov ecx, edi
			mov dword ptr[esp + 0x24], 0x00002AFD
			call RaidInj7call

			RaidInj7jb :
		jmp RaidInj7jmp



	}
}

// RaidInj8 hepsi
DWORD RaidInj8jmp = 0x48D9A3;

DWORD RaidInj8call = 0x48D4A0;

void __declspec(naked) RaidInj8()

{
	__asm
	{
		cmp dword ptr[esp + 0x20], 0x00
		mov ecx, edi
		je playerfirstje
		mov dword ptr[esp + 0x20], 0x00001969
		lea edx, [esp + 0x20]
		push edx
		jmp playerfirstjmp
		playerfirstje :
		lea eax, [esp + 0x20]
			mov dword ptr[esp + 0x20], 0x00001968
			push eax
			playerfirstjmp :
		call RaidInj8call

			cmp dword ptr[raid_pointer_lead], 01
			jb RaidInj8jb
			lea ecx, [esp + 0x20]
			push ecx
			mov ecx, edi
			mov dword ptr[esp + 0x24], 0x00002AF9
			call RaidInj8call

			cmp dword ptr[raid_pointer_lead], 02
			jb RaidInj8jb
			lea ecx, [esp + 0x20]
			push ecx
			mov ecx, edi
			mov dword ptr[esp + 0x24], 0x00002AFA
			call RaidInj8call

			cmp dword ptr[raid_pointer_lead], 03
			jb RaidInj8jb
			lea ecx, [esp + 0x20]
			push ecx
			mov ecx, edi
			mov dword ptr[esp + 0x24], 0x00002AFB
			call RaidInj8call

			cmp dword ptr[raid_pointer_lead], 04
			jb RaidInj8jb
			lea ecx, [esp + 0x20]
			push ecx
			mov ecx, edi
			mov dword ptr[esp + 0x24], 0x00002AFC
			call RaidInj8call

			cmp dword ptr[raid_pointer_lead], 05
			jb RaidInj8jb
			lea ecx, [esp + 0x20]
			push ecx
			mov ecx, edi
			mov dword ptr[esp + 0x24], 0x00002AFD
			call RaidInj8call

			RaidInj8jb :
		jmp RaidInj8jmp




	}
}


// RaidInj9 hepsi
DWORD RaidInj9jmp = 0x53DE78;


void __declspec(naked) RaidInj9()

{
	__asm
	{

		mov[esi + 0x10], 0x5D
		mov edx, [esi + 0x10]
		sub esp, 0x10
		jmp RaidInj9jmp

	}
}



// RaidInj10 hepsi
DWORD RaidInj10jmp = 0x53DECE;

DWORD RaidInj10call = 0x573FF0;


void __declspec(naked) RaidInj10()

{
	__asm
	{
		add esp, 0x0C
		add ebp, 0x0A
		add edi, 0xA
		pushad
		pushfd
		sub esp, 0x50
		mov dword ptr[esp + 0x30], 0x626D654D
		mov dword ptr[esp + 0x34], 0x3A737265
		mov byte ptr[esp + 0x38], 0x20
		lea ecx, [esp + 0x39]
		mov eax, [0x022AA728]
		mov eax, [eax]
		call Members
		mov byte ptr[ecx], 0x00
		lea edx, [esp + 0x30]
		mov ebx, 0x00000000
		push edx
		push ebx
		push 0xFFFFFF4D
		push edi
		push ebp
		push 0x022B69A0
		call RaidInj10call
		lea eax, [esp + 0x48]
		add esp, 0x18
		add esp, 0x50
		popfd
		popad
		add edi, 0x0F
		pushad
		pushfd
		sub esp, 0x50
		mov dword ptr[esp + 0x30], 0x656C6F52
		mov word ptr[esp + 0x34], 0x203A
		mov edx, [0x022AA730]
		cmp dword ptr[edx], 0x00
		je n1
		cmp dword ptr[edx], 0x01
		je n2
		mov dword ptr[esp + 0x36], 0x626D654D
		mov dword ptr[esp + 0x3A], 0x20737265
		mov word ptr[esp + 0x3E], 0x0020
		jmp n3
		n1 :
		mov dword ptr[esp + 0x36], 0x6461654C
			mov dword ptr[esp + 0x3A], 0x00007265
			jmp n3
			n2 :
		mov dword ptr[esp + 0x36], 0x20627553
			mov dword ptr[esp + 0x3A], 0x6461654C
			mov dword ptr[esp + 0x3E], 0x00007265
			n3 :
			lea edx, [esp + 0x30]
			mov ebx, 0x00000000
			push edx
			push ebx
			push 0xFFFFFF4D
			push edi
			push ebp
			push 0x022B69A0
			call RaidInj10call
			lea eax, [esp + 0x48]
			add esp, 0x18
			add esp, 0x50
			popfd
			popad
			add edi, 0x0F
			pushad
			pushfd
			sub esp, 0x50
			mov dword ptr[esp + 0x30], 0x72727543
			mov dword ptr[esp + 0x34], 0x20746E65
			mov dword ptr[esp + 0x38], 0x64696152
			mov dword ptr[esp + 0x3C], 0x2020203a
			mov edx, [raid_pointer]
			add edx, 0x31
			mov byte ptr[esp + 0x3F], dl
			mov byte ptr[esp + 0x40], 0x00
			lea edx, [esp + 0x30]
			mov ebx, 0x00000000
			push edx
			push ebx
			push 0xFFFFFF4D
			push edi
			push ebp
			push 0x022B69A0
			call RaidInj10call
			lea eax, [esp + 0x48]
			add esp, 0x18
			add esp, 0x50
			popfd
			popad
			add edi, 0x0F
			jmp RaidInj10jmp

	}
}


// RaidInj11 hepsi
DWORD RaidInj11jmp = 0x445D70;


void __declspec(naked) RaidInj11()

{
	__asm
	{
		lea eax, [eax + edx * 0x2]
		mov ecx, [raid_pointer]
		imul ecx, ecx, 0x1E
		add eax, ecx
		push eax
		mov ecx, 0x022AA71C
		jmp RaidInj11jmp

	}
}


// RaidInj12 hepsi
DWORD RaidInj12jmp = 0x53D771;

DWORD RaidInj12r1 = 0x022AA750;


DWORD RaidInj12r3 = 0x0227E338;


void __declspec(naked) RaidInj12()

{
	__asm
	{

		push eax
		push ecx
		push edx
		mov eax, ebx
		xor edx, edx
		mov ecx, 0x00000005
		div ecx
		mov ebx, edx
		mov ecx, RaidInj12r1
		mov[ecx], edx
		cmp dword ptr[esp + 0x1C], 0x005A9DBE
		je partychange
		cmp dword ptr[esp + 0x1C], 0x005AA325
		je partychange
		cmp dword ptr[esp + 0x1C], 0x005A98ED
		je partychange
		jmp exits
		partychange :
		mov dword ptr[raid_pointer], eax
			mov dword ptr[RaidInj12r3], eax
			exits :
		pop edx
			pop ecx
			pop eax
			jmp RaidInj12jmp

	}
}


// RaidInj14 hepsi
DWORD RaidInj14jmp = 0x53F32B;

DWORD RaidInj14call = 0x451840;

void __declspec(naked) RaidInj14()

{
	__asm
	{
		mov eax, [raid_pointer]
		imul eax, eax, 0x1E
		add ebx, eax
		mov[esp + 0x3C], ebx
		call RaidInj14call
		jmp RaidInj14jmp
	}
}


// RaidInj15 hepsi
DWORD RaidInj15jmp = 0x540D79;


void __declspec(naked) RaidInj15()

{
	__asm
	{
		mov ecx, [raid_pointer]
		imul ecx, ecx, 0x1E
		add esi, ecx
		push esi
		mov ecx, 0x022AA71C
		jmp RaidInj15jmp
	}
}

BYTE Adjust = 0;
BYTE Adjust_1 = 0;
LPCSTR cTitleon = "/titulo on";
LPCSTR cTitleoff = "/titulo off";
LPCSTR cMarket = "/mer";
LPCSTR Teleport_Command_1 = "/tp 1";
LPCSTR Teleport_Command_2 = "/tp 2";
LPCSTR Teleport_Command_3 = "/tp 3";
LPCSTR Teleport_Command_4 = "/tp 4";
LPCSTR Teleport_Command_5 = "/tp 5";
LPCSTR Teleport_Command_6 = "/tp 6";
LPCSTR Teleport_Command_7 = "/tp 7";
LPCSTR Teleport_Command_8 = "/tp 8";
LPCSTR Teleport_Command_9 = "/tp 9";
LPCSTR Teleport_Command_10 = "/tp 10";
LPCSTR Teleport_Command_11 = "/tp 11";
LPCSTR Teleport_Command_12 = "/tp 12";
LPCSTR Teleport_Command_13 = "/tp 13";
LPCSTR cRecreation = "/rr";
LPCSTR cAjustBuff_On = "/pbuff on";
LPCSTR cAjustBuff_Off = "/pbuff off";
LPCSTR cCraftCommand = "/craft";
LPCSTR cQuestpvp = "/quest pvp";
LPCSTR cQuestpvp2 = "/quest pvp2";
LPCSTR cEnableSmall = "/small on";
LPCSTR cDisableSmall = "/small off";
LPCSTR cEnableBoost = "/boost on";
LPCSTR cDisableBoost = "/boost off";
LPCSTR HP_Bar_1 = "/hpbar 1";
LPCSTR HP_Bar_2 = "/hpbar 2";
LPCSTR HP_Bar_3 = "/hpbar 3";
LPCSTR HP_Bar_4 = "/hpbar 4";


DWORD Send_Use_Item = 0x005EBB40;
__declspec(naked) void comando()
{
	_asm
	{


		push 6
		push Teleport_Command_1
		push edi
		call Comand_imput
		add esp, 0x0C
		test eax, eax
		jne Teleport_2

		pushad
		mov eax, 01 // new bag
		mov ebx, 06 // new slot
		push eax
		push ebx
		call Send_Use_Item
		add esp, 0x08
		popad

		push 0x0C
		push 0x2EE1
		push 0x16
		call mensagem
		add esp, 0x0C
		jmp cmd_jump


		Teleport_2 :
		push 6
			push Teleport_Command_2
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne Teleport_3
			pushad
			mov eax, 02 // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EE2
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump


			Teleport_3 :
		push 6
			push Teleport_Command_3
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne Teleport_4
			pushad
			mov eax, 03 // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EE3
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump


			Teleport_4 :
		push 6
			push Teleport_Command_4
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne Teleport_5
			pushad
			mov eax, 04 // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EE4
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump

			Teleport_5 :
		push 6
			push Teleport_Command_5
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne Teleport_6
			pushad
			mov eax, 05 // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EE5
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump

			Teleport_6 :
		push 6
			push Teleport_Command_6
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne Teleport_7
			pushad
			mov eax, 06 // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EE6
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump

			Teleport_7 :
		push 6
			push Teleport_Command_7
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne Teleport_8
			pushad
			mov eax, 07 // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EE7
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump

			Teleport_8 :
		push 6
			push Teleport_Command_8
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne Teleport_9
			pushad
			mov eax, 0x08 // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EE8
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump

			Teleport_9 :
		push 6
			push Teleport_Command_9
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne Teleport_10
			pushad
			mov eax, 0x09 // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EE9
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump

			Teleport_10 :
		push 6
			push Teleport_Command_10
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne Teleport_11
			pushad
			mov eax, 0x0A // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EEA
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump

			Teleport_11 :
		push 6
			push Teleport_Command_11
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne Teleport_12
			pushad
			mov eax, 0x0B // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EEB
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump

			Teleport_12 :
		push 6
			push Teleport_Command_12
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne Teleport_13
			pushad
			mov eax, 0x0C // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EEC
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump

			Teleport_13 :
		push 6
			push Teleport_Command_13
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne dwFirst
			pushad
			mov eax, 0x0D // new bag
			mov ebx, 06 // new slot
			push eax
			push ebx
			call Send_Use_Item
			add esp, 0x08
			popad

			push 0x0C
			push 0x2EED
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump


			dwFirst :
		push 0x9 // tamanho da string
			push comando1
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne ativar
			jmp remove3


			ativar :
		push 0x8
			push comando2
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne retorne
			jmp ative


			ative :
		mov byte ptr ds : [AsaAtivada] , 0x0
			push 0x5
			push 0x29D8
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump

			remove3 :
		mov byte ptr ds : [AsaAtivada] , 0x1
			push 0x5
			push 0x29D7
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump


			retorne :
		push 0x7
			push comand3
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne ative2
			jmp petremove

			petremove :
		mov byte ptr ds : [PetAtivado] , 0x1
			push 0x5
			push 0x29D9
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump


			ative2 :
		push 0x8
			push comand4
			push edi
			call Comand_imput
			add esp, 0x0C
			test eax, eax
			jne retorne2
			jmp ative3


			ative3 :
		mov byte ptr ds : [PetAtivado] , 0x0
			push 0x5
			push 0x29DA
			push 0x16
			call mensagem
			add esp, 0x0C
			jmp cmd_jump




		retorne2:
		push 0x000013D4
			jmp Cmd_retorno

	}
}


_declspec(naked) void asa()
{
	_asm
	{

		cmp byte ptr ds : [cBoostPointer] , 1
		je remove3

		cLabelOriginal :
		cmp[AsaAtivada], 0x0
			jne codeoriginal
			jmp remove3

			remove3 :
		cmp[AsaAtivada], 0x1
			je codeoriginal
			cmp dword ptr ds : [ecx + 0x0000104] , 0x1
			jmp saida6


			codeoriginal :
		cmp dword ptr ds : [ecx + 0x0000104] , 0x0
			jmp saida6



	}
}












_declspec(naked) void asa2()
{
	_asm
	{
		cmp byte ptr ds : [cBoostPointer] , 1
		je remove2

		cLabelOriginal :
		cmp[AsaAtivada], 0x0
			jne codeoriginal2
			jmp remove2

			remove2 :
		cmp[AsaAtivada], 0x1
			je codeoriginal2
			cmp dword ptr[ecx + 0x0000104], 0x1
			jmp saida7

			codeoriginal2 :
		cmp dword ptr[ecx + 0x0000104], 0x0
			jmp saida7





	}
}








_declspec(naked) void pet1()
{
	_asm
	{
		cmp byte ptr ds : [cBoostPointer] , 1
		je remova

		cLabelOriginal :
		cmp byte ptr ds : [PetAtivado] , 0x0
			jne originalcodepet1
			jmp remova


			remova :
		mov ecx, [esi + 0x0000430]
			jmp petre1


			originalcodepet1 :
		mov ecx, [esi + 0x0000430]
			jmp petret1




	}
}


_declspec(naked) void asa3()
{

	_asm {
		cmp byte ptr ds : [cBoostPointer] , 1
		je removeasa

		cLabelOriginal :
		cmp byte ptr ds : [AsaAtivada] , 0x0
			jne asaoriginalcode
			jmp removeasa

			removeasa :
		cmp dword ptr ds : [esi + 0x0000434] , 0x0
			jge ocultoasa
			jmp asaoriginalcode

			ocultoasa :
		jmp ocultoasa1

			asaoriginalcode :
		cmp dword ptr ds : [esi + 0x434] , 0x0
			jmp Asa3return





	}
}



_declspec(naked) void asa4()
{

	_asm {
		cmp byte ptr ds : [cBoostPointer] , 1
		je removeasa2

		cLabelOriginal :
		cmp byte ptr ds : [AsaAtivada] , 0x0
			jne asaoriginalcode2
			jmp removeasa2

			removeasa2 :
		test eax, eax
			jmp removerasa

			asaoriginalcode2 :
		test eax, eax
			je removerasa2
			jmp returnasa4


			removerasa2 :
		jmp removerasa


	}
}





_declspec(naked) void pet3()
{
	_asm {
		cmp byte ptr ds : [cBoostPointer] , 1
		je remove3

		cLabelOriginal :

		cmp byte ptr ds : [PetAtivado] , 0x0
			jne originalcodepet3
			jmp remove3


			remove3 :
		test eax, eax
			jmp petre2

			originalcodepet3 :
		test eax, eax
			je petre3
			jmp returnpet3

			petre3 :
		jmp petre2



	}
}



_declspec(naked) void pet4()
{
	_asm {
		cmp byte ptr ds : [cBoostPointer] , 1
		je remove5

		cLabelOriginal :
		cmp byte ptr ds : [PetAtivado] , 0x0
			jne originalcodepet4
			jmp remove5


			remove5 :
		mov ecx, [esi + 0x430]
			jmp petre1

			originalcodepet4 :
		mov ecx, [esi + 0x430]
			jmp returnpet4





	}


}



_declspec(naked) void pet5()
{
	_asm
	{
		cmp byte ptr ds : [cBoostPointer] , 1
		je remove6

		cLabelOriginal :
		cmp byte ptr ds : [PetAtivado] , 0x0
			jne originalcodepet5
			jmp remove6

			remove6 :
		cmp dword ptr ds : [ecx + 0x58] , 0x0
			je oculte
			jmp originalcodepet5


			oculte :
		jmp oculto

			originalcodepet5 :
		cmp dword ptr ds : [edx + 0x104] , 0x0
			jmp returnpet5



	}

}


DWORD SendPacketAddr = 0x005EA9F0;

void SendPacket(const char* buf, int len)
{
	void(*InternalCall)(const char*, int) = (void(__cdecl*)(const char*, int)) SendPacketAddr;
	(*InternalCall)(buf, len);
}

BYTE bTypeIDs[100];
BYTE bModels[100];
BYTE bPositions[100];

BYTE GetPositionByModelID(BYTE ModelID) {
	for (int i = 0; i < sizeof(bModels); i++) {

		if (bModels[i] == 0x00) {
			return 0x00;
		}

		if (bModels[i] == ModelID) {
			return bPositions[i];
		}
	}

	return 0x00;
}

BYTE GetModelIDByTypeID(BYTE TypeID) {
	for (int i = 0; i < sizeof(bTypeIDs); i++) {
		if (bTypeIDs[i] == 0x00) {
			return 0x00;
		}

		if (bTypeIDs[i] == TypeID) {
			return bModels[i];
		}
	}
}

DWORD dwExitSetModelID = 0x004E5B47;
DWORD dwContinueSetModelID = 0x004E5CA6;

BYTE ReturnedModelID;
BYTE TypeIDArg;

__declspec(naked) void SetModelID() {
	__asm {
		mov[esp + 0x14], bl

		mov byte ptr[esp + 0x20], 0x01

		mov bl, byte ptr[edi + 0x09]
		mov TypeIDArg, bl

		pushad
	}

	GetModelIDByTypeID(TypeIDArg);

	__asm {
		mov ReturnedModelID, al
		popad

		mov bl, ReturnedModelID

		cmp bl, 0x00

		je _label_original

		mov esi, 0x01

		jmp dwContinueSetModelID

		_label_original :
		cmp eax, 0xD0
			jmp dwExitSetModelID
	}
}

DWORD dwAllowModelsJne = 0x004144CE;
DWORD dwExitAllowModels = 0x0041431D;
DWORD dwSuccessAllowModels = 0x00414872;

__declspec(naked) void AllowModels() {
	__asm {
		pushad
		push al
		call GetPositionByModelID
		add esp, 0x04
		cmp al, 0x00
		popad
		jne _label_success

		_label_original :
		cmp al, 0x0A
			jne _label_jne

			jmp dwExitAllowModels

			_label_jne :
		jmp dwAllowModelsJne

			_label_success :
		jmp dwSuccessAllowModels
	}
}

DWORD dwOriginalCallSetPositionFunc = 0x00659391;
DWORD dwExitSetPosition = 0x004148CE;

BYTE ModelIDArg;
BYTE ReturnedPosition;

__declspec(naked) void SetPosition() {
	__asm {
		call dwOriginalCallSetPositionFunc

		pushad
		mov al, byte ptr[ebp + 0x3C1]
		mov ModelIDArg, al
	}

	GetPositionByModelID(ModelIDArg);

	__asm {
		mov ReturnedPosition, al
		popad

		cmp byte ptr[ReturnedPosition], 0x00
		je _label_original

		movzx eax, byte ptr[ReturnedPosition]

		push eax
		jmp dwExitSetPosition

		_label_original :
		push 0x22
			jmp dwExitSetPosition
	}
}

int PacketAddr;

void PacketAnalyze(DWORD dwPacketAddr) {

	if (*(WORD*)dwPacketAddr != 0x01FE)
		return;

	memcpy(bTypeIDs, (BYTE*)PacketAddr + 2, 49);
	memcpy(bModels, (BYTE*)PacketAddr + 52, 49);
	memcpy(bPositions, (BYTE*)PacketAddr + 102, 49);
}

DWORD dwExitGetPacket = 0x005F440C;

__declspec(naked) void GetPacket() {
	__asm {
		lea edx, [esp + 0x14]
		mov PacketAddr, edx
	}

	PacketAnalyze(PacketAddr);

	__asm {
		mov eax, [esp + 0x2014]
		jmp dwExitGetPacket
	}
}

void PacketMount() {
	SendPacket("\xFE\x01", 2);
}

DWORD dwExitCommand = 0x00486B09;
DWORD dwCommandCheck = 0x00632BD7;

char mount[] = "/mount";

__declspec(naked) void Command() {
	__asm {
		push 0x06
		push offset mount
		push edi
		call dwCommandCheck
		add esp, 0x0C
		test eax, eax
		je _send_packet_mount

		_label_original :
		push 0x05
			push 0x0074E044
			jmp dwExitCommand

			_send_packet_mount :
		pushad
			call PacketMount
			popad
			jmp _label_original
	}
}

DWORD dwExitChangeMountSpeed = 0x0041A581;
__declspec(naked) void ChangeMountSpeed() {
	__asm {
		pushfd
		cmp edx, 00
		je _label_velmax
		cmp edx, 01
		je _label_velmax
		cmp edx, 02
		je _label_velmax
		popfd

		_label_originalcode :
		mov[esi + 0x3C4], edx
			jmp dwExitChangeMountSpeed

			_label_velmax :
		popfd
			mov edx, 03
			jmp _label_originalcode
	}
}

DWORD dwFlashReturn = 0x00427C06;
_declspec(naked) void flash()
{
	///00436945 = jmp
	_asm
	{

		push eax
		mov eax, 0x00436400
		cmp[esp + 0x04], eax
		pop eax
		jb code2

		push eax
		mov eax, 0x00437100
		cmp[esp + 0x04], eax
		pop eax
		jg code2

		mov eax, 0x00
		ret

		code2 :
		sub esp, 0x20
			push esi
			push 0x05
			jmp dwFlashReturn

	}


}

DWORD dwExitEquip = 0x005190DF;

__declspec(naked) void ItemEquip() {

	__asm {

		cmp ebx, 30
		je _label_original
		cmp ebx, 100
		je _label_original
		cmp ebx, 95
		je _label_original

		cmp ebx, 80
		je _label_slot17

		cmp ebx, 79
		je _label_slot18

		_label_original :
		mov bl, al
			mov[esp + 0x0C], bl
			jmp dwExitEquip

			_label_slot17 :
		mov al, 17
			jmp _label_original

			_label_slot18 :
		mov al, 18
			jmp _label_original
	}
}

DWORD dwExitSetCorrectSlotByType = 0x0059FBAE;

__declspec(naked) void SetCorrectSlotByType() {
	__asm {
		mov al, [esp + 0x14]
		mov cl, [esp + 0x18]

		cmp al, 80
		je _label_slot17

		cmp al, 79
		je _label_slot18

		_label_return :
		jmp dwExitSetCorrectSlotByType

			_label_slot17 :
		mov ebx, 17
			jmp _label_return

			_label_slot18 :
		mov ebx, 18
			jmp _label_return
	}
}

DWORD dwExitItemRemove = 0x00518BDF;
DWORD dwAllowItemRemove = 0x00518C79;

__declspec(naked) void ItemRemove() {
	__asm {
		mov dl, [esp + 0x1C]

		cmp dl, 17
		je _label_allow_remove

		cmp dl, 18
		je _label_allow_remove

		cmp[esp + 0x0F], dl
		jmp dwExitItemRemove

		_label_allow_remove :
		jmp dwAllowItemRemove
	}
}

DWORD dwExitRemoveStackText = 0x004E6B37;

__declspec(naked) void RemoveStackText() {
	__asm {
		mov al, [esp + 0x04]

		cmp al, 80
		je _label_return

		cmp al, 79
		je _label_return

		movzx ecx, al
		jmp dwExitRemoveStackText

		_label_return :
		ret 0x04
	}
}

DWORD dwRemoveTypeEffectJe = 0x00519498;
DWORD dwExitRemoveTypeEffect = 0x00519078;

__declspec(naked) void RemoveTypeEffect() {
	__asm {
		cmp ebx, 17
		je _label_exit

		cmp ebx, 18
		je _label_exit

		cmp ebx, 95
		je _label_original_je

		cmp ebx, 30
		je _label_original_je

		cmp al, 0x19
		je _label_original_je

		cmp al, 30
		je _label_original_je

		_label_exit :
		jmp dwExitRemoveTypeEffect

			_label_original_je :
		jmp dwRemoveTypeEffectJe
	}
}

DWORD dwExitSetSlotIconSize = 0x005180D7;

__declspec(naked) void SetSlotIconSize() {
	__asm {
		mov eax, [esp + 0x04]

		cmp eax, 17
		je _label_size32

		cmp eax, 18
		je _label_size32

		cmp eax, 0x08
		jmp dwExitSetSlotIconSize

		_label_size16 :
		mov eax, 0x01
			ret 0x04

			_label_size32 :
			xor eax, eax
			ret 0x04
	}
}

float bag1 = 13.00f;

DWORD dwExitFixBag1BtnA = 0x00519BC0;

__declspec(naked) void FixBag1BtnA() {
	__asm {
		fld dword ptr[offset bag1]
		jmp dwExitFixBag1BtnA
	}
}

DWORD dwExitFixBag1BtnB = 0x0051A2A4;

__declspec(naked) void FixBag1BtnB() {
	__asm {
		fld dword ptr[offset bag1]
		jmp dwExitFixBag1BtnB
	}
}

float bag2A = 225.80f;
float bag2B = 61.00f;

DWORD dwExitFixBag2BtnA = 0x0051A2B7;

__declspec(naked) void FixBag2BtnA() {
	__asm {
		fld dword ptr[offset bag2A]
		jmp dwExitFixBag2BtnA
	}
}

DWORD dwExitFixBag2BtnB = 0x0051A2CA;

__declspec(naked) void FixBag2BtnB() {
	__asm {
		fld dword ptr[offset bag2B]
		jmp dwExitFixBag2BtnB
	}
}

float slot17PositionX = 57.00f;
float slot17PositionY = 229.00f;
float slot18PositionX = 169.00f;
float slot18PositionY = 145.00f;

DWORD dwExitSetSlotIconPosition = 0x0051A7F7;

__declspec(naked) void SetSlotIconPosition() {
	__asm {
		push eax
		mov eax, [slot17PositionX]
		mov dword ptr[esi + 17 * 0x8 + 0x794], eax
		mov eax, [slot17PositionY]
		mov dword ptr[esi + 17 * 0x8 + 0x798], eax
		mov eax, [slot18PositionX]
		mov dword ptr[esi + 18 * 0x8 + 0x794], eax
		mov eax, [slot18PositionY]
		mov dword ptr[esi + 18 * 0x8 + 0x798], eax
		pop eax

		fld dword ptr[esi + ebx * 0x8 + 0x794]
		jmp dwExitSetSlotIconPosition
	}
}

DWORD dwNotShowA = 0x005268BB;
DWORD dwExitShowSkillA = 0x00526200;

__declspec(naked) void ShowSkillA() {
	__asm {
		cmp word ptr[esi + 0x02], 56 // SKILL DE TRANSFORMAÃ‡ÃƒO ID
		jne _label_original

		push eax
		mov eax, 0x0090E66D
		cmp byte ptr[eax], 80 // Type
		jne _label_popeax
		cmp byte ptr[eax + 0x01], 05 // TypeID 
		jne _label_popeax
		pop eax

		_label_original :
		cmp esi, ebx
			je _label_notshow

			jmp dwExitShowSkillA

			_label_popeax :
		pop eax

			_label_notshow :
		jmp dwNotShowA
	}
}

DWORD dwExitShowSkillB = 0x00527139;
DWORD dwNotShowB = 0x005273AE;

__declspec(naked) void ShowSkillB() {
	__asm {
		cmp word ptr[edi + 0x02], 56 // SKILL DE TRANSFORMAÃ‡ÃƒO ID
		jne _label_original

		push eax
		mov eax, 0x0090E66D
		cmp byte ptr[eax], 80 // Type
		jne _label_popeax
		cmp byte ptr[eax + 0x01], 05 // TypeID 
		jne _label_popeax
		pop eax

		_label_original :
		test edi, edi
			je _label_notshow

			jmp dwExitShowSkillB

			_label_popeax :
		pop eax

			_label_notshow :
		jmp dwNotShowB
	}
}

float bag2C = 53.00f;

DWORD dwExitFixBag2BtnC = 0x00519BD3;

__declspec(naked) void FixBag2BtnC() {
	__asm {
		fld dword ptr[offset bag2C]
		jmp dwExitFixBag2BtnC
	}
}

DWORD dwExitFixBag2BtnD = 0x00519BE9;

__declspec(naked) void FixBag2BtnD() {
	__asm {
		fld dword ptr[offset bag2B]
		jmp dwExitFixBag2BtnD
	}
}


DWORD cor1 = 0xFF0000FF;

int SleepElmo1 = 50;
void GMColorChanger() {

	while (true) {
		Sleep(SleepElmo1);
		cor1 = 0xFFff0400;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0800;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0d00;
		Sleep(SleepElmo1);
		cor1 = 0xFFff1100;
		Sleep(SleepElmo1);
		cor1 = 0xFFff1500;
		Sleep(SleepElmo1);
		cor1 = 0xFFff1900;
		Sleep(SleepElmo1);
		cor1 = 0xFFff1e00;
		Sleep(SleepElmo1);
		cor1 = 0xFFff2200;
		Sleep(SleepElmo1);
		cor1 = 0xFFff2600;
		Sleep(SleepElmo1);
		cor1 = 0xFFff2a00;
		Sleep(SleepElmo1);
		cor1 = 0xFFff2f00;
		Sleep(SleepElmo1);
		cor1 = 0xFFff3300;
		Sleep(SleepElmo1);
		cor1 = 0xFFff3700;
		Sleep(SleepElmo1);
		cor1 = 0xFFff3c00;
		Sleep(SleepElmo1);
		cor1 = 0xFFff4000;
		Sleep(SleepElmo1);
		cor1 = 0xFFff4400;
		Sleep(SleepElmo1);
		cor1 = 0xFFff4800;
		Sleep(SleepElmo1);
		cor1 = 0xFFff4d00;
		Sleep(SleepElmo1);
		cor1 = 0xFFff5100;
		Sleep(SleepElmo1);
		cor1 = 0xFFff5500;
		Sleep(SleepElmo1);
		cor1 = 0xFFff5900;
		Sleep(SleepElmo1);
		cor1 = 0xFFff5e00;
		Sleep(SleepElmo1);
		cor1 = 0xFFff6200;
		Sleep(SleepElmo1);
		cor1 = 0xFFff6600;
		Sleep(SleepElmo1);
		cor1 = 0xFFff6a00;
		Sleep(SleepElmo1);
		cor1 = 0xFFff6f00;
		Sleep(SleepElmo1);
		cor1 = 0xFFff7300;
		Sleep(SleepElmo1);
		cor1 = 0xFFff7700;
		Sleep(SleepElmo1);
		cor1 = 0xFFff7b00;
		Sleep(SleepElmo1);
		cor1 = 0xFFff8000;
		Sleep(SleepElmo1);
		cor1 = 0xFFff8400;
		Sleep(SleepElmo1);
		cor1 = 0xFFff8800;
		Sleep(SleepElmo1);
		cor1 = 0xFFff8c00;
		Sleep(SleepElmo1);
		cor1 = 0xFFff9100;
		Sleep(SleepElmo1);
		cor1 = 0xFFff9500;
		Sleep(SleepElmo1);
		cor1 = 0xFFff9900;
		Sleep(SleepElmo1);
		cor1 = 0xFFff9d00;
		Sleep(SleepElmo1);
		cor1 = 0xFFffa200;
		Sleep(SleepElmo1);
		cor1 = 0xFFffa600;
		Sleep(SleepElmo1);
		cor1 = 0xFFffc400;
		Sleep(SleepElmo1);
		cor1 = 0xFFffc800;
		Sleep(SleepElmo1);
		cor1 = 0xFFffcc00;
		Sleep(SleepElmo1);
		cor1 = 0xFFffd000;
		Sleep(SleepElmo1);
		cor1 = 0xFFffd500;
		Sleep(SleepElmo1);
		cor1 = 0xFFffd900;
		Sleep(SleepElmo1);
		cor1 = 0xFFffdd00;
		Sleep(SleepElmo1);
		cor1 = 0xFFffe603;
		Sleep(SleepElmo1);
		cor1 = 0xFFffe600;
		Sleep(SleepElmo1);
		cor1 = 0xFFffea00;
		Sleep(SleepElmo1);
		cor1 = 0xFFffee00;
		Sleep(SleepElmo1);
		cor1 = 0xFFfff200;
		Sleep(SleepElmo1);
		cor1 = 0xFFfff202;
		Sleep(SleepElmo1);
		cor1 = 0xFFfff700;
		Sleep(SleepElmo1);
		cor1 = 0xFFfffb00;
		Sleep(SleepElmo1);
		cor1 = 0xFFf5e905;
		Sleep(SleepElmo1);
		cor1 = 0xFFfbff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFf6ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFeeff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFe5ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFe1ff00;
		Sleep(SleepElmo1);
		Sleep(SleepElmo1);
		cor1 = 0xFFccff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFc8ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFc3ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFc3ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFbfff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFbbff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFb7ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFb3ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFaeff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFaaff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFa6ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFFa2ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF9dff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF99ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF95ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF91ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF8cff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF88ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF84ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF84ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF80ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF7bff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF77ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF73ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF6fff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF6aff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF66ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF62ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF62ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF5eff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF59ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF55ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF51ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF4dff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF48ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF44ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF40ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF3cff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF37ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF33ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF62ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF2fff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF2bff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF26ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF22ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF1eff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF1aff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF15ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF11ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF0dff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF09ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF04ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff04;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff08;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff0d;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff11;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff15;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff1a;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff1e;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff22;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff26;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff2a;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff2f;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff33;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff37;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff3c;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff40;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff44;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff48;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff4c;
		Sleep(SleepElmo1);
		cor1 = 0xFF62ff00;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff51;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff55;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff59;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff5e;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff62;
		Sleep(SleepElmo1);
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff7b;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff80;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff84;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff88;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff8c;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff91;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff95;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff99;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ff9d;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffa2;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffa6;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffaa;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffae;
		cor1 = 0xFF00ffbf;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffc3;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffc8;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffcc;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffd0;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffd5;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffd9;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffdd;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffe1;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffe5;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffea;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffee;
		Sleep(SleepElmo1);
		cor1 = 0xFF00fff2;
		Sleep(SleepElmo1);
		cor1 = 0xFF00fff7;
		Sleep(SleepElmo1);
		cor1 = 0xFF00fffb;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ffff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00fbff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00f7ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00f2ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00eeff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00eaff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00e5ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00e1ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ddff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00d9ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00d9ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00d5ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00d0ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00ccff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00c8ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00c3ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00bfff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00aaff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00a6ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF00a2ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF009dff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0099ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0095ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0091ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF006eff;
		Sleep(SleepElmo1);
		cor1 = 0xFF006aff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0066ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0062ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF005eff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0059ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0055ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0051ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF004cff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0048ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0044ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0040ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF003cff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0037ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0033ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF002fff;
		Sleep(SleepElmo1);
		cor1 = 0xFF002aff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0022ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF001eff;
		Sleep(SleepElmo1);
		cor1 = 0xFF001aff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0015ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0011ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0800ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF0d00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF1100ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF1500ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF1900ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF1e00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF2200ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF2600ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF2b00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF2f00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF3300ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF3700ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF3c00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF4000ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF4400ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF4800ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF4c00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF5100ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF5500ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF5900ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF5d00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF6200ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF6600ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF6a00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF6f00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF7300ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF7700ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF7b00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF8000ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF8400ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF8800ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF8c00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF9000ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF9500ff;
		Sleep(SleepElmo1);
		cor1 = 0xFF9900ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFaa00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFae00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFb300ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFb700ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFbb00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFbf00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFc300ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFc800ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFcc00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFd000ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFd400ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFd900ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFdd00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFe100ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFe600ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFea00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFee00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFf200ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFf700ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFfb00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00ff;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00fb;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00f7;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00f2;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00ee;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00ea;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00e6;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00e1;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00dd;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00d9;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00d4;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00d0;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00cc;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00c8;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00c3;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00bf;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00bb;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00b7;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00b3;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00ae;
		Sleep(SleepElmo1);
		cor1 = 0xFFff00aa;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0099;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0095;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0090;
		Sleep(SleepElmo1);
		cor1 = 0xFFff008c;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0088;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0084;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0080;
		Sleep(SleepElmo1);
		cor1 = 0xFFff007b;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0077;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0073;
		Sleep(SleepElmo1);
		cor1 = 0xFFff006f;
		Sleep(SleepElmo1);
		cor1 = 0xFFff006a;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0066;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0062;
		Sleep(SleepElmo1);
		cor1 = 0xFFff005d;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0059;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0055;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0051;
		Sleep(SleepElmo1);
		cor1 = 0xFFff004c;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0048;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0044;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0040;
		Sleep(SleepElmo1);
		cor1 = 0xFFff003c;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0037;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0033;
		Sleep(SleepElmo1);
		cor1 = 0xFFff002f;
		Sleep(SleepElmo1);
		cor1 = 0xFFff002b;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0026;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0022;
		Sleep(SleepElmo1);
		cor1 = 0xFFff001e;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0019;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0015;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0011;
		Sleep(SleepElmo1);
		cor1 = 0xFFff000d;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0008;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0004;
		Sleep(SleepElmo1);
		cor1 = 0xFFff0000;
	}

}

DWORD dwShowColor = 0x00453539;
DWORD Retorno = 0x004534C2;
DWORD Retorno2 = 0x004534CB;
int Country = 0x22AA816;
DWORD cColorReturn = 0x00453526;
DWORD Return_Color = 0x00453539;
_declspec(naked) void dwColor()
{
	_asm {



		pushad
		mov eax, 0x0
		mov cl, [eax + 0x22AA816] // = facÃƒÂ§ÃƒÂ£o
		cmp cl, [esi + 0x00002B7] // compara se a sua faÃƒÂ§ÃƒÂ£o ÃƒÂ© a mesma da dor player
		popad
		jne originalcode

		cmp byte ptr ds : [esi + 0x00001A8 + 0x10] , 121
		jne originalcode
		cmp byte ptr ds : [esi + 0x1B9 + 0x10] , 2
		je rojo
		cmp byte ptr ds : [esi + 0x1B9 + 0x10] , 3
		je azul
		cmp byte ptr ds : [esi + 0x1B9 + 0x10] , 4
		je laranja
		cmp byte ptr ds : [esi + 0x1B9 + 0x10] , 5
		je rosa
		cmp byte ptr ds : [esi + 0x1B9 + 0x10] , 6
		je verde
		cmp byte ptr ds : [esi + 0x1B9 + 0x10] , 8
		je amarillo
		cmp byte ptr ds : [esi + 0x1B9 + 0x10] , 9
		je negro
		cmp byte ptr ds : [esi + 0x1B9 + 0x10] , 10
		je multi_color





	originalcode:
		cmp byte ptr ds : [esi + 0x00002D4] , bl
			je Retorno3
			mov ebp, cor1
			jmp Return_Color

			Retorno3 :
		jmp Retorno2



		amarillo:
		mov ebp, 0xFFffdd000 // yellow collor
			jmp dwShowColor // mostrar a cor


			laranja :
		mov ebp, 0xFFFFA500
			jmp dwShowColor

			multi_color :
		mov ebp, cor1
			jmp dwShowColor


			negro :
		mov ebp, 0xF0000000
			jmp dwShowColor


			verde :
		mov ebp, 0xFF00FF00
			jmp dwShowColor

			azul :
		mov ebp, 0xFF00BFFF
			jmp dwShowColor

			rosa :
		mov ebp, 0xFFFF1493
			jmp dwShowColor


			violeta :
		mov ebp, 0xFFa200ff
			jmp dwShowColor

			rojo :
		mov ebp, 0xFF4B0082
			jmp dwShowColor
	}


}
DWORD Remove_Traje_Effect = 0x00416830;
DWORD dwEffrtn = 0x0058F8A5;
_declspec(naked) void dwEffects()

{


	_asm
	{

		push eax
		mov eax, 0x00416956
		cmp[esp + 04], eax
		pop eax

		jne LabelOriginal

		cmp eax, 0xDC
		jbe LabelOriginal

		cmp byte ptr ds : [edi + 0x0F + 0x1A8] , 0

		je Remove_Effect_Costume

		cmp byte ptr ds : [Traje_Effect] , 0

		je Remove_Effect_Costume


		jmp originalcode



	LabelOriginal:
		cmp byte ptr ds : [cBoostPointer] , 1
			je remova


			cmp byte ptr ds : [Effect] , 0x0
			jne originalcode
			jmp remova


			originalcode :
		push ecx
			push esi
			mov esi, ecx
			push edi
			jmp dwEffrtn


			remova :
		mov eax, 0x0
			ret


			Remove_Effect_Costume :
		cmp eax, 0xDC
			jbe originalcode
			mov eax, 0
			ret




	}




}

LPCSTR Efeito1 = "effect1.eft";
LPCSTR Efeito2 = "effect2.eft";
LPCSTR Efeito3 = "effect3.eft";
LPCSTR Efeito4 = "effect4.eft";
LPCSTR Efeito5 = "effect5.eft";
LPCSTR Efeito6 = "effect6.eft";
LPCSTR Efeito7 = "effect7.eft";
LPCSTR Efeito8 = "effect8.eft";
LPCSTR Efeito9 = "effect9.eft";
LPCSTR Efeito10 = "efeito10.eft";
LPCSTR Efeito11 = "efeito11.eft";
DWORD Remove_Effect = 0x00416830;//00416970;
DWORD Send_Load_Effect = 0x0058CC40;//0058C460;
DWORD Alloc_Return = 0x0042BBB4;//0042BDB4;
DWORD Effect_Address = 0x0042BA77;//0042BC77;

_declspec(naked) void Alloc_Effects() {

	_asm {
		// 022CBA88 = efeito 2
// 022CBBB4 = efeito 3
// 022CBCE0 = efeito 4
// 022CBE0C = efeito 5
// 022CBF38 = efeito 6
// 022CC064 = efeito 7
// 022CC190 = efeito 8
// 022CC2BC = efeito 9
// 022CC3E8 = efeito 10
// 022CC514 = efeito 11


		push Efeito1
		push 0x00748864 // data/effect 
		mov ecx, 0x022CBA78 // efeito1 
		Call Send_Load_Effect
		test eax, eax
		je Effect_Continue
		//
		push Efeito2
		push 0x00748864 // data/effect 
		mov ecx, 0x022CBBA4 // efeito1  // - / 022BB8B8 = DC
		Call Send_Load_Effect
		test eax, eax
		je Effect_Continue
		//
		push Efeito3
		push 0x00748864 // data/effect   
		mov ecx, 0x22CBCD0 // efeito1  - / 022BB8B8 = DD
		Call Send_Load_Effect
		test eax, eax
		je Effect_Continue

		push Efeito4
		push 0x00748864 // data/effect 
		mov ecx, 0x22CBDFC // efeito1 - / 022BB8B8 
		Call Send_Load_Effect
		test eax, eax
		je Effect_Continue

		push Efeito5
		push 0x00748864 // data/effect 
		mov ecx, 0x22CBF28 // efeito1  - / 022BB8B8 =
		Call Send_Load_Effect
		test eax, eax
		je Effect_Continue

		push Efeito6
		push 0x00748864 // data/effect 
		mov ecx, 0x22CC054 // efeito1  - / 022BB8B8 =
		Call Send_Load_Effect
		test eax, eax
		je Effect_Continue

		push Efeito7
		push 0x00748864 // data/effect 
		mov ecx, 0x22CC180 // efeito1 - / 022BB8B8 =
		Call Send_Load_Effect
		test eax, eax
		je Effect_Continue

		push Efeito8
		push 0x00748864 // data/effect 
		mov ecx, 0x22CC2AC // efeito1 - / 022BB8B8 =
		Call Send_Load_Effect
		test eax, eax
		je Effect_Continue

		push Efeito9
		push 0x00748864 // data/effect 
		mov ecx, 0x22CC3D8 // efeito1 - / 022BB8B8 =
		Call Send_Load_Effect
		test eax, eax
		je Effect_Continue



		push 0x00749E74
		push 0x00748864
		jmp Alloc_Return

		Effect_Continue :
		jmp Effect_Address



	}

}

DWORD Effect_Equip_Return = 0x0059FBA4;//0059F4A4;
DWORD Render_Effect = 0x0041A100;//0041A2C0;
_declspec(naked) void Effect_Costume() {
	_asm {
		//** CHECK TYPE ID OF COSTUMES **//

		cmp byte ptr ds : [esi + ebx + 0x1A8] , 150
		jne originalcode



		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 121
		je Call_Effect
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 130
		je Call_Effect
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 98
		je Call_Effect
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 125
		je Call_Effect3
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 200
		je Call_Effect3
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 71
		je Call_Effect3
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 131
		je Call_Effect2



		pushad
		mov ecx, esi
		call Remove_Effect
		popad

		originalcode :
		cmp dword ptr ds : [0x90E2F4] , edx
			jmp Effect_Equip_Return

			Call_Effect :
		pushad  // função para remover o efeito
			mov ecx, esi // esi = player
			call Remove_Effect
			popad


			pushad // função para carregar o efeito e assim dar um Reload
			fldz
			push 0x00
			push 0x00
			push 0x00
			push 0x01
			push 0x01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 0x02
			push 0xDC
			call Render_Effect // Render Effect
			popad

			jmp originalcode


			Call_Effect2 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 0x02
			push 0xDD
			call Render_Effect // Render Effect
			popad

			jmp originalcode


			Call_Effect3 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xDE
			call Render_Effect // Render Effect
			popad

			jmp originalcode

			Call_Effect4 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xDF
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect5 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE0
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect6 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE1
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect7 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE2
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect8 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE3
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect9 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE4
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect10 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE4
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect11 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE5
			call Render_Effect // Render Effect
			popad


			jmp originalcode
	}
}

DWORD Respawn_Return = 0x005EB8C5;//005EB875;
_declspec(naked) void Show_Effect_When_Respawn() {
	_asm {
		push eax
		mov eax, 0x00595C5B //0059546B
		cmp[esp + 0x04], eax
		pop eax

		je Check_Costumes_ID

		originalcode :
		mov eax, 0x00002008
			jmp Respawn_Return


			Check_Costumes_ID :
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 121
			je Call_Effect
			cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 130
			je Call_Effect
			cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 98
			je Call_Effect
			cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 125
			je Call_Effect3
			cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 200
			je Call_Effect3
			cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 71
			je Call_Effect3
			cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 131
			je Call_Effect2


			jmp originalcode

			Call_Effect :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 0x00
			push 0x00
			push 0x00
			push 0x01
			push 0x01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 0x02
			push 0xDC
			call Render_Effect // Render Effect
			popad

			jmp originalcode


			Call_Effect2 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 0x02
			push 0xDD
			call Render_Effect // Render Effect
			popad

			jmp originalcode


			Call_Effect3 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xDE
			call Render_Effect // Render Effect
			popad

			jmp originalcode

			Call_Effect4 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xDF
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect5 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE0
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect6 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE1
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect7 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE2
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect8 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE3
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect9 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE4
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect10 :
		pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE4
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect11 :
		pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE5
			call Render_Effect // Render Effect
			popad

			jmp originalcode


	}
}
DWORD Respawn_Return_2 = 0x00595C6A;//0059547A;
_declspec(naked) void Show_Effect_When_Respawn_2() {
	_asm {
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 121
		je Call_Effect
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 130
		je Call_Effect
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 98
		je Call_Effect
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 125
		je Call_Effect3
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 200
		je Call_Effect3
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 71
		je Call_Effect3
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 131
		je Call_Effect2


		originalcode :
		mov ecx, esi
			mov[esi + 0x000002C0], bl
			jmp Respawn_Return_2
			Call_Effect :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 0x00
			push 0x00
			push 0x00
			push 0x01
			push 0x01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 0x02
			push 0xDC
			call Render_Effect // Render Effect
			popad

			jmp originalcode


			Call_Effect2 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 0x02
			push 0xDD
			call Render_Effect // Render Effect
			popad

			jmp originalcode


			Call_Effect3 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xDE
			call Render_Effect // Render Effect
			popad

			jmp originalcode

			Call_Effect4 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xDF
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect5 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE0
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect6 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE1
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect7 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE2
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect8 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE3
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect9 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE4
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect10 :
		pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE4
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect11 :
		pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE5
			call Render_Effect // Render Effect
			popad

			jmp originalcode
	}
}

DWORD Effect_Map_Return = 0x00416225;//004162F5;
_declspec(naked) void Effect_When_Change_Map() {
	_asm {
		push eax
		mov eax, 0x00418DE7//00418FA7
		cmp[esp + 0x04], eax
		pop eax
		jne originalcode

		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 121
		je Call_Effect
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 130
		je Call_Effect
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 98
		je Call_Effect
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 125
		je Call_Effect3
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 200
		je Call_Effect3
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 71
		je Call_Effect3
		cmp byte ptr ds : [esi + 0x0F + 0x1B9] , 131
		je Call_Effect2




	originalcode:
		mov eax, [esp + 0x04]
			push esi
			jmp Effect_Map_Return


			Call_Effect :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 0x00
			push 0x00
			push 0x00
			push 0x01
			push 0x01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 0x02
			push 0xDC
			call Render_Effect // Render Effect
			popad

			jmp originalcode


			Call_Effect2 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 0x02
			push 0xDD
			call Render_Effect // Render Effect
			popad

			jmp originalcode


			Call_Effect3 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xDE
			call Render_Effect // Render Effect
			popad

			jmp originalcode

			Call_Effect4 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xDF
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect5 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE0
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect6 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE1
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect7 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE2
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect8 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE3
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect9 :
		pushad
			mov ecx, esi
			call Remove_Effect
			popad


			pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE4
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect10 :
		pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE4
			call Render_Effect // Render Effect
			popad
			jmp originalcode

			Call_Effect11 :
		pushad
			fldz
			push 00
			push 00
			push 00
			push 01
			push 01
			fstp dword ptr ds : [esp]
			mov ecx, esi
			//push 03
			push 02
			push 0xE5
			call Render_Effect // Render Effect
			popad

			jmp originalcode

	}
}



DWORD SendPos = 0x00631AB0;
DWORD SendDisplay = 0x0057BA70;
DWORD cDisplayReturn = 0x00453984;
_declspec(naked) void cDisplayTitle()
{
	_asm {

		cmp byte ptr ds : [Titulo] , 00
		je originalcode


		cmp byte ptr ds : [esi + 0x1A8 + 0x7] , 24
		jne Check_Capes_39
		// REY DE MYSTRA 
		cmp byte ptr ds : [esi + 0x1B9 + 0x7] , 127
		je bTitulo220
		cmp byte ptr ds : [esi + 0x1B9 + 0x7] , 27
		je bTitulo221





		jmp originalcode

		Check_Capes_39 :
		cmp byte ptr ds : [esi + 0x1A8 + 0x7] , 39
			jne originalcode

			cmp byte ptr ds : [esi + 0x1B9 + 0x7] , 90
			je bTitulo222
			cmp byte ptr ds : [esi + 0x1B9 + 0x7] , 120
			je bTitulo223
			cmp byte ptr ds : [esi + 0x1B9 + 0x7] , 94
			je bTitulo224
			cmp byte ptr ds : [esi + 0x1B9 + 0x7] , 97
			je bTitulo225
			cmp byte ptr ds : [esi + 0x1B9 + 0x7] , 96
			je bTitulo226
			cmp byte ptr ds : [esi + 0x1B9 + 0x7] , 95
			je bTitulo227
			cmp byte ptr ds : [esi + 0x1B9 + 0x7] , 112
			je bTitulo228
			cmp byte ptr ds : [esi + 0x1B9 + 0x7] , 89
			je bTitulo229

			jmp originalcode



		bTitulo220:
		fld dword ptr ss : [esp + 0x1C]
			push ecx
			fstp dword ptr ss : [esp]
			fld dword ptr ss : [esp + 0x1C]
			fld qword ptr ss : [0x00748498]
			fsub st(1), st(0)
			fxch st(1)
			call SendPos
			fild dword ptr ss : [esi + 0x00000318]
			add eax, -75
			push eax
			fadd dword ptr ss : [esp + 0x1C]
			fiadd[esp + 0x18]
			fadd qword ptr ss : [0x7480C8]
			FADDP ST(1), ST
			fsub qword ptr ss : [0x748428]
			fadd qword ptr ss : [0x748420]
			call SendPos
			sub eax, dword ptr ds : [esi + 0x00000318]
			sub eax, 136
			push eax
			mov edi, 0x007C4A68 + 0x00141000
			mov ecx, edi
			call SendDisplay
			jmp cDisplayReturn



		bTitulo221:
		fld dword ptr ss : [esp + 0x1C]
			push ecx
			fstp dword ptr ss : [esp]
			fld dword ptr ss : [esp + 0x1C]
			fld qword ptr ss : [0x00748498]
			fsub st(1), st(0)
			fxch st(1)
			call SendPos
			fild dword ptr ss : [esi + 0x00000318]
			add eax, -75
			push eax
			fadd dword ptr ss : [esp + 0x1C]
			fiadd[esp + 0x18]
			fadd qword ptr ss : [0x7480C8]
			FADDP ST(1), ST
			fsub qword ptr ss : [0x748428]
			fadd qword ptr ss : [0x748420]
			call SendPos
			sub eax, dword ptr ds : [esi + 0x00000318]
			sub eax, 136
			push eax
			mov edi, 0x007C4A68 + 0x00141020
			mov ecx, edi
			call SendDisplay
			jmp cDisplayReturn


			bTitulo222 :
		fld dword ptr ss : [esp + 0x1C]
			push ecx
			fstp dword ptr ss : [esp]
			fld dword ptr ss : [esp + 0x1C]
			fld qword ptr ss : [0x00748498]
			fsub st(1), st(0)
			fxch st(1)
			call SendPos
			fild dword ptr ss : [esi + 0x00000318]
			add eax, -75
			push eax
			fadd dword ptr ss : [esp + 0x1C]
			fiadd[esp + 0x18]
			fadd qword ptr ss : [0x7480C8]
			FADDP ST(1), ST
			fsub qword ptr ss : [0x748428]
			fadd qword ptr ss : [0x748420]
			call SendPos
			sub eax, dword ptr ds : [esi + 0x00000318]
			sub eax, 136
			push eax
			mov edi, 0x007C4A68 + 0x00141040
			mov ecx, edi
			call SendDisplay
			jmp cDisplayReturn



		bTitulo223:
		fld dword ptr ss : [esp + 0x1C]
			push ecx
			fstp dword ptr ss : [esp]
			fld dword ptr ss : [esp + 0x1C]
			fld qword ptr ss : [0x00748498]
			fsub st(1), st(0)
			fxch st(1)
			call SendPos
			fild dword ptr ss : [esi + 0x00000318]
			add eax, -75
			push eax
			fadd dword ptr ss : [esp + 0x1C]
			fiadd[esp + 0x18]
			fadd qword ptr ss : [0x7480C8]
			FADDP ST(1), ST
			fsub qword ptr ss : [0x748428]
			fadd qword ptr ss : [0x748420]
			call SendPos
			sub eax, dword ptr ds : [esi + 0x00000318]
			sub eax, 136
			push eax
			mov edi, 0x007C4A68 + 0x00141060
			mov ecx, edi
			call SendDisplay
			jmp cDisplayReturn



		bTitulo224:
		fld dword ptr ss : [esp + 0x1C]
			push ecx
			fstp dword ptr ss : [esp]
			fld dword ptr ss : [esp + 0x1C]
			fld qword ptr ss : [0x00748498]
			fsub st(1), st(0)
			fxch st(1)
			call SendPos
			fild dword ptr ss : [esi + 0x00000318]
			add eax, -75
			push eax
			fadd dword ptr ss : [esp + 0x1C]
			fiadd[esp + 0x18]
			fadd qword ptr ss : [0x7480C8]
			FADDP ST(1), ST
			fsub qword ptr ss : [0x748428]
			fadd qword ptr ss : [0x748420]
			call SendPos
			sub eax, dword ptr ds : [esi + 0x00000318]
			sub eax, 136
			push eax
			mov edi, 0x007C4A68 + 0x00141080
			mov ecx, edi
			call SendDisplay
			jmp cDisplayReturn



		bTitulo225:
		fld dword ptr ss : [esp + 0x1C]
			push ecx
			fstp dword ptr ss : [esp]
			fld dword ptr ss : [esp + 0x1C]
			fld qword ptr ss : [0x00748498]
			fsub st(1), st(0)
			fxch st(1)
			call SendPos
			fild dword ptr ss : [esi + 0x00000318]
			add eax, -75
			push eax
			fadd dword ptr ss : [esp + 0x1C]
			fiadd[esp + 0x18]
			fadd qword ptr ss : [0x7480C8]
			FADDP ST(1), ST
			fsub qword ptr ss : [0x748428]
			fadd qword ptr ss : [0x748420]
			call SendPos
			sub eax, dword ptr ds : [esi + 0x00000318]
			sub eax, 136
			push eax
			mov edi, 0x007C4A68 + 0x00141100
			mov ecx, edi
			call SendDisplay
			jmp cDisplayReturn


			bTitulo226 :
		fld dword ptr ss : [esp + 0x1C]
			push ecx
			fstp dword ptr ss : [esp]
			fld dword ptr ss : [esp + 0x1C]
			fld qword ptr ss : [0x00748498]
			fsub st(1), st(0)
			fxch st(1)
			call SendPos
			fild dword ptr ss : [esi + 0x00000318]
			add eax, -75
			push eax
			fadd dword ptr ss : [esp + 0x1C]
			fiadd[esp + 0x18]
			fadd qword ptr ss : [0x7480C8]
			FADDP ST(1), ST
			fsub qword ptr ss : [0x748428]
			fadd qword ptr ss : [0x748420]
			call SendPos
			sub eax, dword ptr ds : [esi + 0x00000318]
			sub eax, 136
			push eax
			mov edi, 0x007C4A68 + 0x00141120
			mov ecx, edi
			call SendDisplay
			jmp cDisplayReturn


			bTitulo227 :
		fld dword ptr ss : [esp + 0x1C]
			push ecx
			fstp dword ptr ss : [esp]
			fld dword ptr ss : [esp + 0x1C]
			fld qword ptr ss : [0x00748498]
			fsub st(1), st(0)
			fxch st(1)
			call SendPos
			fild dword ptr ss : [esi + 0x00000318]
			add eax, -75
			push eax
			fadd dword ptr ss : [esp + 0x1C]
			fiadd[esp + 0x18]
			fadd qword ptr ss : [0x7480C8]
			FADDP ST(1), ST
			fsub qword ptr ss : [0x748428]
			fadd qword ptr ss : [0x748420]
			call SendPos
			sub eax, dword ptr ds : [esi + 0x00000318]
			sub eax, 136
			push eax
			mov edi, 0x007C4A68 + 0x00141140
			mov ecx, edi
			call SendDisplay
			jmp cDisplayReturn


			bTitulo228 :
		fld dword ptr ss : [esp + 0x1C]
			push ecx
			fstp dword ptr ss : [esp]
			fld dword ptr ss : [esp + 0x1C]
			fld qword ptr ss : [0x00748498]
			fsub st(1), st(0)
			fxch st(1)
			call SendPos
			fild dword ptr ss : [esi + 0x00000318]
			add eax, -75
			push eax
			fadd dword ptr ss : [esp + 0x1C]
			fiadd[esp + 0x18]
			fadd qword ptr ss : [0x7480C8]
			FADDP ST(1), ST
			fsub qword ptr ss : [0x748428]
			fadd qword ptr ss : [0x748420]
			call SendPos
			sub eax, dword ptr ds : [esi + 0x00000318]
			sub eax, 136
			push eax
			mov edi, 0x007C4A68 + 0x00141180
			mov ecx, edi
			call SendDisplay
			jmp cDisplayReturn


			bTitulo229 :
		fld dword ptr ss : [esp + 0x1C]
			push ecx
			fstp dword ptr ss : [esp]
			fld dword ptr ss : [esp + 0x1C]
			fld qword ptr ss : [0x00748498]
			fsub st(1), st(0)
			fxch st(1)
			call SendPos
			fild dword ptr ss : [esi + 0x00000318]
			add eax, -75
			push eax
			fadd dword ptr ss : [esp + 0x1C]
			fiadd[esp + 0x18]
			fadd qword ptr ss : [0x7480C8]
			FADDP ST(1), ST
			fsub qword ptr ss : [0x748428]
			fadd qword ptr ss : [0x748420]
			call SendPos
			sub eax, dword ptr ds : [esi + 0x00000318]
			sub eax, 136
			push eax
			mov edi, 0x007C4A68 + 0x00141200
			mov ecx, edi
			call SendDisplay
			jmp cDisplayReturn

			originalcode :
		cmp dword ptr ds : [esi + 0x00000334] , 01
			jmp cDisplayReturn
	}
}


unsigned char cGetServerName[] = { 0x4E, 0x6F, 0x78, 0x69 };
unsigned char cGetLastNameServer[] = { 0x75, 0x73 };
const char* dwString1 = "Noxius";
const char* dwString2 = "us";
DWORD cPacketProtectReturn = 0x005EA9F5;
_declspec(naked) void cPacketProtect()
{
	_asm {


		cmp byte ptr ds : [0x00486DB5] , 0x77
		jne cSendCrash

		cmp byte ptr ds : [0x0044A61F] , 0x70
		je cSendCrash

		cmp byte ptr ds : [0x005B4A02] , 0x00
		je cSendCrash


		cmp byte ptr ds : [0x004EA005] , 0x02
		je cSendCrash


		cmp byte ptr ds : [0x0044C1CE] , 0x81
		je cSendCrash


		cmp byte ptr ds : [0x004B785B] , 0x80
		je cSendCrash


		cmp byte ptr ds : [0x005B546F] , 0x90
		je cSendCrash


		cmp byte ptr ds : [0x005B3F81] , 0x90
		je cSendCrash


		cmp byte ptr ds : [0x00414F2B] , 0x90
		je cSendCrash


		mov eax, 0x00001004
		jmp cPacketProtectReturn



	cSendCrash:
		int 3

	}
}

LPCSTR cStringEncrypt = "@@*#$!xpo3@%.cfg";
DWORD cHideGsConfigReturn = 0x0060AC7E;
_declspec(naked) void cHideGsConfig()
{
	_asm {

		push cStringEncrypt
		jmp cHideGsConfigReturn
	}
}

float Increase20 = 20.00;
DWORD cZoomLimitReturn = 0x00442933;
_declspec(naked) void cZoomLimit()
{
	_asm {

		mov dword ptr ds : [0x007484DC] , 0x41A00000
		fld dword ptr ds : [0x007484DC]
		jmp cZoomLimitReturn


	}
}

DWORD sahRet = 0x0040E00D;
DWORD sahCall = 0x006339E6;
_declspec(naked) void SahEncrypt()
{
	_asm {


		call sahCall
		pushad
		mov esi, ss: [esp + 0x24]
		mov ebx, dword ptr ds : [esi]
		//mov edx,0x0072BBA7
		xor ebx, 0x74
		xor ebx, 0x61
		xor ebx, 0x68
		xor ebx, 0x10
		mov dword ptr ds : [esi] , ebx
		popad
		jmp sahRet

	}
}

DWORD cPacketReturn = 0x005EC7A4;
_declspec(naked) void cProtectPacket() {
	_asm {
		mov eax, 0xA369
		jmp cPacketReturn
	}
}

unsigned short weapon_step[] = {
	0x0, 07, 14, 21, 31, 41, 51,
	64, 77, 90, 106, 122, 138,
	157, 176, 195, 217, 239, 261,
	286, 311, 0xD16, 0x02E9, 0x0320, 0x03B6,
	0x03E8, 0x044C, 0x04B0, 0x0514, 0x0578
};

DWORD enchan_retn = 0x4B8690;
void __declspec(naked) enchantt_dmg() {
	__asm {
		push ebx
		lea ebx, [weapon_step]
		movzx eax, word ptr ds : [ebx + eax * 2]
		pop ebx
		jmp enchan_retn
	}
}

#define rankpoint_table_rank1 1
#define rankpoint_table_rank2 50
#define rankpoint_table_rank3 300
#define rankpoint_table_rank4 1000
#define rankpoint_table_rank5 5000
#define rankpoint_table_rank6 10000
#define rankpoint_table_rank7 20000
#define rankpoint_table_rank8 30000
#define rankpoint_table_rank9 40000
#define rankpoint_table_rank10 50000
#define rankpoint_table_rank11 70000
#define rankpoint_table_rank12 90000
#define rankpoint_table_rank13 110000
#define rankpoint_table_rank14 130000
#define rankpoint_table_rank15 150000
#define rankpoint_table_rank16 200000
#define rankpoint_table_rank17 250000
#define rankpoint_table_rank18 300000
#define rankpoint_table_rank19 350000
#define rankpoint_table_rank20 400000
#define rankpoint_table_rank21 450000
#define rankpoint_table_rank22 500000
#define rankpoint_table_rank23 550000
#define rankpoint_table_rank24 600000
#define rankpoint_table_rank25 650000
#define rankpoint_table_rank26 700000
#define rankpoint_table_rank27 750000
#define rankpoint_table_rank28 800000
#define rankpoint_table_rank29 850000
#define rankpoint_table_rank30 900000
#define rankpoint_table_rank31 1000000

#define rankpoint_table_rank32 1500000
#define rankpoint_table_rank33 2000000
#define rankpoint_table_rank34 2500000
#define rankpoint_table_rank35 3000000
#define rankpoint_table_rank36 3500000
#define rankpoint_table_rank37 4000000
#define rankpoint_table_rank38 4500000
#define rankpoint_table_rank39 5000000
#define rankpoint_table_rank40 5500000
#define rankpoint_table_rank41 6000000
#define rankpoint_table_rank42 6500000
#define rankpoint_table_rank43 7000000
#define rankpoint_table_rank44 7500000
#define rankpoint_table_rank45 8000000
#define rankpoint_table_rank46 10000000




unsigned rankpoint_table[] =
{
	rankpoint_table_rank1, // Rank 1 (I)
	rankpoint_table_rank2, // Rank 2 (II)
	rankpoint_table_rank3, // Rank 3 (III)
	rankpoint_table_rank4, // Rank 4 (> )
	rankpoint_table_rank5, // Rank 5 (>> )
	rankpoint_table_rank6, // Rank 6 (>> > )
	rankpoint_table_rank7, // Rank 7 (<>)
	rankpoint_table_rank8, // Rank 8 (<><>)
	rankpoint_table_rank9, // Rank 9 (<><><>)
	rankpoint_table_rank10, // Rank 10 (1 Flower)
	rankpoint_table_rank11, // Rank 11 (2 Flowers)
	rankpoint_table_rank12, // Rank 12 (3 Flowers)
	rankpoint_table_rank13, // Rank 13 (*)
	rankpoint_table_rank14, // Rank 14 (**)
	rankpoint_table_rank15, // Rank 15 (***)
	rankpoint_table_rank16, // Rank 16 (Yellow I)
	rankpoint_table_rank17, // Rank 17 (Yellow II)
	rankpoint_table_rank18, // Rank 18 (Yellow III)
	rankpoint_table_rank19, // Rank 19 (Yellow > )
	rankpoint_table_rank20, // Rank 20 (Yellow >> )
	rankpoint_table_rank21, // Rank 21 (Yellow >> > )
	rankpoint_table_rank22, // Rank 22 (Yellow <>)
	rankpoint_table_rank23, // Rank 23 (Yellow <><>)
	rankpoint_table_rank24, // Rank 24 (Yellow <><><>)
	rankpoint_table_rank25, // Rank 25 (Yellow 1 Flower)
	rankpoint_table_rank26, // Rank 26 (Yellow 2 Flowers)
	rankpoint_table_rank27, // Rank 27 (Yellow 3 Flowers)
	rankpoint_table_rank28, // Rank 28 (Yellow*)
	rankpoint_table_rank29, // Rank 29 (Yellow**)
	rankpoint_table_rank30, // Rank 30 (Yellow***)
	rankpoint_table_rank31, // Rank 31 (Pink Star)
	rankpoint_table_rank32, // 
	rankpoint_table_rank33, //
	rankpoint_table_rank34, // 
	rankpoint_table_rank35, // 
	rankpoint_table_rank36, // 
	rankpoint_table_rank37, // 
	rankpoint_table_rank38, // 
	rankpoint_table_rank39, // 
	rankpoint_table_rank40, // 
	rankpoint_table_rank41, // 
	rankpoint_table_rank42, // 
	rankpoint_table_rank43, // 
	rankpoint_table_rank44, // 
	rankpoint_table_rank45, // 
	rankpoint_table_rank46
	// 
};







#define newranksposdbs 0.32
#define newrankspos2fls 0.64
#define newrankspos2fl2s 0.32

double newranksposdb = newranksposdbs;

DWORD newranksposjmp = 0x0044E914;

__declspec(naked) void newrankspos() {
	_asm {

		fld qword ptr[newranksposdb]
		jmp newranksposjmp
	}
}

DWORD newrankspos2jmp = 0x0044E89D;

float newrankspos2fl = newrankspos2fls;
float newrankspos2fl2 = newrankspos2fl2s;

__declspec(naked) void newrankspos2() {
	_asm {

		cmp eax, 0x1F
		jle newrankspos2jle
		fld dword ptr[newrankspos2fl] //64
		newrankspos2exit:
		jmp newrankspos2jmp

			newrankspos2jle :
		fld dword ptr[newrankspos2fl2]//32
			jmp newrankspos2exit
	}
}

DWORD newrankpointjmp = 0x0044E887;
__declspec(naked) void newrankpoint() {
	_asm {

		//cmp ecx, [eax * 0x4 + rankpoint_table]
		mov ebx, [rankpoint_table + eax * 4]
		cmp ecx, ebx

		jmp newrankpointjmp
	}
}


DWORD cBoostReturn = 0x005812C6;
DWORD cBoostRemoveLayer = 0x0058135E;
_declspec(naked) void cFpsBoost()
{
	_asm {
		cmp byte ptr ds : [cBoostPointer] , 01
		je RemoveLayer

		originalcode :
		push ebx
			mov ebx, 0x7B19B0
			jmp cBoostReturn

			RemoveLayer :
		jmp cBoostRemoveLayer
	}
}

DWORD cSendSmall = 0x0057BD80;
DWORD cStopFuncAddr = 0x004B5822;
DWORD cSmallReturn = 0x004B5815;
DWORD cSmallReturn2 = 0x004B57E7;
_declspec(naked) void cSmallIcon()
{
	_asm {
		cmp byte ptr[cSmall], 1
		jne originalcode

		push eax
		mov eax, 0x004D8A50
		cmp[esp + 0x24], eax
		pop eax
		jne originalcode

		push 0x11
		push 0x11
		push esi
		push ebp
		push ecx
		lea ecx, [edi + 0x0090CE10]
		call cSendSmall
		cmp ebx, 0x64
		je cStopFunc
		push ebx
		push 0x0074E5F4
		push 00
		push 00
		push 0x000000FF
		push 0x000000FF
		add esi, 4
		push esi
		add ebp, 1
		push ebp
		jmp cSmallReturn


		cStopFunc :
		jmp cStopFuncAddr

			originalcode :
		push 0x20
			push 0x20
			push esi
			jmp cSmallReturn2
	}
}

DWORD cStackReturn = 0x004D8AED;
_declspec(naked) void cStack()
{
	_asm {
		cmp byte ptr ds : [cSmall] , 0x1
		jne originalcode

		add edi, 0x15
		cmp eax, 0x11
		jmp cStackReturn

		originalcode :
		add edi, 0x28
			cmp eax, 0x11
			jmp cStackReturn
	}
}

DWORD cWhiteReturn = 0x004D8AD8;
_declspec(naked) void cWhiteSmall() {
	_asm {
		cmp byte ptr ds : [cSmall] , 0x1
		jne originalcode

		push 0x11
		push 0x11
		push edx
		jmp cWhiteReturn

		originalcode :
		push 0x20
			push 0x20
			push edx
			jmp cWhiteReturn
	}
}


DWORD cAjustTimeReturn = 0x004B6B68;
_declspec(naked) void cAjustTime()
{
	_asm {
		cmp byte ptr ds : [cSmall] , 0x1
		jne originalcode
		fmul qword ptr ss : [0x748438]
		jmp cAjustTimeReturn

		originalcode :
		fmul qword ptr ss : [0x007480D0]
			jmp cAjustTimeReturn
	}
}
DWORD cAjustTime2Return = 0x004B6B23;
_declspec(naked) void cAjustTime2()
{
	_asm {
		cmp byte ptr ds : [cSmall] , 0x1
		jne originalcode
		push 0x03
		push 0x11
		add esi, 0x11
		jmp cAjustTime2Return
		originalcode :
		push 0x03
			push 0x20
			add esi, 0x20
			jmp cAjustTime2Return
	}
}
DWORD cAjustMenssageReturn = 0x004D8AAB;
_declspec(naked) void cAjustMenssage()
{
	_asm {
		cmp byte ptr ds : [cSmall] , 0x1
		jne originalcode
		add eax, 0x11
		cmp dword ptr ds : [0x7C3C10] , eax
		jmp cAjustMenssageReturn

		originalcode :
		add eax, 0x20
			cmp dword ptr ds : [0x7C3C10] , eax
			jmp cAjustMenssageReturn
	}
}

void HP_Bar()
{
	Hook((void*)0x0044F5D0, cAllocTitle, 9);
	Hook((void*)0x0040E008, SahEncrypt, 5);
	Hook((void*)0x0042BBAA, Alloc_Effects, 5);


	Sleep(10000);

	if (CheckStringWindow("ul3JFL0B")) {


		if (CheckIp("mc2vf8ilFmERzkkiqDwu")) {

			Hook((void*)0x4B57E2, cSmallIcon, 5);
			Hook((void*)0x4D8AE7, cStack, 6);
			Hook((void*)0x4D8AD3, cWhiteSmall, 5);
			Hook((void*)0x4B6B62, cAjustTime, 6);
			Hook((void*)0x4B6B1C, cAjustTime2, 7);
			Hook((void*)0x4D8AA2, cAjustMenssage, 9);



			Hook((void*)0x005EC79F, cProtectPacket, 5);
			Hook((void*)0x4B867F, enchantt_dmg, 17);
			Hook((void*)0x00453853, HP_Bar_Main, 7);

			Hook((void*)0x0051A8A3, Equip, 5);
			Hook((void*)0x00501303, Bar, 5);
			Hook((void*)0x51A68D, Bag, 8);

			Hook((void*)0x0042B4F5, skillbar_main, 6);//0x42B6D4
			//
			Hook((void*)0x004A3E21, skillbar_add1, 7); //4A4021
			//
			Hook((void*)0x004A3F03, skillbar_add2, 8); //4A4103
			//
			Hook((void*)0x004FFC9C, skillbar_add3, 6); //Slot plus GÃƒÂ¶rÃƒÂ¼ntÃƒÂ¼ = 04FE57C
			//
			Hook((void*)0x005008BB, skillbar_add4, 5); //4FF29B
			//
			Hook((void*)0x00500F70, skillbar_add5, 9); // 4FF950
			// 
			Hook((void*)0x00500FB4, skillbar_add6, 7); // Slot plus + ve - dÃƒÂ¼zeltme = 4FF994
			//
			Hook((void*)0x00501490, skillbar_add7, 7); // 4FFE70
			//
			BYTE skillbar_main_memory2[] = { 0x3C, 0x02 };
			memcpy((void*)0x00500559, skillbar_main_memory2, 2);

			Hook((void*)0x0052987D, dwX10Stat, 9);
			Hook((void*)0x005298A0, x10stats3, 5);
			Hook((void*)0x00529890, x10stats2, 6);
			Hook((void*)0x00529898, x10stats, 8);

			Hook((void*)0x005EA9F0, cPacketProtect, 5);
			Hook((void*)0x0044292D, cZoomLimit, 6);
			//RAID 150 SLOT
			//Raid Text Color 1
			BYTE Raidtextcolor1[] = { 0x68, 0x4D, 0xFF, 0xFF, 0xFF };
			memcpy((void*)0x53DF65, Raidtextcolor1, 5);
			//Raid Text Color 2
			BYTE Raidtextcolor2[] = { 0x68, 0x4D, 0xFF, 0xFF, 0xFF };
			memcpy((void*)0x53E005, Raidtextcolor2, 5);


			// RaidInjAdr1*
			Hook((void*)0x53F223, RaidInj1, 6);
			// RaidInjAdr2*
			Hook((void*)0x53FED7, RaidInj2, 6);
			//RaidInjAdr3*
			BYTE RaidInjAdr3[] = { 0x83, 0xFE, 0x96 };
			memcpy((void*)0x4EDDD1, RaidInjAdr3, 3);
			// RaidInjAdr4*
			Hook((void*)0x5410E2, RaidInj4, 9);
			// RaidInjAdr5
			Hook((void*)0x540006, RaidInj5, 9);
			// RaidInjAdr6
			Hook((void*)0x4A42DA, RaidInj6, 6);
			// RaidInjAdr7
			Hook((void*)0x48D977, RaidInj7, 5);
			// RaidInjAdr8
			Hook((void*)0x48D916, RaidInj8, 5);
			// RaidInjAdr9
			Hook((void*)0x53DE72, RaidInj9, 6);
			// RaidInjAdr10
			Hook((void*)0x53DEC5, RaidInj10, 6);
			// RaidInjAdr11
			Hook((void*)0x445D67, RaidInj11, 9);
			// RaidInjAdr12
			Hook((void*)0x53D76B, RaidInj12, 6);
			//RaidInjAdr13
			BYTE RaidInjAdr13[] = { 0x83, 0xFB, 0x18, 0x77, 0x36 };
			memcpy((void*)0x53D748, RaidInjAdr13, 5);
			// RaidInjAdr14
			Hook((void*)0x53F322, RaidInj14, 9);
			// RaidInjAdr15
			Hook((void*)0x540D73, RaidInj15, 6);

			Hook((void*)0x43AB5F, asa, 7);
			Hook((void*)0x43B1D4, asa2, 7);
			Hook((void*)0x4864C1, comando, 5);
			Hook((void*)0x004112A5, pet1, 6);
			Hook((void*)0x00418146, pet3, 8);
			Hook((void*)0x00411222, pet4, 6);
			Hook((void*)0x00439F1F, pet5, 7);
			Hook((void*)0x0041F59D, asa4, 8);
			Hook((void*)0x0041F4D3, asa3, 7);


			BYTE WriteBytes[] = { 0x90,0x90,0x90 };
			Hook((void*)0x004E5B3E, SetModelID, 6);
			memcpy((void*)0x004E5B44, WriteBytes, 3);
			Hook((void*)0x004148C7, SetPosition, 7);
			Hook((void*)0x00414315, AllowModels, 8);
			Hook((void*)0x005F4405, GetPacket, 7);
			Hook((void*)0x00486B02, Command, 7);
			Hook((void*)0x0041A57B, ChangeMountSpeed, 6);

			Hook((void*)0x427C00, flash, 6);

			BYTE bySlotCap = 19;
			//new slots
			memcpy((LPVOID)0x005190E1, &bySlotCap, 1);
			memcpy((LPVOID)0x0051A1D0, &bySlotCap, 1);
			memcpy((LPVOID)0x0051A9B8, &bySlotCap, 1);
			memcpy((LPVOID)0x00518B5C, &bySlotCap, 1);

			Hook((PVOID)0x005190D9, ItemEquip, 6);
			Hook((PVOID)0x0059FBA6, SetCorrectSlotByType, 8);
			Hook((PVOID)0x00518BD7, ItemRemove, 8);
			Hook((PVOID)0x004E6B30, RemoveStackText, 7);
			Hook((PVOID)0x00519070, RemoveTypeEffect, 8);
			Hook((PVOID)0x005180D0, SetSlotIconSize, 7);
			Hook((PVOID)0x00519BBA, FixBag1BtnA, 6);
			Hook((PVOID)0x0051A29E, FixBag1BtnB, 6);
			Hook((PVOID)0x0051A2B1, FixBag2BtnA, 6);
			Hook((PVOID)0x0051A2C4, FixBag2BtnB, 6);
			Hook((PVOID)0x00519BCD, FixBag2BtnC, 6);
			Hook((PVOID)0x00519BE3, FixBag2BtnD, 6);

			Hook((PVOID)0x0051A7F0, SetSlotIconPosition, 7);

			// corrigir trade
			memcpy((LPVOID)0x0053B571, "\x90\x90", 2);
			memcpy((LPVOID)0x0053B5D7, "\x90\x90\x90\x90\x90\x90", 6);
			memcpy((LPVOID)0x00519D92, "\x90\x90", 2);

			Hook((void*)0x004534BC, dwColor, 6);

			Hook((void*)0x0058F8A0, dwEffects, 5);


			Hook((void*)0x45397D, cDisplayTitle, 7);

			Hook((void*)0x416273, onff, 10);
			Hook((void*)0x59F960, conff, 5);
			Hook((void*)0x47858C, wwwconf, 6);
			Hook((void*)0x59FBAE, wwconf, 6);

			Hook((void*)0x00477EF2, dwCharacterScreen, 5);
			Hook((void*)0x00477F64, dwCharacterScreen2, 5);
			Hook((void*)0x00477FEC, dwCharacterScreen3, 5);
			Hook((void*)0x00478078, dwCharacterScreen4, 5);
			Hook((void*)0x00478104, dwCharacterScreen5, 5);
			Hook((void*)0x4759B3, dwCharacterScreen7, 5);
			Hook((void*)0x475A01, dwCharacterScreen8, 9);
			Hook((void*)0x475996, dwCharacterScreen9, 8);

			memcpy((void*)0x0051959E, InvetoryBytes_01, 15);//Permitir Uso de Loja e Jmp Abaixo

			Hook((void*)0x005195A4, Invetory_03, 5);//NPC ID

			Hook((void*)0x0059FB9E, Effect_Costume, 6);
			Hook((void*)0x005EB8C0, Show_Effect_When_Respawn, 5);
			Hook((void*)0x00595C62, Show_Effect_When_Respawn_2, 8);
			Hook((void*)0x00416220, Effect_When_Change_Map, 5);

			Hook((void*)0x0051BA8B, opensetting, 6);

			Hook((void*)0x0051F59D, render, 5);

			Hook((void*)0x00521C35, click, 6);

			Hook((void*)0x0051BDE0, save, 6);

			Hook((void*)0x0051ED3B, bindbuttonposition, 5);


			// Option Ok button Y
			BYTE optionokbutton[] = { 0x68, 0x03, 0x02, 0x00, 0x00 };
			memcpy((void*)0x0051ED2B, optionokbutton, 5);
			// Option Cancel button Y
			BYTE optioncancelbutton[] = { 0x68, 0x03, 0x02, 0x00, 0x00 };
			memcpy((void*)0x0051ED40, optioncancelbutton, 5);
			// Option reset button Y
			BYTE optionresetbutton[] = { 0x68, 0x03, 0x02, 0x00, 0x00, 0x6A,0x0D };
			memcpy((void*)0x0051ED55, optionresetbutton, 7);

			Hook((void*)0x005812C0, cFpsBoost, 6);

			BYTE gradesize[] = { 0x6A, 0x60 };
			memcpy((void*)0x0044F684, &gradesize, 2);

			Hook((void*)0x0044E90E, newrankspos, 6);
			Hook((void*)0x0044E897, newrankspos2, 6);

			Hook((void*)0x0044E880, newrankpoint, 7);

			BYTE ranklimit[] = { 0xB8, 0x2D, 0x00, 0x00, 0x00 };
			memcpy((void*)0x0044E873, &ranklimit, 5);

		}
		else ExitProcess(0);
	}
	else ExitProcess(0);
}

void ExtendedThread()
{
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(HP_Bar), NULL, 0, 0);
	//CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(H_Scan), NULL, 0, 0);
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(GMColorChanger), NULL, 0, 0);
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(fpsboost_save), NULL, 0, 0);
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Effects_Save), NULL, 0, 0);
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Titulos_Save), NULL, 0, 0);
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Small_Icon_Save), NULL, 0, 0);
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Traje_Save), NULL, 0, 0);
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Alas_Save), NULL, 0, 0);
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Pet_Save), NULL, 0, 0);
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(HP_Dark_Save), NULL, 0, 0);
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(HP_Light_Save), NULL, 0, 0);
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Traje_Effect_Save), NULL, 0, 0);




}
