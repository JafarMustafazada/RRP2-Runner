#pragma once
#include <random>
#include <string.h>
#include <vector>

namespace jdevtools {
	static int rando(int end, int start = 1, unsigned seed = 0);
	static int randi(const int probs[], int size, unsigned seed = 0);
	static int randi(const std::vector<int> &probs, unsigned seed = 0);

	static std::string strTokenize(const std::string &str, const char *delim, size_t &prev);
	static std::vector<std::string> split(const std::string &str, const char *delimiter);
	

	int rando(int end, int start, unsigned seed) {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		if (seed) gen = std::mt19937(seed);
		std::uniform_int_distribution<> dis(start, end);
		return dis(gen);
	}

	int randi(const int probs[], int size, unsigned seed) {
		if (size < 1) return -1; // input error
		if (size == 1) return 0;

		int temp = 0;
		std::vector<int> prefixSum(size);

		for (int i = 0; i < size; i++) {
			temp += probs[i];
			prefixSum[i] = temp;
		}

		temp = rando(temp, 1, seed);

		// auto it = std::upper_bound(prefixSum.begin(), prefixSum.end(), temp);
		// return std::distance(prefixSum.begin(), it);
		for (int i = 0; i < size; i++) {
			if (temp <= prefixSum[i]) return i;
		}
		return -2; // function error
	}

	int randi(const std::vector<int> &probs, unsigned seed) {
		return randi(probs.data(), probs.size(), seed);
	}

	std::string strTokenize(const std::string &str, const char *delim, size_t &prev) {
		size_t pos = str.find(delim, prev), temp = prev;
		if (pos == std::string::npos) pos = str.length();
		prev = pos + strlen(delim);
		return str.substr(temp, pos - temp);
	}

	std::vector<std::string> split(const std::string &str, const char *delim) {
		std::vector<std::string> tokens;
		size_t prev = 0, pos;

		while (prev < str.length()) {
			pos = str.find(delim, prev);
			if (pos == std::string::npos) pos = str.length();
			tokens.push_back(str.substr(prev, pos - prev));
			prev = pos + strlen(delim);
		}

		return tokens;
	}


}
