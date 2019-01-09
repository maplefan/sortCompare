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

int *nums = (int *)malloc(20000*sizeof(int));//����һ����СΪ20000��int��������nums
double Timecount;//���������ִ��ʱ��ı�������λΪ��
clock_t start;//���忪ʼʱ��
clock_t End;//�������ʱ��
mysort a[8];//��a�������洢��������ֺ�ʱ�䣬�����������
int cnt= 0;//������

//double����תstring���ͺ���
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

void makeRandNumber()//����20000�������������ĿĿ¼��number.txt��
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

void readNums(int nums[]) //��ȡ�ļ��е����ֵ�������
{
    fstream fin;
    fin.open("number.txt", ios::in);
    for(int i = 0; i<20000; i++)
    {
        fin>>nums[i];
    }
    fin.close();
}

void insertSort(int nums[],int n) //��������
{
//�ӵڶ���Ԫ�ؿ�ʼ�������һ��Ԫ��������������
    for (int i = 1; i < n; i++)
    {
        //������Ԫ�� nums[i]
        if (nums[i] < nums[i - 1])
        {
            int wait = nums[i];
            int j = i;
            while (j > 0 && nums[j - 1] > wait)
            {
                //�Ӻ���ǰ�������������飬��������Ԫ��С�ڱ�����Ԫ�أ������Ԫ�����Ųλ��
                nums[j] = nums[j - 1];
                j--;
            }
            nums[j] = wait;
        }
    }
}

void shellSort(int nums[],int n) //ϣ������
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

void bubbleSort(int nums[],int n) //ð������
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
    int i = b, j = e;  //i�������ͷ��j�������β
    int x = a[(b + e) / 2]; //ѡȡ������м�Ԫ����Ϊ���ֵĻ�׼
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


void selectionSort(int nums[],int n) //ѡ������
{
    int i, j, minn;
    for (i = 0; i < n - 1; i++)
    {
        minn = i;                       //��¼��Сֵ���±꣬��ʼ��Ϊi
        for (j=i+1; j<=n-1; j++)
        {
            if (nums[j] < nums[minn])
                minn = j;            //ͨ�����ϵرȽϣ��õ���Сֵ���±�
        }
        swap(nums[i], nums[minn]);
    }
}

// �ݹ鷽ʽ���������(len��arr�ĳ��ȣ�index�ǵ�һ����Ҷ�ӽڵ���±�)
void adjust(int arr[], int len, int index)
{
    int left = 2*index + 1; // index�����ӽڵ�
    int right = 2*index + 2;// index�����ӽڵ�

    int maxIdx = index;
    if(left<len && arr[left] > arr[maxIdx])     maxIdx = left;
    if(right<len && arr[right] > arr[maxIdx])     maxIdx = right;

    if(maxIdx != index)
    {
        swap(arr[maxIdx], arr[index]);
        adjust(arr, len, maxIdx);
    }

}

