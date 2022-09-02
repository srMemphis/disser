#include "App/MyApp.h"

#include <cstdio>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <Dense>

using namespace std;

double Compare_Times(std::chrono::system_clock::time_point t1, std::chrono::system_clock::time_point t2);
double Run_Eigen(int, int, Eigen::MatrixXd &A, Eigen::MatrixXd &B, int);


int main()
{

    const int N = 1000000;
    const int iterations = 10;

    for (int M = 2; M <= 16; M++) {
        Eigen::MatrixXd A(N, M);
        Eigen::MatrixXd B(N, 1);

        for (size_t i = 0; i < A.size(); i++) {
            A(i) = rand() / (1.0 + RAND_MAX);
        }

        // Perturb B
        for (size_t i = 0; i < B.size(); i++) {
            B(i) += -1.0 + 2 * rand() / (1.0 + RAND_MAX);
        }

        cout << "Matrix size: " << M * N << " iterations: " << iterations << " runtime: " << Run_Eigen(N, M, A, B, iterations) << " seconds" << endl;
    }

    return 0;








	/*
	MyApp myApp;
	myApp.Run();
	return 0;
	*/
}


double Compare_Times(std::chrono::system_clock::time_point t1, std::chrono::system_clock::time_point t2) {
    double t;

    t = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()*0.001;

    return t;
}

double Run_Eigen(int N, int M, Eigen::MatrixXd& A, Eigen::MatrixXd& B, int iterations) {
    Eigen::MatrixXd _A(N, M);
    Eigen::MatrixXd _B(N, 1);
    Eigen::MatrixXd X(M, 1);
    std::chrono::system_clock::time_point t1, t2;
    double d;

    for (int i = 0; i < N; i++) {
        _B(i, 0) = B(i);
        for (int j = 0; j < M; j++) {
            _A(i, j) = A(i, j);
        }
    }

    t1 = std::chrono::system_clock::now();
    for (int i = 0; i < iterations; i++) {
        X = (_A.transpose() * _A).inverse() * (_A.transpose() * _B);
    }
    t2 = std::chrono::system_clock::now();

    d = Compare_Times(t1, t2);

    return d;
}