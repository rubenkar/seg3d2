/* pyconfig.h.in.  Generated from configure.in by autoheader.  */


#ifndef Py_PYCONFIG_H
#define Py_PYCONFIG_H


/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define for AIX if your compiler is a genuine IBM xlC/xlC_r and you want
   support for AIX C++ shared extension modules. */
/* #undef AIX_GENUINE_CPLUSPLUS */

/* Define if you have the Mach cthreads package */
/* #undef C_THREADS */

/* Define if C doubles are 64-bit IEEE 754 binary format, stored in ARM
   mixed-endian order (byte order 45670123) */
/* #undef DOUBLE_IS_ARM_MIXED_ENDIAN_IEEE754 */

/* Define if C doubles are 64-bit IEEE 754 binary format, stored with the most
   significant byte first */
#ifdef __BIG_ENDIAN__
#define DOUBLE_IS_BIG_ENDIAN_IEEE754 1
#endif

/* Define if C doubles are 64-bit IEEE 754 binary format, stored with the
   least significant byte first */
#ifdef __LITTLE_ENDIAN__
#define DOUBLE_IS_LITTLE_ENDIAN_IEEE754 1
#endif

/* Define if --enable-ipv6 is specified */
#cmakedefine ENABLE_IPV6 1

/* Define if flock needs to be linked with bsd library. */
/* #undef FLOCK_NEEDS_LIBBSD */

/* Define if getpgrp() must be called as getpgrp(0). */
#cmakedefine GETPGRP_HAVE_ARG 1

/* Define if gettimeofday() does not have second (timezone) argument This is
   the case on Motorola V4 (R40V4.2) */
/* #undef GETTIMEOFDAY_NO_TZ */

/* Define to 1 if you have the `accept4' function. */
/* #undef HAVE_ACCEPT4 */

/* Define to 1 if you have the `acosh' function. */
#cmakedefine HAVE_ACOSH 1

/* struct addrinfo (netdb.h) */
#cmakedefine HAVE_ADDRINFO 1

/* Define to 1 if you have the `alarm' function. */
#cmakedefine HAVE_ALARM 1

/* Define this if your time.h defines altzone. */
#cmakedefine HAVE_ALTZONE 1

/* Define to 1 if you have the `asinh' function. */
#cmakedefine HAVE_ASINH 1

/* Define to 1 if you have the <asm/types.h> header file. */
#cmakedefine HAVE_ASM_TYPES_H 1

/* Define to 1 if you have the `atanh' function. */
#cmakedefine HAVE_ATANH 1

/* Define if GCC supports __attribute__((format(PyArg_ParseTuple, 2, 3))) */
#cmakedefine HAVE_ATTRIBUTE_FORMAT_PARSETUPLE 1

/* Define to 1 if you have the `bind_textdomain_codeset' function. */
#cmakedefine HAVE_BIND_TEXTDOMAIN_CODESET 1

/* Define to 1 if you have the <bluetooth/bluetooth.h> header file. */
#cmakedefine HAVE_BLUETOOTH_BLUETOOTH_H 1

/* Define to 1 if you have the <bluetooth.h> header file. */
#cmakedefine HAVE_BLUETOOTH_H 1

/* Define if mbstowcs(NULL, "text", 0) does not return the number of wide
   chars that would be converted. */
/* #undef HAVE_BROKEN_MBSTOWCS */

/* Define if nice() returns success/failure instead of the new priority. */
#cmakedefine HAVE_BROKEN_NICE 1

/* Define if the system reports an invalid PIPE_BUF value. */
/* #undef HAVE_BROKEN_PIPE_BUF */

/* Define if poll() sets errno on invalid file descriptors. */
#cmakedefine HAVE_BROKEN_POLL 1

/* Define if the Posix semaphores do not work on your system */
/* #undef HAVE_BROKEN_POSIX_SEMAPHORES */

/* Define if pthread_sigmask() does not work on your system. */
/* #undef HAVE_BROKEN_PTHREAD_SIGMASK */

/* define to 1 if your sem_getvalue is broken. */
#define HAVE_BROKEN_SEM_GETVALUE 1

/* Define this if you have the type _Bool. */
#cmakedefine HAVE_C99_BOOL 1

/* Define to 1 if you have the `chflags' function. */
#cmakedefine HAVE_CHFLAGS 1

/* Define to 1 if you have the `chown' function. */
#cmakedefine HAVE_CHOWN 1

/* Define if you have the 'chroot' function. */
#cmakedefine HAVE_CHROOT 1

/* Define to 1 if you have the `clock' function. */
#cmakedefine HAVE_CLOCK 1

/* Define if the C compiler supports computed gotos. */
#cmakedefine HAVE_COMPUTED_GOTOS 1

/* Define to 1 if you have the `confstr' function. */
#cmakedefine HAVE_CONFSTR 1

/* Define to 1 if you have the <conio.h> header file. */
#cmakedefine HAVE_CONIO_H 1

/* Define to 1 if you have the `copysign' function. */
#cmakedefine HAVE_COPYSIGN 1

/* Define to 1 if you have the `ctermid' function. */
#cmakedefine HAVE_CTERMID 1

/* Define if you have the 'ctermid_r' function. */
#cmakedefine HAVE_CTERMID_R 1

/* Define to 1 if you have the <curses.h> header file. */
#cmakedefine HAVE_CURSES_H 1

/* Define if you have the 'is_term_resized' function. */
#cmakedefine HAVE_CURSES_IS_TERM_RESIZED 1

