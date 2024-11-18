#include <assert.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>

using namespace std;

// 定义结构体，存储魔方每一个状态以及在对应状态时刻之前的操作
struct mofang {
  char qian[4][4];
  char hou[4][4];
  char zuo[4][4];
  char you[4][4];
  char shang[4][4];
  char xia[4][4];

  queue<int> steps;

} init;

// 用于BFS算法，使用队列实现
queue<mofang> q;

// 是否复原
bool flag = 0;

// 读取输入
void input_cube() {
  cout << "input cube: " << endl;

  for (int i = 0; i <= 2; i++)  //输入后面
    for (int j = 0; j <= 2; j++) cin >> init.hou[i][j];
  for (int i = 0; i <= 2; i++)  //输入上面
    for (int j = 0; j <= 2; j++) cin >> init.shang[i][j];
  for (int i = 0; i <= 2; i++)  //输入前面
    for (int j = 0; j <= 2; j++) cin >> init.qian[i][j];
  for (int i = 0; i <= 2; i++)  //输入下面
    for (int j = 0; j <= 2; j++) cin >> init.xia[i][j];
  for (int i = 0; i <= 2; i++)  //输入左面
    for (int j = 0; j <= 2; j++) cin >> init.zuo[i][j];
  for (int i = 0; i <= 2; i++)  //输入右面
    for (int j = 0; j <= 2; j++) cin >> init.you[i][j];
}

// 检测是否复原
// 上午讲座师兄说不能写成这个样子
bool is_back(mofang t) {
  if (t.qian[0][0] == t.qian[0][1] &&
      t.qian[0][1] == t.qian[0][2] &&
      t.qian[0][2] == t.qian[1][0] &&
      t.qian[1][0] == t.qian[1][1] &&
      t.qian[1][1] == t.qian[1][2] &&
      t.qian[1][2] == t.qian[2][0] &&
      t.qian[2][0] == t.qian[2][1] &&
      t.qian[2][1] == t.qian[2][2] && 
      t.hou[0][0] == t.hou[0][1] &&
      t.hou[0][1] == t.hou[0][2] && t.hou[0][2] == t.hou[1][0] &&
      t.hou[1][0] == t.hou[1][1] && t.hou[1][1] == t.hou[1][2] &&
      t.hou[1][2] == t.hou[2][0] && t.hou[2][0] == t.hou[2][1] &&
      t.hou[2][1] == t.hou[2][2] && t.zuo[0][0] == t.zuo[0][1] &&
      t.zuo[0][1] == t.zuo[0][2] && t.zuo[0][2] == t.zuo[1][0] &&
      t.zuo[1][0] == t.zuo[1][1] && t.zuo[1][1] == t.zuo[1][2] &&
      t.zuo[1][2] == t.zuo[2][0] && t.zuo[2][0] == t.zuo[2][1] &&
      t.zuo[2][1] == t.zuo[2][2] && t.you[0][0] == t.you[0][1] &&
      t.you[0][1] == t.you[0][2] && t.you[0][2] == t.you[1][0] &&
      t.you[1][0] == t.you[1][1] && t.you[1][1] == t.you[1][2] &&
      t.you[1][2] == t.you[2][0] && t.you[2][0] == t.you[2][1] &&
      t.you[2][1] == t.you[2][2] &&
      t.shang[0][0] == t.shang[0][1] &&
      t.shang[0][1] == t.shang[0][2] &&
      t.shang[0][2] == t.shang[1][0] &&
      t.shang[1][0] == t.shang[1][1] &&
      t.shang[1][1] == t.shang[1][2] &&
      t.shang[1][2] == t.shang[2][0] &&
      t.shang[2][0] == t.shang[2][1] &&
      t.shang[2][1] == t.shang[2][2] &&
      t.xia[0][0] == t.xia[0][1] && t.xia[0][1] == t.xia[0][2] &&
      t.xia[0][2] == t.xia[1][0] && t.xia[1][0] == t.xia[1][1] &&
      t.xia[1][1] == t.xia[1][2] && t.xia[1][2] == t.xia[2][0] &&
      t.xia[2][0] == t.xia[2][1] && t.xia[2][1] == t.xia[2][2])
    return true;
  else
    return false;
}

