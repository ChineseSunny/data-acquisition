

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <pthread.h>

#include "keymngclientapp.h"
#include "keymngclientabsop.h"




KeyMngClientApp::KeyMngClientApp()
{
	
}

KeyMngClientApp::~KeyMngClientApp()
{
	
}

int KeyMngClientApp::setKeyMngClientOp(KeyMngClientAbsOp  *keyMngClientabsOp)
{
	m_keyMngClientabsOp = keyMngClientabsOp;
	return 0 ;
}

int KeyMngClientApp::setMngClientInfo(MngClient_Info  *mngClientInfo)
{
	m_mngClientInfo = mngClientInfo;
	return 0 ;
}

	
int  KeyMngClientApp::init()
{
	//调用业务逻辑类 完成初始化
	m_keyMngClientabsOp->MngClient_InitInfo(this->m_mngClientInfo);
	
	return 0;
}

int KeyMngClientApp::Usage()
{
    int nSel = -1;
    
    system("clear");   
     
    printf("\n  /*************************************************************/");
    printf("\n  /*************************************************************/");
    printf("\n  /*     1.密钥协商                                            */");
    printf("\n  /*     2.密钥校验                                            */");
    printf("\n  /*     3.密钥注销                                            */");
    printf("\n  /*     4.密钥查看                                            */");
    printf("\n  /*     0.退出系统                                            */");
    printf("\n  /*************************************************************/");
    printf("\n  /*************************************************************/");
    printf("\n\n  选择:");

		scanf("%d",&nSel);
		while(getchar()!='\n');
   
    return nSel;
}


int KeyMngClientApp::run()
{
	int nSel = 0, ret = 0;
	while (1)
	{
		nSel =  Usage();
		switch (nSel)
		{
		case 1:	
			//调用密钥协商
			m_keyMngClientabsOp->MngClient_Agree(m_mngClientInfo);
			//ret = MngClient_Agree(&mngClientInfo);
			break;
		case 2:	
			//调用密钥校验
			//ret = MngClient_Check(m_mngClientInfo);
			break;
		case 3:	
			//调用密钥注销
			break;	
		case 4:	
			//查看本地没有
			break;
		case 0:	
			//退出
			return 0;
		default:
			printf("输入命令不支持\n");
			break;

		}
		
		if (ret)
		{
			printf("\n!!!!!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!");
			printf("\n错误码是：%x\n", ret);
		}
		else
		{
			printf("\n!!!!!!!!!!!!!!!!!!!!SUCCESS!!!!!!!!!!!!!!!!!!!!\n");
		}	
		getchar();
	}
	
	return 0;
}


int KeyMngClientApp::exit()
{
	return 0;
}
	
