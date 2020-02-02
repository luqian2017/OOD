732. Hotel II OO Design
s
题目：设计Booking System

目前系统里有两家Hotel

Hotel目前有两种房间类型：SINGLE和DOUBLE

Booking System能够支持搜索，输入日期 和 人数， 能够返回住得下
的Hotels

能够支持预定

能够取消预定

需要实现BookingSystem class

Example
Hotel(1) // 创建hotel id=1
Hotel(2) // 创建hotel id=2
Room(1, 1, "Single")  // 创建room，第一个参数是room属于hotel_1, type是单间
Room(1, 2, "Single")  
Room(2, 1, "Single")
Room(2, 2, "Double")  // 创建room，第一个参数是room属于hotel_2, type是标间
searchHotelRequest("2013-01-06", "2013-10-10", 3)
searchHotelRequest("2013-01-01", "2013-10-10", 2)
roomsNeeded("Single", 1, "Double", 1)
roomsNeeded("Single", 1)
reservationRequest(2, "2013-01-04", "2013-01-06", 1) // 第一个参数是从hotel_2当中预定
reservationRequest(1, "2013-01-06", "2013-10-10", 2) // 第一个参数是从hotel_1当中预定
search result: 2;
*****************************

search result: 1;2;
*****************************

Hotel Id: 2
Printing Cache ...
Search Request -> Start date is: Jan 1, 2013 12:00:00 AM, End date is: Oct 10, 2013 12:00:00 AM
Value -> For room type: DOUBLE, available rooms are: 2; . For room type: SINGLE, available rooms are: 1; . 

Search Request -> Start date is: Jan 4, 2013 12:00:00 AM, End date is: Jan 6, 2013 12:00:00 AM
Value -> For room type: DOUBLE, available rooms are: . For room type: SINGLE, available rooms are: . 

*****************************

Hotel Id: 1
Printing Cache ...
Search Request -> Start date is: Jan 1, 2013 12:00:00 AM, End date is: Oct 10, 2013 12:00:00 AM
Value -> For room type: DOUBLE, available rooms are: . For room type: SINGLE, available rooms are: 1; 2; . 

Search Request -> Start date is: Jan 6, 2013 12:00:00 AM, End date is: Oct 10, 2013 12:00:00 AM
Value -> For room type: DOUBLE, available rooms are: . For room type: SINGLE, available rooms are: 2; . 

*****************************
