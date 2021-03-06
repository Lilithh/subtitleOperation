#ifndef FUCSET_H
#define FUCSET_H


//常量
#define fileInName "./ioFile/subtitle.txt"       //字幕文件名
#define fileOutChName "./ioFile/China.txt"        //汉语部分
#define fileOutEnName "./ioFile/English.txt"        //英语部分
#define fileName "./ioFile/pure.txt"          //合并字幕文件
#define maxLine 10240                  //每行最大字符数
#define Interval 3//中英间隔

//功能
#define serial true           //是否需要第二部分部分的序号？(bool)
#define lineSpace true        //是否每行下保留空行？
#define prio "EN"          //中文CN 还是 英文 "EN" 在前？
#define format true        //考虑显示问题? (CN时txt中显示正常true 或pages显示正常false)

//全局变量
extern int maxlengthC;
extern int maxlengthE;
extern int mergeCheckA;   //合并行数校验

//函数
int extractFile();   //分离初始文件
int mergeFile();    //合并文件




#endif /* FUCSET_H */
