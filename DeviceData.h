#pragma once

#include <string>
#include<time.h>
#include <iostream>
#include <vector>
#include <fstream>
using std::string;
using std::ostream;
using std::istream;

class DeviceManager;

class DeviceData
{
public:
    // 构造函数
    DeviceData(string id, string temp, int y, string status_message)
    {
        std:: cout << "DeviceData构造函数调用了\n";
        ID = id;
        t = time(nullptr);
        temperature = temp;
        data = y;
        status = status_message;
    }

    DeviceData(int y, string status)
    {
        std::cout << "未知设备在未知温度下生成数据\n";
        ID = "NULL";
        t = time(nullptr);
        temperature = "unknown";
        data = y;
        this->status = status;
    }

    // 拷贝构造
    DeviceData(const DeviceData& df)
    {
        std::cout << "拷贝构造函数调用了\n";
        ID = df.ID;
        t = time(nullptr);
        temperature = df.temperature;
        data = df.data;
        status = df.status;
    }

    ~DeviceData()
    {
        std::cout << "DeviceData析构函数调用了\n";
    }

    // 获取当前时间
  //  void curr_time()
  //  {
		//time_t now = time(nullptr);
  //      struct tm* p =localtime(&now);
		//char* time_str = asctime(p);
  //      //time_t now = time(nullptr);
  //      //struct tm* local_time = localtime(&now);
  //      //char* time_str = asctime(local_time);
  //      std::cout << "当前时间为: " << time_str;
  //  }
    std::string curr_time() const
    {
		time_t now = time(nullptr);
		struct tm tm_buf {};
		localtime_s(&tm_buf, &now);
        char buf[64];
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm_buf);

		return std::string(buf);
		//tm tm_buf{};

    }

    // 获取 data
    int operator()() const { return data; }

    // 修改 data
    DeviceData& operator()(int d)
    {
        data = d;
        return *this;
    }

    // 输入输出
    friend istream& operator>>(istream& is, DeviceData& df)
    {
        is >> df.ID >> df.t >> df.temperature >> df.data >> df.status;
        return is;
    }

    friend ostream& operator<<(ostream& os, const DeviceData& df)
    {
        os << df.ID << " " << df.t << " "
            << df.temperature << " " << df.data << " " << df.status;
        return os;
    }
    //In my opinions,these original codes were meaningless
    // // 比较
    // bool operator==(const DeviceData& other)
    // {
    //     return (status == other.status) && (data == other.data);
    // }

    // bool operator!=(const DeviceData& other)
    // {
    //     return !(*this == other);
    // }

    // bool operator<(const DeviceData& other)
    // {
    //     if (data != other.data)
    //         return data < other.data;
    //     return ID < other.ID;
    // }

    // bool operator>(const DeviceData& other)
    // {
    //     if (data != other.data)
    //         return data > other.data;
    //     return ID > other.ID;
    // }

    // bool operator>=(const DeviceData& other)
    // {
    //     return (*this > other) || (*this == other);
    // }

    // bool operator<=(const DeviceData& other)
    // {
    //     return (*this < other) || (*this == other);
    // }

    friend DeviceManager;

   //数据获取的接口
    string getID() const { return ID; }
    int getData() const { return data; }
    string getStatus() const { return status; }

private:
    string ID;
    time_t t;
    string temperature;
    int data;
    string status;
};

