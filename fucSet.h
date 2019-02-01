#ifndef FUCSET_H
#define FUCSET_H


//常量
#define fileInName "./inAndOutFile/subtitle.txt"       //字幕文件名
#define fileOutChName "./inAndOutFile/China.txt"        //汉语部分
#define fileOutEnName "./inAndOutFile/English.txt"        //英语部分
#define fileName "./inAndOutFile/pure.txt"          //合并字幕文件
#define maxLine 10240                  //每行最大字符数
#define Interval 3                   //中英间隔

//功能
#define serial true           //是否需要英文部分的序号？
#define lineSpace true        //是否每行下保留空行？

//全局变量
extern int maxlength;

//函数
int extractFile();   //分离初始文件
int mergeFile();    //合并文件




#endif /* FUCSET_H */
