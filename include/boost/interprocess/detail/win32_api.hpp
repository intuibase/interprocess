//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gazta�aga 2005-2007. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WIN32_SYNC_PRIMITIVES_HPP
#define BOOST_INTERPROCESS_WIN32_SYNC_PRIMITIVES_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)
#  include <stddef.h>
#  include <stdarg.h>
#  include <boost/detail/interlocked.hpp>
#else
# error "This file can only be included in Windows OS"
#endif

//The structures used in Interprocess with the
//same binary interface as windows ones
namespace boost {
namespace interprocess {
namespace winapi {

//Some used constants
static const unsigned long infinite_time        = 0xFFFFFFFF;
static const unsigned long error_already_exists = 183L;
static const unsigned long error_file_not_found = 2u;

static const unsigned long semaphore_all_access = (0x000F0000L)|(0x00100000L)|0x3;
static const unsigned long mutex_all_access     = (0x000F0000L)|(0x00100000L)|0x0001;

static const unsigned long page_readonly        = 0x02;
static const unsigned long page_readwrite       = 0x04;
static const unsigned long page_writecopy       = 0x08;

static const unsigned long standard_rights_required   = 0x000F0000L;
static const unsigned long section_query              = 0x0001;
static const unsigned long section_map_write          = 0x0002;
static const unsigned long section_map_read           = 0x0004;
static const unsigned long section_map_execute        = 0x0008;
static const unsigned long section_extend_size        = 0x0010;
static const unsigned long section_all_access         = standard_rights_required |
                                                        section_query            |
                                                        section_map_write        |
                                                        section_map_read         |
                                                        section_map_execute      |
                                                        section_extend_size;

static const unsigned long file_map_copy        = section_query;
static const unsigned long file_map_write       = section_map_write;
static const unsigned long file_map_read        = section_map_read;
static const unsigned long file_map_all_access  = section_all_access;

static const unsigned long file_share_read      = 0x00000001;
static const unsigned long file_share_write     = 0x00000002;

static const unsigned long generic_read         = 0x80000000L;
static const unsigned long generic_write        = 0x40000000L;

static const unsigned long wait_object_0        = 0;
static const unsigned long wait_abandoned       = 0x00000080L;
static const unsigned long wait_timeout         = 258L;
static const unsigned long wait_failed          = (unsigned long)0xFFFFFFFF;

static const unsigned long duplicate_close_source  = (unsigned long)0x00000001;
static const unsigned long duplicate_same_access   = (unsigned long)0x00000002;

static const unsigned long format_message_allocate_buffer
   = (unsigned long)0x00000100;
static const unsigned long format_message_ignore_inserts
   = (unsigned long)0x00000200;
static const unsigned long format_message_from_string
   = (unsigned long)0x00000400;
static const unsigned long format_message_from_hmodule
   = (unsigned long)0x00000800;
static const unsigned long format_message_from_system
   = (unsigned long)0x00001000;
static const unsigned long format_message_argument_array
   = (unsigned long)0x00002000;
static const unsigned long format_message_max_width_mask
   = (unsigned long)0x000000FF;
static const unsigned long lang_neutral         = (unsigned long)0x00;
static const unsigned long sublang_default      = (unsigned long)0x01;
static const unsigned long invalid_file_size    = (unsigned long)0xFFFFFFFF;
static       void * const  invalid_handle_value = (void*)(long*)-1;
static const unsigned long create_new        = 1;
static const unsigned long create_always     = 2;
static const unsigned long open_existing     = 3;
static const unsigned long open_always       = 4;
static const unsigned long truncate_existing = 5;

static const unsigned long file_attribute_temporary = 0x00000100;

static const unsigned long file_begin     = 0;
static const unsigned long file_current   = 1;
static const unsigned long file_end       = 2;

static const unsigned long lockfile_fail_immediately  = 1;
static const unsigned long lockfile_exclusive_lock    = 2;
static const unsigned long error_lock_violation       = 33;

}  //namespace winapi {
}  //namespace interprocess  {
}  //namespace boost  {

