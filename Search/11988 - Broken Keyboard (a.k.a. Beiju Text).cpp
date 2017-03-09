#include<cstdio>
#include<cstring>
const int maxn = 100000 + 5;
int last, cur, next[maxn]; // 光标位于cur号字符之后面
char s[maxn];
int main() {
  while(scanf("%s", s+1) == 1) {
    int n = strlen(s+1); // 输入保存在s[1], s[2]...中
    last = cur = 0;
    next[0] = 0;

    for(int i = 1; i <= n; i++) {
      char ch = s[i];
      if(ch == '[') cur = 0;
      else if(ch == ']') cur = last;
      else {
        next[i] = next[cur];  //表示新元素i的下一个元素指向当前head指向的元素，
        next[cur] = i;        //更新head的指向，指向新的第一个元素i。
        if(cur == last) last = i; // 更新“最后一个字符”编号
        cur = i; // 移动光标        //维护head
      }
    }
    for(int i = next[0]; i != 0; i = next[i])
      printf("%c", s[i]);
    printf("\n");
  }
  return 0;
}
/*
最初我们需要一个头结点，不妨将它设为0，即Next[0]=0。头结点只是起到一个标记的作用，不表示真实的位置。
链表中的头结点总是指向链表的第一个元素。然后开始插入元素。链表中插入元素就两句代码：
Next[i]=next[head]   表示新元素i的下一个元素指向当前head指向的元素，
next[head]=i。       更新head的指向，指向新的第一个元素i。
head=i               维护head，再插入新元素
当所有元素插入完毕后，只需要从头结点开始，顺着Next数组即可按顺序输出整个链表。
注意，这样的插入实际上是在尾部插入，链表的尾部在不断地变长。
这道题中用cur来当做头结点，通过移动头结点的位置即可实现在链表的不同位置插入新元素。
根据题意，当遇到‘['时，头结点变为0，遇到‘]'时，头结点变为last即可。
*/
