#pragma once
#include <map>
#include <string>
#include <memory>
#include <mutex>
#include "ObjectClass.h"
class ObjectFactory;
class ClassManage
{
public:
	static ClassManage& getDefaultClassManage();

	static std::unique_ptr<ObjectClass> createObjectClass(std::string strClassName);

	explicit ClassManage();

	void registerClass(const std::string strClassName, std::unique_ptr<ObjectFactory> objFactory);

	void unregisterClass();

	void unregisterClass(const std::string strClassName);

	std::unique_ptr<ObjectClass> CreateObject(std::string strClassName);

protected:
	std::map<std::string, std::unique_ptr<ObjectFactory>> m_mapClassManage;
	mutable std::mutex internal_mutex_;

};

