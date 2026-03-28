#pragma once
#include<iostream>
#include<string>
#include<ctime>
#include<fstream>
class Logger//不需要状态,只充当一个工具类
{
private:
	inline static std::ofstream outFile;//用于类的静态数据成员，表示该成员在头文件中既是声明又是定义
public:
	static void init()
	{
		outFile.open("log.txt",std::ios::app);
		if (outFile.is_open())
		{
			outFile << "日志文件初始化成功\n";
			outFile.flush();
		}
		else
		{
			std::cout << "无法创建日志文件\n";
		}
	}
	static std::string curr_time()  //静态函数不允许使用类型限定符
	{
		std::time_t now = time(nullptr);
		struct tm local;
		localtime_s(&local, &now);
		char buf[64];
		strftime(buf, sizeof(buf),"%Y-%m-%d %H:%M:%S",&local);
		return std::string(buf);
	}
	static void error(const std::string& message) 
	{
		std::string line = "[ERROR]:" + message + "\n";
		std::cout << line;
		if (outFile.is_open())
		{
			outFile << line;
		}
	}
	static void info(const std::string& message)
	{
		std::string line = "[INFO]:" + message + "\n";
		std::cout << line;
		if (outFile.is_open())
		{
			outFile << line;
		}
	}
static void close()
{
	if (outFile.is_open())
	{
		outFile.close();
	}
}	

};

