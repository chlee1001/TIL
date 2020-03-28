#pragma once

#include <iostream>
#include "Arr1D.h"
#include "Matrix.h"

class NeuralNetwork {
public:
	int numInput;
	int numOutput;
	int numLayers; // hidden + 2

	double bias;
	double alpha;

	Arr1D<VectorND<double>> layerNeuronAct;
	Arr1D<VectorND<double>> layerNeuronGrad;
	Arr1D<Matrix<double>> weights;

	VectorND<unsigned> numLayerActs;

	NeuralNetwork();
	NeuralNetwork(const int inputNum, const int outputNum, const int hiddenNum);

	void initialize(const int inputNum, const int outputNum, const int hiddenNum);
	void initialize(const VectorND<unsigned>& layerActsNum, const int hiddenNum);

	double getSigmoid(const double x);
	double getRELU(const double x);
	double getLRELU(const double x);

	double getSigmoidGradFromY(const double y);
	double getRELUGradFromY(const double y);
	double getLRELUGradFromY(const double y);

	void applySigmoidToVector(VectorND<double>& vector);
	void applyRELUToVector(VectorND<double>& vector);
	void applyLRELUToVector(VectorND<double>& vector);

	void forwardProp();
	void backProp(const VectorND<double>& target);
	void updateWeight(Matrix<double>& weightMatrix, VectorND<double>& nextLayerGrad, VectorND<double>& prevLayerAct);

	void setInputVector(const VectorND<double>& input);
	void copyOutputVector(VectorND<double>& copy, bool copyBias = false);
};