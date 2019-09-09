# OpenBSD 6.3 errata 012

This issue is a DoS in OpenBSD 6.3 and 6.2. A regular user can trigger a kernel panic by executing a specially crafted ELF file. The vulnerable code is in the ELF parser of the syscall sys_execve. The issue was assigned [OpenBSD 6.3 errata 012](https://ftp.openbsd.org/pub/OpenBSD/patches/6.3/common/012_execsize.patch.sig).

## Description
I was stress testing the system call sys_execve (59) with invalid ELF
files. I utilized [my fork](https://github.com/tbarabosch/elf_fuzzer) of the ELF fuzzer Melkor_ELF_Fuzzer.

Within a couple of minutes I found an interesting bug that leads to a
kernel panic ("exec_process_vmcmds: RELATIVE no base"). This occurs in
"exec_process_vmcmds" in "sys/kern/exec_subr.c". The pointer base_vc is
NULL. Actually, there is a DIAGNOSTIC check that catches this case. I
can reproduce this bug on 6.3 amd64 and -CURRENT amd64. Unfortunately, I
cannot get a crash dump. Neither with ddb's boot crash nor boot dump.

Though I did not conduct an extensive fuzzing (with coverage), the
kernel seems to withstand a lot of the invalid ELF test cases. It
correctly bails on process creation. This should also be the behavior in
this case. I am not acquainted with the code flow from sysenter to this
bug. However, it seems that the parsing of the ELF header is already
done and the kernel is creating the new process space. So it probably
should bail out earlier.

I believe this is just a minor issue. It may be debatable whether or not
this is a security bug. However, I decided against directly mailing to
@bugs because this issue can be easily triggered by an unprivileged
user. This leads obviously to a local DoS. 

There is a test case that triggers this panic, which I've
shortened to 100 KB. The actual program does not matter, it is the
header that is broken.
