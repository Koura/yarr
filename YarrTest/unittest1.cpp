#include "stdafx.h"

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxgi.lib")
#include "CppUnitTest.h"
#include "Entity.h"
#include "DxCamera.h"
#include <D3D10.h>
#include <DXGI.h>
#include <D3DX10.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace YarrTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(NewEntityWithCorrectValues)
		{
			Entity* ent = new Entity;
			Assert::AreEqual<std::string>("Nameless One", ent->GetName());
			Assert::AreEqual<float>(0.0f, ent->GetPosition().x);
			Assert::AreEqual<float>(0.0f, ent->GetPosition().y);
			Assert::AreEqual<float>(0.0f, ent->GetPosition().z);
		}
		TEST_METHOD(NewEntityWithCorrectValuesAndParameters)
		{
			Entity* ent = new Entity("Boogey", 1.0f, 0.0f, 5.0f);
			Assert::AreEqual<std::string>("Boogey", ent->GetName());
			Assert::AreEqual<float>(1.0f, ent->GetPosition().x);
			Assert::AreEqual<float>(0.0f, ent->GetPosition().y);
			Assert::AreEqual<float>(5.0f, ent->GetPosition().z);
		}
		TEST_METHOD(EntityReturnCorrectName)
		{
			Entity* ent = new Entity("Ratman", 0.0f, 0.0f, 0.0f);
			Assert::AreEqual<std::string>("Ratman", ent->GetName());
		}

		TEST_METHOD(EntityChangedPosition)
		{
			Entity* ent = new Entity("Ratman", 0.0f, 0.0f, 0.0f);
			Assert::AreEqual<float>(0.0f, ent->GetPosition().x);
			Assert::AreEqual<float>(0.0f, ent->GetPosition().y);
			Assert::AreEqual<float>(0.0f, ent->GetPosition().z);
			ent->SetPosition(1.0f, 2.0f, 3.0f);
			Assert::AreEqual<float>(1.0f, ent->GetPosition().x);
			Assert::AreEqual<float>(2.0f, ent->GetPosition().y);
			Assert::AreEqual<float>(3.0f, ent->GetPosition().z);
		}

		TEST_METHOD(NewCameraWithCorrectValues)
		{
			DxCamera* cam = new DxCamera;
			Assert::AreEqual<float>(0.0f, cam->GetPosition().x);
			Assert::AreEqual<float>(0.0f, cam->GetPosition().y);
			Assert::AreEqual<float>(0.0f, cam->GetPosition().z);
		}
		TEST_METHOD(CameraChangedPosition)
		{
			DxCamera* cam = new DxCamera;
			cam->SetPosition(1.0f, 2.0f, 3.0f);
			Assert::AreEqual<float>(1.0f, cam->GetPosition().x);
			Assert::AreEqual<float>(2.0f, cam->GetPosition().y);
			Assert::AreEqual<float>(3.0f, cam->GetPosition().z);
		}
		TEST_METHOD(CameraChangedRotation)
		{
			DxCamera* cam = new DxCamera;
			cam->SetRotation(4.0f, 4.0f, 5.0f);
			Assert::AreEqual<float>(4.0f, cam->GetRotation().x);
			Assert::AreEqual<float>(4.0f, cam->GetRotation().y);
			Assert::AreEqual<float>(5.0f, cam->GetRotation().z);
		}
			
	};
}