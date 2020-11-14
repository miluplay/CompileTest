#include <iostream>
#include <stack>
#include <cmath>

using namespace std;
struct Node_Bin {
//  S: Length > 0
//  B: Length = 0
//  V: Length = -1
  double Value;
  int Length;
} MyBin, LastBin;
stack <Node_Bin> MyStack;
string str;

Node_Bin GetValue(bool sp, Node_Bin A, Node_Bin B) {
  Node_Bin ans;
  if (sp) {//SB to S
    ans.Value = A.Value * 2 + B.Value;
    ans.Length = A.Length + 1;
  } else { //S.S to N
    ans.Value = A.Value + pow(B.Value, -B.Length);
    ans.Length = -1;
  }
  return ans;
}

int GetBinNum() {
  int position = 0, status = 0;
  while (true) {
    if (status == 0) {
      if (MyStack.empty()) {
        MyBin.Length = 0;
        MyBin.Value = str[position] - '0';
        MyStack.push(MyBin);
      } else {
        MyBin = MyStack.top();
        if (MyBin.Length == -1) {
          position++;
          status = 1;
        } else if (MyBin.Length == 0) {
          MyStack.pop();
          LastBin = MyStack.top(), MyStack.pop();
          LastBin = GetValue(true, LastBin, MyBin);
          MyStack.push(LastBin);
        } else {

        }
      }
    }
  }
}

int main() {
  cin >> str;
  str += '#';

  return 0;
}