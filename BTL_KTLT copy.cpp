#include <iostream>
#include <windows.h>
#include <iomanip>
#include <fstream>      //doc ghi file
#include <conio.h>      //bat phim
#include <vector> 
using namespace std;

#define BARRIER 3    //vat can

struct robot        
{
  int locationX;
  int locationY;
  int count;
  int point;
  vector<bool>visited;
  vector<int>printcount;
};

struct map          
{
    int row;
    int col;
   vector<vector<int>> arrayMap;
};
void ShowCur(bool CursorVisibility);
void setColor(int color);
void inputMap(map &arr, const char *nameFile);
void outputMap(robot bot, map arr, map arrs,int textcolor);
void copyMap(map arr, map &arrs);
bool mapSameCheck(robot bot,map arrs, bool checkm=true);
void inputRobot(robot &bot,map arr, map &arrs);
void outputRobot (robot bot, map arr);
void writeFileRobot(robot bot, map arr, const char *nameFile);
void writeFileMap(map arrs, const char *nameFile);
void moveUp(robot &bot,map arr,map &arrs);
void moveDown(robot &bot, map arr, map &arrs);
void moveLeft(robot &bot, map arr, map &arrs);
void moveRight(robot &bot, map arr, map &arrs);
bool testVisited(robot &bot,map arr,map &arrs,int temp1, int temp2);
int maxPoint(robot &bot, map arr,map &arrs, int test1,int test2);
void check1 (robot &bot, map arr,map &arrs);
void check2 (robot &bot, map arr,map &arrs);
void check3(robot &bot, map arr,map &arrs);
void findline(robot &bot, map arr,map &arrs);
void autoPlay(robot &bot, map arr, map &arrs);
void twoAutoPlay(robot &bot,robot &bots, map arr, map &arrs, bool twoplay);
void robotPlay(robot &bot, map arr, map arrs);
void same(robot bot, robot bots, map arr, map arrs, bool checkf);
void robotTwoAutoPlay(robot &bot,robot &bots, map arr, map arrs,char temp);
void delay(int ms);
void chooseMap(robot bot,robot bots, map &arr, map &arrs);
void menu(robot bot, robot bots, map arr,map arrs);




//an hien tro
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;
    
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;
    
    SetConsoleCursorInfo(handle, &ConCurInf);
}


void setColor(int color)
{
	WORD wColor;
     

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
}


//Hàm tạo độ trễ
void delay(int ms){
//Thực hiện vòng lặp for nhàm tạo độ trễ chương trình
    for(int t = 0; t< ms; t++){
        for(int i = 0; i<1230000;i++); 
    }
}

//Thong tin ban do
void inputMap(map &arr, const char *nameFile)
{
    ifstream fileMap(nameFile);
    if(!fileMap)
    {
        cerr<<"Can't open File.";
    }
    fileMap>>arr.row>>arr.col;
    arr.arrayMap.resize(arr.row);
    for(int i=0;i<arr.row;i++)
    {
        arr.arrayMap[i].resize(arr.col);
        for (int j=0;j<arr.col;j++)
        {
            fileMap>>arr.arrayMap[i][j];
        }
    }
    fileMap.close();
}


