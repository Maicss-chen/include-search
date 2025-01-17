// -*- mode: cpp; mode: fold -*-
/* Internationalization macros for apt. This header should be included last
   in each C file. */

// Set by autoconf
#define USE_NLS

#ifdef USE_NLS
// apt will use the gettext implementation of the C library
#include <libintl.h>
#include <locale.h>
# ifdef APT_DOMAIN
#   define _(x) dgettext(APT_DOMAIN,x)
#   define P_(msg,plural,n) dngettext(APT_DOMAIN,msg,plural,n)
# else
#   define _(x) gettext(x)
#   define P_(msg,plural,n) ngettext(msg,plural,n)
# endif
# define N_(x) x
#else
// apt will not use any gettext
# define setlocale(a, b)
# define textdomain(a)
# define bindtextdomain(a, b)
# define _(x) x
# define P_(msg,plural,n) (n == 1 ? msg : plural)
# define N_(x) x
# define dgettext(d, m) m
#endif