/* Define if you have the 'resizeterm' function. */
#cmakedefine HAVE_CURSES_RESIZETERM 1

/* Define if you have the 'resize_term' function. */
#cmakedefine HAVE_CURSES_RESIZE_TERM 1

/* Define to 1 if you have the declaration of `isfinite', and to 0 if you
   don't. */
#define HAVE_DECL_ISFINITE 1

/* Define to 1 if you have the declaration of `isinf', and to 0 if you don't.
   */
#define HAVE_DECL_ISINF 1

/* Define to 1 if you have the declaration of `isnan', and to 0 if you don't.
   */
#define HAVE_DECL_ISNAN 1

/* Define to 1 if you have the declaration of `tzname', and to 0 if you don't.
   */
/* #undef HAVE_DECL_TZNAME */

/* Define to 1 if you have the device macros. */
#cmakedefine HAVE_DEVICE_MACROS 1

/* Define if we have /dev/ptc. */
#cmakedefine HAVE_DEV_PTC 1

/* Define if we have /dev/ptmx. */
#cmakedefine HAVE_DEV_PTMX 1

/* Define to 1 if you have the <direct.h> header file. */
#cmakedefine HAVE_DIRECT_H 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#cmakedefine HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#cmakedefine HAVE_DLFCN_H 1

/* Define to 1 if you have the `dlopen' function. */
#cmakedefine HAVE_DLOPEN 1

/* Define to 1 if you have the `dup2' function. */
#cmakedefine HAVE_DUP2 1

/* Defined when any dynamic module loading is enabled. */
#undef HAVE_DYNAMIC_LOADING

/* Define if you have the 'epoll' functions. */
#cmakedefine HAVE_EPOLL 1

/* Define to 1 if you have the `erf' function. */
#cmakedefine HAVE_ERF 1

/* Define to 1 if you have the `erfc' function. */
#cmakedefine HAVE_ERFC 1

/* Define to 1 if you have the <errno.h> header file. */
#cmakedefine HAVE_ERRNO_H 1

/* Define to 1 if you have the `execv' function. */
#cmakedefine HAVE_EXECV 1

/* Define to 1 if you have the `expm1' function. */
#cmakedefine HAVE_EXPM1 1

/* Define if you have the 'fchdir' function. */
#cmakedefine HAVE_FCHDIR 1

/* Define to 1 if you have the `fchmod' function. */
#cmakedefine HAVE_FCHMOD 1

/* Define to 1 if you have the `fchown' function. */
#cmakedefine HAVE_FCHOWN 1

/* Define to 1 if you have the <fcntl.h> header file. */
#cmakedefine HAVE_FCNTL_H 1

/* Define if you have the 'fdatasync' function. */
#cmakedefine HAVE_FDATASYNC

/* Define to 1 if you have the `finite' function. */
#cmakedefine HAVE_FINITE 1

/* Define to 1 if you have the `flock' function. */
#cmakedefine HAVE_FLOCK 1

/* Define to 1 if you have the `fork' function. */
#cmakedefine HAVE_FORK 1

/* Define to 1 if you have the `forkpty' function. */
#cmakedefine HAVE_FORKPTY 1

/* Define to 1 if you have the `fpathconf' function. */
#cmakedefine HAVE_FPATHCONF 1

/* Define to 1 if you have the `fseek64' function. */
#cmakedefine HAVE_FSEEK64 1

/* Define to 1 if you have the `fseeko' function. */
#cmakedefine HAVE_FSEEKO 1

/* Define to 1 if you have the `fstatvfs' function. */
#cmakedefine HAVE_FSTATVFS 1

/* Define if you have the 'fsync' function. */
#cmakedefine HAVE_FSYNC 1

/* Define to 1 if you have the `ftell64' function. */
#cmakedefine HAVE_FTELL64 1

/* Define to 1 if you have the `ftello' function. */
#cmakedefine HAVE_FTELLO 1

/* Define to 1 if you have the `ftime' function. */
#cmakedefine HAVE_FTIME 1

/* Define to 1 if you have the `ftruncate' function. */
#cmakedefine HAVE_FTRUNCATE 1

/* Define to 1 if you have the `gai_strerror' function. */
#cmakedefine HAVE_GAI_STRERROR 1

/* Define to 1 if you have the `gamma' function. */
#cmakedefine HAVE_GAMMA 1

/* Define if we can use gcc inline assembler to get and set x87 control word
   */
#cmakedefine HAVE_GCC_ASM_FOR_X87 1

/* Define if you have the getaddrinfo function. */
#cmakedefine HAVE_GETADDRINFO 1

/* Define to 1 if you have the `getcwd' function. */
#cmakedefine HAVE_GETCWD 1

/* Define this if you have flockfile(), getc_unlocked(), and funlockfile() */
#cmakedefine HAVE_GETC_UNLOCKED 1

/* Define to 1 if you have the `getgroups' function. */
#cmakedefine HAVE_GETGROUPS 1

/* Define to 1 if you have the `gethostbyname' function. */
#cmakedefine HAVE_GETHOSTBYNAME 1

/* Define this if you have some version of gethostbyname_r() */
#cmakedefine HAVE_GETHOSTBYNAME_R 1

/* Define this if you have the 3-arg version of gethostbyname_r(). */
#cmakedefine HAVE_GETHOSTBYNAME_R_3_ARG 1