//操作1：0正向
void act_1(mofang t) {
  mofang tmp;
  tmp = t;
  // hou_change
  tmp.hou[0][0] = t.shang[0][0];
  tmp.hou[1][0] = t.shang[1][0];
  tmp.hou[2][0] = t.shang[2][0];
  // shang_change
  tmp.shang[0][0] = t.qian[0][0];
  tmp.shang[1][0] = t.qian[1][0];
  tmp.shang[2][0] = t.qian[2][0];
  // qian_change
  tmp.qian[0][0] = t.xia[0][0];
  tmp.qian[1][0] = t.xia[1][0];
  tmp.qian[2][0] = t.xia[2][0];
  // xia_change
  tmp.xia[0][0] = t.hou[0][0];
  tmp.xia[1][0] = t.hou[1][0];
  tmp.xia[2][0] = t.hou[2][0];
  // zuomian_change_______逆时针
  tmp.zuo[0][0] = t.zuo[0][2];
  tmp.zuo[2][0] = t.zuo[0][0];
  tmp.zuo[2][2] = t.zuo[2][0];
  tmp.zuo[0][2] = t.zuo[2][2];

  tmp.zuo[0][1] = t.zuo[1][2];
  tmp.zuo[1][0] = t.zuo[0][1];
  tmp.zuo[2][1] = t.zuo[1][0];
  tmp.zuo[1][2] = t.zuo[2][1];

  tmp.steps.push(1);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}

