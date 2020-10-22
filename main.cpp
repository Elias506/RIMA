#include <iostream>
#include <string>

using namespace std;

const string alf[4][10] = {
    {" ", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},//строка 0
    {" ", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},//строка 1
    {" ", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},//строка 2
    {" ", "M", "MM", "MMM", "  ", " ", "  ", "   ", "    ", "  "} //строка 4
};

const char q[8] = {"IVXLCDM"};

int per(char a)
{
	int p;
	switch(a) {
		case 'I': p = 1; break;
		case 'V': p = 5; break;
		case 'X': p = 10; break;
		case 'L': p = 50; break;
		case 'C': p = 100; break;
		case 'D': p = 500; break;
		case 'M': p = 1000; break;
        default: p = 0; break;
	}
	return p;
}

int searhcInArrayQ(char a)
{
    int r;
    if (a == '\0')
    {
        return -2;
    }
    for (int j = 0; j < 7; j++)
    {            
        if (a == q[j])
        {
            r = j;
            break;
        }
    }
    return r;
}


int main() 
{   
    string s;
    char a, b;
    int Ia, Ib, Ic, k, shift;
    cin >> s;
    int ans = 0;
    int sumA = 3001;
    int sumB = 0;
    int j = 0;  
    bool err = false;

    if (s[0] == 'M')
    {
        while (s[j] == 'M')
        {           
            j++;
            ans += 1000;
            sumA += 1000;
        }
    } 
    for (int i = j; i < s.length(); i++)
    {
        a = s[i];
        b = s[i + 1];
        Ia = searhcInArrayQ(a);
        Ib = searhcInArrayQ(b);
        //printf("%c %c %d %d\n", a, b, Ia, Ib);
        if (Ia > Ib)
        {
            if (Ia - Ib == 1)
            {
                k = 1;
                while (s[i + k + 1] == b)
                {
                    k++;
                    if (k > 3)
                    {
                        err = true;
                        break;
                    }
                }
                if (err) {break;} 
                sumB = per(a) + per(b) * k;  
                shift = k; 
            }
            else
            {
                sumB = per(a);
                shift = 0;
            }      
        }
        else
        {
            if (Ia < Ib)
            {
                if ((Ib - Ia > 2) /*|| (searhcInArrayQ(s[i + 2]) < Ia)*/)
                {
                    err = true;
                    break;
                }
                sumB = per(b) - per(a);
                shift = 1;              
            }
            else
            {
                //Ia = Ib
                //...
                
                if (Ia % 2 == 1)
                {
                    err = true;
                    break;
                }
                k = 2;
                while (s[i + k] == b)
                {
                    k++;
                    if (k > 3)
                    {
                        err = true;
                        break;
                    }
                }
                if (err) {break;}
                
                sumB = per(a)*k;
                shift = k - 1;
            }
            
        }
        if (sumA < sumB)
        {
            err = true;
            break;
        }
        ans += sumB;
        sumA = sumB;
        i += shift;      
    }

    if (!err)
    {
        cout << ans << endl;
    }
    else
    {
        cout << "Ошибка" << endl;
    }   
} 
