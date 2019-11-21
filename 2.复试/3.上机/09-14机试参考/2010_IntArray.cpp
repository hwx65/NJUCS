// IntArray.cpp
#include "2010_IntArray.h"
#include <iostream>

IntArray::IntArray(int size){
    size=size>0? size:0;  //如果size为负数,将无法创建对象,但为0可以
    array = new int[size];
    _size = size;
    for(int i=0; i< size; i++) {
        array[i] = 0;
    }
}

IntArray::~IntArray(){
    delete []array;
}

int IntArray::size() const {
    return _size;
}

int &IntArray::Item(int i){
    return array[i];      //沿袭C++不检查数组越界的传统
}

bool IntArray::equal(IntArray &a) { 
    if(a._size != _size) return false;

    for(int i=0; i<_size; i++) {
        if(a.array[i] != this->array[i]) {
                return false;
        }
    }
    return true;
}

void IntArray::assign(IntArray &a){
    if(a._size > _size) { //若a的大小超过当前大小,直接退出
        exit(0);        
    }

    int i=0;
    for(; i<a._size; i++){//注意: a.size <= this->size;
        array[i] = a.array[i];
    }
    //注:题目并未说明this->size超出a的部分数据如何处理,一般应置0
    for(;i<this->_size;i++){
        array[i]=0;
    }
    //也可理解为令a._size = this->_size; 
    //这需要 deleted[] array; array=new int[a._size];然后再拷贝数组; 
    //如果是拷贝构造函数,则应按此种理解;
}

void IntArray::enlarge(int delta){
    if(delta<=0) return;

    int newSize = _size + delta;
    int *newArray = new int[newSize];

    int i=0;
    for(; i<_size; i++){
        newArray[i] = array[i];
    }
    for(; i<newSize; i++){
        newArray[i] = 0;
    }
    _size = newSize; 
    delete []array;    
    array = newArray;
}

void IntArray::sort(){    //这里采用插入排序
    int temp;
    for(int i=1; i<_size; i++) {
        temp=array[i];
        int j=i-1;
        for(; j>=0 && temp<array[j]; j--) {
            array[j+1] = array[j];
        }
        array[j+1] = temp;
    }    
}

void IntArray::display(){
    if(_size>0) {
        int len=_size-1;
        for(int i=0; i<len; i++) {
            std::cout << array[i] << ", ";
        }
        std::cout<<array[len];
    }
    std::cout<<std::endl;
}

//2010年
//要求实现一个整数数组类，定义放在IntArray.h中，实现放intArray.cpp中。
//实现下列程序功能
//class IntArray{
//public:
//    IntArray(int size);          //初始化数组，长度为 size,且赋初值为 0 
//    ~IntArray();
//    int size() const;            //返回数组长度
//    int &Item(int i);            //返回 i下标的引用
//    bool equal(IntArray &a);     //长度和数据相等返回 True，否则 False
//    void assign(IntArray &a);    //将 a中的数组赋值到 this中，若a长度大于this长度，
//                                 //则终止程序！ 
//    void enlarge(int delta);     //将 this中的数组延长 Delta个单位，
//                                 //并将这 Delta个单位的数组赋初值为 0 
//    void sort();                 //this中的数组排序，从小到大 
//    void display();              //打印数组
//};

//test
/*
using namespace std;

void IntArray_copy(IntArray& array, int a[], int len){
    if(len<=array.size()){
        for(int i=0;i<len;i++){
            array.Item(i)=a[i];
        }
    }
}

void IntArray_test(){
    cout<<"构造函数 & display()\n";
    IntArray a(10), b(-10), aa(10);
    a.display();
    b.display();
    aa.display();

    cout<<"\na Item()\n";
    int t[] = {5, 4, 7, 8, 3, 1, 5};
    IntArray_copy(a,t, 7);
    a.display();

    cout<<"\na size(): "<< a.size()<<endl;

    cout<< "\na sort()\n";
    a.sort();
    a.display();

    cout<< "\na enlarge(-1) & enlarge(5)\n";
    a.enlarge(-1);
    a.display();
    a.enlarge(5);
    a.display();

    cout<< "\nb.equal(a)? " << b.equal(a)<<
           ", aa.equal(a)? "<<aa.equal(a)<<endl;

    cout<< "\nassign()\n";
    IntArray_copy(aa,t,7);
    aa.enlarge(5);
    aa.assign(a);
    aa.display();
    cout<< "\naa.equal(a)?  "<<aa.equal(a)<<endl;
}

int main(){
    IntArray_test();
    return 0;
}
/**/
