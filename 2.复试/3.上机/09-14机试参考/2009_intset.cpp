#include "2009_intset.h"
#include <iostream>

IntSet::IntSet(){
    value=0;
    next=NULL;
}

IntSet::~IntSet(){
    delete next; //递归释放
}

IntSet::IntSet(const IntSet& s){//拷贝构造函数
    clone(s);
}

IntSet& IntSet::operator=(const IntSet& s){
    if(&s==this) return *this;
	
    delete next;
    clone(s); 
    return *this;
}

void IntSet::clone(const IntSet& s){
    this->value=s.value;
    this->next=NULL;//!注意:当拷贝构造函数调用clone时,this尚未初始化,
    // 若此处不对next置NULL,则this->next悬空
    // 由拷贝构造函数建立的对象在使用next时会无法判断链表尾,导致访存错误
    IntSet *ps=s.next, *p=this;
    while(NULL!=ps){
        IntSet *temp=new IntSet;
        temp->value=ps->value;        temp->next=NULL;
        p->next=temp;                 p=p->next;

        ps=ps->next;
    }
}

//插入元素
void IntSet::insert(const int value)  {
    IntSet *p=this;
    while(NULL!=p->next){
        if (value>p->next->value)     { //链表从小到大有序,查找插入位置
            p=p->next;
        } else {
            if (value==p->next->value){ //集合中不允许有重复的元素
                return;
            } 
        }
    }
	
    //在p之后插入新元素
    IntSet *temp=new IntSet();
    temp->value=value;  
    temp->next=p->next;
    p->next=temp;
    this->value++;    //注：只维护头结点的value(即元素个数)；
}

//比较与s是否相等
bool IntSet::IsEqual(IntSet& s){
    if(s.value!=this->value) return false;

    IntSet *s1=this,*s2=&s;
    while (NULL!=s1->next && 
           s1->next->value==s2->next->value){//前面已经确认2个集合的元素个数相同
           s1=s1->next;
           s2=s2->next;
    }
    return NULL==s1->next;					 //循环若到达最后一个元素,说明均相等
}

//求 s1与 s2的并
IntSet IntSet::union2(IntSet& s1, IntSet& s2){
    IntSet *ps1=&s1, *ps2=&s2;
    IntSet s;
    for(;NULL!=ps1->next;ps1=ps1->next){
        s.insert(ps1->next->value);
    }
    for(;NULL!=ps2->next;ps2=ps2->next){
        s.insert(ps2->next->value);
    }
    return s;  //此处会自动调用拷贝构造函数
}

//求 s1与 s2的交
IntSet IntSet::incorporate2(IntSet& s1,IntSet& s2){
    IntSet *ps1=&s1, *ps2=&s2;
    IntSet s;
    while(NULL!=ps1->next && NULL!=ps2->next){
        if(ps1->next->value == ps2->next->value){    
            s.insert(ps1->next->value);
            ps1=ps1->next;
            ps2=ps2->next;
        } else { //在两个有序链表中交错后移,每次都是移动较小那个
            if(ps1->next->value < ps2->next->value){
                ps1=ps1->next;
            } else { // >
                ps2=ps2->next;
            }
        }
    }
    return s;  //同样,此处也会自动调用拷贝构造函数
}

//输出元素
void IntSet::print(){
    IntSet *temp=this;
    while(NULL!=temp->next){
        std::cout<<temp->next->value<<", ";
        temp=temp->next;
    }
    std::cout<<" 元素个数:"<<this->value<<std::endl;
}

//2009年
//要求写一个整数集合的类，分别放在 intset.h和 intset.cpp中，实现下列程序功能。
//test
//注:请测试s1,s2均为空、有1个为空、有交集、无交集、相等的情况

/*
using namespace std;

int main(){
    IntSet s1, s2, s3, s4;
    int x;

    for(cin >> x; x != 0; cin >> x)    //在 s1中插入元素
        s1.insert(x); 
    for(cin >> x; x != 0; cin >> x)    //在 s2中插入元素
        s2.insert(x); 
    if(s1.IsEqual(s2))                 //比较 s1与 s2是否相等
        cout << "s1 is equal s2 \n";
    s3 = s3.union2(s1, s2);            //求 s1与 s2的交(注:不应该返回一个对象!
                                       //否则需要重载=,并实现拷贝构造函数,下同)
    s4 = s4.incorporate2(s1, s2);      //求 s1与 s2的并(注:函数名应为intersection)
    cout << "\ns1:";    s1.print();    //输出 s1中的元素
    cout << "\ns2:";    s2.print();
    cout << "\ns3:";    s3.print();
    cout << "\ns4:";    s4.print();

    return 0;
}
/**/