710. Hotel OO Design
中文English
The Hotel has two room type：SINGLE and DOUBLE

Using searchRequest() to search date and return the available rooms

It can support reservation

Users could also cancel reservation

Using LRUCache to store searching result, and using Cache for every search

Implement Hotel and Room , we will call printCacheto test the code.

Example
Hotel(4)
Room(1, "Single")
Room(2, "Single")
Room(3, "Double")
Room(4, "Double")
searchRequest("2013-01-01", "2013-10-10")
roomsNeeded("Single", 1)
roomsNeeded("Single", 1, "Double", 2)
roomsNeeded("Single", 1)
reservationRequest("2013-01-06", "2013-10-10", 2)
Printing Cache ...
Search Request -> Start date is: Jan 1, 2013 12:00:00 AM, End date is: Oct 10, 2013 12:00:00 AM
Value -> For room type: DOUBLE, available rooms are: 3; 4; . For room type: SINGLE, available rooms are: 1; 2; . 

*****************************

Printing Cache ...
Search Request -> Start date is: Jan 1, 2013 12:00:00 AM, End date is: Oct 10, 2013 12:00:00 AM
Value -> For room type: DOUBLE, available rooms are: 3; 4; . For room type: SINGLE, available rooms are: 1; 2; . 

Search Request -> Start date is: Jan 6, 2013 12:00:00 AM, End date is: Oct 10, 2013 12:00:00 AM
Value -> For room type: DOUBLE, available rooms are: . For room type: SINGLE, available rooms are: 1; 2; . 

*****************************
题目描述英文描述
Hotel目前有两种房间类型：SINGLE和DOUBLE

能够支持搜索，输入日期，返回能住的房间

能够支持预定

能够取消预定

使用LRUCache来储存搜索结果, 每次搜索时使用Cache

Hotel, Room 需要大家实现, 在函数searchRequest和reservationRequest(makeReservation)之后我们会调用printCache来验证程序的正确性。

在线评测地址: http://www.lintcode.com/problem/hotel-oo-design/


enum RoomType{DOUBLE, SINGLE};
class Hotel;
class Room;
class Reservation;
class SearchRequest;
class Date //时间类
{
private:
	int year, month, day;
	int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	string en[13] = { "","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
	bool is_LeapYear(int year)
	{
		return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	}

public:
	Date(int _year=0,int _month=0,int _day=0):year(_year),month(_month),day(_day){}

	Date(string str){
	    int index = 0, start = 0, len = str.size();
	    str = str.substr(1, str.size() - 2);
		vector<int> nums;
		while(index <= str.size()){
			if(index == str.size() || str[index] == '-'){
				nums.push_back(stoi(str.substr(start, index)));
				start = index + 1;
			}
			index++;
		}
		year = nums[0], month = nums[1], day = nums[2];
	}

	Date NextDay()
	{
		day++;
		int limit = days[month];
		if (is_LeapYear(year) && month == 2){
			limit++;
		}
		if (day > limit){
			day = 1;
			month++;
		}
		if (month > 12){
			year++; 
			month = 1;
		}
		return *this;
	}

	string toString()
	{
		string ret= en[month] + " ";
		ret += to_string(day) + ", " + to_string(year)+" 12:00:00 AM";
		return ret;
	}

	bool operator <(const Date& compare)const
	{
		if (year != compare.year){
			return year <compare.year;
		}

		if (month != compare.month){
			return month < compare.month;
		}

		return day < compare.day;
	}

	bool operator <=(const Date& compare)const
	{
		if (year != compare.year){
			return year <=compare.year;
		}

		if (month != compare.month){
			return month <= compare.month;
		}

		return day <= compare.day;
	}

	bool operator !=(const Date& compare)const
	{
		return year != compare.year|| month != compare.month|| day != compare.day;
	}

	bool operator ==(const Date& compare)const
	{
		return year && compare.year && month != compare.month && day != compare.day;
	}
};

class SearchRequest{
public:
	SearchRequest(Date startDate, Date endDate){
		this->startDate = startDate;
		this->endDate = endDate;
	}

	Date getStartDate(){
		return startDate;
	}

	Date getEndDate(){
		return endDate;
	}

	bool operator <(const SearchRequest & compare)const{
		if(startDate != compare.startDate){
			return startDate < compare.startDate;
		}
		return endDate < compare.endDate;
	}

	bool operator !=(const SearchRequest &compare)const{
		return startDate != compare.startDate || endDate != compare.endDate;
	}

