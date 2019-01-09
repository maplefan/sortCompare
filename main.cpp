#ifdef __cplusplus
extern "C"  {
#endif
#include "acllib.h"
#include <stdio.h>
#ifdef __cplusplus
}
#endif
#include <ctime>
#include<string>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;

struct mysort
{
    string name;
    double time;
};

int *nums = (int *)malloc(20000*sizeof(int));//定义一个大小为20000的int类型数组nums
double Timecount;//定义代表函数执行时间的变量，单位为秒
clock_t start;//定义开始时间
clock_t End;//定义结束时间
mysort a[8];//用a数组来存储排序的名字和时间，方便后面排序
int cnt= 0;//计数器

//double类型转string类型函数
string doubleToString(double num)
{
    stringstream ss;
    string str;
    ss << num;
    ss >> str;
    str = str+"s";
    return str;
}


bool comp(const mysort &a,const mysort &b)
{
    if(a.time == b.time)
    {
        return a.name<b.name;
    }
    else
        return a.time<b.time;
}

void makeRandNumber()//生成20000个随机数放在项目目录的number.txt下
{
    int num = 20000;
    ofstream fout;
    fout.open("number.txt");
    while(num--)
    {
        fout<<rand()<<endl;
    }
    fout.close();
}

void readNums(int nums[]) //读取文件中的数字到数组中
{
    fstream fin;
    fin.open("number.txt", ios::in);
    for(int i = 0; i<20000; i++)
    {
        fin>>nums[i];
    }
    fin.close();
}

void insertSort(int nums[],int n) //插入排序
{
//从第二个元素开始，加入第一个元素是已排序数组
    for (int i = 1; i < n; i++)
    {
        //待插入元素 nums[i]
        if (nums[i] < nums[i - 1])
        {
            int wait = nums[i];
            int j = i;
            while (j > 0 && nums[j - 1] > wait)
            {
                //从后往前遍历已排序数组，若待插入元素小于遍历的元素，则遍历元素向后挪位置
                nums[j] = nums[j - 1];
                j--;
            }
            nums[j] = wait;
        }
    }
}

void shellSort(int nums[],int n) //希尔排序
{
    int i, j;
    int increment = n;
    do
    {
        increment = increment / 3 +1;
        for (i = increment ; i <= n - 1; i++)
        {
            if (nums[i] < nums[i - increment])
            {
                int tmp;
                tmp = nums[i];
                for (j = i - increment; j >= 0 && tmp < nums[j]; j -= increment)
                    nums[j + increment] = nums[j];
                nums[j + increment] = tmp;
            }
        }
    }
    while (increment > 1);
}

void bubbleSort(int nums[],int n) //冒泡排序
{
    for(int i = 0; i<n-1; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            if(nums[i]>nums[j])
            {
                swap(nums[i],nums[j]);
            }
        }
    }
}

void quickSort(int b, int e, int a[])
{
    int i = b, j = e;  //i是数组的头，j是数组的尾
    int x = a[(b + e) / 2]; //选取数组的中间元素作为划分的基准
    while (i<j)
    {
        while (a[i]<x) i++;
        while (a[j]>x) j--;
        if (i <= j)
            std::swap(a[i++], a[j--]);
    }
    if (i<e)
        quickSort(i, e, a);
    if (j>b)
        quickSort(b, j, a);
}


void selectionSort(int nums[],int n) //选择排序
{
    int i, j, minn;
    for (i = 0; i < n - 1; i++)
    {
        minn = i;                       //记录最小值的下标，初始化为i
        for (j=i+1; j<=n-1; j++)
        {
            if (nums[j] < nums[minn])
                minn = j;            //通过不断地比较，得到最小值的下标
        }
        swap(nums[i], nums[minn]);
    }
}

// 递归方式构建大根堆(len是arr的长度，index是第一个非叶子节点的下标)
void adjust(int arr[], int len, int index)
{
    int left = 2*index + 1; // index的左子节点
    int right = 2*index + 2;// index的右子节点

    int maxIdx = index;
    if(left<len && arr[left] > arr[maxIdx])     maxIdx = left;
    if(right<len && arr[right] > arr[maxIdx])     maxIdx = right;

    if(maxIdx != index)
    {
        swap(arr[maxIdx], arr[index]);
        adjust(arr, len, maxIdx);
    }

}

