//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#include <Math.hpp>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <IniFiles.hpp>
#include <fstream>
#pragma hdrstop
#include <string>
#include <vector>
#include <utility>
#include <iomanip>
#include "AddString.h"
#include "ModelingUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	FormatSettings.DecimalSeparator = '.';
	SourceDir = GetCurrentDir();
	ReadINI(SourceDir + "\\options.ini");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	WriteINI(SourceDir + "\\options.ini");
}
//---------------------------------------------------------------------------

void TForm1::ReadINI(AnsiString path)
{
	TIniFile *Ini  = new TIniFile(path);
//Device
	EditFoc->Text  = Ini->ReadString("Device", "Foc",  "32");
	EditElem->Text = Ini->ReadString("Device", "Elem", "0.0055");
	EditWidth->Text  = Ini->ReadString("Device", "Width",  "2048");
	EditHeight->Text = Ini->ReadString("Device", "Height", "2048");
	EditRad->Text  = Ini->ReadString("Device", "Radius", "9.9");
	EditDiag->Text = Ini->ReadString("Device", "Diag",   "28");
	CheckBoxCoordError->Checked = StrToInt(Ini->ReadString("Device", "CheckCoordError", "0"));
	EditCoordError->Text  = Ini->ReadString("Device", "CoordError", "0");
	CheckBoxDist->Checked = StrToInt(Ini->ReadString("Device", "CheckDist", "0"));
	EditFileDist->Text  = Ini->ReadString("Device", "FileDist", "");

//Stend
	EditStepOX->Text  = Ini->ReadString("Stend", "StepX", "1");
	EditStepOZ->Text  = Ini->ReadString("Stend", "StepZ", "10");
	CheckBoxAngleError->Checked = StrToInt(Ini->ReadString("Stend", "CheckAngleError", "0"));
	EditAngleErrorOX->Text  = Ini->ReadString("Stend", "AngleErrorX", "0");
	EditAngleErrorOZ->Text  = Ini->ReadString("Stend", "AngleErrorZ", "0");
	CheckBoxEqualNet->Checked = StrToInt(Ini->ReadString("Stend", "CheckEqualNet", "0"));
	CheckBoxModelCentre->Checked = StrToInt(Ini->ReadString("Stend", "CheckModelCentre", "0"));
	EditCentrePoint->Text  = Ini->ReadString("Stend", "CentrePoint", "2");
	EditPercent->Text  = Ini->ReadString("Stend", "Percent", "75");
//View
	EditScale->Text  = Ini->ReadString("View", "Scale", "100");

	delete Ini;
}
//---------------------------------------------------------------------------

