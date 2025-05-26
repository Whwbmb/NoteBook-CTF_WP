#include <iostream>
using namespace std;
int ga=0,gb=0;
void judge(int a,int b){
	if(a==0&&b==0)return ;
	if(a==0&&b==1){
	gb++;
	return ;
	}
	if(a==0&&b==2){
	ga++;
	return;
	}
	if(a==0&&b==3){
	ga++;
	return;
	}
	if(a==0&&b==4){
	gb++;
	return;
	}
	if(a==1&&b==0){
	ga++;
	return;
	}
	if(a==1&&b==1)return;
	if(a==1&&b==2){
	gb++;
	return;
	}
	if(a==1&&b==3){
	ga++;
	return;
	}
	if(a==1&&b==4){
	gb++;
	return;
	}
	if(a==2&&b==0){
	gb++;
	return;
	}
	if(a==2&&b==1){
	ga++;
	return;
	}
	if(a==2&&b==2)return;
	if(a==2&&b==3){
	gb++;
	return;
	}
	if(a==2&&b==4){
	ga++;
	return;
	}	
	if(a==3&&b==0){
	gb++;
	return;
	}
	if(a==3&&b==1){
	gb++;
	return;
	}
	if(a==3&&b==2){
	ga++;
	return;
	}
	if(a==3&&b==3)return;
	if(a==3&&b==4){
	ga++;
	return;
	}
	if(a==4&&b==0){
	ga++;
	return;
	}
	if(a==4&&b==1){
	ga++;
	return;
	}
	if(a==4&&b==2){
	gb++;
	return;
	}
	if(a==4&&b==3){
	gb++;
	return;
	}
	if(a==4&&b==4)return ;
	
}

int main(){
	int N,Na,Nb;
	int n=0;
	int NA[201],NB[201];
	cin>>N>>Na>>Nb;
	while(n<Na){
	cin>>NA[n];
	n++;
	}
	n=0;
	while(n<Nb){
	cin>>NB[n];
	n++;
	}
	n=0;
	while(n<N){
	judge(NA[n%Na],NB[n%Nb]);
	n++; 
	}
	cout<<ga<<" "<<gb;
}



//另外一种题解，编写代码更快更便捷
//使用一个5*5的数组矩阵代表25种猜拳结果
//通过两个数组来确定这个矩阵中元素的坐标，以此来确定本次判定的得分情况
// #include <iostream>

// using namespace std;

// int N;                  //猜拳次数
// int N_A;                //A的猜拳周期长度
// int N_B;                //B的猜拳周期长度
// int circle_A[205];      //A的猜拳周期
// int circle_B[205];      //B的猜拳周期
// int score_A = 0;		//A的得分
// int score_B = 0;		//B的得分
// int game[5][5] =        //游戏的结果情况，1表示A赢，-1表示A输，0表示平
// {
// 	{0, -1, 1, 1, -1},
// 	{1, 0, -1, 1, -1},
// 	{-1, 1, 0, -1, 1},
// 	{-1, -1, 1, 0, 1},
// 	{1, 1, -1, -1, 0}
// };

// int main(void)
// {
// 	cin >> N >> N_A >> N_B;
	
// 	for(int i = 0; i < N_A; i++)
// 	{
// 		cin >> circle_A[i];
// 	}
// 	for(int i = 0; i < N_B; i++)
// 	{


// 		cin >> circle_B[i];
// 	}
	
// 	int i = 0;          //遍历A的猜拳周期
// 	int j = 0;          //遍历B的猜拳周期
// 	while(N--)
// 	{
// 		if(i >= N_A)
// 		{
//             i = 0;
// 		}
// 		if(j >= N_B)
// 		{
//             j = 0;
// 		}
		
// 		//比较结果
// 		int result = game[circle_A[i]][circle_B[j]];
// 		if(result == 1)
// 		{
// 			score_A++;
// 		}
// 		else if(result == -1)
// 		{
// 			score_B++;
// 		}
		
// 		i++;
// 		j++;
// 	}
	
// 	cout << score_A << " " << score_B;
	
// 	return 0;
// }