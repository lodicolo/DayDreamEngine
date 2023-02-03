#include <pch.h>
#include<assert.h>
#include <iostream>
#include "DreamGraphics.h"
#include "DreamMesh.h"
#include <DreamAllocatorManager.h>
#include <DreamFileIO.h>
#include <DreamUnitTest.h>
#include <DreamTimeManager.h>
#include <Windows.h>
#include "DreamCameraManager.h"



void UnitTestFileIO() {

	std::string testLines[]{
	"Yaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahh",
	"Yoooooooo",
	"Yaeeeeeeeeeee",
	"Yweeeeeeeeeeeeeee",
	};

	DreamFileIO::OpenFileWrite("word.txt", FileWriteType::OverWrite);

	for (int i = 0; i < sizeof(testLines) / sizeof(std::string); i++) {
		DreamFileIO::WriteLine(testLines[i].c_str());
	}
	DreamFileIO::CloseFileWrite();

	if (DreamFileIO::OpenFileRead("word.txt")) {
		int i = 0;
		std::string line;
		while (DreamFileIO::ReadLine(line)) {

			assert(line == testLines[i]);
			printf("%s\n", line.c_str());
			i++;
		}
		DreamFileIO::CloseFileRead();
	}
}

void UnitTestMath() {

	DreamUnitTest::PrintUnitTestRunName("MATH TEST");

	float num = 89.0f; // result: 0.86006940581

	float sinCalc = DreamMath::round(DreamMath::sin(num));
	float cosCalc = DreamMath::round(DreamMath::cos(num));
	float tanCalc = DreamMath::round(DreamMath::tan(num));

	float sinResult = 1.00f;
	float cosResult = 0.02f;
	float tanResult = 57.29f;

	DreamUnitTest::FloatUnitTest("Sin Math Unit Test", sinResult, sinCalc);
	DreamUnitTest::FloatUnitTest("Cos Math Unit Test", cosResult, cosCalc);
	DreamUnitTest::FloatUnitTest("Tan Math Unit Test", tanResult, tanCalc);

	assert(sinResult == sinCalc);
	assert(cosResult == cosCalc);
	assert(tanResult == tanCalc);
}

void UnitTestAllocators() {
	DreamAllocatorManager::InitMainStackAllocator();
	DreamMath::DreamVector3* newPosition = DreamAllocatorManager::AllocateOnMainSA<DreamMath::DreamVector3>();

	printf("x: %f, y: %f, z: %f\n", newPosition->x, newPosition->y, newPosition->z);

	DreamAllocatorManager::ShutDownMainStackAllocator();
}

void UnitTest() {
	UnitTestFileIO();
	UnitTestMath();
	UnitTestAllocators();
}

// NOTE: Dont run on a Samsung Fridge
int main()
{
	UnitTest();

	DreamGraphics* graphics = DreamGraphics::GetInstance();

	graphics->InitWindow(800, 600, "Hey It's a window!");
	graphics->InitGraphics();
	graphics->SetScreenClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//graphics->SetViewPort(0,0, 200, 200); // TODO: doesnt work halp ;-;

	DreamShader* vertexShader = new VertexDreamShader(L"vertex");
	DreamShader* pixelShader = new PixelDreamShader(L"pixel");

	DreamShaderLinker* mainLink = DreamGraphics::GenerateShaderLinker();
	mainLink->AttachShader(vertexShader);
	mainLink->AttachShader(pixelShader);
	mainLink->Finalize();

	std::vector<DreamVertex> vert = std::vector<DreamVertex>();
	std::vector<uint32_t> indices = std::vector<uint32_t>();

	vert.push_back(DreamVertex(-0.5, -0.5, 0.0f));
	vert.push_back(DreamVertex(0.0, 0.5, 0.0f));
	vert.push_back(DreamVertex(0.5, -0.5, 0.0f));
	vert.push_back(DreamVertex(1.0, 0.5, 0.0f));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);

	DreamMesh* mesh = new DreamMesh(mainLink, vert);
	//DreamMesh* mesh = new DreamMesh(mainLink, vert, indices);

	DreamCameraManager* camManager = DreamCameraManager::GetInstance();
	DreamCamera* camera = new DreamCamera();
	camManager->SetActiveCamera(camera);


	DreamTimeManager::Init();
	while (!graphics->CheckWindowClose())
	{
		DreamTimeManager::Update();

		// Controller
		graphics->CheckInputs(); //TODO: needs to be on input manager

		// Model
		camera->Update();

		// View
		graphics->ClearScreen();

		//NOTE: there is a black line on the side of the drawn triangle, halp
		// TODO: Bind Graphic pipelines instead of shaders individually
		// TODO: Spirv-Cross to handle all shader platform types
		mesh->DrawOpaque();
		graphics->Draw();

		graphics->SwapBuffers();
	}

	if (mesh) {
		delete mesh;
		mesh = nullptr;
	}

	// TODO: Garbage Collector? delay deletes till end of frame [MarkForDeletion]
	graphics->ReleaseShader(vertexShader);
	graphics->ReleaseShader(pixelShader);
	graphics->DestroyWindow();
	graphics->TerminateGraphics();

	if (graphics) {
		delete graphics;
		graphics = nullptr;
	}

	return 0;
}
