#pragma once
#include<string>
#include<vector>
#include<map>
using namespace std;


namespace Json {
	namespace json {
		class parser {
		public:
			//构造函数
			parser();
			//析构函数
			~parser();
			void load(const string& str);
			//解析函数
			json parse();

		private:
			void skip_white_space();//跳过空格，换行符，
			char get_token();//获取当前有效元素
			json parse_null();//null解析
			json parse_bool();//bool解析
			json parse_number();//数字解析
			string parse_string();//字符串解析
			json parse_array();
			json parse_object();
		private:
			string j_str;
			int j_index;
		};
	}
}