void outputMap(robot bot, map arr, map arrs,int textcolor=7)
{
    bool test=false;
    bool test2=true;
    int index=1;
    setColor(7);
    cout<<"\n\n\t\t\t\t\t\tSimulation maze:"<<endl;
    for (int temp1=0;temp1<=arr.row;temp1++)
        {
            cout<<"\t\t\t\t\t\t";

            for(int temp2=0;temp2<arr.col;temp2++)
            {   
                if(test2==true || temp1==arr.row)
                {
                    cout<<"----------------";
                }
                else
                {    
                    if(arrs.arrayMap[temp1][temp2]==-3)
                    {
                        cout<<"|";
                        setColor(6);
                        cout<<"\tS\t";
                    }
                    else
                        if(arrs.arrayMap[temp1][temp2]==-2 && bot.visited[temp1*arrs.col+temp2]!=true)
                        {
                            cout<<"|";
                            if(textcolor==9)
                            {
                                setColor(10);
                                cout<<"\tR2\t";
                            }
                            else
                            {
                                setColor(9);
                                cout<<"\tR1\t";
                            }
                        }
                    else
                        if(arrs.arrayMap[temp1][temp2]==-2)
                        {
                            for(int temp=1;temp<=bot.printcount.size();temp++)
                            {
                                if(bot.printcount[temp]==arr.arrayMap[temp1][temp2])
                                {
                                    test=true;
                                }
                            }
                            if (test)
                            {
                                test=false;
                                cout<<"|";
                                setColor(textcolor);
                                if(textcolor==9)
                                {
                                    cout<<"\tR1\t";
                                }
                                else
                                {
                                    cout<<"\tR2\t";
                                }
                            }
                            else
                            {
                                cout<<"|";
                                if(textcolor==9)
                                {
                                    setColor(10);
                                    cout<<"\tR2\t";
                                }
                                else
                                {
                                    setColor(9);
                                    cout<<"\tR1\t";
                                }
                            }
                            
                        }
                    else
                        if(arrs.arrayMap[temp1][temp2]==0)
                        {
                            cout<<"|";
                            setColor(4);
                            cout<<"     |0_0|     ";
                        }
                    else
                    {
                        cout<<"|\t"<<arr.arrayMap[temp1][temp2]<<"\t";
                    }
                    setColor(7);
                }
                if(temp2==arr.col-1)
                {
                    if(test2==true)
                    {
                        cout<<"-";
                    }
                    else
                    {
                        cout<<"|";
                    }
                }
            }
            if(test2==true && temp1!=arr.row)
            {
                temp1--;
                test2=false;
            }
            else
            {
                test2=true;
            }
            cout<<"\n";
        }         
}

// ban do di chuyen cua robot
void copyMap(map arr, map &arrs)
{
    arrs.row=arr.row;
    arrs.col=arr.col;
    arrs.arrayMap.swap(arr.arrayMap);    
}




bool mapSameCheck(robot bot,map arrs, bool checkm)
{
    static int copmap=0;
    if(checkm)
    {
        if(arrs.arrayMap[bot.locationX][bot.locationY]==-2)
        {
            copmap=1;
        }
        if(copmap==1 && arrs.arrayMap[bot.locationX][bot.locationY]==0)
        {
            copmap--;
            return true;
        }
    }
    else
    {
        copmap=0;
    }
    return false;
}




//Thong tin robot
void inputRobot(robot &bot,map arr, map &arrs)
{
    do
    {
        cout<<"enter robot location:";
        cin>>bot.locationX;
        cin>>bot.locationY;
        if((bot.locationX<0) || (bot.locationY<0) || (bot.locationX>=arr.row) || (bot.locationY>=arr.col) )
        {
            cout<<"location is off map."<<endl;
        }
    }
    while ((bot.locationX<0) || (bot.locationY<0) || (bot.locationX>=arr.row) || (bot.locationY>=arr.col) || (arr.arrayMap[bot.locationX][bot.locationY]==BARRIER));
    bot.printcount.push_back(bot.locationX*arr.col+bot.locationY);
    bot.count=1;
    bot.point=arr.arrayMap[bot.locationX][bot.locationY];
    bot.printcount.push_back(arr.arrayMap[bot.locationX][bot.locationY]);
    bot.visited.resize(arr.col*arr.row);
    bot.visited.assign(bot.visited.size(),false);          //gan giia tri false cho vung chua
    mapSameCheck(bot,arrs);
    arrs.arrayMap[bot.locationX][bot.locationY]=0;
    system("cls");
}


void outputRobot (robot bot, map arr)
{
    cout<<"\n\n\nStarting position of the robot:("<<bot.printcount[0]/arr.col<<","<<bot.printcount[0]%arr.col<<")"<<endl;
    cout<<"Number of steps: "<<bot.count<<endl;
    cout<<"Point: "<<bot.point<<endl;
    cout<<"Go way: ";
    for(int i=1;i<=bot.count;i++)
    {   if(i<bot.count)
        {
            cout<<bot.printcount[i]<<" -> ";
        }
        else
        {
            cout<< bot.printcount[i];
        }
    }
    cout<<endl;

}




