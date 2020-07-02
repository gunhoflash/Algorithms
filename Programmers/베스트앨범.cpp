#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool cmp_pair_genre(pair<int, vector<pair<int, int>>> a, pair<int, vector<pair<int, int>>> b)
{
	return a.first > b.first;
}
bool cmp_pair_song(pair<int, int> a, pair<int, int> b)
{
	if (a.second == b.second)
		return a.first < b.first;
	else
		return a.second > b.second;
}

vector<int> solution(vector<string> genres, vector<int> plays) {

	/*

	genre: {
		total play,
		songs: [
			{ id, play },
			...
		]
	}

	*/
	map<string, pair<int, vector<pair<int, int>>>>::iterator it_genre_best;
	map<string, pair<int, vector<pair<int, int>>>> genre_best;
	vector<pair<int, vector<pair<int, int>>>> genre_populated;
	vector<pair<int, int>> *p_vector;
	vector<int> answer;

	int i, j, size, play;
	string genre;

	// make map from every song
	size = plays.size();
	for (i = 0; i < size; i++) {
		genre = genres[i];
		play = plays[i];
		it_genre_best = genre_best.find(genre);

		// if new genre
		if (it_genre_best == genre_best.end()) {
			// make new genre
			genre_best.insert(make_pair(genre, make_pair(0, vector<pair<int, int>>())));
			it_genre_best = genre_best.find(genre);
		}

		// add songs's play to the genre's total play
		it_genre_best->second.first += play;

		// push song data
		it_genre_best->second.second.push_back(make_pair(i, play));
	}

	// populate up to 2 songs for each genre
	for (it_genre_best = genre_best.begin(); it_genre_best != genre_best.end(); it_genre_best++) {
		// sort songs in a genre
		p_vector = &(it_genre_best->second.second);
		sort(p_vector->begin(), p_vector->end(), cmp_pair_song);

		// remain only up to 2 songs
		if (p_vector->size() > 2) {
			p_vector->erase(p_vector->begin() + 2, p_vector->end());
		}

		genre_populated.push_back(it_genre_best->second);
	}

	// sort by total play
	sort(genre_populated.begin(), genre_populated.end(), cmp_pair_genre);

	// make answer
	size = genre_populated.size();
	for (i = 0; i < size; i++) {
		p_vector = &(genre_populated[i].second);
		for (j = 0; j < p_vector->size(); j++) {
			answer.push_back((*p_vector)[j].first);
		}
	}

	return answer;
}