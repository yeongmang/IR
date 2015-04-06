#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>
#include<fstream>
using namespace std;

vector<pair<int, int> > c1, c2;
pair<int, int> tPoint;

void readOutFile(const char *fileName) {
	ifstream infile;
	char ch;
	string s;
	int x, y;
	infile.open(fileName);
	if (infile.is_open()) {
		while (!infile.eof()) {
			infile >> ch >> x >> ch >> y >> ch;
			infile >> s;
			if (s == "C1") {
				c1.push_back(make_pair(x, y));
			} else if (s == "C2") {
				c2.push_back(make_pair(x, y));
			} else {
				tPoint = make_pair(x, y);
			}
			s = "";
		}
	}
	infile.close();
}

float calProb(vector<pair<int, int> > & v, int interval) {
	int count = 0;
	int a = v[0].first;
	int b = a + interval;
	float p = 0.0;
	for (int i = 0; i < v.size(); i++) {
		if (a <= v[i].first && v[i].first <= b) {
			count++;
		} else {
			if (a <= tPoint.first && tPoint.first <= b) {
				p =  (float) count / (float)v.size();
			}
			a = b + 1;
			b = a + interval;
			count = 0;
		}

	}
	if (p == 0.0 && count != 0) {
		if (a <= tPoint.first && tPoint.first <= b) {
			p =  (float) count / (float)v.size();
		}
	}
	return p;
}

int main(int argc, char *argv[]) {
	string fileName ="output.txt";
	if (argc == 2) {
		cout << "Input File(command line) : " << argv[1] << endl;
		readOutFile(argv[1]);
	} else {
		cout << "Input File : " << fileName << endl;
		readOutFile("output.txt");
	}
	sort(c1.begin(), c1.end());
	sort(c2.begin(), c2.end());
	for (int i = 0; i < c1.size(); i++) {
	//	cout << c1[i].first << " " << c1[i].second << endl;
	}
	float N = c1.size() + c2.size();
	float Nc1 = c1.size();
	float Nc2 = c2.size();
	float P1 = Nc1 / N, P2 = Nc2 / N;
	cout << "N = " << N << endl << "Nc1 = " << Nc1 << " Nc2 = " << Nc2 << endl;
	cout << "P1 = " << P1 << endl;
	cout << "P2 = " << P2 << endl;
	cout << endl;
	cout << "test Point : " << tPoint.first << " " << tPoint.second << endl;
	int interval;
	cout << "Enter Interval Size : " ;
	cin >> interval;
	float p1 = calProb(c1, interval);
	float p2 = calProb(c2, interval);
	cout << "p1(x, y) = " << p1 << endl;
	cout << "p2(x, y) = " << p2 << endl;
	if (P1 * p1 < P2 * p2) {
		cout << "Point Belongs to C2" << endl;
	} else {	
		cout << "Point Belongs to C1" << endl;
	}
	return 0;
}
