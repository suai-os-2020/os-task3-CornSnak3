#include <windows.h>
#include <iostream>
#include "lab3.h"

using namespace std;

#define THREAD_COUNT 11

DWORD ThreadID;
HANDLE wait,up;
HANDLE Mutex;

HANDLE threadA, threadB, threadC, threadD, threadE, threadF, threadG, threadH, threadI, threadK, threadM;
HANDLE SemE, SemF, SemG, SemH;

unsigned int lab3_thread_graph_id()
{
    return 4;
}

const char* lab3_unsynchronized_threads()
{
    return "bcde";
}

const char* lab3_sequential_threads()
{
    return "efgh";
}



DWORD WINAPI thread_a(LPVOID);
DWORD WINAPI thread_b(LPVOID);
DWORD WINAPI thread_c(LPVOID);
DWORD WINAPI thread_d(LPVOID);
DWORD WINAPI thread_e(LPVOID);
DWORD WINAPI thread_f(LPVOID);
DWORD WINAPI thread_g(LPVOID);
DWORD WINAPI thread_h(LPVOID);
DWORD WINAPI thread_i(LPVOID);
DWORD WINAPI thread_k(LPVOID);
DWORD WINAPI thread_m(LPVOID);

DWORD WINAPI thread_e(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(Mutex);
    }

    threadA = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);
    if (threadA == NULL) {
        return GetLastError();
    }
    threadC = CreateThread(NULL, 0, thread_c, NULL, 0, &ThreadID);
    if (threadC == NULL) {
        return GetLastError();
    }
    threadD = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
    if (threadD == NULL) {
        return GetLastError();
    }

    WaitForSingleObject(threadA, INFINITE);
    WaitForSingleObject(wait, INFINITE);
    WaitForSingleObject(wait, INFINITE);

    ReleaseSemaphore(up, 1, NULL);
    ReleaseSemaphore(up, 1, NULL);

    threadB = CreateThread(NULL, 0, thread_b, NULL, 0, &ThreadID);
    if (threadB == NULL) {
        return GetLastError();
    }
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(Mutex);
    }

    WaitForSingleObject(threadB, INFINITE);
    WaitForSingleObject(threadC, INFINITE);
    WaitForSingleObject(wait, INFINITE);



    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(Mutex);
    }


    ReleaseSemaphore(up, 1, NULL);
    threadG = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
    if (threadG == NULL) {
        return GetLastError();
    }
    threadH = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
    if (threadH == NULL) {
        return GetLastError();
    }

    WaitForSingleObject(threadD, INFINITE);
    WaitForSingleObject(wait, INFINITE);
    WaitForSingleObject(wait, INFINITE);

    threadF = CreateThread(NULL, 0, thread_f, NULL, 0, &ThreadID);
    if (threadF == NULL) {
        return GetLastError();
    }

    ReleaseSemaphore(up, 1, NULL);
    ReleaseSemaphore(up, 1, NULL);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(SemE, INFINITE);
        WaitForSingleObject(Mutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(Mutex);
        ReleaseSemaphore(SemF, 1, NULL);
    }

    WaitForSingleObject(threadG, INFINITE);
    WaitForSingleObject(threadF, INFINITE);
    WaitForSingleObject(wait, INFINITE);

    threadI = CreateThread(NULL, 0, thread_i, NULL, 0, &ThreadID);
    if (threadI == NULL) {
        return GetLastError();
    }
    threadK = CreateThread(NULL, 0, thread_k, NULL, 0, &ThreadID);
    if (threadK == NULL) {
        return GetLastError();
    }

    ReleaseSemaphore(up, 1, NULL);
    WaitForSingleObject(threadI, INFINITE);
    WaitForSingleObject(threadK, INFINITE);
    WaitForSingleObject(threadH, INFINITE);

    threadM = CreateThread(NULL, 0, thread_m, NULL, 0, &ThreadID);
    if (threadM == NULL) {
        return GetLastError();
    }
    WaitForSingleObject(threadM, INFINITE);
    return 0;
}

DWORD WINAPI thread_a(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "a" << flush;
        computation();
        ReleaseMutex(Mutex);
    }

    return 0;
}

