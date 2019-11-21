//2011年
//编写函数
//int find_str_replace(char str[],
//                     const char find_str[],
//                     const char replace_str[]);
//将 str 中的所有子串 find_str 替换为 replace_str,返回替换的个数。
//不允许用STL。

int _str_len(const char str[]){
    const char *p = str;
    while('\0' != *p)	{
        p++;
    }
    return p-str;
}

int _find_str(char str[],const char find_str[]){
    int   i = 0;
    char *s = str;
    bool match=true;

    for (; s !='\0'; s++) {
        match=true;
        for (i = 0; find_str[i] !='\0'; i++) {
            if (s[i]=='\0') { //str先到达结尾,可以肯定没有找到
                return -1;
            }
            if (find_str[i]!=s[i]) {
                match=false;
                break;
            }
        }
        if (match) {
            return s-str;
        }
    }
    return -1;
}

int find_str_replace(char str[],const char find_str[],const char replace_str[]){
    int str_len = _str_len(str), 
        f_len   = _str_len(find_str), 
        r_len   = _str_len(replace_str);

    if (f_len==0 || str_len <f_len) {//注:r_len==0时相当于从str中删除find_str
        return 0;
    }

    int *indx=new int[str_len/f_len];//indx保存各个查找结果的索引
    int cnt=0, i=_find_str(str,find_str);
    indx[0]=i; 

    while(i!=-1){                    //计算indx[]
        i=_find_str(str+indx[cnt]+f_len,find_str);
        cnt++;
        if (i==-1){
            break;
        }
        indx[cnt]=indx[cnt-1]+f_len+i; 
    }

    if (cnt>0) {
        char *s=new char[str_len - cnt*(f_len - r_len)+2],
            *sp=s;
        int c=0;

        for (int j = 0; j < str_len; j++) {
            if (j>=indx[c] && c<cnt) { //将replace_str拷贝到s
                for (int k = 0; k < r_len; k++) {
                    *sp=replace_str[k];
                    sp++;
                }
                c++;                   //继续下一个替换
                j+=f_len;
            }
            *sp=str[j];                //将str的其它部分拷贝到s
            sp++;
        }
        *sp='\0';

        //将s拷贝回str;
        //由于题目的限制,当f_len < r_len时会截断,以防止str溢出
        int m = 0;
        for (; m < str_len; m++) {
            if (s[m]=='\0') {
                break;
            }
            str[m]=s[m];
        }
        str[m]='\0';

        delete[] s;
    }

    delete[] indx;
    return cnt;
}

/*
#include <iostream>
using namespace std;

int main(){
    char str[] = ""
        "This is is the original string."
        ;
    char find_str[] = ""
        //" "
        "is"
        ;
    char replace_str[] = ""
        //"="
        "=="
        ;
    cout << find_str_replace(str, find_str, replace_str) <<endl;
    cout << str << endl;

    return 0;
}
/**/