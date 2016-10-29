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


/******************************************************************************
   版权所有 (C), 2008-2011, 华为技术有限公司

 ******************************************************************************
  文件名          : CLockGuard.cpp
  版本号          : 1.0
  作者            : 
  生成日期        : 2008-8-17
  最近修改        : 
  功能描述        : 实现智能锁功能
  函数列表        : 
  修改历史        : 
  1 日期          : 
    作者          : 
    修改内容      : 
*******************************************************************************/
#include "LockGuard.h"

CLockGuard::CLockGuard(VOS_Mutex *pMutex)
{
    m_pMutex = NULL;

    if(NULL == pMutex)
    {
        return;
    }

    m_pMutex = pMutex;

    (void)VOS_MutexLock(m_pMutex);
}

CLockGuard::~CLockGuard()
{
    if(NULL == m_pMutex)
    {
        return;
    }
    (void)VOS_MutexUnlock(m_pMutex);
    
    m_pMutex = NULL;
}

/*******************************************************************************
Function:       // CLockGuard::lock
Description:    // 加锁
Calls:          // 
Data Accessed:  // 
Data Updated:   // 
Input:          // VOS_Mutex *pMutex
Output:         // 无
Return:         // 无
Others:         // 无
*******************************************************************************/
void CLockGuard::lock(VOS_Mutex *pMutex)
{
    if(NULL == pMutex)
    {
        return;
    }
    (void)VOS_MutexLock(pMutex);
}

/*******************************************************************************
Function:       // CLockGuard::unlock
Description:    // 释放锁
Calls:          // 
Data Accessed:  // 
Data Updated:   // 
Input:          // VOS_Mutex *pMutex
Output:         // 无
Return:         // 无
Others:         // 无
*******************************************************************************/
void CLockGuard::unlock(VOS_Mutex *pMutex)
{
    if(NULL == pMutex)
    {
        return;
    }
    (void)VOS_MutexUnlock(pMutex);
}
