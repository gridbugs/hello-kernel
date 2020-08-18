# Hello Kernel

Small x64 kernel-mode program that boots with BOOTBOOT and prints "Hello, World!"
over serial. Depends on BOOTBOOT's `mkbootimg` (not the android tool!).
Get it from here: [gitlab.com/bztsrc/bootboot](https://gitlab.com/bztsrc/bootboot/)

## Linux
```
make run
```

## FreeBSD

```
LD=/usr/local/bin/ld gmake run
```
