#pragma once
#include "TMTypes.h"

// BEGIN CParent
class CParent_SomethingMemberInfo : public CMwMemberInfo
{
public:
	CParent_SomethingMemberInfo();
};

extern CParent_SomethingMemberInfo CParent_Something;
extern CMwMemberInfo* CParentMembers[1];

class CParentClassInfo : public CMwClassInfo
{
public:
	CParentClassInfo();
};

extern CParentClassInfo CParentInfo;

class CParent : public CMwNod
{
public:
	virtual CMwClassInfo* MwGetClassInfo();

	int Something = 69;
};
// END CParent

// BEGIN CChild
class CChild_AnotherThingMemberInfo : public CMwMemberInfo
{
public:
	CChild_AnotherThingMemberInfo();
};

extern CMwMemberInfo* CChildMembers[1];

class CChildClassInfo : public CMwClassInfo
{
public:
	CChildClassInfo();
};

extern CChildClassInfo CChildInfo;

class CChild : public CParent
{
public:
	virtual CMwClassInfo* MwGetClassInfo();

	int AnotherThing = 42;
};
// END CChild

// BEGIN CSibling
class CSibling_SiblingThingMemberInfo : public CMwMemberInfo
{
public:
	CSibling_SiblingThingMemberInfo();
};

extern CMwMemberInfo* CSiblingMembers[1];

class CSiblingClassInfo : public CMwClassInfo
{
public:
	CSiblingClassInfo();
};

extern CSiblingClassInfo CSiblingInfo;

class CSibling : public CParent
{
public:
	virtual CMwClassInfo* MwGetClassInfo();

	int AnotherThing = 67;
};
// END CSibling

extern CMwClassInfo* AvailableClasses[4];
extern uint32_t ClassesAmount;
extern CChild TheChild;
extern CSibling TheSibling;

void CMwNod_AddRef(CMwNod*);
void CMwNod_RemoveRef(CMwNod*);