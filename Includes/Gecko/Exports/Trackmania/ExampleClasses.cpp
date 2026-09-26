#include "pch.h"
#include "ExampleClasses.h"

// TL;DR
// The relation graph is as follows:
// CMwNod -> CParent -> CChild
// CMwNod -> CParent -> CSibling

// BEGIN CParent
CParent_SomethingMemberInfo::CParent_SomethingMemberInfo()
{
	MemberOffset = 40;
	MemberName = "Something";
	MemberType = INT;
	MemberID = 0x08008000;
}

CParent_SomethingMemberInfo CParent_Something = CParent_SomethingMemberInfo();
CMwMemberInfo* CParentMembers[1] = { &CParent_Something };

CParentClassInfo::CParentClassInfo()
{
	ClassID = 0x08008000;
	ClassName = (char*)"CParent";
	Members = CParentMembers;
	MembersAmount = sizeof(CParentMembers) / sizeof(CParentMembers[0]);
	ParentClassInfo = &CMwNodInfo;
}

CParentClassInfo CParentInfo = CParentClassInfo();

CMwClassInfo* CParent::MwGetClassInfo()
{
	return &CParentInfo;
}
// END CParent

// BEGIN CChild
CChild_AnotherThingMemberInfo::CChild_AnotherThingMemberInfo()
{
	MemberOffset = 48;
	MemberName = "AnotherThing";
	MemberType = INT;
	MemberID = 0x08009000;
}

CChild_AnotherThingMemberInfo CChild_AnotherThing = CChild_AnotherThingMemberInfo();
CMwMemberInfo* CChildMembers[1] = { &CChild_AnotherThing };

CChildClassInfo::CChildClassInfo()
{
	ClassID = 0x08009000;
	ClassName = (char*)"CChild";
	Members = CChildMembers;
	MembersAmount = sizeof(CChildMembers) / sizeof(CChildMembers[0]);
	ParentClassInfo = &CParentInfo;
}

CChildClassInfo CChildInfo = CChildClassInfo();

CMwClassInfo* CChild::MwGetClassInfo()
{
	return &CChildInfo;
}
// END CChild

// BEGIN CSibling
CSibling_SiblingThingMemberInfo::CSibling_SiblingThingMemberInfo()
{
	MemberOffset = 48;
	MemberName = "SiblingThing";
	MemberType = INT;
	MemberID = 0x0800A000;
}

CSibling_SiblingThingMemberInfo CSibling_SiblingThing = CSibling_SiblingThingMemberInfo();
CMwMemberInfo* CSiblingMembers[1] = { &CSibling_SiblingThing };

CSiblingClassInfo::CSiblingClassInfo()
{
	ClassID = 0x0800A000;
	ClassName = (char*)"CSibling";
	Members = CSiblingMembers;
	MembersAmount = sizeof(CSiblingMembers) / sizeof(CSiblingMembers[0]);
	ParentClassInfo = &CParentInfo;
}

CSiblingClassInfo CSiblingInfo = CSiblingClassInfo();

CMwClassInfo* CSibling::MwGetClassInfo()
{
	return &CSiblingInfo;
}
// END CSibling

CMwClassInfo* AvailableClasses[4] = { &CMwNodInfo, &CParentInfo, &CChildInfo, &CSiblingInfo };
uint32_t ClassesAmount = 4;
CChild TheChild;
CSibling TheSibling;

void CMwNod_AddRef(CMwNod* Nod)
{
	// printf("AddRef\n");
	Nod->ReferenceCount++;
}

void CMwNod_RemoveRef(CMwNod* Nod)
{
	// printf("RemoveRef\n");
	if (Nod->ReferenceCount == 0) Nod->~CMwNod();
	Nod->ReferenceCount--;
	if (Nod->ReferenceCount == 0) Nod->~CMwNod();
}