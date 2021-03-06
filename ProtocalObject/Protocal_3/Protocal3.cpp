#include "stdafx.h"
#include "protocal3.h"

static CProtocal3 s_ProtocalOBJ;
__PROTOCAL_INTERFACE_API bool CreateProtocalObject(IProtocalObject** pProtocalObject)
{
	*pProtocalObject = &s_ProtocalOBJ;
	return true;
}

CProtocal3::CProtocal3()
{
	;
}

CProtocal3::~CProtocal3()
{
	;
}


bool CProtocal3::InitObject(IDBObject* pDB)
{
	return true;
}

/*	根据协议类型封包

@ pData: 对应tagTASKPacket结构体

@ ret：成功：1 失败：0

注：通过pData->szRecvData来解码。解码后的中间数据存入pData->szSendData

有连续帧收发的时候通过中间帧来继续进行编码。
*/
bool CProtocal3::EncodePacket(void* pTask)
{
	return true;
}

/* 解码。

@ pData ：tagTask除了设备返回的数据外，还要包含终端的SN码，表计的SN码，任务的SN码

@ ret：成功：1 失败：0

注：通过pData->szRecvData来解码。解码后的中间数据存入pData->szSendData

pData->szReturnData存入最终的结果数据。有连续帧收发的时候才需要保存中间帧。
*/
bool CProtocal3::DecodePacket(void* pData, UInt32 nDataLen, void* pTask)
{
	return true;
}