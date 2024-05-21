#pragma once
#include <map>
#include <string>
#include <memory>
#include <mutex>
#include "ObjectFactory.h"
class ObjectClass;
class Properties;
class ClassManage
{
public:
	static ClassManage& getDefaultClassManage();

	static std::shared_ptr<ObjectClass> createObjectClass(std::string strClassName);

	void registerClass(const std::string strClassName, std::unique_ptr<ObjectFactory> objFactory);

	void unregisterClass();

	void unregisterClass(const std::string strClassName);

	bool insertClass(const std::string&, const std::string&, const std::string&, std::shared_ptr<Properties>);

	bool insertClass(std::shared_ptr<ObjectClass>);

	std::shared_ptr<ObjectClass> GetObjectPrtFromLoadClass(const std::string strLable);

	bool initClassInfo();
private:
	std::shared_ptr<ObjectClass> CreateObject(std::string strClassName);
	ClassManage() {};
	ClassManage(const ClassManage&) = delete;
	ClassManage(const ClassManage&&) = delete;;
	ClassManage& operator=(const ClassManage&) = delete;;
protected:
	std::map<std::string, std::unique_ptr<ObjectFactory>> m_mapClassManage;
	std::map<std::string, std::shared_ptr<ObjectClass>> m_mapClassLoad;
	mutable std::mutex m_mutexUnternal;

};

