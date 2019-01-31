#include <iostream>
#include <fstream>
#include <string>

#define fileInName "subtitle.txt"       //字幕文件名
#define fileOutChName "China.txt"        //汉语部分
#define fileOutEnName "English.txt"        //英语部分
#define fileName "pure.txt"          //合并字幕文件
#define maxLine 10240                  //每行最大字符数
#define Interval 3                   //中英间隔

//功能
#define serial true           //是否需要英文部分的序号？
#define lineSpace true        //是否每行下保留空行？

using namespace std;

int main(){
    

    ofstream outfile1(fileOutChName);//实例化写入文件对象 并打开
    ofstream outfile2(fileOutEnName);
    ifstream infile(fileInName);     //～读取文件～
    
    if(!outfile1 || !outfile2) {        //确定写入文件打开 不知道有什么用
        cout<< "no file" << endl;
        exit(1);
    }

    char buf[maxLine];
    string s;    //每次读取一行 存储
    
    int i = 1, j = 1;int maxlength = 0;
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
        
        cout << "提取操作完成" << endl;
    }
    else cout << "初始文件打开失败" << endl;
    
    /*
        整合文件
    */
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
            int aalen = aa.size();         //汉语长度
            
            //cout << aalen << " and " << blocklen << endl;
            if(!aalen) {  //空行的字符串 s[0]为空 以字符数组形式访问可以，以下面.append访问会报越界错误
                if(lineSpace) outfile<<endl;
                continue;
            }
            //cout << aa.size() << endl; //测试
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
            float blacklen = (maxlength/2) - 10 - showlen + Interval;  //假设maxlen全汉字，算成显示长度 maxlenth/3 * 1.5
            
            for(int ver = 0; ver < blacklen+0.5; ver ++) {
                aa.append(" ");                    //追加空格 形成统一结尾长度
            }
            string bbb = bb.substr(2);         //英语部分去除序号
            //cout << aa.size() << endl; //测试
            aa += serial ? bb : bbb;
            //cout << maxlength << "  " << aalen << "  " << blocklen << "       " << aa.size() << endl;
            
            outfile << aa << endl;           //整合行 输出到文件
        }
        cout << "合并结束" << endl;
    } else cout << "写入文件再打开错误" << endl;
    
    infile1.close(); infile2.close(); outfile.close();
    
    cout << "合并字幕文件成功" << endl;
    
    //string t1 = "测", t2 = "a", t3 = "\"", t4 = "-", t5 = " ", t6 = "·";
    //cout<<"测 "<<t1.size()<<"  a "<<t2.length()<<"  \" "<<t3.length()<<"  - "<<t4.length()<<" 空格 "<<t5.length()<<"  · "<<t6.length()<<endl;//测试字符lenth
    return 1;
}
