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
		return startDate != compare.startDate || endDate != compare.endDate;
	}

	bool operator ==(const SearchRequest &compare)const
	{
		return startDate == compare.startDate && endDate == compare.endDate;
	}

	string toString()
	{
		return "Start date is: " + startDate.toString() + ", End date is: " + endDate.toString();
	}
};
class SearchHotelRequest {
private:
	Date startDate;
	Date endDate;
	int groupSize;
public:
	SearchHotelRequest(Date startDate, Date endDate, int groupSize)
	{
		this->startDate = startDate;
		this->endDate = endDate;
		this->groupSize = groupSize;
	}

	Date getStartDate()
	{
		return startDate;
	}

	Date getEndDate()
	{
		return endDate;
	}

	int getGroupSize()
	{
		return groupSize;
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
	vector<Room *> *rooms;
	int hotelId;
public:
	
	Reservation(Date startDate, Date endDate)
	{
		this->startDate = startDate;
		this->endDate = endDate;
		rooms = new vector<Room*>;
		hotelId = 0;
	}
	~Reservation()
	{
		delete rooms;
	}

	int getHotelId()
	{
		return hotelId;
	}

	int setHotel(int id)
	{
		hotelId = id;
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

	string toString()
	{
		string res = "Hotel is: " + to_string(hotelId) + ", start date is: " + startDate.toString() + ", End date is: " + endDate.toString()
			+ ", rooms are: ";
		for (Room *room : (*rooms))
		{
			res += to_string(room->getId()) + "; ";
		}
		res += ". ";
		return res;
	}

};


class LRUCache //LRUCache类
{
private:
	int capacity;
	queue<SearchRequest>Que;
	map<SearchRequest, map<string, vector<Room*>* >* >* cache;

public:
	LRUCache(int capacity = 0)
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
		while (Que.size() > this->capacity)
		{
			if (cache->find(Que.front()) != cache->end())
			{
				cache->erase(Que.front());

			}
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
			
		}
		Que.push(searchRequest);
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
		if (rooms == NULL)
		{
			rooms = new map<string, vector<Room*>* >;
		}
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

};


class Hotel
{
private:
	int id;
	vector<Room*>* rooms;
	LRUCache* cache;
public:
	Hotel(int id)
	{
		this->id = id;
		cache = new LRUCache(2);
		rooms = new vector<Room*>;
	}
	~Hotel()
	{
		delete rooms;
		delete cache;
	}

	int getId()
	{
		return this->id;
	}

	Reservation *makeReservation(ReservationRequest* request)
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
				return NULL;
			}
			for (int i = 0; i < roomCount; i++)
			{
				(*rooms->begin())->makeReservation(reservation->getStartDate(), reservation->getEndDate());
				rooms->erase(rooms->begin());
			}
		}
		cache->putEntry(*search, roomAvailable);
		return reservation;
	}

	map<string, vector<Room*>* >* handleSearchResult(SearchRequest *request)
	{
		map<string, vector<Room*>* >* ret = cache->findCache(*request);
		if (ret != NULL)
		{
			return ret;
		}
		ret = getAvailableRooms(request);
		cache->putEntry(*request, ret);
		return ret;
	}

	void cancelReservation(Reservation* reservation)
	{
		for (Room* room : *reservation->getRooms())
		{
			room->cancelReservation(reservation->getStartDate(), reservation->getEndDate());
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
		return "Hotel Id: " + to_string(getId()) + "\nPrinting Cache ...\n" + cache->toString() +
			"*****************************\n\n";
	}

};


class BookingSystem
{
private:

	vector<Hotel *> *hotels;

public:

	BookingSystem()
	{
		hotels = new vector<Hotel *>;
	}

	vector<Hotel *> *searchHotel(SearchHotelRequest *request)
	{
		vector<Hotel *> *availableHotels = new vector<Hotel *>();
		for (Hotel *hotel : (*hotels))
		{
			SearchRequest *searchRequest = new SearchRequest(request->getStartDate(), request->getEndDate());
			map<string, vector<Room *> *> *searchRes = hotel->handleSearchResult(searchRequest);
			int availableCapacity = 0;
			for (auto it : (*searchRes))
			{
				int capaticity = 2;
				if (it.first == "SINGLE")
				{
					capaticity = 1;
				}
				availableCapacity += capaticity * it.second->size();
			}
			if (availableCapacity >= request->getGroupSize())
			{
				availableHotels->push_back(hotel);
			}
		}
		return availableHotels;
	}

	Reservation *makeReservation(Hotel *hotel, ReservationRequest *request)
	{
		return hotel->makeReservation(request);
	}

	void cancelReservation(Reservation *reservation,vector<Hotel *> *hotels)
	{
		hotels->at(reservation->getHotelId() - 1)->cancelReservation(reservation);
	}

	vector<Hotel *> *getHotels()
	{
		return hotels;
	}
};