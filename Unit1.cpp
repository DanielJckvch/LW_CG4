//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//Призма
void print(MyPoint* o, TImage* Image1);
//void rotandscale(TImage* Image1, double par, int sw, char a, char b, MyPoint& V);

void prisminit(MyPoint* o);
MyPoint* prism=new MyPoint[6];
double h=150.0;

int x=200;
int y=400;
int rad=100;
double a_step=10;
int sc_step=2;
int mov_step=10;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Form1Create(TObject *Sender)
{
//Инициализация и вывод шестиугольнка
prisminit(prism);
print(prism, Image1);
}
//---------------------------------------------------------------------------
void print(MyPoint* o, TImage* Image1)
{
int k;
double pi = 3.1415926;
double a=45.0*pi/180; //x
double b=35.26*pi/180; //y
int d=200;
double isproj[4][4]=
{{cos(a),sin(a)*cos(b),sin(a)*sin(b),0},
{-sin(a),cos(a)*cos(b),sin(b)*cos(a),0},
{0,-sin(b),cos(b),0},
{0,0,0,1}};
double c=b;
double zrot[4][4]=
{{1,0,0,0},
{0,cos(c),sin(c),0},
{0,-sin(c),cos(c),0},
{0,0,0,1}};
double zproj[4][4]=
{{1,0,0,0},
{0,1,0,0},
{0,0,0,0},
{0,0,0,1}};
double sp[6][4];
for(k=0;k<6;k++)
{
int v1[4]={o[k].get_x(),o[k].get_y(),o[k].get_z(),1};
int v2[4]={0, 0, 0, 1};
int i, j;
for (i = 0;i < 4;i++)
{
        double sum = 0;
        for (j = 0;j < 4;j++)
        {
                sum= sum+ (isproj[j][i] * v1[j]);
        }

        v2[i] = sum;
}
sp[k][0]= v2[0];
sp[k][1]= v2[1];
sp[k][2]= v2[2];
sp[k][3]= v2[3];
}
 
/*
 //Проверка на выход точки за холст
v1[0]=v2[0];
v1[1]=v2[1];
if(v2[0]+hexagon[0].get_x()<=0||v2[1]+hexagon[0].get_y()<=0)
{
hexagon[0].set_x();
hexagon[0].set_y();
hexagon[1].set_x();
hexagon[1].set_y();
out_f=true;
break;
 }    */

//Отрисовка контура
int off_x, off_y;
for(k=0; k<6;k++)
{
Image1->Canvas->MoveTo(sp[k][0]+d,sp[k][1]+d);
if(k%3!=2)
{
Image1->Canvas->LineTo(sp[k+1][0]+d,sp[k+1][1]+d);
}
else
{
 Image1->Canvas->LineTo(sp[k-2][0]+d,sp[k-2][1]+d);
}
Image1->Canvas->TextOutA(sp[k][0]+d,sp[k][1]+d,o[k].get_let());
}
for(k=0; k<3;k++)
{
Image1->Canvas->MoveTo(sp[k][0]+d,sp[k][1]+d);
Image1->Canvas->LineTo(sp[k+3][0]+d,sp[k+3][1]+d);

}

/*for(++k; k<6; k++)
{
Image1->Canvas->MoveTo(sp[k][0]+200,sp[k][1]+200);
Image1->Canvas->LineTo(sp[k+1][0]+200,sp[k+1][1]+200);
}
Image1->Canvas->MoveTo(sp[k-1][0]+200,sp[k][k-1]+200);
Image1->Canvas->LineTo(sp[k-3][0]+200,sp[k-3][1]+200);
*/
/*
//Расставление букв точек
for(k=0; k<3; k++)
{
//Определение значения отступа для буквы
off_x=(o[k].get_x()<0)?-6:4;
off_y=(o[k].get_y()<0)?-12:2;

Image1->Canvas->MoveTo(o[k].get_x(),o[k].get_y());
Image1->Canvas->TextOutA(o[k].get_x()+off_x,o[k].get_y()+off_y,o[k].get_let());
}
 */
}
/*
void rotandscale(TImage* Image1, double par, int sw, MyPoint& V)
{
double r[3][3];
// Выбор способа преобразования
 switch(sw)
 {
 case 0:
 r[0][0]=cos(par*3.14/180);
 r[0][1]=sin(par*3.14/180);
 r[0][2]=0;
 r[1][0]=-sin(par*3.14/180);
 r[1][1]=cos(par*3.14/180);
 r[1][2]=0;
 r[2][0]=0;
 r[2][1]=0;
 r[2][2]=1;
 break;
 case 1:
 r[0][0]=par;
 r[0][1]=0;
 r[0][2]=0;
 r[1][0]=0;
 r[1][1]=par;
 r[1][2]=0;
 r[2][0]=0;
 r[2][1]=0;
 r[2][2]=1;
 break;
 }
// Преобразование точки V
int v1[3]={V.get_x(),V.get_y(),1};
int v2[3]={0, 0, 1};
int i, j;
for (i = 0;i < 3;i++)
{
        double sum = 0;
        for (j = 0;j < 3;j++)
        {
                sum= sum+ (r[j][i] * v1[j]);
        }

        v2[i] = sum;
        if(v2[i]-sum>=0.5)
        {
        v2[i]++;
        }
}
V.set_x(v2[0]);
V.set_y(v2[1]);
}
 */
