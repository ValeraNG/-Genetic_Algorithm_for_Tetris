#include "Game.h"
using namespace std;


int main() {
	const int BIAS_X = 2;
	const int WIDTH = 10, HEIGHT = 20;
	Game::createWindow(WIDTH, HEIGHT, BIAS_X);

	Game game(WIDTH, HEIGHT);

	size_t input = WIDTH * HEIGHT, output = 4;
	NeuralNetwork net{ input, 20, 10, output };

	game.setControl(net);

	game.run<true>();



	//vector games(100000, new Game(WIDTH, HEIGHT));
	//for (auto& i : games) i->run();
}












//int main() {
//	Test test{
//		{ { 0, 0 }, { 0 } },
//		{ { 1, 0 }, { 1 } },
//		{ { 0, 1 }, { 1 } },
//		{ { 1, 1 }, { 0 } }
//	};
//
//	NeuralNetwork net{ 2, 4, 1 };
//
//	Config config{ -2, 2, 16, 2, 0.7, 4 };
//	GeneticAlgorithm(net, test, config);
//
//	while (true) {
//		cout << "input: ";
//		vector<float> input(2);
//		for (auto& i : input) cin >> i;
//	
//		auto result = net.goNet(input);
//	
//		cout << "out: ";
//		for (auto& i : result) cout << (i > 0.7) << ' ';
//		cout << "\n\n";
//	}
//}

//#include <iostream>
//#include <random>
////#include <algorithm>
//using namespace std;
//
//float random(float a, float b) {
//	static mt19937 gen(random_device{}());
//	uniform_real_distribution<float> dist(a, b);
//	return dist(gen);
//}
//int random(int a, int b) {
//	static mt19937 gen(random_device{}());
//	uniform_int_distribution dist(a, b);
//	return dist(gen);
//}
//
//using Weights = vector<vector<vector<float>>>;
//void initWeights(Weights& weights, vector<size_t> layers) {
//	weights.resize(layers.size() - 1);
//	for (size_t pos = 0; pos < weights.size(); ++pos) {
//		auto width = layers[pos];
//		auto height = layers[pos + 1];
//		auto& matrix = weights[pos];
//		matrix.resize(height, vector(width, 0.f));
//	}
//}
//void setRandomWeights(Weights& weights, float min, float max) {
//	for (auto& matrix : weights) {
//		for (auto& i : matrix) {
//			for (auto& j : i) j = random(min, max);
//		}
//	}
//}
//float acamulateRow(vector<float>& row, vector<float>& arr) {
//	float sum = 0;
//	for (size_t i = 0; i < row.size(); i++) sum += row[i] * arr[i];
//	return sum;
//}
//auto getSize(vector<vector<float>>& matrix) {
//	auto height = matrix.size();
//	auto width = matrix.front().size();
//	return make_pair(width, height);
//}
//
//class NeuralNetwork {
//public:
//	NeuralNetwork(vector<size_t> layers) {
//		vFx.resize(layers.size());
//		for (size_t i = 0; i < vFx.size(); ++i) vFx[i].resize(layers[i]);
//		initWeights(weights, layers);
//		setRandomWeights(weights, -2, 2);
//	}
//	auto goNet(vector<float> input) {
//		vFx.front() = input;
//		auto size = weights.size();
//		for (size_t pos = 0; pos < size; ++pos) {
//			auto& matrix = weights[pos];
//			for (size_t i = 0; i < matrix.size(); i++) {
//				float sum = acamulateRow(matrix[i], vFx[pos]);
//				vFx[pos + 1][i] = sigmoida(sum);
//			}
//		}
//		return vFx.back();
//	}
//	
//private:
//	float sigmoida(float x) { return 1 / (1 + exp(-x)); }
//
//	vector<vector<float>> vFx;
//public: 
//	Weights weights;
//};
//
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
//
//
//
//int main() {
//	vector<vector<float>> test{
//	{ 0, 0, 0 },
//	{ 0, 1, 1 },
//	{ 1, 0, 1 },
//	{ 1, 1, 0 }
//	};
//
//	auto net = GeneticAlgorithm({ 2, 3, 1 }, test);
//
//	while (true) {
//		cout << "input: ";
//		vector<float> input(2);
//		for (auto& i : input) cin >> i;
//
//		auto result = net.goNet(input);
//
//		cout << "out: ";
//		for (auto& i : result) cout << (i > 0.7) << ' ';
//		cout << "\n\n";
//	}
//
//	//vector v{ 4, 5,1,3,9,2,6 };
//	//sort(begin(v), end(v), [](int a, int b) { return a > b; });
//	//for (auto& i : v)
//	//{
//	//	cout << i << ' ';
//	//}
//	//NeuralNetwork net({ 2, 2, 1 });
//	//auto result = net.goNet({ 1, 0 });
//	//for (auto& i : result) cout << i << '\t';
//	//cout << endl;
//}

