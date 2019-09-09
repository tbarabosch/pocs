# NetBSD-SA2019-001

This was joint-work with Maxime Villard. While investigating kernel memory disclosures in the NetBSD kernel, we came up with a method and subsequently a tool *KLEAK* to detect these disclosures generically.

KLEAK detected more than a dozen kernel memory disclosures in NetBSD until February 2019. The NetBSD project bundled all these issues in [NetBSD-SA2019-001](http://ftp.netbsd.org/pub/NetBSD/security/advisories/NetBSD-SA2019-001.txt.asc). 

## KLEAK
For information on KLEAK check out 

* [the paper](https://www.netbsd.org/gallery/presentations/maxv/kleak.pdf) 
* the presentation at [FOSDEM 2019](https://archive.fosdem.org/2019/schedule/event/kleak/)
* the [slides](https://papers.freebsd.org/2019/FOSDEM/barabosch-kleak.files/barabosch_kleak_fosdem_2019.pdf) for FOSDEM 2019
* the initial [source commit](https://freshbsd.org/commit/netbsd/src/2FElgv11KoHQEg2B)

## Kernel Stack Memory Disclosure: syscall ntp_gettime

This is a description of issue 1 as refered to in NetBSD-SA2019-001.

A memory disclosure in syscall ntp_gettime (448, sys/kern/kern_ntptime.c). The struct ntptimeval is allocated on the stack but never properly initialized. This causes a memory disclosure of 4 bytes of stack memory. An attacker could use these bytes to circumvent KASLR.

``` shell
localhost$ ./netbsd_gettime50
size of struct ntptimeval is 48 bytes.
localhost$ hexdump gettime50_dump.bin
0000000 71df 5bd7 0000 0000 7542 26ef 0000 0000
0000010 4a48 0000 0000 0000 0010 0000 0000 0000
0000020 0000 0000 0000 0000 0000 0000 4545 4545
0000030
```
-> the 45 bytes are leaked (use kern_ntptime.c.test_patch)

Even though I only tested the syscall ntp_gettime (448), I suppose that the compat syscalls ntp_gettime (393) and net_gettime (175) could be also used to disclose memory to userspace. However, the older struct versions are slightly different. 

 There is a demo program (netbsd_gettime50.c) and a patch to make the leak visible (kern_ntptime.c.test_patch).
