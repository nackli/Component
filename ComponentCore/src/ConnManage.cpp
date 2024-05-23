/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/

#include "ConnManage.h"
#include <typeinfo>
#include <memory>
#include "StringUtils.h"
#include "ConnectAtom.h"
#ifndef WIN32
#include <cxxabi.h>
#endif
/**
 * @brief 
*/
ConnManage& ConnManage::getDefaultConnManage() {
	static ConnManage ret;
	return ret;
}

ConnManage::ConnManage() :m_setConnData()
{
}
/**
 * @brief 
*/
ConnManage::~ConnManage()
{
}

bool ConnManage::addConnsData(std::shared_ptr<ObjectBase> objCons)
{
	auto insertRet = m_setConnData.insert(objCons);
	return insertRet.second;
}

std::shared_ptr<ObjectBase> ConnManage::getConnPtrBySrcId(std::string strSrcId)
{
	auto test = std::find_if(m_setConnData.begin(), m_setConnData.end(),
		[strSrcId](std::shared_ptr<ObjectBase> first){ 
			std::shared_ptr<ConnectAtom> pTemp = std::static_pointer_cast<ConnectAtom>(first);
			std::string strConnSrcId = pTemp->getSrcObject()->getObjectId();
			return strConnSrcId.compare(strSrcId) == 0;
		});
	if(test != m_setConnData.end())
		return *test;
	return nullptr;
}
/**
 * @brief 
 * @param strDestId 
 * @return 
*/
std::shared_ptr<ObjectBase> ConnManage::getConnPtrByDestId(std::string strDestId)
{
	auto test = std::find_if(m_setConnData.begin(), m_setConnData.end(),
		[strDestId](std::shared_ptr<ObjectBase> first) {
			std::shared_ptr<ConnectAtom> pTemp = std::static_pointer_cast<ConnectAtom>(first);
			if (pTemp->getDestObject())
			{
				std::string strConnSrcId = pTemp->getDestObject()->getObjectId();
				return strConnSrcId.compare(strDestId) == 0;
			}
			return false;
		});
	if (test != m_setConnData.end())
		return *test;
	return nullptr;
}
