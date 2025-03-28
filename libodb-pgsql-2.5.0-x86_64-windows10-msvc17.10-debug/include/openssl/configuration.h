/* file      : libcrypto/downstream/openssl/configuration.h -*- C -*-
 * license   : Apache License 2.0; see accompanying LICENSE file
 */

#ifndef LIBCRYPTO_DOWNSTREAM_OPENSSL_CONFIGURATION_H
#define LIBCRYPTO_DOWNSTREAM_OPENSSL_CONFIGURATION_H

/* Define OPENSSL_PIC and {L|B}_ENDIAN macros (that upstream defines on the
 * command line via -D) if we are building libcrypto (see ../../buildfile for
 * details).
 */
#ifdef LIBCRYPTO_BUILD
#  define OPENSSL_PIC

/* Endianess.
 */
#  ifdef __FreeBSD__
#    include <sys/endian.h> /* BYTE_ORDER */
#  else
#    if defined(_WIN32)
#      ifndef BYTE_ORDER
#        define BIG_ENDIAN    4321
#        define LITTLE_ENDIAN 1234
#        define BYTE_ORDER    LITTLE_ENDIAN
#      endif
#    else
#      include <sys/param.h>  /* BYTE_ORDER/__BYTE_ORDER */
#      ifndef BYTE_ORDER
#        ifdef __BYTE_ORDER
#          define BYTE_ORDER    __BYTE_ORDER
#          define BIG_ENDIAN    __BIG_ENDIAN
#          define LITTLE_ENDIAN __LITTLE_ENDIAN
#        else
#          error no BYTE_ORDER/__BYTE_ORDER define
#        endif
#      endif
#    endif
#  endif

#  if BYTE_ORDER == BIG_ENDIAN
#    define B_ENDIAN
#  else
#    define L_ENDIAN
#  endif
#endif

/* Include upstream's auto-generated platform-specific configuration.h.
 */
#include <openssl/configuration/platform.h>

/* Only enable Kernel TLS (kTLS) for Linux and FreeBSD.
 *
 * Note that support for kTLS is added to Linux kernel in the version 4.13.0.
 * However, in the early implementations (until 4.15.0) the
 * /usr/include/linux/tls.h header can be broken, including some non-existent
 * system headers (net/tcp.h, etc). It also seems that until the kernel
 * version 5.19.0 kTLS is not fully implemented, which results in a number of
 * warnings about skipping some kTLS functionality, while building OpenSSL for
 * such kernels. Thus, let's only enable kTLS starting the kernel version
 * 5.19.0.
 *
 * Also note that FreeBSD adds support for TLS socket kernel offload in 13.0.
 */
#ifndef OPENSSL_NO_KTLS
#  define OPENSSL_NO_KTLS
#endif

#if defined(__linux__)
#  include <linux/version.h>
#  if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0)
#    undef OPENSSL_NO_KTLS
#  endif
#elif defined(__FreeBSD__) && __FreeBSD__ >= 13
#  undef OPENSSL_NO_KTLS
#endif

#endif /* LIBCRYPTO_DOWNSTREAM_OPENSSL_CONFIGURATION_H */
