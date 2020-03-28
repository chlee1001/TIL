#include <iostream>
#include "NeuralNetwork.h"
#include "pGNUPlot.h"

void main() {
	int inputNum, outputNum, hiddenNum;
	float alphaValue;

	printf("NeuralNetwork Setup\n");
	printf("Enter input) Number of input, Number of output, Number of hidden layer, learning rate\n");
	scanf_s("%d %d %d %f", &inputNum, &outputNum, &hiddenNum, &alphaValue);

	//input vector
	VectorND<double> x(inputNum);

	//output (Desired outcome)
	VectorND<double> yTarget(outputNum);

	//output vector
	VectorND<double> yTemp(outputNum);

	NeuralNetwork nn;

	nn.initialize(inputNum, outputNum, hiddenNum);//input num, outputnum, hidden layer num
	nn.alpha = alphaValue;//Learning rate

	getchar();
	char inputLocation[255];
	printf("input file location : ");
	gets_s(inputLocation, 255);

	FILE *fp;
	fopen_s(&fp, inputLocation, "r");
	if (fp == NULL) {
		printf("Location Error!\n");
		return;
	}

	FILE *out;
	fopen_s(&out, "output.txt", "w");
	if (out == NULL)
		return;

	double *input = new double[inputNum];
	double *output = new double[outputNum];

	printf("Studing...\n");

	int excutionIndex = 1;
	while (!feof(fp)) {
		for (int i = 0; i < inputNum; i++) {
			fscanf_s(fp, "%lf", &input[i]);
			x[i] = input[i];
		}
		for (int i = 0; i < outputNum; i++) {
			fscanf_s(fp, "%lf", &output[i]);
			yTarget[i] = output[i];
		}

		nn.setInputVector(x);

		nn.forwardProp();

		nn.copyOutputVector(yTemp);

		nn.backProp(yTarget);

		int wnum = 1;
		for (int j = 0; j < nn.weights.numElements; j++) {
			for (int k = 0; k < nn.weights[j].rows*nn.weights[j].cols; k++) {
				fprintf(out, "%d %d %f\n", excutionIndex++, wnum++, nn.weights[j].values[k]);
			}
		}
	}
	fclose(fp);
	fclose(out);

	//그래프 실행
	CpGnuplot plot(("gnuplot\\bin\\wgnuplot.exe"));

	plot.cmd(("set title 'Result'"));
	plot.cmd(("set xlab 'Weight#'"));
	plot.cmd(("set ylab '실행#'"));
	plot.cmd(("set zlab 'Weight'"));
	plot.cmd(("splot 'output.txt'"));

	printf("complete\n");
	printf("Open the Graph");


	printf("Enter the input value )\n");
	for (int i = 0; i < inputNum; i++) {
		scanf_s("%lf", &input[i]);
		x[i] = input[i];
	}

	nn.setInputVector(x);
	nn.forwardProp();
	nn.copyOutputVector(yTemp);

	printf("Output is\n");
	std::cout << yTemp << std::endl;


	delete[] input;
	delete[] output;




}