#pragma once
#include <iostream>
#include <random>
using namespace std;
using MatrixFloat = vector<vector<float>>;
using Weights = vector<MatrixFloat>;
using Test = vector<pair<vector<float>, vector<float>>>;

namespace net {
	float random(float a, float b) {
		static mt19937 gen(random_device{}());
		uniform_real_distribution<float> dist(a, b);
		return dist(gen);
	}
	int random(int a, int b) {
		static mt19937 gen(random_device{}());
		uniform_int_distribution dist(a, b);
		return dist(gen);
	}

	auto initWeights(vector<size_t> layers) {
		Weights temp(layers.size() - 1);
		for (size_t i = 0; i < temp.size(); ++i) {
			auto width = layers[i], height = layers[i + 1];
			temp[i].resize(height, vector(width, 0.f));
		}
		return temp;
	}
	void setRandomValue(Weights& weights, float min, float max) {
		for (auto& matrix : weights) {
			for (auto& i : matrix) {
				for (auto& j : i) j = random(min, max);
			}
		}
	}
	float acamulateRow(vector<float>& row, vector<float>& arr) {
		float sum = 0;
		for (size_t i = 0; i < row.size(); i++) sum += row[i] * arr[i];
		return sum;
	}
	auto getSize(MatrixFloat& matrix) {
		auto width = matrix[0].size();
		auto height = matrix.size();
		return make_pair(width, height);
	}
}
using namespace net;

class NeuralNetwork {
public:
	NeuralNetwork(initializer_list<size_t> layers) {
		vectorFx.resize(layers.size());
		for (size_t i = 0; i < layers.size(); ++i) 
			vectorFx[i] = vector<float>(*(layers.begin() + i));
		weights = initWeights(layers);
		setRandomValue(weights, -2, 2);//////////////////////////
	}

	auto goNet(vector<float> input) {
		vectorFx[0] = move(input);
		for (size_t pos = 0; pos < weights.size(); ++pos) {
			auto& matrix = weights[pos];
			for (size_t row = 0; row < matrix.size(); ++row) {
				float sum = acamulateRow(matrix[row], vectorFx[pos]);
				vectorFx[pos + 1][row] = sigmoida(sum);
			}
		}
		return vectorFx.back();
	}

	void setWeights(Weights newWeights) { weights = move(newWeights); }
	auto getStructLayers() {
		vector<size_t> info(vectorFx.size());
		for (size_t i = 0; i < info.size(); ++i) info[i] = vectorFx[i].size();
		return info;
	}

private:
	float sigmoida(float x) { return 1 / (1 + exp(-x)); }

	vector<vector<float>> vectorFx;
	Weights weights;
};

struct Config {
	float min, max;
	size_t COUNT;
	size_t countNew;
	float porog;
	size_t move;
};

auto GeneticAlgorithm(NeuralNetwork& net, Test test, Config config) {
	vector<pair<Weights, size_t>> TEMP(config.COUNT);

	auto layers = net.getStructLayers();
	for (auto& t : TEMP) {
		auto weigths = initWeights(layers);
		setRandomValue(weigths, config.min, config.max);
		t = { weigths, 0 };
	}

	while (true) {
		int count = 0;
		for (auto& temp : TEMP) {
			auto& [weights, eval] = temp;
			eval = 0;

			if (++count < 5) continue;
			for (size_t n = 0; n < config.countNew; ++n) {
				auto idM = random(0, weights.size() - 1);
				auto [w, h] = getSize(weights[idM]);
				auto i = random(0, h - 1), j = random(0, w - 1);
				weights[idM][i][j] = random(config.min, config.max);
			}

			net.setWeights(weights);
			for (auto& t : test) {
				auto& [input, ansver] = t;
				auto result = net.goNet(input);
				for (auto& i : result) i = float(i > config.porog);
				if (result == ansver) ++eval;
			}
			if (eval == test.size()) return;
		}
		sort(begin(TEMP), end(TEMP), [](auto a, auto b) { return a.second > b.second; });
		for (size_t i = config.move; i < config.COUNT; ++i) TEMP[i] = TEMP[(i - config.move) / config.move];
	}
}



//auto GeneticAlgorithm(vector<size_t> layers, vector<vector<float>> test) {
//	const size_t COUNT = 16;
//
//	vector<pair<Weights, size_t>> vWeights(COUNT);
//	for (auto& i : vWeights) {
//		Weights temp;
//		initWeights(temp, layers);
//		setRandomWeights(temp, -2, 2);
//		i = { move(temp), 0 };
//	}
//
//	NeuralNetwork net(layers);
//	while (true) {
//		int count = 0;
//		for (auto& para : vWeights) {
//			auto& [weights, eval] = para;
//			eval = 0;
//
//			if (++count < 5) continue;
//			for (size_t neW = 0; neW < 2; ++neW) {
//				auto idM = random(0, weights.size() - 1);
//				auto [w, h] = getSize(weights[idM]);
//				auto i = random(0, h - 1);
//				auto j = random(0, w - 1);
//				weights[idM][i][j] = random(-2, 2);
//			}
//
//			net.weights = weights;
//			for (auto& test : test) {
//				auto result = net.goNet(test);
//				auto res = (result.back() > 0.7);
//				if (res == test.back()) ++eval;
//			}
//
//			if (eval == 4) return net;
//		}
//
//		sort(begin(vWeights), end(vWeights), [](auto a, auto b) { return a.second > b.second; });
//		for (size_t i = 4; i < COUNT; ++i) vWeights[i] = vWeights[(i - 4) / 4];
//	}
//	
//	return net;
//}