//xuat File
void writeFileRobot(robot bot, map arr, const char *nameFile)
{
    fstream outputRobot(nameFile, std::ios::app);
    if(!outputRobot)
    {
        cerr<<"Can't open File.";
    }
    else
    {
        outputRobot<<"\nStarting position of the robot:("<<bot.printcount[0]/arr.col<<","<<bot.printcount[0]%arr.col<<")"<<endl;
        outputRobot<<"Number of steps: "<<bot.count<<endl;
        outputRobot<<"Point: "<<bot.point<<endl;
        outputRobot<<"Go way: ";
        for(int i=1;i<=bot.count;i++)
        {   if(i<bot.count)
            {
                outputRobot<<bot.printcount[i]<<" -> ";
            }
            else
            {
                outputRobot<< bot.printcount[i];
            }
        }
        outputRobot<<endl;
        outputRobot.close();
    }
}


void writeFileMap(map arrs, const char *nameFile)
{
    fstream outputMap(nameFile, std::ios::app);
    if(!outputMap)
    {
        cerr<<"Can't open File."<<endl;
    }
    outputMap<<"\n\nMap:"<<endl;
    for(int i=0;i<arrs.row;i++)
    {
        for(int j=0;j<arrs.col;j++)
        {
            outputMap<<arrs.arrayMap[i][j]<<"  ";
        }
        outputMap<<endl;
    }
    outputMap.close();
}




//huong di chuyen cua Robot
void moveUp(robot &bot,map arr, map &arrs)
{  
    static int same1;
    if(mapSameCheck(bot,arrs))
    {
        arrs.arrayMap[bot.locationX][bot.locationY]=-3;
    }
    else
        if(same1<=bot.count-1 && same1!=0)
        {
            arrs.arrayMap[bot.locationX][bot.locationY]=0;
        }
    else
    {
        arrs.arrayMap[bot.locationX][bot.locationY]=-2;
    }
    bot.locationX--;
    if(arrs.arrayMap[bot.locationX][bot.locationY]==0 && bot.visited[bot.locationX*arr.col+bot.locationY]!=true)
    {
        same1=bot.count;
    }
    else
    {
        same1=0;
    }
    bot.count++;
    bot.point+=arr.arrayMap[bot.locationX][bot.locationY];
    bot.printcount.push_back(arr.arrayMap[bot.locationX][bot.locationY]);
    mapSameCheck(bot,arrs);
    arrs.arrayMap[bot.locationX][bot.locationY]=0;
}


void moveDown(robot &bot, map arr, map &arrs)
{

    static int same1;
    if(mapSameCheck(bot,arrs))
    {
        arrs.arrayMap[bot.locationX][bot.locationY]=-3;
    }
    else
        if(same1<=bot.count-1 && same1!=0)
        {
            arrs.arrayMap[bot.locationX][bot.locationY]=0;
        }
    else
    {
        arrs.arrayMap[bot.locationX][bot.locationY]=-2;
    }
    bot.locationX++;
    if(arrs.arrayMap[bot.locationX][bot.locationY]==0 && bot.visited[bot.locationX*arr.col+bot.locationY]!=true)
    {
        same1=bot.count;
    }
    else
    {
        same1=0;
    }
    bot.count++;
    bot.point+=arr.arrayMap[bot.locationX][bot.locationY];
    bot.printcount.push_back(arr.arrayMap[bot.locationX][bot.locationY]);
    mapSameCheck(bot,arrs);
    arrs.arrayMap[bot.locationX][bot.locationY]=0;
}