//操作2：0反向
void act_2(mofang t) {
  mofang tmp;
  tmp = t;  // tmp 新状态
  // hou_change
  tmp.hou[0][0] = t.xia[0][0];
  tmp.hou[1][0] = t.xia[1][0];
  tmp.hou[2][0] = t.xia[2][0];
  // shang_change
  tmp.shang[0][0] = t.hou[0][0];
  tmp.shang[1][0] = t.hou[1][0];
  tmp.shang[2][0] = t.hou[2][0];
  // qian_change
  tmp.qian[0][0] = t.shang[0][0];
  tmp.qian[1][0] = t.shang[1][0];
  tmp.qian[2][0] = t.shang[2][0];
  // xia_change
  tmp.xia[0][0] = t.qian[0][0];
  tmp.xia[1][0] = t.qian[1][0];
  tmp.xia[2][0] = t.qian[2][0];
  // zuomian_change_____顺时针
  tmp.zuo[0][0] = t.zuo[2][0];
  tmp.zuo[2][0] = t.zuo[2][2];
  tmp.zuo[2][2] = t.zuo[0][2];
  tmp.zuo[0][2] = t.zuo[0][0];

  tmp.zuo[0][1] = t.zuo[1][0];
  tmp.zuo[1][0] = t.zuo[2][1];
  tmp.zuo[2][1] = t.zuo[1][2];
  tmp.zuo[1][2] = t.zuo[0][1];

  

  tmp.steps.push(2);
  if (is_back(tmp)) {  // 结束，输出到当前状态所需要的所有操作
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作3：1正向
void act_3(mofang t) {
  mofang tmp;
  tmp = t;
  // hou_change
  tmp.hou[0][1] = t.shang[0][1];
  tmp.hou[1][1] = t.shang[1][1];
  tmp.hou[2][1] = t.shang[2][1];
  // shang_change
  tmp.shang[0][1] = t.qian[0][1];
  tmp.shang[1][1] = t.qian[1][1];
  tmp.shang[2][1] = t.qian[2][1];
  // qian_change
  tmp.qian[0][1] = t.xia[0][1];
  tmp.qian[1][1] = t.xia[1][1];
  tmp.qian[2][1] = t.xia[2][1];
  // xia_change
  tmp.xia[0][1] = t.hou[0][1];
  tmp.xia[1][1] = t.hou[1][1];
  tmp.xia[2][1] = t.hou[2][1];

  tmp.steps.push(3);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}

//操作4：1反向
void act_4(mofang t) {
  mofang tmp;
  tmp = t;
  // hou_change
  tmp.hou[0][1] = t.xia[0][1];
  tmp.hou[1][1] = t.xia[1][1];
  tmp.hou[2][1] = t.xia[2][1];
  // shang_change
  tmp.shang[0][1] = t.hou[0][1];
  tmp.shang[1][1] = t.hou[1][1];
  tmp.shang[2][1] = t.hou[2][1];
  // qian_change
  tmp.qian[0][1] = t.shang[0][1];
  tmp.qian[1][1] = t.shang[1][1];
  tmp.qian[2][1] = t.shang[2][1];
  // xia_change
  tmp.xia[0][1] = t.qian[0][1];
  tmp.xia[1][1] = t.qian[1][1];
  tmp.xia[2][1] = t.qian[2][1];

  tmp.steps.push(4);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}

//操作5：2正向
void act_5(mofang t) {
  mofang tmp;
  tmp = t;
  // hou_change
  tmp.hou[0][2] = t.shang[0][2];
  tmp.hou[1][2] = t.shang[1][2];
  tmp.hou[2][2] = t.shang[2][2];
  // shang_change
  tmp.shang[0][2] = t.qian[0][2];
  tmp.shang[1][2] = t.qian[1][2];
  tmp.shang[2][2] = t.qian[2][2];
  // qian_change
  tmp.qian[0][2] = t.xia[0][2];
  tmp.qian[1][2] = t.xia[1][2];
  tmp.qian[2][2] = t.xia[2][2];
  // xia_change
  tmp.xia[0][2] = t.hou[0][2];
  tmp.xia[1][2] = t.hou[1][2];
  tmp.xia[2][2] = t.hou[2][2];
  // youmian_change
  tmp.you[0][0] = t.you[2][0];
  tmp.you[2][0] = t.you[2][2];
  tmp.you[2][2] = t.you[0][2];
  tmp.you[0][2] = t.you[0][0];

  tmp.you[0][1] = t.you[1][0];
  tmp.you[1][0] = t.you[2][1];
  tmp.you[2][1] = t.you[1][2];
  tmp.you[1][2] = t.you[0][1];

  tmp.steps.push(5);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作6：2反向
void act_6(mofang t) {
  mofang tmp;
  tmp = t;
  // hou_change
  tmp.hou[0][2] = t.xia[0][2];
  tmp.hou[1][2] = t.xia[1][2];
  tmp.hou[2][2] = t.xia[2][2];
  // shang_change
  tmp.shang[0][2] = t.hou[0][2];
  tmp.shang[1][2] = t.hou[1][2];
  tmp.shang[2][2] = t.hou[2][2];
  // qian_change
  tmp.qian[0][2] = t.shang[0][2];
  tmp.qian[1][2] = t.shang[1][2];
  tmp.qian[2][2] = t.shang[2][2];
  // xia_change
  tmp.xia[0][2] = t.qian[0][2];
  tmp.xia[1][2] = t.qian[1][2];
  tmp.xia[2][2] = t.qian[2][2];
  //=youmian_change
  tmp.you[0][0] = t.you[2][0];
  tmp.you[2][0] = t.you[2][2];
  tmp.you[2][2] = t.you[0][2];
  tmp.you[0][2] = t.you[0][0];

  tmp.you[0][1] = t.you[1][0];
  tmp.you[1][0] = t.you[2][1];
  tmp.you[2][1] = t.you[1][2];
  tmp.you[1][2] = t.you[0][1];

  tmp.steps.push(6);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作7：3正向
void act_7(mofang t) {
  mofang tmp;
  tmp = t;
  // hou_change
  tmp.hou[0][0] = t.you[0][2];
  tmp.hou[0][1] = t.you[1][2];
  tmp.hou[0][2] = t.you[2][2];
  // you_change
  tmp.you[0][2] = t.qian[2][2];
  tmp.you[1][2] = t.qian[2][1];
  tmp.you[2][2] = t.qian[2][0];
  // qian_change
  tmp.qian[2][0] = t.zuo[0][0];
  tmp.qian[2][1] = t.zuo[1][0];
  tmp.qian[2][2] = t.zuo[2][0];
  // zuo_change
  tmp.zuo[0][0] = t.qian[2][0];
  tmp.zuo[1][0] = t.qian[2][1];
  tmp.zuo[2][0] = t.qian[2][2];
  // xiamian_change
  tmp.xia[0][0] = t.xia[2][0];
  tmp.xia[2][0] = t.xia[2][2];
  tmp.xia[2][2] = t.xia[0][2];
  tmp.xia[0][2] = t.xia[0][0];

  tmp.xia[0][1] = t.xia[1][0];
  tmp.xia[1][0] = t.xia[2][1];
  tmp.xia[2][1] = t.xia[1][2];
  tmp.xia[1][2] = t.xia[0][1];

  tmp.steps.push(7);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作8：3反向
void act_8(mofang t) {
  mofang tmp;
  tmp = t;
  // hou_change
  tmp.hou[0][0] = t.zuo[2][0];
  tmp.hou[0][1] = t.zuo[1][0];
  tmp.hou[0][2] = t.zuo[0][0];
  // zuo_change
  tmp.zuo[0][0] = t.qian[2][0];
  tmp.zuo[1][0] = t.qian[2][1];
  tmp.zuo[2][0] = t.qian[2][2];
  // qian_change
  tmp.qian[2][0] = t.you[2][2];
  tmp.qian[2][1] = t.you[1][2];
  tmp.qian[2][2] = t.you[0][2];
  // you_change
  tmp.you[0][2] = t.hou[0][0];
  tmp.you[1][2] = t.hou[0][1];
  tmp.you[2][2] = t.hou[0][2];
  // xiamian_change
  tmp.xia[0][0] = t.xia[0][2];
  tmp.xia[2][0] = t.xia[0][0];
  tmp.xia[2][2] = t.xia[2][0];
  tmp.xia[0][2] = t.xia[2][2];

  tmp.xia[0][1] = t.xia[1][2];
  tmp.xia[1][0] = t.xia[0][1];
  tmp.xia[2][1] = t.xia[1][0];
  tmp.xia[1][2] = t.xia[2][1];

  tmp.steps.push(8);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}

//操作9：4正向
void act_9(mofang t) {
  mofang tmp;
  tmp = t;
  // hou_change
  tmp.hou[1][0] = t.zuo[2][1];
  tmp.hou[1][1] = t.zuo[1][1];
  tmp.hou[1][2] = t.zuo[0][1];
  // zuo_change
  tmp.zuo[2][1] = t.qian[1][2];
  tmp.zuo[1][1] = t.qian[1][1];
  tmp.zuo[0][1] = t.qian[1][0];
  // qian_change
  tmp.qian[1][0] = t.you[2][1];
  tmp.qian[1][1] = t.you[1][1];
  tmp.qian[1][2] = t.you[0][1];
  // you_change
  tmp.you[0][1] = t.hou[1][0];
  tmp.you[1][1] = t.hou[1][1];
  tmp.you[1][2] = t.hou[1][2];

  tmp.steps.push(9);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}

//操作10：4反向
void act_10(mofang t) {
  mofang tmp;
  tmp = t;
  // hou_change
  tmp.hou[1][0] = t.you[0][1];
  tmp.hou[1][1] = t.you[1][1];
  tmp.hou[1][2] = t.zuo[2][1];
  // zuo_change
  tmp.zuo[2][1] = t.hou[1][0];
  tmp.zuo[1][1] = t.hou[1][1];
  tmp.zuo[0][1] = t.hou[1][2];
  // qian_change
  tmp.qian[1][0] = t.zuo[0][1];
  tmp.qian[1][1] = t.zuo[1][1];
  tmp.qian[1][2] = t.zuo[2][1];
  // you_change
  tmp.you[0][1] = t.qian[1][2];
  tmp.you[1][1] = t.qian[1][1];
  tmp.you[1][2] = t.qian[1][0];

  tmp.steps.push(10);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作11：5正向
void act_11(mofang t) {
  mofang tmp;
  tmp = t;
  // hou_change
  tmp.hou[2][0] = t.zuo[2][2];
  tmp.hou[2][1] = t.zuo[1][2];
  tmp.hou[2][2] = t.zuo[0][2];
  // zuo_change
  tmp.zuo[0][2] = t.qian[0][0];
  tmp.zuo[1][2] = t.qian[0][1];
  tmp.zuo[2][2] = t.qian[0][2];
  // qian_change
  tmp.qian[0][0] = t.you[2][0];
  tmp.qian[0][1] = t.you[1][0];
  tmp.qian[0][2] = t.you[0][0];
  // you_change
  tmp.you[0][0] = t.hou[2][0];
  tmp.you[1][0] = t.hou[2][1];
  tmp.you[2][0] = t.hou[2][2];
  // shangmian_change
  tmp.shang[0][0] = t.shang[2][0];
  tmp.shang[2][0] = t.shang[2][2];
  tmp.shang[2][2] = t.shang[0][2];
  tmp.shang[0][2] = t.shang[0][0];

  tmp.shang[0][1] = t.shang[1][0];
  tmp.shang[1][0] = t.shang[2][1];
  tmp.shang[2][1] = t.shang[1][2];
  tmp.shang[1][2] = t.shang[0][1];

  tmp.steps.push(11);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作12：5反向
void act_12(mofang t) {
  mofang tmp;
  tmp = t;
  // hou_change
  tmp.hou[2][0] = t.you[0][0];
  tmp.hou[2][1] = t.you[1][0];
  tmp.hou[2][2] = t.you[2][0];
  // zuo_change
  tmp.zuo[0][2] = t.hou[2][2];
  tmp.zuo[1][2] = t.hou[2][1];
  tmp.zuo[2][2] = t.hou[2][0];
  // qian_change
  tmp.qian[0][0] = t.zuo[0][2];
  tmp.qian[0][1] = t.zuo[1][2];
  tmp.qian[0][2] = t.zuo[2][2];
  // you_change
  tmp.you[0][0] = t.qian[0][2];
  tmp.you[1][0] = t.qian[0][1];
  tmp.you[2][0] = t.qian[0][0];
  // shangmian_change
  tmp.shang[0][0] = t.shang[0][2];
  tmp.shang[2][0] = t.shang[0][0];
  tmp.shang[2][2] = t.shang[2][0];
  tmp.shang[0][2] = t.shang[2][2];

  tmp.shang[0][1] = t.shang[1][2];
  tmp.shang[1][0] = t.shang[0][1];
  tmp.shang[2][1] = t.shang[1][0];
  tmp.shang[1][2] = t.shang[2][1];

  tmp.steps.push(12);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作13：6正向
void act_13(mofang t) {
  mofang tmp;
  tmp = t;
  // shang_change
  tmp.shang[2][0] = t.zuo[2][0];
  tmp.shang[2][1] = t.zuo[2][1];
  tmp.shang[2][2] = t.zuo[2][2];
  // zuo_change
  tmp.zuo[2][0] = t.xia[0][2];
  tmp.zuo[2][1] = t.xia[0][1];
  tmp.zuo[2][2] = t.xia[0][0];
  // xia_change
  tmp.xia[0][2] = t.you[2][2];
  tmp.xia[0][1] = t.you[2][1];
  tmp.xia[0][0] = t.you[2][0];
  // you_change
  tmp.you[2][0] = t.shang[2][2];
  tmp.you[2][1] = t.shang[2][1];
  tmp.you[2][2] = t.shang[2][0];
  // qianmian_change
  tmp.qian[0][0] = t.qian[2][0];
  tmp.qian[2][0] = t.qian[2][2];
  tmp.qian[2][2] = t.qian[0][2];
  tmp.qian[0][2] = t.qian[0][0];

  tmp.qian[0][1] = t.qian[1][0];
  tmp.qian[1][0] = t.qian[2][1];
  tmp.qian[2][1] = t.qian[1][2];
  tmp.qian[1][2] = t.qian[0][1];

  tmp.steps.push(13);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作14：6反向
void act_14(mofang t) {
  mofang tmp;
  tmp = t;
  // shang_change
  tmp.shang[2][0] = t.you[2][0];
  tmp.shang[2][1] = t.you[2][1];
  tmp.shang[2][2] = t.you[2][2];
  // zuo_change
  tmp.zuo[2][0] = t.shang[2][2];
  tmp.zuo[2][1] = t.shang[2][1];
  tmp.zuo[2][2] = t.shang[2][0];
  // xia_change
  tmp.xia[0][0] = t.zuo[2][2];
  tmp.xia[0][1] = t.zuo[2][1];
  tmp.xia[0][2] = t.zuo[2][0];
  // you_change
  tmp.you[2][0] = t.xia[0][2];
  tmp.you[2][1] = t.xia[0][1];
  tmp.you[2][2] = t.xia[0][0];
  // qianmian_change
  tmp.qian[0][0] = t.qian[0][2];
  tmp.qian[2][0] = t.qian[0][0];
  tmp.qian[2][2] = t.qian[2][0];
  tmp.qian[0][2] = t.qian[2][2];

  tmp.qian[0][1] = t.qian[1][2];
  tmp.qian[1][0] = t.qian[0][1];
  tmp.qian[2][1] = t.qian[1][0];
  tmp.qian[1][2] = t.qian[2][1];

  tmp.steps.push(14);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作15：7正向
void act_15(mofang t) {
  mofang tmp;
  tmp = t;
  // shang_change
  tmp.shang[1][0] = t.zuo[1][0];
  tmp.shang[1][1] = t.zuo[1][1];
  tmp.shang[1][2] = t.zuo[1][2];
  // zuo_change
  tmp.zuo[1][0] = t.xia[1][2];
  tmp.zuo[1][1] = t.xia[1][1];
  tmp.zuo[1][2] = t.xia[1][0];
  // xia_change
  tmp.xia[1][0] = t.you[1][2];
  tmp.xia[1][1] = t.you[1][1];
  tmp.xia[1][2] = t.you[1][0];
  // you_change
  tmp.you[1][0] = t.shang[1][0];
  tmp.you[1][1] = t.shang[1][1];
  tmp.you[1][2] = t.shang[1][2];

  tmp.steps.push(15);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作16：7反向
void act_16(mofang t) {
  mofang tmp;
  tmp = t;
  // shang_change
  tmp.shang[1][0] = t.you[1][0];
  tmp.shang[1][1] = t.you[1][1];
  tmp.shang[1][2] = t.you[1][2];
  // zuo_change
  tmp.zuo[1][0] = t.shang[1][0];
  tmp.zuo[1][1] = t.shang[1][1];
  tmp.zuo[1][2] = t.shang[1][2];
  // xia_change
  tmp.xia[1][0] = t.zuo[1][2];
  tmp.xia[1][1] = t.zuo[1][1];
  tmp.xia[1][2] = t.zuo[1][0];
  // you_change
  tmp.you[1][0] = t.xia[1][2];
  tmp.you[1][1] = t.xia[1][1];
  tmp.you[1][2] = t.xia[1][0];

  tmp.steps.push(16);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作17：8正向
void act_17(mofang t) {
  mofang tmp;
  tmp = t;
  // shang_change
  tmp.shang[0][0] = t.zuo[0][0];
  tmp.shang[0][1] = t.zuo[0][1];
  tmp.shang[0][2] = t.zuo[0][2];
  // zuo_change
  tmp.zuo[0][0] = t.xia[2][2];
  tmp.zuo[0][1] = t.xia[2][1];
  tmp.zuo[0][2] = t.xia[2][0];
  // xia_change
  tmp.xia[2][0] = t.you[0][2];
  tmp.xia[2][1] = t.you[0][1];
  tmp.xia[2][2] = t.you[0][0];
  // you_change
  tmp.you[0][0] = t.shang[0][0];
  tmp.you[0][1] = t.shang[0][1];
  tmp.you[0][2] = t.shang[0][2];
  // qianmian_change
  tmp.qian[0][0] = t.qian[2][0];
  tmp.qian[2][0] = t.qian[2][2];
  tmp.qian[2][2] = t.qian[0][2];
  tmp.qian[0][2] = t.qian[0][0];

  tmp.qian[0][1] = t.qian[1][0];
  tmp.qian[1][0] = t.qian[2][1];
  tmp.qian[2][1] = t.qian[1][2];
  tmp.qian[1][2] = t.qian[0][1];

  tmp.steps.push(17);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}
//操作18：8反向
void act_18(mofang t) {
  mofang tmp;
  tmp = t;
  // shang_change
  tmp.shang[0][0] = t.you[0][0];
  tmp.shang[0][1] = t.you[0][1];
  tmp.shang[0][2] = t.you[0][2];
  // zuo_change
  tmp.zuo[0][0] = t.shang[0][0];
  tmp.zuo[0][1] = t.shang[0][1];
  tmp.zuo[0][2] = t.shang[0][2];
  // xia_change
  tmp.xia[2][0] = t.zuo[0][2];
  tmp.xia[2][1] = t.zuo[0][1];
  tmp.xia[2][2] = t.zuo[0][0];
  // you_change
  tmp.you[0][0] = t.xia[2][2];
  tmp.you[0][1] = t.xia[2][1];
  tmp.you[0][2] = t.xia[2][0];

  tmp.steps.push(18);
  if (is_back(tmp)) {
    flag = 1;
    cout << tmp.steps.size() << endl;
    cout << "steps: " << endl;
    while (!tmp.steps.empty()) {
      cout << tmp.steps.front() << endl;
      tmp.steps.pop();
    }
  }
  q.push(tmp);
}

// 将传入状态t进行num操作，得到的新状态存于队列q中
 
void search(mofang t, int num) {
  
  switch (num) {
    case 1:
      act_1(t);
      break;
    case 2:
      act_2(t);
      break;
    case 3:
      act_3(t);
      break;
    case 4:
      act_4(t);
      break;
    case 5:
      act_5(t);
      break;
    case 6:
      act_6(t);
      break;
    case 7:
      act_7(t);
      break;
    case 8:
      act_8(t);
      break;
    case 9:
      act_9(t);
      break;
    case 10:
      act_10(t);
      break;
    case 11:
      act_11(t);
      break;
    case 12:
      act_12(t);
      break;
    case 13:
      act_13(t);
      break;
    case 14:
      act_14(t);
      break;
    case 15:
      act_15(t);
      break;
    case 16:
      act_16(t);
      break;
    case 17:
      act_17(t);
      break;
    case 18:
      act_18(t);
      break;

    default:
      assert(false);
      break;
  }
}

void my_find_best() {
  q.push(init);
  bool tag = 0; //循环的条件

  while (!q.empty()) {
    mofang tmp = q.front();
    q.pop();

    for (int i = 1; i <= 18; i++) {
      search(tmp, i);
      if (flag == 1) {
        tag = 1;
        break;
      }
    }

    if (tag) {
      break;
    }
  }
}

// 主函数入口
int main() {
  input_cube();
  my_find_best();
}
