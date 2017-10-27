#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define LEARNING_RATE    0.05
#define MAX_ITERATION    100

float randomFloat()
{
	return (float)rand() / (float)RAND_MAX;
}

int calculateOutput(float weights[], float x, float y)
{
	float sum = x * weights[0] + y * weights[1] + weights[2];
	return (sum >= 0) ? 1 : -1;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	float weights[3], localError, globalError;
	int x[208], y[208], outputs[208], patternCount, i, p, iteration, output, proba[4];

	FILE *fp;
	if ((fp = fopen("test.txt", "r")) == NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}

	i = 0;
	while (fscanf(fp, "%d %d %d", &x[i], &y[i], &outputs[i]) != EOF) {
		if (outputs[i] == 0) {
			outputs[i] = -1;
		}
		i++;
	}
	patternCount = i;

	weights[0] = randomFloat();
	weights[1] = randomFloat();
	weights[2] = randomFloat();

	iteration = 0;
	do {
		iteration++;
		globalError = 0;
		for (p = 0; p < patternCount; p++) {
			output = calculateOutput(weights, x[p], y[p]);

			localError = outputs[p] - output;
			weights[0] += LEARNING_RATE * localError * x[p];
			weights[1] += LEARNING_RATE * localError * y[p];
			weights[2] += LEARNING_RATE * localError;
			globalError += (localError*localError);
		}

		/* Root Mean Squared Error */
		printf("Iteration %d : RMSE = %.4f\n", iteration,
			sqrt(globalError / patternCount));
	} while (globalError != 0 && iteration <= MAX_ITERATION);
	printf("asd %d", patternCount);
	printf("\nDecision boundary (line) equation: %.2f*x + %.2f*y + %.2f = 0\n",
		weights[0], weights[1], weights[2]);

	proba[0] = calculateOutput(weights, 0, 0);
	printf(" %d \n", proba[0]);
	proba[1] = calculateOutput(weights, 0, 1);
	printf(" %d \n", proba[1]);
	proba[2] = calculateOutput(weights, 1, 0);
	printf(" %d \n", proba[2]);
	proba[3] = calculateOutput(weights, 1, 1);
	printf(" %d \n", proba[3]);
	system("pause");
	return 0;
}