// 백준 임계경로 1948
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;
// 방향이 정해져있고 사이클이 없다.
//입력 vertex 개수, edges의 수, edges의 수만큼 (src, dst, weight) 받음, 출발도시와 도착도시 입력

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int citynum, edgenum;
	cin >> citynum;
	cin >> edgenum;
	vector<vector<pair<int,int>>> citys(citynum+1);
	vector<pair<int,vector<int>>> maxweight(citynum + 1, { 0,{}}); // [도시번호]={최대가중치,{이전 부모노드}}
	vector<int> degree(citynum + 1,0);
	for (int i = 0; i < edgenum; ++i)
	{
		int src,dst,weight;
		cin >> src >> dst >> weight;
		citys[src].push_back({dst,weight});
		degree[dst]++;
	}

	int srt, dst;
	cin >> srt >> dst;
	queue<pair<int, int>> search; //{ 도시번호, 이번탐색의 가중치}
	search.push({ srt,0 });
	while (!search.empty())
	{
		// 도착지를 찾은 경우
		auto curcity = search.front();
		search.pop();
		int curcitynum = curcity.first;
		int curweight = curcity.second;
		if (curcitynum == dst)
		{
			continue;
		}
		// 해야할일
		// 현재 도시의 연결된 정점에 대해 반복문
		for (auto adjcity : citys[curcitynum])
		{
			degree[adjcity.first]--;
			if (maxweight[adjcity.first].first < adjcity.second + curweight)
			{
				maxweight[adjcity.first].first = adjcity.second + curweight;
				maxweight[adjcity.first].second.clear();
				maxweight[adjcity.first].second.push_back(curcitynum);
			}
			else if (maxweight[adjcity.first].first == adjcity.second + curweight)
			{
				maxweight[adjcity.first].second.push_back(curcitynum);
			}

			if (degree[adjcity.first] == 0)
			{
				search.push({adjcity.first,maxweight[adjcity.first].first });
			}
		}
		// 그후 큐에 인접 정점 넣기 => 위상정렬을 통해 위상이 0이된 것만 넣기
		// 그러면 기존 계산된 해당 정점 이후의 값은 다시 한번 계산되면서 갱신 될 것
	}

	// 계산된 마지막 도시 반환
	// 되돌아가기
	queue<int> roads;
	vector<bool> visited(citynum + 1, false);
	int numofroads = 0;
	roads.push(dst);
	while (!roads.empty())
	{
		auto curcity = roads.front();
		roads.pop();
		for (auto newcity : maxweight[curcity].second)
		{
			numofroads++;
			if (!visited[newcity])
			{
				roads.push(newcity);
				visited[newcity] = true;
			}
		}
	}
	cout << maxweight[dst].first << endl;;
	cout << numofroads << endl;
}

