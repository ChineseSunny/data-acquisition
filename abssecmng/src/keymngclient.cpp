
#include <iostream>
using namespace std;

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

#include "keymnglog.h"
#include "keymngclientapp.h"

#include "keymngclientabsop.h"

#include "keymngclientop_wxy.h"
#include "keymng_msg.h"
#include "keymngclientop_sunny.h"

int mainxxxx()
{
	
	LogHelper::KeyMng_Log(__FILE__, __LINE__,LogHelper::KeyMngLevel[1], 1,"func 11111");	
	LogHelper::KeyMng_Log(__FILE__, __LINE__,LogHelper::KeyMngLevel[0], 0,"func 0000000000000");
	LogHelper::KeyMng_Log(__FILE__, __LINE__,LogHelper::KeyMngLevel[1], 1,"func 1111111111111() err");
	LogHelper::KeyMng_Log(__FILE__, __LINE__,LogHelper::KeyMngLevel[2], 2,"func 2222222222222() err");
	LogHelper::KeyMng_Log(__FILE__, __LINE__,LogHelper::KeyMngLevel[3], 3,"func 333333333() err");
	LogHelper::KeyMng_Log(__FILE__, __LINE__,LogHelper::KeyMngLevel[4], 4,"func 4444444444444 () err");

	cout << "keymngclient cpp hello...\n";	
	return 0;
}

int Abs_WXY()
{
			KeyMngClientAbsOp *keyMngClientAbsOp = new KeyMngClientOp_WXY;
			
			MngClient_Info 	mngClientInfo;
			KeyMngClientApp 	keyMngClientApp;
			
			memset(&mngClientInfo, 0, sizeof(mngClientInfo));
			
			keyMngClientApp.setKeyMngClientOp(keyMngClientAbsOp);
			
			keyMngClientApp.setMngClientInfo(&mngClientInfo);
		
			int ret = keyMngClientApp.init();
			if (ret != 0)
			{
				printf("初始化err:%d\n", ret);
				return ret;
			}
			
			printf("初始化ok\n");
			
			keyMngClientApp.run();
			keyMngClientApp.exit();
		
			delete keyMngClientAbsOp;
			return 0;
}

int Abs_SUNNY()
{
			KeyMngClientAbsOp *keyMngClientAbsOp = new KeyMngClientOp_SUNNY;
			
			MngClient_Info 	mngClientInfo;
			KeyMngClientApp 	keyMngClientApp;
			
			memset(&mngClientInfo, 0, sizeof(mngClientInfo));
			
			keyMngClientApp.setKeyMngClientOp(keyMngClientAbsOp);
			
			keyMngClientApp.setMngClientInfo(&mngClientInfo);
		
			int ret = keyMngClientApp.init();
			if (ret != 0)
			{
				printf("初始化err:%d\n", ret);
				return ret;
			}
			
			printf("初始化ok\n");
			
			keyMngClientApp.run();
			keyMngClientApp.exit();
		
			delete keyMngClientAbsOp;
			
			return 0;
}

int Usage()
{
	printf("选择1，则用WXY的方案，选择2则用SUNNY的方案\n");
	
	int num = -1;
	
	scanf("%d",&num);
	
	//while(getchar()!='\n');
	
	getchar();
	
	return num;
}

int main()
{
	int nSel = 0, ret = 0;
	
	nSel =  Usage();

	switch (nSel)
	{
		case 1:
			//选用WXY方案
			ret = Abs_WXY();
			break;
		case 2:
			ret = Abs_SUNNY();
			break;
	}
}