void moveLeft(robot &bot, map arr, map &arrs)
{
    static int same1;
    if(mapSameCheck(bot,arrs))
    {
        arrs.arrayMap[bot.locationX][bot.locationY]=-3;
    }
    else
        if(same1<=bot.count-1 && same1!=0)
        {
            arrs.arrayMap[bot.locationX][bot.locationY]=0;
        }
    else
    {
        arrs.arrayMap[bot.locationX][bot.locationY]=-2;
    }
    bot.locationY--;
    if(arrs.arrayMap[bot.locationX][bot.locationY]==0 && bot.visited[bot.locationX*arr.col+bot.locationY]!=true)
    {
        same1=bot.count;
    }
    else
    {
        same1=0;
    }
    bot.count++;
    bot.point+=arr.arrayMap[bot.locationX][bot.locationY];
    bot.printcount.push_back(arr.arrayMap[bot.locationX][bot.locationY]);
    mapSameCheck(bot,arrs);
    arrs.arrayMap[bot.locationX][bot.locationY]=0;
}


void moveRight(robot &bot, map arr, map &arrs)
{
    static int same1;
    if(mapSameCheck(bot,arrs))
    {
        arrs.arrayMap[bot.locationX][bot.locationY]=-3;
    }
    else
        if(same1<=bot.count-1 && same1!=0)
        {
            arrs.arrayMap[bot.locationX][bot.locationY]=0;
        }
    else
    {
        arrs.arrayMap[bot.locationX][bot.locationY]=-2;
    }
    bot.locationY++;
    if(arrs.arrayMap[bot.locationX][bot.locationY]==0 && bot.visited[bot.locationX*arr.col+bot.locationY]!=true)
    {
        same1=bot.count;
    }
    else
    {
        same1=0;
    }
    bot.count++;
    bot.point+=arr.arrayMap[bot.locationX][bot.locationY];
    bot.printcount.push_back(arr.arrayMap[bot.locationX][bot.locationY]);
    mapSameCheck(bot,arrs);
    arrs.arrayMap[bot.locationX][bot.locationY]=0;
}



//vi tri ghe tham
bool testVisited(robot &bot,map arr,map &arrs,int temp1, int temp2)
{
    if((bot.visited[temp1*arr.col+temp2]==true) 
        && ((arrs.arrayMap[temp1][temp2]==-2) ||(arrs.arrayMap[temp1][temp2]==-3) ||(arrs.arrayMap[temp1][temp2]==0)))
    {
        return true;
    }
    else 
        return false;
    
}                                           
int maxPoint(robot &bot, map arr,map &arrs, int test1,int test2)
{
    int max=test1;
    int temp=2;
    do
    {
        if(test1==BARRIER)
        {
            if(test2==BARRIER)
            {
                break;
            }
            else
            {
                max=test2;
            }
        }
        for(int i=0;i<arr.row;i++)
        {
            for(int j=0;j<arr.col;j++)
            {
                if(max==arr.arrayMap[i][j])
                {
                    if((max==test1) && (testVisited(bot,arr,arrs,i,j)==true))
                    {
                       max=test2;
                       test1=BARRIER;
                       temp--;
                    }
                    else 
                        if((max==test1) && (testVisited(bot,arr,arrs,i,j)!=true))
                        {
                            if(max<test2 )
                            {
                                max=test2 ;
                                temp--;
                            }
                            else
                            {
                                return test1;
                            }
                        }
                    else
                    {
                        if(testVisited(bot,arr,arrs,i,j) || test2==BARRIER)
                        {
                            if(test1!=BARRIER )
                                {
                                    return test1;
                                }
                            else
                            {
                                return BARRIER;
                            }
                        }
                        else 
                        {
                            return test2;
                        }
                    }
                }    
            }
        }
    }
    while(temp>0);
    return BARRIER;
}


