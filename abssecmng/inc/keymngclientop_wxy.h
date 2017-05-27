#pragma once

// keymngclientabsop.h

class KeyMngClientOp_WXY : public KeyMngClientAbsOp
{
public:
	//初始化客户端 全局变量
	
	virtual int MngClient_InitInfo(MngClient_Info *pCltInfo);
	
	virtual int MngClient_Quit(MngClient_Info *pCltInfo);
	
	virtual int MngClient_Agree(MngClient_Info *pCltInfo);
	
	virtual int MngClient_Check(MngClient_Info *pCltInfo);
	
	virtual int MngClient_Revoke(MngClient_Info *pCltInfo);
	
	virtual int MngClient_view(MngClient_Info *pCltInfo);
};

