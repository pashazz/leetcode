#include <iostream>
#include <vector>
#include <stack>
#include <limits>
using namespace std;

class Stack : public vector<int> {
protected:
    int topIndex = -1;
public:
    void clear() {
        topIndex = -1;
        vector<int>::clear();
    }
    int top() {
        return this->at(topIndex);
    }
    void pop() {
        if (topIndex > -1)
            topIndex--;
    }
    bool empty() {
        return topIndex == -1;
    }
    void push(int i) {
        ++topIndex;
        if (topIndex == size()) {
            push_back(i);
        } else {
            at(topIndex) = i;
        }
    }
    /**
     * Replace all occurences of numbers more than n to n
     *
     * @param n: n == 0 clears the stack
     */
    void lowerTo(int n) {
        if (n == 0) {
            clear();
        }
        for (auto iter = begin(); iter != end(); ++iter) {
            if (*iter > n) {
                *iter = n;
            }
        }
    }
    /**
     * Undelete all stack items and restore them if deleted by pop
     * use clear or vector methods to really delete
     */
    void restore() {
        topIndex = size() - 1;
    }
};

class Solution {
    private:
    int maxArea(int currentArea, int height, int width) {
        int newArea = height*width;
        if (currentArea > newArea) {
            return currentArea;
        } else {
            return newArea;
        }
    }
    int calculateAreaFromStack(int area) {
        int stackSize = s.size();
        int width = 0;
        while (!s.empty()) {
            int currentHeight = s.top();
            s.pop();
            width++;
            // We only need to calculate area if next item in stack is not the same as this
            if (s.empty() || currentHeight != s.top()) {
                area = maxArea(area, currentHeight, width);
            }
        }
        return area;
    }
    Stack s;
public:
    int largestRectangleArea(vector<int> heights) {
        int width = 0;
        int area = 0;
        s.clear();
        auto iter = heights.begin();
        while (true) {
            if (iter == heights.end()) {
                area = calculateAreaFromStack(area);
                cerr << "Calculating final area: " << area << endl;
                break;
            }
            cerr << *iter << ": ";
            if (s.size() > 0 && *iter < s.top()) { // Площадь под гистограммой может уменьшиться
                cerr << "downgrading from " << s.top() << " to " << *iter << endl;
                area = calculateAreaFromStack(area);
                s.restore();
                s.lowerTo(*iter);
                cerr << area << ", ";
            }
            cerr << "adding item: " << *iter << endl;
            s.push(*iter);
            iter++;
        }
        return area;
    }
};


#define CATCH_CONFIG_MAIN
#include "catch.hpp"
TEST_CASE("Works") {
    Solution s;
    REQUIRE(s.largestRectangleArea(vector<int>({2,1,5,6,2,3})) == 10);
    REQUIRE(s.largestRectangleArea(vector<int>({2,1,2})) == 3);
}