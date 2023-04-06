#include "json.h"
#include"parser.h"
#include <stdexcept>
#include<sstream>
using namespace std;

using namespace Json::json;


//构造函数实现
//默认构造函数
json::json() :j_type(json_null),j_bool(false),j_int(0),j_double(0.0) {

}
//int构造函数
json::json(int value) :j_type(json_int) {
	j_int = value;
}
//double构造函数
json::json(double value) : j_type(json_double) {
	j_double = value;
}
//bool构造函数
json::json(bool value) : j_type(json_bool) {
	j_bool = value;
}
//c char构造函数
json::json(const char* value) : j_type(json_string) {
    j_string =value;
}
//string 构造函数
json::json(const string& value) : j_type(json_string) {
	j_string =value;
}
//json构造函数
json::json(const json& value) {
	copy(value);
}
//type构造函数
json::json(type value) : j_type(value) {
	switch (j_type)
	{
	case json_null:
		break;
	case json_int:
		j_int = 0;
		break;
	case json_double:
		j_double = 0.0;
		break;
	case json_bool:
		j_bool = false;
		break;
	default:
		break;
	}
}
//析构函数
Json::json::json::~json()
{
	clear(); //调用clear函数清理
}
//类型转换运算符
json::operator bool(){
	if (j_type != json_bool) {
		throw logic_error("type error,not bool value");
	}
	return j_bool;
}
json::operator int() {
	if (j_type != json_int) {
		throw logic_error("type error,not int value");
	}
	return j_int;
}
json::operator double() {
	if (j_type != json_double) {
		throw logic_error("type error,not double value");
	}
	return j_double;
}
json::operator string() {
	if (j_type != json_string) {
		throw logic_error("type error,not string value");
	}
	return j_string;
}
//数组[]运算符重载
json& json::operator [](int index) {
	if (j_type == json_null) {
		j_type = json_array;
	}
	//判断类型
	if (j_type != json_array) {
		throw std::logic_error("function Json::operator [int] requires array value");
	}
	int size = j_array.size();
	//判断索引是否合法
	if (index < 0)
	{
		throw std::logic_error("function Json::operator [int] index less 0");
	}
	if (index > 0 && index < size)
	{
		return j_array.at(index);
	}
	//需要扩容
	if (index >= size)
	{
		for (int i = size; i <= index; i++)
		{
			j_array.push_back(json());
		}
	}
	return j_array.at(index);
}
////字典[]重载
json& json::operator[](const char* key)
{
	// TODO: 在此处插入 return 语句
	string name(key);
	return (*this)[name];//调用operator [](const string& key)
}
json& json::operator[](const string& key)
{
	// TODO: 在此处插入 return 语句
	if (j_type == json_null) {
		j_type = json_object;
	}
	//判断类型
	if (j_type != json_object) {
		throw std::logic_error("function Json::operator [const string &] requires object value");
	}
	return (j_object)[key];
}
//运算符重载
void json::operator =(const json& value) {
	copy(value);
}
bool json::operator ==(const json& value) {
	if (j_type != value.j_type) {
		return false;
	}
	switch (j_type)
	{
	case json_null:
		return true;
		break;
	case json_bool:
		return j_bool == value.j_bool;
		break;
	case json_int:
		return j_int == value.j_int;
		break;
	case json_double:
		return j_double == value.j_double;
		break;
	case json_string:
		return j_string == value.j_string;
		break;
	}
}
bool json::operator !=(const json& value) {
	return !((*this) == value);
}
bool json::operator <(const json& value) {
	if (j_type != value.j_type) {
		return false;
	}
	switch (j_type)
	{
	case json_int:
		return j_int < value.j_int;
		break;
	case json_double:
		return j_double < value.j_double;
		break;
	}
}
bool json::operator <=(const json& value) {
	if (j_type != value.j_type) {
		return false;
	}
	switch (j_type)
	{
	case json_int:
		return j_int <= value.j_int;
		break;
	case json_double:
		return j_double <= value.j_double;
		break;
	}
}
bool json::operator >(const json& value) {
	if (j_type != value.j_type) {
		return false;
	}
	switch (j_type)
	{
	case json_int:
		return j_int > value.j_int;
		break;
	case json_double:
		return j_double > value.j_double;
		break;
	}
}
bool json::operator >=(const json& value) {
	if (j_type != value.j_type) {
		return false;
	}
	switch (j_type)
	{
	case json_int:
		return j_int >= value.j_int;
		break;
	case json_double:
		return j_double >= value.j_double;
		break;
	}
}
//append函数实现
void json::append(const json& value) {
	//检查类型
	if (j_type == json_null) {
		j_type = json_array;
	}
	if (j_type != json_array) {
		throw logic_error("function Json::append() requires array value");
	}
	j_array.push_back(value);
}
//str()函数实现
string json::str() const {
	stringstream ss;
	switch (j_type)
	{
	case json_null:
		ss << "null";
		break;
	case json_bool:
		if (j_bool == true) {
			ss << "ture";
		}
		else if (j_bool == false)
		{
			ss << "false";
		}
		break;
	case json_int:
		ss << j_int;
		break;
	case json_double:
		ss << j_double;
		break;
	case json_string:
		ss << '\"' << j_string << '\"';
		break;
	case json_array:
		ss << "[";
		for (auto begin = j_array.begin(); begin != j_array.end(); begin++) {
			if (begin != j_array.begin()) {
				ss << ',';
			}
			ss << begin->str();
		}
		ss << "]";
		break;
	case json_object:
		ss << "{";
		for (auto begin = j_object.begin(); begin != j_object.end(); begin++) {
			if (begin != j_object.begin()) {
				ss << ',';
			}
			ss << '\"' << begin->first << '\"' << ':' << begin->second.str();
		}
		ss << "}";
		break;
	default:
		break;
	}
	return ss.str();
}
//根据index删除数组元素
bool json::remove(const int index) {
	if (j_type != json_array) {
		return false;
	}
	//判断index合法性
	if (index < 0 || index >= j_array.size()) {
		return false;
	}
	j_array.erase(j_array.begin() + index);
	return true;
}
//根据key删除object
bool json::remove(const char* key) {
	string v(key);
	return remove(v);
}
bool json::remove(const string& key) {
	if (j_object.find(key) == j_object.end()) {
		return false;
	}
	j_object.erase(key);
	return true;
}
//copy()函数
void json::copy(const json& value)
{
	clear();//先清理

	j_type = value.j_type;

	switch (value.j_type)
	{
	case json_null:
		break;
	case json_int:
		j_int = value.j_int;
		break;
	case json_double:
		j_double = value.j_double;
		break;
	case json_bool:
		j_bool = value.j_bool;
		break;
	case json_string:
		j_string = value.j_string;
		break;
	case json_array:
		j_array = value.j_array;
		break;
	case json_object:
		j_object = value.j_object;
		break;
	default:
		break;
	}
}
//clear()函数
void json::clear()
{
	j_int = 0;
	j_double = 0.0;
	j_bool = false;
	j_string.clear();
	j_array.clear();
	j_object.clear();
}
//定义迭代器
json::iterator json::begin() {
	return j_array.begin();
}
json::iterator json::end() {
	return j_array.end();
}

//返回type
json::type Json::json::json::jsontype()
{
	return j_type;
}
//返回size
int Json::json::json::size()
{
	switch (type())
	{
	case json_array:
		return j_array.size();
	case json_object:
		return j_object.size();
	default:
		break;
	}
	throw std::logic_error("function Json::size value type error");
}
//检验empty
bool Json::json::json::empty()
{
	switch (type())
	{
	case json_null:
		return true;
	case json_array:
		return j_array.empty();
	case json_object:
		return j_object.empty();
	default:
		break;
	}
	throw std::logic_error("function Json::empty value type error");
}


//解析函数
void json::parse(const string& str) {
	parser p;
	p.load(str);
	*this = p.parse();
}