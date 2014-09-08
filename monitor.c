/*
 * UTF - Universal Tethetered FORTH
 *
 * (C) 2012 - Kevin Haddock
 * All Rights Reserved
 * This software is distributed according to the:
 *	GNU LESSER GENERAL PUBLIC LICENSE
 * A copy of which can be found online at the following URL:
 *  http://www.gnu.org/licenses/lgpl.html
 *
 * Monitor.c - UFW's one word tether.
 *
 * This code is as of yet untested, use at your own risk!
 * In many cases, this one word tether may have to be hand
 * coded in assembly and is provded here as a working model
 * to pattern your own asembly code after.
 */


#include <stdio.h>

/* 64 k words should be enough to start */

#define MEMSIZE 65535

typedef union {
   void *loc;
  int data;
} ram;

ram mem[MEMSIZE];

int idx, val;

int main(void) {

 begin:

  /* make the first memory location point to this mainline */

  mem[0].loc = &&begin;

  /* first, get the memory location */

  fread(&idx, sizeof (idx), 1,  stdin);

  /* then get the value to put there */

  fread (&val, sizeof(val), 1, stdin);

  /* then send up the value that is currently there */

  fwrite(&mem[idx], sizeof(val), 1, stdout);
  
  /* then set that location to that value */

  mem[idx].data = val;
  
  /* now jump to the address at mem[0] (which initially points to main()) */
  
   goto *mem[0].loc;

   return (0);  /* never reached, but to shut the compiler up */
}
