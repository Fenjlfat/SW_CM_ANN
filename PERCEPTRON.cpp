#include "PERCEPTRON.h"
#include "PERCEPTRON.h"
#include "header.h"



PERCEPTRON::PERCEPTRON()
{

}

PERCEPTRON::~PERCEPTRON()
{
}


double function(double t, double koef_relu, std::string name_function)
{
    if (name_function == "RELU")
    {
        if (t >= 0)
        {
            return t;
        }
        else
        {
            return t * koef_relu;
        }
    }

    if (name_function == "Dif_RELU")
    {
        if (t >= 0)
        {
            return 1;
        }
        else
        {
            return  koef_relu;
        }
    }

    //сигмоидальна€ функци€
    if (name_function == "sigmoid")
    {
        return (1 / (1 + exp(-t)));
    }

    //производна€ сигмоидальной функции
    if (name_function == "dif_sigmoid")
    {
        return ((1 / (1 + exp(-t))) * (1 - (1 / (1 + exp(-t)))));
    }

}

//считывание векторов
void PERCEPTRON::initialization_Vectors()
{
    int l = 0, h = 0, a = 0, s = 0;
    double q;
    std::fstream F;//объ€вл€ем двунаправленный поток который работает как на запись так и на чтение
    //считывание весовых коэффициентов
    F.open("koefficientsWeightOut.txt", std::ios::in);
    if (!F.is_open()) std::cout << "File not open" << std::endl;
    else
    {
        std::cout << "File open" << std::endl;

        //while (!F.eof())
        //{
        while (a < layer)
        {
            std::vector<std::vector<double>> arr;
            while (h < neuron)
            {
                std::vector<double> vec;
                while (s < connect)
                {
                    F >> q;
                    vec.push_back(q);
                    s = s + 1;
                }
                arr.push_back(vec);
                vec.clear();
                s = 0;
                h = h + 1;
            }
            WEIGHT.push_back(arr);
            arr.clear();
            h = 0;
            a = a + 1;
        }
        h = 0;
        a = 0;
        s = 0;
        //}
        l = 0;
    }
    F.close();
    //считывание коэффициентов смещений
    F.open("koefficientsBiasOut.txt", std::ios::in);
    if (!F.is_open()) std::cout << "File not open" << std::endl;
    else
    {
        std::cout << "File open" << std::endl;
        s = layer;
        //while (!F.eof())
        //{
        while (a < layer)
        {
            std::vector<double> vec;
            while (h < neuron)
            {
                F >> q;
                vec.push_back(q);
                h = h + 1;
            }
            BIAS.push_back(vec);
            vec.clear();
            h = 0;
            a = a + 1;
        }
        //a = 0;
        //}
        l = 0;
        h = 0;
        a = 0;
        s = 0;
    }
    F.close();

    h = 0;
    //PARAMETRS_ANN PARAM;
    //определение максимальных и минимальных значений дл€ нормировки
    std::fstream FILE;
    //считывам данные с файла
    FILE.open("minInput.txt", std::ios::in);
    if (!FILE.is_open())
    {
        std::cout << "File not open" << std::endl;
    }
    else
    {
        std::cout << "File open" << std::endl;
        while (!FILE.eof())
        {
            while (h < inputData)
            {
                FILE >> q;
                inputMin.push_back(q);
                h = h + 1;
            }
            h = 0;
        }
    }
    FILE.close();

    FILE.open("maxInput.txt", std::ios::in);
    if (!FILE.is_open())
    {
        std::cout << "File not open" << std::endl;
    }
    else
    {
        std::cout << "File open" << std::endl;
        while (!FILE.eof())
        {
            while (h < inputData)
            {
                FILE >> q;
                inputMax.push_back(q);
                h = h + 1;
            }
            h = 0;
        }
    }
    FILE.close();

    FILE.open("minOutput.txt", std::ios::in);
    if (!FILE.is_open())
    {
        std::cout << "File not open" << std::endl;
    }
    else
    {
        std::cout << "File open" << std::endl;
        while (!FILE.eof())
        {
            while (h < outputData)
            {
                FILE >> q;
                outputMin.push_back(q);
                h = h + 1;
            }
            h = 0;
        }
    }
    FILE.close();

    FILE.open("maxOutput.txt", std::ios::in);
    if (!FILE.is_open())
    {
        std::cout << "File not open" << std::endl;
    }
    else
    {
        std::cout << "File open" << std::endl;
        while (!FILE.eof())
        {
            while (h < outputData)
            {
                FILE >> q;
                outputMax.push_back(q);;
                h = h + 1;
            }
            h = 0;
        }
    }
    FILE.close();

    //intializationn summForFunction
    //intializationn сигнал каждого нейрона
    //инициализаци€ масива ошибок нейронов
    std::cout << "initialization  summForFunction" << std::endl;
    for (int i = 0; i < layer; i++)
    {
        std::vector<double> vec;
        for (int j = 0; j < neuron; j++)
        {
            vec.push_back(0.00);
        }
        summForFunction.push_back(vec);    //intializationn summForFunction
        signalsNeurons.push_back(vec);     //intializationn сигнал каждого нейрона
        vec.clear();
    }
}

