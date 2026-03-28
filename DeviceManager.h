#pragma once
#include<vector>
#include<iostream>
#include<functional>
#include"DeviceData.h"
#include"IDataProcessor.h"
#include"Pipeline.h"
#include"Logger.h"
//using namespace std;
using std::vector;
class DeviceManager
{
private:
	std:: vector<DeviceData> deviceDataList; // 存储设备数据的列表
public:
	void add_DeviceData(const DeviceData& data)//添加设备数据
	{
		deviceDataList.emplace_back(data);
	}
	void process_data(IDataProcessor& processor)//处理数据
	{
		for (auto& data : deviceDataList)
		{
			processor.process(data);
		}
	}
	//自己正在跨入流程设计（Pipeline思维）
	void process_All(vector<std::reference_wrapper<IDataProcessor> > pile)// 一个数据经过所有 Processor 
	{
		for(auto& data:deviceDataList)
		{
			for (auto& processor : pile)
			{
				//if (!processor.get().process(data))  break;
				if (!processor.get().process(data))
				{
					Logger::error("pipeline中断了!");
					return;
				}
			}
			std::cout << "成功处理设备" << data.getID() << "的数据\n";
		}
	}
	
	void run(Pipeline& pile)
	{
		Logger::info("设备数据开始读取");
		for (auto& data : deviceDataList)
		{
			pile.execute(data);
		}
		Logger::info("设备数据处理完成");
	}
};
/*
1 DeviceManager
职责：
存数据
遍历数据
调用流程
2️Pipeline
职责：
存 Processor
控制执行顺序
控制中断
3️Processor
职责：
实施具体数据处理行为
*/