/* Define this if you have the 5-arg version of gethostbyname_r(). */
#cmakedefine HAVE_GETHOSTBYNAME_R_5_ARG 1

/* Define this if you have the 6-arg version of gethostbyname_r(). */
#cmakedefine HAVE_GETHOSTBYNAME_R_6_ARG 1

/* Define to 1 if you have the `getitimer' function. */
#cmakedefine HAVE_GETITIMER 1

/* Define to 1 if you have the `getloadavg' function. */
#cmakedefine HAVE_GETLOADAVG 1

/* Define to 1 if you have the `getlogin' function. */
#cmakedefine HAVE_GETLOGIN 1

/* Define to 1 if you have the `getnameinfo' function. */
#cmakedefine HAVE_GETNAMEINFO 1

/* Define if you have the 'getpagesize' function. */
#cmakedefine HAVE_GETPAGESIZE 1

/* Define to 1 if you have the `getpeername' function. */
#cmakedefine HAVE_GETPEERNAME 1

/* Define to 1 if you have the `getpgid' function. */
#cmakedefine HAVE_GETPGID 1

/* Define to 1 if you have the `getpgrp' function. */
#cmakedefine HAVE_GETPGRP 1

/* Define to 1 if you have the `getpid' function. */
#cmakedefine HAVE_GETPID 1

/* Define to 1 if you have the `getpriority' function. */
#cmakedefine HAVE_GETPRIORITY 1

/* Define to 1 if you have the `getpwent' function. */
#cmakedefine HAVE_GETPWENT 1

/* Define to 1 if you have the `getresgid' function. */
#cmakedefine HAVE_GETRESGID 1

/* Define to 1 if you have the `getresuid' function. */
#cmakedefine HAVE_GETRESUID 1

/* Define to 1 if you have the `getsid' function. */
#cmakedefine HAVE_GETSID 1

/* Define to 1 if you have the `getspent' function. */
#cmakedefine HAVE_GETSPENT 1

/* Define to 1 if you have the `getspnam' function. */
#cmakedefine HAVE_GETSPNAM 1

/* Define to 1 if you have the `gettimeofday' function. */
#cmakedefine HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the `getwd' function. */
#cmakedefine HAVE_GETWD 1

/* Define to 1 if you have the <grp.h> header file. */
#cmakedefine HAVE_GRP_H 1

/* Define if you have the 'hstrerror' function. */
#cmakedefine HAVE_HSTRERROR 1

/* Define to 1 if you have the `hypot' function. */
#cmakedefine HAVE_HYPOT 1

/* Define to 1 if you have the <ieeefp.h> header file. */
#cmakedefine HAVE_IEEEFP_H 1

/* Define if you have the 'inet_aton' function. */
#cmakedefine HAVE_INET_ATON 1

/* Define if you have the 'inet_pton' function. */
#cmakedefine HAVE_INET_PTON 1

/* Define to 1 if you have the `initgroups' function. */
#cmakedefine HAVE_INITGROUPS 1

/* Define to 1 if you have the <inttypes.h> header file. */
#cmakedefine HAVE_INTTYPES_H 1

/* Define to 1 if you have the <io.h> header file. */
#cmakedefine HAVE_IO_H 1

/* Define to 1 if you have the `kill' function. */
#cmakedefine HAVE_KILL 1

/* Define to 1 if you have the `killpg' function. */
#cmakedefine HAVE_KILLPG 1

/* Define if you have the 'kqueue' functions. */
#cmakedefine HAVE_KQUEUE 1

/* Define to 1 if you have the <langinfo.h> header file. */
#cmakedefine HAVE_LANGINFO_H 1

/* Defined to enable large file support when an off_t is bigger than a long
   and long long is available and at least as big as an off_t. You may need to
   add some flags for configuration and compilation to enable this mode. (For
   Solaris and Linux, the necessary defines are already defined.) */
/* #undef HAVE_LARGEFILE_SUPPORT */

/* Define to 1 if you have the `lchflags' function. */
#cmakedefine HAVE_LCHFLAGS 1

/* Define to 1 if you have the `lchmod' function. */
#cmakedefine HAVE_LCHMOD 1

/* Define to 1 if you have the `lchown' function. */
#cmakedefine HAVE_LCHOWN 1

/* Define to 1 if you have the `lgamma' function. */
#cmakedefine HAVE_LGAMMA 1

/* Define to 1 if you have the `dl' library (-ldl). */
#cmakedefine HAVE_LIBDL 1

/* Define to 1 if you have the `dld' library (-ldld). */
#cmakedefine HAVE_LIBDLD 1

/* Define to 1 if you have the `ieee' library (-lieee). */
#cmakedefine HAVE_LIBIEEE 1

/* Define to 1 if you have the <libintl.h> header file. */
#cmakedefine HAVE_LIBINTL_H 1

/* Define if you have the readline library (-lreadline). */
#cmakedefine HAVE_LIBREADLINE 1

/* Define to 1 if you have the `resolv' library (-lresolv). */
#cmakedefine HAVE_LIBRESOLV 1

/* Define to 1 if you have the <libutil.h> header file. */
#cmakedefine HAVE_LIBUTIL_H 1

/* Define if you have the 'link' function. */
#cmakedefine HAVE_LINK 1

/* Define to 1 if you have the <linux/netlink.h> header file. */
#cmakedefine HAVE_LINUX_NETLINK_H 1

/* Define to 1 if you have the <linux/tipc.h> header file. */
#cmakedefine HAVE_LINUX_TIPC_H 1

