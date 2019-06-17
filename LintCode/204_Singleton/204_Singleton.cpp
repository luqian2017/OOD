class Solution {
public:
    /**
     * @return: The same instance of this class every time
     */
    static Solution* getInstance() {
        if (!instance) {
            instance = new Solution();
        }
        return instance;
    }
    
    static Solution* instance;
};

Solution* Solution::instance = NULL;