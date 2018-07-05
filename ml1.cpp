#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<cmath>
#include<algorithm>

using namespace std;
struct distances{

    float dist;
    float clas;

};
bool compare(distances a , distances b)
{
    if(a.dist<b.dist)
        return true;

    return false;
}
int main()
{
                                                    /* DECLARATION OF VARIABLES */
    int knn = 100;        /* SELECTING FIRST K ITEMS */
    int td = 135;       /* TRAINING DATA */
    int tt = 6;         /* TEST DATA */
    float acc=0;
    int t;
    distances pp[td];   /* DISTANCES BETWEEN THE POINTS */
    float a[150][5];    /* ARRAY TO STORE THE CLASSIFIED DATA */
    float train[td][5]; /* ARRAY TO STORE TRAINING DATA*/
    float test[tt][5];  /* ARRAY TO STORE TESTED DATA */
    int i =0,j;
    int k,y;
    int p=0;
    FILE *fp =fopen("iris.txt","r");

    FILE *fout1 = fopen("fulliris.txt","w");
    FILE *fout2 = fopen("test.txt","r");
    float sl,sw,pl,pw,l;
    char s[100];
    float ne;
    while(fscanf(fp,"%f,%f,%f,%f,%s",&sl,&sw,&pl,&pw, s)!=EOF)
    {

        a[i][0] = sl;
        a[i][1] = sw;
        a[i][2] = pl;
        a[i][3] = pw;

        if(!strcmp(s,"Iris-setosa"))
        {
            a[i][4] = 0;
        }
        else if(!strcmp(s,"Iris-versicolor" ))
        {
            a[i][4] = 1;
        }
        else if(!strcmp(s,"Iris-virginica"))
        {
            a[i][4] = 2;
        }

        i++;
    }
            for(j=0;j<td;j++)
            {
                fprintf(fout1,"%f %f %f %f %f \n",a[j][0],a[j][1],a[j][2],a[j][3],a[j][4]);
            }
    fclose(fout1);

   p = 0;
   FILE *fout = fopen("training.txt", "r");
   while(fscanf(fout,"%f%f%f%f%f",&sl,&sw,&pl,&pw,&ne)!=EOF)
    {
        train[p][0] = sl;
        train[p][1] = sw;
        train[p][2] = pl;
        train[p][3] = pw;
        train[p][4] = ne;
        p++;
    }

    p=0;
     while(fscanf(fout2,"%f%f%f%f%f",&sl,&sw,&pl,&pw, &ne)!=EOF)
    {

        test[p][0] = sl;
        test[p][1] = sw;
        test[p][2] = pl;
        test[p][3] = pw;
        test[p][4] = ne;
        p++;
    }

    for(i=0 ;i<tt;i++)
    {
        for(j=0 ;j< td ; j++)
        {
            float temp=0;
            for(y=0 ; y<4 ; y++)
            {
                temp+=pow(test[i][y] - train[j][y],2);

            }

            pp[j].dist = sqrt(temp);
            pp[j].clas = train[j][4];

        }

        sort(pp,pp+td,compare);

        int c0=0,c1=0,c2=0,maxx=0;
        for(t=0 ;t< knn;t++)
        {
            if(pp[t].clas == 0)
            {
                c0++;
            }
            else if(pp[t].clas==1)
            {
                c1++;
            }
            else
            {
                c2++;
            }
        }
            int index = 0;
            maxx = c0;
            if(maxx < c1)
            {
                maxx = c1;
                index = 1;
            }
            if(maxx < c2)
            {
                index = 2;
            }

            if(index == test[i][4])
                acc++;

    }
cout<<"ACCURACY IS" <<" "<<(acc/tt)*100;
}