/* Define to 1 if you have the `log1p' function. */
#cmakedefine HAVE_LOG1P 1

/* Define this if you have the type long double. */
#cmakedefine HAVE_LONG_DOUBLE 1

/* Define this if you have the type long long. */
#cmakedefine HAVE_LONG_LONG 1

/* Define to 1 if you have the `lstat' function. */
#cmakedefine HAVE_LSTAT 1

/* Define this if you have the makedev macro. */
#cmakedefine HAVE_MAKEDEV 1

/* Define to 1 if you have the `mbrtowc' function. */
#cmakedefine HAVE_MBRTOWC 1

/* Define to 1 if you have the `memmove' function. */
#cmakedefine HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#cmakedefine HAVE_MEMORY_H 1

/* Define to 1 if you have the `mkfifo' function. */
#cmakedefine HAVE_MKFIFO 1

/* Define to 1 if you have the `mknod' function. */
#cmakedefine HAVE_MKNOD 1

/* Define to 1 if you have the `mktime' function. */
#cmakedefine HAVE_MKTIME 1

/* Define to 1 if you have the `mremap' function. */
/* #undef HAVE_MREMAP */

/* Define to 1 if you have the <ncurses.h> header file. */
#cmakedefine HAVE_NCURSES_H 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
#cmakedefine HAVE_NDIR_H 1

/* Define to 1 if you have the <netpacket/packet.h> header file. */
#cmakedefine HAVE_NETPACKET_PACKET_H 1

/* Define to 1 if you have the `nice' function. */
#cmakedefine HAVE_NICE 1

/* Define to 1 if you have the `openpty' function. */
#cmakedefine HAVE_OPENPTY 1

/* Define if compiling using MacOS X 10.5 SDK or later. */
#define HAVE_OSX105_SDK 1

/* Define to 1 if you have the `pathconf' function. */
#cmakedefine HAVE_PATHCONF 1

/* Define to 1 if you have the `pause' function. */
#cmakedefine HAVE_PAUSE 1

/* Define if the OS supports pipe2() */
#cmakedefine HAVE_PIPE2 1

/* Define to 1 if you have the `plock' function. */
#cmakedefine HAVE_PLOCK 1

/* Define to 1 if you have the `poll' function. */
#cmakedefine HAVE_POLL 1

/* Define to 1 if you have the <poll.h> header file. */
#cmakedefine HAVE_POLL_H 1

/* Define to 1 if you have the <process.h> header file. */
#cmakedefine HAVE_PROCESS_H 1

/* Define if your compiler supports function prototype */
#cmakedefine HAVE_PROTOTYPES 1

/* Defined for Solaris 2.6 bug in pthread header. */
/* #undef HAVE_PTHREAD_DESTRUCTOR */

/* Define to 1 if you have the <pthread.h> header file. */
#cmakedefine HAVE_PTHREAD_H 1

/* Define to 1 if you have the `pthread_init' function. */
#cmakedefine HAVE_PTHREAD_INIT 1

/* Define to 1 if you have the `pthread_sigmask' function. */
#cmakedefine HAVE_PTHREAD_SIGMASK 1

/* Define to 1 if you have the <pty.h> header file. */
#cmakedefine HAVE_PTY_H 1

/* Define to 1 if you have the `putenv' function. */
#cmakedefine HAVE_PUTENV 1

/* Define to 1 if you have the `readlink' function. */
#cmakedefine HAVE_READLINK 1

/* Define to 1 if you have the `realpath' function. */
#cmakedefine HAVE_REALPATH 1

/* Define if you have readline 2.1 */
#cmakedefine HAVE_RL_CALLBACK 1

/* Define if you can turn off readline's signal handling. */
#cmakedefine HAVE_RL_CATCH_SIGNAL 1

/* Define if you have readline 2.2 */
#cmakedefine HAVE_RL_COMPLETION_APPEND_CHARACTER 1

/* Define if you have readline 4.0 */
#cmakedefine HAVE_RL_COMPLETION_DISPLAY_MATCHES_HOOK 1

/* Define if you have readline 4.2 */
#cmakedefine HAVE_RL_COMPLETION_MATCHES 1

/* Define if you have rl_completion_suppress_append */
#cmakedefine HAVE_RL_COMPLETION_SUPPRESS_APPEND 1

/* Define if you have readline 4.0 */
#cmakedefine HAVE_RL_PRE_INPUT_HOOK 1

/* Define to 1 if you have the `round' function. */
#cmakedefine HAVE_ROUND 1

/* Define to 1 if you have the `select' function. */
#cmakedefine HAVE_SELECT 1

/* Define to 1 if you have the `sem_getvalue' function. */
#cmakedefine HAVE_SEM_GETVALUE 1

/* Define to 1 if you have the `sem_open' function. */
#cmakedefine HAVE_SEM_OPEN 1

/* Define to 1 if you have the `sem_timedwait' function. */
#cmakedefine HAVE_SEM_TIMEDWAIT 1

/* Define to 1 if you have the `sem_unlink' function. */
#cmakedefine HAVE_SEM_UNLINK 1

/* Define to 1 if you have the `setegid' function. */
#cmakedefine HAVE_SETEGID 1

/* Define to 1 if you have the `seteuid' function. */
#cmakedefine HAVE_SETEUID 1

/* Define to 1 if you have the `setgid' function. */
#cmakedefine HAVE_SETGID 1