void check1 (robot &bot, map arr,map &arrs)
{
    int temp2, temp3, temp4;
    int test1, test2;
    temp2=arr.arrayMap[bot.locationX-1][bot.locationY];     //moveUp
    if(bot.locationY==(arr.col-1))
    {
        temp4=arr.arrayMap[bot.locationX][bot.locationY-1];     //moveLeft
        test1= maxPoint(bot,arr,arrs,temp2,temp4);
        if(temp2==test1 )
        {
            moveUp(bot,arr,arrs);
        }
        else
            if(test1!=BARRIER)
            {
                moveLeft(bot,arr,arrs);
            }
    }
    else
        if(bot.locationY==0)
        {            
            temp3=arr.arrayMap[bot.locationX][bot.locationY+1];     //moveRight
            test1=maxPoint(bot,arr,arrs,temp3,temp2);
            if(temp3==test1)
            {
                moveRight(bot,arr,arrs);
            }
            else
                if(test1!=BARRIER)
                {
                    moveUp(bot,arr,arrs);
                }
        }
    else
    {
        temp3=arr.arrayMap[bot.locationX][bot.locationY+1];     //moveRight
        temp4=arr.arrayMap[bot.locationX][bot.locationY-1];     //moveLeft
        test1=maxPoint(bot,arr,arrs,temp3,temp4);
        test2=maxPoint(bot,arr,arrs,temp2,test1);
        if(test1==test2 && test1!=BARRIER)
        {
            if(test1==temp3)
            {
                moveRight(bot,arr,arrs);
            }
            else
            {
                moveLeft(bot,arr,arrs);
            }
        }
        else
            if(test2!=BARRIER)
            {
                moveUp(bot,arr,arrs);
            }
    }
}

void check2 (robot &bot, map arr,map &arrs)
{
    int temp1, temp3, temp4;
    int test1, test2;
    temp1=arr.arrayMap[bot.locationX+1][bot.locationY];     //moveDown
   if(bot.locationY==(arr.col-1))
    {
        temp4=arr.arrayMap[bot.locationX][bot.locationY-1];     //moveLeft
        test1= maxPoint(bot,arr,arrs,temp1,temp4);
        if(temp1==test1)
        {
            moveDown(bot,arr,arrs);
        }
        else
            if(test1!=BARRIER)
            {
                moveLeft(bot,arr,arrs);
            }
    }
    else
        if(bot.locationY==0)
        {
            temp3=arr.arrayMap[bot.locationX][bot.locationY+1];     //moveRight
            test1=maxPoint(bot,arr,arrs,temp3,temp1);
            if(temp3==test1)
            {
                moveRight(bot,arr,arrs);
            }
            else
                if(test1!=BARRIER)
                {
                    moveDown(bot,arr,arrs);
                }
        } 
    else
    {
        temp3=arr.arrayMap[bot.locationX][bot.locationY+1];     //moveRight
        temp4=arr.arrayMap[bot.locationX][bot.locationY-1];     //moveLeft
        test1=maxPoint(bot,arr,arrs,temp3,temp4);
        test2=maxPoint(bot,arr,arrs,temp1,test1);
        if(test1==test2 && test1!=BARRIER)
        {
            if(test1==temp3)
            {
                moveRight(bot,arr,arrs);
            }
            else
            {
                moveLeft(bot,arr,arrs);
            }
        }
        else
            if(test2!=BARRIER)
            {
                moveDown(bot,arr,arrs);
            }
    }
}

void check3(robot &bot, map arr,map &arrs)
{
    int temp1,temp2, temp3, temp4;
    int test1, test2;
    temp1=arr.arrayMap[bot.locationX+1][bot.locationY];     //moveDown
    temp2=arr.arrayMap[bot.locationX-1][bot.locationY];     //moveUp
    if(bot.locationY==(arr.col-1))
    {
        temp4=arr.arrayMap[bot.locationX][bot.locationY-1];     //moveLeft
        test1= maxPoint(bot,arr,arrs,temp1,temp2);
        test2=maxPoint(bot,arr,arrs,temp4,test1);
        if(test1==test2 && test1!=BARRIER)
        {
            if(test1==temp1)
            {
                moveDown(bot,arr,arrs);
            }
            else
            {
                moveUp(bot,arr,arrs);
            }
        }
        else
            if(test2!=BARRIER)
            {
                moveLeft(bot,arr,arrs);
            }
    }
    else
        if(bot.locationY==0)
        {
            temp3=arr.arrayMap[bot.locationX][bot.locationY+1];     //moveRight
            test1=maxPoint(bot,arr,arrs,temp2,temp1);
            test2=maxPoint(bot,arr,arrs,temp3,test1);
            if(test1==test2 && test1!=BARRIER)
            {
                if(test1==temp1)
                {
                    moveDown(bot,arr,arrs);
                }
                else
                {
                    moveUp(bot,arr,arrs);
                }
            }
            else
                if(test2!=BARRIER)
                {
                    moveRight(bot,arr,arrs);
                } 
        }  
    else
    {
        temp3=arr.arrayMap[bot.locationX][bot.locationY+1];     //moveRight
        temp4=arr.arrayMap[bot.locationX][bot.locationY-1];     //moveLeft
        test1=maxPoint(bot,arr,arrs,temp1,temp2);
        test2=maxPoint(bot,arr,arrs,temp3,temp4);
        if(test1>test2 && test1!=BARRIER)
        {
            if(test1==temp1)
            {
                moveDown(bot,arr,arrs);
            }
            else
            {
                moveUp(bot,arr,arrs);
            }
        }
        else
            if(test2!=BARRIER)
            {
                if(test2==temp3)
                {
                    moveRight(bot,arr,arrs);
                }
                else
                {
                    moveLeft(bot,arr,arrs);
                }
            }
    }       
}