void TForm1::WriteINI(AnsiString path)
{
	TIniFile *Ini = new TIniFile(path);
//Device
	Ini->WriteString("Device", "Foc",  EditFoc->Text);
	Ini->WriteString("Device", "Elem", EditElem->Text);
	Ini->WriteString("Device", "Width",  EditWidth->Text);
	Ini->WriteString("Device", "Height", EditHeight->Text);
	Ini->WriteString("Device", "Radius", EditRad->Text);
	Ini->WriteString("Device", "Diag",   EditDiag->Text);
	Ini->WriteString("Device", "CheckCoordError", IntToStr((int)CheckBoxCoordError->Checked));
	Ini->WriteString("Device", "CoordError", EditCoordError->Text);
	Ini->WriteString("Device", "CheckDist", IntToStr((int)CheckBoxDist->Checked));
	Ini->WriteString("Device", "FileDist", EditFileDist->Text);

//Stend
	Ini->WriteString("Stend", "StepX", EditStepOX->Text);
	Ini->WriteString("Stend", "StepZ", EditStepOZ->Text);
	Ini->WriteString("Stend", "CheckAngleError", IntToStr((int)CheckBoxAngleError->Checked));
	Ini->WriteString("Stend", "AngleErrorX", EditAngleErrorOX->Text);
	Ini->WriteString("Stend", "AngleErrorZ", EditAngleErrorOZ->Text);
	Ini->WriteString("Stend", "CheckEqualNet", IntToStr((int)CheckBoxEqualNet->Checked));
	Ini->WriteString("Stend", "CheckModelCentre", IntToStr((int)CheckBoxModelCentre->Checked));
	Ini->WriteString("Stend", "CentrePoint", EditCentrePoint->Text);
	Ini->WriteString("Stend", "Percent", EditPercent->Text);
//View
	Ini->WriteString("View", "Scale", EditScale->Text);
	delete Ini;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonCloseClick(TObject *Sender)
{
	Form1->Close();
}
//---------------------------------------------------------------------------

double degtorad(double angle)
{
	double angle_out = angle * pi / 180;
	return angle_out;
}
//---------------------------------------------------------------------------

double radtodeg(double angle)
{
	double angle_out = angle * 180. / pi;
	return angle_out;
}
//---------------------------------------------------------------------------



void TForm1::XY(double* Xout, double* Yout, int a, int b, VectorCos& v, double Mx[3][3])
{
	v.Lst[a][b] = Mx[0][0] * LMN[0] + Mx[0][1] * LMN[1] + Mx[0][2] * LMN[2];
	v.Mst[a][b] = Mx[1][0] * LMN[0] + Mx[1][1] * LMN[1] + Mx[1][2] * LMN[2];
	v.Nst[a][b] = Mx[2][0] * LMN[0] + Mx[2][1] * LMN[1] + Mx[2][2] * LMN[2];    //Знаменатель
	*Xout = - f * v.Lst[a][b] / v.Nst[a][b];
	*Yout = - f * v.Mst[a][b] / v.Nst[a][b];

}

//---------------------------------------------------------------------------

vector < pair<short, short> > TForm1::RadToPix(XYCoords& in, XYCoords& out, double SKOpixel, bool flDist)
{
	vector < pair<short, short> > vec;
	for (int i = 0; i < CountOZ; i++)
	{
		int starCountLine = 0;
		for (int j = 0; j < CountOX; j++)
		{
			if (flDist) {
				dx[i][j] = Ax[0] + Ax[1]*in.X[i][j] + Ax[2]*in.Y[i][j]
				+ Ax[3]*in.X[i][j]*in.X[i][j] + Ax[4]*in.X[i][j]*in.Y[i][j]+Ax[5]*in.Y[i][j]*in.Y[i][j]
				+ Ax[6]*in.X[i][j]*in.X[i][j]*in.X[i][j] + Ax[7]*in.X[i][j]*in.X[i][j]*in.Y[i][j] + Ax[8]*in.X[i][j]*in.Y[i][j]*in.Y[i][j]
				+ Ax[9]*in.Y[i][j]*in.Y[i][j]*in.Y[i][j];

				dy[i][j] = Ay[0] + Ay[1]*in.X[i][j] + Ay[2]*in.Y[i][j]
				+ Ay[3]*in.X[i][j]*in.X[i][j] + Ay[4]*in.X[i][j]*in.Y[i][j]+Ay[5]*in.Y[i][j]*in.Y[i][j]
				+ Ay[6]*in.X[i][j]*in.X[i][j]*in.X[i][j] + Ay[7]*in.X[i][j]*in.X[i][j]*in.Y[i][j] + Ay[8]*in.X[i][j]*in.Y[i][j]*in.Y[i][j]
				+ Ay[9]*in.Y[i][j]*in.Y[i][j]*in.Y[i][j];
			}
			else {
				dx[i][j] = 0.;
				dy[i][j] = 0.;
			}

//вводим ошибку дисторсии со знаком "+"
			double x = (in.X[i][j] + dx[i][j])/Delement + Cx;
			double y = (in.Y[i][j] + dy[i][j])/Delement + Cy;
			if (CenterModel)		//С ПРОПУСКОМ ЦЕНТРА
			{
				if ( (i+1) % center != 0)
				{
					if ((x >= 0) && (x <= MaxX) && (y >= 0)&& (y <= MaxY) &&
						((j <= floor(CountOX*DelCenter)) || (j >= floor(CountOX*(1-DelCenter)))))
					{
						out.X[i][starCountLine] = x + RandG(0, SKOpixel);
						out.Y[i][starCountLine] = y + RandG(0, SKOpixel);
						AngleOX[i][starCountLine] = AngleOX_1[i][j];
						AngleOY[i][starCountLine] = AngleOY_1[i][j];
						vec.push_back(make_pair(i, j));
						starCountLine++;

					}
				}
				else
				{
					if ((x >= 0) && (x <= MaxX) && (y >= 0) && (y <= MaxY))
					{
						out.X[i][starCountLine] = x + RandG(0, SKOpixel);
						out.Y[i][starCountLine] = y + RandG(0, SKOpixel);
						AngleOX[i][starCountLine] = AngleOX_1[i][j];
						AngleOY[i][starCountLine] = AngleOY_1[i][j];
						vec.push_back(make_pair(i, j));
						starCountLine++;

					}
				}
			}
			else
			{
				if ((x >= 0) && (x <= MaxX) && (y >= 0) && (y <= MaxY))
				{
					out.X[i][starCountLine] = x + RandG(0, SKOpixel);
					out.Y[i][starCountLine] = y + RandG(0, SKOpixel);
					AngleOX[i][starCountLine] = AngleOX_1[i][j];
					AngleOY[i][starCountLine] = AngleOY_1[i][j];
					dx_r[i][starCountLine] = dx[i][j];
					dy_r[i][starCountLine] = dy[i][j];
					vec.push_back(make_pair(i, j));
					starCountLine++;
				}
			}
		}
		CountPixY[i] = starCountLine;
	}
					// вывод dx, dy в файл
	if (flDist)
	{
		ofstream ofs;
		ofs.open("dx_dy.txt");
		for (int i = 0; i <= CountOZ; i++)
		{
			ofs << i << "\n";
			for (int j = 0; j < CountPixY[i]; j++)
			{
				ofs << (out.X[i][j] - Cx) * Delement << "\t"
				 << (out.Y[i][j] - Cy) * Delement<< "\t"
				 << dx_r[i][j] << "\t"
				 << dy_r[i][j] << "\n";
			}
		}
		ofs.close();
	}

	return vec;
}
//---------------------------------------------------------------------------

void MatrProizv3x3(double M1[3][3],double M2[3][3],double Mout[3][3])
{

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			Mout[i][j]=0;
			for(int k = 0; k < 3; k++)
				Mout[i][j] += M1[i][k] * M2[k][j];
		}
	}
}

void RotateOY(double Alpha, double M_in[3][3], double Mout[3][3])
{
	double M[3][3] = {{cos(Alpha), 0, sin(Alpha)},
					  {0, 1, 0},
					  {-sin(Alpha), 0, cos(Alpha)}};
	MatrProizv3x3(M, M_in, Mout);

}
////---------------------------------------------------------------------------
//
void RotateOZ(double Alpha, double M_in[3][3], double Mout[3][3])
{
	double M[3][3] = {{cos(Alpha), -sin(Alpha), 0},
					  {sin(Alpha), cos(Alpha), 0},
					  {0, 0, 1}};
	MatrProizv3x3(M, M_in, Mout);
}
////---------------------------------------------------------------------------
//
//
void RotateOX(double Alpha, double M_in[3][3], double Mout[3][3])
{
	double M[3][3] = {{1, 0, 0},
					  {0, cos(Alpha), -sin(Alpha)},
					  {0, sin(Alpha), cos(Alpha)}};
	MatrProizv3x3(M, M_in , Mout);
}

void initMatrix(double m[3][3])
 {
		static double mi [3][3] = {{1,0,0},{0,1,0},{0,0,1}};
		for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m[i][j] = mi[i][j];
		}
	}
 }

