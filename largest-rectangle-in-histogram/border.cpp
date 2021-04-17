//
// Created by Pasha on 06.05.2020.
//
#include <algorithm>
#include <vector>
using namespace std;
class Solution {
private:
    vector<int> leftBorder;
    vector<int> rightBorder;

    // Call this in loop from begin to end
    int fillLeftBorder(int height, int index, const vector<int> &heights) {
        if (index == 0) {
            return 0;
        }
        int result = index;
        while (true) {
            if (result == 0) {
                return 0;
            }
            if (heights[result - 1] < height) {
                return result;
            }
            result = leftBorder[result - 1];
        }
    }

    //Call this im loop from end to begin
    int fillRightBorder(int height, int index,  const vector<int> &heights) {
        if (index == heights.size() - 1) {
            return index;
        }
        int result = index;
        while (true) {
            if (result == heights.size() - 1) {
                return result;
            }
            if (heights[result + 1] < height) {
                return result;
            }
            result = rightBorder[result + 1];
        }
    }
public:
    int largestRectangleArea(vector<int> heights) {
        leftBorder.clear();
        rightBorder.clear();

        leftBorder.resize(heights.size());
        rightBorder.resize(heights.size());

        for (size_t i = 0; i < heights.size(); ++i) {
            leftBorder[i] = fillLeftBorder(heights[i], i, heights);
        }
        for (int i = heights.size() - 1; i >= 0; --i) {
            rightBorder[i] = fillRightBorder(heights[i], i, heights);
        }

        int area = 0;
        for (size_t i = 0; i < heights.size(); ++i) {
            int myArea = heights[i]*(rightBorder[i] - leftBorder[i] + 1);
            area = max(area, myArea);
        }
        return area;
    }
};

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
TEST_CASE("Border solution works") {
    Solution s;
    REQUIRE(s.largestRectangleArea(vector<int>({2,1,5,6,2,3})) == 10);
    REQUIRE(s.largestRectangleArea(vector<int>({2,1,2})) == 3);
    REQUIRE(s.largestRectangleArea(vector<int>({1,1,4, 1, 1})) == 5);
}