/*
    Backpropagation karya Benhard Tampubolon
    Github: github.com/benhard123
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define dimensi1 4
#define inputlayerneuron 2
#define hiddenlayerneuron 3
#define maxepoh 1

using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void backpropagation(double x[dimensi1][inputlayerneuron], double t[dimensi1], double v[inputlayerneuron][hiddenlayerneuron], double v0[hiddenlayerneuron], double w[hiddenlayerneuron], double w0, double alpha, double terror){
    bool stop = false;
    for(int a=0; (a<maxepoh && !stop); a++){
    	double E=0;
    	double mse;
        printf("\nEpoh ke -%d\n", a+1);
        printf("--------------------------------------\n");
        for(int i=0; i<dimensi1; i++){
            double z_in[hiddenlayerneuron];
            double z[hiddenlayerneuron];
            double y_in;
            double y;
            double error;
            double delta1;
            double deltaw[hiddenlayerneuron];
            double deltaw0;
            double delta2in[hiddenlayerneuron];
            double delta2[hiddenlayerneuron];
            double deltav[inputlayerneuron][hiddenlayerneuron];
            double deltav0[hiddenlayerneuron];

            printf("Data ke -%d\n", i+1);
            printf("--------------------------------------\n\n");
            for(int j=0; j<hiddenlayerneuron; j++){
                z_in[j] = v0[j];
                for(int k=0; k<inputlayerneuron; k++){
                    z_in[j] = z_in[j] + v[k][j] * x[i][k];
                }
                printf("z_in ke-%d = %g\n",j+1,z_in[j]);
            }
            printf("\n");
            for(int j=0; j<hiddenlayerneuron; j++){
                z[j] = 1 / (1+exp(0.0 - z_in[j]));
                printf("z ke-%d = %g\n",j+1,z[j]);
            }
            printf("\n");
            y_in = w0;
            for(int j=0; j<hiddenlayerneuron; j++){
                y_in = y_in + w[j]*z[j];
            }
            printf("y_in = %g\n\n",y_in);
            y = 1 / (1+exp(0.0 - y_in));
            // y = y_in;
            printf("y = %g\n\n",y);
            error=t[i]- y;
            printf("Error = %g\n", error);
            E = E+error*error;
            printf("Jumlah Kuadrat Error = %g\n\n", E);
            delta1 = error * y * (1-y);
            printf("delta = %g\n\n", delta1);
            for(int j=0; j<hiddenlayerneuron; j++){
                deltaw[j] = alpha*delta1*z[j];
                printf("delta w ke-%d = %g\n",j+1,deltaw[j]);
            }
            printf("\n");
            deltaw0 = alpha*delta1;
            printf("delta w0 = %.4f\n\n",deltaw0);
            for(int j=0; j<hiddenlayerneuron; j++){
                delta2in[j] = delta1*w[j];
                printf("delta 2 in ke-%d = %g\n",j+1,delta2in[j]);
            }
            printf("\n");
            for(int j=0; j<hiddenlayerneuron; j++){
                delta2[j] = delta2in[j]*z[j]*(1-z[j]);
                printf("delta 2 ke-%d = %g\n",j+1,delta2in[j]);
            }
            printf("\n");
            for(int j=0; j<inputlayerneuron; j++){
                for(int k=0; k<hiddenlayerneuron; k++){
                    deltav[j][k] = alpha*delta2[k]*x[i][j];
                    printf("deltav%d%d = %g\n",j+1,k+1,deltav[j][k]);
                }
            }
            printf("\n");
            for(int j=0; j<hiddenlayerneuron; j++){
                deltav0[j] = alpha*delta2[j];
                printf("deltav0 ke-%d = %g\n",j+1,deltav0[j]);
            }
            printf("\n");
            for(int j=0; j<inputlayerneuron; j++){
                for(int k=0; k<hiddenlayerneuron; k++){
                    v[j][k] = v[j][k] + deltav[j][k];
                    printf("v%d%d = %g\n",j+1,k+1,v[j][k]);
                }
            }
            printf("\n");
            for(int j=0; j<hiddenlayerneuron; j++){
                v0[j] = v0[j] + deltav0[j];
                printf("v%d = %g\n",j+1,v0[j]);
            }
            printf("\n");
            for(int j=0; j<hiddenlayerneuron; j++){
                w[j] = w[j] + deltaw[j];
                printf("w%d = %g\n",j+1,w[j]);
            }
            w0 = w0 + deltaw0;
            printf("\nw0 = %g\n\n",w0);
            printf("\n");
        }
        mse = E/(dimensi1+1);
        printf("mse = %g\n\n",mse);
        if(mse<terror){
            stop = true;
            break;
        }
    }
    printf("hasil\n");
    for(int j=0; j<inputlayerneuron; j++){
        for(int k=0; k<hiddenlayerneuron; k++){
            printf("v%d%d = %g\n",j+1,k+1,v[j][k]);
        }
    }
    printf("\n");
    for(int j=0; j<hiddenlayerneuron; j++){
        printf("v%d = %g\n",j+1,v0[j]);
    }
    printf("\n");
    for(int j=0; j<hiddenlayerneuron; j++){
        printf("w%d = %g\n",j+1,w[j]);
    }
    printf("\nw0 = %g\n",w0);
}

int main(){
    srand(time(NULL));
    double x[dimensi1][inputlayerneuron] = {{1,1},{0,1},{1,0},{0,0}};
    double t[dimensi1] = {0,1,1,0};
    double v[inputlayerneuron][hiddenlayerneuron]={{0.9562,0.7762,0.1623},{0.1962,0.6133,0.0311}};
    // for(int i=0; i<inputlayerneuron; i++){
    //     for(int j=0; j<hiddenlayerneuron; j++){
    //         v[i][j] = fRand(0.0,1.0);
    //     }
    // }
    double v0[hiddenlayerneuron]={0.7496,0.3796,0.7256};
    // for(int i=0; i<hiddenlayerneuron; i++){
    //     v0[i] = fRand(0.0,1.0);
    // }
    double w[hiddenlayerneuron]={0.2280,0.9585,0.6799};
    // for(int i=0; i<hiddenlayerneuron; i++){
    //     w[i] = fRand(0.0,1.0);
    // }
    double w0 = 0.9505;
    // double w0 = fRand(0.0,1.0);
    // double alpha = 0.35000;
    double alpha = 0.2;
    // double terror = 0.0000000001;
    double terror = 0.001;
    backpropagation(x,t,v,v0,w,w0,alpha,terror);
    return 0;
}