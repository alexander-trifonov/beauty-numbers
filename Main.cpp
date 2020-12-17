#include <iostream>
#include <math.h>

using namespace std;

//Ineffective + doesn't work on big numbers
unsigned long long int fact(unsigned long long int value)
{
    if (value < 0)
        return 0;
    if (value == 0)
        return 1;
    else
        return value * fact(value - 1);
}

long int C(int n, int k)
{
    return (fact(n) / (fact(n - k) * fact(k)));
}

//Effective
unsigned int nChoosek(unsigned int n, unsigned int k)
{
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;

    int result = n;
    for (int i = 2; i <= k; i++) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}


//Task: Write the number of 13-digit beautiful numbers with leading zeros in 13-decimal system. (The number is beautiful if his left and right-end sums are equal, e.g. 2111110111121 is beautiful)
//
//Method: Stars and bars (combintation)
//https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)
//Korablev, Tasks 1,8: http://math.csu.ru/new_files/students/lectures/diskr_matem/korablev_combinatoric.pdf
//
//Example:
//0CCCCC0CCCCC0 is beautiful, because left-sum and right-sum are equal (0+12+12+12+12+12 == 12+12+12+12+12+0) = 12*5 = 60;
//Boxes: 6
//Let's put "12" (as max) in each box, it's 12*6 = 72 balls, but have only 60; 
//So, we need to calculate how much options we have to extract those 12 balls (equal to adding 12 balls)
//It's can be made by placing bars (5 in this case). Let bars be 1, balls 0:
//|(00100100100100100)| = 12+5 = 17
//C(n=17,k=5);
//But we have left and right ends of number, so C(n=17,k=5)^2
//Plus, multiply by 13 if number length is odd;
//(C(n=17,k=5)^2 * 13) for sum == 60; But we have sums from 0 to 12*6;

void main()
{
    int NumberLength = 13;
    int NumberSystem = 13;

    int Boxes = NumberLength / 2;
    unsigned long int sum = 0;
    for (int i = 0; i < (NumberSystem-1)*Boxes; i++) //for all sums
    {
        //((NumberSystem-1) * Boxes - i) is how many balls we have to extract
        //((NumberSystem-1) * Boxes - i) + (Boxes - 1) + (Boxes - 1) is "n", aka |(00100100100100100)|
        sum = sum + pow(nChoosek(((NumberSystem-1) * Boxes - i) + (Boxes - 1), (NumberSystem-1) * Boxes - i),2);
    }
    if (NumberLength % 2 == 1)
    {
        sum = sum * NumberSystem;
    }

    cout << sum << endl;

}