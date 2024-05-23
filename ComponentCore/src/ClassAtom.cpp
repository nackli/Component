/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/

#include "ClassAtom.h"
#include <typeinfo>
#include "StringUtils.h"
#include "Properties.h"
#include "ConnManage.h"
#include <iostream>
#include "ConnectAtom.h"
#ifndef WIN32
#include <cxxabi.h>
#endif
/**
 * @brief 
*/
ClassAtom::ClassAtom() :ObjectBase(), Properties()
{

}

ClassAtom::~ClassAtom()
{
}

bool ClassAtom::initClassAtom()
{ 
	if(getTypeClass() == ObjectBase::TYPE_IN)
		m_connObject = ConnManage::getDefaultConnManage().getConnPtrBySrcId(getObjectId());
	else if(getTypeClass() == ObjectBase::TYPE_OUT)
		m_connObject = ConnManage::getDefaultConnManage().getConnPtrByDestId(getObjectId());
	else
		std::cout << "Current Class unConnect Info" << std::endl;
	this->initObject();
	return true; 
};

bool  ClassAtom::writeData(Value vData)
{
	if (getTypeClass() == ObjectBase::TYPE_IN)
	{
		std::shared_ptr<ConnectAtom> pTemp = std::static_pointer_cast<ConnectAtom>(m_connObject);
		return pTemp->addData(vData);
	}
	return false;
}

Value ClassAtom::readData()
{
	if (getTypeClass() == ObjectBase::TYPE_OUT)
	{
		std::shared_ptr<ConnectAtom> pTemp = std::static_pointer_cast<ConnectAtom>(m_connObject);
		return pTemp->getData();
	}
	return Value();
}