void calculateLMN(double alpha, double delta, double azimut, double LMN_rot[3])
{
	double Mc[3][3];
	double Mrot[3][3];
	double Maz[3][3];
	double Malpha[3][3];

	initMatrix(Mc);
	initMatrix(Mrot);
	initMatrix(Maz);
	initMatrix(Malpha);

	RotateOZ(azimut, Mc, Maz);
	RotateOX(alpha, Maz, Malpha);
	RotateOY(delta, Malpha, Mrot);


	double LMNtemp[3] = {0, 0, 1};
	LMN_rot[0] = Mrot[0][0] * LMNtemp[0] + Mrot[0][1] * LMNtemp[1] + Mrot[0][2] * LMNtemp[2];
	LMN_rot[1] = Mrot[1][0] * LMNtemp[0] + Mrot[1][1] * LMNtemp[1] + Mrot[1][2] * LMNtemp[2];
	LMN_rot[2] = Mrot[2][0] * LMNtemp[0] + Mrot[2][1] * LMNtemp[1] + Mrot[2][2] * LMNtemp[2];    //Знаменатель
}

void calculateLMN(double Mrot[3][3], double LMN_rot[3])
{
	double LMNtemp[3] = {0, 0, 1};
	LMN_rot[0] = Mrot[0][0] * LMNtemp[0] + Mrot[0][1] * LMNtemp[1] + Mrot[0][2] * LMNtemp[2];
	LMN_rot[1] = Mrot[1][0] * LMNtemp[0] + Mrot[1][1] * LMNtemp[1] + Mrot[1][2] * LMNtemp[2];
	LMN_rot[2] = Mrot[2][0] * LMNtemp[0] + Mrot[2][1] * LMNtemp[1] + Mrot[2][2] * LMNtemp[2];    //Знаменатель

}
//---------------------------------------------------------------------------


void MultMatrix(double matrix1[3][3], double matrix2[3][3], double matrix[3][3])
{
	int i, j, k;
	double buf;
	double matrixC[3][3];

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			buf = 0;
			for (k = 0; k < 3; k++) {
				buf += (matrix1[i][k] * matrix2[k][j]);
			}
			matrixC[i][j] = buf;
		}
	}

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			matrix[i][j] = matrixC[i][j];
		}
	}
}


double atan2mod(double yf, double xf)
{
	double ang;
    if (fabs(xf) > 1e-10)
    {
        ang = atan2(yf, xf);
    }
    else
    {
		if (yf > 0)
		{
			ang = M_PI/2.;
		}
		else
		{
			ang = -M_PI/2.;
		}
	}
	return ang;
}



void matrToEkvA(double M_ornt[3][3], double& al, double& dl, double& Az)
{
	dl = asin(M_ornt[2][2]);
	al = atan2mod(M_ornt[2][1], M_ornt[2][0]);
	if (al<0)
	{
		al += 2 * M_PI;
	}
	Az = atan2mod(M_ornt[0][2], M_ornt[1][2]);
	if (Az < 0)
	{
		Az += 2 * M_PI;
	}
}

void TForm1::Model_Result(double SKO_angle_OZ, double SKO_angle_OX, OffsetAngles& offsetAngles, VectorCos& vecCos, XYCoords& in, SimulateCatalogData& simCat)
{
     //Mc = Minit для 1 шага
 //Моделирование результатов испытаний

	double MsecondPlatfOY[3][3];
	double MsecondPlatfOX[3][3];
	double MgammaOY[3][3];
	double MgammaOZ[3][3];
	double MgammaOX[3][3];
	double MVSKNoDir[3][3];
	double MVSK[3][3];
	double MDelta[3][3];

//	CountOZ = floor(2 * pi / incOZ) + 1; 	//Кол-во поворотов вокруг OZ
//	if (radtodeg(incOZ * CountOZ) > 359.9)
//	{
//		CountOZ = CountOZ - 1;
//	}

	if (CountOX > MaxPoint) CountOX = MaxPoint;
	CountOZ = CountOX;
	double triangleAngles [3][2] =  {{0, 0},
	{addPointsParams.firstPointOffsetY, addPointsParams.firstPointOffsetX},
	{addPointsParams.secondPointOffsetY, addPointsParams.secondPointOffsetX}};

	double Mi[3][3]  = {{0, 0, 1}, {0, -1, 0}, {1, 0, 0}};
	double Mtemp[3][3];
	vector <double> gammaOZAngles;

	int pointCount;
	if (AddPointsCheckBox->Checked)
	{
		pointCount = 3;
	}
	else
	{
		pointCount = 1;
	}

	for (int i = 0; i <= CountOZ; i++)
	{
		double errorOz = 0;
		if (CheckBoxAngleError->Checked) {
			errorOz = RandG(0.0055, offsetAngles.SKOGammaOZ);
		}
		gammaOZAngles.push_back(errorOz);
	}

		CountOX = pointCount * simCat.alpha.size();
		for (int j = 0; j < CountOX; j++)
		{
			for (int i = 0; i < CountOZ ; i++)
			{
				int pointPos = j * pointCount;
				for (int k = 0; k < pointCount; k++)
				{
					RotateOZ(gammaOZAngles[i], Minit, MgammaOZ);    // новый поворот
					RotateOY(offsetAngles.gammaOY, MgammaOZ, MgammaOY);
					RotateOX(offsetAngles.gammaOX, MgammaOY, MgammaOX);
					AngleOZ[i] = i * incOZ;
					AngleOY_1[i][pointPos] = degtorad(simCat.delta[j]);
					double AngleOZReal =  AngleOZ[i] + degtorad(RandG(0, SKO_angle_OZ));
					AngleOX_1[i][pointPos] = degtorad(simCat.alpha[j]);
					double AngleOXReal =  AngleOX_1[i][pointPos] + degtorad(RandG(0, SKO_angle_OX));
					RotateOZ(AngleOXReal, Minit, Mx);
					RotateOY(offsetAngles.alphaTwoOY, Minit , MsecondPlatfOY);
					RotateOX(offsetAngles.alphaTwoOX, MsecondPlatfOY, MsecondPlatfOX);
					MatrProizv3x3(Mi ,MsecondPlatfOX , Mtemp);
					//RotateOZ(AngleOZReal, Mtemp, Mc);
					RotateOY(Gamma[i], Mtemp, Mc);  // новый поворот
					MatrProizv3x3(Mc ,Mx, Mtemp);
					MatrProizv3x3(MgammaOX, Mtemp, MVSKNoDir);
					MatrProizv3x3(Maxis, MVSKNoDir, MVSK);
					LMN[0] = -cos(degtorad(simCat.delta[j]) + offsetAngles.alphaOneOY + triangleAngles[k][0])
					* cos(offsetAngles.lambdaOX + offsetAngles.alphaOneOX + + triangleAngles[k][1]);
					LMN[1] = -cos(degtorad(simCat.delta[j]) + offsetAngles.alphaOneOY + triangleAngles[k][0])
					* sin(offsetAngles.lambdaOX + offsetAngles.alphaOneOX + triangleAngles[k][1]);
					LMN[2] = -sin(degtorad(simCat.delta[j])+ offsetAngles.alphaOneOY + triangleAngles[k][0]);
					XY(&in.X[i][pointPos], &in.Y[i][pointPos], i, pointPos, vecCos, MVSK);
					++pointPos;
				}
			}
		}
}

