
// keymngclient.h 

#include <iostream>
using namespace std;


//#include "keymngclientinfo.h"
//#include "keymngclientbaseop.h"

#include "keymngclientabsop.h"
#include "keymngclientop_wxy.h"
#include "keymngclientop_sunny.h"

class KeyMngClientApp
{
public:
	KeyMngClientApp();
	~KeyMngClientApp();
	
public:
	int setKeyMngClientOp(KeyMngClientAbsOp  *keyMngClientabsOp);
	int setMngClientInfo(MngClient_Info  *mngClientInfo);
	
	
public:
	int Usage();
	int init();
	int run();
	int exit();
	
private:
	KeyMngClientAbsOp  *m_keyMngClientabsOp;
	MngClient_Info 	*m_mngClientInfo;
};