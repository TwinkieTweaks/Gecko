#include "pch.h"
#include "CppUnitTest.h"
#include <Gecko/Gecko.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Gecko
{
	TEST_CLASS(Gecko)
	{
	public:
		TEST_METHOD(ClassRelationshipTest)
		{
			TheScriptManager.AddFromSource(
				u8"void Main()\n"
				u8"{\n"
				u8"    CChild@ Child = GetTheChild();\n"
				u8"    CSibling@ Sibling = GetTheSibling();\n"
				u8"\n"
				u8"    bool ChildIsNull = (Child is null);\n"
				u8"    bool SiblingIsNull = (Sibling is null);\n"
				u8"\n"
				u8"    CParent@ ChildAsParent = cast<CParent>(Child);\n"
				u8"    CParent@ SiblingAsParent = cast<CParent>(Sibling);\n"
				u8"\n"
				u8"    bool ChildAsParentIsNull = (ChildAsParent is null);\n"
				u8"    bool SiblingAsParentIsNull = (SiblingAsParent is null);\n"
				u8"\n"
				u8"    CSibling@ ChildAsSibling = cast<CSibling>(ChildAsParent);\n"
				u8"    CChild@ ChildAsParentAsChild = cast<CChild>(ChildAsParent);\n"
				u8"    CChild@ SiblingAsChild = cast<CChild>(SiblingAsParent);\n"
				u8"    CSibling@ SiblingAsParentAsSibling = cast<CSibling>(SiblingAsParent);\n"
				u8"\n"
				u8"    bool ChildAsSiblingIsNull = (ChildAsSibling is null);\n"
				u8"    bool ChildAsParentAsChildIsNull = (ChildAsParentAsChild is null);\n"
				u8"    bool SiblingAsChildIsNull = (SiblingAsChild is null);\n"
				u8"    bool SiblingAsParentAsSiblingIsNull = (SiblingAsParentAsSibling is null);\n"
				u8"    yield();"
				u8"}\n",
				u8"Script");

			TheScriptManager.BuildAll();
			TheScriptManager.RunAll(CallbackType::Main);
			
			auto CtxMain = TheScriptManager.Scripts[0].Ctxs.CtxMain;
			auto GetVarByName = [&](const char* Needle) 
			{
				int VarCount = CtxMain->GetVarCount();
				for (int VarIdx = 0; VarIdx < VarCount; VarIdx++) 
				{
					const char* Haystack = nullptr;
					int TypeID = 0;

					CtxMain->GetVar(VarIdx, 0, &Haystack, &TypeID);

					if (Haystack && strcmp(Haystack, Needle) == 0) 
					{
						return (bool*)CtxMain->GetAddressOfVar(VarIdx, 0);
					}
				}
				return (bool*)nullptr;
			};

			Assert::IsFalse(*GetVarByName("ChildIsNull"));
			Assert::IsFalse(*GetVarByName("SiblingIsNull"));

			Assert::IsFalse(*GetVarByName("ChildAsParentIsNull"));
			Assert::IsFalse(*GetVarByName("SiblingAsParentIsNull"));

			Assert::IsTrue(*GetVarByName("ChildAsSiblingIsNull"));
			Assert::IsFalse(*GetVarByName("ChildAsParentAsChildIsNull"));
			Assert::IsTrue(*GetVarByName("SiblingAsChildIsNull"));
			Assert::IsFalse(*GetVarByName("SiblingAsParentAsSiblingIsNull"));
		}
	};
}
