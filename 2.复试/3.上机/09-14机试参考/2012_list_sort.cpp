//2012年
//函数定义为 Node *list_sort(Node *h); h指向单链表的头结点，
//要求把 h指向的单链表内结点值按升序排序，然后返回排序后的单链表头结点指针。
//结果保存在list_sort.cpp里，测试代码不用提交。
#include <iostream>

struct Node{
    int value;
    Node *next;
};

Node *list_sort(Node *h){
    //使用插入排序:将链表h的首结点依次摘下,插入已有序的链表s中;
    if(NULL==h) return NULL;

    Node *s=h,                   //s为已排序的链表,初始化h的首结点
        *hp=NULL, *sp=NULL;      //用于临时保存结点 
    h=h->next;                   //令h为剩余结点
    s->next=NULL;                //!
    while(NULL!=h){
        if(h->value <= s->value){//h应插在s前面
            hp=h;    h=h->next;  //摘下h          
            hp->next=s;    s=hp; //插到s之前,并更新s
        } else {
            sp=s;
            while(NULL!=sp->next && 
                h->value > sp->next->value){//寻找插入位置
                    sp=sp->next;
            }
            hp=h;    h=h->next;  //摘下h
            hp->next=sp->next;   //此处即便sp->next==NULL也可以
            sp->next=hp;         //插入结点
        }
    }
    return s;
}


//test
/*
using namespace std;

void print(Node *h){
    if (h==NULL) {
        cout<<endl;
        return;
    }
    for (; h->next!=0; h=h->next)    {
        cout<<h->value<<", ";
    }
    cout<<h->value<<endl;
}

Node* initList(int a[], int len){
    Node *h=new Node, *p=h;
    h->value=a[0];    h->next=NULL;
    for(int i=1;i<len;i++){
        Node *t=new Node;
        t->value=a[i];    t->next=NULL;
        p->next=t;        p=p->next;
    }
    return h;
}

void list_sort_test(){
    int a[]={1,0,1,2,3,2,1};
    Node *h=initList(a, 7 );
    cout<<"h \t:";
    print(h);
    cout<<"排序后\t:";
    print(list_sort(h));
}

int main() {
    list_sort_test();
    return 0;
}
/**/