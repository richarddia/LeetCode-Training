class Solution {
public:
	vector<int> asteroidCollision(vector<int>& a) {
		vector<int> res;
		deque<int> dq;
		int n = a.size();
		bool flag;
		for (int i = 0; i < n; ++i) {
			flag = false;
			while (!dq.empty() && dq.back() >= 0 && a[i] < 0) {
				if (dq.back() < -a[i]) {
					dq.pop_back();
				}
				else if (dq.back() == -a[i]) {
					dq.pop_back();
					flag = true;
					break;
				}
				else {
					flag = true;
					break;
				}
			}
			if (!flag) dq.push_back(a[i]);
		}
		while (!dq.empty()) {
			res.push_back(dq.front());
			dq.pop_front();
		}
		return res;
	}
};