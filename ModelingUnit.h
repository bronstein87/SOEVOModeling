//---------------------------------------------------------------------------

#ifndef ModelingUnitH
#define ModelingUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "Chart.hpp"
#include <Dialogs.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "VCLTee.ArrowCha.hpp"
#include "VCLTee.BubbleCh.hpp"
#include "VCLTee.GanttCh.hpp"
#include "VCLTee.TeeShape.hpp"
#include <VclTee.TeeGDIPlus.hpp>
#include "VCLTee.TeeTools.hpp"
#include "VCLTee.TeeEdit.hpp"
#include "VCLTee.ErrorBar.hpp"
#include "VCLTee.TeeHighLowLine.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.EngExt.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.SysUtils.hpp>
#include <System.Rtti.hpp>
#include <Vcl.Bind.DBEngExt.hpp>
#include <Vcl.Bind.Editors.hpp>
#include <memory>
#include <string>
//---------------------------------------------------------------------------

const int MaxPoint = 3000;
double const pi = 3.1415926535897932384626433832795;
const int MaxDist = 10;
using namespace std;

struct OffsetAngles
{
	OffsetAngles():  alphaOneOY(0), alphaOneOX(0),
	 alphaTwoOY(0), alphaTwoOX(0),
	 lambdaOY(0),lambdaOX(0),
	 gammaOY(0), gammaOX(0),
	 SKOGammaOZ(0)
	 {}

	double alphaOneOY;
	double alphaOneOX;
	double alphaTwoOY;
	double alphaTwoOX;
	double lambdaOY;
	double lambdaOX;
	double gammaOY;
	double gammaOX;
	double SKOGammaOZ;
};

struct VectorCos
{
   double** Lst;
   double** Mst;
   double** Nst;
	VectorCos()
	{
		Lst = new double* [MaxPoint];
		Mst = new double* [MaxPoint];
		Nst = new double* [MaxPoint];
		for (int i = 0; i < MaxPoint; i++)
		{
			Lst[i] = new double [MaxPoint];
			Mst[i] = new double [MaxPoint];
			Nst[i] = new double [MaxPoint];
		}
	}

   ~VectorCos()
   {
		for(int i = 0; i < MaxPoint; i++)
		{
			delete[] Lst[i];
			delete[] Mst[i];
			delete[] Nst[i];
		}
		delete[] Lst;
		delete[] Mst;
		delete[] Nst;

   }
};

struct XYCoords
{
	double** X;
	double** Y;

	XYCoords()
	{
		X = new double* [MaxPoint];
		Y = new double* [MaxPoint];
		for (int i = 0; i < MaxPoint; i++) {
			X[i] = new double [MaxPoint];
			Y[i] = new double [MaxPoint];
		}
	}

   ~XYCoords()
   {
		for(int i = 0; i < MaxPoint; i++)
		{
			delete[] X[i];
			delete[] Y[i];
		}
		delete[] X;
		delete[] Y;
   }

};

struct AdditionalPointsOffset
{
	AdditionalPointsOffset():
	 firstPointOffsetX(0),
	firstPointOffsetY(0),
	 secondPointOffsetX(0),
	 secondPointOffsetY(0)
	 {}
   double	firstPointOffsetX;
   double   firstPointOffsetY;
   double	secondPointOffsetX;
   double	secondPointOffsetY;
};

