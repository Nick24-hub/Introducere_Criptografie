#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

ifstream fin("crypto.txt");
ofstream fout("out.txt");

double frecvAlf[26] = {0.08167,0.01492,0.02782,0.04253,0.12702,0.02228,0.02015,0.06094,0.06966,0.00153,0.00772,0.04025,0.02406,0.06749,0.07507,0.01929,0.00095,0.05987,0.06327,0.09056,0.02758,0.00978,0.02360,0.00150,0.01974,0.00074 };

string shiftStr(string &y,int s)
{
    string B;
    for (int i = 0;i < y.length();i++)
    {
        B += (y[i] - 'A' + s) % 26 + 'A';
    }
    return B;
}

double DetIC(int fr[26], string &y)
{
    double IC=0;
    for (int i = 0;i < 26;i++)
    {
        if (fr[i] < 1)
            IC += 0;
        else
            IC += ((double)fr[i] / y.length()) * (((double)fr[i] - 1) / (y.length() - 1));
    }
    return IC;
}

int DetKeyLength(string &a)
{
    int j, m, fr[26] , l, keyLength;
    double IC,medIC,bestMed=0.065;
    string y;
    for (m = 2;m <= 100;++m)
    {
        y = "";
        medIC = 0;
        for (j = 0;j < m;++j)
        {
            for (l = 0;l < 26;l++)
                fr[l] = 0;
            l = j;
            while (l < a.length())
            {
                y += a[l];
                l += m;
            }
            for (int i = 0;i < y.length();++i)
                fr[y[i] - 'A']++;
            IC = DetIC(fr, y);
            medIC += IC;
        }
        medIC /= m;
        if (m == 2)
        {
            bestMed = medIC;
            keyLength = 2;
        }
        else if (fabs(medIC - 0.065) <fabs( bestMed - 0.065 ))
            {
                bestMed = medIC;
                keyLength = m;
            }
    }
    return keyLength;
}

double DetMIC(int fr[26], string &B)
{
    double MIC = 0;
    for (int i = 0;i < 26;++i)
    {
        MIC += frecvAlf[i] * ((double)fr[i] / B.length());
    }
    return MIC;
}

string DetKey(string &a, int kl)
{
    int l,fr[26],s,bestS,k;
    double MIC,bestMIC;
    string y,key="";
    for (int j = 0;j < kl;++j)
    {
        y = "";
        l = j;
        while (l < a.length())
        {
            y += a[l];
            l += kl;
        }
        for (s = 0;s < 26;++s)
        {
            for ( k = 0;k < 26;++k)
                fr[k] = 0;
            string B = shiftStr(y, s);
            for ( k = 0;k < B.length();++k)
                fr[B[k] - 'A']++;
            MIC = DetMIC(fr, B);
            if (s == 0)
            {
                bestMIC = MIC;
                bestS = 0;
            }
            else if (fabs(MIC - 0.065) < fabs(bestMIC - 0.065))
            {
                bestMIC = MIC;
                bestS = s;
            }
        }
        key += (26-bestS)%26+'A';
    }
    return key;
}

int main()
{   
   string crypto;
   fin >> crypto;
   int keyLength = DetKeyLength(crypto);
   cout << keyLength << '\n';
   string key = DetKey(crypto,keyLength);
   cout << key << '\n';
   int a,x;
   char c;
   for (int i = 0;i < crypto.length();++i)
   {
       a = i % keyLength;
       x = crypto[i] - key[a];
       if (x >= 0)
           c = x + 'A';
       else c = 26 + x + 'A';
       fout << c;
   }
}