void heapSort(int nums[],int n) //堆排序
{
    // 构建大根堆（从最后一个非叶子节点向上）
    for(int i=n/2 - 1; i >= 0; i--)
    {
        adjust(nums, n, i);
    }
    // 调整大根堆
    for(int i = n - 1; i >= 1; i--)
    {
        swap(nums[0], nums[i]);           // 将当前最大的放置到数组末尾
        adjust(nums, i, 0);              // 将未完成排序的部分继续进行堆排序
    }
}

void Merge(int A[], int start, int mid, int step, int n)
{
    int rightLen = 0;
    if (mid + step > n)
    {
        rightLen = n - mid;
    }
    else
    {
        rightLen = step;
    }
    //申请空间存放临时结果
    int *tempArray = new int[step + rightLen]();
    int i = 0, j = 0, k = 0;
    while (i < step && j < rightLen)
    {
        if (A[start + i] < A[mid + j])
        {
            tempArray[k++] = A[start + i];
            i++;
        }
        else
        {
            tempArray[k++] = A[mid + j];
            j++;
        }
    }
    //如果左边没有归并完，那么直接将剩余的元素复制到tempArray的后面
    if (j == rightLen)
    {
        memcpy(tempArray + i + j, A + start + i, (step - i) * sizeof(int));
    }
    //如果右边没有归并完，那么直接将剩余的元素复制到tempArray的后面
    else if (i == step)
    {
        memcpy(tempArray + i + j, A + mid + j, (rightLen - j) * sizeof(int));
    }
    //将临时数组中排好序的内容复制回原数组
    memcpy(A + start, tempArray, (step + rightLen) * sizeof(int));
    delete[] tempArray;
}

void mergeSort(int nums[],int n) //归并排序
{
    for (int step = 1; step < n; step *= 2)
    {
        for (int i = 0; i < n - step; i += 2*step)
        {
            Merge(nums ,i, i+step, step, n);
        }
    }
}

