#include "okno.h"

#include <QMouseEvent>
#include <QPainter>
#include <stack>
#include <vector>

Okno::Okno(QWidget *parent) : QWidget(parent)
{
    im = QImage(900,500,QImage::Format_RGB32);

        im.fill(Qt::black);
        x=0;
        y=0;



}

void Okno::paintEvent(QPaintEvent *)
{
    QPainter p(this);


    p.drawImage(0,0,im);
}

void Okno::mousePressEvent(QMouseEvent *ev)
{
    Point z;

    z.x=ev->x();
    z.y=ev->y();

    p.push_back(z);

    drawDot(z.x,z.y,255,255,255);
    update();

    /*
    if(opcja==1)
    {
        x=ev->x();
        y=ev->y();
    }
    else if(opcja ==2)
    {
       uchar *buf;
       buf = im.scanLine(ev->y());
       bb=buf[ev->x()*4];
       gg=buf[ev->x()*4+1];
       rr= buf[ev->x()*4+2];

       fill(ev->x(),ev->y(),rr,gg,bb,255,255,255);


    }
*/

}

void Okno::mouseMoveEvent(QMouseEvent *ev)
{

}

void Okno::mouseReleaseEvent(QMouseEvent *ev)
{
    /*
    if(opcja==1)
    {
        drawLine(x,y,ev->x(),ev->y(),255,255,255);
    }


    update();
    */
}

void Okno::rysuj()
{
    opcja =1;
}

void Okno::wypelniaj()
{
    scan_line(p,255,255,255);
    update();
}

void Okno::drawDot(int x, int y, int r, int g, int b)
{
    if(x>=0 && x<im.width() && y>=0 && y<im.height())
    {
         uchar *buf= im.scanLine(y);

        buf[4*x]=b;
        buf[4*x+1]=g;
        buf[4*x+2]=r;

    }
}

void Okno::scan_line(std::vector<Okno::Point> p, int r, int g, int bb)
{
    float y_min=p[0].y;
    float y_max=p[0].y;


    for(int i=0;i<p.size();i++)
    {
        if(p[i].y<y_min)
        {
            y_min=p[i].y;
        }

        if(p[i].y>y_max)
        {
            y_max=p[i].y;
        }
    }


    for(int y=y_min;y<y_max;y++)
    {

         std::vector<float> tab;
          Point a,b;
          int x;

        for(int i=0;i<p.size()-1;i++)
        {
            a=p[i];
            b=p[i+1];

            if((y<=a.y && y>b.y) ||(y<=b.y && y>a.y))
                if(b.y!=a.y)
                {
                    x = a.x+((y-a.y)/(b.y-a.y))*(b.x-a.x);
                    /*
                    Point k;
                    k.x=x;
                    k.y=y;
                    bool is =1;

                    for(int j=0;j<p.size();j++)
                    {
                        if(k.x==p[j].x && k.y==p[j].y)
                        {
                            is=0;
                        }
                    }

                    if(is==1)
                    */
                    tab.push_back(x);
                }
        }

        a=p[p.size()-1];
        b=p[0];
        if((y<=a.y && y>b.y) ||(y<=b.y && y>a.y))
            if(b.y!=a.y)
            {
                x = a.x+((y-a.y)/(b.y-a.y))*(b.x-a.x);
               /*
                Point k;
                k.x=x;
                k.y=y;
                bool is =1;

                for(int j=0;j<p.size();j++)
                {
                    if(k.x==p[j].x && k.y==p[j].y)
                    {
                        is=0;
                    }
                }

                if(is==1)
                */
                tab.push_back(x);
            }




        sort(tab.begin(),tab.end());

        for(int i=0;i<tab.size();i++)
        {
            if(i%2==0)
            {
                drawLine(tab[i],(float)y,tab[i+1],(float)y,r,g,bb);
            }

        }













    }

}


void Okno::drawLine(float x1, float y1, float x2, float y2, int r, int g, int b)
{


        float a,N;
        int x,y;

        uchar *buf ;




        if(abs(x2-x1) >=abs(y2-y1))
        {

            if(x1<x2)
            {


                for(x=x1;x<=x2;x++)
                {

                        y=(y2-y1)*(x-x1)/(x2-x1)+y1;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }else
            {
                for(x=x2;x<=x1;x++)
                {

                        y=(y1-y2)*(x-x2)/(x1-x2)+y2;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }


        }else
        {
            if(y1<y2)
            {


                for(y=y1;y<=y2;y++)
                {

                        x=(x2-x1)*(y-y1)/(y2-y1)+x1;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }else
            {
                for(y=y2;y<=y1;y++)
                {

                        x=(x1-x2)*(y-y2)/(y1-y2)+x2;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }

        }
}

void Okno::fill(float x1, float y1, int r1, int g1, int b1, int r2, int g2, int b2)
{
    if(r1==r2, g1==g2, b1==b2)
    {

    }else
    {
        Point p,b;
        uchar *buf;

        p.x = x1;
        p.y = y1;

        std::stack<Point> stos;

        stos.push(p);

        while(!stos.empty())
        {
            b= stos.top();
            stos.pop();

            if(b.x>=0 && b.x<im.width() && b.y >= 0 && b.y <im.height())
            {
                buf = im.scanLine(b.y);
                if(buf[(int)b.x*4]==b1 && buf[(int)b.x*4+1]==g1 && buf[(int)b.x*4+2]==r1)
                {

                    buf[(int)b.x*4]=b2;
                    buf[(int)b.x*4+1]=g2;
                    buf[(int)b.x*4+2]=r2;

                    p.x=b.x-1;
                    p.y=b.y;
                    stos.push(p);
                    p.x=b.x+1;
                    p.y=b.y;
                    stos.push(p);
                    p.x=b.x;
                    p.y=b.y+1;
                    stos.push(p);
                    p.x=b.x;
                    p.y=b.y-1;
                    stos.push(p);

                }

            }

        }
    }


}
