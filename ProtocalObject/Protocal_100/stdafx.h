// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "../pro_c62056/C62056.h"

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

#include "../../include/common.h"
#include "../../include/ProtocalInterFace.h"
#include "../../include/DBInterFace.h"
using namespace WSProtocalInterFace;
using namespace WSDBInterFace;



extern void HexStrToByteArray(const char* pHexStr, unsigned char* szByte, unsigned long& nSize);
extern bool OBISToHexStr(char* pOBIS, char* pHexStr);
extern void StrToHEXStr(const char* pStr, char* pHexStr, unsigned long& nSize);
extern bool StrIsDigit(char* pStr, int nLen);


// TODO: 在此处引用程序需要的其他头文件
