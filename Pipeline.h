#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include<memory>
#include "DeviceData.h"
#include "IDataProcessor.h"
//using namespace std;
/*
把:pipeline.add(std::make_unique<PrintProcessor>());变成：pipeline.add(factory.create("print"));
✔ main 不关心具体类
✔ 可以动态扩展
✔ 更像真实系统
*/
class Pipeline
{
private:
	//std::vector<std::reference_wrapper<IDataProcessor> > processors; // 存储数据处理器的列表
	std::vector<std::unique_ptr<IDataProcessor> > processors; // 存储数据处理器的列表
public:
	void add_processor(std::unique_ptr<IDataProcessor> p)
	{
		processors.emplace_back(std::move(p));
	}

	void execute(DeviceData& data)
	{
		for (auto& processor : processors)
		{
			if (!processor->process(data))
				break;
		}
	}
	
};

