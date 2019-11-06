class Elevator;
class ExternalRequest;
class InternalRequest;

enum Direction {
    _UP, _DOWN
};

enum Status {
	UP, DOWN, IDLE
};

class Request {
	private :
		int level;
	
	public :
    	Request(int l = 0){
    		level = l;
    	}
    	
    	int getLevel(){
    		return level;
    	}
};


class ElevatorButton{
    private :
		int level;
		Elevator *elevator;
	
	public :
		ElevatorButton(int level, Elevator *e){
			this->level = level;
			this->elevator = e;
		}
	
		void pressButton();
};
class ExternalRequest:public Request{

	private :
		Direction direction;
	
	public :
    	ExternalRequest(){
            
        }
		ExternalRequest(int l, Direction d):Request(l) {
			// TODO Auto-generated constructor stub
			this->direction = d;
		}
	
    	Direction getDirection(){
    		return direction;
    	}
};

class InternalRequest:public Request{

	public :
    	InternalRequest(int l = 0):Request(l) {
    		// TODO Auto-generated constructor stub
    	}
};

string writeVector(vector<bool>& vec){
    string temp = Lib::writeVector(vec);
    for(auto ch = temp.begin();ch != temp.end();ch++){
        if((*ch) == ','){
            ch = temp.insert(++ch,' ');
        }
    }
    return temp;
}

class Elevator {
	private :
		vector<ElevatorButton> buttons;
		vector<bool> upStops;
		vector<bool> downStops;
		int currLevel;
		Status status;
	
	public :
		Elevator(int n) {
			status = IDLE;
			for (int i = 0; i < n; ++i) {
			    upStops.push_back(false);
			    downStops.push_back(false);
			}
		}
	
		void insertButton(ElevatorButton eb){
			buttons.push_back(eb);
		}
	
		void handleExternalRequest(ExternalRequest r){
			if(r.getDirection() == _UP){
				upStops[r.getLevel() - 1] = true;
			    if (noRequests(downStops))
			    {
				    status = UP;
			    }
			}
			else {
				downStops[r.getLevel() - 1] = true;
				if (noRequests(upStops))
			    {
				    status = DOWN;
			    }
			}
		}
	
		void handleInternalRequest(InternalRequest r){
			// check valid
			if(status == UP)
    		{
    			if(r.getLevel() >= currLevel + 1)
    			{
    				upStops[r.getLevel() - 1] = true;
    			}
    		}
    		else if(status == DOWN)
    		{
    			if(r.getLevel() <= currLevel + 1)
    			{
    				downStops[r.getLevel() - 1] = true;
    			}
    		}
		}
	
		void openGate(){
			if(status == UP)
    		{
    			for(int i = 0; i < upStops.size(); i++)
    			{
    				int checkLevel = (currLevel + i) % upStops.size();
    				if(upStops[checkLevel])
    				{
    					currLevel = checkLevel;
    					upStops[checkLevel] = false;
    					break;
    				}
    			}
    		}
    		else if(status == DOWN)
    		{
    			for(int i = 0; i < downStops.size(); i++)
    			{
    				int checkLevel = (currLevel + downStops.size() - i) % downStops.size();
    				if(downStops[checkLevel])
    				{
    					currLevel = checkLevel;
    					downStops[checkLevel] = false;
    					break;
    				}
    			}
    		}
		}
		
		void closeGate(){
			if(status == IDLE)
    		{
    			if(noRequests(downStops))
    			{
    				status = UP;
    				return;
    			}
    			if(noRequests(upStops))
    			{
    				status = DOWN;
    				return;
    			}
    		}
    		else if(status == UP)
    		{
    			if(noRequests(upStops))
    			{
    				if(noRequests(downStops))
    				{
    					status = IDLE;
    				}
    				else status = DOWN;
    			}
    		}
    		else {
    			if(noRequests(downStops))
    			{
    				if(noRequests(upStops))
    				{
    					status = IDLE;
    				}
    				else status = UP;
    			}
    		}
		}
		
		bool noRequests(vector<bool>& stops)
    	{
    		for (int i = 0; i < stops.size(); i++)
    		{
    			if (stops[i])
    			{
    				return false;
    			}
    		}
    		return true;
    	}
	
		string elevatorStatusDescription(){
		    string status_;
		    if(status == UP){
		        status_="UP";
		    }
		    else if(status == DOWN){
		        status_="DOWN";
		    }
		    else if(status == IDLE){
		        status_="IDLE";
		    }
			string description = "Currently elevator status is : " + status_ 
					+ ".\nCurrent level is at: " + Utility::toString(currLevel + 1)
					+ ".\nup stop list looks like: " + writeVector(upStops)
					+ ".\ndown stop list looks like:  " + writeVector(downStops)
					+ ".\n*****************************************\n";
			//cout<<description<<endl;
			return description;
		}
};

void ElevatorButton::pressButton() {
	InternalRequest request = InternalRequest(level);
	elevator->handleInternalRequest(request);
}