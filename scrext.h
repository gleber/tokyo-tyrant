/*************************************************************************************************
 * Scripting language extension of Tokyo Tyrant
 *                                                      Copyright (C) 2006-2008 Mikio Hirabayashi
 * This file is part of Tokyo Tyrant.
 * Tokyo Tyrant is free software; you can redistribute it and/or modify it under the terms of
 * the GNU Lesser General Public License as published by the Free Software Foundation; either
 * version 2.1 of the License or any later version.  Tokyo Tyrant is distributed in the hope
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Tokyo
 * Tyrant; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA.
 *************************************************************************************************/


#ifndef _SCREXT_H                        // duplication check
#define _SCREXT_H



/*************************************************************************************************
 * configuration
 *************************************************************************************************/


#include "myconf.h"
#include <ttutil.h>
#include <tculog.h>
#include <tcrdb.h>


#if defined(_MYLUA)
#define TTLUAEXT
#else
#define TTNOEXT
#endif



/*************************************************************************************************
 * pseudo API
 *************************************************************************************************/


/* Initialize the scripting language extension.
   `thnum' specifies the number of the native threads.
   `thid' specifies the thread ID number.
   `path' specifies the path of the initilizing script.
   `adb' specifies the abstract database object.
   `ulog' specifies the update log object.
   `sid' specifies the server ID.
   `stash' specifies the stash object.
   `lcks' specifies the mutex objects for user locks.
   `lcknum' specifies the number of user locks.
   `logger' specifies the pointer to a function to do with a log message.
   The return value is the scripting object or `NULL' on failure. */
void *scrextnew(int thnum, int thid, const char *path, TCADB *adb, TCULOG *ulog,
                uint32_t sid, TCMDB *stash, pthread_mutex_t *lcks, int lcknum,
                void (*logger)(int, const char *, void *));


/* Destroy the scripting language extension.
   `scr' specifies the scripting object.
   If successful, the return value is true, else, it is false. */
bool scrextdel(void *scr);


/* Call a method of the scripting language extension.
   `scr' specifies the scripting object.
   `name' specifies the name of the method to be called.
   `kbuf' specifies the pointer to the region of the key.
   `ksiz' specifies the size of the region of the key.
   `vbuf' specifies the pointer to the region of the value.
   `vsiz' specifies the size of the region of the value.
   `sp' specifies the pointer to the variable into which the size of the region of the return
   value is assigned.
   If successful, the return value is the pointer to the region of the value of the corresponding
   record.  It should be allocated by `malloc' call.  `NULL' is returned on failure.
   Note that the returned region is released by the caller. */
char *scrextcallmethod(void *scr, const char *name,
                       const void *kbuf, int ksiz, const void *vbuf, int vsiz, int *sp);



#endif                                   // duplication check


// END OF FILE
