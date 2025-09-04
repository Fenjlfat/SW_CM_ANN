#pragma once

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>

double GNUPLOT(std::vector<double>& vectorVEL, std::vector<double>& vectorPRESS, std::vector<double>& vectorDENS, std::vector<double>& vectorENERG, std::vector<double>& Z);

struct PARAMETRS_MSS
{
	std::string direct_string = "XX";
	std::string vel_string = "V400";
	int time = 100000;
	int length = 100;  //количество €чеек или разбиений
	int direct = 1; //направление сжати€  1=XX; 2=YY; 3=ZZ
	int metall = 3; //1 = Al; 2 = Mg; 3 = CU

	double XX = 20.00e-3;  //длина моделируемой системы
	double VEL0 = 400.00e0; //скорость поршн€

	double VEPS = 1.00e5;
	double COEF_FORMS_PORE = 1.2410e0; //SPHERE = 1.00

	double POROSITY0 = 0.05;
	double TEMPERATURE = 300.00e0;


	double alpha = 1000;   //коэффициент в€зкости
	double betta = 9.0;    //второй коэффициент в€зкости
	double timesss = 2.5e-6;  //до какого момента времени моделируем
	double correct_press = 0.208;
};
