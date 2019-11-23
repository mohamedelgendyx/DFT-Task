#include <iostream>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;

#define PI 3.14159265
typedef long long  ll;

struct Complex
{
    double real;
    double img;
};

class DFT
{
    private:
        ll N;
        vector<double>x;
        vector<vector<Complex>>w;
        vector<Complex> resX;
        vector<double> Mag;
        vector<double> Phase;

    public:
        void setN(ll n) { N=n; }

        void setX(vector<double>&xn)
        {
            for(int i=0;i<N;i++)
                x.push_back(xn[i]);
        }

        void setW()
        {
            double theta;
            Complex temp;
            for(int i=0;i<N;i++)
            {
                vector<Complex> row;
                for(int j=0;j<N;j++)
                {
                    theta=(2*PI*i*j/N);
                    temp.real=round(cos(theta)*1e7)/1e7;
                        if(fabs(temp.real)==0){temp.real=0;}//handle -0
                    temp.img=-round(sin(theta)*1e7)/1e7;
                        if(fabs(temp.img)==0){temp.img=0;}//handle -0
                    row.push_back(temp);


                }
                w.push_back(row);
            }
        }

       /* void getW()
        {
            cout << "[W]    = ";
            for(int i=0;i<N;i++)
            {
                 for(int j=0;j<N;j++)
                    cout<< w[i][j].real << ((w[i][j].img >= 0) ? "+j" : "-j") << abs(w[i][j].img) << " " ;
                 cout <<"\n         ";
            }
            cout<<"\n";
        }
       */
        void set_resX()
        {
            Complex temp;
            for(int k=0; k<N; k++)
            {
                temp.real = 0;
                temp.img = 0;
                for(int n=0; n<N; n++)
                {
                   temp.real += w[k][n].real * x[n];
                   temp.img  += w[k][n].img * x[n];
                }
            resX.push_back(temp);

            }

        }

        void setMag()
        {
            for (int i=0; i<N ; i++)
            {
                Mag.push_back(sqrt(pow(resX[i].real,2) + pow(resX[i].img,2)));
            }
        }

        void setPhase()
        {
           for (int i=0;i<N;i++)
            {
                double result;
                if (resX[i].real == 0)
                {
                    if(resX[i].img >0)
                        result = 90.0;
                    else if(resX[i].img <0)
                        result = 270.0;
                }
                else if (resX[i].img == 0)
                {
                    if(resX[i].real >0)
                        result = 0.0;
                    else if(resX[i].real <0)
                        result = 180.0;
                }
                else if (resX[i].img >0)
                {
                    if(resX[i].real > 0 )
                    {
                        result = resX[i].img / resX[i].real;
                        result = atan (result) * 180 / PI;
                    }
                    else if (resX[i].real < 0 )
                    {
                        result = resX[i].img / resX[i].real;
                        result = atan (result) * 180 / PI;
                        result = 180 - (result * -1);
                    }
                }
                else if (resX[i].img <0)
                {
                    if(resX[i].real < 0)
                    {
                        result = resX[i].img / resX[i].real;
                        result = atan (result) * 180 / PI;
                        result += 180;
                    }
                    else if(resX[i].real > 0)
                    {
                        result = resX[i].img / resX[i].real;
                        result = atan (result) * 180 / PI;
                        result = 360 - (result * -1);
                    }
                }
                Phase.push_back(result);
            }
        }

        void get_resX()
        {
            cout << "X[k]   = {";
            for(int i=0;i<N-1;i++)
                cout<< resX[i].real << ((resX[i].img>= 0) ? "+j" : "-j") << abs(resX[i].img) << " , " ;
            cout << resX[N-1].real << ((resX[N-1].img>= 0) ? "+j" : "-j") << abs(resX[N-1].img) << "}\n";
        }

        void getMag()
        {
            cout << "Mag    = {";
            for(int i=0;i<N-1;i++)
                cout << Mag[i] << " , " ;
            cout << Mag[N-1] <<"}\n";
        }

        void getPhase()
        {
            cout << "Phase  = {";
            for(int i=0;i<N-1;i++)
                cout << Phase[i] << " , " ;
            cout << Phase[N-1] <<"}\n";
        }

        void execute(ll n,vector<double>&xn)
        {
            setN(n);
            setX(xn);
            setW();
            //getW();
            set_resX();
            get_resX();
            setMag();
            getMag();
            setPhase();
            getPhase();
        }

};



int main()
{
    ll N;
    cout<<"Enter value of N: ";
    cin>>N;

    vector<double>xn;
    cout<<"Enter The Discrete Input X(n): ";
    for(int i=0;i<N;i++)
    {
        double x;
        cin>>x;
        xn.push_back(x);
    }

    DFT t;
    cout<<"\n";
    t.execute(N,xn);

    return 0;
}
