/*
$info$
meta: LinuxSyscalls|syscalls-shared ~ Syscall implementations shared between x86 and x86-64
tags: LinuxSyscalls|syscalls-shared
$end_info$
*/

#include "Tests/LinuxSyscalls/Syscalls.h"
#include "Tests/LinuxSyscalls/x64/Syscalls.h"
#include "Tests/LinuxSyscalls/x32/Syscalls.h"

#include <FEXCore/IR/IR.h>

#include <stdint.h>
#include <sys/epoll.h>

namespace FEX::HLE {
  void RegisterEpoll() {
    using namespace FEXCore::IR;

    REGISTER_SYSCALL_IMPL_PASS_FLAGS(epoll_create, SyscallFlags::OPTIMIZETHROUGH | SyscallFlags::NOSYNCSTATEONENTRY,
      [](FEXCore::Core::CpuStateFrame *Frame, int size) -> uint64_t {
      uint64_t Result = epoll_create(size);
      SYSCALL_ERRNO();
    });

    REGISTER_SYSCALL_IMPL_PASS_FLAGS(epoll_create1, SyscallFlags::OPTIMIZETHROUGH | SyscallFlags::NOSYNCSTATEONENTRY,
      [](FEXCore::Core::CpuStateFrame *Frame, int flags) -> uint64_t {
      uint64_t Result = epoll_create1(flags);
      SYSCALL_ERRNO();
    });
  }
}
