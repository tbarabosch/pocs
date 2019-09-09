# PoCs
This repository contains dumps of PoCs of security issues that I've reported. Some may have a proper write-up, some may have actual code, some may have just a binary that triggers a bug. Since the bugs should be fixed by now the PoCs should not do any harm. They should serve as examples for other (white-hat) hackers and folks that wish to study security bugs.

## List of Security Issues

* [FreeBSD: CVE-2018-17155](FreeBSD/CVE-2018-17155)

## A Word On Responsible Disclosure
I followed a responsible disclosure approach. Hence, most of the bugs should be fixed by now. Unfortunately, one organization stopped answering my mails, fixed several kernel memory disclosures on their repo's HEAD but did not backport them (i.e. leaving their users vulnerable), and did not file any CVE for bugs for which they should (according to their security advisory strategy).
