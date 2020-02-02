731. Restaurant II OO Design

No food delivery.

You can reserve seats.

MAX_DINETIME = 2， which mean the maximum time for a meal is 2 hours

If the table has been reserved, it could not be assigned to another party.

The table has different size

The restaurant will choose the smallest table which fit the numbers of people(For example, if the party has 3 people, the restaurant would assign a 4-people table instead of a 10-people table)

Different from Restaurant I，you have to implement new functions in "Table". The function restaurantDescription, will be called to test your program.

Example
meal(10.0)
meal(13.0)
meal(15.0)
table(1, 4)
table(2, 10)
party(3)
reservedDate(6) // Date(4 Jan 2013 06:00:00 GMT);
party(7)
reservedDate(7) // Date(4 Jan 2013 07:00:00 GMT);
order(1)
order(2, 3)
findTableForReservation(1, 1) // First variable is the ID of party，the second variable is the ID of reservedDate
findTableForReservation(2, 2) 
Table: 1, table size: 4, isAvailable: true. No current order for this table. Current reservation dates for this table are: 4 Jan 2013 06:00:00 GMT ; .
Table: 2, table size: 10, isAvailable: true. No current order for this table. Current reservation dates for this table are: .
*****************************************

Table: 1, table size: 4, isAvailable: true. No current order for this table. Current reservation dates for this table are: 4 Jan 2013 06:00:00 GMT ; .
Table: 2, table size: 10, isAvailable: true. No current order for this table. Current reservation dates for this table are: 4 Jan 2013 07:00:00 GMT ; .
*****************************************
