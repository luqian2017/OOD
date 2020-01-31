class Solution {
public:
    /**
     * @return: The same instance of this class every time
     */
    static Solution* getInstance() {
        if (_instance == NULL) {
            _instance = new Solution();
        }
        return _instance;
    }

private:
    Solution() {
        cout<<"constructor() is private"<<endl;
    }
    static Solution * _instance;
};

Solution * Solution::_instance = NULL;