//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPenguinHockey *PenguinHockey;
int verticalMove=-6;
int horizontalMove=-5;
int remainingTime=100;

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
LabelTime->Caption="REMAINING TIME: "+ IntToStr(remainingTime/600)+":"
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
   ball->Top>= playerTarget->Top-15 &&
   ball->Top<= playerTarget->Top &&
   ball->Left  >= playerTarget->Left &&
   ball->Left +ball->Width <= playerTarget->Left+playerTarget->Width)
   {
    ballMove->Enabled=false;
    opponentGoals+=1;
    LabelOpponentGoals->Caption=opponentGoals;
    ball->Visible=false;
    playerTargetGoal->Visible=true;
    LabelGoal->Visible=true;
    Application->ProcessMessages(); Sleep(800);
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
   ball->Top >= opponentTarget->Top+15 &&
   ball->Top<= opponentTarget->Top+30 &&
   ball->Left  >= opponentTarget->Left &&
   ball->Left +ball->Width <= opponentTarget->Left+opponentTarget->Width )
   {
    ballMove->Enabled=false;
    playerGoals+=1;
    LabelPlayerGoals->Caption=playerGoals;
    ball->Visible=false;
    opponentTargetGoal->Visible=true;
    LabelGoal->Visible=true;
    Application->ProcessMessages(); Sleep(800);
    opponentTargetGoal->Visible=false;
    LabelGoal->Visible=false;
        ball->Left=100;     ball->Top=400;
        int verticalMove=-6;    int horizontalMove=6;
        ball->Visible=true;
        ballMove->Enabled=true;
   }


   //CONTACT WITH SIDE PARTS OF TARGETS
   if   (ball->Top + ball->Height >opponentTarget->Top &&
        ball->Top < opponentTarget->Top+opponentTarget->Height &&
        (ball->Left+ball->Width >  opponentTarget->Left &&
        ball->Left+ball->Width <  opponentTarget->Left+6  ||
        ball->Left <  opponentTarget->Left+opponentTarget->Width &&
        ball->Left >  opponentTarget->Left+opponentTarget->Width-6 ))
        {
         horizontalMove=-horizontalMove;
        }
        if (ball->Top + ball->Height >playerTarget->Top &&
        ball->Top < playerTarget->Top+playerTarget->Height &&
        (ball->Left+ball->Width >  playerTarget->Left &&
        ball->Left+ball->Width <  playerTarget->Left+6  ||
        ball->Left <  playerTarget->Left+playerTarget->Width &&
        ball->Left >  playerTarget->Left+playerTarget->Width-6 ))
        {
         horizontalMove=-horizontalMove;
        }

      //CONTACTS WITH PLAYERS AND TARGETS
   else
   {
   if (verticalMove>0)
   {
        if (ball->Left >player->Left-ball->Width/2 &&
        ball->Left <player->Left+player->Width &&
        ball->Top+ball->Height >  player->Top &&
        ball->Top+ball->Height <  player->Top+6)
        {
        verticalMove=- verticalMove;
        }
        else if (ball->Left >opponentTarget->Left-ball->Width/2 &&
        ball->Left <opponentTarget->Left+opponentTarget->Width &&
        ball->Top+ball->Height >  opponentTarget->Top &&
        ball->Top+ball->Height <  opponentTarget->Top+6)
        {
        verticalMove=- verticalMove;
        }
        else if (ball->Top + ball->Height >player->Top &&
        ball->Top < player->Top+player->Height &&
        (ball->Left+ball->Width >  player->Left &&
        ball->Left+ball->Width <  player->Left+15  ||
        ball->Left <  player->Left+player->Width &&
        ball->Left >  player->Left+player->Width-6 ))
        {
         horizontalMove=-horizontalMove;
         verticalMove=-4;
        }
        else if (ball->Top + ball->Height >opponent->Top &&
        ball->Top < opponent->Top+opponent->Height &&
        (ball->Left+ball->Width >  opponent->Left &&
        ball->Left+ball->Width <  opponent->Left+15  ||
        ball->Left <  opponent->Left+opponent->Width &&
        ball->Left >  opponent->Left+opponent->Width-6 ))
        {
         horizontalMove=-horizontalMove;
         verticalMove=4;
        }
   }
   else if (verticalMove<0)
    {
        {
        if (ball->Left >opponent->Left-ball->Width/2 &&
        ball->Left <opponent->Left+opponent->Width &&
        ball->Top <  opponent->Top+opponent->Height &&
        ball->Top >  opponent->Top+opponent->Height-6)
        {
        verticalMove=- verticalMove;
        }
        else if (ball->Left >playerTarget->Left-ball->Width/2 &&
        ball->Left <playerTarget->Left+playerTarget->Width &&
        ball->Top <  playerTarget->Top+playerTarget->Height &&
        ball->Top >  playerTarget->Top+playerTarget->Height-6)
        {
        verticalMove=- verticalMove;
        }
        else if (ball->Left >player->Left-ball->Width/2 &&
        ball->Left <player->Left+player->Width &&
        ball->Top <  player->Top+player->Height &&
        ball->Top >  player->Top+player->Height-6)
        {
        verticalMove=- verticalMove;
        }
        else if (ball->Top + ball->Height >player->Top &&
        ball->Top < player->Top+player->Height &&
        (ball->Left+ball->Width >  player->Left &&
        ball->Left+ball->Width <  player->Left+6  ||
        ball->Left <  player->Left+player->Width &&
        ball->Left >  player->Left+player->Width-6 ))
        {
         horizontalMove=-horizontalMove;
         verticalMove=-verticalMove;
        }
        else if (ball->Top + ball->Height >opponent->Top &&
        ball->Top < opponent->Top+opponent->Height &&
        (ball->Left+ball->Width >  opponent->Left &&
        ball->Left+ball->Width <  opponent->Left+15  ||
        ball->Left <  opponent->Left+opponent->Width &&
        ball->Left >  opponent->Left+opponent->Width-15 ))
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
        player->Visible=false;
        opponent->Visible=false;

    }
    }
    }
}

//---------------------------------------------------------------------------



void __fastcall TPenguinHockey::playerLeftMoveTimer(TObject *Sender)
{
if (player->Left>10)    player->Left-=10;
}
//---------------------------------------------------------------------------

void __fastcall TPenguinHockey::playerRightMoveTimer(TObject *Sender)
{
if (player->Left+player->Width<background->Width-10)    player->Left+=10;
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
 if (opponent->Left+opponent->Width > background->Width-280) opponent->Left-=3;
 else opponentDirection='R';
}
//---------------------------------------------------------------------------


void __fastcall TPenguinHockey::opponentRightMoveTimer(TObject *Sender)
{
 if (opponent->Left+opponent->Width < background->Width-190) opponent->Left+=3;
 else  opponentDirection='L';
}
//---------------------------------------------------------------------------


void __fastcall TPenguinHockey::FormActivate(TObject *Sender)
{
        LabelTime->Caption=remainingTime;
        opponentRightMove->Enabled=true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




