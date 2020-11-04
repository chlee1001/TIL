#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork() {};

NeuralNetwork::NeuralNetwork(const int inputNum, const int outputNum, const int hiddenNum) {
	initialize(inputNum, outputNum, hiddenNum);
}

void NeuralNetwork::initialize(const int inputNum, const int outputNum, const int hiddenNum) {
	numLayerActs.initialize(hiddenNum + 2);

	numLayerActs[0] = inputNum + 1;
	for (int i = 1; i < hiddenNum + 1; i++) {
		numLayerActs[i] = inputNum + 1;
	}

	numLayerActs[hiddenNum + 1] = outputNum + 1;

	initialize(numLayerActs, hiddenNum);
}

void NeuralNetwork::initialize(const VectorND<unsigned>& layerActsNum, const int hiddenNum) {
	numInput = layerActsNum[0] - 1;
	numOutput = layerActsNum[hiddenNum + 1] - 1;
	numLayers = hiddenNum + 2;

	/*basic bias and learning rate*/
	bias = 1;
	alpha = 0.1;

	//initialize layer
	layerNeuronAct.initialize(numLayers);
	for (int i = 0; i < numLayers; i++) {
		layerNeuronAct[i].initialize(layerActsNum[i], true);
		layerNeuronAct[i][layerActsNum[i] - 1] = bias;
	}

	//initialize gradient
	layerNeuronGrad.initialize(numLayers);
	for (int i = 0; i < numLayers; i++)
		layerNeuronGrad[i].initialize(numLayerActs[i], true);

	//initialize weight
	weights.initialize(numLayers - 1);
	for (int i = 0; i < weights.numElements; i++) {
		weights[i].initialize(layerNeuronAct[i + 1].numDimension - 1, layerNeuronAct[i].numDimension);
		
		for (int j = 0; j < weights[i].rows*weights[i].cols; j++)
			weights[i].values[j] = (double)rand() / RAND_MAX * 0.1;//first random weight
	}
}

/*Activation functions*/
double NeuralNetwork::getSigmoid(const double x) {
	return 1.0 / (1.0 + exp(-x));
}

double NeuralNetwork::getRELU(const double x) {
	return 0.0 < x ? x : 0.0;
}

double NeuralNetwork::getLRELU(const double x) {
	return 0.0 < x ? x : 0.01 * x;
}

double NeuralNetwork::getSigmoidGradFromY(const double y) {
	return (1.0 - y) * y;
}

double NeuralNetwork::getRELUGradFromY(const double y) {
	return y > 0.0 ? 1.0 : 0;
}

double NeuralNetwork::getLRELUGradFromY(const double y) {
	return y > 0.0 ? 1.0 : 0.01;
}

/*apply activate function*/
void NeuralNetwork::applySigmoidToVector(VectorND<double>& vector) {
	for (int i = 0; i < vector.numDimension - 1; i++)
		vector[i] = getSigmoid(vector[i]);
}

void NeuralNetwork::applyRELUToVector(VectorND<double>& vector) {
	for (int i = 0; i < vector.numDimension - 1; i++)
		vector[i] = getRELU(vector[i]);
}

void NeuralNetwork::applyLRELUToVector(VectorND<double>& vector) {
	for (int i = 0; i < vector.numDimension - 1; i++)
		vector[i] = getLRELU(vector[i]);
}

/*forward propagation*/
void NeuralNetwork::forwardProp() {
	for (int i = 0; i < weights.numElements; i++) {
		weights[i].multiply(layerNeuronAct[i], layerNeuronAct[i + 1]);

		applyRELUToVector(layerNeuronAct[i + 1]);//apply activation function
		//if you want another actfunction, change other
	}
}

/*back propagation (studing)*/
void NeuralNetwork::backProp(const VectorND<double>& target) {
	//output layer
	const int i = layerNeuronGrad.numElements - 1;

	for (int j = 0; j < layerNeuronGrad[i].numDimension - 1; j++) {
		const double &outputValue(layerNeuronAct[i][j]);
		layerNeuronGrad[i][j] = (target[j] - outputValue) * getRELUGradFromY(outputValue);
	}
	//

	//hidden layer
	for (int j = weights.numElements - 1; j >= 0; j--) {
		weights[j].multiplyTransposed(layerNeuronGrad[j + 1], layerNeuronGrad[j]);

		for (int k = 0; k < layerNeuronAct[j].numDimension - 1; k++) {
			layerNeuronGrad[j][k] *= getLRELUGradFromY(layerNeuronAct[j][k]);
		}
	}
	//

	//update weight
	for (int j = weights.numElements - 1; j >= 0; j--) {
		updateWeight(weights[j], layerNeuronGrad[j + 1], layerNeuronAct[j]);
	}
}

/*update weight (studing)*/
void NeuralNetwork::updateWeight(Matrix<double>& weightMatrix, VectorND<double>& nextLayerGrad, VectorND<double>& prevLayerAct) {
	for (int i = 0; i < weightMatrix.rows; i++) {
		for (int j = 0; j < weightMatrix.cols; j++) {
			const double deltaW = alpha * nextLayerGrad[i] * prevLayerAct[j];

			weightMatrix.getValue(i, j) += deltaW;
		}
	}
}

/*put input*/
void NeuralNetwork::setInputVector(const VectorND<double>& input) {
	if (input.numDimension < numInput)
		std::cout << "wrong input" << std::endl;

	for (int i = 0; i < numInput; i++) {
		layerNeuronAct[0][i] = input[i];
	}
}

/*copy forward propagation output*/
void NeuralNetwork::copyOutputVector(VectorND<double>& copy, bool copyBias) {
	const VectorND<double>& outputLayerAct(layerNeuronAct[layerNeuronAct.numElements - 1]);

	if (copyBias == false) {
		copy.initialize(numOutput, false);

		for (int i = 0; i < numOutput; i++)
			copy[i] = outputLayerAct[i];
	}
	else {
		copy.initialize(numOutput + 1, false);

		for (int i = 0; i < numOutput + 1; i++)
			copy[i] = outputLayerAct[i];
	}
}