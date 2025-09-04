#include "header.h"
//рисование графиков
double GNUPLOT(std::vector<double>& vectorVEL, std::vector<double>& vectorPRESS, std::vector<double>& vectorDENS, std::vector<double>& vectorENERG, std::vector<double>& Z)
{
	FILE* pipe = _popen("C:\\gnuplot\\bin\\gnuplot.exe", "w");
	if (pipe != NULL)
	{
		//PARAMETRS_MSS PARAMETR;
		std::ofstream DATAGNUPLOT;
		char tempChar[40];

		std::string tempSTRING;

		tempSTRING = tempChar;

		DATAGNUPLOT.open("DataGnuplot.txt");
		for (int i = 0; i < vectorPRESS.size() - 1; i++)
		{
			DATAGNUPLOT << i << " " << Z[i]-0.0008  << " " << vectorPRESS[i] * 1e-9 << " " << -vectorVEL[i] << " " << vectorDENS[i] << " " << vectorENERG[i] << std::endl;   //SIG11
		}
		DATAGNUPLOT.close();

		//fprintf(pipe, "plot  'E:\\WORK\\SPH\\SHOCK_WAVE_CM\\SHOCK_WAVE_CM\\DataGnuplot.txt' using 1:3 title 'MODEL' with lines linecolor 5\n");
		fprintf(pipe, "plot 'D:\\WORK\\SPH\\PROGRAMMS\\C++\\SW_CM_ANN\\SW_CM_ANN\\DataGnuplot.txt' using 2:3 title 'MODEL' with lines linecolor 1,'D:\\WORK\\SPH\\PROGRAMMS\\C++\\SW_CM_ANN\\SW_CM_ANN\\400MS_25MKS.txt' using 3:4 title 'SPH' with lines linecolor 5\n");
		fflush(pipe);

		// ожидание нажатия клавиши
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();

#ifdef WIN32
		_pclose(pipe);
#else
		_pclose(pipe);
#endif
	}
	else puts("Could not open the file\n");
	//getchar();
	_pclose(pipe);
	return 0;
}