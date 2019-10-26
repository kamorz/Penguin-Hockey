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
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TTimer *playerMove;
        void __fastcall ballMoveTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPenguinHockey(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPenguinHockey *PenguinHockey;
//---------------------------------------------------------------------------
#endif
