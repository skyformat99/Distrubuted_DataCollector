#pragma once

#include "DLMS46.h"
#include "DLMS47.h"
#include "DLMS47Ex.h"

#include <map>
#include <string>
#include <memory>
using namespace std;

class CProtocal100 : public IProtocalObject
{
public:

	CProtocal100();
	virtual ~CProtocal100();


	virtual bool InitObject(void* pDB) override;

	/*	根据协议类型封包

	@ pData: 对应tagTASKPacket结构体

	@ ret：成功：1 失败：0

	注：通过pData->szRecvData来解码。解码后的中间数据存入pData->szReturnData

	有连续帧收发的时候通过中间帧来继续进行编码。
	*/
	virtual bool EncodePacket(void* pTask) override;

	/* 解码。

	@ pData ：tagTask除了设备返回的数据外，还要包含终端的SN码，表计的SN码，任务的SN码

	@ ret：成功：1 失败：0

	注：通过pData->szRecvData来解码。解码后的中间数据存入pData->szSendData

	pData->szReturnData存入最终的结果数据。有连续帧收发的时候才需要保存中间帧。
	*/
	virtual bool DecodePacket(void* pData, UInt32 nDataLen, void* pTask) override;

private:

private:
	map<string, shared_ptr<CDLMS46>>	m_map46;
	map<string, shared_ptr<CDLMS47>>	m_map47;
	map<string, shared_ptr<CDLMS47Ex>>	m_map47Ex;

	IDBObject* m_pDB;
};