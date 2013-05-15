#include "stdafx.h"
#include "CppUnitTest.h"
#include "Entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace YarrTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(EntityReturnCorrectName)
		{
			Entity* ent = new Entity;
			Assert::AreEqual<int>(1,1);
		}
	};
}