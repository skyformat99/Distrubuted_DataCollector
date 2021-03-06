
#include "stdafx.h"
#include "protocal100.h"

static CProtocal100 s_ProtocalOBJ;
__PROTOCAL_INTERFACE_API bool CreateProtocalObject(WSProtocalInterFace::IProtocalObject** pProtocalObject)
{
	*pProtocalObject = &s_ProtocalOBJ;
	return true;
}

CProtocal100::CProtocal100()
{
	;
}

CProtocal100::~CProtocal100()
{
	;
}


bool CProtocal100::InitObject(void* pDB)
{
	m_pDB = (IDBObject*)pDB;
	return true;
}

/*	根据协议类型封包

@ pData: 对应tagTASKPacket结构体

@ ret：成功：1 失败：0

注：通过pData->szRecvData来解码。解码后的中间数据存入pData->szSendData

有连续帧收发的时候通过中间帧来继续进行编码。
*/
bool CProtocal100::EncodePacket(void* pTask)
{
	bool bRet = false;
	WSCOMMON::PTASKPACKET pPacket = (WSCOMMON::PTASKPACKET)pTask;

	if (pPacket->cMeterType == 20 || pPacket->cMeterType == 21)
	{
		// 20 单相表协议 21 三相表协议
		map<string, shared_ptr<CDLMS47Ex>>::iterator iter;
		iter = m_map47Ex.find(pPacket->szSNTask);
		if (iter != m_map47Ex.end())
		{
			bRet = iter->second->EncodePacket(pTask, m_pDB);
		}
		else
		{
			CDLMS47Ex* pDLMS47ex = new CDLMS47Ex();
			shared_ptr<CDLMS47Ex> spDlMS47ex(pDLMS47ex);
			m_map47Ex.insert(make_pair(pPacket->szSNTask, spDlMS47ex));
			bRet = pDLMS47ex->EncodePacket(pTask, m_pDB);
		}
	}
	else if (pPacket->cMeterType == 22)
	{
		// 标准46 协议
		map<string, shared_ptr<CDLMS46>>::iterator iter;
		iter = m_map46.find(pPacket->szSNTask);
		if (iter != m_map46.end())
		{
			bRet = iter->second->EncodePacket(pTask);
		}
		else
		{
			CDLMS46* pDLMS46 = new CDLMS46();
			shared_ptr<CDLMS46> spDlMS46(pDLMS46);
			m_map46.insert(make_pair(pPacket->szSNTask, spDlMS46));
			bRet = pDLMS46->EncodePacket(pTask);
		}
	}
	else if (pPacket->cMeterType == 23)
	{
		// 标准47 协议
		map<string, shared_ptr<CDLMS47>>::iterator iter;
		iter = m_map47.find(pPacket->szSNTask);
		if (iter != m_map47.end())
		{
			bRet = iter->second->EncodePacket(pTask);
		}
		else
		{
			CDLMS47* pDLMS47 = new CDLMS47();
			shared_ptr<CDLMS47> spDlMS47(pDLMS47);
			m_map47.insert(make_pair(pPacket->szSNTask, spDlMS47));
			bRet = pDLMS47->EncodePacket(pTask);
		}
	}

	return bRet;
}

/* 解码。

@ pData ：tagTask除了设备返回的数据外，还要包含终端的SN码，表计的SN码，任务的SN码

@ ret：成功：1 失败：0

注：通过pData->szRecvData来解码。解码后的中间数据存入pData->szSendData

pData->szReturnData存入最终的结果数据。有连续帧收发的时候才需要保存中间帧。
*/
bool CProtocal100::DecodePacket(void* pData, UInt32 nDataLen, void* pTask)
{
	bool bRet = false;
	WSCOMMON::PTASKPACKET pPacket = (WSCOMMON::PTASKPACKET)pTask;

	if (pPacket->cMeterType == 20 || pPacket->cMeterType == 21)
	{
		// 20 单相表协议 21 三相表协议
		map<string, shared_ptr<CDLMS47Ex>>::iterator iter;
		iter = m_map47Ex.find(pPacket->szSNTask);
		if (iter != m_map47Ex.end())
		{
			bRet = iter->second->DecodePacket((const char*)pData, nDataLen, pTask);
			if (pPacket->cStatus == 4)
			{
				// 整个协议过程结束
				m_map47Ex.erase(iter);
			}
		}
	}
	else if (pPacket->cMeterType == 22)
	{
		// 标准46 协议
		map<string, shared_ptr<CDLMS46>>::iterator iter;
		iter = m_map46.find(pPacket->szSNTask);
		if (iter != m_map46.end())
		{
			bRet = iter->second->DecodePacket((const char*)pData, nDataLen, pTask);
			if (pPacket->cStatus == 4)
			{
				// 整个协议过程结束
				m_map46.erase(iter);
			}
		}
	}
	else if (pPacket->cMeterType == 23)
	{
		// 标准47 协议
		map<string, shared_ptr<CDLMS47>>::iterator iter;
		iter = m_map47.find(pPacket->szSNTask);
		if (iter != m_map47.end())
		{
			bRet = iter->second->DecodePacket((const char*)pData, nDataLen, pTask);
			if (pPacket->cStatus == 4)
			{
				// 整个协议过程结束
				m_map47.erase(iter);
			}
		}
	}

	return bRet;
}
