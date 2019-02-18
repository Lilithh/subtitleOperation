#include <iostream>
#include "fucSet.h"



using namespace std;

int maxlengthC = 0;
int maxlengthE = 0;
int mergeCheckA = 0;      //.h全局

int main(){
    
    int f1 = extractFile();    //分离初始文件 得到中英字
    int f2 = mergeFile();      //合并文件
    if(f1==1) cout << "提取操作完成" << endl;
    else {
        cout << "初始文件打开失败" << endl;
        return 0;
    }
    if(f2==1) cout <<"合并结束"<<endl;
    else {
        cout << "写入文件再打开失败" <<endl;
        return 0;
    }
    //cout << f1?"提取操作完成":"初始文件打开失败"<< endl;
    //cout << f2?"合并结束":"写入文件再打开失败" << endl;
    if(f1 && f2) cout << "succeed!" << endl;
    return 1;
}


