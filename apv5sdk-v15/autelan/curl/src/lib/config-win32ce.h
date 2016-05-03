#ifndef __LIB_CONFIG_WIN32CE_H
#define __LIB_CONFIG_WIN32CE_H

/* ================================================================ */
/*  lib/config-win32ce.h - Hand crafted config file for windows ce  */
/* ================================================================ */

/* ---------------------------------------------------------------- */
/*                          HEADER FILES                            */
/* ---------------------------------------------------------------- */

/* Define if you have the <arpa/inet.h> header file.  */
/* #define HAVE_ARPA_INET_H 1 */

/* Define if you have the <assert.h> header file.  */
/* #define HAVE_ASSERT_H 1 */

/* Define if you have the <crypto.h> header file.  */
/* #define HAVE_CRYPTO_H 1 */

/* Define if you have the <err.h> header file.  */
/* #define HAVE_ERR_H 1 */

/* Define if you have the <fcntl.h> header file.  */
#define HAVE_FCNTL_H 1

/* Define if you have the <getopt.h> header file.  */
/* #define HAVE_GETOPT_H 1 */

/* Define if you have the <io.h> header file.  */
#define HAVE_IO_H 1

/* Define if you need the malloc.h header header file even with stdlib.h  */
#define NEED_MALLOC_H 1

/* Define if you have the <netdb.h> header file.  */
/* #define HAVE_NETDB_H 1 */

/* Define if you have the <netinet/in.h> header file.  */
/* #define HAVE_NETINET_IN_H 1 */

/* Define if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define if you have the <sgtty.h> header file.  */
/* #define HAVE_SGTTY_H 1 */

/* Define if you have the <ssl.h> header file.  */
/* #define HAVE_SSL_H 1 */

/* Define if you have the <stdlib.h> header file.  */
#define HAVE_STDLIB_H 1

/* Define if you have the <process.h> header file.  */
#define HAVE_PROCESS_H 1

/* Define if you have the <sys/param.h> header file.  */
/* #define HAVE_SYS_PARAM_H 1 */

/* Define if you have the <sys/select.h> header file.  */
/* #define HAVE_SYS_SELECT_H 1 */

/* Define if you have the <sys/socket.h> header file.  */
/* #define HAVE_SYS_SOCKET_H 1 */

/* Define if you have the <sys/sockio.h> header file.  */
/* #define HAVE_SYS_SOCKIO_H 1 */

/* Define if you have the <sys/stat.h> header file.  */
#define HAVE_SYS_STAT_H 1

/* Define if you have the <sys/time.h> header file */
/* #define HAVE_SYS_TIME_H 1 */

/* Define if you have the <sys/types.h> header file.  */
/* #define HAVE_SYS_TYPES_H 1 */

/* Define if you have the <sys/utime.h> header file */
#define HAVE_SYS_UTIME_H 1

/* Define if you have the <termio.h> header file.  */
/* #define HAVE_TERMIO_H 1 */

/* Define if you have the <termios.h> header file.  */
/* #define HAVE_TERMIOS_H 1 */

/* Define if you have the <time.h> header file.  */
#define HAVE_TIME_H 1

/* Define if you have the <unistd.h> header file.  */
#if defined(__MINGW32__) || defined(__WATCOMC__) || defined(__LCC__)
#define HAVE_UNISTD_H 1
#endif

/* Define if you have the <windows.h> header file.  */
#define HAVE_WINDOWS_H 1

/* Define if you have the <winsock.h> header file.  */
#define HAVE_WINSOCK_H 1

/* Define if you have the <winsock2.h> header file.  */
/* #define HAVE_WINSOCK2_H 1 */

/* Define if you have the <ws2tcpip.h> header file.  */
/* #define HAVE_WS2TCPIP_H 1 */

/* ---------------------------------------------------------------- */
/*                        OTHER HEADER INFO                         */
/* ---------------------------------------------------------------- */

