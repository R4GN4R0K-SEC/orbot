/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.in by autoheader.  */
#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
/*********************************************************************
 *
 * File        :  $Source: /cvsroot/ijbswa/current/acconfig.h,v $
 *
 * Purpose     :  This file should be the first thing included in every
 *                .c file.  (Before even system headers).  It contains 
 *                #define statements for various features.  It was
 *                introduced because the compile command line started
 *                getting ludicrously long with feature defines.
 *
 * Copyright   :  Written by and Copyright (C) 2001 the SourceForge
 *                Privoxy team. http://www.privoxy.org/
 *
 *                Based on the Internet Junkbuster originally written
 *                by and Copyright (C) 1997 Anonymous Coders and 
 *                Junkbusters Corporation.  http://www.junkbusters.com
 *
 *                This program is free software; you can redistribute it 
 *                and/or modify it under the terms of the GNU General
 *                Public License as published by the Free Software
 *                Foundation; either version 2 of the License, or (at
 *                your option) any later version.
 *
 *                This program is distributed in the hope that it will
 *                be useful, but WITHOUT ANY WARRANTY; without even the
 *                implied warranty of MERCHANTABILITY or FITNESS FOR A
 *                PARTICULAR PURPOSE.  See the GNU General Public
 *                License for more details.
 *
 *                The GNU General Public License should be included with
 *                this file.  If not, you can view it at
 *                http://www.gnu.org/copyleft/gpl.html
 *                or write to the Free Software Foundation, Inc., 59
 *                Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Revisions   :
 *    $Log: acconfig.h,v $
 *    Revision 1.36  2008/10/18 11:17:52  fabiankeil
 *    Connection keep-alive support is ready for testing,
 *    allow enabling it through the configure script.
 *
 *    Revision 1.35  2008/04/06 15:18:33  fabiankeil
 *    Oh well, rename the --enable-pcre-host-patterns option to
 *    --enable-extended-host-patterns as it's not really PCRE syntax.
 *
 *    Revision 1.34  2008/04/06 14:54:26  fabiankeil
 *    Use PCRE syntax in host patterns when configured
 *    with --enable-pcre-host-patterns.
 *
 *    Revision 1.33  2006/12/17 19:15:26  fabiankeil
 *    Added ./configure switch for FEATURE_GRACEFUL_TERMINATION.
 *
 *    Revision 1.32  2006/07/18 14:48:45  david__schmidt
 *    Reorganizing the repository: swapping out what was HEAD (the old 3.1 branch)
 *    with what was really the latest development (the v_3_0_branch branch)
 *
 *    Revision 1.27.2.4  2003/12/17 16:34:40  oes
 *    Cosmetics
 *
 *    Revision 1.27.2.3  2003/03/27 16:03:19  oes
 *    Another shot at Bug #707467
 *
 *    Revision 1.27.2.2  2003/03/21 14:39:12  oes
 *    Presumably fixed Bug #707467 by defining unix ifdef __unix__
 *
 *    Revision 1.27.2.1  2002/08/10 11:22:31  oes
 *    - Add two AC_DEFINEs that indicate if the pcre*.h headers
 *      are located in a pcre/ subdir to the include path.
 *
 *    Revision 1.27  2002/04/25 19:13:57  morcego
 *    Removed RPM release number declaration on configure.in
 *    Changed makefile to use given value for RPM_PACKAGEV when on uploading
 *    targets (will produce an error, explaining who to do it, if no value
 *    if provided).
 *
 *    Revision 1.26  2002/04/11 11:00:21  oes
 *    Applied Moritz' fix for socklen_t on Solaris
 *
 *    Revision 1.25  2002/04/06 20:38:01  jongfoster
 *    Renaming VC++ versions of config.h
 *
 *    Revision 1.24  2002/04/04 00:36:36  gliptak
 *    always use pcre for matching
 *
 *    Revision 1.23  2002/04/03 22:28:03  gliptak
 *    Removed references to gnu_regex
 *
 *    Revision 1.22  2002/03/26 22:29:54  swa
 *    we have a new homepage!
 *
 *    Revision 1.21  2002/03/24 14:31:08  swa
 *    remove more crappy files. set RPM
 *    release version correctly.
 *
 *    Revision 1.20  2002/03/24 13:46:44  swa
 *    name change related issue.
 *
 *    Revision 1.19  2002/03/24 13:25:42  swa
 *    name change related issues
 *
 *    Revision 1.18  2002/03/08 16:40:28  oes
 *    Added FEATURE_NO_GIFS
 *
 *    Revision 1.17  2002/03/04 17:52:44  oes
 *    Deleted PID_FILE_PATH
 *
 *    Revision 1.16  2002/01/10 12:36:18  oes
 *    Moved HAVE_*_R to acconfig.h, where they belong.
 *
 *    Revision 1.15  2001/12/30 14:07:31  steudten
 *    - Add signal handling (unix)
 *    - Add SIGHUP handler (unix)
 *    - Add creation of pidfile (unix)
 *    - Add action 'top' in rc file (RH)
 *    - Add entry 'SIGNALS' to manpage
 *    - Add exit message to logfile (unix)
 *
 *    Revision 1.14  2001/10/23 21:24:09  jongfoster
 *    Support for FEATURE_CGI_EDIT_ACTIONS
 *
 *    Revision 1.13  2001/10/07 15:30:41  oes
 *    Removed FEATURE_DENY_GZIP
 *
 *    Revision 1.12  2001/09/13 19:56:37  jongfoster
 *    Reverting to revision 1.10 - previous checking was majorly broken.
 *
 *    Revision 1.10  2001/07/30 22:08:36  jongfoster
 *    Tidying up #defines:
 *    - All feature #defines are now of the form FEATURE_xxx
 *    - Permanently turned off WIN_GUI_EDIT
 *    - Permanently turned on WEBDAV and SPLIT_PROXY_ARGS
 *
 *    Revision 1.9  2001/07/29 19:08:52  jongfoster
 *    Changing _CONFIG_H to CONFIG_H_INCLUDED.
 *    Also added protection against using a MinGW32 or CygWin version of
 *    config.h from within MS Visual C++
 *
 *    Revision 1.8  2001/07/29 17:09:17  jongfoster
 *    Major changes to build system in order to fix these bugs:
 *    - pthreads under Linux was broken - changed -lpthread to -pthread
 *    - Compiling in MinGW32 mode under CygWin now correctly detects
 *      which shared libraries are available
 *    - Solaris support (?) (Not tested under Solaris yet)
 *
 *    Revision 1.7  2001/07/25 22:53:59  jongfoster
 *    Will #error if pthreads is enabled under BeOs
 *
 *    Revision 1.6  2001/07/15 17:54:29  jongfoster
 *    Renaming #define STATIC to STATIC_PCRE
 *    Adding new #define FEATURE_PTHREAD that will be used to enable
 *    POSIX threads support.
 *
 *    Revision 1.5  2001/07/13 13:48:37  oes
 *     - (Fix:) Copied CODE_STATUS #define from config.h.in
 *     - split REGEX #define into REGEX_GNU and REGEX_PCRE
 *       and removed PCRE.
 *       (REGEX = REGEX_GNU || REGEX_PCRE per project.h)
 *     - Moved STATIC (for pcre) here from Makefile.in
 *     - Introduced STATIC_PCRS #define to allow for dynaimc linking with
 *       libpcrs
 *     - Removed PCRS #define, since pcrs is now needed for CGI anyway
 *
 *    Revision 1.4  2001/05/29 09:50:24  jongfoster
 *    Unified blocklist/imagelist/permissionslist.
 *    File format is still under discussion, but the internal changes
 *    are (mostly) done.
 *
 *    Also modified interceptor behaviour:
 *    - We now intercept all URLs beginning with one of the following
 *      prefixes (and *only* these prefixes):
 *        * http://i.j.b/
 *        * http://ijbswa.sf.net/config/
 *        * http://ijbswa.sourceforge.net/config/
 *    - New interceptors "home page" - go to http://i.j.b/ to see it.
 *    - Internal changes so that intercepted and fast redirect pages
 *      are not replaced with an image.
 *    - Interceptors now have the option to send a binary page direct
 *      to the client. (i.e. ijb-send-banner uses this)
 *    - Implemented show-url-info interceptor.  (Which is why I needed
 *      the above interceptors changes - a typical URL is
 *      "http://i.j.b/show-url-info?url=www.somesite.com/banner.gif".
 *      The previous mechanism would not have intercepted that, and
 *      if it had been intercepted then it then it would have replaced
 *      it with an image.)
 *
 *    Revision 1.3  2001/05/26 01:26:34  jongfoster
 *    New #define, WIN_GUI_EDIT, enables the (embryonic) Win32 GUI editor.
 *    This #define cannot be set from ./configure - there's no point, it
 *    doesn't work yet.  See feature request # 425722
 *
 *    Revision 1.2  2001/05/22 17:43:35  oes
 *
 *    - Enabled filtering banners by size rather than URL
 *      by adding patterns that replace all standard banner
 *      sizes with the "Junkbuster" gif to the re_filterfile
 *
 *    - Enabled filtering WebBugs by providing a pattern
 *      which kills all 1x1 images
 *
 *    - Added support for PCRE_UNGREEDY behaviour to pcrs,
 *      which is selected by the (nonstandard and therefore
 *      capital) letter 'U' in the option string.
 *      It causes the quantifiers to be ungreedy by default.
 *      Appending a ? turns back to greedy (!).
 *
 *    - Added a new interceptor ijb-send-banner, which
 *      sends back the "Junkbuster" gif. Without imagelist or
 *      MSIE detection support, or if tinygif = 1, or the
 *      URL isn't recognized as an imageurl, a lame HTML
 *      explanation is sent instead.
 *
 *    - Added new feature, which permits blocking remote
 *      script redirects and firing back a local redirect
 *      to the browser.
 *      The feature is conditionally compiled, i.e. it
 *      can be disabled with --disable-fast-redirects,
 *      plus it must be activated by a "fast-redirects"
 *      line in the config file, has its own log level
 *      and of course wants to be displayed by show-proxy-args
 *      Note: Boy, all the #ifdefs in 1001 locations and
 *      all the fumbling with configure.in and acconfig.h
 *      were *way* more work than the feature itself :-(
 *
 *    - Because a generic redirect template was needed for
 *      this, tinygif = 3 now uses the same.
 *
 *    - Moved GIFs, and other static HTTP response templates
 *      to project.h
 *
 *    - Many minor fixes
 *
 *    - Removed some >400 CRs again (Jon, you really worked
 *      a lot! ;-)
 *
 *    Revision 1.1.1.1  2001/05/15 13:58:45  oes
 *    Initial import of version 2.9.3 source tree
 *
 *
 *********************************************************************/


