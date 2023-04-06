#include "json.h"
#include"parser.h"
#include <stdexcept>
using namespace std;

using namespace Json::json;
//构造函数
parser::parser():j_str(""),j_index(0) {
}
//析构函数
parser::~parser()
{
}
void parser::load(const string& str) {
	j_index = 0;
	j_str = str;
}


json parser::parse() {
	char ch = get_token();
	if (ch == 'n') {
		return parse_null();
	}
	if (ch == 't' || ch == 'f') {
		return parse_bool();
	}
	if (ch == '-' || (ch >= '0' && ch <= '9')) {
		return parse_number();
	}
	if (ch == '"') {
		return json(parse_string());
	}
	if (ch == '[') {
		return parse_array();
	}
	if (ch == '{') {
		return parse_object();
	}
	throw logic_error("unexpected char");
}


//跳过空格，换行符，
void parser::skip_white_space() {
	while (j_str[j_index] == ' ' || j_str[j_index] == '\n' || j_str[j_index] == '\r' || j_str[j_index] == '\t') {
		j_index++;
	}
}
//获取有效元素
char parser::get_token() {
	skip_white_space();
	//索引到头
	if (j_index == j_str.size()) {
		throw std::logic_error("unexpected end of input");
	}
	return j_str[j_index];
}

//null解析
json parser::parse_null() {
	if (j_str.compare(j_index,4,"null") == 0) {
		j_index += 4;//索引下移
		return json();
	}
	throw logic_error("parse_null error");
}
//bool解析
json parser::parse_bool() {
	if (j_str.compare(j_index, 4, "true") == 0) {
		j_index += 4;//索引下移
		return json(true);
	}
	if (j_str.compare(j_index, 5, "false") == 0) {
		j_index += 5;//索引下移
		return json(false);
	}
	throw logic_error("parse_bool error");
}
//数字解析
json parser::parse_number() {
	int pos = j_index;
	//跳过-号
	if (j_str[j_index] == '-') {
		j_index++;
	}
	//检测整数部分
	if (j_str[j_index] < '0' || j_str[j_index]>'9') {
		throw logic_error("parse_number error");
	}
	while (j_str[j_index] >= '0' && j_str[j_index] <= '9') {
		j_index++;
	}
	//是否为小数点
	if (j_str[j_index] != '.') {
		//转为整数
		int i = std::atoi(j_str.c_str() + pos);
		return json(i);
	}
	//检测小数部分
	j_index++;
	if (j_str[j_index] < '0' || j_str[j_index]>'9') {
		throw logic_error("parse_number error");
	}
	while (j_str[j_index] >= '0' && j_str[j_index] <= '9') {
		j_index++;
	}
	//转为浮点数
	double f = std::atof(j_str.c_str() + pos);
	return json(f);
}
//字符串解析
string parser::parse_string() {
	string str;
	j_index++;//从"移到第一个字符
	while (true) {
		if (j_index == j_str.size())
		{
			throw std::logic_error("unexpected end of input in string");
		}
		char ch = j_str[j_index++];
		//到字符串末尾"
		if (ch == '"') {
			return str;
		}
		//是否为\转义
		if (ch != '\\') {
			str += ch;
			continue;
		}
	}
}
json parser::parse_array() {
	json arr(json::json_array);
	j_index++;//从[移到第一个字符
	char ch = get_token();
	if (ch == ']') {
		return arr;
	}
	while (true) {
		arr.append(parse());
		ch = get_token();
		if (ch == ']') {
			j_index++;//移到]后一个字符
			return arr;
		}
		if (ch != ',') {
			throw std::logic_error("expected ',' in array");
		}
		j_index++;
	}
}
json parser::parse_object() {
	json obj(json::json_object);
	j_index++;//从{移到第一个字符
	char ch = get_token();
	if (ch == '}') {
		return obj;
	}
	while (true) {
		if (ch != '"') {
			throw std::logic_error("expected '\"' in object");
		}
		string key = parse_string();
		ch = get_token();
		if (ch != ':')
		{
			throw std::logic_error("expected ':' in object");
		}
		j_index++;//移到:下一个字符
		obj[key] = parse();
		ch = get_token();
		if (ch == '}') {
			j_index++;
			return obj;
		}
		if (ch != ',')
		{
			throw std::logic_error("expected ',' in object");
		}
		j_index++;//移到下一个"
		ch = get_token();
	}
}