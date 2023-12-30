// 백준 1460 진욱이의 농장
#include <iostream>
#include <algorithm> // std::find
#include <vector>

using namespace std;

int main() {
	
	int field;
	int seed;
	cin >> field >> seed;
	
	vector<vector<int>> fruit(field,vector<int>(field,0)); 
	for (int k = 0; k < seed; ++k)
	{
		int x, int y, int L, int F;
		cin >> x >> y >> L >> F;
		for (int i = 0; i < x + L; ++x)
		{
			for (int j = 0; j < y + L; ++y)
			{
				fruit[i][j] = F;
			}
		}
	}
}
	