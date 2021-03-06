/*
 * timer.h
 *
 *  Created on: 26/08/2020
 *      Author: Ruth Solis Velasco - A01703206
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <string>
#include <sstream>
using namespace std;

class Timer {
private:
	int hours, minutes;

public:
	Timer();
	Timer(int, int);
	Timer(const Timer&);

	int getHours() const;
	int getMinutes() const;
	std::string toString() const;

	void operator= (const Timer&);
	void operator+= (const Timer&);
};

Timer::Timer() : hours(0), minutes(0) {}

Timer::Timer(int hh, int mm) {
  hours = hh;
  minutes = mm;
 
  while(minutes > 59){
    
    minutes = minutes - 60;
    if (hours > 23){
      hours = 0;
    }
    hours++;
    //cout<<"\nHours: "<<hours<<endl;
    //cout<<"\nMinutes: "<<minutes<<endl;
  }

}

Timer::Timer(const Timer &t) {}

int Timer::getHours() const {
  //cout<<"Hours= "<<hours<<endl;
  return hours;
}

int Timer::getMinutes() const {
  //cout<<"Minutes= "<<minutes<<endl;
  return minutes;
}

std::string Timer::toString() const {
	 std::stringstream aux;

	 if (hours < 10) {
		 aux << "0";
	 }
	 aux << hours << ":";
	 if (minutes < 10) {
		 aux << "0";
	 }
	 aux << minutes;
	 return aux.str();
}

void Timer::operator= (const Timer &right) {
  hours = right.getHours();
  minutes= right.getMinutes();
}

void Timer::operator+= (const Timer &right) {
 
  hours  += right.getHours();
  minutes  += right.getMinutes();
 
   while(minutes > 59){
    
    minutes = minutes - 60;
    
    if (hours > 23){
      //cout<<"\nAQUI2"<<endl;
      hours = 0;
    cout<<"\nHours: "<<hours<<endl;
    cout<<"\nMinutes: "<<minutes<<endl;
    }
    hours++;

  }
     if (hours > 23){
      //cout<<"\nAQUI2"<<endl;
      hours = 0;
      hours++;
    cout<<"\nHours: "<<hours<<endl;
    cout<<"\nMinutes: "<<minutes<<endl;
    } 

}

bool operator== (const Timer &left, const Timer &right) {
  if(left.getHours() == right.getHours() && left.getMinutes() == right.getMinutes()){
    return true;
  }else{
    return false;
  }
}

bool operator> (const Timer &left, const Timer &right) {
    if(left.getHours() >= right.getHours() && left.getMinutes() >= right.getMinutes()){
    return true;
  }else{
    return false;
  }
}

#endif /* TIMER_H_ */