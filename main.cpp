#include <iostream>
#include <fstream>
#include <string>

#define fileInName "subtitle.txt"       //字幕文件名
#define fileOutChName "China.txt"        //汉语部分
#define fileOutEnName "English.txt"        //英语部分
#define fileName "pure.txt"          //合并字幕文件
#define maxLine 10240                  //每行最大字符数
#define Interval 6                   //中英间隔

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
                    outfile1 << i << "  " << part1 << endl; //立即写入文件
                    outfile1 << flush;   //保存？
                    i++;
                    if(part1.length() > maxlength) maxlength = s.length();
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
        outfile1 << "结束" <<endl; outfile2 << "end" << endl;  //读取结束 关闭文件
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
    return 1;
}