/*
 * Version number - Major (X._._)
 */
#define VERSION_MAJOR 3

/*
 * Version number - Minor (_.X._)
 */
#define VERSION_MINOR 0

/*
 * Version number - Point (_._.X)
 */
#define VERSION_POINT 12

/*
 * Version number, as a string
 */
#define VERSION "3.0.12"

/*
 * Status of the code: "alpha", "beta" or "stable".
 */
#define CODE_STATUS "stable"

/* 
 * Should pcre be statically built in instead of linkling with libpcre?
 * (This is determined by configure depending on the availiability of
 * libpcre and user preferences). The name is ugly, but pcre needs it.
 * Don't bother to change this here! Use configure instead.
 */
#define STATIC_PCRE 1

/* 
 * Should pcrs be statically built in instead of linkling with libpcrs?
 * (This is determined by configure depending on the availiability of
 * libpcrs and user preferences).
 * Don't bother to change this here! Use configure instead.
 */
#define STATIC_PCRS 1

/*
 * Allows the use of an ACL to control access to the proxy by IP address.
 */
#define FEATURE_ACL 1

/*
 * Enables the web-based configuration (actionsfile) editor.  If you
 * have a shared proxy, you might want to turn this off.
 */
#define FEATURE_CGI_EDIT_ACTIONS 1