#if !defined( BOOST_USE_WINDOWS_H )

namespace boost  {
namespace interprocess  {
namespace winapi {

struct interprocess_overlapped 
{
   unsigned long *internal;
   unsigned long *internal_high;
   union {
      struct {
         unsigned long offset;
         unsigned long offset_high;
      }dummy;
      void *pointer;
   };

   void *h_event;
};

struct interprocess_filetime
{  
   unsigned long  dwLowDateTime;  
   unsigned long  dwHighDateTime;
};

struct interprocess_security_attributes
{
   unsigned long nLength;
   void *lpSecurityDescriptor;
   int bInheritHandle;
};

struct system_info {
    union {
        unsigned long dwOemId;          // Obsolete field...do not use
        struct {
            unsigned short wProcessorArchitecture;
            unsigned short wReserved;
        } dummy;
    };
    unsigned long dwPageSize;
    void * lpMinimumApplicationAddress;
    void * lpMaximumApplicationAddress;
    unsigned long * dwActiveProcessorMask;
    unsigned long dwNumberOfProcessors;
    unsigned long dwProcessorType;
    unsigned long dwAllocationGranularity;
    unsigned short wProcessorLevel;
    unsigned short wProcessorRevision;
};

struct interprocess_memory_basic_information
{
   void *         BaseAddress;  
   void *         AllocationBase;
   unsigned long  AllocationProtect;
   unsigned long  RegionSize;
   unsigned long  State;
   unsigned long  Protect;
   unsigned long  Type;
};

//Some windows API declarations
extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentThreadId();
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError();
extern "C" __declspec(dllimport) void * __stdcall GetCurrentProcess();
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void*);
extern "C" __declspec(dllimport) int __stdcall DuplicateHandle
   ( void *hSourceProcessHandle,    void *hSourceHandle
   , void *hTargetProcessHandle,    void **lpTargetHandle
   , unsigned long dwDesiredAccess, int bInheritHandle
   , unsigned long dwOptions);
extern "C" __declspec(dllimport) void __stdcall GetSystemTimeAsFileTime(interprocess_filetime*);
extern "C" __declspec(dllimport) void * __stdcall CreateMutexA(interprocess_security_attributes*, int, const char *);
extern "C" __declspec(dllimport) void * __stdcall OpenMutexA(unsigned long, int, const char *);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *);
extern "C" __declspec(dllimport) int __stdcall UnmapViewOfFile(void *);
extern "C" __declspec(dllimport) void * __stdcall CreateSemaphoreA(interprocess_security_attributes*, long, long, const char *);
extern "C" __declspec(dllimport) int __stdcall ReleaseSemaphore(void *, long, long *);
extern "C" __declspec(dllimport) void * __stdcall OpenSemaphoreA(unsigned long, int, const char *);
extern "C" __declspec(dllimport) void * __stdcall CreateFileMappingA (void *, interprocess_security_attributes*, unsigned long, unsigned long, unsigned long, const char *);
extern "C" __declspec(dllimport) void * __stdcall MapViewOfFileEx (void *, unsigned long, unsigned long, unsigned long, size_t, void*);
extern "C" __declspec(dllimport) void * __stdcall OpenFileMappingA (unsigned long, int, const char *);
extern "C" __declspec(dllimport) void * __stdcall CreateFileA (const char *, unsigned long, unsigned long, struct _SECURITY_ATTRIBUTES*, unsigned long, unsigned long, void *);
extern "C" __declspec(dllimport) int __stdcall    DeleteFileA (const char *);
extern "C" __declspec(dllimport) void __stdcall GetSystemInfo (struct system_info *);
extern "C" __declspec(dllimport) int __stdcall FlushViewOfFile (void *, size_t);
extern "C" __declspec(dllimport) int __stdcall GetFileSizeEx (void *, __int64 *size);
extern "C" __declspec(dllimport) unsigned long __stdcall FormatMessageA
   (unsigned long dwFlags,       const void *lpSource,   unsigned long dwMessageId, 
   unsigned long dwLanguageId,   char *lpBuffer,         unsigned long nSize, 
   va_list *Arguments);
extern "C" __declspec(dllimport) void *__stdcall LocalFree (void *);
extern "C" __declspec(dllimport) int __stdcall CreateDirectoryA(const char *, interprocess_security_attributes*);
extern "C" __declspec(dllimport) int __stdcall GetTempPathA(unsigned long length, char *buffer);
extern "C" __declspec(dllimport) int __stdcall CreateDirectory(const char *, interprocess_security_attributes*);
extern "C" __declspec(dllimport) int __stdcall SetFileValidData(void *, __int64 size);
extern "C" __declspec(dllimport) int __stdcall SetEndOfFile(void *);
extern "C" __declspec(dllimport) int __stdcall SetFilePointerEx(void *, __int64 distance, __int64 *new_file_pointer, unsigned long move_method);
extern "C" __declspec(dllimport) int __stdcall LockFile  (void *hnd, unsigned long offset_low, unsigned long offset_high, unsigned long size_low, unsigned long size_high);
extern "C" __declspec(dllimport) int __stdcall UnlockFile(void *hnd, unsigned long offset_low, unsigned long offset_high, unsigned long size_low, unsigned long size_high);
extern "C" __declspec(dllimport) int __stdcall LockFileEx(void *hnd, unsigned long flags, unsigned long reserved, unsigned long size_low, unsigned long size_high, interprocess_overlapped* overlapped);
extern "C" __declspec(dllimport) int __stdcall UnlockFileEx(void *hnd, unsigned long reserved, unsigned long size_low, unsigned long size_high, interprocess_overlapped* overlapped);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement( long volatile * );
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile * );
extern "C" __declspec(dllimport) long __stdcall InterlockedCompareExchange( long volatile *, long, long );
extern "C" __declspec(dllimport) long __stdcall InterlockedExchangeAdd(long volatile *, long);
extern "C" __declspec(dllimport) long __stdcall InterlockedExchange(long volatile *, long);

}  //namespace winapi {
}  //namespace interprocess  {
}  //namespace boost  {

