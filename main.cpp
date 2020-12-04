#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <iostream>
#include <cmath>

using namespace std;
char *action[13][4] = {   /*ACTION表*/
    "S4#", "S5#", NULL, NULL,
    NULL, NULL, NULL, "acc",
    "S4#", "S5#", "S7#", NULL,
    "r2#", "r2#", "r2#", NULL,
    "r3#", "r3#", "r3#", NULL,
    "r4#", "r4#", "r4#", NULL,
    "r5#", "r5#", "r5#", NULL,
    "S10#", "S11#", NULL, NULL,
    "S10#", "S11#", NULL, "r6",
    "r2#", "r2#", NULL, "r2#",
    "r3#", "r3#", NULL, "r3#",
    "r4#", "r4#", NULL, "r4#",
    "r5#", "r5#", NULL, "r5#",
};

int goto1[13][3] = {    /*GOTO表*/
    3, 2, 1,
    0, 0, 0,
    6, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    9, 8, 0,
    12, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
};

bool flag;
struct BinaryNum {
  double Value;
  int Length;
} LastNum, TempNum;
stack<BinaryNum> stack_v;
double Ans;

void DeStatute(int status) {
  switch (status) {
    case 1:
      Ans = stack_v.top().Value;
      stack_v.pop();
      break;
    case 2:
      TempNum = stack_v.top();
      stack_v.pop();
      TempNum.Length = 1;
      stack_v.push(TempNum);
      break;
    case 3:
      TempNum.Value = 0;
      TempNum.Length = 0;
      stack_v.push(TempNum);
      break;
    case 4:
      TempNum.Value = 1;
      TempNum.Length = 0;
      stack_v.push(TempNum);
      break;
    case 5:
      TempNum = stack_v.top();
      stack_v.pop();
      LastNum = stack_v.top();
      stack_v.pop();
      LastNum.Value = LastNum.Value * 2 + TempNum.Value;
      LastNum.Length++;
      stack_v.push(LastNum);
      break;
    case 6:
      TempNum = stack_v.top();
      stack_v.pop();
      LastNum = stack_v.top();
      stack_v.pop();
      LastNum.Value = LastNum.Value + TempNum.Value * pow(2, -TempNum.Length);
      LastNum.Length = -1;
      stack_v.push(LastNum);
      break;
  }
}


char input[50];
int len;

void LR() {
  char vt[4] = {'0', '1', '.', '#'};
  char vn[3] = {'B', 'S', 'N'};
  char *grammar[7] = {"", "E-N#", "S-B#", "B-0#", "B-1#", "S-SB#", "N-S.S#"};

  int stack_a[50];        /*状态栈*/
  char stack_b[50];       /*符号栈*/
  int top_a, top_b;
  int step;
  int ip;
  int i;

  int row, column;

  int pNo;                /*产生式编号*/
  int bodyLen, state;
  char sym, entry[10], production[10];

  stack_a[0] = 0;
  stack_b[0] = '#';
  top_a = 0;
  top_b = 0;
  ip = 0;
  step = 0;

  printf("步骤\t状态栈\t\t符号栈\t\t输入串\t\tACTION\tGOTO\n");
  while (1) {
    row = stack_a[top_a];
    sym = input[ip];
    printf("%d\t", step++);

    i = 0;
    while (i <= top_a)            /*输出状态栈*/
      printf("%d", stack_a[i++]);
    printf("\t\t");

    i = 0;
    while (i <= top_b)            /*输出符号栈*/
      printf("%c", stack_b[i++]);
    printf("\t\t");

    i = ip;
    while (i < len)               /*输出输入串*/
      printf("%c", input[i++]);
    printf("\t\t");

    column = 0;
    while (column <= 3) {
      if (sym == vt[column])
        break;
      column++;
    }
    if (column == 4) {
      printf("error...illegal input!\n");
      return;
    }

    if (action[row][column] == NULL) {      /*查表*/
      printf("error...NULL\n");
      return;
    } else if (action[row][column] == "acc") {
      printf("acc!\n");
      flag = true;
      return;
    } else {
      strcpy(entry, action[row][column]);
      printf("%s", action[row][column]);
    }

    if (entry[0] == 'S') {              /*处理移进*/
      if (entry[2] == '#')
        state = entry[1] - '0';
      else state = (entry[1] - '0') * 10 + entry[2] - '0';
      stack_a[++top_a] = state;
      stack_b[++top_b] = sym;
      ip++;
      printf("\n");
    }

    if (entry[0] == 'r') {                       /*处理归约*/
      pNo = entry[1] - '0';
      strcpy(production, grammar[pNo]);
      DeStatute(pNo);
      column = 0;
      while (production[0] != vn[column])
        column++;
      bodyLen = strlen(grammar[pNo]) - 3;

      top_a = top_a - bodyLen;
      top_b = top_b - bodyLen;

      row = stack_a[top_a];
      state = goto1[row][column];

      stack_a[++top_a] = state;
      stack_b[++top_b] = production[0];
      printf("\t");
      printf("%d\n", state);
    }
  }
}

int main() {
  char c;
  FILE *ques = NULL;
  ques = fopen("C:\\WorkSpace\\CompileTest\\ques.txt", "r");
  while (1) {
    printf("\ninput length<50,ending with'#'; '^#' to return!\n");
    len = 0;
    flag = false;
    fscanf(ques, "%s", input);
//    do {
//      scanf("%c", &c);
//      input[len++] = c;
//    } while (c != '#');
//    getchar();
    if (input == NULL)break;
    if (input[0] == '^' && input[1] == '#') {
      fclose(ques);
      return 0;
    }
    LR();
    if (flag) {
      Ans = stack_v.top().Value;
      stack_v.pop();
      cout << "\n\nGet the Value:  " << Ans << endl;
      FILE *ans = NULL;
      ans = fopen("C:\\WorkSpace\\CompileTest\\ans.txt", "a");
      string myans = to_string(Ans);
      fprintf(ans, myans.data());
      fprintf(ans, "\n");
      fclose(ans);
    } else
      cout << "ERROR!" << endl;
  }
}
