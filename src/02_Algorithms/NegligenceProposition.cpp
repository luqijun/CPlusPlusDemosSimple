#include <string>
#include <iostream>

using namespace std;

const int MAXN = 100;
int arr[MAXN];

void OutputResult(int n){
    string res = "";
    for (size_t i = 0; i < n; i++)
    {
        res += std::to_string(arr[i]);
        //cout << arr[i];
        if(i!=n-1)
            res += ' ';
            //cout << ' ';
    } 
    cout << res << endl;
    fflush(stdout);  
    cout.clear();
}

int main()
{
    int n;
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        arr[i] = 0;
    }
    
    int currentLastIndex=1;
    arr[currentLastIndex] = -1;
    OutputResult(n);

    string res;
    while (cin >> res && currentLastIndex<n){
        if (res == "AC")
            break;

        if (res == "RE")
        {
           arr[currentLastIndex]=0;
           arr[currentLastIndex+1]=-1; 
           currentLastIndex++;   
           OutputResult(n);
        }

        if (res == "WQ")
        {
            arr[currentLastIndex-1]=!arr[currentLastIndex-1];
            arr[currentLastIndex]=0;
            arr[currentLastIndex+1]=-1;    
            currentLastIndex++;
            OutputResult(n);
        }
        fflush(stdin);
    }
}