// DevicePipeLineSystem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
/*
DevicePipelineSystem/
│
├── main.cpp
├── DeviceData.h
├── DeviceManager.h
│
├── processors/
│   ├── IDataProcessor.h
│   ├── PrintProcessor.h
│   ├── ErrorProcessor.h
│   ├── SaveProcessor.h
│
├── pipeline/
│   └── Pipeline.h
*/
#include <iostream>
#include "Pipeline.h"
#include "DeviceManager.h"
#include "IDataProcessor.h"
#include "ProcessorFactory.h"

//	// 1. 获取实例 (在这里工厂内部加了 () 完成了调用)
//	auto processor = factory.factory_func("print");
//	// 2. 使用实例处理数据
//	if (processor) 
//	{
//		processor->process(d1); // 真正干活的地方
//	}


int main()
{
	system("chcp 65001");;
	Logger::init();
	Logger::info("程序开始运行");
	//存储工业设备数据
	DeviceManager manager;

	DeviceData d1("device1", "25C", 100, "ok");
	DeviceData d2("device2", "30C", 200, "error");
	DeviceData d3("device3", "20C", 150, "ok");
	manager.add_DeviceData(d1);
	manager.add_DeviceData(d2);
	manager.add_DeviceData(d3);

	//管道1
	Pipeline pipeline1;
	pipeline1.add_processor(std::make_unique<PrintProcessor>());
	pipeline1.add_processor(std::make_unique<ErrorProcessor>());
	pipeline1.add_processor(std::make_unique<SaveProcessor>());

	manager.run(pipeline1);
	//管道2, 利用工厂模式 factory
	Pipeline pipeline2;
	ProcessorFactory factory;
	factory.register_processor("print", []() { return std::make_unique<PrintProcessor>(); });
	pipeline2.add_processor(factory.factory_func("print"));

	manager.run(pipeline2);

	Logger::info("程序结束运行");
	Logger::close();
}