void TForm1::Model_Result(double SKO_angle_OZ, double SKO_angle_OX, OffsetAngles& offsetAngles, VectorCos& vecCos, XYCoords& in)
{
 //Mc = Minit для 1 шага
 //Моделирование результатов испытаний

	double MsecondPlatfOY[3][3];
	double MsecondPlatfOX[3][3];
	double MgammaOZ[3][3];
	double MgammaOY[3][3];
	double MgammaOX[3][3];
	double MVSKNoDir[3][3];
	double MVSK[3][3];
	double MDelta[3][3];

	CountOZ = floor(2 * pi / incOZ) + 1; 	//Кол-во поворотов вокруг OZ
	if (radtodeg(incOZ * CountOZ) > 359.9)
	{
		CountOZ = CountOZ - 1;
	}

	if (CountOZ > MaxPoint) CountOZ = MaxPoint;
	if (CountOX > MaxPoint) CountOX = MaxPoint;
	//CountOZ = CountOX;

	double triangleAngles [3][2] =  {{0, 0},
	{addPointsParams.firstPointOffsetY, addPointsParams.firstPointOffsetX},
	{addPointsParams.secondPointOffsetY, addPointsParams.secondPointOffsetX}};

	double Mi[3][3]  = {{0, 0, 1}, {0, -1, 0}, {1, 0, 0}};
	double Mtemp[3][3];
	//double MfirstPlatfOX[3][3];
	//RotateOX(offsetAngles.lambdaOX + offsetAngles.alphaOneOX, Minit, MfirstPlatfOX);
	vector <double> gammaOZAngles;

	int pointCount;
	if (AddPointsCheckBox->Checked)
	{
		pointCount = 3;
		CountOX = NumberInRow * pointCount;
	}
	else
	{
		pointCount = 1;
		CountOX = NumberInRow;
	}

	for (int i = 0; i < CountOZ; i++)
	{
		double errorOz = 0;
		if (CheckBoxAngleError->Checked) {
			errorOz = RandG(0.0055, offsetAngles.SKOGammaOZ);
		}
		gammaOZAngles.push_back(errorOz);
	}
		for (int j = 0; j < CountOX; j++)
		{
			for (int i = 0; i < CountOZ; i++)
			{
				int pointPos = j * pointCount;
				for (int k = 0; k < pointCount; k++)
				{
					RotateOZ(gammaOZAngles[i], Minit, MgammaOZ);    // новый поворот
					RotateOY(offsetAngles.gammaOY, MgammaOZ, MgammaOY);
					RotateOX(offsetAngles.gammaOX, MgammaOY, MgammaOX);
					AngleOZ[i] = i * incOZ;
					double AngleOZReal =  AngleOZ[i] + degtorad(RandG(0, SKO_angle_OZ));
					AngleOX_1[i][pointPos] = Gamma[j];
					double AngleOXReal =  AngleOX_1[i][pointPos] + degtorad(RandG(0, SKO_angle_OX));
					RotateOZ(AngleOXReal, Minit, Mx);
					RotateOY(offsetAngles.alphaTwoOY, Minit , MsecondPlatfOY);
					RotateOX(offsetAngles.alphaTwoOX, MsecondPlatfOY, MsecondPlatfOX);
					MatrProizv3x3(Mi ,MsecondPlatfOX , Mtemp);
					//RotateOZ(AngleOZReal, Mtemp, Mc);
					RotateOY(Gamma[i], Mtemp, Mc);  // новый поворот
					MatrProizv3x3(Mc ,Mx, Mtemp);
					MatrProizv3x3(MgammaOX, Mtemp, MVSKNoDir);
					MatrProizv3x3(Maxis, MVSKNoDir, MVSK);
					LMN[0] = -cos(offsetAngles.lambdaOY + offsetAngles.alphaOneOY + triangleAngles[k][0])
					* cos(offsetAngles.lambdaOX + offsetAngles.alphaOneOX + triangleAngles[k][1]);
					LMN[1] = -cos(offsetAngles.lambdaOY + offsetAngles.alphaOneOY + triangleAngles[k][0])
					* sin(offsetAngles.lambdaOX + offsetAngles.alphaOneOX + triangleAngles[k][1]);
					LMN[2] = -sin(offsetAngles.lambdaOY + offsetAngles.alphaOneOY + triangleAngles[k][0]);
					XY(&in.X[i][pointPos], &in.Y[i][pointPos], i, pointPos, vecCos, MVSK);
					++pointPos;
				}
			}
		}
}


