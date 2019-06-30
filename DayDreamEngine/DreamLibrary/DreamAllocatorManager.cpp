#include <iostream>
#include "DreamAllocatorManager.h"
#include "DreamPoolAllocator.h"

DreamStaticStackAllocator* DreamAllocatorManager::stackAllocator = nullptr;

void DreamAllocatorManager::InitMainStackAllocator(uint32_t maxStackSize)
{
	if (stackAllocator == nullptr) {
		stackAllocator = new DreamStaticStackAllocator(maxStackSize);
	}
}

void DreamAllocatorManager::ShutDownMainStackAllocator()
{
	delete stackAllocator;
}

void DreamAllocatorManager::MarkChunkOnMainSA(const char * memChunkTitle)
{
	stackAllocator->MarkChunk(memChunkTitle);
}

void DreamAllocatorManager::PopChunkOffMainSA()
{
	stackAllocator->PopChunk();
}

void DreamAllocatorManager::PopOffMainSA()
{
	stackAllocator->Pop();
}

void DreamAllocatorManager::ClearMainSA()
{
	stackAllocator->Clear();
}

void DreamAllocatorManager::GetMainStaticAllocatorUsedMemorySize()
{
	stackAllocator->GetUsedMemorySize();
}

void DreamAllocatorManager::PrintMainStaticAllocatorUsedMemorySize()
{
	printf("Main Static Allocator Used Mem Size: %d\n", (int)stackAllocator->GetUsedMemorySize());
}

DreamStaticStackAllocator * DreamAllocatorManager::CreateNewStackAllocator(uint32_t stackSize)
{

	return nullptr;
}

DreamPoolAllocator * DreamAllocatorManager::CreateNewPoolAllocator(uint32_t poolSize)
{
	return nullptr;
}

