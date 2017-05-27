
#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <pthread.h>

#include "keymngserverapp.h"
#include "poolsocket.h"
#include "icdbapi.h"
//#include "keymngclientop.h"


int g_EndTag = 0;
KeyMngServerApp::KeyMngServerApp()
{
	
}

KeyMngServerApp::~KeyMngServerApp()
{
	
}


 
int KeyMngServerApp::setKeyMngServerOp(KeyMngServerAbsOp  *keyMngServerAbsOp)
{
	m_keyMngServerAbsOp = keyMngServerAbsOp;
	return 0 ;
}


int KeyMngServerApp::setMngServerInfo(MngServer_Info  *mngServerInfo)
{
	m_mngServerInfo = mngServerInfo;
	return 0 ;
}



void mysighandler_t(int arg)
 {
 	printf("func mysighandler_t() begin arg:%d\n", arg);
 	g_EndTag = 1;
 	//keyMngServerApp.g_EndTag = 0; 在这个全局函数中 无法获取keyMngServerApp类的对象 无法给对象属性赋值
 	
 	printf("func mysighandler_t() end\n");
 	
 	return ;
 }
 
 
 //void  mysighandler_t2(KeyMngServerApp *this, int arg)
 
 void  KeyMngServerApp::mysighandler_t2(int arg)
 {
 	printf("func mysighandler_t() begin arg:%d\n", arg);
 	g_EndTag2 = 1;
 	//keyMngServerApp.g_EndTag = 0; 在这个全局函数中 无法获取keyMngServerApp类的对象 无法给对象属性赋值
 	
 	printf("func mysighandler_t() end\n");
 	return ;
 }
 	
int  KeyMngServerApp::init()
{
	int			ret = 0;
	//安装一个信号处理函数
	//signal(SIGUSR1, mysighandler_t); //告诉linux内核 当有人向我发送用户自定义信号1的时候 请你调用myfunc api函数

	//signal(SIGUSR1, reinterpret_cast<void (*)(int)>(&KeyMngServerApp::mysighandler_t2) );
	signal(SIGUSR1, mysighandler_t );
	signal(SIGPIPE, SIG_IGN); //告诉linux内核 当有管道破裂时候 ，请你不要在发送SIGPIPE 让1.exe死掉 请你忽略
	
	
	//初始化服务器 全局变量	
	ret = m_keyMngServerAbsOp->MngServer_InitInfo(m_mngServerInfo);
	if (ret != 0)
	{
		printf("func MngServer_InitInfo() err:%d \n", ret);
		return ret;
	}
	
	ret =  sckServer_init(m_mngServerInfo->serverport, &m_listenfd);
	if (ret != 0)
	{
		printf("func sckServer_init() err:%d \n", ret);
		return ret;	
	}

	return ret;
}

struct ThreadInfo
{
	KeyMngServerApp *keyMngServerApp;
	int 		connfd;
};