//Duong di hop le thoa đieu kien Robot co the di
void findline(robot &bot, map arr,map &arrs)
{  
    if(bot.locationX==(arr.row-1))
    {
        check1(bot,arr,arrs);           
    }
    else
        if(bot.locationX==0)
        {
            check2(bot,arr,arrs);
        }
    else
        {
            check3(bot,arr,arrs);
        }   
}



void autoPlay(robot &bot, map arr, map &arrs)
{
    ShowCur(false);
    outputRobot(bot,arr);
    outputMap(bot,arr,arrs,9);
    if(bot.visited[bot.locationX*arr.col+bot.locationY]!=true)
    {       
        bot.visited[bot.locationX*arr.col+bot.locationY]=true;
        delay(1000);
        findline(bot,arr,arrs);
        system("cls");
        autoPlay(bot,arr,arrs);
    }
    else
    {
        ShowCur(true);
    }
}


void twoAutoPlay(robot &bot,robot &bots, map arr, map &arrs, bool twoplay=true)
{
    int &temp1=bot.locationX;
    int &temp2=bot.locationY;
    int &temp3=bots.locationX; 
    int &temp4=bots.locationY;
    ShowCur(false);
    outputRobot(bot,arrs);
    outputMap(bots,arr,arrs,10);
    outputRobot(bots,arr); 
    if(twoplay)
    {   
        if(bots.visited[temp3*arr.col+temp4]!=true || bot.visited[temp1*arr.col+temp2]!=true)
        {
            if(bot.visited[temp1*arr.col+temp2]!=true )
            {
                bot.visited[temp1*arr.col+temp2]=true;
                delay(1400);
                findline(bot,arr,arrs);
                bots.visited[temp1*arr.col+temp2]=true;
                system("cls");
                outputRobot(bot,arr);
                outputMap(bots,arr,arrs,10);
                outputRobot(bots,arr);
            }
            if(bots.visited[temp3*arr.col+temp4]!=true)
            { 
                bots.visited[temp3*arr.col+temp4]=true;
                delay(1400);
                findline(bots,arr,arrs);
                bot.visited[temp3*arr.col+temp4]=true;
                system("cls");
            } 
            else
            {
                delay(1300);
                system("cls");
            }
            twoAutoPlay(bot,bots,arr,arrs);  
        }
        else
        {
            ShowCur(true);
        }
    }
    else
    {
        if(bots.visited[temp3*arr.col+temp4]!=true)
        {
            delay(1000);
            bots.visited[temp3*arr.col+temp4]=true;
            findline(bots,arr,arrs);
            system("cls");
            twoAutoPlay(bot,bots,arr,arrs,0);
        }
        else
        {
            ShowCur(true);
        }
    }
}





