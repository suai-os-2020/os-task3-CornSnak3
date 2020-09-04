#include "lab3.h"
#include <windows.h>
#include <stdio.h>

#define THREADCOUNT 5

HANDLE Thread[THREADCOUNT];
HANDLE Mutex;
HANDLE SemA, SemB, SemC, SemD;

unsigned int lab3_thread_graph_id() {
	return 4;
}

const char* lab3_unsynchronized_threads() {
	return "bcde";
}

const char* lab3_sequential_threads() {
	return "efgh";
}

DWORD WINAPI threads_unsynchronized(LPVOID text) {
	for (int i = 0; i < 4; ++i) {
		WaitForSingleObject(Mutex, INFINITE);
		std::cout << (char const*)text << std::flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_e(LPVOID text) {
	for (int i = 0; i < 4; ++i) {
		WaitForSingleObject(SemA, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		std::cout <<(char const*)text << std::flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemB, 1, nullptr);
	}
	return 0;
}

DWORD WINAPI thread_f(LPVOID text) {
	for (int i = 0; i < 4; ++i) {
		WaitForSingleObject(SemB, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		std::cout <<(char const*)text << std::flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemC, 1, nullptr);
	}
	return 0;
}

DWORD WINAPI thread_g(LPVOID text) {
	for (int i = 0; i < 4; ++i) {
		WaitForSingleObject(SemC, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		std::cout << (char const*) text << std::flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemD, 1, nullptr);
	}
	return 0;
}

DWORD WINAPI thread_h(LPVOID text) {
	for (int i = 0; i < 4; ++i) {
		WaitForSingleObject(SemD, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		std::cout << (char const*) text << std::flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemA, 1, nullptr);
	}
	return 0;
}

int lab3_init() {
	DWORD ThreadID;

	Mutex = CreateMutex(nullptr, FALSE, nullptr);
	if (Mutex == nullptr) {
		std::cout << "CreateMutex error " << GetLastError() << std::endl;
		return 1;
	}

	SemA = CreateSemaphore(nullptr, 1, 1, nullptr);
	if (SemA == nullptr) {
		std::cout << "Error: SemA" << GetLastError() << std::endl;
		return 1;
	}

	SemB = CreateSemaphore(nullptr, 0, 1, nullptr);
	if (SemA == nullptr) {
		std::cout << "Error: Sem2 " << GetLastError() << std::endl;
		return 1;
	}

	SemC = CreateSemaphore(nullptr, 0, 1, nullptr);
	if (SemA == nullptr) {
		std::cout << "Error: Sem3" << GetLastError() << std::endl;
		return 1;
	}

	SemD = CreateSemaphore(nullptr, 0, 1, nullptr);
	if (SemA == nullptr) {
		std::cout << "Error: Sem4" << GetLastError() << std::endl;
		return 1;
	}


	int count = 0;

	char const* textsCADE[] = { "c", "a", "d", "e" };

	for (int i = 0; i < 4; ++i)	{
		Thread[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsCADE[i], 0, &ThreadID);
		if (Thread[i] == nullptr) {
			std::cout << "CreateThread error: " << textsCADE[i] << GetLastError() << std::endl;
			return 1;
		}
		else ++count;
	}

	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	count = 0;

	char const* textsCBDE[] = { "c", "b", "d", "e" };

	for (int i = 0; i < 4; ++i)	{
		Thread[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsCBDE[i], 0, &ThreadID);
		if (Thread[i] == nullptr) {
			std::cout << "CreateThread error: " << textsCBDE[i] << GetLastError() << std::endl;
			return 1;
		}
		else ++count;
	}

	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}


	count = 0;

	char const* textsHGDE[] = { "h", "g", "d", "e" };

	for (int i = 0; i < 4; ++i)	{
		Thread[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsHGDE[i], 0, &ThreadID);
		if (Thread[i] == nullptr) {
			std::cout << "CreateThread error: " << textsHGDE[i] << GetLastError() << std::endl;
			return 1;
		}
		else ++count;
	}

	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}


	count = 0;

	char const* textsHFEG[] = { "e", "f", "g", "h" };

	Thread[0] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)thread_e, (void*)textsHFEG[0], 0, &ThreadID);
	if (Thread[0] == nullptr) {
		std::cout << "CreateThread error: " << textsHGDE[0] << GetLastError() << std::endl;
		return 1;
	}

	Thread[1] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)thread_f, (void*)textsHFEG[1], 0, &ThreadID);
	if (Thread[1] == nullptr) {
		std::cout << "CreateThread error: " << textsHGDE[1] << GetLastError() << std::endl;
		return 1;
	}

	Thread[2] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)thread_g, (void*)textsHFEG[2], 0, &ThreadID);
	if (Thread[2] == nullptr) {
		std::cout << "CreateThread error: " << textsHGDE[2] << GetLastError() << std::endl;
		return 1;
	}

	Thread[3] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)thread_h, (void*)textsHFEG[3], 0, &ThreadID);
	if (Thread[3] == nullptr) {
		std::cout << "CreateThread error: " << textsHGDE[3] << GetLastError() << std::endl;
		return 1;
	}


	for (int i = 0; i < 3; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	count = 0;

	char const* textsHIK[] = { "h", "i", "k"};

	for (int i = 0; i < 3; ++i)	{
		Thread[i] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsHIK[i], 0, &ThreadID);
		if (Thread[i] == nullptr) {
			std::cout << "CreateThread error: " << textsHIK[i] << GetLastError() << std::endl;
			return 1;
		}
		else ++count;
	}

	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}


	char const* textsM = "m";
	Thread[0] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsM, 0, &ThreadID);
	if (Thread[0] == nullptr) {
		std::cout << "CreateThread error: " << textsM << GetLastError() << std::endl;
		return 1;
	}

	WaitForSingleObject(Thread[0], INFINITE);

	for (int i = 0; i < THREADCOUNT; ++i) {
		CloseHandle(Thread[i]);
	}

	CloseHandle(SemA);
	CloseHandle(SemB);
	CloseHandle(SemC);
	CloseHandle(SemD);
	CloseHandle(Mutex);

	std::cout << std::endl;

	return 0;
}