struct SimulateCatalogData
{
	vector <double> alpha;
	vector <double> delta;
};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *ButtonClose;
	TButton *ButtonSimulate;
	TLabel *Label2;
	TEdit *L;
	TEdit *M;
	TEdit *N;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TChart *Chart1;
	TPointSeries *Series1;
	TCheckBox *CheckBoxCoordError;
	TEdit *EditCoordError;
	TLabel *Label22;
	TLabel *Label23;
	TArrowSeries *Series2;
	TCheckBox *CheckBoxAngleError;
	TEdit *EditAngleErrorOZ;
	TLabel *Label24;
	TLabel *Label25;
	TEdit *EditAngleErrorOX;
	TLabel *Label26;
	TLabel *Label27;
	TEdit *EditScale;
	TLabel *Label28;
	TCheckBox *CheckBoxEqualNet;
	TCheckBox *CheckBoxModelCentre;
	TEdit *EditCentrePoint;
	TLabel *Label29;
	TEdit *EditPercent;
	TLabel *Label30;
	TLabel *Label31;
	TCheckBox *CheckBoxDist;
	TEdit *EditFileDist;
	TButton *ButtonOpenDist;
	TOpenDialog *OpenDialogDist;
	TLabel *Label32;
	TEdit *EditAlpha1OY;
	TLabel *Label33;
	TLabel *Label34;
	TEdit *EditAlpha1OX;
	TLabel *Label36;
	TLabel *Label37;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TEdit *EditAlpha2OY;
	TLabel *Label40;
	TEdit *EditGammaOY;
	TLabel *Label42;
	TLabel *Label44;
	TEdit *EditLambdaOY;
	TLabel *Label46;
	TGroupBox *GroupBox3;
	TEdit *EditAlpha2OX;
	TEdit *EditGammaOX;
	TEdit *EditLambdaOX;
	TLabel *Label48;
	TLabel *Label49;
	TLabel *Label50;
	TLabel *Label51;
	TLabel *Label52;
	TLabel *Label53;
	TLabel *Label54;
	TGroupBox *GroupBox4;
	TRadioButton *UpRadioButton;
	TRadioButton *DownRadioButton;
	TRadioButton *LeftRadioButton;
	TRadioButton *RightRadioButton;
	TGroupBox *GroupBox5;
	TEdit *EditFoc;
	TLabel *Label17;
	TLabel *Label8;
	TEdit *EditElem;
	TLabel *Label9;
	TLabel *Label4;
	TEdit *EditWidth;
	TLabel *Label7;
	TEdit *EditHeight;
	TLabel *Label10;
	TLabel *Label5;
	TEdit *EditRad;
	TLabel *Label11;
	TLabel *Label6;
	TEdit *EditDiag;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *EditStepOX;
	TLabel *Label14;
	TLabel *Label15;
	TEdit *EditStepOZ;
	TLabel *Label16;
	TPageControl *PageControl1;
	TTabSheet *Углы;
	TTabSheet *Точки;
	TGroupBox *GroupBox6;
	TLabel *Label3;
	TLabel *Label35;
	TEdit *EditFirstPointY;
	TLabel *Label1;
	TEdit *EditFirstPointX;
	TLabel *Label38;
	TLabel *Label41;
	TEdit *EditSecondPointX;
	TLabel *Label43;
	TEdit *EditSecondPointY;
	TLabel *Ошибки;
	TLabel *Label47;
	TEdit *EditGammaErrorZ;
	TCheckBox *AddPointsCheckBox;
	TBindingsList *BindingsList1;
	TLinkControlToProperty *LinkControlToPropertyEnabled;
	TLinkControlToProperty *LinkControlToPropertyEnabled2;
	TLinkControlToProperty *LinkControlToPropertyEnabled3;
	TLinkControlToProperty *LinkControlToPropertyEnabled4;
	TLabel *Label39;
	TButton *Button1;
	TOpenDialog *OpenDialog;
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall ButtonSimulateClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall EditFocChange(TObject *Sender);
	void __fastcall EditElemChange(TObject *Sender);
	void __fastcall EditWidthChange(TObject *Sender);
	void __fastcall CheckBoxCoordErrorClick(TObject *Sender);
	void __fastcall CheckBoxAngleErrorClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CheckBoxModelCentreClick(TObject *Sender);
	void __fastcall CheckBoxDistClick(TObject *Sender);
	void __fastcall ButtonOpenDistClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);

private:	// User declarations
	void ReadINI(AnsiString path);
	void WriteINI(AnsiString path);
	void WriteToFile(string filename, XYCoords& out, VectorCos& out_v);
	void XY(double* Xout,double* Yout, int a, int b, VectorCos& v, double Mx[3][3]);
	vector < pair<short, short> > RadToPix(XYCoords& in, XYCoords& out, double SKOpixel, bool flDist);
	void Model_Result(double SKO_angle_OZ, double SKO_angle_OX, OffsetAngles& offsetAngles, VectorCos& vecCos, XYCoords& in);
	void Model_Result(double SKO_angle_OZ, double SKO_angle_OX, OffsetAngles& offsetAngles, VectorCos& vecCos, XYCoords& in, SimulateCatalogData& simCat);
	void initErrors();
	void initMatrixes();
	void initLeftParams();
	void readSimCat(String filename, SimulateCatalogData& catData);

	OffsetAngles offsetAngles;
	AdditionalPointsOffset addPointsParams;
	double f, Delement, RadiusPZ, DiagPZ;
	double GammaMax, GammaInc, incOX, incOZ;
	double Gamma[MaxPoint];
	double dx[MaxPoint][MaxPoint], dy[MaxPoint][MaxPoint], dx_r[MaxPoint][MaxPoint], dy_r[MaxPoint][MaxPoint];
	int Cx, Cy, CountOX, CountOZ, CountPixY[MaxPoint], CountOZ_1, CountPixY_1[MaxPoint];
	int MaxX, MaxY;
	double Minit[3][3], Mc[3][3], Mx[3][3], Mz[3][3], My[3][3], LMN[3], Maxis[3][3];

	int NumberInRow, center, AmountNotCenter[MaxPoint];
	double SKOpix, SKOangleOZ, SKOangleOX;
	bool if_SKO, CenterModel;
	double scale, DelCenter;
	double Ax[MaxDist], Ay[MaxDist];
	double AngleOZ[MaxPoint], AngleOX[MaxPoint][MaxPoint], AngleOX_1[MaxPoint][MaxPoint],
	 AngleOY[MaxPoint][MaxPoint], AngleOY_1[MaxPoint][MaxPoint];





AnsiString SourceDir;

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
