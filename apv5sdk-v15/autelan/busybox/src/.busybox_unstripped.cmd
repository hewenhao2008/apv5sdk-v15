cmd_busybox_unstripped := /home/zhangsiyu/pc018work-v15-at/apv5sdk-v15/autelan/busybox/src/scripts/trylink mips-linux-uclibc-gcc  -o busybox_unstripped -Wl,--warn-common -Wl,--sort-common -Wl,--gc-sections -Wl,--start-group  applets/built-in.o  archival/lib.a  archival/libipkg/lib.a  archival/libunarchive/lib.a  console-tools/lib.a  coreutils/lib.a  coreutils/libcoreutils/lib.a  debianutils/lib.a  e2fsprogs/lib.a  editors/lib.a  findutils/lib.a  init/lib.a  libbb/lib.a  libpwdgrp/lib.a  loginutils/lib.a  miscutils/lib.a  modutils/lib.a  networking/lib.a  networking/libiproute/lib.a  networking/udhcp/lib.a  procps/lib.a  runit/lib.a  shell/lib.a  sysklogd/lib.a  util-linux/lib.a  archival/built-in.o  archival/libipkg/built-in.o  archival/libunarchive/built-in.o  console-tools/built-in.o  coreutils/built-in.o  coreutils/libcoreutils/built-in.o  debianutils/built-in.o  e2fsprogs/built-in.o  editors/built-in.o  findutils/built-in.o  init/built-in.o  libbb/built-in.o  libpwdgrp/built-in.o  loginutils/built-in.o  miscutils/built-in.o  modutils/built-in.o  networking/built-in.o  networking/libiproute/built-in.o  networking/udhcp/built-in.o  procps/built-in.o  runit/built-in.o  shell/built-in.o  sysklogd/built-in.o  util-linux/built-in.o -Wl,--end-group