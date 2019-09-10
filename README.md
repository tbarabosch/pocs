# PoCs
This repository contains dumps of PoCs of security issues that I've reported. Some may have a proper write-up, some may have actual code, some may have just a binary that triggers a bug. Since the bugs should be fixed by now the PoCs should not do any harm. They should serve as examples for other (white-hat) hackers and folks that wish to study security bugs.

## List of Security Issues

* [FreeBSD: CVE-2018-6924](FreeBSD/CVE-2018-6924)
* [FreeBSD: CVE-2018-17155](FreeBSD/CVE-2018-17155)
* [NetBSD: NetBSD-SA2019-001](NetBSD/NetBSD-SA2019-001)
* [OpenBSD: CVE-2018-14775](OpenBSD/CVE-2018-14775)
* [OpenBSD: 6.3 errata 012](OpenBSD/errata_6.3_012)
* [VirtualBox: CVE-2018-3005](VirtualBox/CVE-2018-3005)

This repository does only contain PoCs for issues I consider most interesting. For instance, I reported **dozens** of (kernel) security bugs to BSD-based projects. [FreshBSD](https://freshbsd.org/search?q=Thomas+Barabosch&project%5B%5D=freebsd&project%5B%5D=netbsd&project%5B%5D=openbsd&sort=commit_date) lists all commits to FreeBSD, OpenBSD, and NetBSD that reference my name.

## A Word On Responsible Disclosure
I followed a responsible disclosure approach. Hence, most of the bugs should be fixed by now. Unfortunately, one organization stopped answering my mails, fixed several kernel memory disclosures on their repo's HEAD but did not backport them (i.e. leaving their users vulnerable), and did not file any CVE for bugs for which they should (according to their security advisory strategy).
