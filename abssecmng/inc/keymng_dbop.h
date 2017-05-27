
// keymng_dbop.h
#ifndef _KEYMNG_DBOP_H_
#define _KEYMNG_DBOP_H_

#include <iostream>

//#include "keymngserverop.h"
#include "keymng_shmop.h"


class KeyMngDBOp
{
public:	
	static int KeyMngsvr_DBOp_GenKeyID(void *dbhdl, int *keyid);
	
	static int KeyMngsvr_DBOp_WriteSecKey(void *dbhdl, NodeSHMInfo *pNodeInfo); 
	
	static int KeyMngsvr_DBOp_upKeyStatus(void *dbdl, int keysn );
};





#endif