#else
#  include <windows.h>
#endif   //#if !defined( BOOST_USE_WINDOWS_H )

namespace boost {
namespace interprocess {
namespace winapi {

static inline unsigned long format_message
   (unsigned long dwFlags, const void *lpSource,
    unsigned long dwMessageId, unsigned long dwLanguageId,
    char *lpBuffer, unsigned long nSize, va_list *Arguments)
{
   return FormatMessageA
      (dwFlags, lpSource, dwMessageId, dwLanguageId, lpBuffer, nSize, Arguments);
}

//And now, wrapper functions
static inline void * local_free(void *hmem)
{  return LocalFree(hmem); }

static inline unsigned long make_lang_id(unsigned long p, unsigned long s)
{  return ((((unsigned short)(s)) << 10) | (unsigned short)(p));   }

static inline void sched_yield()
{  Sleep(1);   }

static inline unsigned long get_current_thread_id()
{  return GetCurrentThreadId();  }

static inline unsigned int close_handle(void* handle)
{  return CloseHandle(handle);   }

static inline bool duplicate_current_process_handle
   (void *hSourceHandle, void **lpTargetHandle)
{
   return 0 != DuplicateHandle
      ( GetCurrentProcess(),  hSourceHandle,    GetCurrentProcess()
      , lpTargetHandle,       0,                0
      , duplicate_same_access);
}

static inline unsigned long get_last_error()
{  return GetLastError();  }

static inline void get_system_time_as_file_time(interprocess_filetime *filetime)
{  GetSystemTimeAsFileTime(filetime);  }

static inline void *create_mutex(const char *name)
{  return CreateMutexA(0, 0, name); }

static inline void *open_mutex(const char *name)
{  return OpenMutexA(mutex_all_access, 0, name); }

static inline unsigned long wait_for_single_object(void *handle, unsigned long time)
{  return WaitForSingleObject(handle, time); }

static inline int release_mutex(void *handle)
{  return ReleaseMutex(handle);  }

static inline int unmap_view_of_file(void *address)
{  return UnmapViewOfFile(address); }

static inline void *create_semaphore(long initialCount, const char *name)
{  return CreateSemaphoreA(0, initialCount, (long)(((unsigned long)(-1))>>1), name);   }

static inline int release_semaphore(void *handle, long release_count, long *prev_count)
{  return ReleaseSemaphore(handle, release_count, prev_count); }

static inline void *open_semaphore(const char *name)
{  return OpenSemaphoreA(semaphore_all_access, 1, name); }

static inline void * create_file_mapping (void * handle, unsigned long access, unsigned long high_size, unsigned long low_size, const char * name)
{  return CreateFileMappingA (handle, 0, access, high_size, low_size, name);  }

static inline void * open_file_mapping (unsigned long access, const char *name)
{  return OpenFileMappingA (access, 0, name);   }

static inline void *map_view_of_file_ex(void *handle, unsigned long file_access, unsigned long highoffset, unsigned long lowoffset, std::size_t numbytes, void *base_addr)
{  return MapViewOfFileEx(handle, file_access, highoffset, lowoffset, numbytes, base_addr);  }

static inline void *create_file(const char *name, unsigned long access, unsigned long creation_flags, unsigned long attributes = 0)
{  return CreateFileA(name, access, file_share_read | file_share_write, 0, creation_flags, attributes, 0);  }

static inline bool delete_file(const char *name)
{  return 0 != DeleteFileA(name);  }

static inline void get_system_info(system_info *info)
{  GetSystemInfo(info); }

static inline int flush_view_of_file(void *base_addr, std::size_t numbytes)
{  return FlushViewOfFile(base_addr, numbytes); }

static inline bool get_file_size(void *handle, __int64 &size)
{  return 0 != GetFileSizeEx(handle, &size);  }

static inline bool create_directory(const char *name, interprocess_security_attributes* security)
{  return 0 != CreateDirectoryA(name, security);   }

static inline unsigned long get_temp_path(unsigned long length, char *buffer)
{  return GetTempPathA(length, buffer);   }

static inline int set_end_of_file(void *handle)
{  return 0 != SetEndOfFile(handle);   }

static inline bool set_file_pointer_ex(void *handle, __int64 distance, __int64 *new_file_pointer, unsigned long move_method)
{  return 0 != SetFilePointerEx(handle, distance, new_file_pointer, move_method);   }

static inline bool lock_file_ex(void *hnd, unsigned long flags, unsigned long reserved, unsigned long size_low, unsigned long size_high, interprocess_overlapped *overlapped)
{  return 0 != LockFileEx(hnd, flags, reserved, size_low, size_high, overlapped); }

static inline bool unlock_file_ex(void *hnd, unsigned long reserved, unsigned long size_low, unsigned long size_high, interprocess_overlapped *overlapped)
{  return 0 != UnlockFileEx(hnd, reserved, size_low, size_high, overlapped);  }

static inline long interlocked_increment(long volatile *addr)
{  return InterlockedIncrement(addr);  }

static inline long interlocked_decrement(long volatile *addr)
{  return InterlockedDecrement(addr);  }

static inline long interlocked_compare_exchange(long volatile *addr, long val1, long val2)
{  return InterlockedCompareExchange(addr, val1, val2);  }

static inline long interlocked_exchange_add(long volatile* addend, long value)
{  return InterlockedExchangeAdd((long*)addend, value);  }

static inline long interlocked_exchange(long volatile* addend, long value)
{  return InterlockedExchange((long*)addend, value);  }

}  //namespace winapi 
}  //namespace interprocess
}  //namespace boost 

#include <boost/interprocess/detail/config_end.hpp>

#endif //#ifdef BOOST_INTERPROCESS_WIN32_SYNC_PRIMITIVES_HPP