void robotPlay(robot &bot, map arr, map arrs)
{
    system("cls");
    inputRobot(bot,arr,arrs);
    autoPlay(bot,arr,arrs);
    char temp;

    cout<<"Do you want to export the file?"<<endl;
    cout<<"[y/n]:";
    cin>>temp;
    if(temp=='y' || temp=='Y')
    {
       writeFileRobot(bot,arr,"output.txt");
        writeFileMap(arrs,"output.txt");
    }
    bot.printcount.clear();
    copyMap(arr,arrs);
}


//trung nhau
void same(robot bot, robot bots, map arr, map arrs, bool checkf=false)
{
    int index=0;
    vector <int> temp;
    temp.push_back(0);
    int temp1=0;
        for(int i=1;i<=bot.count;i++)
        {
            for(int j=1;j<=bots.count;j++)
            {
                if(bot.printcount[i]==bots.printcount[j])
                {
                    temp.push_back(bot.printcount[i]);
                    break;
                }
            }
        }
        if(temp.size()==1)
        {
            cout<<0;
        }
        else
        {
            for(int j=0;j<(arr.col)*(arr.row);j++)
            {
                for(const auto &i:temp )
                {
                    if (i==arr.arrayMap[j/(arr.col)][j%(arr.col)])
                    {
                        temp1++;
                        if(checkf)
                        {
                            fstream outputSame("output.txt", std::ios::app);
                            if(!outputSame)
                            {
                                cerr<<"Can't open File.";
                            }
                            else
                                if(temp.size()==1)
                                {
                                    outputSame<<0;
                                }
                            else
                            {
                                outputSame<<"("<<j/(arr.col)<<","<<j%(arr.col)<<"):"<<i<<"  ";
                            }
                            outputSame.close();
                        }
                        else
                        {
                            cout<<i<<"  ";
                        }
                        break;
                    }
                }
            }
        }
    cout<<"\n\nTotal number of dmoveUplicate steps:"<<temp1;
}


void robotTwoAutoPlay(robot &bot,robot &bots, map arr, map arrs,char temp)
{   
    system("cls");
    if(temp=='3')
    {
        inputRobot(bot,arr,arrs);
        autoPlay(bot,arr,arrs);
        inputRobot(bots,arr,arrs);
        if(bot.printcount[0]==bots.printcount[0])
        {
            inputRobot(bots,arr,arrs);
        }
        twoAutoPlay(bot,bots,arr,arrs,0);
        cout<<"Coincident positions: ";
        same(bot,bots,arr,arrs); 
    }
    if(temp=='4')
    {
        inputRobot(bot,arr,arrs);
        inputRobot(bots,arr,arrs);
        if(bot.printcount[0]==bots.printcount[0])
        {
            inputRobot(bots,arr,arrs);
        }
        bot.visited[bots.locationX*arr.col+bots.locationY]=true;
        bots.visited[bot.locationX*arr.col+bot.locationY]=true;
        twoAutoPlay(bot,bots,arr,arrs);
        cout<<"\n\n\n";
        cout<<setw(74)<<"END GAME\n\n"<<endl;
        if(bot.point>bots.point)
        {
            cout<<setw(50)<<"Robot 1 Win"<<setw(50)<<"Robot 2 Lost."<<endl;
            cout<<setw(45)<<"Point: "<<bot.point<<setw(47)<<"Point: "<<bots.point;
        }
        else
            if(bot.point==bots.point)
            {
                cout<<setw(50)<<"Two RoBot Win."<<endl;
                cout<<setw(45)<<"Point: "<<bot.point;
            }
        else
        {
            cout<<setw(50)<<"Robot 1 Lost"<<setw(50)<<"Robot 2 Win."<<endl;
            cout<<setw(45)<<"Point: "<<bot.point<<setw(47)<<"Point: "<<bots.point;
        }
    }   
    char temps;
    cout<<"\n\n\nDo you want to export the file?"<<endl;
    cout<<"[y/n]:";
    cin>>temps;
    if(temps=='y' || temps=='Y')
    {
        writeFileRobot(bot,arr,"output.txt");
        writeFileRobot(bots,arr,"output.txt");
        writeFileMap(arrs,"output.txt");
        if(temp=='3')
        {
            fstream openfile("output.txt", std::ios::app);
            openfile<<"Coincident positions:\n";
            openfile.close();
            same(bot,bots,arr,arrs,1);
        }
    }
    system("cls");
    bot.printcount.clear();
    bots.printcount.clear();
    copyMap(arr,arrs);
}



