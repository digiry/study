#include <iostream>

using namespace std;

extern void init(int N);
extern int callJob(int cTime, int wID, int mNum, int mOpt);
extern void returnJob(int cTime, int wID);
extern void broken(int cTme, int rID);
extern void repair(int cTime, int rID);
extern int check(int cTime, int rID);

int main() {

	init(10);
	int ans = callJob(2, 1, 4, 0);
	cout << "ans= " << ans << endl;
	ans = check(3, 1);
	cout << "ans= " << ans << endl;
	ans = check(4, 2);
	broken(5, 3);
	repair(6, 3);
	returnJob(10, 1);

	ans = check(13, 1);
	cout << "ans= " << ans << endl;

	return 0;
}
