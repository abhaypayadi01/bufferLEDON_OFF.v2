#include "FiniteStateMachine.h"
#include <memory>
#include <iostream>
#include <conio.h>
#include <string>
#include<ctime>
using namespace std;
using namespace Patterns;
string cqueue[5];
int front = -1, rear = -1, n=5,count=0;
bool KeyPresses[255];

enum class LED
{
  OFF,
  ON,
};


class LEDOFFState : public State<LED>
{
public:
  LEDOFFState(FiniteStateMachine<LED>& fsm)
    : State<LED>(fsm,
      LED::OFF, 
      "OFF")
  {
  }

  void enter()
  {
    State<LED>::enter();
    printf("led state: off \n");
    time_t tmNow = time(0);
    string dt = ctime(&tmNow);
    dt=dt + "OFF";

    insertCQ(dt);
  }

  void update()
  {
    State<LED>::update();
    if (KeyPresses['c'])
    {
      printf(" Turning on the LED\n");
      mFsm.setCurrentState(LED::ON);
    }
    else
    {
      printf("Press c to on the LED.\n");
    }
     if (KeyPresses['d'])
    {
      displayCQ();
    }
    
  }
  void insertCQ(string val) {
   if(count>n) count=n;
   rear=(rear+1)%n;
   cqueue[rear]=val;
   count++;

}

void displayCQ() {
   int f = front, r = rear;
   cout<<"The Buffer stored is:"<<endl;
   for(int i=1;i<=count;i++){
      cout<<cqueue[f]<<endl;
      f=(f+1)%n;
   }
}
}; 

class LEDONState : public State<LED>
{
public:
  LEDONState(FiniteStateMachine<LED>& fsm)
    : State<LED>(fsm,LED::ON, "ON")
  {
  }

  void enter()
  {
    State<LED>::enter();
    printf("LED state: ON \n");
    time_t tmNow = time(0);
    string dt = ctime(&tmNow);
    dt=dt + "ON";
    insertCQ(dt);
  }

  void update()
  {
    State<LED>::update();
    if (KeyPresses['p'])
    {
      printf(" Press p to off LED\n");
      mFsm.setCurrentState(LED::OFF);
    }
    if (KeyPresses['d'])
    {
      displayCQ();
    }

  }
 void insertCQ(string val) {
   if(count>n) count=n;
   rear=(rear+1)%n;
   cqueue[rear]=val;
   count++;

}

void displayCQ() {
   int f = front, r = rear;
   cout<<"The buffer stored is:"<<endl;
   for(int i=1;i<=count;i++){
      cout<<cqueue[f]<<endl;
      f=(f+1)%n;
   }
}

};

int main(int argc, char* argv)
{
  

  std::unique_ptr<FiniteStateMachine<LED>> fsm = std::make_unique<FiniteStateMachine<LED>>();

  State<LED>& state_off = fsm->add<LEDOFFState>(LED::OFF);
  State<LED>& state_on = fsm->add<LEDONState>(LED::ON);

  fsm->setCurrentState(LED::OFF);

  bool done = false;
  while (!done)
  {
    char input = _getch();
    KeyPresses[input] = true;
    if (KeyPresses['q'])
    {
      done = true;
      break;
    }

    fsm->update();

    for (int i = 0; i < 255; ++i)
      KeyPresses[i] = false;
  }
  printf("You have exited the fsm\n");
}