## Solution to the Rubik’s Cube！

**1. Experiment Objective**  
The goal of this experiment is to implement a program that solves the Rubik's Cube, i.e., given an initial state, output the sequence of moves required to solve the cube using the breadth-first search (BFS) algorithm.

**2. Solution Approach**  
**(a) Problem Decomposition**  
The Rubik's Cube is unfolded into a flat plane as shown below:

<img width="187" alt="image" src="https://github.com/user-attachments/assets/c5c22726-aa0a-457b-a4f1-3bc92ea46210">

Define a structure `struct mofang` to hold information for the six faces of the cube, where each face is represented as a 2D array to record the color information and the state of the cube. A queue `steps` is used to record the operations performed on the Rubik's Cube.

**(b) Operation Definitions**  
Based on the initial state of the Rubik's Cube, 18 operations are defined for three non-opposite faces, such as 0 clockwise/counterclockwise, 1 clockwise/counterclockwise, and so on, up to 18 clockwise/counterclockwise. The corresponding operation codes are 1, 2, ..., 18.

<img width="415" alt="image" src="https://github.com/user-attachments/assets/cba0775e-6758-4349-8357-2911304c909f">
(PPT image source)

**(c) Core Algorithm**  
The breadth-first search algorithm is used. If the queue is not empty, each of the 18 operations is applied, progressing layer by layer.

**3. Experiment Code**  
1. Define a structure to store each state of the Rubik's Cube and the corresponding operations performed before reaching that state.
   
``` cpp
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
```

2. Write a function to check if the Rubik's Cube is solved, which is quite complex.
```cpp
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
```   
3. Define 18 different operations, taking the first move (0 clockwise) as an example.
   
```cpp
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
```
More in the main.cpp file
   
4. If the cube is solved, end the process and output all the operations required to reach the current state.
``` cpp
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
   ```
5. Implement the breadth-first search algorithm.

```cpp
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
```

**4. Experiment Results**  
The input is the color sequence of the faces of the cube in the order of back, top, front, bottom, left, and right. The output format is:

```cpp
[Total steps needed]
Steps:
Specific steps]
```

1. **Test 1 Output**
   
<img width="265" alt="image" src="https://github.com/user-attachments/assets/5ecb1a8d-42e6-41c4-b483-79056ca03113">

(Results for test case 1)

2. **Test 2 Output**

<img width="118" alt="image" src="https://github.com/user-attachments/assets/03db823e-f4b9-4228-bcb8-57b5b8aefe72">

(Results for test case 2)