/* Define if you have the 'setgroups' function. */
#cmakedefine HAVE_SETGROUPS 1

/* Define to 1 if you have the `setitimer' function. */
#cmakedefine HAVE_SETITIMER 1

/* Define to 1 if you have the `setlocale' function. */
#cmakedefine HAVE_SETLOCALE 1

/* Define to 1 if you have the `setpgid' function. */
#cmakedefine HAVE_SETPGID 1

/* Define to 1 if you have the `setpgrp' function. */
#cmakedefine HAVE_SETPGRP 1

/* Define to 1 if you have the `setregid' function. */
#cmakedefine HAVE_SETREGID 1

/* Define to 1 if you have the `setresgid' function. */
#cmakedefine HAVE_SETRESGID 1

/* Define to 1 if you have the `setresuid' function. */
#cmakedefine HAVE_SETRESUID 1

/* Define to 1 if you have the `setreuid' function. */
#cmakedefine HAVE_SETREUID 1

/* Define to 1 if you have the `setsid' function. */
#cmakedefine HAVE_SETSID 1

/* Define to 1 if you have the `setuid' function. */
#cmakedefine HAVE_SETUID 1

/* Define to 1 if you have the `setvbuf' function. */
#cmakedefine HAVE_SETVBUF 1

/* Define to 1 if you have the <shadow.h> header file. */
#cmakedefine HAVE_SHADOW_H 1

/* Define to 1 if you have the `sigaction' function. */
#cmakedefine HAVE_SIGACTION 1

/* Define to 1 if you have the `siginterrupt' function. */
#cmakedefine HAVE_SIGINTERRUPT 1

/* Define to 1 if you have the <signal.h> header file. */
#cmakedefine HAVE_SIGNAL_H 1

/* Define to 1 if you have the `sigrelse' function. */
#cmakedefine HAVE_SIGRELSE 1

/* Define to 1 if you have the `snprintf' function. */
#cmakedefine HAVE_SNPRINTF 1

/* Define if sockaddr has sa_len member */
#cmakedefine HAVE_SOCKADDR_SA_LEN 1

/* struct sockaddr_storage (sys/socket.h) */
#cmakedefine HAVE_SOCKADDR_STORAGE 1

/* Define if you have the 'socketpair' function. */
#cmakedefine HAVE_SOCKETPAIR 1

/* Define to 1 if you have the <spawn.h> header file. */
#cmakedefine HAVE_SPAWN_H 1

/* Define if your compiler provides ssize_t */
#cmakedefine HAVE_SSIZE_T 1

/* Define to 1 if you have the `statvfs' function. */
#cmakedefine HAVE_STATVFS 1

/* Define if you have struct stat.st_mtim.tv_nsec */
#cmakedefine HAVE_STAT_TV_NSEC 1

/* Define if you have struct stat.st_mtimensec */
#cmakedefine HAVE_STAT_TV_NSEC2 1

/* Define if your compiler supports variable length function prototypes (e.g.
   void fprintf(FILE *, char *, ...);) *and* <stdarg.h> */
#define HAVE_STDARG_PROTOTYPES 1

/* Define to 1 if you have the <stdint.h> header file. */
#cmakedefine HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#cmakedefine HAVE_STDLIB_H 1

/* Define to 1 if you have the `strdup' function. */
#cmakedefine HAVE_STRDUP 1

/* Define to 1 if you have the `strftime' function. */
#cmakedefine HAVE_STRFTIME 1

/* Define to 1 if you have the <strings.h> header file. */
#cmakedefine HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#cmakedefine HAVE_STRING_H 1

/* Define to 1 if you have the `strlcpy' function. */
#cmakedefine HAVE_STRLCPY 1

/* Define to 1 if you have the <stropts.h> header file. */
#cmakedefine HAVE_STROPTS_H 1

/* Define to 1 if `st_birthtime' is a member of `struct stat'. */
#cmakedefine HAVE_STRUCT_STAT_ST_BIRTHTIME 1

/* Define to 1 if `st_blksize' is a member of `struct stat'. */
#cmakedefine HAVE_STRUCT_STAT_ST_BLKSIZE 1

/* Define to 1 if `st_blocks' is a member of `struct stat'. */
#cmakedefine HAVE_STRUCT_STAT_ST_BLOCKS 1

/* Define to 1 if `st_flags' is a member of `struct stat'. */
#cmakedefine HAVE_STRUCT_STAT_ST_FLAGS 1

/* Define to 1 if `st_gen' is a member of `struct stat'. */
#cmakedefine HAVE_STRUCT_STAT_ST_GEN 1

/* Define to 1 if `st_rdev' is a member of `struct stat'. */
#cmakedefine HAVE_STRUCT_STAT_ST_RDEV 1

/* Define to 1 if `tm_zone' is a member of `struct tm'. */
#cmakedefine HAVE_STRUCT_TM_TM_ZONE 1

/* Define to 1 if your `struct stat' has `st_blocks'. Deprecated, use
   `HAVE_STRUCT_STAT_ST_BLOCKS' instead. */
#cmakedefine HAVE_ST_BLOCKS 1

/* Define if you have the 'symlink' function. */
#cmakedefine HAVE_SYMLINK 1

/* Define to 1 if you have the `sysconf' function. */
#cmakedefine HAVE_SYSCONF 1

/* Define to 1 if you have the <sysexits.h> header file. */
#cmakedefine HAVE_SYSEXITS_H 1

