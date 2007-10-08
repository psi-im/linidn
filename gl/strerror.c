/* strerror.c --- ANSI C compatible system error routine

   Copyright (C) 1986, 1988, 1989, 1991, 2002, 2003, 2006, 2007 Free
   Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <config.h>

#if REPLACE_STRERROR

# include <string.h>
# include <stdio.h>

# undef strerror

char *rpl_strerror (int n)
{
  static char const fmt[] = "Unknown error (%d)";
  static char mesg[sizeof fmt + sizeof n * CHAR_BIT / 3];

  char *result = strerror (n);

  if (! result)
    {
      sprintf (mesg, fmt, n);
      return mesg;
    }
  return result;
}

#elif !HAVE_STRERROR

#include <limits.h>

/* Don't include <stdio.h>, since it may or may not declare
   sys_errlist and its declarations may collide with ours.  Just
   declare the stuff that we need directly.  Standard hosted C89
   implementations define strerror and they don't need this strerror
   function, so take some liberties with the standard to cater to
   ancient or limited freestanding implementations.  */
int sprintf (char *, char const *, ...);
extern int sys_nerr;
extern char *sys_errlist[];

char *
strerror (int n)
{
  static char const fmt[] = "Unknown error (%d)";
  static char mesg[sizeof fmt + sizeof n * CHAR_BIT / 3];

  if (n < 0 || n >= sys_nerr)
    {
      sprintf (mesg, fmt, n);
      return mesg;
    }
  else
    return sys_errlist[n];
}

#else

/* This declaration is solely to ensure that after preprocessing
   this file is never empty.  */
typedef int dummy;

#endif