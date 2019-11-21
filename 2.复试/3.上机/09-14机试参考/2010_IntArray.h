#pragma once

// IntArray.h
class IntArray{
public:
    IntArray(int size);          //初始化数组，长度为 size,且赋初值为 0
    ~IntArray();
    int size() const;            //返回数组长度
    int &Item(int i);            //返回 i下标的引用
    bool equal(IntArray &a);     //长度和数据相等返回 True，否则 False
    void assign(IntArray &a);    //将 a中的数组赋值到 this中，若a长度大于this长度，
                                 //则终止程序！ 
    void enlarge(int delta);     //将 this中的数组延长 Delta个单位，
                                 //并将这 Delta个单位的数组赋初值为 0 
    void sort();                 //this中的数组排序，从小到大 
    void display();              //打印数组

private:
    int *array;
    int _size;
};