/*
 * Allows the use of jar files to capture cookies.
 */
/* #undef FEATURE_COOKIE_JAR */

/*
 * Locally redirect remote script-redirect URLs
 */
#define FEATURE_FAST_REDIRECTS 1

/*
 * Bypass filtering for 1 page only
 */
#define FEATURE_FORCE_LOAD 1

/*
 * Allow blocking using images as well as HTML.
 * If you do not define this then everything is blocked as HTML.
 *
 * Note that this is required if you want to use FEATURE_IMAGE_DETECT_MSIE.
 */
#define FEATURE_IMAGE_BLOCKING 1

/*
 * Detect image requests automatically for MSIE.  Will fall back to
 * other image-detection methods (i.e. "+image" permission) for other
 * browsers.
 *
 * You must also define FEATURE_IMAGE_BLOCKING to use this feature.
 *
 * It detects the following header pair as an image request:
 *
 * User-Agent: Mozilla/4.0 (compatible; MSIE 5.5; Windows NT 5.0)
 * Accept: * / *
 *
 * And the following as a HTML request:
 *
 * User-Agent: Mozilla/4.0 (compatible; MSIE 5.5; Windows NT 5.0)
 * Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, * / *
 *
 * And no, I haven't got that backwards - IE is being wierd.
 *
 * Known limitations: 
 * 1) If you press shift-reload on a blocked HTML page, you get
 *    the image "blocked" page, not the HTML "blocked" page.
 * 2) Once an image "blocked" page has been sent, viewing it 
 *    in it's own browser window *should* bring up the HTML
 *    "blocked" page, but it doesn't.  You need to clear the 
 *    browser cache to get the HTML version again.
 *
 * These limitations are due to IE making inconsistent choices
 * about which "Accept:" header to send.
 */