/* Define if sig_atomic_t is an available typedef. */
#define HAVE_SIG_ATOMIC_T 1

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if you can safely include both <sys/time.h> and <time.h>.  */
/* #define TIME_WITH_SYS_TIME 1 */

/* ---------------------------------------------------------------- */
/*                             FUNCTIONS                            */
/* ---------------------------------------------------------------- */

/* Define if you have the closesocket function.  */
#define HAVE_CLOSESOCKET 1

/* Define if you don't have vprintf but do have _doprnt.  */
/* #define HAVE_DOPRNT 1 */

/* Define if you have the gethostbyaddr function.  */
#define HAVE_GETHOSTBYADDR 1

/* Define if you have the gethostname function.  */
#define HAVE_GETHOSTNAME 1

/* Define if you have the getpass function.  */
/* #define HAVE_GETPASS 1 */

/* Define if you have the getservbyname function.  */
#define HAVE_GETSERVBYNAME 1

/* Define if you have the gettimeofday function.  */
/*  #define HAVE_GETTIMEOFDAY 1 */

/* Define if you have the inet_addr function.  */
#define HAVE_INET_ADDR 1

/* Define if you have the inet_ntoa function.  */
#define HAVE_INET_NTOA 1

/* Define if you have the ioctlsocket function.  */
#define HAVE_IOCTLSOCKET 1

/* Define if you have the perror function.  */
#define HAVE_PERROR 1

/* Define if you have the RAND_screen function when using SSL  */
#define HAVE_RAND_SCREEN 1

/* Define if you have the `RAND_status' function when using SSL. */
#define HAVE_RAND_STATUS 1

/* Define if you have the select function.  */
#define HAVE_SELECT 1

/* Define if you have the setvbuf function.  */
#define HAVE_SETVBUF 1

/* Define if you have the socket function.  */
#define HAVE_SOCKET 1

/* Define if you have the strcasecmp function.  */
/* #define HAVE_STRCASECMP 1 */

/* Define if you have the stricmp function.  */
/* #define HAVE_STRICMP 1 */

/* Define if you have the strdup function.  */
/* #define HAVE_STRDUP 1 */

/* Define if you have the strftime function.  */
/* #define HAVE_STRFTIME 1 */

/* Define if you have the strstr function.  */
#define HAVE_STRSTR 1

/* Define if you have the strtoll function.  */
#if defined(__MINGW32__) || defined(__WATCOMC__)
#define HAVE_STRTOLL 1
#endif

/* Define if you have the tcgetattr function.  */
/* #define HAVE_TCGETATTR 1 */

/* Define if you have the tcsetattr function.  */
/* #define HAVE_TCSETATTR 1 */

/* Define if you have the utime function */
#define HAVE_UTIME 1

/* Define if you have the getnameinfo function. */
#define HAVE_GETNAMEINFO 1

/* Define to the type qualifier of arg 1 for getnameinfo. */
#define GETNAMEINFO_QUAL_ARG1 const

/* Define to the type of arg 1 for getnameinfo. */
#define GETNAMEINFO_TYPE_ARG1 struct sockaddr *

/* Define to the type of arg 2 for getnameinfo. */
#define GETNAMEINFO_TYPE_ARG2 socklen_t

/* Define to the type of args 4 and 6 for getnameinfo. */
#define GETNAMEINFO_TYPE_ARG46 DWORD

/* Define to the type of arg 7 for getnameinfo. */
#define GETNAMEINFO_TYPE_ARG7 int

/* Define if you have the recv function. */
#define HAVE_RECV 1

/* Define to the type of arg 1 for recv. */
#define RECV_TYPE_ARG1 SOCKET

/* Define to the type of arg 2 for recv. */
#define RECV_TYPE_ARG2 char *

/* Define to the type of arg 3 for recv. */
#define RECV_TYPE_ARG3 int

/* Define to the type of arg 4 for recv. */
#define RECV_TYPE_ARG4 int

/* Define to the function return type for recv. */
#define RECV_TYPE_RETV int

/* Define if you have the send function. */
#define HAVE_SEND 1

/* Define to the type of arg 1 for send. */
#define SEND_TYPE_ARG1 SOCKET

