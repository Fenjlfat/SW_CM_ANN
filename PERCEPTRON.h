#pragma once
#pragma once
#include "header.h"
class PERCEPTRON
{
private:
    int layer = 4;
    int neuron = 32;
    int connect = 32;
    int inputData = 3;
    int outputData = 2;
    int columns_File = 5;
    //int function = 2; //function activation 1=sigmoidal, 2=ReLU
    int funct{ 2 }; //funct 1=sigmoidal, 2=ReLU
    double koef_relu = 0.05;
    double koefNormirovki = 0.068;//0.0565;
public:
    //массив весов
    std::vector<std::vector<std::vector<double>>> WEIGHT;
    //массив смещений
    std::vector<std::vector<double>> BIAS;
    //массив сумм 
    std::vector<std::vector<double>> summForFunction;
    //сигнал каждого нейрона
    std::vector<std::vector<double>> signalsNeurons;
    //минимальные значения входного вектора
    std::vector<double> inputMin;
    //максимальные значения входного вектора
    std::vector<double> inputMax;
    //минимальные значения выходного вектора
    std::vector<double> outputMin;
    //максимальные значения выходного вектора
    std::vector<double> outputMax;

public:
    PERCEPTRON();
    ~PERCEPTRON();
    void initialization_Vectors();
    double FORWARD_PROPAGATION(std::vector<double>& input, std::vector<double>& output);
};

