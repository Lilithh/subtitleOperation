#include <iostream>
#include <fstream>
#include <string>
#include "fucSet.h"

using namespace std;
int mergeFile(){
    ofstream outfile(fileName);
    ifstream infile1(fileOutChName);
    ifstream infile2(fileOutEnName);
    char tem[maxLine];                  //暂存字符数组
    int mergeCheckB = 0;  //校验行数
    if(infile1.is_open() && infile2.is_open()) {
        while(infile1.good() && infile2.good() && !infile1.eof() && !infile2.eof()){
            mergeCheckB ++;
            string aa, bb;
            memset(tem, 0, maxLine);
            infile1.getline(tem, maxLine);
            aa = tem;                       //得到一行汉语aa
            memset(tem, 0, maxLine);
            infile2.getline(tem, maxLine);
            bb = tem;                        //得到一行英语bb
            int aalen = aa.size();         //汉语长度
            int bblen = bb.size();
            //cout << aalen << " and " << blocklen << endl;
            if(!aalen || !bblen) {  //空行的字符串 s[0]为空 以字符数组形式访问可以，以下面.append访问会报越界错误
                if(lineSpace) outfile<<endl;
                -- mergeCheckB;
                continue;
            }
            /*
             计算每行中汉字的个数
             汉字占3个lenth, 汉字标点，英文字母标点占1个lenth
             汉字屏上占1.5个英文字母， 其他占一个英文字母
             需要调整 才能在显示中对齐，末端
             汉字内码由两个（三个？）ASCII码组成 且都小于0
             */
            int count = 0;
            //int xxplace = aa.find("·");
            for(int i = 0; i<aalen; ){
                if(aa[i]<0) {            //是汉字 或· 汉字字符
                    count++;
                    i += 3;
                } else i++;
            }
            //cout << xxplace << endl;
            //cout << "汉字数" << count << endl;
            float showlen = 1.5 * count + aalen-(3*count);
            float blacklenC = (maxlengthC/2) - showlen + Interval;  //假设maxlen全汉字，算成显示长度 maxlenth/3 * 1.5
            
            float blacklenE = maxlengthE - bblen + Interval;    //英文在前的black
            if (prio == "CN") {
                for(int ver = 0; ver < blacklenC+0.5; ver ++) {
                    aa.append(" ");                    //追加空格 形成统一结尾长度
                }
                string bbb = "";
                if(mergeCheckB<10) {
                    bbb = bb.substr(1);
                } else if(mergeCheckB<100) {
                    bbb = bb.substr(2);
                } else {
                    bbb = bb.substr(3);     //英语部分去除序号
                }
                
                //cout << aa.size() << endl; //测试
                aa += serial ? bb : bbb;
                outfile << aa << endl;           //整合行 输出到文件
            } else if(prio == "EN") {    //英先
                for(int vei = 0; vei < blacklenE; vei ++) {
                    bb.append(" ");
                }
                string aaa = "";
                if(mergeCheckB<10) {
                    aaa = aa.substr(1);
                } else if(mergeCheckB<100) {
                    aaa = aa.substr(2);
                } else {
                    aaa = aa.substr(3);     //汉语部分去除序号
                }
                bb += serial ? aa : aaa;
                outfile << bb << endl;
            } else break;
            
        }
        if(mergeCheckB < mergeCheckA) return -2;    //while中出错 一般是CN EN那里
    } else return -1;
    
    infile1.close(); infile2.close(); outfile.close();
    return 1;
}
