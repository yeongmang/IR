#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>
#include<fstream>
#include<cmath>
#define X first
#define Y second

using namespace std;

vector<pair<double, double> > p;

void readInFile(const char *fileName) {
	ifstream infile;
	double x, y;
	infile.open(fileName);
	if (infile.is_open()) {
		while (!infile.eof()) {
			infile >> x >> y;
			p.push_back(make_pair(x, y));
		}
	}
	p.pop_back();
	cout << p.size() << endl;
	infile.close();
}

double getDist(pair<double, double> p1, pair<double ,double> p2) {
	double res = 0.0;
	res =  sqrt((p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y));
	return res;
}

int main(int argc, char *argv[]) {
	string fileName ="points.txt";
	if (argc == 2) {
		cout << "Input File(command line) : " << argv[1] << endl;
		readInFile(argv[1]);
	} else {
		cout << "Input File : " << fileName << endl;
		readInFile(fileName.c_str());
	}
	for (int i = 0; i < p.size(); i++) {
		cout << p[i].X << " " << p[i].Y << endl;
	}
	double dist[20][20];
	for (int i = 0; i < p.size(); i++) {
		for (int j = 0; j < p.size(); j++) {
			dist[i][j] = getDist(p[i], p[j]);
			cout << dist[i][j] <<  " " ;
		}
		cout << endl;
	}

	vector<vector<int> > cluster;
	for (int i = 0; i < p.size(); i++) {
		cluster.push_back(vector<int>());
		cluster[i].push_back(i);
	}
	int count = 0;
	do {
	int a, b, aa, bb;
	double minDist = 100.0, maxDist = 0;
	for (int i = 0; i < cluster.size(); i++) {
		for (int k = i+1; k < cluster.size(); k++) {
			for (int j = 0; j < cluster[i].size(); j++) {
				for (int l = 0; l < cluster[k].size(); l++) {
					if (cluster[i].size() == 1 && cluster[k].size() == 1) {
						if (dist[cluster[i][j]][cluster[k][l]] < minDist) {
						minDist = dist[cluster[i][j]][cluster[k][l]];
						a = i;
						b = k;
						}
					} else {
						if (dist[cluster[i][j]][cluster[k][l]] > maxDist) {
						maxDist = dist[cluster[i][j]][cluster[k][l]];
						aa = i;
						bb = k;
						}
					}
				}
			}
			if (maxDist != 0) {
				if (maxDist < minDist) {
				minDist = maxDist;
				a = aa;
				b = bb;
				}
				maxDist = 0;
			}
		}
	}
	
	cout << " (" ;
	for (int i = 0; i < cluster[a].size(); i++) cout << cluster[a][i]+1 << ' ';
	cout << ") <--->  ("; 
	for (int i = 0; i < cluster[b].size(); i++) cout << cluster[b][i]+1 << ' ';
	cout << ") " << endl;

	for (int i = 0; i < cluster[b].size(); i++) {
		cluster[a].push_back(cluster[b][i]);
	}
	cluster[b].clear();
	cluster.erase(cluster.begin() + b);
	count++;
	} while (cluster.size() > 1);
	
	return 0;
}

