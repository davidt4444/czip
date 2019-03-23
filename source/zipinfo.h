/* Header for holding data address and speid
   Programmer: Andy Anderson
*/

#ifndef __zipinfo_h__
#define __zipinfo_h__

#include <stdlib.h>

typedef union{
        unsigned long long ull;
        unsigned int ui[2];
}addr64;

typedef struct _control_block{
        int id;
        int name_size;
	addr64 address;
        unsigned char name[108];
}control_block;


#endif

