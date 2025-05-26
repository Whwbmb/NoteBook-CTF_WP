# include <iostream>
# include <cmath>
using namespace std;

void check(int n){
	int flag;
	if(n==1)cout<<"2(0)";
	else if(n==2)cout<<"2";
	else if(n==3)cout<<"2+2(0)";
	else if(n==4)cout<<"2(2)";
	else if(n==8)cout<<"2(2+2(0))";
	else{
		for(int i=0;pow(2,i)<=n;i++){
			flag=i;
		}
		cout<<"2(";
		check(flag);
		cout<<")";
		cout<<"+";
		check(n-pow(2,flag));
			
		
	} 
	
}

int main(){
	
int n;
cin>>n;
check(n);

}




//更合理更清晰的答案：
#include <iostream> //不解释
#include <cmath> //其中有log2(x)和pow(x,y)函数，具体作用往下看
using namespace std;
void divide(int x)
{
    bool flag = false; //...判断是否是第一个，如果是的话就不输出加号
    while (x != 0)
    {
        int t = int(log2(x));//使用log2和int取整替换了原来的使用for循环得到幂指数的方法
        /*
        log2(x)这个函数求以2为底x的对数，例如log2(8)返回3，因为2^3=8
        而这里把返回值强制转换为int是为了找到离x最近又小于x的能表示为2^k的数
        例如int(log2(137))就能返回7，而2^7=128，恰为离137最近的能表示为2^k的数
        */
        if (flag) cout << "+"; //开头不输出加号
        if (t == 1) cout << "2"; //如果这一项是1，输出2，不递归
        else if (t == 0) cout << "2(0)"; //如果这一项是0，输出2(0)，不递归
        else
        {
            cout << "2(";
            divide(t); //递归一层，把括号里的数分解输出
            cout << ")";
        }
        x -= pow(2,t); //继续处理下一项
        flag = true;
    }
}
int main()
{
    int n;
    cin >> n;
    divide(n);
    return 0;
}





//另外一种处理加号的思路
#include<iostream>
#include<cmath>
using namespace std;
int a;
void fff(int x)
{
    for(int i=14;i>=0;i--) //两万的数据最多是2（14）
    {
        if(pow(2,i)<=x){
        //pow（n，m）在cmath库中，返回n^m；枚举出第一个幂次方
            if(i==1) cout<<"2"; //2（1）不用再往后分解了且2^1输出为2，单独出来
            else if(i==0) cout<<"2(0)"; //2（0）也不用再往后分解了，单独出来
            else{ //若i>1则继续分解指数i
                cout<<"2(";
            fff(i);
            cout<<")";
            }
            x-=pow(2,i); //继续循环分解余下的
            if(x!=0) cout<<"+";
            //加号处理的最简单方法：若此x还没分解完，则后面还有项，所以输出一个+号
        }
    }
}
int main()
{
    cin>>a;
    fff(a);
    return 0;
}