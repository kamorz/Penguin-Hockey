//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPenguinHockey *PenguinHockey;
int verticalMove=-6;
int horizontalMove=-6;

int playerGoals=0;
int opponentGoals=0;

//---------------------------------------------------------------------------
__fastcall TPenguinHockey::TPenguinHockey(TComponent* Owner)
        : TForm(Owner)

{
}
//---------------------------------------------------------------------------



void __fastcall TPenguinHockey::ballMoveTimer(TObject *Sender)
{
   ball->Left+=horizontalMove;
   ball->Top+=verticalMove;

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
    Application->ProcessMessages(); Sleep(800);
    playerTargetGoal->Visible=false;
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
    Application->ProcessMessages(); Sleep(800);
    opponentTargetGoal->Visible=false;
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
  opponent->Left-=3;
}
//---------------------------------------------------------------------------





void __fastcall TPenguinHockey::opponentRightMoveTimer(TObject *Sender)
{
  opponent->Left+=3;
}
//---------------------------------------------------------------------------


void __fastcall TPenguinHockey::FormActivate(TObject *Sender)
{
        while (opponent->Left>15)
  opponentLeftMove->Enabled=true;
}
//---------------------------------------------------------------------------
