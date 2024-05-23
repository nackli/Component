#pragma once
#include <string>
#include <memory>
#include "ObjectBase.h"
#include <stack>
#include "Value.h"
/**
 * connent class
*/
class ConnectAtom: public ObjectBase
{
public:
	ConnectAtom(std::string strConnsId,std::string strConnName);

	virtual	~ConnectAtom();

	void setSrcObject(std::shared_ptr<ObjectBase> pSrcPtr);

	void setDestObject(std::shared_ptr<ObjectBase> pDestPtr);

	std::shared_ptr<ObjectBase> getSrcObject() const;

	std::shared_ptr<ObjectBase>  getDestObject() const;

	bool addData(Value&);

	Value getData();
private:
	std::shared_ptr<ObjectBase> m_pSrcPtr;
	std::shared_ptr<ObjectBase> m_pDestPtr;
	std::stack<Value> m_sData;
};