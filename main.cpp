#include <iostream>
#include "fucSet.h"



using namespace std;

int maxlength = 0;  //.h全局
int main(){
    
    bool f1 = extractFile();    //分离初始文件 得到中英字
    bool f2 = mergeFile();      //合并文件

    if(f1) cout << "提取操作完成" << endl;
    else {
        cout << "初始文件打开失败" << endl;
        return 0;
    }
    if(f2) cout <<"合并结束"<<endl;
    else {
        cout << "写入文件再打开失败" <<endl;
        return 0;
    }
    //cout << f1?"提取操作完成":"初始文件打开失败"<< endl;
    //cout << f2?"合并结束":"写入文件再打开失败" << endl;
    if(f1 && f2) cout << "succeed!" << endl;
    return 1;
}







/**



ofstream outfile(fileName);
ifstream infile1(fileOutChName);
ifstream infile2(fileOutEnName);
char tem[maxLine];                  //暂存字符数组
int k = 1;
if(infile1.is_open() && infile2.is_open()) {
    while(infile1.good() && infile2.good() && !infile1.eof() && !infile2.eof()){
        string aa, bb;
        memset(tem, 0, maxLine);
        infile1.getline(tem, maxLine);
        aa = tem;                       //得到一行汉语aa
        memset(tem, 0, maxLine);
        infile2.getline(tem, maxLine);
        bb = tem;                        //得到一行英语bb
        int aalen = aa.length();         //汉语长度
        
        int blocklen = maxlength-aalen + Interval;
        //cout << aalen << " and " << blocklen << endl;
        if(!aalen) continue;                              //空行的字符串 s[0]为空 以字符数组形式访问可以，以下面.append访问会报越界错误
        for(int ver = 0; ver < blocklen; ver ++) {
            aa.append(" ");                    //追加空格 形成统一结尾长度
        }
        string bbb = bb.substr(2);         //英语部分去除序号
        //cout << bbb << endl;
        aa += bbb;
        //cout << "文件 " << aa << endl;
        
        outfile << aa << endl;           //整合行 输出到文件
        }
        cout << "合并结束" << endl;
        } else cout << "写入文件再打开错误" << endl;
        
        infile1.close(); infile2.close(); outfile.close();
        
        cout << "合并字幕文件成功" << endl;

**/
