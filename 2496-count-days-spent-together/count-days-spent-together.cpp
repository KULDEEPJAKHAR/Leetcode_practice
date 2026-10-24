#include <string>
#include <vector>
#include <algorithm>

class Solution {
private:
    int getDayOfYear(std::string date) {
        std::vector<int> daysInMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int month = std::stoi(date.substr(0, 2));
        int day = std::stoi(date.substr(3, 2));
        int dayOfYear = day;
        for (int i = 0; i < month - 1; ++i) {
            dayOfYear += daysInMonths[i];
        }
        return dayOfYear;
    }

public:
    int countDaysTogether(std::string arriveAlice, std::string leaveAlice, std::string arriveBob, std::string leaveBob) {
        int arrAlice = getDayOfYear(arriveAlice);
        int depAlice = getDayOfYear(leaveAlice);
        int arrBob = getDayOfYear(arriveBob);
        int depBob = getDayOfYear(leaveBob);
        
        int startOverlap = std::max(arrAlice, arrBob);
        int endOverlap = std::min(depAlice, depBob);
        
        if (startOverlap <= endOverlap) {
            return endOverlap - startOverlap + 1;
        }
        
        return 0;
    }
};