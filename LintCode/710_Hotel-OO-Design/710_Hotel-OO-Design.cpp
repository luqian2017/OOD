
enum RoomType{DOUBLE, SINGLE};
class Hotel;
class Room;
class Reservation;
class SearchRequest;

string InttoString(int x)
{
    std::stringstream ss;
	string ans;
	ss << x;
	ss >> ans;
	return ans;
}


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

	Date NextDay()
	{
		day++;
		int limit = days[month];
		if (is_LeapYear(year) && month == 2)
		{
			limit++;
		}
		if (day > limit)
		{
			day = 1;
			month++;
		}
		if (month > 12)
		{
			year++; 
			month = 1;
		}
		return *this;
	}

	string toString()
	{
		string ret= en[month] + " ";
		ret += InttoString(day) + ", " + InttoString(year)+" 12:00:00 AM";
		return ret;
	}

	bool operator <(const Date& compare)const
	{
		if (year != compare.year)
		{
			return year <compare.year;
		}
		if (month != compare.month)
		{
			return month < compare.month;
		}
		return day < compare.day;
	}

	bool operator <=(const Date& compare)const
	{
		if (year != compare.year)
		{
			return year <=compare.year;
		}
		if (month != compare.month)
		{
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

class SearchRequest  //搜索需求
{
private:
	Date startDate;
	Date endDate;

public:
	SearchRequest(Date startDate, Date endDate)
	{
		this->startDate = startDate;
		this->endDate = endDate;
	}

	Date getStartDate()
	{
		return startDate;
	}

	Date getEndDate()
	{
		return endDate;
	}

	bool operator <(const SearchRequest &compare)const
	{
		if (startDate != compare.startDate)
		{
			return startDate < compare.startDate;
		}
		return endDate < compare.endDate;

	}

	bool operator !=(const SearchRequest &compare)const
	{
		return startDate != compare.startDate||endDate != compare.endDate;
	}

	string toString()
	{
		return "Start date is: " + startDate.toString() + ", End date is: " + endDate.toString();
	}

};



class Room   //房间类
{
private:
	int id;
	string roomType;
	set<Date>* reservations;

public:
	Room(int id, string roomType)
	{
		this->id = id;
		this->roomType = roomType;
		reservations = new set<Date>;
	}

	~Room()
	{
		delete reservations;
	}

	bool isValidRequest(SearchRequest* request)
	{
		Date Date = request->getStartDate();
		while (Date <= request->getEndDate())
		{
			if (reservations->find(Date) != reservations->end())
			{
				return false;
			}
			Date = Date.NextDay();
		}
		return true;
	}

	void makeReservation(Date startDate, Date endDate)
	{
		Date Date = startDate;
		while (Date < endDate)
		{
			reservations->insert(Date);
			Date = Date.NextDay();
		}
	}

	void cancelReservation(Date startDate, Date endDate)
	{
		Date Date = startDate;
		while (Date.NextDay() < endDate)
		{
			if (reservations->find(Date) != reservations->end())
			{
				reservations->erase(Date);
			}
			Date = Date.NextDay();
		}
	}

	int getId()
	{
		return this->id;
	}

	string getRoomType()
	{
		return roomType;
	}
};

class ReservationRequest  //预定请求类
{
private:
	Date startDate;
	Date endDate;
	map<string, int>* roomsNeeded;

public:
	ReservationRequest(Date startDate, Date endDate, map<string, int>* roomsNeeded)
	{
		this->startDate = startDate;
		this->endDate = endDate;
		this->roomsNeeded = roomsNeeded;
	}

	~ReservationRequest()
	{
		delete roomsNeeded;
	}

	Date getStartDate()
	{
		return startDate;
	}

	Date getEndDate()
	{
		return endDate;
	}

	map<string, int> * getRoomsNeeded()
	{
		return roomsNeeded;
	}
};

class Reservation //预定类
{
private:
	Date startDate;
	Date endDate;
	vector<Room*>* rooms;

public:
	Reservation(Date startDate, Date endDate)
	{
		this->startDate = startDate;
		this->endDate = endDate;
		rooms = new vector<Room*>;
	}

	~Reservation()
	{
		delete rooms;
	}

	Date getStartDate()
	{
		return startDate;
	}

	Date getEndDate()
	{
		return endDate;
	}

	vector<Room*>* getRooms()
	{
		return rooms;
	}
};

class LRUCache //LRUCache类
{
private:
	int capacity;
	queue<SearchRequest>Que;
	map<SearchRequest, map<string, vector<Room*>* >* >* cache;

public:
	LRUCache(int capacity=0)
	{
		this->capacity = capacity;
		cache = new map<SearchRequest, map<string, vector<Room*>* >* >;
	}

	~LRUCache()
	{
		delete cache;
	}

	void removeEldestEntry()
	{
		if (Que.size() > this->capacity)
		{
			cache->erase(Que.front());
			Que.pop();
		}
	}

	void putEntry(SearchRequest searchRequest, map<string, vector<Room*>* >* Data)
	{
		
		if (cache->find(searchRequest) != cache->end())
		{
			queue<SearchRequest>temp;
			while (!Que.empty())
			{
				if (Que.front() != searchRequest)
				{
					temp.push(Que.front());
				}
				Que.pop();
			}
			Que = temp;
			Que.push(searchRequest);
			delete (*cache)[searchRequest];
		}
		else
		{
			Que.push(searchRequest);
		}
		(*cache)[searchRequest] = Data;
		removeEldestEntry();
	}

	map<string, vector<Room*>* >* findCache(SearchRequest searchRequest)
	{
		if (cache->find(searchRequest) != cache->end())
		{
			return (*cache)[searchRequest];
		}
		return NULL;
	}

	string printAvailableRooms(map<string, vector<Room*>* >* rooms)
	{
		string ret = "";
		(*rooms)["DOUBLE"];
		(*rooms)["SINGLE"];
		for (auto it : (*rooms))
		{
			ret += "For room type: " + it.first + ", available rooms are: ";
			if (it.second != NULL)
			{
				for (Room* room : (*it.second))
				{

					ret += InttoString(room->getId()) + "; ";
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

};

class Hotel
{
private:
	vector<Room*>* rooms;
	LRUCache* cache;
public:
	Hotel(int cacheSize)
	{
		cache = new LRUCache(cacheSize);
		rooms = new vector<Room*>;
	}
	~Hotel()
	{
		delete rooms;
		delete cache;
	}
	void makeReservation(ReservationRequest* request)
	{
		Reservation* reservation = new Reservation(request->getStartDate(), request->getEndDate());
		SearchRequest* search = new SearchRequest(request->getStartDate(), request->getEndDate());
		map<string, vector<Room*>* >* roomAvailable = getAvailableRooms(search);
		map<string, int>* roomsNeeded = request->getRoomsNeeded();
		for (auto it : (*roomsNeeded))
		{
			string roomtype = it.first;
			int roomCount = it.second;
			vector<Room*>* rooms = (*roomAvailable)[roomtype];
			if (rooms == NULL || roomCount > rooms->size())
			{
				cache->putEntry(*search, roomAvailable);
				delete reservation;
				delete search;
				return;
			}
			for (int i = 0; i < roomCount; i++)
			{
				(*rooms->begin())->makeReservation(reservation->getStartDate(), reservation->getEndDate());
				rooms->erase(rooms->begin());
			}
		}
		cache->putEntry(*search, roomAvailable);
		delete reservation;
		delete search;
	}

	map<string, vector<Room*>* >* handleSearchResult(SearchRequest *request)
	{
		map<string, vector<Room*>* >* ret = cache->findCache(*request);
		if (ret!=NULL)
		{
			return ret;
		}
		ret= getAvailableRooms(request);
		cache->putEntry(*request, ret);
		return ret;
	}

	void cancelReservation(Reservation* reservation)
	{
		for (Room* room : *reservation->getRooms())
		{
			room->cancelReservation(reservation->getStartDate(),reservation->getEndDate());
		}
	}

	vector<Room*> * getRooms()
	{
		return rooms;
	}

	map<string, vector<Room*>* >* getAvailableRooms(SearchRequest* request)
	{
		map<string, vector<Room*>* >* ret = new map<string, vector<Room*>* >;
		
		for (Room *room : *rooms)
		{
			if (room->isValidRequest(request))
			{
				string roomtype = room->getRoomType();
				if ((*ret)[roomtype] == NULL)
				{
					(*ret)[roomtype] = new vector<Room*>;
				}
				(*ret)[roomtype]->push_back(room);
			}
		}
		return ret;
	}

	string printCache()
	{
		return "Printing Cache ...\n" + cache->toString() +
			"*****************************\n\n";
	}

};