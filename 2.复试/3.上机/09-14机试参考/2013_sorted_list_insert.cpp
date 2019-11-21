#include <iostream> //#define NULL    0
#pragma once

//2013年
//编写一个 C++函数 sorted_list_insert 
//该函数能够在一个已按结点值由小到大排序的双向链表（h为第一个结点的指针）
//中插入一个结点值为 i的结点，
//要求插入结点后，链表结点仍然是由小到大排序的。
//函数返回插入结点后链表的第一个元素的指针。

//结点类型 Node 
struct Node { 
    int value;  //结点的值 
    Node *prev; //链表中前一个结点的指针；对第一个结点，  它为 0 
    Node *next; //链表中下一个结点的指针；对最后一个结点，它为 0 
};

Node *sorted_list_insert(Node *h, int i){
    if (NULL==h) return NULL;

    Node *n=h;
    Node *temp=new Node;
    temp->value=i;    temp->prev=0;    temp->next=0;

    if (i<=n->value){//i比首结点的值还小,需将其插到链表首
        temp->next=n;    n->prev=temp;
        h=temp;
        return h;
    }
    //else i>n->value; 对剩余的结点，确定插入位置，应插入n的后面
    //此时插入结点不会影响h
    while (NULL!=n->next&&i>n->next->value){
        n=n->next;
    }

    temp->prev=n;    temp->next=n->next;
    n->next=temp;
    if (NULL!=temp->next){ //不是在链表尾
        temp->next->prev=temp;
    } 

    return h;
}

//test
/*
using namespace std;

void print(Node *n){
    if(NULL==n) {
        cout<<endl;
        return;
    }

    for (; n->next!=NULL; n=n->next)    {
        cout<<n->value<<", ";
    }
    cout<<n->value<<endl;
}

Node* initList(int a[],int len){
    Node *h=new Node;
    h->value=a[0];
    h->prev=NULL;
    h->next=NULL;//初始化指针是必要的，否则建立链表时会出错

    for (int i = 1; i < len; i++)    {
        h=sorted_list_insert(h,a[i]);//这里也算测试了
    }
    return h;
}

void sorted_list_insert_test(){
    int a[]={-1, 0,2};

    Node* h=initList(a,3);
    cout<<"初始链表\t";
    print(h);

    h=sorted_list_insert(h,-1);//首部
    cout<<"插入-1\t\t";
    print(h);

    h=sorted_list_insert(h,1);//中部
    cout<<"插入1\t\t";
    print(h);

    h=sorted_list_insert(h,2);//尾部
    cout<<"插入2\t\t";
    print(h);
}

int main(){
    sorted_list_insert_test();
    return 0;
}
/**/