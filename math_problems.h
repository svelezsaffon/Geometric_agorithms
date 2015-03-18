//
// Created by santiago on 3/18/15.
//

#include <cstdio> //for printf
#include <cmath>

#ifndef _OTHER_STUDY_EIGHT_OF_CIRCLE_H_
#define _OTHER_STUDY_EIGHT_OF_CIRCLE_H_

#define COLINEAR 0
#define COUNTER_CLOCKWISE 1
#define CLOCKWISE 2

#define MAX(A,B) (A>B? A:B)
#define MIN(A,B) (A>B? B:A)




/*
* The following problem tries to draw 1/8 of a circle
*
* The circle is centerd at (0,0)
*/


void set_pixel(int xcoor,int ycoor){
    printf("(%d,%d)\n",xcoor,ycoor);
}


void drawEightOfCircle(int radious){


    int x=0;
    int y=radious;
    int r2=radious*radious;
    while(y>=x){
        y=sqrt(r2-(x*x))+0.5;
        set_pixel(x,y);
        x++;
    }

}



/*
* This problems solves if two rectagles overlap
*/

class point{
private :

    int x;
    int y;

public:

    point(int x,int y){
        point::x=x;
        point::y=y;
    }

    point(){

    }

    void copy(point c){
        point::x=c.getX();
        point::y=c.getY();
    }


    int getX() const {
        return x;
    }

    void setX(int x) {
        point::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        point::y = y;
    }


};

bool line_overlap(point a,int l1 , point b,int l2){

    point left(0,0);
    point right(0,0);
    int l;


    if(a.getX() < b.getX()){
        left.copy(a);
        l=l1;
        right.copy(b);

    }else{
        left.copy(b);
        right.copy(a);
        l=l2;
    }

    if(left.getX()+l >=right.getX()){
        return true;
    }

    return false;
}




int orientation(point a, point b, point c){

    int ls=(b.getY()-a.getY())*(c.getX()-b.getX());
    int rs=(c.getY()-b.getY())*(b.getX()-a.getX());
    int res=ls-rs;

    if(res==0){
        return COLINEAR;
    }if(res>0){
        return CLOCKWISE;
    }else{
        return COUNTER_CLOCKWISE;
    }


}


//checks if point b is between a and c
bool point_between(point a,point b, point c){

    if(b.getX()<=MAX(a.getX(),c.getX()) &&
            b.getX() >= MIN(a.getX(),c.getX()) &&
            b.getY() <= MAX(a.getY(),b.getY()) &&
            b.getY() >= MIN(a.getY(),c.getY())   ){
        return true;
    }


    return false;
}




class line{
private:
    point head;
    point tail;

public:


    line(point const &head, point const &tail) : head(head), tail(tail) {
    }

    point const &getHead() const {
        return head;
    }

    void setHead(point const &head) {
        line::head = head;
    }

    point const &getTail() const {
        return tail;
    }

    void setTail(point const &tail) {
        line::tail = tail;
    }


    bool intersect(line b){


        int hth1=orientation(line::head,line::tail,b.getHead());
        int htt1=orientation(line::head,line::tail,b.getTail());
        int hth2=orientation(b.getHead(),b.getTail(),line::head);
        int htt2=orientation(b.getHead(),b.getTail(),line::tail);

        printf("hth1=%d\n",hth1);
        printf("htt2=%d\n",htt1);
        printf("hth2=%d\n",hth2);
        printf("htt2=%d\n",htt2);


        if(hth1!=htt1 && hth2!=htt2){
            return true;
        }

        if(hth1==COLINEAR){
            if(point_between(line::head,b.getHead(),line::tail)){
                return true;
            }
        }

        if(htt1==COLINEAR){
            if(point_between(line::head,b.getTail(),line::tail)){
                return true;
            }
        }

        if(hth2==COLINEAR){
            if(point_between(b.getHead(),line::head,b.getTail())){
                return true;
            }
        }

        if(htt2==COLINEAR){
            if(point_between(b.getHead(),line::tail,b.getTail())){
                return true;
            }
        }



        return false;
    }


};

class rectangle{
public:

    point ul;
    point lr;

    rectangle(point lu,point rl){
        rectangle::ul.setX(lu.getX());
        rectangle::ul.setY(lu.getY());

        rectangle::lr.setX(rl.getX());
        rectangle::lr.setY(rl.getY());
    }

    int get_width(){
        return rectangle::lr.getX()-rectangle::ul.getX();
    }

    int get_height(){
        return rectangle::ul.getY()-rectangle::lr.getY();
    }

    bool overlap(rectangle b){
        bool ret;


        //checking horizontally
        ret=line_overlap(rectangle::ul,rectangle::get_width(),b.ul,b.get_width());

        //checking vertically

        point auxa(rectangle::ul.getX(),rectangle::ul.getY()-rectangle::get_height());
        point auxb(b.ul.getX(),b.ul.getY()-b.get_height());

        auxa.setX(auxa.getY());
        auxa.setY(auxa.getX());

        auxb.setX(auxb.getY());
        auxb.setY(auxb.getX());


        ret=ret && line_overlap(auxa,rectangle::get_height(),auxb,b.get_height());




        return ret;
    }

};



#endif //_OTHER_STUDY_EIGHT_OF_CIRCLE_H_
