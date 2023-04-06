#pragma once
#include<string>
#include<vector>
#include<map>
using namespace std;

namespace Json {
	namespace json {
		class json {
		public:
			//定义json类型
			enum type 
			{
				json_null=0,
				json_int,
				json_double,
				json_bool,
				json_string,
				json_array,
				json_object
			};
			//构造函数
			json();//默认构造函数
			json(int value);//int构造函数
			json(double value);//double构造函数
			json(bool value);//bool构造函数
			json(const char* value);//c char构造函数
			json(const string& value);//string 构造函数
			json(const json& value);//json构造函数
			json(type value);//type构造函数

			//析构函数
			~json();

			//重载运算符
			operator bool();//类型转换
			operator int();
			operator double();
			operator string();
			json& operator [](int index);//数组[]重载
			json& operator [](const char* key);//字典[]重载(char)
			json& operator [](const string& key);//字典[]重载(string)
			void operator =(const json& value);
			bool operator ==(const json& value);
			bool operator !=(const json& value);
			bool operator <(const json& value);
			bool operator <=(const json& value);
			bool operator >(const json& value);
			bool operator >=(const json& value);
			//数组尾部添加数据
			void append(const json& value);
			//转为string输出
			string str() const;
			//根据index删除数组元素json
			bool remove(const int index);
			//根据key删除j_object
			bool remove(const char* key);
			bool remove(const string& key);
			//copy()函数
			void copy(const json& value);
			//clear()函数
			void clear();
			//定义迭代器
			typedef std::vector<json>::iterator iterator;
			iterator begin();
			iterator end();
			//返回type
			type jsontype();
			//返回size
			int size();
			//检验empty
			bool empty();
			//解析函数
			void parse(const string& str);

		private:
			//定义json存储
			int j_int;
			double j_double;
			bool j_bool;
			std::string j_string;
			std::vector<json> j_array;
			std::map<std::string, json> j_object;
			type j_type;//标识json类型
		};
	}
}
