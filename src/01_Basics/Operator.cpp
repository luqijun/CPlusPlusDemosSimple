
/// @brief 异或运算符使用
void XorTest()
{
   
    // 交换两个变量  按位与时 如果第一次不相同  原理：1^0^0=1; 0^1^1=0
    int a = 1;
    int b = 2;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    // 判断两个数是否相等
    bool equal = (a ^ b) == 0;

    // 任意数^1都会翻转 原理：0^1=1; 1^1=0;

    // 任意数^0值不变 找出非成对的数 如A^B^C^D^C^B^A=D   

}

int main()
{
    XorTest();
}