void heapSort(int nums[],int n) //������
{
    // ��������ѣ������һ����Ҷ�ӽڵ����ϣ�
    for(int i=n/2 - 1; i >= 0; i--)
    {
        adjust(nums, n, i);
    }
    // ���������
    for(int i = n - 1; i >= 1; i--)
    {
        swap(nums[0], nums[i]);           // ����ǰ���ķ��õ�����ĩβ
        adjust(nums, i, 0);              // ��δ�������Ĳ��ּ������ж�����
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
    //����ռ�����ʱ���
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
    //������û�й鲢�꣬��ôֱ�ӽ�ʣ���Ԫ�ظ��Ƶ�tempArray�ĺ���
    if (j == rightLen)
    {
        memcpy(tempArray + i + j, A + start + i, (step - i) * sizeof(int));
    }
    //����ұ�û�й鲢�꣬��ôֱ�ӽ�ʣ���Ԫ�ظ��Ƶ�tempArray�ĺ���
    else if (i == step)
    {
        memcpy(tempArray + i + j, A + mid + j, (rightLen - j) * sizeof(int));
    }
    //����ʱ�������ź�������ݸ��ƻ�ԭ����
    memcpy(A + start, tempArray, (step + rightLen) * sizeof(int));
    delete[] tempArray;
}

void mergeSort(int nums[],int n) //�鲢����
{
    for (int step = 1; step < n; step *= 2)
    {
        for (int i = 0; i < n - step; i += 2*step)
        {
            Merge(nums ,i, i+step, step, n);
        }
    }
}

void mouseListener(int x , int y ,int button ,int event){//���������������ж������
   // cout<<x<<" "<<y<<endl;
       if(x>30 &&x<190&&y>50 &&y<77 && button == 1 && event == 0)//���������жϵ��������������ʱ
    {
             readNums(nums);//��ȡ�ļ��е����ֵ�������
             start = clock();//��ÿ�ʼʱ��
             insertSort(nums,20000);
             End = clock();//��ý���ʱ��
             Timecount = ((double)(End - start)) / CLK_TCK;
             a[0].name = "��������";
             a[0].time = Timecount;
             ofstream fout;
             fout.open("insertSort.txt");//�����������������ļ�
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
             fout.close();
             beginPaint();
             rectangle(190+10,50,190+10+100,75);//��ԭ�ȵ����ָ���
             paintText(190+10,50,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<210&&y>50+70 &&y<77+70 && button == 1 && event == 0)//���������жϵ������ϣ������ʱ
    {
             readNums(nums);//��ȡ�ļ��е����ֵ�������
             start = clock();//��ÿ�ʼʱ��
             shellSort(nums,20000);
             End = clock();//��ý���ʱ��
             Timecount = ((double)(End - start)) / CLK_TCK;
             a[1].name = "ϣ������";
             a[1].time = Timecount;
             ofstream fout;
             fout.open("shellSort.txt");//�����������������ļ�
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(210+10,50+70,210+10+100,75+70);//��ԭ�ȵ����ָ���
             paintText(210+10,50+70,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<195&&y>50+70*2 &&y<77+70*2 && button == 1 && event == 0)//���������жϵ������ð������ʱ
    {
             readNums(nums);//��ȡ�ļ��е����ֵ�������
             start = clock();//��ÿ�ʼʱ��
             bubbleSort(nums,20000);
             End = clock();//��ý���ʱ��
             Timecount = ((double)(End - start)) / CLK_TCK;
            a[2].name = "ð������";
             a[2].time = Timecount;
             ofstream fout;
             fout.open("bubbleSort.txt");//�����������������ļ�
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(195+10,50+70*2,195+10+100,75+70*2);//��ԭ�ȵ����ָ���
             paintText(195+10,50+70*2,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<260&&y>50+70*3 &&y<77+70*3 && button == 1 && event == 0)//���������жϵ��������������ʱ
    {
             readNums(nums);//��ȡ�ļ��е����ֵ�������
             start = clock();//��ÿ�ʼʱ��
             quickSort(0,20000-1,nums);
             End = clock();//��ý���ʱ��
             Timecount = ((double)(End - start)) / CLK_TCK;
                a[3].name = "��������";
             a[3].time = Timecount;
             ofstream fout;
             fout.open("quickSort.txt");//�����������������ļ�
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(260+10,50+70*3,260+10+100,75+70*3);//��ԭ�ȵ����ָ���
             paintText(260+10,50+70*3,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<192&&y>50+70*4 &&y<77+70*4 && button == 1 && event == 0)//���������жϵ������ѡ������ʱ
    {
             readNums(nums);//��ȡ�ļ��е����ֵ�������
             start = clock();//��ÿ�ʼʱ��
             selectionSort(nums,20000);
             End = clock();//��ý���ʱ��
             Timecount = ((double)(End - start)) / CLK_TCK;
             a[4].name = "ѡ������";
             a[4].time = Timecount;
             ofstream fout;
             fout.open("selectionSort.txt");//�����������������ļ�
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(192+10,50+70*4,192+10+100,75+70*4);//��ԭ�ȵ����ָ���
             paintText(192+10,50+70*4,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<237&&y>50+70*5 &&y<77+70*5 && button == 1 && event == 0)//���������жϵ������������ʱ
    {
             readNums(nums);//��ȡ�ļ��е����ֵ�������
             start = clock();//��ÿ�ʼʱ��
             heapSort(nums,20000);
             End = clock();//��ý���ʱ��
             Timecount = ((double)(End - start)) / CLK_TCK;
            a[5].name = "������";
             a[5].time = Timecount;
             ofstream fout;
             fout.open("heapSort.txt");//�����������������ļ�
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(237+10,50+70*5,237+10+100,75+70*5);//��ԭ�ȵ����ָ���
             paintText(237+10,50+70*5,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<257&&y>50+70*6 &&y<77+70*6 && button == 1 && event == 0)//���������жϵ�������鲢����ʱ
    {
             readNums(nums);//��ȡ�ļ��е����ֵ�������
             start = clock();//��ÿ�ʼʱ��
             mergeSort(nums,20000);
             End = clock();//��ý���ʱ��
             Timecount = ((double)(End - start)) / CLK_TCK;
            a[6].name = "�鲢����";
             a[6].time = Timecount;
             ofstream fout;
             fout.open("mergeSort.txt");//�����������������ļ�
             for(int i = 0;i<20000;i++)
             {
                 fout<<nums[i]<<endl;
             }
              fout.close();
             beginPaint();
            rectangle(257+10,50+70*6,257+10+100,75+70*6);//��ԭ�ȵ����ָ���
             paintText(257+10,50+70*6,doubleToString(Timecount).data());
             endPaint();
    }
    else if(x>30 &&x<120&&y>50+70*7 &&y<77+70*7 && button == 1 && event == 0)//���������жϵ�������˳�ʱ
    {
         exit(0);
    }
    else if(x>130 &&x<220&&y>50+70*7 &&y<77+70*7 && button == 1 && event == 0)//���������жϵ����������ʱ
    {
        beginPaint();
        cnt = 0;
        mysort b[7];
        for(int i = 0;i<7;i++){//����һ��������
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

void showIndex()//������
{
    beginPaint();
    setPenColor(RGB(220,220,220));
    setBrushColor(RGB(220,220,220));
    rectangle(0,0,800,600);
    setTextSize(25);
    setTextFont("΢���ź�");
    setTextBkColor(EMPTY);
    setTextColor(YELLOW);
    paintText(30,10,"������������ִ�в�����(ʱ�临�Ӷ�Ϊƽ������)");
    setTextSize(30);
    setTextColor(RGB(246,83,20));
    paintText(30,50,"�������� O(N2)");
    setTextColor(RGB(124,187,0));
    paintText(30,120,"ϣ������ O(N1.3)");
    setTextColor(RGB(0,161,241));
    paintText(30,190,"ð������ O(N2)");
    setTextColor(RGB(255,187,0));
    paintText(30,260,"�������� O(N*log2N) ");
    setTextColor(RGB(96,96,96));
    paintText(30,330,"ѡ������ O(N2)");
    setTextColor(RGB(139, 0, 255));
    paintText(30,400,"������ O(N*log2N)");
    setTextColor(BLACK);
    paintText(30,470,"�鲢���� O(N*log2N) ");
    setTextColor(WHITE);
    paintText(30,540,"�˳�");
    paintText(130,540,"����");
    setTextColor(YELLOW);
    paintText(450,20,"���а�");
    registerMouseEvent(mouseListener);//ע����������������
    endPaint();
}


int Setup()
{
    makeRandNumber();//����20000�������������ĿĿ¼��number.txt��
    initWindow("Sort",DEFAULT,DEFAULT,800,600);
    showIndex();
}