//需要使用app中的业务操作类op对象, /配置信息类的对象, 连接connetfd
void *mystart_routine (void *arg)
{
	
	
	int 					ret = 0;
	int 					connfd = 0;
	int 					mytimeout = 3;
	
	//接受的客户端的请求报文 编码以后的结果
	unsigned char 			*out = NULL;
	int 					outlen = 0;
		
		
	//客户端请求报文数据结构
	MsgKey_Req				*pMsgKeyReq = NULL;
	int 					iMsgKeyReq = 0;
	
	//服务器应答报文 编码以后的结果
	unsigned char 			*pMsgKey_ResData = NULL;
	int 					iMsgKey_ResDataLen = 0;
	
	ThreadInfo				*pTmpThreadInfo = NULL;	
	
	KeyMngServerApp 		*keyMngServerApp = NULL;  

	
	pTmpThreadInfo = reinterpret_cast<ThreadInfo *>(arg);
	
	keyMngServerApp = pTmpThreadInfo->keyMngServerApp;
	connfd = pTmpThreadInfo->connfd;
	
	while (1)
	{
		if (g_EndTag ==1)
		{
			break;
		}
		out = NULL;
		outlen = 0;
		
		//客户端请求报文数据结构
		pMsgKeyReq = NULL;
		iMsgKeyReq = 0;
		
		//服务器应答报文 编码以后的结果
		pMsgKey_ResData = NULL;
		iMsgKey_ResDataLen = 0;
	
		
		//服务器端端接受报文
		//异常情况 1对方已经关闭 2 出错 3 超时
		ret =  sckServer_rev(connfd, mytimeout, &out, &outlen); //1 sck_FreeMem((void ** )&out);
		if (ret == Sck_ErrPeerClosed)
		{
			printf("服务端监测出 客户端已经关闭\n");
			break;	
		}
		else if (ret == Sck_ErrTimeOut)
		{
			goto End;	
		}
		else if (ret != 0)
		{
			printf("func sckServer_rev() err:%d \n", ret);
			break;
		}
	

		//2 解析客户端的请求报文
		ret = MsgDecode(out, outlen, (void **)&pMsgKeyReq, &iMsgKeyReq); //2  MsgMemFree((void **) &pMsgKeyReq, iMsgKeyReq);
		if (ret != 0)
		{
			printf("func MsgDecode() err:%d \n", ret);
			goto End;
		}

		//3 cmdType 123
		switch (pMsgKeyReq->cmdType)
		{
		case KeyMng_NEWorUPDATE:
			//密钥协商应答
			//keyMngServerApp->getKeyMngServerOp()->MngServer_Agree(&mngServerInfo, pMsgKeyReq, &pMsgKey_ResData, &iMsgKey_ResDataLen);
			ret = keyMngServerApp->m_keyMngServerAbsOp->MngServer_Agree(keyMngServerApp->m_mngServerInfo, pMsgKeyReq, &pMsgKey_ResData, &iMsgKey_ResDataLen); //3 MsgMemFree( (void **) &pMsgKey_ResData, 0);
			break;
		case KeyMng_Check:
			//密钥校验
			ret = keyMngServerApp->m_keyMngServerAbsOp->MngServer_Check(keyMngServerApp->m_mngServerInfo, pMsgKeyReq, &pMsgKey_ResData, &iMsgKey_ResDataLen); 
			break;
		case KeyMng_Revoke:
			//密钥注销
			break;	
		default:
			ret = MngSvr_ParamErr;
			break;		
			
		}
		if  (ret != 0)
		{
			printf("服务器端业务流处理失败 err:%d .\n",ret);
			//MsgKey_Res			msgKeyRes;
			//msgKeyRes
			//msgKeyRes.rv = 200;
			//sckServer_send(connfd, mytimeout, pMsgKey_ResData, iMsgKey_ResDataLen);
			goto End;	
		}
	
		//服务器端发送报文
		ret = sckServer_send(connfd, mytimeout, pMsgKey_ResData, iMsgKey_ResDataLen);
		if (ret == Sck_ErrPeerClosed)
		{
			printf("服务端监测出 客户端已经关闭\n");
			break;	
		}
		else if (ret == Sck_ErrTimeOut)
		{
			goto End;	
		}
		else if (ret != 0)
		{
			sck_FreeMem((void ** )&out);
			printf("func sckServer_rev() err:%d \n", ret);
			break;
		}
	
	End:
			if (out) 				sck_FreeMem((void ** )&out);
			if (pMsgKeyReq)			MsgMemFree((void **) &pMsgKeyReq, iMsgKeyReq);
			if (pMsgKey_ResData)	MsgMemFree( (void **) &pMsgKey_ResData, 0);
	}		
	
	if (out) 				sck_FreeMem((void ** )&out);
	if (pMsgKeyReq)			MsgMemFree((void **) &pMsgKeyReq, iMsgKeyReq);
	if (pMsgKey_ResData)	MsgMemFree( (void **) &pMsgKey_ResData, 0);


	sckServer_close(connfd);
	
	free(pTmpThreadInfo);
	return NULL;
}

/* 
int KeyMngServerApp::mystart_routine()
{
}
*/


int KeyMngServerApp::run()
{
	//函数声明
	//服务器端初始化
	int 	ret = 0;
	int 		connfd = 0;
	int 		mytime = 3;
	pthread_t	pid;
	
	

	
	while (1)
	{
		if (g_EndTag == 1)
		{
			break;
		}
		ret = sckServer_accept(m_listenfd, mytime, &connfd);
		if (ret == Sck_ErrTimeOut)
		{
			printf("func sckServer_accept() 检测到内核中没有连接 \n ");
			continue;
		}
		
		ThreadInfo  *pTmpThreadInfo = (ThreadInfo *)malloc(sizeof(ThreadInfo));
		pTmpThreadInfo->keyMngServerApp = this;
		pTmpThreadInfo->connfd = connfd;
		
       pthread_create(&pid,  NULL, mystart_routine, (void *)pTmpThreadInfo);

	}
	
	
	return 0;
}


int KeyMngServerApp::exit()
{
	sleep(2);
	
	//释放资源
	sckClient_closeconn(m_listenfd);
	//服务器端环境释放 
	sckServer_destroy();
	
	//释放数据库连接池
	IC_DBApi_PoolFree();
	
	return 0;
}
	