	string toString(){
		return "Start date is: " + startDate.toString() + ", End date is: " + endDate.toString();
	}

private:
	Date startDate;
	Date endDate;
};

class Reservation{
public:
	Reservation(Date startDate, Date endDate){
		this->startDate = startDate;
		this->endDate = endDate;
		rooms = new vector<Room*>;
	}

	~Reservation(){
		delete rooms;
	}

	Date getStartDate(){
		return startDate;
	}

	Date getEndDate(){
		return endDate;
	}

	vector<Room*>* getRooms(){
		return rooms;
	}

private:
	Date startDate;
	Date endDate;
	vector<Room*>* rooms;
};


class Room{
public:
	Room(int id, RoomType roomType){

	}

	~Room(){
		
	}

	bool isValidRequest(SearchRequest *request){
		
	}

	void makeReservation(Date startDate, Date endDate){
		
	}

	void cancelReservation(Date startDate, Date endDate){
		
	}


	int getId(){
		
	}

	RoomType getRoomType(){
    
    }

private:
	int id;
	RoomType roomType;
	set<Date>* reservation;
};

class ReservationRequest{
public:
	ReservationRequest(Date startDate, Date endDate, map<RoomType, int>* roomsNeeded){
		this->startDate = startDate;
		this->endDate = endDate;
		this->roomsNeeded = roomsNeeded;
	}

	~ReservationRequest(){
		delete roomsNeeded;
	}

	Date getStartDate(){
		return startDate;
	}

	Date getEndDate(){
		return endDate;
	}

	map<RoomType, int> * getRoomsNeeded(){
		return roomsNeeded;
	}

private:
	Date startDate;
	Date endDate;
	map<RoomType, int>* roomsNeeded;
};



class LRUCache{
public:
	LRUCache(int capacity = 0){
		this->capacity = capacity;
		cache = new map<SearchRequest, map<RoomType, vector<Room*>*>*>;
	}

	~LRUCache(){
		delete cache;
	}

	void removeEldestEntry(){
		if(Que.size() > this->capacity){
			cache->erase(Que.front());
			Que.pop();
		}
	}

	void putEntry(SearchRequest searchRequest, map<RoomType, vector<Room*>*>* Data){
		if(cache->find(searchRequest) != cache->end()){
			queue<SearchRequest> temp;
			while(!Que.empty()){
				if(Que.front() 	!= searchRequest){
					temp.push(Que.front());
				}
				Que.pop();
			}
			Que = temp;
			Que.push(searchRequest);
			delete (*cache)[searchRequest];
		}
		else{
			Que.push(searchRequest);
		}
		(*cache)[searchRequest] = Data;
		removeEldestEntry();
	}

	map<RoomType, vector<Room*>*>* findCache(SearchRequest searchRequest){
		if(cache->find(searchRequest) != cache->end()){
			return (*cache)[searchRequest];
		}
		return NULL;
	}

	string printAvailableRooms(map<RoomType, vector<Room*>* >* rooms)
	{
		string ret = "";
		(*rooms)[DOUBLE];
		(*rooms)[SINGLE];
		for (auto it : (*rooms))
		{
		    string temp = "";
		    if(it.first == DOUBLE) temp = "DOUBLE";
		    else temp = "SINGLE";
			ret += "For room type: " + temp + ", available rooms are: ";
			if (it.second != NULL)
			{
				for (Room* room : (*it.second))
				{

					ret += to_string(room->getId()) + "; ";
				}
			}
			ret += ". ";
		}
		return ret;
	}

	string toString()
	{
		string ret = "";
		queue<SearchRequest>data(Que);
		while (!data.empty())
		{
			auto it = data.front();
			data.pop();
			ret += ("Search Request -> " + it.toString() + "\n");
			ret += ("Value -> " + printAvailableRooms((*cache)[it]) + "\n");
			ret += "\n";
		}

		return ret;
	}
private:
	int capacity;
	queue<SearchRequest>Que;
	map<SearchRequest, map<RoomType, vector<Room*>*>*>* cache;
};


class Hotel{
public:
	Hotel(int cacheSize){
		
	}

	~Hotel(){
		
	}

	void makeReservation(ReservationRequest* request)
	{
		
	}

	map<RoomType, vector<Room*>* >* handleSearchResult(SearchRequest *request){
		
	}

	void cancelReservation(Reservation* reservation){
		
	}

	vector<Room*> * getRooms(){
		
	}

	map<RoomType, vector<Room*>* >* getAvailableRooms(SearchRequest* request){
		
	}

	string printCache(){
		return "Printing Cache ...\n" + cache->toString() +
			"*****************************\n";
	}

private:
	vector<Room*>* rooms;
	LRUCache *cache;
};