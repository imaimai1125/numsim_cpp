#include <cstdio>
#include <cstdlib>
#include <math.h>

using namespace std;

double gaussian(double x,double mu,double sigma){
	return (1/sqrt(2*M_PI*sigma))*exp(-(x-mu)*(x-mu)/sigma);
}


int main(int argc, char* argv[], char* envp[])
{
	/******************************************
	/数値計算保管用一時ファイルに値を書き込む		
	******************************************/
	FILE* Fp = fopen("tmp.dat","w"); //fopen
	double x,y = 0;
	for (x = -5; x < 5; x+=0.05){
		//描画用関数
		y = gaussian(x,0,10)+ gaussian(x,0,0.5);
		fprintf(Fp,"%f %f\n" ,x,y);
	}
	fclose(Fp);

	/******************************************
	/gnuplotにさっき作った一時ファイルを送り描画
	******************************************/
	FILE* Gp = popen("gnuplot -persist", "w"); //popen
	//座標の名前と範囲を入力
	fprintf(Gp, "set xlabel \"x\"\n");
	fprintf(Gp, "set ylabel \"y\"\n");
	fprintf(Gp, "set xrange [-5:5] \n");
	fprintf(Gp, "set yrange [0:1] \n");

	//描画(さっき出した一時ファイルから)
	fprintf(Gp, "plot \"tmp.dat\" with linespoints"); 
	fflush(Gp); //バッファを書き出す
	pclose(Gp);

	return EXIT_SUCCESS;
}