//class NeuralNetwork {
//public:
//	NeuralNetwork() {};
//	NeuralNetwork(ushort input, vector<ushort> hidden, ushort output) {
//		setInfoLayers(input, hidden, output);
//		setWeights();
//		setArr_fx();
//	}
//	void goNetwork(float* input) {
//		arr_fx[0] = input;
//		ushort countMatrix = sizeInfoL - 1;
//		for (ushort pos = 0; pos < countMatrix; ++pos) {
//			auto matrix = weights[pos];
//			auto width = infoLayers[pos];
//			auto height = infoLayers[pos + 1];
//			for (ushort row = 0; row < height; ++row) {
//				auto sum = getSum(matrix[row], arr_fx[pos], width);
//				arr_fx[pos + 1][row] = sigmoida(sum);
//			}
//		}
//	}
//
//protected:
//	//void operator ()(NeuralNetwork& net) {
//	//	sizeInfoL = net.sizeInfoL;
//	//	infoLayers = net.infoLayers;
//	//	arr_fx = net.arr_fx;
//	//	weights = net.weights;
//	//}
//
//	/*-----go net-----*/
//	float sigmoida(float x) { return 1 / (1 + exp(-x)); }
//	float getSum(float* arrW, float* arrF, ushort size) {
//		float sum = 0;
//		for (ushort i = 0; i < size; ++i) sum += arrW[i] * arrF[i];
//		return sum;
//	}
//
//	/*-----temp-----*/
//	auto setMatrixWeights(ushort width, ushort height) {
//		auto matrix = new float* [height];
//		for (ushort row = 0; row < height; ++row) {
//			matrix[row] = new float[width];
//			for (ushort col = 0; col < width; ++col) matrix[row][col] = random(-2, 2);
//		}
//		return matrix;
//	}
//	/*-----init-----*/
//	void setInfoLayers(ushort input, vector<ushort>& hidden, ushort output) {
//		infoLayers = new ushort[sizeInfoL = hidden.size() + 2];
//		infoLayers[0] = input;
//		for (ushort i = 0; i < hidden.size(); ++i) infoLayers[i + 1] = hidden[i];
//		infoLayers[sizeInfoL - 1] = output;
//	}
//	auto initMatrixWeights(ushort width, ushort height) {
//		auto matrix = new float* [height];
//		for (ushort row = 0; row < height; ++row) matrix[row] = new float[width];
//		return matrix;
//	}
//	void setWeights() {
//		ushort countMatrix = sizeInfoL - 1;
//		weights = new float** [countMatrix];
//		for (ushort pos = 0; pos < countMatrix; ++pos) {
//			auto matrix = weights[pos];
//			auto width = infoLayers[pos];
//			auto height = infoLayers[pos + 1];
//			matrix = initMatrixWeights(width, height);
//		}
//	}
//	void setArr_fx() {
//		arr_fx = new float* [sizeInfoL];
//		for (size_t i = 1; i < sizeInfoL; ++i) arr_fx[i] = new float[infoLayers[i]];
//	}
//
//	ushort sizeInfoL = 0;
//	ushort* infoLayers = nullptr;
//	float** arr_fx = nullptr;
//	float*** weights = nullptr;
//};