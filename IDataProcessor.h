#pragma once
#include<iostream>
#include<fstream>
#include"DeviceData.h"
#include"Logger.h"
class IDataProcessor
{
public:
	virtual bool process(DeviceData& data) = 0;//纯虚函数，要求派生类必须实现)
	virtual ~IDataProcessor() = default;//虚析构函数，确保派生类对象被正确销毁
};
/*
├── PrintProcessor.h
├── ErrorProcessor.h
├── SaveProcessor.h
*/
class PrintProcessor :public IDataProcessor
{
	bool process(DeviceData& data) override
	{
		if (data.getStatus() == "error")
		{
			Logger::error("设备" + data.getID() + "在" + Logger::curr_time() + "发生错误，数据值为" + std::to_string(data.getData()));
			return false;
		}
		else if(data.getStatus() == "ok")
		{
			Logger::info("设备" + data.getID() + "在" + Logger::curr_time() + "状态正常，数据值为" + std::to_string(data.getData()));
			return true;
		}

		return true;
	}
};
class ErrorProcessor :public IDataProcessor
{
	bool process(DeviceData& data) override
	{
		if (data.getStatus() == "error")
		{

			//std::cout << "ErrorProcessor检测到错误数据: " << data << "\n";
			//std::cout << "设备ID: " << data.getID() << ", 数据值: " << data.getData() << ", 状态: " << data.getStatus() << "\n";
			return false;
		}
		else
		{
			std::cout << "ErrorProcessor未检测到错误数据: " << data << "\n";
			std::cout << "设备ID: " << data.getID() << ", 数据值: " << data.getData() << ", 状态: " << data.getStatus() << "\n";
		}
		return true;
	}
};
class SaveProcessor :public IDataProcessor
{
	bool process(DeviceData& data) override
	{
		std:: ofstream outFile("data.txt", std::ios::out);
		if (outFile.is_open())
		{
			std::cout << "文件打开成功" << "\n";
			outFile << "设备ID" << data.getID() << ",数据值:" << data.getData() << ",状态:" << data.getStatus() << "\n";
		}
		else
		{
			std::cout << "文件打开失败" << "\n";
			return false;
		}
		outFile.close();
		return true;
	}
};

