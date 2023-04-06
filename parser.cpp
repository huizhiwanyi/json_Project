#include "json.h"
#include"parser.h"
#include <stdexcept>
using namespace std;

using namespace Json::json;
//���캯��
parser::parser():j_str(""),j_index(0) {
}
//��������
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


//�����ո񣬻��з���
void parser::skip_white_space() {
	while (j_str[j_index] == ' ' || j_str[j_index] == '\n' || j_str[j_index] == '\r' || j_str[j_index] == '\t') {
		j_index++;
	}
}
//��ȡ��ЧԪ��
char parser::get_token() {
	skip_white_space();
	//������ͷ
	if (j_index == j_str.size()) {
		throw std::logic_error("unexpected end of input");
	}
	return j_str[j_index];
}

//null����
json parser::parse_null() {
	if (j_str.compare(j_index,4,"null") == 0) {
		j_index += 4;//��������
		return json();
	}
	throw logic_error("parse_null error");
}
//bool����
json parser::parse_bool() {
	if (j_str.compare(j_index, 4, "true") == 0) {
		j_index += 4;//��������
		return json(true);
	}
	if (j_str.compare(j_index, 5, "false") == 0) {
		j_index += 5;//��������
		return json(false);
	}
	throw logic_error("parse_bool error");
}
//���ֽ���
json parser::parse_number() {
	int pos = j_index;
	//����-��
	if (j_str[j_index] == '-') {
		j_index++;
	}
	//�����������
	if (j_str[j_index] < '0' || j_str[j_index]>'9') {
		throw logic_error("parse_number error");
	}
	while (j_str[j_index] >= '0' && j_str[j_index] <= '9') {
		j_index++;
	}
	//�Ƿ�ΪС����
	if (j_str[j_index] != '.') {
		//תΪ����
		int i = std::atoi(j_str.c_str() + pos);
		return json(i);
	}
	//���С������
	j_index++;
	if (j_str[j_index] < '0' || j_str[j_index]>'9') {
		throw logic_error("parse_number error");
	}
	while (j_str[j_index] >= '0' && j_str[j_index] <= '9') {
		j_index++;
	}
	//תΪ������
	double f = std::atof(j_str.c_str() + pos);
	return json(f);
}
//�ַ�������
string parser::parse_string() {
	string str;
	j_index++;//��"�Ƶ���һ���ַ�
	while (true) {
		if (j_index == j_str.size())
		{
			throw std::logic_error("unexpected end of input in string");
		}
		char ch = j_str[j_index++];
		//���ַ���ĩβ"
		if (ch == '"') {
			return str;
		}
		//�Ƿ�Ϊ\ת��
		if (ch != '\\') {
			str += ch;
			continue;
		}
	}
}
json parser::parse_array() {
	json arr(json::json_array);
	j_index++;//��[�Ƶ���һ���ַ�
	char ch = get_token();
	if (ch == ']') {
		return arr;
	}
	while (true) {
		arr.append(parse());
		ch = get_token();
		if (ch == ']') {
			j_index++;//�Ƶ�]��һ���ַ�
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
	j_index++;//��{�Ƶ���һ���ַ�
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
		j_index++;//�Ƶ�:��һ���ַ�
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
		j_index++;//�Ƶ���һ��"
		ch = get_token();
	}
}