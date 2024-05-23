#pragma once
#include <string>
#include <memory>
#include <unordered_set>
class ObjectBase;
class ConnManage 
{
public:
	static ConnManage& getDefaultConnManage();

	virtual	~ConnManage();

	bool addConnsData(std::shared_ptr<ObjectBase>);

	std::shared_ptr<ObjectBase> getConnPtrBySrcId(std::string strSrcId);
	std::shared_ptr<ObjectBase> getConnPtrByDestId(std::string strDestId);
private:
	ConnManage();
private:
	std::unordered_set<std::shared_ptr<ObjectBase>> m_setConnData;
};