#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

class Solution {
public:
    std::vector<int> minReverseOperations(int n, int p, std::vector<int>& banned, int k) {
        std::set<int> even;
        std::set<int> odd;

        std::set<int>* setPtr;

        std::vector<bool> skip(n, false);

        for (int num : banned) {
            skip[num] = true;
        }

        int start = p;

        // Add values to the set that are not banned
        for (int i = 0; i < n; ++i) {
            if (skip[i] || i == p)
                continue;

            if (i % 2 == 1)
                odd.insert(i);
            else
                even.insert(i);
        }

        std::vector<int> result(n, -1);

        std::queue<int> queue;
        queue.push(p);

        int size;
        int current;
        int moves = 0;

        int min, max;

        int mCurrent;

        while (!queue.empty()) {
            size = queue.size();

            while (size-- > 0) {
                current = queue.front();
                queue.pop();

                result[current] = moves;

                // calculate min index
                if (current < k - 1) {
                    min = (k - 1) - current;
                } else {
                    min = current - k + 1;
                }

                // calculate max index
                mCurrent = (n - 1) - current;
                if (mCurrent < k - 1) {
                    max = (k - 1) - mCurrent;
                } else {
                    max = mCurrent - k + 1;
                }
                max = (n - 1) - max;

                // choose the correct parity set
                setPtr = (min % 2 == 0) ? &even : &odd;

                auto it = setPtr->lower_bound(min);

                // add all values in range to the queue and remove from set
                while (it != setPtr->end() && *it <= max) {
                    queue.push(*it);
                    setPtr->erase(it++);
                }
            }

            ++moves;
        }

        return result;
    }
};