void chooseMap(robot bot,robot bots, map &arr, map &arrs)
{
    system("cls");
    char temp1;
    cout<<"\n\n";
    cout<<"\t\t\t\t\t\t\t\t1. Choose Map.\n\n";
    cout<<"\t\t\t\t\t\t\t\t\tI. Map_1(5x5)\t\t\tII. Map_2(6x6)\n";
    cout<<"\t\t\t\t\t\t\t\t\tIII. Map_3(10x10)\t\tIV. Map\n\n";
    cout<<"\t\t\t\t\t\t\t\t\tChoose: ";
    temp1=getch();
    cout<<temp1;
    delay(550);
    if(temp1=='1')
        {
            system("cls");
            cout<<"\n\n\t\t\t\t\t\tI. Map_1(5x5)\n";
            inputMap(arr,"Map1.txt");
            copyMap(arr,arrs);
            outputMap(bot,arr,arrs);
            delay(3000);
        }
    else
        if(temp1=='2')
        {
            system("cls");
            cout<<"\n\n\t\t\t\t\t\tII. Map_2(6x6)\n";
            inputMap(arr,"Map2.txt");
            copyMap(arr,arrs);
            outputMap(bot,arr,arrs);
            delay(3000);

        }
    else
        if(temp1=='3')
        {
            system("cls");
            cout<<"\n\n\t\t\t\t\t\tIII. Map_3(10x10)\n";
            inputMap(arr,"Map3.txt");
            copyMap(arr,arrs);
            outputMap(bot,arr,arrs);
            delay(3000);
        }
    else 
        if(temp1=='4')
        {
            system("cls");
            cout<<"\n\n\t\t\t\t\t\tIV. Map\n";
            inputMap(arr,"Map.txt");
            copyMap(arr,arrs);
            outputMap(bot,arr,arrs);
            delay(3000);
        }
}


void menu(robot bot, robot bots, map arr,map arrs)
{
    char index;
    do
    {   
        system("cls");
        cout<<"\n\n";
        cout<<"\t\t\t\t\t\t\t\t=============================MENU============================\n\n";
        cout<<"\t\t\t\t\t\t\t\t\t\t\tSIMULATION MAZE\n\n";
        cout<<"\t\t\t\t\t\t\t\t1. Choose Map.\n";
        cout<<"\t\t\t\t\t\t\t\t2. Robot moves in the maze.\n";
        cout<<"\t\t\t\t\t\t\t\t3. Two robots moving in the maze.(The moving position may overlap)\n";
        cout<<"\t\t\t\t\t\t\t\t4. Two robots moving in the maze.(The moving position can't overlap)\n";
        cout<<"\t\t\t\t\t\t\t\t5.Exit.\n";
        cout<<"\t\t\t\t\t\t\t\t*Note: You can use 1-2-3-4-5 keys to choose\n\n";
        cout<<"\t\t\t\t\t\t\t\t==============================END==============================\n";
        cout<<"\t\t\t\t\t\t\tChoose:";
        index=getch();
        cout<<index;
        delay(600);
        cout<<"\n\n";
            if(index=='1')
            {
                chooseMap(bot,bots,arr,arrs);
            }
            else
                if(index=='2')
                {
                   robotPlay(bot,arr,arrs);
                }
            else
                if(index=='3')
                {
                    robotTwoAutoPlay(bot,bots,arr,arrs,index);
                    mapSameCheck(bot,arrs,0);
                }
            else
                if(index=='4')
                {
                    robotTwoAutoPlay(bot,bots,arr,arrs,index);
                    mapSameCheck(bot,arrs,0);
                }
            else 
                if(index=='5')
                    exit(0);
    } while (true);   
}



int main()
{
    robot robot1;
    robot robot2;
    map array;
    map arrays;
    menu(robot1,robot2,array,arrays);   
    return 0;
}