/* Define to 1 if you have the <sys/audioio.h> header file. */
#cmakedefine HAVE_SYS_AUDIOIO_H 1

/* Define to 1 if you have the <sys/bsdtty.h> header file. */
#cmakedefine HAVE_SYS_BSDTTY_H 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
#cmakedefine HAVE_SYS_DIR_H 1

/* Define to 1 if you have the <sys/epoll.h> header file. */
#cmakedefine HAVE_SYS_EPOLL_H 1

/* Define to 1 if you have the <sys/event.h> header file. */
#cmakedefine HAVE_SYS_EVENT_H 1

/* Define to 1 if you have the <sys/file.h> header file. */
#cmakedefine HAVE_SYS_FILE_H 1

/* Define to 1 if you have the <sys/loadavg.h> header file. */
#cmakedefine HAVE_SYS_LOADAVG_H 1

/* Define to 1 if you have the <sys/lock.h> header file. */
#cmakedefine HAVE_SYS_LOCK_H 1

/* Define to 1 if you have the <sys/mkdev.h> header file. */
#cmakedefine HAVE_SYS_MKDEV_H 1

/* Define to 1 if you have the <sys/modem.h> header file. */
#cmakedefine HAVE_SYS_MODEM_H 1

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
#cmakedefine HAVE_SYS_NDIR_H 1

/* Define to 1 if you have the <sys/param.h> header file. */
#cmakedefine HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/poll.h> header file. */
#cmakedefine HAVE_SYS_POLL_H 1

/* Define to 1 if you have the <sys/resource.h> header file. */
#cmakedefine HAVE_SYS_RESOURCE_H 1

/* Define to 1 if you have the <sys/select.h> header file. */
#cmakedefine HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#cmakedefine HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/statvfs.h> header file. */
#cmakedefine HAVE_SYS_STATVFS_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#cmakedefine HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/termio.h> header file. */
#cmakedefine HAVE_SYS_TERMIO_H 1

/* Define to 1 if you have the <sys/times.h> header file. */
#cmakedefine HAVE_SYS_TIMES_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#cmakedefine HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#cmakedefine HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/un.h> header file. */
#cmakedefine HAVE_SYS_UN_H 1

/* Define to 1 if you have the <sys/utsname.h> header file. */
#cmakedefine HAVE_SYS_UTSNAME_H 1

/* Define to 1 if you have the <sys/wait.h> header file. */
#cmakedefine HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the `tcgetpgrp' function. */
#cmakedefine HAVE_TCGETPGRP 1

/* Define to 1 if you have the `tcsetpgrp' function. */
#cmakedefine HAVE_TCSETPGRP 1

/* Define to 1 if you have the `tempnam' function. */
#cmakedefine HAVE_TEMPNAM 1

/* Define to 1 if you have the <termios.h> header file. */
#cmakedefine HAVE_TERMIOS_H 1

/* Define to 1 if you have the <term.h> header file. */
#cmakedefine HAVE_TERM_H 1

/* Define to 1 if you have the `tgamma' function. */
#cmakedefine HAVE_TGAMMA 1

/* Define to 1 if you have the <thread.h> header file. */
#cmakedefine HAVE_THREAD_H 1

/* Define to 1 if you have the `timegm' function. */
#cmakedefine HAVE_TIMEGM 1

/* Define to 1 if you have the `times' function. */
#cmakedefine HAVE_TIMES 1

/* Define to 1 if you have the `tmpfile' function. */
#cmakedefine HAVE_TMPFILE 1

/* Define to 1 if you have the `tmpnam' function. */
#cmakedefine HAVE_TMPNAM 1

/* Define to 1 if you have the `tmpnam_r' function. */
#cmakedefine HAVE_TMPNAM_R 1

/* Define to 1 if your `struct tm' has `tm_zone'. Deprecated, use
   `HAVE_STRUCT_TM_TM_ZONE' instead. */
#cmakedefine HAVE_TM_ZONE 1

/* Define to 1 if you have the `truncate' function. */
#cmakedefine HAVE_TRUNCATE 1

/* Define to 1 if you don't have `tm_zone' but do have the external array
   `tzname'. */
#cmakedefine HAVE_TZNAME 1

/* Define this if you have tcl and TCL_UTF_MAX==6 */
/* #undef HAVE_UCS4_TCL */

/* Define to 1 if the system has the type `uintptr_t'. */
#cmakedefine HAVE_UINTPTR_T 1

/* Define to 1 if you have the `uname' function. */
#cmakedefine HAVE_UNAME 1

/* Define to 1 if you have the <unistd.h> header file. */
#cmakedefine HAVE_UNISTD_H 1

/* Define to 1 if you have the `unsetenv' function. */
#cmakedefine HAVE_UNSETENV 1

/* Define if you have a useable wchar_t type defined in wchar.h; useable means
   wchar_t must be an unsigned type with at least 16 bits. (see
   Include/unicodeobject.h). */
#cmakedefine HAVE_USABLE_WCHAR_T 1

/* Define to 1 if you have the <util.h> header file. */
#cmakedefine HAVE_UTIL_H 1

/* Define to 1 if you have the `utimes' function. */
#cmakedefine HAVE_UTIMES 1

/* Define to 1 if you have the <utime.h> header file. */
#cmakedefine HAVE_UTIME_H 1

/* Define to 1 if you have the `wait3' function. */
#cmakedefine HAVE_WAIT3 1

