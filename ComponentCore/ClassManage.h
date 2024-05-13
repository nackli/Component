#pragma once
#include <map>
#include <string>
#include <memory>
#include <mutex>
#include "ObjectClass.h"
#include "ObjectFactory.h"
class ClassManage
{
public:
	static ClassManage& getDefaultClassManage();

	static std::unique_ptr<ObjectClass> createObjectClass(std::string strClassName);

	void registerClass(const std::string strClassName, std::unique_ptr<ObjectFactory> objFactory);

	void unregisterClass();

	void unregisterClass(const std::string strClassName);

	bool initLoadClass(const std::string& strClassName, const std::string strLable,std::string strObjectName = std::string());

	std::unique_ptr<ObjectClass> GetObjectPrtFromLoadClass(const std::string strLable);
private:
	std::unique_ptr<ObjectClass> CreateObject(std::string strClassName);
	ClassManage() {};
	ClassManage(const ClassManage&) = delete;
	ClassManage(const ClassManage&&) = delete;;
	ClassManage& operator=(const ClassManage&) = delete;;
protected:
	std::map<std::string, std::unique_ptr<ObjectFactory>> m_mapClassManage;
	std::map<std::string, std::unique_ptr<ObjectClass>> m_mapClassLoad;
	mutable std::mutex internal_mutex_;

};

