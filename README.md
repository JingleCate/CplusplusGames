## C++项目

> 旧事重提算是，复习一下C++的知识，顺便尝试一下`VS2022`新功能 —— 模块

---

### 1 CoolRun

- 该项目资源来源于[Bilibili](https://www.bilibili.com/video/BV1Ca411k7wU?p=17&spm_id_from=pageDriver&vd_source=41e7e0e737d748569af7bd28d7a17e95)

#### 1.1 文件结构：

```
├─CoolRun
│  │  base.cpp						// 项目基本类实现
│  │  base.h						// 项目基本类
│  │  main.cpp						// 主函数
│  │  obstacles.ixx					// 模块
│  │  SDL2.dll						// SDL库
│  │  tools.cpp						// 工具函数
│  │  tools.h
│  │
│  ├─res					   // 资源文件
```

#### 1.2 代码解析

​	第一个项目没有什么可说的，主要是重新复习一下知识（热身）,CoolRun-setup

操作：

- `Space`起跳
- `Z` or`z` 下蹲

​	初始按任意键进入即可~~

​	其实这个项目有许多的问题，比如跳跃的手感和下蹲的手感差强人意，不过这都问题不大(bushi)....

初始和终态界面都没有优化，按任意键即可开始或退出。后面慢慢优化吧..

---

## 写在最后

> 库函数的生成与使用——VS环境下(代码来源于网络)

###  静态库(`lib`)

#### 1. 生成

​    静态库是不包含main函数。之所以称之为lib静态库，其实就是指，我们需要用到lib里头的函数时，我们才会去手动打包到我们的可执行文件当中。使用静态库中函数要读整块lib，内存空间占取大。

> vs点击属性 --> 常规 --> Configuration Type 将Application (.exe) 改为Static library (.lib)

```c++
#include<stdio.h>
#include<string.h>
#include<windows.h>
 
void msg(char text[] ){
   MessageBox(0, text, "title", 0);
}

int _max(int a , int b) {
    return a > b ? a : b;
}
```

​	生成之后，将该lib文件放置于我们项目的目录中。

#### 2.使用

​	在头文件初，`#prama comment(lib,"*.lib")`;

调用代码：

```c++
#pragma comment(lib,"staticlib.lib")  //引入一个静态库

int main(int argv ,char args []){
   
     meg("你好！");
     printf("%d\n",_max(3,4));
     getchar();
  return 0;
}
```

### 动态库(`dll`)

​	动态库封装了每一个函数，作为一个接口，当我们需要哪个的时候，就可以读取哪个函数的代码到内存块中，占用的内存相对的小很多。

 #### 1. 生成

> vs点击属性 --> 常规 --> Configuration Type 将Application (.exe) 改为 (.lib)

不过在定义函数时需要在前面加载：  `_eclspec(dllexport)`

```c++
#include<stdio.h>
#include<string.h>
#include<windows.h>

_declspec(dllexport) void msg(char text[] ){
  MessageBox(0, text, "title", 0);
}

_declspec(dllexport) int _max(int a , int b) {
    return a > b ? a : b;
}
```

#### 2. 使用

 首先，我们需要定义一些函数指针，来指向这些dll函数地址。 如下面的代码：

```javascript

//定义一个函数指针类型
typedef void(*pmeg)(char []);  //指向meg的一个指针
//定义一个函数指针类型
typedef int(*pmax) (int ,int );  //定义一个指向_max的指针

int main(int argv ,int args[]){

  //定义了指针之后，我们需要使用widow API 来HMoDULE来定义一个模块
    HMODULE mdll;
    mdll = LoadLibraryA("dongdll.dll");  //加载dll文件，需要带路径
    if (NULL == mdll) {
        printf("dll加载失败");
        return ;
    }
    else{
       pmeg mymeg;
        mymeg = (pmeg )GetProcAddress(mdll,"msg");
        if (mymeg != NULL) 
            mymeg("nihao");
        else 
             printf("没有相关函数！ msg");
    }
    getchar();
    return 0;
}
```

