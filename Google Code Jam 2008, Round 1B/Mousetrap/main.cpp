#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>

using namespace std;

int main()
{
	ifstream fin("C-large-practice.in");
    ofstream fout("C-large-practice.out");

    int cases;
    fin >> cases;
	fin.ignore(1);
	 
/*
    int answers[100];
	int queries[100];
	for (int cas = 0; cas < cases; cas++)
    {
      int K;
	  fin >> K;

	  int n;
	  fin >> n;

	  for(int i = 0; i < n; ++i)
	  {
		 fin >> queries[i];
	  }
	 
	  for(int i = 0; i < n; ++i)
		answers[i] = -1;

	  for(int i = 1, pos = 0; i <= K; ++i)
	  {
		  pos = (pos + i - 1) % (K - i + 1);
		  for(int j = 0; j < n; ++j)
		  {
			  if(answers[j] < 0)
			  {
				  if(queries[j] == pos + 1 )
				  {
					  answers[j] = i;
				  }
				  else if(queries[j] > pos + 1 )
				  {
					  --queries[j];
				  }
			  }
		  }
	  }

	  fout << "Case #" << cas + 1 << ": "  ;

	  for(int i = 0; i < n; ++i)
	  {
		  fout << answers[i] << " ";
	  }
	  
	  fout << "\n";
    }
*/

    for (int cas = 0; cas < cases; cas++)
    {
      int K;
	  fin >> K;

	  int n;
	  fin >> n;

	  vector<int> indices;
	  indices.reserve(n);

	  int temp;
	  for(int i = 0; i < n; ++i)
	  {
		  fin >> temp;
		  indices.push_back(temp);
	  }

	  int first_num;
	  int second_num;

	  second_num = sqrt(K);

	  vector<list<int>> remain_cards;
	  remain_cards.resize(1);
	  remain_cards.reserve(K/second_num + 1);

	  for(int i = 0; i<K; ++i)
	  {
		  if(remain_cards[remain_cards.size()-1].size() < second_num)
		  {
			  remain_cards[remain_cards.size()-1].push_back(i);
		  }
		  else
		  {
			  remain_cards.resize(remain_cards.size()+1);
			  remain_cards[remain_cards.size()-1].push_back(i);
		  }
	  }

	  int *remain_size = new int[K/second_num + 1];
	  for(int i = 0; i<remain_cards.size(); ++i)
	  {
		  remain_size[i] = remain_cards[i].size();
	  }

	  vector<int> cards;
	  cards.resize(K);

	  int p =0;
	  int pos = 0;
	  for(int i = 1; i <= K; ++i)
	  {
		 pos = (pos + i - 1) % (K - i + 1);
		 
		 int now_pos = 0;
		 int what_pos = 0;
		 int this_pos = 0;
		 int j = 0;
		 while(true)
		 {
			 if(now_pos + remain_size[j] - 1 < pos) 
			 {
				 now_pos += remain_size[j];
			 }
			 else
				 break;
			 ++j;
		 }

		 list<int>::iterator ite = remain_cards[j].begin();
		 while(true)
		 {
			 if(now_pos < pos)
			 {
				 ++now_pos;
				 ++ite;
			 }
			 else
				 break;
		 }
		 cards[*ite] = i;
		 remain_cards[j].erase(ite);
		 --remain_size[j];

	  }

	  fout << "Case #" << cas + 1 << ": "  ;

	  for(int i = 0; i < n; ++i)
	  {
		  fout << cards[indices[i]-1] << " ";
	  }
	  
	  fout << "\n";
    }

	
    return 0;
}