/* #undef FEATURE_IMAGE_DETECT_MSIE */

/*
 * Kills JavaScript popups - window.open, onunload, etc.
 */
/* #undef FEATURE_KILL_POPUPS */

/*
 * Use PNG instead of GIF for built-in images
 */
/* #undef FEATURE_NO_GIFS */

/*
 * Allow to shutdown Privoxy through the webinterface.
 */
/* #undef FEATURE_GRACEFUL_TERMINATION */

/*
 * Allow PCRE syntax in host patterns.
 */
/* #undef FEATURE_EXTENDED_HOST_PATTERNS */

/*
 * Keep outgoing connections alive if possible.
 */
#define FEATURE_CONNECTION_KEEP_ALIVE 1

/*
 * Use POSIX threads instead of native threads.
 */
#define FEATURE_PTHREAD 1

/*
 * Enables statistics function.
 */
#define FEATURE_STATISTICS 1

/*
 * Allow Privoxy to be "disabled" so it is just a normal non-blocking
 * non-anonymizing proxy.  This is useful if you're trying to access a
 * blocked or broken site - just change the setting in the config file,
 * or use the handy "Disable" menu option in the Windows GUI.
 */
#define FEATURE_TOGGLE 1

/*
 * Allows the use of trust files.
 */
#define FEATURE_TRUST 1

/*
 * Defined on Solaris only.  Makes the system libraries thread safe.
 */
/* #undef _REENTRANT */

/*
 * Defined on Solaris only.  Without this, many important functions are not
 * defined in the system headers.
 */
/* #undef __EXTENSIONS__ */

/*
 * Defined always.
 * FIXME: Don't know what it does or why we need it.
 * (presumably something to do with MultiThreading?)
 */
#define __MT__ 1

/* If the (nonstandard and thread-safe) function gethostbyname_r
 * is available, select which signature to use
 */
#define HAVE_GETHOSTBYNAME_R_6_ARGS 1
/* #undef HAVE_GETHOSTBYNAME_R_5_ARGS */
/* #undef HAVE_GETHOSTBYNAME_R_3_ARGS */

/* If the (nonstandard and thread-safe) function gethostbyaddr_r
 * is available, select which signature to use
 */
/* #undef HAVE_GETHOSTBYADDR_R_8_ARGS */
/* #undef HAVE_GETHOSTBYADDR_R_7_ARGS */
/* #undef HAVE_GETHOSTBYADDR_R_5_ARGS */

/* Defined if you have gmtime_r and localtime_r with a signature
 * of (struct time *, struct tm *)
 */
#define HAVE_GMTIME_R 1
#define HAVE_LOCALTIME_R 1

/* Define to 'int' if <sys/socket.h> doesn't have it. 
 */
/* #undef socklen_t */

/* Define if pcre.h must be included as <pcre/pcre.h>
 */
/* #undef PCRE_H_IN_SUBDIR */

/* Define if pcreposix.h must be included as <pcre/pcreposix.h>
 */
/* #undef PCREPOSIX_H_IN_SUBDIR */


/* Define to 1 to use compression through the zlib library. */
#define FEATURE_ZLIB 1

