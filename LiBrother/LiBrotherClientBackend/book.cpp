#include "book.h"
#include "netclient.h"
#include <json/json.h>
CBook::CBook() : m_CBBI(nullptr) {}
CBook::~CBook() {
	if (m_CBBI) delete m_CBBI;
}
bool CBook::getBasicInfo(TBookBasicInfo& info)
{
	/*if (!m_CBBI) m_CBBI = new TBookBasicInfo;
	Json::Value value0;
	value0["command"] = "getBasicInfo";
	value0["bookid"] = m_Id;
	Json::FastWriter writer;
	std::string strRequest;
	std::string strRespond;
	strRequest = writer.write(value0);
	sendRequest(strRequest, strRespond);//respnod contains 4 elements
	Json::Reader reader;
	Json::Value value;
	reader.parse(strRespond, value);
	m_CBBI->id = m_Id;
	m_CBBI->author = value["author"].asString();
	m_CBBI->count = value["count"].asInt();
	m_CBBI->isbn = value["isbn"].asString();
	m_CBBI->name = value["name"].asString();
	m_CBBI->publisher = value["publisher"].asString();
	if (!check(*m_CBBI))
	{
		setError(InvalidParam, 1, "This book is not valid.");
		return false;
	}
	info = *m_CBBI;*/
	info = * m_CBBI;
	return true;
}

bool CBook::getDescription(std::string& description)
{
	Json::Value value0;
	value0["command"] = "book_getDescription";
	value0["id"] = m_Id;
	Json::FastWriter writer;
	std::string strRequest;
	std::string strRespond;
	strRequest = writer.write(value0);
	sendRequest(strRequest, strRespond);//respnod contains 1 elements
	Json::Reader reader;
	Json::Value value;
	reader.parse(strRespond, value);
	m_Description = value["description"].asString();
		description = m_Description;
		return true;
}

bool CBook::setBasicInfo(const TBookBasicInfo& info)
{
	*m_CBBI = info;
	Json::Value value0;
	value0["command"] = "book_setBasicInfo";
	value0["id"] = m_CBBI->id;
	value0["count"] = m_CBBI->count;
	value0["name"] = m_CBBI->name;
	value0["publisher"] = m_CBBI->publisher;
	value0["author"] = m_CBBI->author;
	value0["isbn"] = m_CBBI->isbn;
	Json::FastWriter writer;
	std::string strRequest;
	std::string strRespond;
	strRequest = writer.write(value0);
	sendRequest(strRequest, strRespond);//respnod contains result as key
	Json::Reader reader;
	Json::Value value;
	reader.parse(strRespond, value);
	if(value["result"].asInt() == 1) return true;
	return false;
}

bool CBook::setDescription(const char * description)
{
	if (!description)
	{
		setError(InvalidParam, 4, "The pointer is NULL.");
		return false;
	}
	m_Description = description;
	Json::Value value0;
	value0["command"] = "book_setDescription";
	value0["id"] = m_Id;
	value0["description"] = m_Description;
	Json::FastWriter writer;
	std::string strRequest;
	std::string strRespond;
	strRequest = writer.write(value0);
	sendRequest(strRequest, strRespond);//respnod contains result as key
	Json::Reader reader;
	Json::Value value;
	reader.parse(strRespond, value);
	if (value["result"].asInt() == 1) return true;
	return false;
}

bool CBook::deleteBook(int number) 
{
	Json::Value value0;
	value0["command"] = "book_deleteBook";
	value0["id"] = m_Id;
	value0["number"] = number;
	Json::FastWriter writer;
	std::string strRequest;
	std::string strRespond;
	strRequest = writer.write(value0);
	sendRequest(strRequest, strRespond);
	Json::Reader reader;
	Json::Value value;
	reader.parse(strRespond, value);
	if (value["result"].asInt() == 1)  return true;//lots of error types to be handled
	return false;
}

bool CBook::getBorrowInfo(std::vector<TBorrowInfo> &binfo)
{
	Json::Value value0;
	value0["command"] = "book_getBorrowInfo";
	value0["id"] = m_Id;
	Json::FastWriter writer;
	std::string strRequest;
	std::string strRespond;
	strRequest = writer.write(value0);
	sendRequest(strRequest, strRespond);
	Json::Reader reader;
	Json::Value value;
	reader.parse(strRespond, value);
	int num = value["result"].asInt();
	if (num>0) {
		for (int i = 1; i <= num; i++) {
			Json::Value tem_value = value["1"];
			TBorrowInfo borrow_info;
			borrow_info.bookID = tem_value["bookID"].asInt();
			borrow_info.userID = tem_value["userID"].asInt();
			borrow_info.borrowTime = tem_value["borrowTime"].asInt64();
			borrow_info.flag = tem_value["flag"].asBool();
			binfo.push_back(borrow_info);
		}
		return true;
	}
	return false;
}