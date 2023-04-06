#pragma once
#include<string>
#include<vector>
#include<map>
using namespace std;

namespace Json {
	namespace json {
		class json {
		public:
			//����json����
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
			//���캯��
			json();//Ĭ�Ϲ��캯��
			json(int value);//int���캯��
			json(double value);//double���캯��
			json(bool value);//bool���캯��
			json(const char* value);//c char���캯��
			json(const string& value);//string ���캯��
			json(const json& value);//json���캯��
			json(type value);//type���캯��

			//��������
			~json();

			//���������
			operator bool();//����ת��
			operator int();
			operator double();
			operator string();
			json& operator [](int index);//����[]����
			json& operator [](const char* key);//�ֵ�[]����(char)
			json& operator [](const string& key);//�ֵ�[]����(string)
			void operator =(const json& value);
			bool operator ==(const json& value);
			bool operator !=(const json& value);
			bool operator <(const json& value);
			bool operator <=(const json& value);
			bool operator >(const json& value);
			bool operator >=(const json& value);
			//����β���������
			void append(const json& value);
			//תΪstring���
			string str() const;
			//����indexɾ������Ԫ��json
			bool remove(const int index);
			//����keyɾ��j_object
			bool remove(const char* key);
			bool remove(const string& key);
			//copy()����
			void copy(const json& value);
			//clear()����
			void clear();
			//���������
			typedef std::vector<json>::iterator iterator;
			iterator begin();
			iterator end();
			//����type
			type jsontype();
			//����size
			int size();
			//����empty
			bool empty();
			//��������
			void parse(const string& str);

		private:
			//����json�洢
			int j_int;
			double j_double;
			bool j_bool;
			std::string j_string;
			std::vector<json> j_array;
			std::map<std::string, json> j_object;
			type j_type;//��ʶjson����
		};
	}
}
