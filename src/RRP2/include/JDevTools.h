#pragma once
#include <string>
#include <vector>
#include <random>

namespace JDevTools {
	static int rando(int end, int start = 1);
	static int randi(int size, const int probs[]);
	static int randi(const std::vector<int>& probs);

	static int indexes_toflags(int indexes[], int size = 1);
	static bool check_bits(const int& byte, int flags, bool all_true = true);
	static void edit_bits(int& byte, int flags, bool to_true = true);
	static void detoggle_bits(int& byte, int flags);

	//static std::vector<std::string> split(const std::string& s, const std::string& delimiter);
	static std::vector<std::string> split(const char* str, char delimiter);



	int rando(int end, int start) {
		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_int_distribution<> dis(start, end);
		return dis(gen);
	}

	int randi(const std::vector<int>& probs) {
		return randi(probs.size(), probs.data());
	}

	int randi(int size, const int probs[]) {
		if (size < 1) return -1; // input error
		else if (size == 1) return 0;

		std::vector<int> prefixSum(size);
		int temp(0);

		for (int i = 0; i < size; i++) {
			temp += probs[i];
			prefixSum[i] = temp;
		}

		temp = rando(temp);
		for (int i = 0; i < size; i++) {
			if (temp <= prefixSum[i]) return i;
		}

		return -2; // function error
	}

	int indexes_toflags(int indexes[], int size) {
		int flags = 0;

		for (int i = 0; i < size; i++)
		{
			flags |= (1 << indexes[i]);
		}

		return flags;
	}

	bool check_bits(const int& byte, int flags, bool all_true) {
		int result = (byte & flags);
		if (all_true) return (result == flags);
		return result;
	}

	void edit_bits(int& byte, int flags, bool to_true) {
		if (to_true) byte |= flags;
		else byte &= ~flags;
	}

	void detoggle_bits(int& byte, int flags) {
		byte ^= flags;
	}

	std::vector<std::string> split(const char* str, char delimiter) {
		int size = strlen(str);
		const char* ptr = str;
		const char* end = ptr + size;
		std::vector<std::string> result;

		if (ptr != end) {
			const char* token_start = ptr;

			do {
				if (*ptr == delimiter) {
					size = ptr - token_start;
					if (size) result.emplace_back(token_start, size);
					++ptr;
					token_start = ptr;
				}
				else ++ptr;
			} while (ptr != end);

			size = end - token_start;
			if (size) result.emplace_back(token_start, size);
		}

		return result;
	}
}