/* Define to 1 if you have the `wait4' function. */
#cmakedefine HAVE_WAIT4 1

/* Define to 1 if you have the `waitpid' function. */
#cmakedefine HAVE_WAITPID 1

/* Define if the compiler provides a wchar.h header file. */
#cmakedefine HAVE_WCHAR_H 1

/* Define to 1 if you have the `wcscoll' function. */
#cmakedefine HAVE_WCSCOLL 1

/* Define to 1 if you have the `wcsftime' function. */
#cmakedefine HAVE_WCSFTIME 1

/* Define to 1 if you have the `wcsxfrm' function. */
#cmakedefine HAVE_WCSXFRM 1

/* Define if tzset() actually switches the local timezone in a meaningful way.
   */
#cmakedefine HAVE_WORKING_TZSET 1

/* Define if the zlib library has inflateCopy */
#cmakedefine HAVE_ZLIB_COPY 1

/* Define to 1 if you have the `_getpty' function. */
#cmakedefine HAVE__GETPTY 1

/* Define if you are using Mach cthreads directly under /include */
/* #undef HURD_C_THREADS */

/* Define if log1p(-0.) is 0. rather than -0. */
/* #undef LOG1P_DROPS_ZERO_SIGN */

/* Define if you are using Mach cthreads under mach / */
/* #undef MACH_C_THREADS */

/* Define to 1 if `major', `minor', and `makedev' are declared in <mkdev.h>.
   */
/* #undef MAJOR_IN_MKDEV */

/* Define to 1 if `major', `minor', and `makedev' are declared in
   <sysmacros.h>. */
/* #undef MAJOR_IN_SYSMACROS */

/* Define if mvwdelch in curses.h is an expression. */
#cmakedefine MVWDELCH_IS_EXPRESSION 1

/* Define to the address where bug reports for this package should be sent. */
/* #undef PACKAGE_BUGREPORT */

/* Define to the full name of this package. */
/* #undef PACKAGE_NAME */

/* Define to the full name and version of this package. */
/* #undef PACKAGE_STRING */

/* Define to the one symbol short name of this package. */
/* #undef PACKAGE_TARNAME */

/* Define to the home page for this package. */
/* #undef PACKAGE_URL */

/* Define to the version of this package. */
/* #undef PACKAGE_VERSION */

/* Define if POSIX semaphores aren't enabled on your system */
/* #undef POSIX_SEMAPHORES_NOT_ENABLED */

/* Defined if PTHREAD_SCOPE_SYSTEM supported. */
#cmakedefine PTHREAD_SYSTEM_SCHED_SUPPORTED 1

/* Define as the preferred size in bits of long digits */
/* #undef PYLONG_BITS_IN_DIGIT */

/* Define to printf format modifier for long long type */
#define PY_FORMAT_LONG_LONG "ll"

/* Define to printf format modifier for Py_ssize_t */
#define PY_FORMAT_SIZE_T "z"

/* Define as the integral type used for Unicode representation. */
#define PY_UNICODE_TYPE unsigned short

/* Define if you want to build an interpreter with many run-time checks. */
/* #undef Py_DEBUG */

/* Defined if Python is built as a shared library. */
/* #undef Py_ENABLE_SHARED */

/* Define as the size of the unicode type. */
#define Py_UNICODE_SIZE 2

/* assume C89 semantics that RETSIGTYPE is always void */
#define RETSIGTYPE void

/* Define if setpgrp() must be called as setpgrp(0, 0). */
#cmakedefine SETPGRP_HAVE_ARG 

/* Define this to be extension of shared libraries (including the dot!). */
#define SHLIB_EXT "@CMAKE_SHARED_LIBRARY_SUFFIX@"

/* Define if i>>j for signed int i does not extend the sign bit when i < 0 */
/* #undef SIGNED_RIGHT_SHIFT_ZERO_FILLS */

/* The size of `double', as computed by sizeof. */
#cmakedefine SIZEOF_DOUBLE @SIZEOF_DOUBLE@

/* The size of `float', as computed by sizeof. */
#cmakedefine SIZEOF_FLOAT @SIZEOF_FLOAT@

/* The size of `fpos_t', as computed by sizeof. */
#cmakedefine SIZEOF_FPOS_T @SIZEOF_FPOS_T@

/* The size of `int', as computed by sizeof. */
#cmakedefine SIZEOF_INT @SIZEOF_INT@

/* The size of `long', as computed by sizeof. */
#cmakedefine SIZEOF_LONG @SIZEOF_LONG@

/* The size of `long double', as computed by sizeof. */
#cmakedefine SIZEOF_LONG_DOUBLE @SIZEOF_LONG_DOUBLE@

/* The size of `long long', as computed by sizeof. */
#cmakedefine SIZEOF_LONG_LONG @SIZEOF_LONG_LONG@

/* The size of `off_t', as computed by sizeof. */
#cmakedefine SIZEOF_OFF_T @SIZEOF_OFF_T@

/* The size of `pid_t', as computed by sizeof. */
#cmakedefine SIZEOF_PID_T @SIZEOF_PID_T@

/* The size of `pthread_t', as computed by sizeof. */
#cmakedefine SIZEOF_PTHREAD_T @SIZEOF_PTHREAD_T@

/* The size of `short', as computed by sizeof. */
#cmakedefine SIZEOF_SHORT @SIZEOF_SHORT@

/* The size of `size_t', as computed by sizeof. */
#cmakedefine SIZEOF_SIZE_T @SIZEOF_SIZE_T@

