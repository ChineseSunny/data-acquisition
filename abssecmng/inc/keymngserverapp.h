
// keymngserverapp.h 

#include <iostream>
using namespace std;

#include "keymngserverabsop.h"

class KeyMngServerApp
{
	friend void *mystart_routine (void *arg2);
	
public:
	KeyMngServerApp();
	~KeyMngServerApp();
	
public:
	int setKeyMngServerOp(KeyMngServerAbsOp  *keyMngServerAbsOp);
	int setMngServerInfo(MngServer_Info  *mngServerInfo);
	
	//KeyMngServerOp  * getKeyMngServerOp();
	
public:
	 void  mysighandler_t2(int arg);
	
	
public:
	
	int init();
	int run();
	int exit();
	
private:
	KeyMngServerAbsOp  *m_keyMngServerAbsOp;
	MngServer_Info 	*m_mngServerInfo;
	
private:
	int 		m_listenfd;
	int 		g_EndTag2;
};