void mouseListener(int x , int y ,int button ,int event){//监听函数，用来判断鼠标点击
   // cout<<x<<" "<<y<<endl;
       if(x>30 &&x<190&&y>50 &&y<77 && button == 1 && event == 0)//根据坐标判断当鼠标点击插入排序时
    {
             readNums(nums);//读取文件中的数字到数组中
             start = clock();//获得开始时间
             insertSort(nums,20000);
             End = clock();//获得结束时间
             Timecount = ((double)(End - start)) / CLK_TCK;
             a[0].name = "插入排序";
             a[0].time = Timecount;
             ofstream fout;
             fout.open("insertSort.txt");//将排序后数组输出到文件
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
             fout.close();
             beginPaint();
             rectangle(190+10,50,190+10+100,75);//将原先的数字覆盖
             paintText(190+10,50,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<210&&y>50+70 &&y<77+70 && button == 1 && event == 0)//根据坐标判断当鼠标点击希尔排序时
    {
             readNums(nums);//读取文件中的数字到数组中
             start = clock();//获得开始时间
             shellSort(nums,20000);
             End = clock();//获得结束时间
             Timecount = ((double)(End - start)) / CLK_TCK;
             a[1].name = "希尔排序";
             a[1].time = Timecount;
             ofstream fout;
             fout.open("shellSort.txt");//将排序后数组输出到文件
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(210+10,50+70,210+10+100,75+70);//将原先的数字覆盖
             paintText(210+10,50+70,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<195&&y>50+70*2 &&y<77+70*2 && button == 1 && event == 0)//根据坐标判断当鼠标点击冒泡排序时
    {
             readNums(nums);//读取文件中的数字到数组中
             start = clock();//获得开始时间
             bubbleSort(nums,20000);
             End = clock();//获得结束时间
             Timecount = ((double)(End - start)) / CLK_TCK;
            a[2].name = "冒泡排序";
             a[2].time = Timecount;
             ofstream fout;
             fout.open("bubbleSort.txt");//将排序后数组输出到文件
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(195+10,50+70*2,195+10+100,75+70*2);//将原先的数字覆盖
             paintText(195+10,50+70*2,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<260&&y>50+70*3 &&y<77+70*3 && button == 1 && event == 0)//根据坐标判断当鼠标点击快速排序时
    {
             readNums(nums);//读取文件中的数字到数组中
             start = clock();//获得开始时间
             quickSort(0,20000-1,nums);
             End = clock();//获得结束时间
             Timecount = ((double)(End - start)) / CLK_TCK;
                a[3].name = "快速排序";
             a[3].time = Timecount;
             ofstream fout;
             fout.open("quickSort.txt");//将排序后数组输出到文件
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(260+10,50+70*3,260+10+100,75+70*3);//将原先的数字覆盖
             paintText(260+10,50+70*3,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<192&&y>50+70*4 &&y<77+70*4 && button == 1 && event == 0)//根据坐标判断当鼠标点击选择排序时
    {
             readNums(nums);//读取文件中的数字到数组中
             start = clock();//获得开始时间
             selectionSort(nums,20000);
             End = clock();//获得结束时间
             Timecount = ((double)(End - start)) / CLK_TCK;
             a[4].name = "选择排序";
             a[4].time = Timecount;
             ofstream fout;
             fout.open("selectionSort.txt");//将排序后数组输出到文件
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(192+10,50+70*4,192+10+100,75+70*4);//将原先的数字覆盖
             paintText(192+10,50+70*4,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<237&&y>50+70*5 &&y<77+70*5 && button == 1 && event == 0)//根据坐标判断当鼠标点击堆排序时
    {
             readNums(nums);//读取文件中的数字到数组中
             start = clock();//获得开始时间
             heapSort(nums,20000);
             End = clock();//获得结束时间
             Timecount = ((double)(End - start)) / CLK_TCK;
            a[5].name = "堆排序";
             a[5].time = Timecount;
             ofstream fout;
             fout.open("heapSort.txt");//将排序后数组输出到文件
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(237+10,50+70*5,237+10+100,75+70*5);//将原先的数字覆盖
             paintText(237+10,50+70*5,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<257&&y>50+70*6 &&y<77+70*6 && button == 1 && event == 0)//根据坐标判断当鼠标点击归并排序时
    {
             readNums(nums);//读取文件中的数字到数组中
             start = clock();//获得开始时间
             mergeSort(nums,20000);
             End = clock();//获得结束时间
             Timecount = ((double)(End - start)) / CLK_TCK;
            a[6].name = "归并排序";
             a[6].time = Timecount;
             ofstream fout;
             fout.open("mergeSort.txt");//将排序后数组输出到文件
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(257+10,50+70*6,257+10+100,75+70*6);//将原先的数字覆盖
             paintText(257+10,50+70*6,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<120&&y>50+70*7 &&y<77+70*7 && button == 1 && event == 0)//根据坐标判断当鼠标点击退出时
    {
         exit(0);
    }
    else if(x>130 &&x<220&&y>50+70*7 &&y<77+70*7 && button == 1 && event == 0)//根据坐标判断当鼠标点击排名时
    {
        beginPaint();
        cnt = 0;
        mysort b[7];
        for(int i = 0;i<7;i++){//复制一份再排序
            b[i].name = a[i].name;
            b[i].time = a[i].time;
        }
         sort(b,b+7,comp);
         rectangle(450,100,600,450);
         for(int i = 0;i<7;i++){
            if(b[i].time-0.000 != 0)
           {
           string str = b[i].name + " " + doubleToString(b[i].time);
            paintText(450,100+cnt*50,str.data());
            cnt++;
           }
           }

        endPaint();
    }
}

void showIndex()//画界面
{
    beginPaint();
    setPenColor(RGB(220,220,220));
    setBrushColor(RGB(220,220,220));
    rectangle(0,0,800,600);
    setTextSize(25);
    setTextFont("微软雅黑");
    setTextBkColor(EMPTY);
    setTextColor(YELLOW);
    paintText(30,10,"单击下列排序执行操作：(时间复杂度为平均数据)");
    setTextSize(30);
    setTextColor(RGB(246,83,20));
    paintText(30,50,"插入排序 O(N2)");
    setTextColor(RGB(124,187,0));
    paintText(30,120,"希尔排序 O(N1.3)");
    setTextColor(RGB(0,161,241));
    paintText(30,190,"冒泡排序 O(N2)");
    setTextColor(RGB(255,187,0));
    paintText(30,260,"快速排序 O(N*log2N) ");
    setTextColor(RGB(96,96,96));
    paintText(30,330,"选择排序 O(N2)");
    setTextColor(RGB(139, 0, 255));
    paintText(30,400,"堆排序 O(N*log2N)");
    setTextColor(BLACK);
    paintText(30,470,"归并排序 O(N*log2N) ");
    setTextColor(WHITE);
    paintText(30,540,"退出");
    paintText(130,540,"排名");
    setTextColor(YELLOW);
    paintText(450,20,"排行榜：");
    registerMouseEvent(mouseListener);//注册监听函数监听鼠标
    endPaint();
}


int Setup()
{
    makeRandNumber();//生成20000个随机数放在项目目录的number.txt下
    initWindow("Sort",DEFAULT,DEFAULT,800,600);
    showIndex();
}
