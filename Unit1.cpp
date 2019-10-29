//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit1.h"
#include "Unit2.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPenguinHockey *PenguinHockey;
int verticalMove=-5;
int horizontalMove=-4;
int remainingTime=1800;

int playerGoals=0;
int opponentGoals=0;
char opponentDirection='R';


//---------------------------------------------------------------------------
__fastcall TPenguinHockey::TPenguinHockey(TComponent* Owner)
        : TForm(Owner)

{
}
//---------------------------------------------------------------------------


void __fastcall TPenguinHockey::MatchTimeTimer(TObject *Sender)
{
remainingTime-=1;
if ((remainingTime%600)/10>=10)
LabelTime->Caption="REMAINING TIME: "+ IntToStr(remainingTime/600)+":"
+IntToStr((remainingTime%600)/10);
else
LabelTime->Caption="REMAINING TIME: "+ IntToStr(remainingTime/600)+":0"
+IntToStr((remainingTime%600)/10);
if (opponentDirection=='L')
      {
       opponentLeftMove->Enabled=true;
       opponentRightMove->Enabled=false;
      }
else if (opponentDirection=='R')
        {
        opponentRightMove->Enabled=true;
        opponentLeftMove->Enabled=false;
        }
}


void __fastcall TPenguinHockey::ballMoveTimer(TObject *Sender)
{

   ball->Left+=horizontalMove;
   ball->Top+=verticalMove;

   //CONTACTS WITH WALLS
   if (ball->Left-5  <= background->Left)       horizontalMove=-horizontalMove;
   if (ball->Top-5   <= background->Top)        verticalMove=-verticalMove;
   if (ball->Left +ball->Width+5 >= background->Width) horizontalMove=-horizontalMove;
   if (ball->Top+ ball->Height>= background->Top+background->Height)    verticalMove=-verticalMove;


   //OPPONENT GOAL
   if (
   verticalMove>=0 &&
   ball->Top>= playerTarget->Top-30 &&
   ball->Top<= playerTarget->Top+5 &&
   ball->Left  >= playerTarget->Left-5 &&
   ball->Left +ball->Width <= playerTarget->Left+playerTarget->Width+5)
   {
    ballMove->Enabled=false;
    opponentGoals+=1;
    LabelOpponentGoals->Caption=opponentGoals;
    ball->Visible=false;
    playerTargetGoal->Visible=true;
    LabelGoal->Visible=true;
    Application->ProcessMessages(); Sleep(1200);
    playerTargetGoal->Visible=false;
    LabelGoal->Visible=false;
        ball->Left=100;     ball->Top=200;
        int verticalMove=6;    int horizontalMove=6;
        ball->Visible=true;
        ballMove->Enabled=true;
   }

   //PLAYER GOAL
   if (
   verticalMove<=0 &&
   ball->Top >= opponentTarget->Top-10 &&
   ball->Top<= opponentTarget->Top+opponentTarget->Height+5 &&
   ball->Left  >= opponentTarget->Left-5 &&
   ball->Left +ball->Width <= opponentTarget->Left+opponentTarget->Width+5 )
   {
    ballMove->Enabled=false;
    playerGoals+=1;
    LabelPlayerGoals->Caption=playerGoals;
    ball->Visible=false;
    opponentTargetGoal->Visible=true;
    LabelGoal->Visible=true;
    Application->ProcessMessages(); Sleep(1200);
    opponentTargetGoal->Visible=false;
    LabelGoal->Visible=false;
        ball->Left=200;     ball->Top=400;
        int verticalMove=-6;    int horizontalMove=6;
        ball->Visible=true;
        ballMove->Enabled=true;
   }


   //CONTACT WITH SIDE PARTS OF TARGETS
        if   (ball->Top + ball->Height >opponentTarget->Top &&
        ball->Top < opponentTarget->Top+opponentTarget->Height &&
        (ball->Left+ball->Width >  opponentTarget->Left-6 &&
        ball->Left+ball->Width <  opponentTarget->Left  ||
        ball->Left <  opponentTarget->Left+opponentTarget->Width+6 &&
        ball->Left >  opponentTarget->Left+opponentTarget->Width ))
        {
         horizontalMove=-horizontalMove;
        }
        else if (ball->Top + ball->Height >playerTarget->Top &&
        ball->Top < playerTarget->Top+playerTarget->Height &&
        (ball->Left+ball->Width >  playerTarget->Left-6 &&
        ball->Left+ball->Width <  playerTarget->Left  ||
        ball->Left <  playerTarget->Left+playerTarget->Width+6 &&
        ball->Left >  playerTarget->Left+playerTarget->Width ))
        {
         horizontalMove=-horizontalMove;
        }

      //CONTACTS WITH PLAYERS AND TARGETS DURING BALL TOWARDS DOWN
   else
   {
   if (verticalMove>0)
   {    //WITH PLAYER
        if (ball->Left >player->Left-ball->Width &&
        ball->Left <player->Left+player->Width+ball->Width &&
        ball->Top+ball->Height >  player->Top &&
        ball->Top+ball->Height <  player->Top+6)
        {
                if (ball->Left+ball->Width/2<player->Left+8)
                {
                verticalMove=-4;
                horizontalMove=-5;
                }
                else if (ball->Left+ball->Width/2>=player->Left+8 &&
                ball->Left+ball->Width/2<player->Left+17)
                {
                verticalMove=-6;
                horizontalMove=-2;
                }
                else if(ball->Left+ball->Width/2>=player->Left+17 &&
                ball->Left+ball->Width/2<player->Left+25)
                {
                verticalMove=-6;
                horizontalMove=2;
                }
                else if (ball->Left+ball->Width/2>=player->Left+25)
                {
                verticalMove=-4;
                horizontalMove=5;
                }
        }  //WITH OPPONENT TARGET
        else if (ball->Left+ball->Width >=opponentTarget->Left &&
        ball->Left <=opponentTarget->Left+opponentTarget->Width &&
        ball->Top+ball->Height >  opponentTarget->Top-6 &&
        ball->Top+ball->Height <  opponentTarget->Top)
        {
        verticalMove=- verticalMove;
        }     //WITH PLAYER SIDE
        else if (ball->Top +ball->Height > player->Top &&
        ball->Top < player->Top+player->Height &&
        (ball->Left+ball->Width >  player->Left-6 &&
        ball->Left+ball->Width <  player->Left+15  ||
        ball->Left <  player->Left+player->Width-15 &&
        ball->Left >  player->Left+player->Width+6 ))
        {
         horizontalMove=-horizontalMove;
         verticalMove=-verticalMove;
        }     //WITH OPPONENT SIDE
        else if (ball->Top + ball->Height >opponent->Top &&
        ball->Top < opponent->Top+opponent->Height &&
        (ball->Left+ball->Width >  opponent->Left-6 &&
        ball->Left+ball->Width <  opponent->Left+20  ||
        ball->Left <  opponent->Left+opponent->Width-20 &&
        ball->Left >  opponent->Left+opponent->Width+6 ))
        {
         horizontalMove=-horizontalMove;
        }
           //CONTACT WITH CORNER PARTS OF OPPONENT TARGET
        else if   (ball->Top + ball->Height >opponentTarget->Top-6 &&
        ball->Top <= opponentTarget->Top &&
        (ball->Left+ball->Width >  opponentTarget->Left-6 &&
        ball->Left+ball->Width <  opponentTarget->Left && horizontalMove>0 ||
        ball->Left <  opponentTarget->Left+opponentTarget->Width+6 &&
        ball->Left >  opponentTarget->Left+opponentTarget->Width && horizontalMove<0))
        {
         horizontalMove=-horizontalMove;
         verticalMove=-verticalMove;
        }
   }
   else if (verticalMove<0)   //DURING BALL TOWARDS UP
    {
        {     // WITH OPPONENT
        if (ball->Left >opponent->Left-ball->Width/2 &&
        ball->Left <opponent->Left+opponent->Width &&
        ball->Top <  opponent->Top+opponent->Height &&
        ball->Top >  opponent->Top+opponent->Height-6)
        {
                if (ball->Left+ball->Width/2<opponent->Left+20)
                {
                verticalMove=4;
                horizontalMove=-6;
                }
                else if(ball->Left+ball->Width/2>=opponent->Left+21 &&
                ball->Left+ball->Width/2<opponent->Left+30)
                {
                verticalMove=-6;
                horizontalMove=2;
                }
                else if (ball->Left+ball->Width/2>=opponent->Left+31)
                {
                verticalMove=4;
                horizontalMove=6;
                }
        }     //WITH PLAYER TARGET
        else if (ball->Left+ball->Width >=playerTarget->Left &&
        ball->Left <=playerTarget->Left+playerTarget->Width &&
        ball->Top <  playerTarget->Top+playerTarget->Height+6 &&
        ball->Top >  playerTarget->Top+playerTarget->Height)
        {
        verticalMove=- verticalMove;
        }     //WITH PLAYER
        else if (ball->Left >player->Left-ball->Width/2 &&
        ball->Left <player->Left+player->Width &&
        ball->Top <  player->Top+player->Height &&
        ball->Top >  player->Top+player->Height-6)
        {
        verticalMove=- verticalMove;
        }       //WITH PLAYER SIDE
        else if (ball->Top + ball->Height >player->Top &&
        ball->Top < player->Top+player->Height &&
        (ball->Left+ball->Width >  player->Left-6 &&
        ball->Left+ball->Width <  player->Left+15  ||
        ball->Left <  player->Left+player->Width-15 &&
        ball->Left >  player->Left+player->Width+6 ))
        {
         horizontalMove=-horizontalMove;
        }      //WITH OPPONENT SIDE
        else if (ball->Top + ball->Height >opponent->Top &&
        ball->Top < opponent->Top+opponent->Height &&
        (ball->Left+ball->Width >  opponent->Left-6 &&
        ball->Left+ball->Width <  opponent->Left+20  ||
        ball->Left <  opponent->Left+opponent->Width+6 &&
        ball->Left >  opponent->Left+opponent->Width-20 ))
        {
         horizontalMove=-horizontalMove;
         verticalMove=-verticalMove;
        }       //WITH CORNER PARTS OF PLAYER TARGET
        else if (ball->Top >=playerTarget->Top+playerTarget->Height &&
        ball->Top < playerTarget->Top+playerTarget->Height+6 &&
        (ball->Left+ball->Width >  playerTarget->Left-6 &&
        ball->Left+ball->Width <  playerTarget->Left && horizontalMove>0 ||
        ball->Left <  playerTarget->Left+playerTarget->Width+6 &&
        ball->Left >  playerTarget->Left+playerTarget->Width && horizontalMove<0))
        {
         horizontalMove=-horizontalMove;
         verticalMove=-verticalMove;
        }
    }
    //TIME OVER
    if (remainingTime<=0)
    {
     LabelGoal->Caption="Final result: "+IntToStr(playerGoals)+":"+IntToStr(opponentGoals);
     LabelGoal->Visible=true;
        ball->Visible=false;
        ballMove->Enabled=false;
        MatchTime->Enabled=false;
        LabelTime->Visible=false;

        if (playerGoals>opponentGoals)
        LabelFinal->Caption="YOU WON!";
        else if (playerGoals<opponentGoals)
        LabelFinal->Caption="YOU LOSE!";
        else if (playerGoals==opponentGoals)
        LabelFinal->Caption="IT'S A DRAW!";

        LabelFinal->Visible=true;
        Application->ProcessMessages(); Sleep(1500);
        startPicture->Visible=true;
        Button1->Visible=true;
        Button2->Visible=true;
        opponentRightMove->Enabled=false;
        remainingTime=1800;
        int playerGoals=0;
        int opponentGoals=0;
    }
    }
    }
}

