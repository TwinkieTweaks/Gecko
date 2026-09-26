#include "pch.h"
#include "TMTypes.h"

CMwNodClassInfo::CMwNodClassInfo()
{
	ClassName = (char*)"CMwNod";
	ClassID = 0x01001000;
	Members = nullptr;
	MembersAmount = 0;
}

CMwNodClassInfo CMwNodInfo = CMwNodClassInfo();