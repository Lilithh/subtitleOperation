#include <iostream>
#include <fstream>
#include <string>
#include "fucSet.h"

using namespace std;

int extractFile(){
    ofstream outfile1(fileOutChName);//实例化写入文件对象 并打开
    ofstream outfile2(fileOutEnName);
    ifstream infile(fileInName);     //～读取文件～
    
    if(!outfile1 || !outfile2) {        //确定写入文件打开 不知道有什么用
        cout<< "no file" << endl;
        exit(1);
    }
    
    char buf[maxLine];
    string s;    //每次读取一行 存储
    
    int i = 1, j = 1;
    if(infile.is_open()){   //读取文件打开成功
        while(infile.good() && !infile.eof()){   //文件是否打开正确 是否结束
            memset(buf, 0, maxLine);
            infile.getline(buf, maxLine);
            s = buf;                            //读一行 赋给s
            //对 s 进行操作
            if(s.rfind("Dialogue", 12) != -1){     //找到字幕起始行
                s = s.substr(63);              //去除前面多余部分 这里是63位（需调整）
                if(s[0] != '{') {
                    //汉字部分
                    int p = s.find('\\');      //汉字结束部分标示 位置(调整)
                    string part1 = s;
                    part1.erase(p);           //得到汉字部分
                    if(part1.find("摩登家庭")+1) continue;  //需要去除这一行，因为英语部分会读到汉语 导致转码问题。 找到的时候返回位置0，要加一
                    //outfile1 << part1 << endl;//测试
                    outfile1 << i << "  " << part1 << endl; //立即写入文件
                    outfile1 << flush;   //保存？
                    i++;
                    if(part1.size() > maxlength) maxlength = s.size();
                    //英语部分
                    int q = s.find("{\\shad1}");
                    string part2 = s.substr(q+8);        //得到英语部分串
                    outfile2 << j << "  " << part2 << endl;   //立即写入文件
                    outfile2 << flush;   //保存？
                    j++;
                }
                outfile1 << endl;
                outfile2 << endl;            //冗余字幕 输出空行代替
            }
            else continue;       //非字幕部分
        }
        outfile1 << "结束" <<endl; outfile2 << "  end" << endl;  //读取结束 关闭文件
        outfile1.close();
        outfile2.close();
        infile.close();
    }
    else return -1;
    
    
    return 1;
}
 