double normirovka(double X, double Xmin, double Xmax, double koefNormirovki)
{
    double s = 0.00;
    double ret = 0.00;

    if (Xmax != Xmin)
    {
        s = (Xmax - Xmin) * koefNormirovki;
        Xmin = Xmin - s;
        Xmax = Xmax + s;
        ret = (X - Xmin) / (Xmax - Xmin);
    }
    else
    {
        s = Xmax * koefNormirovki;
        Xmin = Xmin - s;
        Xmax = Xmax + s;
        ret = (X - Xmin) / (Xmax - Xmin);
    }
    if (Xmax == 0 || Xmin == 0)
    {
        ret = 0.00;
    }
    //Xmin = Xmin - s;
    //Xmax = Xmax + s;
    //return (X - Xmin) / (Xmax - Xmin);
    return ret;
}

double perenormirovka(double Ynorm, double Ymin, double Ymax, double koefNormirovki)
{
    double s = 0.00;
    s = (Ymax - Ymin) * koefNormirovki;
    Ymin = Ymin - s;
    Ymax = Ymax + s;
    return Ynorm * (Ymax - Ymin) + Ymin;
    //return Ynorm * (Ymax - Ymin - Ymin * 0.2) + Ymin + Ymin * 0.2;

}

//пр€мое распространение
double PERCEPTRON::FORWARD_PROPAGATION(std::vector<double>& input, std::vector<double>& output)
{
    double summa = 0.00;
    int z = 0;

    //нормировка входного вектора
    for (int i = 0; i < inputData; i++)
    {
        input[i] = normirovka(input[i], inputMin[i], inputMax[i], koefNormirovki);
    }

    //инициализаци€ сигналов входного сло€
    //cout << "initialization input signals" << endl;
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < neuron; j++)
        {
            for (int k = 0; k < connect; k++)
            {
                summa += input[k] * WEIGHT[i][j][k];
            }
            summa = summa + BIAS[i][j];
            summForFunction[i][j] = summa;
            signalsNeurons[i][j] = function(summa, koef_relu, "sigmoid");
            summa = 0.00;
        }
    }
    //вычисление сигналов нейронов дл€ скрытого и выходного слоев
    for (int i = 1; i < layer; i++)
    {
        for (int j = 0; j < neuron; j++)
        {
            z = layer - i;
            for (int k = 0; k < connect; k++)
            {
                summa += signalsNeurons[i - 1][k] * WEIGHT[i][j][k];
            }
            summa = summa + BIAS[i][j];
            summForFunction[i][j] = summa;
            if (z == 1)
            {
                signalsNeurons[i][j] = function(summa, koef_relu, "sigmoid");
            }
            else
            {
                if (funct == 1)
                {
                    signalsNeurons[i][j] = function(summa, koef_relu, "sigmoid");
                }
                if (funct == 2)
                {
                    signalsNeurons[i][j] = function(summa, koef_relu, "RELU");
                }
            }
            summa = 0.00;
            z = 0;
        }

        z = layer - i;
        //вычисление выходного сло€
        if (z == 1)
        {
            for (int n = 0; n < outputData; n++)
            {
                output[n] = signalsNeurons[i][n];
            }
        }
        z = 0;
        //перенормировка выходного сло€
        for (int i = 0; i < outputData; i++)
        {
            output[i] = perenormirovka(output[i], outputMin[i], outputMax[i], koefNormirovki);
        }
    }
    return  0;
}