//---------------------------------------------------------------------------



void __fastcall TPenguinHockey::playerLeftMoveTimer(TObject *Sender)
{
if (player->Left>40)    player->Left-=10;
}
//---------------------------------------------------------------------------

void __fastcall TPenguinHockey::playerRightMoveTimer(TObject *Sender)
{
if (player->Left+player->Width<background->Width-40)    player->Left+=10;
}
//---------------------------------------------------------------------------

void __fastcall TPenguinHockey::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key==VK_LEFT)        playerLeftMove->Enabled=true;
if (Key==VK_RIGHT)       playerRightMove->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TPenguinHockey::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key==VK_LEFT)        playerLeftMove->Enabled=false;
if (Key==VK_RIGHT)       playerRightMove->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TPenguinHockey::opponentLeftMoveTimer(TObject *Sender)
{
 if (opponent->Left+opponent->Width > background->Width-280) opponent->Left-=4;
 else opponentDirection='R';
}
//---------------------------------------------------------------------------


void __fastcall TPenguinHockey::opponentRightMoveTimer(TObject *Sender)
{
 if (opponent->Left+opponent->Width < background->Width-160) opponent->Left+=4;
 else  opponentDirection='L';
}
//---------------------------------------------------------------------------


void __fastcall TPenguinHockey::FormActivate(TObject *Sender)
{
        LabelTime->Caption=remainingTime;

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




void __fastcall TPenguinHockey::Button1Click(TObject *Sender)
{
 startPicture->Visible=false;
 Button1->Visible=false;
 Button2->Visible=false;
 LabelFinal->Visible=false;
 ballMove->Enabled=true;
 ball->Visible=true;
 MatchTime->Enabled=true;
 LabelTime->Caption=remainingTime;
 opponentRightMove->Enabled=true;
 LabelGoal->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TPenguinHockey::Button3Click(TObject *Sender)
{
Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TPenguinHockey::Button2Click(TObject *Sender)
{
 Rules->ShowModal();
}
//---------------------------------------------------------------------------