/* Define to 1 if you have the `access' function. */
#define HAVE_ACCESS 1

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to 1 if you have the `atexit' function. */
#define HAVE_ATEXIT 1

/* Define to 1 if you have the `bcopy' function. */
#define HAVE_BCOPY 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define to 1 if you have the `gethostbyaddr' function. */
#define HAVE_GETHOSTBYADDR 1

/* Define to 1 if you have the `gethostbyaddr_r' function. */
/* #undef HAVE_GETHOSTBYADDR_R */

/* Define to 1 if you have the `gethostbyname' function. */
#define HAVE_GETHOSTBYNAME 1

/* Define to 1 if you have the `gethostbyname_r' function. */
#define HAVE_GETHOSTBYNAME_R 1

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the `inet_ntoa' function. */
#define HAVE_INET_NTOA 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `nsl' library (-lnsl). */
/* #undef HAVE_LIBNSL */

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the `localtime_r' function. */
#define HAVE_LOCALTIME_R 1

/* Define to 1 if you have the `memchr' function. */
#define HAVE_MEMCHR 1

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <OS.h> header file. */
/* #undef HAVE_OS_H */

/* Define to 1 if you have the `poll' function. */
#define HAVE_POLL 1

/* Define to 1 if you have the `putenv' function. */
#define HAVE_PUTENV 1

/* Define to 1 if you have the `random' function. */
/* #undef HAVE_RANDOM */

/* Define to 1 if you have the `regcomp' function. */
#define HAVE_REGCOMP 1

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define to 1 if you have the `socket' function. */
#define HAVE_SOCKET 1

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the `strftime' function. */
#define HAVE_STRFTIME 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strlcat' function. */
#define HAVE_STRLCAT 1

/* Define to 1 if you have the `strlcpy' function. */
#define HAVE_STRLCPY 1

/* Define to 1 if you have the `strptime' function. */
#define HAVE_STRPTIME 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/timeb.h> header file. */
#define HAVE_SYS_TIMEB_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the `timegm' function. */
/* #undef HAVE_TIMEGM */

/* Define to 1 if you have the `tzset' function. */
#define HAVE_TZSET 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Define to 1 if the `setpgrp' function takes no argument. */
#define SETPGRP_VOID 1

/* The size of `char *', as computed by sizeof. */
#define SIZEOF_CHAR_P 4

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 4

/* The size of `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG 8

/* The size of `size_t', as computed by sizeof. */
#define SIZEOF_SIZE_T 4

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to 'int' if <sys/socket.h> doesn't have it. */
/* #undef socklen_t */

/*
 * Defined always.
 * FIXME: Don't know what it does or why we need it.
 * (presumably something to do with ANSI Standard C?)
 */
#ifndef __STDC__
#define __STDC__ 1
#endif /* ndef __STDC__ */

/*
 * Need to set up this define only for the Pthreads library for
 * Win32, available from http://sources.redhat.com/pthreads-win32/
 */
#if defined(FEATURE_PTHREAD) && defined(_WIN32)
#define __CLEANUP_C
#endif /* defined(FEATURE_PTHREAD) && defined(_WIN32) */

/*
 * BEOS does not currently support POSIX threads.
 * This *should* be detected by ./configure, but let's be sure.
 */
#if defined(FEATURE_PTHREAD) && defined(__BEOS__)
#error BEOS does not support pthread - please run ./configure again with "--disable-pthread"

#endif /* defined(FEATURE_PTHREAD) && defined(__BEOS__) */

/*
 * On OpenBSD and maybe also FreeBSD, gcc doesn't define the cpp
 * symbol unix; it defines __unix__ and sometimes not even that:
 */
#if ( defined(__unix__) || defined(__NetBSD__) ) && !defined(unix)
#define unix 1
#endif

/*
 * It's too easy to accidentally use a Cygwin or MinGW32 version of config.h
 * under VC++, and it usually gives many wierd error messages.  Let's make
 * the error messages understandable, by bailing out now.
 */
#ifdef _MSC_VER
#error For MS VC++, please use vc_config_winthreads.h or vc_config_pthreads.h.  You can usually do this by selecting the "Build", "Clean" menu option.
#endif /* def _MSC_VER */

#endif /* CONFIG_H_INCLUDED */
