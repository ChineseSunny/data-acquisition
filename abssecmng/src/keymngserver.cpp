
#include <iostream>
using namespace std;

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
//#include "poolsocket.h"


#include "keymngserverapp.h"
#include "keymnglog.h"
#include "keymngserverabsop.h"
#include "keymngserverop_lisi.h"

int mainxxx11()
{
	LogHelper::KeyMng_Log(__FILE__, __LINE__,LogHelper::KeyMngLevel[1], 0,"func main()  begin");
	printf("keymngserver -cpp hello.. .\n"); 
	LogHelper::KeyMng_Log(__FILE__, __LINE__,LogHelper::KeyMngLevel[1], 0,"func main()  end");
		
		
	return 0;	
}

#define INIT_DAEMON \
{ \
	if(fork() >0) exit(0); \
	setsid(); \
	if(fork()>0) exit(0); \
}

int main()
{
	int 	ret = 0;
	
	INIT_DAEMON
	
	//创建业务类对象
	KeyMngServerAbsOp  	*keyMngServerAbsOp = new KeyMngServerOp_LiSi;

	//创建一个配置信息类对象
	MngServer_Info			mngServerInfo;
	
	memset(&mngServerInfo, 0, sizeof(MngServer_Info));
	
	KeyMngServerApp		keyMngServerApp;
	
	keyMngServerApp.setKeyMngServerOp(keyMngServerAbsOp);
	keyMngServerApp.setMngServerInfo(&mngServerInfo);

	ret = keyMngServerApp.init();
	if (ret != 0)
	{
		printf("func keyMngServerApp.init() err:%d \n", ret);
		return ret;
	}
	keyMngServerApp.run();
	keyMngServerApp.exit();
	
	delete keyMngServerAbsOp;
	
	return 0;	
}