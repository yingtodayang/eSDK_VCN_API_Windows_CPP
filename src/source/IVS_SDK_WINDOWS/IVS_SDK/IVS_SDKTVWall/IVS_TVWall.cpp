/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

// IVS_SDKTVWall.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "IVS_TVWall.h"
#include "TVWallService.h"
#include "bp_log.h"
#include "bp_def.h"
// 初始化电视上墙模块SDK
IVS_INT32 __stdcall IVS_TVWall_Init(PCUMW_CALLBACK_NOTIFY pFunNotifyCallBack, void* pUserData)
{
	int iRet = IVS_FAIL;
	iRet = CTVWallService::GetInstance()->InitTVWallService(pFunNotifyCallBack, pUserData);
	return iRet;
}

// 释放电视上墙模块
IVS_INT32 __stdcall IVS_TVWall_Release()
{
	int iRet = IVS_FAIL;
	iRet = CTVWallService::GetInstance()->ReleaseTVWallService();
	return iRet;
}


// 初始化远程解码器
IVS_INT32 __stdcall IVS_TVWall_InitBusiness(IPI_INIT_BUSINESS_REQ* pParaInfo)
{
    int iRet = IVS_FAIL;
	CHECK_POINTER(pParaInfo, IVS_TVWALL_MEMORY_NULL);
    CTVWallService* pTVWallService = CTVWallService::GetInstance();
	CHECK_POINTER(pTVWallService, IVS_TVWALL_MEMORY_NULL);
    iRet = pTVWallService->IniBusiness(pParaInfo);
    return iRet;
}

// 初始化远程解码器
IVS_INT32 __stdcall IVS_TVWall_ReInitBusiness(IPI_INIT_BUSINESS_REQ* pParaInfo)
{
	int iRet = IVS_FAIL;
	CHECK_POINTER(pParaInfo, IVS_TVWALL_MEMORY_NULL);
	CTVWallService* pTVWallService = CTVWallService::GetInstance();
	CHECK_POINTER(pTVWallService, IVS_TVWALL_MEMORY_NULL);
	iRet = pTVWallService->ReIniBusiness(pParaInfo);
	return iRet;
}

// 命令远程解码器开始解码
IVS_INT32 __stdcall IVS_TVWall_StartBusiness(IPI_START_BUSINESS_REQ* pParaInfo)
{
	int iRet = IVS_FAIL;
	CHECK_POINTER(pParaInfo, IVS_TVWALL_MEMORY_NULL);
	CTVWallService* pTVWallService = CTVWallService::GetInstance();
	CHECK_POINTER(pTVWallService, IVS_TVWALL_MEMORY_NULL);
    iRet = pTVWallService->StartBusiness(pParaInfo);
    return iRet;
}

// 命令远程解码器重新开始解码
IVS_INT32 __stdcall IVS_TVWall_ReStartBusiness(IPI_START_BUSINESS_REQ* pParaInfo)
{
	int iRet = IVS_FAIL;
	CHECK_POINTER(pParaInfo, IVS_TVWALL_MEMORY_NULL);
	CTVWallService* pTVWallService = CTVWallService::GetInstance();
	CHECK_POINTER(pTVWallService, IVS_TVWALL_MEMORY_NULL);
	iRet = pTVWallService->ReStartBusiness(pParaInfo);
	return iRet;
}

// 命令远程解码器停止解码
IVS_INT32 __stdcall IVS_TVWall_StopBusiness(IPI_STOP_BUSINESS_REQ* pParaInfo)
{
	int iRet = IVS_FAIL;
	CHECK_POINTER(pParaInfo, IVS_TVWALL_MEMORY_NULL);
	CTVWallService* pTVWallService = CTVWallService::GetInstance();
	CHECK_POINTER(pTVWallService, IVS_TVWALL_MEMORY_NULL);
    iRet = pTVWallService->StopBusiness(pParaInfo);
    return iRet;
}

/*
// 播放/停止播放声音
IVS_INT32 __stdcall IVS_TVWall_PlayAudio(IPI_AUDIO_CONTROL_REQ *pParaInfo)
{
    //int iRet = IVS_FAIL;
    //CHECK_POINTER(pParaInfo, IVS_TVWALL_MEMORY_NULL);
    //CTVWallService* pTVWallService = CTVWallService::GetInstance();
    //CHECK_POINTER(pTVWallService, IVS_TVWALL_MEMORY_NULL);
    //iRet = pTVWallService->PlayAudio(pParaInfo);
    //return iRet;
    
    return IVS_SYS_NO_SUPPORT;
}

// 设置音量
IVS_INT32 __stdcall IVS_TVWall_SetVolume(IPI_TUNEUP_VOLUME_REQ* pParaInfo)
{
    //int iRet = IVS_FAIL;
    //CHECK_POINTER(pParaInfo, IVS_TVWALL_MEMORY_NULL);
    //CTVWallService* pTVWallService = CTVWallService::GetInstance();
    //CHECK_POINTER(pTVWallService, IVS_TVWALL_MEMORY_NULL);
    //iRet = pTVWallService->SetVolume(pParaInfo);
    //return iRet;

    return IVS_SYS_NO_SUPPORT;
}
*/


