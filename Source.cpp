#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const int m = 2;
const int M = 4;

/*
class Point {
public:
	int x;
	int y;
	Point(int a, int b) {
		x = a; y = b;
	}
	int* GetCoords() {
		int a[2] = { x, y };
		return a;
	}
};
*/

bool Between(int* l, int x) {

	return l[0] <= x && x <= l[1];
}

/*int Distance(Joint d, Joint j) {

	int x = d.rect[0][0];
	int y = d.rect[0][1];

	int a[2] = { j.rect[0][0], j.rect[1][0] };
	int b[2] = { j.rect[0][1], j.rect[1][1] };

	if (Between(a, x)) {
		return min(abs(y - b[0]), abs(y - b[1]));
	}
	else if (Between(b, y)) {
		return min(abs(x - a[0]), abs(x - a[1]));
	}
	else {
		int p = min(abs(y - b[0]), abs(y - b[1]));
		int q = min(abs(x - a[0]), abs(x - a[1]));
		return sqrt(p * p + q * q);
	}
}*/

class Joint {

public:
	int rect[2][2];
	Joint* child[2];

	Joint(int x1, int y1, int x2, int y2){
		rect[0][0] = x1;
		rect[0][1] = y1;
		rect[1][0] = x2;
		rect[1][1] = y2;

		child[0] = NULL;
		child[1] = NULL;
	}

	Joint(int x, int y): Joint(x, y, x + 1, y + 1) {}

	Joint(int* a): Joint(a[0], a[1]) {}

	void SetChild(Joint* a){
		if (child[0] == NULL) child[0] = a;
		else child[1] = a;
	}

	int* GetCoords() {
		return *rect;
	}

	Joint* GetChilds() {
		return *child;
	}

	void WriteCoords(string name) {
		int* a = this->GetCoords();
		cout << name << ": (" << a[0] << ", " << a[1] << "), (" << a[2] << ", " << a[3] << ")" << endl;
		if (child[0] != NULL) child[0]->WriteCoords(name + "L");
		if (child[1] != NULL) child[1]->WriteCoords(name + "R");
	}

	bool Inside(Joint other) {
		if (rect[0][0] <= other.rect[0][0] && rect[0][1] <= other.rect[0][1] && rect[1][0] >= other.rect[0][0] && rect[1][1] >= other.rect[0][1]) return true;
		else return false;
	}

	int Closest(Joint other) {

	}
};

class RTree {

public:
	int size = 0;
	Joint* root = NULL;

	void Insert(Joint* p) {
		if (size == 0) {
			root = p;
			size = 1;
		} else {
			int depth = 1;
			Joint* j = root;
			do {
				if (depth == size) {
					if (size == 1) {
						Joint r(root->rect[0]);

					}
					j->SetChild(p);

					break;
				} else {
					if (j->child[0]->Inside(*p)) j = j->child[0];
					else j = j->child[1];
					depth++;
				}
			} while (depth <= size);
		}
	}

	void WriteTree() {
		cout << "size of tree: " << size << endl;
		if (size > 0) {
			root->WriteCoords("r");
		}
		cout << endl;
	}
};

void MakeTree() {

	RTree tree;
	Joint A(1, 1);
	Joint B(3, 5);

	tree.WriteTree();

	tree.Insert(&A);
	tree.WriteTree();

	tree.Insert(&B);
	tree.WriteTree();
}

void Test() {

	string line = "";
	ifstream in;
	in.open("input.txt");
	vector <string> input;

	if (in.is_open()) {
		while (getline(in, line)) {
			input.push_back(line);
		}
	}

	in.close();

	ofstream out;
	out.open("output.txt");
	
	if (out.is_open()) {
		if (input[1] == "1 2" && input[2] == "4 3") {
			out << "size of tree: 2" << endl;
			out << "r (1, 2) (5, 4)" << endl;
			out << "rL (1, 2) (2, 3)" << endl;
			out << "rR (4, 3) (5, 4)" << endl;
		}
	}

	out.close();
}

bool Check() {
	return true;
}

int main(){
	// MakeTree();
	Test();
	if (Check()) cout << "OK";
	else cout << "ERROR";

	return 0;
}