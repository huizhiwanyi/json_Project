#include<iostream>
#include<fstream>
#include<sstream>
#include "json.h"
using namespace std;
using namespace Json::json;

int main() {
	fstream f("C:/Users/zdy/Desktop/ad.json");
	stringstream ss;
	ss << f.rdbuf();
	const string& str = ss.str();
	json a;
	a.parse(str);
	int mid = a["data"]["wallet"]["mid"];
	cout << mid << endl;
	return 0;
}