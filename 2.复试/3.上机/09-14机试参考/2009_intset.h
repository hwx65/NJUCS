#pragma once

class IntSet {
//由于元素数不定,故使用带头结点的单链表实现. 实现时没有单独定义结点结构.
//因为只需提供插入元素的操作,插入中保持链表有序（从小到大）,可以简化求交;
//注意：集合中不含有重复的元素！
//另外,这里没有单独定义结点结构(struct Node), IntSet本身就是结点
public:
    IntSet();
    IntSet(const IntSet& s);
    virtual ~IntSet();
    
    //插入元素
    void insert(const int value);

    //比较与 s是否相等
    bool IsEqual(IntSet& s);

    //求 s1与 s2的并
    IntSet union2(IntSet& s1, IntSet& s2);

    //求 s1与 s2的交
    IntSet incorporate2(IntSet& s1,IntSet& s2);

    //重载=,实现深拷贝
    IntSet& operator=(const IntSet& s);

    //输出元素
    void print();

private:
    int value;//注：头结点的value表示元素个数；
    void clone(const IntSet& s);
    IntSet* next;
};