/*====================================================================*
 *   
 *   Copyright (c) 2010, Atheros Communications Inc.
 *   
 *   Permission to use, copy, modify, and/or distribute this software 
 *   for any purpose with or without fee is hereby granted, provided 
 *   that the above copyright notice and this permission notice appear 
 *   in all copies.
 *   
 *   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL 
 *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED 
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL  
 *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR 
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, 
 *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN 
 *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *   
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   
 *   void HPAVKeySpec (const char * string);
 *   
 *   HPAVKey.h
 *   
 *   confirm that a string is a legal HomePlug AV pass phrase; return
 *   on success; exit the program on failure; legal pass phrases have 
 *   12 to 64 character values ranging from 0x20 thru 0x7F;
 *
 *   this function is intended to check pass phrases entered from the
 *   command line as arguments therefore it explains why it failed;
 *   
 *   This software and documentation is the property of Intellon 
 *   Corporation, Ocala, Florida. It is provided 'as is' without 
 *   expressed or implied warranty of any kind to anyone for any 
 *   reason. Intellon assumes no responsibility or liability for 
 *   errors or omissions in the software or documentation and 
 *   reserves the right to make changes without notification. 
 *   
 *   Intellon customers may modify and distribute the software 
 *   without obligation to Intellon. Since use of this software 
 *   is optional, users shall bear sole responsibility and 
 *   liability for any consequences of it's use. 
 *
 *.  Intellon INT6000 Linux Toolkit for HomePlug AV;
 *:  Published 2006-2008 by Intellon Corp. ALL RIGHTS RESERVED;
 *;  For demonstration; Not for production use;
 *
 *   Contributor(s);
 *	Charles Maier <charles.maier@intellon.com>
 *
 *--------------------------------------------------------------------*/

#ifndef HPAVKEYSPEC_SOURCE
#define HPAVKEYSPEC_SOURCE

#include <ctype.h>

#include "../tools/error.h"
#include "../crypt/HPAVKey.h"

void HPAVKeySpec (const char * string) 

{
	const char * sp = string;
	while (isprint (*sp)) 
	{
		sp++;
	}
	if (*sp) 
	{
		error (1, ENOTSUP, "Phrase \"%s\" has illegal characters", string);
	}
	if ((sp - string) < HPAVKEY_PHRASE_MIN) 
	{
		error (1, ENOTSUP, "Phrase \"%s\" less than %d characters", string, HPAVKEY_PHRASE_MIN);
	}
	if ((sp - string) > HPAVKEY_PHRASE_MAX) 
	{
		error (1, ENOTSUP, "Phrase \"%s\" more than %d characters", string, HPAVKEY_PHRASE_MAX);
	}
	return;
}

#endif