DWORD WINAPI thread_b(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "b" << flush;
        computation();
        ReleaseMutex(Mutex);
    }

    return 0;
}

DWORD WINAPI thread_c(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "c" << flush;
        computation();
        ReleaseMutex(Mutex);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "c" << flush;
        computation();
        ReleaseMutex(Mutex);
    }

    return 0;
}

DWORD WINAPI thread_d(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "d" << flush;
        computation();
        ReleaseMutex(Mutex);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "d" << flush;
        computation();
        ReleaseMutex(Mutex);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "d" << flush;
        computation();
        ReleaseMutex(Mutex);
    }
    return 0;
}



DWORD WINAPI thread_i(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "i" << flush;
        computation();
        ReleaseMutex(Mutex);
    }

    return 0;
}


DWORD WINAPI thread_h(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "h" << flush;
        computation();
        ReleaseMutex(Mutex);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(SemH, INFINITE);
        WaitForSingleObject(Mutex, INFINITE);
        cout << "h" << flush;
        computation();
        ReleaseMutex(Mutex);
        ReleaseSemaphore(SemE, 1, NULL);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "h" << flush;
        computation();
        ReleaseMutex(Mutex);
    }

    return 0;
}

DWORD WINAPI thread_g(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "g" << flush;
        computation();
        ReleaseMutex(Mutex);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(SemG, INFINITE);
        WaitForSingleObject(Mutex, INFINITE);
        cout << "g" << flush;
        computation();
        ReleaseMutex(Mutex);
        ReleaseSemaphore(SemH, 1, NULL);
    }

    return 0;
}

DWORD WINAPI thread_f(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(SemF, INFINITE);
        WaitForSingleObject(Mutex, INFINITE);
        cout << "f" << flush;
        computation();
        ReleaseMutex(Mutex);
        ReleaseSemaphore(SemG, 1, NULL);
    }

    return 0;
}

DWORD WINAPI thread_k(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "k" << flush;
        computation();
        ReleaseMutex(Mutex);
    }

    return 0;
}

DWORD WINAPI thread_m(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "m" << flush;
        computation();
        ReleaseMutex(Mutex);
    }

    return 0;
}

DWORD WINAPI thread_n(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(Mutex, INFINITE);
        cout << "n" << flush;
        computation();
        ReleaseMutex(Mutex);
    }

    return 0;
}



int lab3_init()
{
    Mutex = CreateMutex(NULL, 0, NULL);
    if (Mutex == NULL) {
        cout << "CreateMutex error: " << GetLastError();
        return 1;
    }

    wait = CreateSemaphore(NULL, 0, 3, NULL);
    up = CreateSemaphore(NULL, 0, 3, NULL);

    SemE = CreateSemaphore(nullptr, 1, 1, nullptr);
    if (SemE == nullptr)
    {
        cout << "CreateSemaphore error: SemD" << GetLastError() << endl;
        return 1;
    }

    SemF = CreateSemaphore(nullptr, 0, 1, nullptr);
    if (SemF == nullptr)
    {
        cout << "CreateSemaphore error: SemE " << GetLastError() << endl;
        return 1;
    }

    SemG = CreateSemaphore(nullptr, 0, 1, nullptr);
    if (SemG == nullptr)
    {
        cout << "CreateSemaphore error: SemG" << GetLastError() << endl;
        return 1;
    }

    SemH = CreateSemaphore(nullptr, 0, 1, nullptr);
    if (SemH == nullptr)
    {
        cout << "CreateSemaphore error: SemH" << GetLastError() << endl;
        return 1;
    }

    threadE = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
    if (threadE == NULL) {
        return GetLastError();
    }

    WaitForSingleObject(threadE, INFINITE);

    CloseHandle(threadA);
    CloseHandle(threadB);
    CloseHandle(threadC);
    CloseHandle(threadD);
    CloseHandle(threadE);
    CloseHandle(threadF);
    CloseHandle(threadG);
    CloseHandle(threadH);
    CloseHandle(threadI);
    CloseHandle(threadK);
    CloseHandle(threadM);

    CloseHandle(SemE);
    CloseHandle(SemF);
    CloseHandle(SemG);
    CloseHandle(SemH);

    CloseHandle(wait);
    CloseHandle(up);

    return 0;
}