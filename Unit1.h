//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TPenguinHockey : public TForm
{
__published:	// IDE-managed Components
        TShape *background;
        TImage *opponentTarget;
        TImage *playerTarget;
        TImage *player;
        TImage *opponent;
        TImage *ball;
        TTimer *ballMove;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *LabelPlayerGoals;
        TLabel *LabelOpponentGoals;
        TTimer *playerLeftMove;
        TImage *playerTargetGoal;
        TImage *opponentTargetGoal;
        TTimer *playerRightMove;
        TTimer *opponentLeftMove;
        TTimer *opponentRightMove;
        TLabel *LabelTime;
        TTimer *MatchTime;
        TLabel *LabelGoal;
        TLabel *LabelFinal;
        TImage *startPicture;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        void __fastcall ballMoveTimer(TObject *Sender);
        void __fastcall playerLeftMoveTimer(TObject *Sender);
        void __fastcall playerRightMoveTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall opponentLeftMoveTimer(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall opponentRightMoveTimer(TObject *Sender);
        void __fastcall MatchTimeTimer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPenguinHockey(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPenguinHockey *PenguinHockey;
//---------------------------------------------------------------------------
#endif