/* Define to the type qualifier of arg 2 for send. */
#define SEND_QUAL_ARG2 const

/* Define to the type of arg 2 for send. */
#define SEND_TYPE_ARG2 char *

/* Define to the type of arg 3 for send. */
#define SEND_TYPE_ARG3 int

/* Define to the type of arg 4 for send. */
#define SEND_TYPE_ARG4 int

/* Define to the function return type for send. */
#define SEND_TYPE_RETV int

/* ---------------------------------------------------------------- */
/*                       TYPEDEF REPLACEMENTS                       */
/* ---------------------------------------------------------------- */

/* Define this if in_addr_t is not an available 'typedefed' type */
#define in_addr_t unsigned long

/* Define as the return type of signal handlers (int or void).  */
#define RETSIGTYPE void

/* Define ssize_t if it is not an available 'typedefed' type */
#if (defined(__WATCOMC__) && (__WATCOMC__ >= 1240)) || defined(__POCC__)
#elif defined(_WIN64)
#define ssize_t __int64
#else
#define ssize_t int
#endif

/* ---------------------------------------------------------------- */
/*                            TYPE SIZES                            */
/* ---------------------------------------------------------------- */

/* The number of bytes in a long double.  */
#define SIZEOF_LONG_DOUBLE 16

/* The number of bytes in a long long.  */
/* #define SIZEOF_LONG_LONG 8 */

/* Undef SIZEOF_CURL_OFF_T if already defined. */
#ifdef SIZEOF_CURL_OFF_T
#undef SIZEOF_CURL_OFF_T
#endif

/* Define SIZEOF_CURL_OFF_T as computed by sizeof(curl_off_t) */
#define SIZEOF_CURL_OFF_T 4

/* ---------------------------------------------------------------- */
/*                          STRUCT RELATED                          */
/* ---------------------------------------------------------------- */

/* Define this if you have struct sockaddr_storage */
/* #define HAVE_STRUCT_SOCKADDR_STORAGE 1 */

/* Define this if you have struct timeval */
#define HAVE_STRUCT_TIMEVAL 1

/* ---------------------------------------------------------------- */
/*                        COMPILER SPECIFIC                         */
/* ---------------------------------------------------------------- */

/* Undef keyword 'const' if it does not work.  */
/* #undef const */

/* ---------------------------------------------------------------- */
/*                           LDAP SUPPORT                           */
/* ---------------------------------------------------------------- */

#define CURL_LDAP_WIN 1
#undef CURL_LDAP_HYBRID
#undef HAVE_LDAP_URL_PARSE

/* ---------------------------------------------------------------- */
/*                       ADDITIONAL DEFINITIONS                     */
/* ---------------------------------------------------------------- */

/* Defines set for VS2005 to _not_ deprecate a few functions we use. */
#define _CRT_SECURE_NO_DEPRECATE 1
#define _CRT_NONSTDC_NO_DEPRECATE 1

/* Define cpu-machine-OS */
#undef OS
#define OS "i386-pc-win32ce"

/* Name of package */
#define PACKAGE "curl"

/* ---------------------------------------------------------------- */
/*                       WinCE                                      */
/* ---------------------------------------------------------------- */

#define CURL_DISABLE_FILE 1
#define CURL_DISABLE_TELNET 1
#define CURL_DISABLE_LDAP 1
#define WITHOUT_MM_LIB 1

#ifdef HAVE_WINDOWS_H
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  include <windows.h>
#  ifdef HAVE_WINSOCK2_H
#    include <winsock2.h>
#    ifdef HAVE_WS2TCPIP_H
#       include <ws2tcpip.h>
#    endif
#  else
#    ifdef HAVE_WINSOCK_H
#      include <winsock.h>
#    endif
#  endif
#  include <process.h>
#endif

#define ENOSPC 1
#define ENOMEM 2
#define EAGAIN 3

extern int stat(const char *path,struct stat *buffer );

#endif /* __LIB_CONFIG_WIN32CE_H */