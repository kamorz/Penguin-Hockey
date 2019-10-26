//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPenguinHockey *PenguinHockey;
int verticalMove=6;
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
    Label5->Caption=playerGoals;
    ball->Visible=false;

   }

   }
//---------------------------------------------------------------------------



