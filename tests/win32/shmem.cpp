/* tests/win32/shmem.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <numeric>

#include "tests/catch.hpp"

#include "win32/shmem.hpp"

TEST_CASE("Shared memory", "[Win32]")
{
  SECTION("typed access")
  {
    Windows::SharedMemory< DWORD > sm(L"test_shared_memory");
    REQUIRE(sm);

    HANDLE h = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,L"Local\\test_shared_memory_SHMEM");
    REQUIRE(h != NULL);

    LPVOID p = MapViewOfFileEx(h,FILE_MAP_ALL_ACCESS,0,0,0,NULL);
    REQUIRE(p != NULL);

    UnmapViewOfFile(p);
    CloseHandle(h);

    sm.access([] (DWORD *ptr)
      {
        *ptr = 5;
      });

    sm.access([](DWORD *ptr)
      {
        REQUIRE(*ptr == 5);
      });
  }

  SECTION("raw access")
  {
    Windows::RawSharedMemory sm(256,L"test_raw_shared_memory");
    REQUIRE(sm);

    HANDLE h = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,L"Local\\test_raw_shared_memory_SHMEM");
    REQUIRE(h != NULL);

    LPVOID p = MapViewOfFileEx(h,FILE_MAP_ALL_ACCESS,0,0,0,NULL);
    REQUIRE(p != NULL);

    UnmapViewOfFile(p);
    CloseHandle(h);

    sm.access([] (DWORD size, LPVOID mp)
      {
        BYTE *ptr = reinterpret_cast< BYTE * >(mp);
        std::iota(ptr,ptr + size,static_cast< BYTE >(0));
      });

    sm.access([] (DWORD size, LPVOID mp)
      {
        BYTE *ptr = reinterpret_cast< BYTE * >(mp);
        REQUIRE(*ptr == 0);
        REQUIRE(*(ptr + size - 1) == 255);
    });
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}