/* The size of `time_t', as computed by sizeof. */
#cmakedefine SIZEOF_TIME_T @SIZEOF_TIME_T@

/* The size of `uintptr_t', as computed by sizeof. */
#cmakedefine SIZEOF_UINTPTR_T @SIZEOF_UINTPTR_T@

/* The size of `void *', as computed by sizeof. */
#cmakedefine SIZEOF_VOID_P @SIZEOF_VOID_P@

/* The size of `wchar_t', as computed by sizeof. */
#cmakedefine SIZEOF_WCHAR_T @SIZEOF_WCHAR_T@

/* The size of `_Bool', as computed by sizeof. */
#cmakedefine SIZEOF__BOOL @SIZEOF__BOOL@

/* Define to 1 if you have the ANSI C header files. */
#cmakedefine STDC_HEADERS 1

/* Define if you can safely include both <sys/select.h> and <sys/time.h>
   (which you can't on SCO ODT 3.0). */
#cmakedefine SYS_SELECT_WITH_SYS_TIME 1

/* Define if tanh(-0.) is -0., or if platform doesn't have signed zeros */
#define TANH_PRESERVES_ZERO_SIGN 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#cmakedefine TIME_WITH_SYS_TIME 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
#cmakedefine TM_IN_SYS_TIME 1

/* Define if you want to use computed gotos in ceval.c. */
/* #undef USE_COMPUTED_GOTOS */

/* Define to use the C99 inline keyword. */
#define USE_INLINE 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# undef _ALL_SOURCE
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Define if a va_list is an array of some kind */
#cmakedefine VA_LIST_IS_ARRAY 1

/* Define if you want SIGFPE handled (see Include/pyfpe.h). */
#undef WANT_SIGFPE_HANDLER 1

/* Define if WINDOW in curses.h offers a field _flags. */
#cmakedefine WINDOW_HAS_FLAGS 1

/* Define if you want documentation strings in extension modules */
#cmakedefine WITH_DOC_STRINGS 1

/* Define if you want to use the new-style (Openstep, Rhapsody, MacOS) dynamic
   linker (dyld) instead of the old-style (NextStep) dynamic linker (rld).
   Dyld is necessary to support frameworks. */
#define WITH_DYLD 1

/* Define to 1 if libintl is needed for locale functions. */
#undef WITH_LIBINTL

/* Define if you want to produce an OpenStep/Rhapsody framework (shared
   library plus accessory files). */
#undef WITH_NEXT_FRAMEWORK

/* Define if you want to compile in Python-specific mallocs */
#cmakedefine WITH_PYMALLOC 1

/* Define if you want to compile in rudimentary thread support */
#cmakedefine WITH_THREAD 1

/* Define to profile with the Pentium timestamp counter */
#cmakedefine WITH_TSC 1

/* Define if you want pymalloc to be disabled when running under valgrind */
/* #undef WITH_VALGRIND */

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Define if arithmetic is subject to x87-style double rounding issue */
/* #undef X87_DOUBLE_ROUNDING */

/* Define on OpenBSD to activate all library features */
#cmakedefine _BSD_SOURCE 1

/* Define on Irix to enable u_int */
#cmakedefine _BSD_TYPES 1

/* Define on Darwin to activate all library features */
#cmakedefine _DARWIN_C_SOURCE 1

/* This must be set to 64 on some systems to enable large file support. */
#define _FILE_OFFSET_BITS 64

/* Define on Linux to activate all library features */
#define _GNU_SOURCE 1

/* This must be defined on some systems to enable large file support. */
#define _LARGEFILE_SOURCE 1

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define on NetBSD to activate all library features */
#define _NETBSD_SOURCE 1

/* Define _OSF_SOURCE to get the makedev macro. */
/* #undef _OSF_SOURCE */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to activate features from IEEE Stds 1003.1-2001 */
/* #undef _POSIX_C_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define if you have POSIX threads, and your system does not define that. */
/* #undef _POSIX_THREADS */

/* Define to force use of thread-safe errno, h_errno, and other functions */
#define _REENTRANT 1

/* Define for Solaris 2.5.1 so the uint32_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT32_T */

/* Define for Solaris 2.5.1 so the uint64_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT64_T */

/* Define to the level of X/Open that your system supports */
/* #undef _XOPEN_SOURCE */

/* Define to activate Unix95-and-earlier features */
/* #undef _XOPEN_SOURCE_EXTENDED */

/* Define on FreeBSD to activate all library features */
#define __BSD_VISIBLE 1

/* Define to 1 if type `char' is unsigned and you are not using gcc.  */
#ifndef __CHAR_UNSIGNED__
/* # undef __CHAR_UNSIGNED__ */
#endif

/* Define to 'long' if <time.h> doesn't define. */
/* #undef clock_t */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to the type of a signed integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int32_t */

/* Define to the type of a signed integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int64_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to empty if the keyword does not work. */
/* #undef signed */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/socket.h> does not define. */
/* #undef socklen_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */

/* Define to the type of an unsigned integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint32_t */

/* Define to the type of an unsigned integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint64_t */

/* Define to empty if the keyword does not work. */
/* #undef volatile */


/* Define the macros needed if on a UnixWare 7.x system. */
#if defined(__USLC__) && defined(__SCO_VERSION__)
#define STRICT_SYSV_CURSES /* Don't use ncurses extensions */
#endif

#endif /*Py_PYCONFIG_H*/