//---------------------------------------------------------------------------

void TForm1::WriteToFile(string filename, XYCoords& out, VectorCos& out_v)
{
 //Открытие файла для записи результатов моделирования
	FILE* f_out;
	FILE* f_lmn;
	string flmn = filename + "LMN.txt";
	f_out = fopen(filename.append(".txt").c_str(), "w");
	f_lmn = fopen(flmn.c_str(), "w");
 //Вывод результатов испытаний в файл
	fprintf(f_out, "№OX	№OZ	AngleOZ		AngleOX		AngleOY		    X	  	    Y	DeltaOY\n");
	fprintf(f_lmn, "№OX	№OZ		Lst		Mst		Nst\n");

	for (int i = 0; i <= CountOZ; i++) {
		for (int j = 0; j < CountPixY[i]; j++) {
			if (out.X[i][j] == 0 || out.Y[i][j] == 0) {
				continue;
			}
			fprintf(f_out, "%i	%i	%f	%f	%f	%f	%f	%f\n", i+1, j+1,
			radtodeg(AngleOZ[i]), radtodeg(AngleOX[i][j]),
			radtodeg(AngleOY[i][j]), out.X[i][j], out.Y[i][j], radtodeg(0));
		}
	}
	for (int i = 0; i <= CountOZ; i++) {
		for (int j = 0; j < CountOX; j++) {
			fprintf(f_lmn, "%i	%i	%.9g	%.9g	%.9g\n", i+1, j+1, out_v.Lst[i][j], out_v.Mst[i][j], out_v.Nst[i][j]);
		}
	}

 //Закрытие файла
	fclose(f_out);
	fclose(f_lmn);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonSimulateClick(TObject *Sender)
{

	EditFoc->Enabled    = False;
	EditElem->Enabled   = False;
	EditWidth->Enabled  = False;
	EditHeight->Enabled = False;
 //-------------------------

 	initErrors();
	initMatrixes();
	initLeftParams();

	if (CheckBoxEqualNet->Checked == False)
	{
  //НЕРАВНОМЕРНАЯ СЕТКА
		NumberInRow = floor(DiagPZ/GammaInc)+1;
		if (NumberInRow > MaxPoint) NumberInRow = MaxPoint;

		for (int i = 0; i < NumberInRow/2; i++)
		{
			Gamma[i] = -GammaInc*(NumberInRow/2-i);
		}
		Gamma[NumberInRow/2] = 0;
		for (int i = floor((double)(NumberInRow/2)) + 1; i < NumberInRow; i++)
		{
			Gamma[i] = GammaInc * (i - floor((double)(NumberInRow / 2)));
		}
	}
	else
	{
  //РАВНОМЕРНАЯ СЕТКА
		int n_Gamma = 1;
		double Gamma_1[50];
		Gamma_1[0] = GammaInc;
		double step = f * tan(GammaInc); //Шаг вдоль ОХ [мм]
		while (Gamma_1[n_Gamma-1] <= DiagPZ/2)
		{
			Gamma_1[n_Gamma] = atan((n_Gamma + 1) * step/f);
			n_Gamma++;
		}
		Gamma[n_Gamma]=0;

		int i;
		for (i = 0; i < n_Gamma; i++)
		{
			Gamma[n_Gamma - i - 1] = -Gamma_1[i];
			Gamma[i + n_Gamma + 1] =  Gamma_1[i];
		}
		NumberInRow = i * 2 + 1;
	}
	CenterModel = CheckBoxModelCentre->Checked;  	//Проверка пропусков моделирования центра
	center = StrToInt(EditCentrePoint->Text);   	//Шаг моделирования центра
	DelCenter = StrToFloat(EditPercent->Text)/200;		//Процент моделируемых точек  [половина значения]

 //РАСЧЕТ БЕЗ ОТКЛОНЕНИЙ
	SKOangleOZ = 0;
	SKOangleOX = 0;
	SKOpix = 0;

	XYCoords in;
	XYCoords out_n;
	XYCoords out_r;
	VectorCos vecNoError;
	OffsetAngles zeroAngles;
	Model_Result(0, 0, zeroAngles, vecNoError, in);
	//Modeling(0, 0, zeroAngles, vecNoError, in);
	RadToPix(in, out_n, SKOpix, false);							//Перевод в пиксели
	string f_clear = "Results_Clear";
	WriteToFile(f_clear, out_n, vecNoError);

	VectorCos vecAngles;
   Model_Result(SKOangleOZ, SKOangleOX, offsetAngles, vecAngles, in);
   //Modeling(SKOangleOZ, SKOangleOX, offsetAngles, vecAngles, in);

	vector< pair<short,short> > vec = RadToPix(in, out_n, SKOpix, false);		 //Перевод в пиксели

	string f_without_SKO = "Results_Needed";
	WriteToFile(f_without_SKO, out_n, vecAngles);

	CountOZ_1 = CountOZ;

 //Вывод результатов испытаний на график
	Series2->Active = false; //Отключение Series2
	Series1->Clear();		//Очистка Series1 в TChart
	Series1->Active = true;

	for (int i = 0; i <= CountOZ; i++) {
		for (int j = 0; j < CountPixY[i]; j++) {
			Series1->AddXY(out_n.X[i][j], out_n.Y[i][j]);
		}
		CountPixY_1[i] = CountPixY[i];
	}

	scale = 1;//StrToFloat(EditScale->Text);

//Моделирование в случае наличия отклонений
	if (if_SKO)
	{
		VectorCos vecError;
		Model_Result(SKOangleOZ, SKOangleOX, offsetAngles, vecError, in);			//Моделирование результатов
		//Modeling(SKOangleOZ, SKOangleOX, offsetAngles, vecError, in);
		vector< pair<short,short> > vec = RadToPix(in, out_r, SKOpix, true);	//Перевод в пиксели

		VectorCos vecInters;
		int row =  vec[0].first;
		int k = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			if (row != vec[i].first)
			{
				k = 0;
				row = vec[i].first;
			}
			vecInters.Lst[vec[i].first][k] = vecNoError.Lst[vec[i].first][vec[i].second];
			vecInters.Mst[vec[i].first][k] = vecNoError.Mst[vec[i].first][vec[i].second];
			vecInters.Nst[vec[i].first][k] = vecNoError.Nst[vec[i].first][vec[i].second];
			++k;

		}

		ofstream ofs;
		ofs.open("LMN_RECOGNITION.txt");
		for (int i = 0; i <= CountOZ; i++)
		{
			for (int j = 0; j < CountPixY[i]; j++)
			{
				ofs<< std::setprecision(9) << i << "\t" << j << "\t"
				<< vecInters.Lst[i][j] << "\t"
				<< vecInters.Mst[i][j] << "\t"
				<< vecInters.Nst[i][j] << "\t"
				<< "\n";
			}
		}
		ofs.close();

		ofs.open("LMN_COMPARE.txt");
        for (int i = 0; i < vec.size(); i++)
		{
			ofs << std::setprecision(9) << i << "\t"
			 << vecError.Lst[vec[i].first][vec[i].second] << "\t"
			 << vecError.Mst[vec[i].first][vec[i].second] << "\t"
			 << vecError.Nst[vec[i].first][vec[i].second] << "\t"
			 << "\n";
        }
		ofs.close();


		string f_with_SKO = "Results_Factical";
		WriteToFile(f_with_SKO, out_r, vecError);    //Вывод в файл "Results_Factical.txt"
		//Вывод результатов испытаний на график
		Series1->Active = true;
		Series2->Clear();		//Очистка Series2 в TChart
		Series2->Active = true;

		if (CountOZ_1 < CountOZ) {
			CountOZ = CountOZ_1;
		}
		for (int i = 0; i <= CountOZ; i++)
		{
			if (CountPixY_1[i] < CountPixY[i]) {
				CountPixY[i] = CountPixY_1[i];
			}
			for (int j = 0; j < CountPixY[i]; j++)
			{
				double offsetX = (out_r.X[i][j] - out_n.X[i][j]) * scale;
				double offsetY = (out_r.Y[i][j] - out_n.Y[i][j]) * scale;
				Series1->AddXY(out_n.X[i][j], out_n.Y[i][j]);
				Series2->AddArrow(out_n.X[i][j], out_n.Y[i][j], out_r.X[i][j] + offsetX, out_r.Y[i][j] + offsetY);
			}
		}
	}

//-------------------------
	EditFoc->Enabled    = True;
	EditElem->Enabled   = True;
	EditWidth->Enabled  = True;
	EditHeight->Enabled = True;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
	Series1->Active = false;
	Series2->Active = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditFocChange(TObject *Sender)
{
	f=StrToFloat(EditFoc->Text);
	Delement=StrToFloat(EditElem->Text);
	MaxX=StrToInt(EditWidth->Text);
	MaxY=StrToInt(EditHeight->Text);
	RadiusPZ=atan(MaxX/2*Delement/f);
	RadiusPZ=radtodeg(RadiusPZ);
	EditRad->Text=FloatToStr(RadiusPZ);
	DiagPZ=SimpleRoundTo(sqrt(8*RadiusPZ*RadiusPZ),-4);
	GammaMax=DiagPZ / 2;
	GammaInc=SimpleRoundTo(GammaMax/14,-4);    //шаг поворота вокруг осей OX и OZ
	incOX=GammaInc;
	EditDiag->Text=FloatToStr(DiagPZ);
	EditStepOX->Text=FloatToStr(incOX);

//те же числа переводим в радианы
	DiagPZ=degtorad(DiagPZ);
	incOX=degtorad(incOX);
	GammaInc=degtorad(GammaInc);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditElemChange(TObject *Sender)
{
	f = StrToFloat(EditFoc->Text);
	Delement = StrToFloat(EditElem->Text);
	MaxX = StrToInt(EditWidth->Text);
	MaxY = StrToInt(EditHeight->Text);
	RadiusPZ = atan(MaxX / 2 * Delement / f);
	RadiusPZ = radtodeg(RadiusPZ);
	EditRad->Text = FloatToStr(RadiusPZ);
	DiagPZ = SimpleRoundTo(sqrt(8 * RadiusPZ * RadiusPZ), -4);
	GammaMax = DiagPZ / 2;
	GammaInc = SimpleRoundTo(GammaMax / 14, -4);    //шаг поворота вокруг осей OX и OZ
	incOX = GammaInc;
	EditDiag->Text = FloatToStr(DiagPZ);
	EditStepOX->Text = FloatToStr(incOX);

//те же числа переводим в радианы
	DiagPZ   = degtorad(DiagPZ);
	incOX    = degtorad(incOX);
	GammaInc = degtorad(GammaInc);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditWidthChange(TObject *Sender)
{
	f = StrToFloat(EditFoc->Text);
	Delement = StrToFloat(EditElem->Text);
	MaxX = StrToInt(EditWidth->Text);
	MaxY = StrToInt(EditHeight->Text);
	RadiusPZ = atan(MaxX/2 * Delement/f);
	RadiusPZ = radtodeg(RadiusPZ);
	EditRad->Text = FloatToStr(RadiusPZ);
	DiagPZ = SimpleRoundTo(sqrt(8 * RadiusPZ*RadiusPZ), -4);
	GammaMax = DiagPZ/2;
	GammaInc = SimpleRoundTo(GammaMax/14, -4);    //шаг поворота вокруг осей OX и OZ
	incOX = GammaInc;
	EditDiag->Text   = FloatToStr(DiagPZ);
	EditStepOX->Text = FloatToStr(incOX);

//те же числа переводим в радианы
	DiagPZ   = degtorad(DiagPZ);
	incOX    = degtorad(incOX);
	GammaInc = degtorad(GammaInc);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBoxDistClick(TObject *Sender)
{
	EditFileDist->Enabled = CheckBoxDist->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonOpenDistClick(TObject *Sender)
{
	if (OpenDialogDist->Execute()) {
		EditFileDist->Text = OpenDialogDist->FileName;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBoxModelCentreClick(TObject *Sender)
{
	EditCentrePoint->Enabled = CheckBoxModelCentre->Checked;
	EditPercent->Enabled = CheckBoxModelCentre->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBoxCoordErrorClick(TObject *Sender)
{
	EditCoordError->Enabled = CheckBoxCoordError->Checked;

	if ((!CheckBoxAngleError->Checked) && (!CheckBoxCoordError->Checked)) {
		EditScale->Enabled = false;
	}
	else {
		EditScale->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBoxAngleErrorClick(TObject *Sender)
{
	EditAngleErrorOX->Enabled = CheckBoxAngleError->Checked;
	EditAngleErrorOZ->Enabled = CheckBoxAngleError->Checked;

	if ((!CheckBoxAngleError->Checked) && (!CheckBoxCoordError->Checked)) {
		EditScale->Enabled = false;
	}
	else {
		EditScale->Enabled = true;
	}
}

	void  TForm1::initErrors()
	{
		for (int i = 0; i < MaxDist; i++) {
			Ax[i] = 0.;
			Ay[i] = 0.;
		}
		if_SKO = false;
		if (CheckBoxDist->Checked == true) {
			if_SKO = true;
			//чтение Ax, Ay из файла
			FILE* flist;
			flist = fopen(AnsiString(EditFileDist->Text).c_str(), "rt");
			if (flist != NULL) {
				int i = 0;
				char line[200];
				while ((!feof(flist)) && (i < MaxDist)) {
					if (fgets(line, 200, flist) != NULL) {
						if (sscanf(line, "%le%le\n", &Ax[i], &Ay[i]) == 2)
							i++;
					}
				}
				fclose(flist);
			}
		}

		if (CheckBoxCoordError->Checked == true) {
			if_SKO = true;
			SKOpix = StrToFloat(EditCoordError->Text);
		}

		if (CheckBoxAngleError->Checked == true) {
			if_SKO = true;
			SKOangleOZ = StrToFloat(EditAngleErrorOZ->Text) / 3600.; //Чтение в " и перевод в [град]
			SKOangleOX = StrToFloat(EditAngleErrorOX->Text) / 3600.; //Чтение в " и перевод в [град]
			offsetAngles.SKOGammaOZ = degtorad(StrToFloat(EditGammaErrorZ->Text) / 3600.);
			//offsetAngles.SKOGammaOY = degtorad(StrToFloat(EditGammaErrorY->Text) / 3600.);
		}


		offsetAngles.alphaOneOY = degtorad(StrToFloat(EditAlpha1OY->Text));
		offsetAngles.alphaOneOX = degtorad(StrToFloat(EditAlpha1OX->Text));
		offsetAngles.lambdaOY = degtorad(StrToFloat(EditLambdaOY->Text));
		offsetAngles.lambdaOX = degtorad(StrToFloat(EditLambdaOX->Text));
		offsetAngles.alphaTwoOY = degtorad(StrToFloat(EditAlpha2OY->Text));
		offsetAngles.alphaTwoOX = degtorad(StrToFloat(EditAlpha2OX->Text));
		offsetAngles.gammaOY = degtorad(StrToFloat(EditGammaOY->Text));
		offsetAngles.gammaOX = degtorad(StrToFloat(EditGammaOX->Text));

		if (AddPointsCheckBox->Checked) {
			addPointsParams.firstPointOffsetX = degtorad(StrToFloat(EditFirstPointX->Text) / 60);
			addPointsParams.firstPointOffsetY = degtorad(StrToFloat(EditFirstPointY->Text) / 60);
			addPointsParams.secondPointOffsetX = degtorad(StrToFloat(EditSecondPointX->Text) / 60);
			addPointsParams.secondPointOffsetY = degtorad(StrToFloat(EditSecondPointY->Text) / 60);
		}
	}

 void  TForm1::initMatrixes()
 {
      		//Задание матрицы начальной установки М0
		Minit[0][0] = 1;
		Minit[0][1] = 0;
		Minit[0][2] = 0;
		Minit[1][0] = 0;
		Minit[1][1] = 1;
		Minit[1][2] = 0;
		Minit[2][0] = 0;
        Minit[2][1] = 0;
		Minit[2][2] = 1;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 10; j++) {
				Maxis[i][j] = 0;
			}
		}
		if (UpRadioButton->Checked) {
			Maxis[0][0] = 1;
			Maxis[1][1] = 1;
			Maxis[2][2] = 1;
		}
		else if (DownRadioButton->Checked) {
			Maxis[0][0] = -1;
			Maxis[1][1] = -1;
			Maxis[2][2] = 1;
		}
		else if (LeftRadioButton->Checked) {
			Maxis[0][1] = -1;
			Maxis[1][0] = 1;
			Maxis[2][2] = 1;
		}
		else if (RightRadioButton->Checked) {
			Maxis[0][1] = 1;
			Maxis[1][0] = -1;
			Maxis[2][2] = 1;
		}

		//Задание вектора направляющих косинусов
		LMN[0] = StrToFloat(L->Text);
		LMN[1] = StrToFloat(M->Text);
		LMN[2] = StrToFloat(N->Text);
 }

 void  TForm1::initLeftParams()
 {
      //Задание параметров оптической системы прибора (Диагональ и радиус поля зрения считаются по ходу ввода)
	f = StrToFloat(EditFoc->Text);
	Delement = StrToFloat(EditElem->Text);
	MaxX = StrToInt(EditWidth->Text);
	MaxY = StrToInt(EditHeight->Text);
	RadiusPZ = StrToFloat(EditRad->Text);
	DiagPZ = SimpleRoundTo(sqrt(8*RadiusPZ*RadiusPZ),-2);
	EditDiag->Text = FloatToStr(DiagPZ);
	GammaInc = StrToFloat(EditStepOX->Text);
 //Перевод углов в радианы
	GammaInc = degtorad(GammaInc);
	DiagPZ   = degtorad(DiagPZ);
	incOX    = degtorad(StrToFloat(EditStepOX->Text));
	incOZ    = degtorad(StrToFloat(EditStepOZ->Text));
	Cx = MaxX / 2;
	Cy = MaxY / 2; //Координаты центра поля зрения

	SKOangleOZ = 0;
	SKOangleOX = 0;
	SKOpix = 0;

 }
 void TForm1::readSimCat(String filename, SimulateCatalogData& catData)
 {
		ifstream ifs;
		ifs.open(AnsiString(filename).c_str());
		string line;
		getline(ifs, line);
		while (getline(ifs, line))
		{
			vector <string> splitted = add_string::split(line, "\t");
			catData.alpha.push_back(stod(splitted[1]));
			catData.delta.push_back(stod(splitted[2]));
		}
		ifs.close();
 }

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	EditFoc->Enabled = False;
	EditElem->Enabled = False;
	EditWidth->Enabled = False;
	EditHeight->Enabled = False;
	OpenDialog->Options.Clear();
	OpenDialog->Filter = "txt|*.txt";
	OpenDialog->Options << ofAllowMultiSelect;
if (OpenDialog->Execute()) {
	unique_ptr<TStringList> FileList(new TStringList());
	FileList->Assign(OpenDialog->Files);
	initErrors();
	initMatrixes();
	initLeftParams();
	for (int k = 0; k < FileList->Count; k++) {
		SimulateCatalogData simCat;
		readSimCat(FileList->Strings[k], simCat);
		XYCoords in;
		XYCoords out_n;
		XYCoords out_r;
		//РАСЧЕТ БЕЗ ОТКЛОНЕНИЙ
		VectorCos vecNoError;
        OffsetAngles zeroAngles;

        VectorCos vecAngles;
		Model_Result(SKOangleOZ, SKOangleOX, offsetAngles, vecAngles, in, simCat);
		vector<pair<short, short> > vec = RadToPix(in, out_n, SKOpix, false); //Перевод в пиксели
		UnicodeString initFileName = FileList->Strings[k];

		initFileName = StringReplace(initFileName, " .txt", "needed_res", TReplaceFlags() << rfReplaceAll);
		string f_without_SKO = add_string::toStdString(initFileName);
		WriteToFile(f_without_SKO, out_n, vecAngles);

        CountOZ_1 = CountOZ;

        //Вывод результатов испытаний на график
		Series2->Active = false; //Отключение Series2
        Series1->Clear(); //Очистка Series1 в TChart
        Series1->Active = true;

        for (int i = 0; i <= CountOZ; i++) {
            for (int j = 0; j < CountPixY[i]; j++) {
                Series1->AddXY(out_n.X[i][j], out_n.Y[i][j]);
            }
            CountPixY_1[i] = CountPixY[i];
        }

		scale = 1;//StrToFloat(EditScale->Text);
        //Моделирование в случае наличия отклонений
		if (if_SKO) {
            VectorCos vecError;
			Model_Result(SKOangleOZ, SKOangleOX, offsetAngles, vecError, in, simCat); //Моделирование результатов
            vector<pair<short, short> > vec = RadToPix(in, out_r, SKOpix, true); //Перевод в пиксели
            VectorCos vecInters;
            int row = vec[0].first;
			int k = 0;
            for (int i = 0; i < vec.size(); i++) {
                if (row != vec[i].first) {
                    k = 0;
                    row = vec[i].first;
                }
                vecInters.Lst[vec[i].first][k] = vecNoError.Lst[vec[i].first][vec[i].second];
                vecInters.Mst[vec[i].first][k] = vecNoError.Mst[vec[i].first][vec[i].second];
                vecInters.Nst[vec[i].first][k] = vecNoError.Nst[vec[i].first][vec[i].second];
                ++k;
			}
			initFileName = StringReplace(initFileName, "needed_res", "factical_res", TReplaceFlags() << rfReplaceAll);
			string f_with_SKO = add_string::toStdString(initFileName);
			WriteToFile(f_with_SKO, out_r, vecError); //Вывод в файл "Results_Factical.txt"
            //Вывод результатов испытаний на график
			Series1->Active = true;
            Series2->Clear(); //Очистка Series2 в TChart
            Series2->Active = true;

			if (CountOZ_1 < CountOZ) {
                CountOZ = CountOZ_1;
            }
			for (int i = 0; i <= CountOZ; i++) {
				if (CountPixY_1[i] < CountPixY[i]) {
                    CountPixY[i] = CountPixY_1[i];
                }
				for (int j = 0; j < CountPixY[i]; j++) {
					double offsetX = (out_r.X[i][j] - out_n.X[i][j]) * scale;
					double offsetY = (out_r.Y[i][j] - out_n.Y[i][j]) * scale;
					Series1->AddXY(out_n.X[i][j], out_n.Y[i][j]);
					Series2->AddArrow(out_n.X[i][j], out_n.Y[i][j], out_r.X[i][j] + offsetX, out_r.Y[i][j] + offsetY);
                }
            }
		}
	}
		EditFoc->Enabled = True;
		EditElem->Enabled = True;
		EditWidth->Enabled = True;
		EditHeight->Enabled = True;
}
}
//---------------------------------------------------------------------------


