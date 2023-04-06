#pragma once
#include<string>
#include<vector>
#include<map>
using namespace std;


namespace Json {
	namespace json {
		class parser {
		public:
			//���캯��
			parser();
			//��������
			~parser();
			void load(const string& str);
			//��������
			json parse();

		private:
			void skip_white_space();//�����ո񣬻��з���
			char get_token();//��ȡ��ǰ��ЧԪ��
			json parse_null();//null����
			json parse_bool();//bool����
			json parse_number();//���ֽ���
			string parse_string();//�ַ�������
			json parse_array();
			json parse_object();
		private:
			string j_str;
			int j_index;
		};
	}
}