void __fastcall TForm1::Button1Click(TObject *Sender)
{
//Поворот против часовой стрелки
//rotandscale(Image1, -a_step, 0, (hexagon[1]));
//Очистка холста
TRect rct;
rct = Rect(0,0,Image1->Width,Image1->Height);
Image1->Canvas->Brush->Style=bsSolid;
Image1->Canvas->FillRect(rct);
 //Отрисовка
print(prism, Image1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
//Поворот по часовой стрелке
//rotandscale(Image1, a_step, 0, (hexagon[1]));
//Очистка холста
TRect rct;
rct = Rect(0,0,Image1->Width,Image1->Height);
Image1->Canvas->Brush->Style=bsSolid;
Image1->Canvas->FillRect(rct);
 //Отрисовка
//printhexagon(hexagon, Image1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
//?Масштаб -
//rotandscale(Image1, (double)1/sc_step, 1, (hexagon[1]));
//Очистка холста
TRect rct;
rct = Rect(0,0,Image1->Width,Image1->Height);
Image1->Canvas->Brush->Style=bsSolid;
Image1->Canvas->FillRect(rct);
 //Отрисовка
//printhexagon(hexagon, Image1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
//Масштаб +
//rotandscale(Image1, sc_step, 1, (hexagon[1]));
//Очистка холста
TRect rct;
rct = Rect(0,0,Image1->Width,Image1->Height);
Image1->Canvas->Brush->Style=bsSolid;
Image1->Canvas->FillRect(rct);
 //Отрисовка
//printhexagon(hexagon, Image1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
//Сдвиг влево
for(int i=0; i<6; i++)
{
 prism[i].set_x(prism[i].get_x()-mov_step);
}
//Очистка холста
TRect rct;
rct = Rect(0,0,Image1->Width,Image1->Height);
Image1->Canvas->Brush->Style=bsSolid;
Image1->Canvas->FillRect(rct);
//Отрисовка
print(prism, Image1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
//Сдвиг вправо
for(int i=0; i<6; i++)
{
 prism[i].set_x(prism[i].get_x()+mov_step);
}
//Очистка холста
TRect rct;
rct = Rect(0,0,Image1->Width,Image1->Height);
Image1->Canvas->Brush->Style=bsSolid;
Image1->Canvas->FillRect(rct);
//Отрисовка
print(prism, Image1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
//Сдвиг вниз
for(int i=0; i<6; i++)
{
 prism[i].set_z(prism[i].get_z()+mov_step);
}
//Очистка холста
TRect rct;
rct = Rect(0,0,Image1->Width,Image1->Height);
Image1->Canvas->Brush->Style=bsSolid;
Image1->Canvas->FillRect(rct);
 //Отрисовка
print(prism, Image1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
//Сдвиг вверх
for(int i=0; i<6; i++)
{
 prism[i].set_z(prism[i].get_z()-mov_step);
}
//Очистка холста
TRect rct;
rct = Rect(0,0,Image1->Width,Image1->Height);
Image1->Canvas->Brush->Style=bsSolid;
Image1->Canvas->FillRect(rct);
//Отрисовка
print(prism, Image1);
}
//---------------------------------------------------------------------------
void prisminit(MyPoint* o)
{ int i=0;
  o[0]=MyPoint('A',0.0,200.0,-h/2);
  o[1]=MyPoint(char('A'+1),0.0,0.0,-h/2);
  o[2]=MyPoint(char('A'+2),200.0,0,-h/2);
 for(i=3; i<6; i++)
 {
 o[i]=MyPoint(char('A'+i),o[i-3].get_x(),o[i-3].get_y(),o[i-3].get_z()+h);
 }
 }
