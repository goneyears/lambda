/*******************************************************************************************************
**
** Dateiname          : SPS.h
** Datum              : 01.01.2002
** Rev. Nr.		      : 0.1
** Rev. Änderungen	  : siehe Verzeichnis "Standard_Prg" RevNr.xls
**
** Funktion			  : Eingangs- und Ausgangsadressierung, Grundfunktionen
**						wie Maschine Ein/Aus. Luft Ein/Aus etc.,
**						Aufruf des Hauptablaufs und der Stationsabläufe
**
********************************************************************************************************
**
** Projekt            : BM 
**
** Maschinenteil      : SPS
** Programmierer      : 
**
** Programmänderungen : Datum			Name				Bemerkung
**						19.11.2005		Torsten Weber		Programmerstellung, mit Grundprogramm V1.26
**                      04.06.2007      Christoph Hülsmann  Funktionen umgeordnet wg. neuer Ordnerstruktur V2.00
**                      26.11.2007      Christoph Hülsmann  Grundprg. V2.10 >> Zuführung der Grundprogramme
**						09.01.2009		M.van de Wouw		Überarbeitet für Grundprogramm V2.2
**						25.02.2010		A.Pelka				Umbau auf 3/2 Wege Ventile V2.2.02
**
**
********************************************************************************************************/

void Input(void);
void Output(void);
void Stations_Process(void);
void Service_activate(bool activate);
void BDE_Data_Transfer(void);
void ArticleData(void);
void Machine_ON(void);
void Machine_OFF(void);
void Error_MaOff(void);
void Unload_Machine(void);
void General_Error(void);
void Conveyor_OnOff(bool M_ConvReset, bool M_QuitReset);
void EndPositionByStart(void);
void SPS_Programm_Stop(void);
void SPS_Programm_Start(void);
void MachineProcess1();
void MachineProcess2();

#if defined(Scanner_V24) || defined(Scanner_IBS_RS232)
	#include "Scanner.h"
#endif

#include "Bewegungstest.h"

#ifdef GrundprgTest
	#include "Grundprgtest.h"
#endif

#include "SPS_Bibliothek.h"
#include "spsprog.h"
#include "SPS_Sonder.h"

#include "Ibanalog.h"

#include "sps_Antriebe.h"

#include "SBT_V3.h"
#include "sps_sicherheit.h"

#include "stopwatches.h"

#ifdef Log_aktiv
	#include "Laufzeiten.h"
	#include "HDDActivity.h"
#endif

#ifdef Axis_exist	// Achse_vorhanden
	#ifdef DoubleAxis
		#include "St201_SPS_DoppelAchse.h"
	#endif
	#ifdef SingleAxis
		#include "St201_SPS_EinfachAchse.h"
		#include "St201_Kette_EinfachAchse.h"
	#endif
#endif

#ifdef Plate_exist
	#include "St202_SPS_Teller.h"
#endif
 
#ifdef Plate_FU_exist
	#include "St203_SPS_Teller_mit_FU.h"
#endif

#ifdef Plate_Siemens_FU_exist
	#include "St204_SPS_Teller_mit_Siemens_FU.h"
#endif


#ifdef Verstellanschlag_aktiv
	#include "Verstellanschlag.h"
#endif
#ifdef Extraablauf
	#include "Extraablauf.h"
#endif

// Stationsabläufe einbinden
#ifdef Scanner_V24
	#include "Barcodescanner.h"
#endif

#ifdef Scanner_IBS_RS232
	#include "Barcodescanner_IBS_RS232.h"
#endif

#ifdef HVPruefung_vorhanden
	#include "Hochspg.h"
	#include "HV_Pruefung.h"
#endif

#ifdef TCPCOM
  #include "TCPCOM.h"
#endif    

// TODO: Headerdateien der Baugruppen einfügen!
#include "St1_housing_and_cover_insert.h"
#include "St2_check_housing.h"
#include "St3_Carrier_position_checking.h"
#include "St4_insert_pin_MainProcess.h"
#include "St5_pin_pressing.h"
#include "St7_Carrier_position_checking.h"
#include "St8_pressure_test.h"
#include "St9_reject_parts_output.h"
#include "St10_good_parts_output.h"


//*****************************************************************
//*****************  Interbus Eingänge  ***************************
//*****************  Interbus Input     ***************************
//*****************************************************************
void Input(void)
{
// TODO: Eingänge eintragen
	for (WORD i=0; i<=NUMBERSAFETYDOORS; i++)
	{
		SBTMaPart1.E_Door[i] = true;
	}

//##ANF_EINGAENGE      Zeile nicht loeschen			don't delete this line

//-----------------------------------------------------------------
//---------------------------- +SK01A -----------------------------
//-----------------------------------------------------------------
// ******************************
// -A31/A32- /IB IL 24 DI/32
// ******************************
	E_Button_MaOn			                    = Eing(A31, 0);	// -S50.1
	E_Button_MaOff			                    = Eing(A31, 1);	// -S50.2
	E_Button_Quit				                = Eing(A31, 2);	// -S50.3
	E_Button_AirOn			                    = Eing(A31, 3);	// -S50.4
	E_Button_ConveyorOn			                = Eing(A31, 4);	// -S50.5
    E_Button_TipMode				            = Eing(A31, 5);  // -S50.6 Tasterpult
//	Teller[Plate1].E_Motor_SafeTorqueOff       	= Eing(A31, 6);  // 
//	Teller[Plate1].E_Motor_Bereit              	= Eing(A31, 7);
	E_Unload_Machine			                = Eing(A31, 8);						// switch in the cable canal	// Taster im Kabelkanal
  	E_Bridge_StandByPosition		            = Eing(A31, 9);						// switch in the cable canal	// Taster im Kabelkanal
//    E_Button_Quit				                = Eing(A31,10) || E_Button_Quit;	// switch in the cable canal	// -B1 (Taster im Kabel-Kanal)
	E_Button_Only_Axis_Unload	                = Eing(A31,11);
//  frei                                        = Eing(A31,12);	
//  frei                                        = Eing(A31,13);	
//  frei                                        = Eing(A31,14);	
//  frei                                        = Eing(A31,15);

	St4_Coiler->E_Stoerung						= Eing(A32, 0);
	St4_Coiler->E_Freigabe						= Eing(A32, 1);
	E_Button_ProcessObservationMode				= Eing(A32, 2);	// +M-XES5.1AN:2
	St4_Coiler->E_Bereit						= Eing(A32, 3);
//	frei										= Eing(A32, 4);
//	frei										= Eing(A32, 5);
//	frei									    = Eing(A32, 6);	
//	frei										= Eing(A32, 7);	
//	E_St4_B1_Pin_available						= Eing(A32,8);
//	frei										= Eing(A32,9);	
//	E_St8_Peak_Channel1_25N						= Eing(A32,10);	
//	frei										= Eing(A32,11);	
//	frei										= Eing(A32,12);	
//	E_surge_protective_release					= Eing(A32,13);	
	E_PressureSwitch				            = Eing(A32,14); // -S01
//	frei										= Eing(A32,15);
	

// ******************************
// -A33/A34- /IB IL 24 DI/32
// ******************************
//	frei										= Eing(A33,0);
    St4_PositionRad->E_Sammelfehler_low_aktiv	= Eing(A33,1);
	St4_PositionRad->E_Bereit					= Eing(A33,2);
	St4_PositionRad->E_Start_bestaetigt			= Eing(A33,3);
	St4_PositionRad->E_Motion_Complete			= Eing(A33,4);
//	frei										= Eing(A33,5);
//	frei										= Eing(A33,6);
//	frei										= Eing(A33,7);
	SBTMaPart1.E_Door[1]				        = Eing(A33, 8);	// -S401.1
	SBTMaPart1.E_Door[2]				        = Eing(A33, 9);	// -S401.2
	SBTMaPart1.E_Door[3]				        = Eing(A33,10);	// -S401.3
	SBTMaPart1.E_Door[4]				        = Eing(A33,11);	// -S401.4
	SBTMaPart1.E_Door[5]				        = Eing(A33,12);	// -S402.1
	SBTMaPart1.E_Door[6]				        = Eing(A33,13);	// -S402.2
	SBTMaPart1.E_Door[7]				        = Eing(A33,14);	// -S402.3
//	SBTMaPart1.E_Door[8]				        = Eing(A33,15);	// -S402.4

    St4_Ejector->E_Motion_Complete				= Eing(A34,0);
	St4_Ejector->E_Sammelfehler_low_aktiv		= Eing(A34,1);
	St4_Ejector->E_Bereit						= Eing(A34,2);
	St4_Ejector->E_Start_bestaetigt				= Eing(A34,3);
	St4_Inserter->E_Motion_Complete				= Eing(A34,4);
	St4_Inserter->E_Sammelfehler_low_aktiv		= Eing(A34,5);
	St4_Inserter->E_Bereit						= Eing(A34,6);
	St4_Inserter->E_Start_bestaetigt			= Eing(A34,7); 
//	frei										    = Eing(A34,8);
//	frei										    = Eing(A34,9);
//	frei										    = Eing(A34,10);
//	frei										    = Eing(A34,11);
//	frei										    = Eing(A34,12);
//	frei										    = Eing(A34,13);
//	frei										    = Eing(A34,14);
//	frei										    = Eing(A34,15);  

//-----------------------------------------------------------------
//---------------------------- +SK02A -----------------------------
//-----------------------------------------------------------------
// ******************************
// -A41- /IB IL 24 DI/16
// ******************************
#ifdef Axis_exist
	Achse[Axis1].E_Controller_OK				    = Eing(A42,0); // -A201.1/27
	Achse[Axis1].E_Motor_stand					    = Eing(A42,1); // -A201.1/25
	E_Axis1_Controller_STO_Active					= Eing(A42,2); // -A201.1/9  //PHX add this for STO function????? 04.08.2014
	Achse[Axis1].E_Pos_StopPosition				    = Eing(A42,4); // +201-B1
	Achse[Axis1].E_Neg_StopPosition				    = Eing(A42,5); // +201-B2
	Achse[Axis1].E_Ref_Switch						= Eing(A42,6); // +201-B3
	E_St201_B4_WPC_InPosition					    = Eing(A42,7); // +201-B4

	Achse[Axis2].E_Controller_OK				    = Eing(A42,8); // -A1.1/27
	Achse[Axis2].E_Motor_stand					    = Eing(A42,9); // -A1.1/25
	E_Axis2_Controller_STO_Active				    = Eing(A42,10); // -A1.1/9  //PHX add this for STO function????? 04.08.2014
//	frei										    = Eing(A42,11);
//	Achse[Axis2].E_Pos_StopPosition				    = Eing(A42,12); // +1-B10
//	Achse[Axis2].E_Neg_StopPosition				    = Eing(A42,13); // +1-B11
	Achse[Axis2].E_Ref_Switch						= Eing(A42,3); // +8-B2
#endif


#ifdef Scanner_IBS_RS232
	bReadData[0] = EingByte (Scanner_RS232,8);
	bReadData[1] = EingByte (Scanner_RS232,0);
	bReadData[2] = EingByte (Scanner_RS232+1,8);
	bReadData[3] = EingByte (Scanner_RS232+1,0);
	bReadData[4] = EingByte (Scanner_RS232+2,8);
	bReadData[5] = EingByte (Scanner_RS232+2,0);
	bReadData[6] = EingByte (Scanner_RS232+3,8);
	bReadData[7] = EingByte (Scanner_RS232+3,0);
	bReadData[8] = EingByte (Scanner_RS232+4,8);
	bReadData[9] = EingByte (Scanner_RS232+4,0);
	bReadData[10] = EingByte (Scanner_RS232+5,8);
	bReadData[11] = EingByte (Scanner_RS232+5,0);
#endif

//-----------------------------------------------------------------
//------------------------------ +M -------------------------------
//-----------------------------------------------------------------
// *************************
// -A50- /FLS IB M12 DI 8 
// *************************	
//	frei											= Eing(A50,0);
//	frei											= Eing(A50,1);
//	frei									        = Eing(A50,2);
//	frei											= Eing(A50,3);
//	frei											= Eing(A50,4);
//	frei											= Eing(A50,5);
//	frei									        = Eing(A50,6);
//	frei											= Eing(A50,7);

// *************************
// -A51- /FLS IB M12 DI 8 
// *************************
	E_St4_B1_4_Belt_crushing_in_front				= Eing(A51,0);
	E_St4_B1_2_Belt_crushing_back					= Eing(A51,1);
	E_St1_B1_4_housing_presser_in_front			 	= Eing(A51,2);
	E_St1_B1_2_housing_presser_back					= Eing(A51,3);
	E_St1_B3_4_fixture_presser2_down				= Eing(A51,4);
	E_St1_B3_2_fixture_presser2_up				    = Eing(A51,5);
	E_St1_B2_4_fixture_presser1_down				= Eing(A51,6);
	E_St1_B2_2_fixture_presser1_up					= Eing(A51,7);

// *************************
// -A52- /FLS IB M12 DI 8 
// *************************
	E_St10_B2_4_fixture_presser1_down				= Eing(A52,0);
	E_St10_B2_2_fixture_presser1_up					= Eing(A52,1);
	E_St10_B3_4_fixture_presser2_down				= Eing(A52,2);
	E_St10_B3_2_fixture_presser2_up					= Eing(A52,3);
	E_St9_B2_4_fixture_presser1_down			 	= Eing(A52,4);
	E_St9_B2_2_fixture_presser1_up					= Eing(A52,5);
	E_St9_B3_4_fixture_presser2_down				= Eing(A52,6);
	E_St9_B3_2_fixture_presser2_up				    = Eing(A52,7);

// *************************
// -A53- /FLS IB M12 DI 8 
// *************************
	E_St10_B1_4_good_parts_ejector_in_front		    = Eing(A53,0);
	E_St10_B1_2_good_parts_ejector_back			    = Eing(A53,1);
	E_St9_B1_4_reject_parts_ejector_in_front	 	= Eing(A53,2);
	E_St9_B1_2_reject_parts_ejector_back			= Eing(A53,3);
	E_St5_B1_4_pin_presser_down					 	= Eing(A53,4);
	E_St5_B1_2_pin_presser_up						= Eing(A53,5);
//	frei											= Eing(A53,6);
//	frei											= Eing(A53,7);

//***************************************
// -A108- /FLS IB M12 DIO 4/4 (US2/US3)
// **************************************
	E_St4_B2_Ejector_back							= Eing(A34,8);
	E_St4_B3_Inserter_up		                    = Eing(A34,9);
	E_St4_B5_rapid_clamping_system_closed		    = Eing(A108,2);
	E_St4_B1_Pin_available						    = Eing(A108,3);
//	frei											= Eing(A108,4);
//	frei											= Eing(A108,5);
//	frei											= Eing(A108,7);

//***************************************
// -A109- /FLS IB M12 DIO 4/4 (US2/US3)
// **************************************
	E_St1_B1_housing_in_position					= Eing(A109,0);
	E_St1_B2_housing_channel_empty					= Eing(A109,1);
	E_St1_B3_housing_channel_full			        = Eing(A109,2);
//	frei											= Eing(A109,3);

// *************************
// -A110- /FLS IB M12 DI 8 
// *************************
	E_St7_B1_fixture_checking					    = Eing(A110,0);
	E_St2_B2_housing_checking					    = Eing(A110,1);
	E_St2_B1_housing_flange_checking				= Eing(A110,2);
//	frei										    = Eing(A110,3);
//	frei										    = Eing(A110,4);
	E_St3_B1_fixture_checking					    = Eing(A110,5);
	E_St4_B4_Inserter_down_bus						= Eing(A110,6);
	E_St4_B6_Inserter_down							= Eing(A110,7);

// *************************
// -A111- /FLS IB M12 DI 8 
// *************************
	//	frei									    = Eing(A111,0);
	//	frei									    = Eing(A111,1);
	//	frei									    = Eing(A111,2);
	//	frei									    = Eing(A111,3);
//	E_St201_B1_4_SwivelUnit_in_front			    = Eing(A111,4); // +201-B1/4
//	E_St201_B1_2_SwivelUnit_back				    = Eing(A111,5); // +201-B1/2

// *************************
// -A114- /FLS IB M12 DI 8 
// *************************
//	frei										    = Eing(A114,0);
//	frei										    = Eing(A114,1);
//	frei										    = Eing(A114,2);
// 	E_St302_B1_FB_voll								= Eing(A114,3); // +302-B1
//	frei										    = Eing(A114,4);
//	frei										    = Eing(A114,5);
//	frei										    = Eing(A114,6);
//	frei										    = Eing(A114,7);

// **************************************
// -A120- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************

//	frei                                            = Eing(A120,2);
//	frei                                            = Eing(A120,3);
//	E_St301_B2_AxisProtector_in_front				= Eing(A120,2); // +301-B2
//	E_St301_B3_AxisProtector_in_front				= Eing(A120,3); // +301-B3

	E_St201_B1_4_SwivelUnit_in_front			    = Eing(A121,0); // +201-B1/4
	E_St201_B1_2_SwivelUnit_back				    = Eing(A121,1); // +201-B1/2

//##END_EINGAENGE      Zeile nicht loeschen		don't delete this line


#ifdef Camera_Pipe_exist
// TODO: Eingaenge von der Kamera prüfen
// Pipe-Übergaben zum Kamerarechner 1
	E_Kamera_fertig[1]			= Kameradaten_E[KameraPC_1].Fertigmeldung_Kamera1;
	E_Kamera_Gutmeldung[1]		= Kameradaten_E[KameraPC_1].Gutmeldung_Kamera1;
	E_Kamera_Beleuchtung_OK[1]	= Kameradaten_E[KameraPC_1].Beleuchtung_Kamera1_ok;
	E_Kamera_Beleuchtung_ein[1]	= Kameradaten_E[KameraPC_1].Beleuchtung_Kamera1_ein;

	E_Kameraprogramm_RUN[KameraPC_1]		= Kameradaten_E[KameraPC_1].Kameraprogramm_laeuft;
#endif//#ifdef Camera_Pipe_exist



//TODO: Zuweisen der Zylindervariablen, die als Bewegungstest dienen sollen
//		Assign to the cylinder variable who should serve as a movement test

//	E_MovingTest_in_front[1]	= E_St3_B5_4_WT_Oeffner_vorne;
//	E_MovingTest_back[1]		= E_St3_B5_2_WT_Oeffner_hinten;


}

//*****************************************************************
//******************  Interbus Ausgänge  **************************
//******************  Interbus Output    **************************
//*****************************************************************
void Output(void)
{
// TODO: Ausgänge eintragen

//##ANF_AUSGAENGE      Zeile nicht loeschen			don't delete this line


//-----------------------------------------------------------------
//------------------------------ +M -------------------------------
//-----------------------------------------------------------------

// ----------------- Station 1 --------------------

if (!M_Error_Air_Off[1])
{
	SetAusg(A1,0,A.St4_Y1_4_Belt_crushing_forward);
	SetAusg(A1,1,A.St4_Y1_2_Belt_crushing_backward);
	SetAusg(A1,2,A.St1_Y1_4_housing_presser_forward);	
	SetAusg(A1,3,A.St1_Y1_2_housing_presser_backward);
	SetAusg(A1,4,A.St1_Y3_4_fixture_presser2_downward);
	SetAusg(A1,5,A.St1_Y3_2_fixture_presser2_upward);
	SetAusg(A1,6,A.St1_Y2_4_fixture_presser1_downward);
	SetAusg(A1,7,A.St1_Y2_2_fixture_presser1_upward);
	SetAusg(A1,8,false);
	SetAusg(A1,9,false);
	SetAusg(A1,10,false);
	SetAusg(A1,11,false);
	SetAusg(A1,12,false);
	SetAusg(A1,13,false);
	SetAusg(A1,14,false);
	SetAusg(A1,15,false);
}
else
{
	SetAusg (A1,0,false);
	SetAusg (A1,1,false);
	SetAusg (A1,2,false);
	SetAusg (A1,3,false);
	SetAusg (A1,4,false);
	SetAusg (A1,5,false);
	SetAusg (A1,6,false);
	SetAusg (A1,7,false);
	SetAusg (A1,8,false);
	SetAusg (A1,9,false);
	SetAusg (A1,10,false);
	SetAusg (A1,11,false);
	SetAusg (A1,12,false);
	SetAusg (A1,13,false);
	SetAusg (A1,14,false);
	SetAusg (A1,15,false);
}

if (!M_Error_Air_Off[2])
{
	SetAusg(A2,0,A.St10_Y1_4_good_parts_ejector_forward);
	SetAusg(A2,1,A.St10_Y1_2_good_parts_ejector_backward);
	SetAusg(A2,2,A.St9_Y1_4_reject_parts_ejector_forward);	
	SetAusg(A2,3,A.St9_Y1_2_reject_parts_ejector_backward);
	SetAusg(A2,4,A.St5_Y1_4_pin_presser_downward);
	SetAusg(A2,5,A.St5_Y1_2_pin_presser_upward);
	SetAusg(A2,6,false);
	SetAusg(A2,7,false);
	SetAusg(A2,8,A.St10_Y2_4_fixture_presser1_downward);
	SetAusg(A2,9,A.St10_Y2_2_fixture_presser1_upward);
	SetAusg(A2,10,A.St10_Y3_4_fixture_presser2_downward);	
	SetAusg(A2,11,A.St10_Y3_2_fixture_presser2_upward);
	SetAusg(A2,12,A.St9_Y2_4_fixture_presser1_downward);
	SetAusg(A2,13,A.St9_Y2_2_fixture_presser1_upward);
	SetAusg(A2,14,A.St9_Y3_4_fixture_presser2_downward);
	SetAusg(A2,15,A.St9_Y3_2_fixture_presser2_upward);
}
else
{
	SetAusg (A2,0,false);
	SetAusg (A2,1,false);
	SetAusg (A2,2,false);
	SetAusg (A2,3,false);
	SetAusg (A2,4,false);
	SetAusg (A2,5,false);
	SetAusg (A2,6,false);
	SetAusg (A2,7,false);
	SetAusg (A2,8,false);
	SetAusg (A2,9,false);
	SetAusg (A2,10,false);
	SetAusg (A2,11,false);
	SetAusg (A2,12,false);
	SetAusg (A2,13,false);
	SetAusg (A2,14,false);
	SetAusg (A2,15,false);
}

//***************************************
// -A109- /FLS IB M12 DIO 4/4 (US2/US3)
// **************************************
	SetAusg(A109,0,A_St1_A1_bowl_feeder);
	SetAusg(A109,1,A_St1_A2_linear_feeder);
	SetAusg(A109,2,A_St1_A3_linear_feeder);
	SetAusg(A109,3,A_St1_Y1_blowing_air_for_feeder);

// **************************************
// -A120- /FLS IB M12 DO 8 (US2/US3)
// **************************************

#ifdef Axis_exist

	if (!M_Error_Air_Off[201])
	{
		SetAusg(A120,4,A.St201_Y1_4_SwivelUnit_forward);
		SetAusg(A120,5,A.St201_Y1_2_SwivelUnit_backward);
	}
	else
	{
		SetAusg (A120,4,false);	
		SetAusg (A120,5,false);
	}

	SetAusg(A120,3,A_MainAir[201]);

#endif

	SetAusg(A120,0,A_MainAir[1]);
	SetAusg(A120,1,A_MainAir[2]);

// **************************************
// -A110- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************
    //SetAusg(A110,0,A_St3_A1_Enable_BF);        
    //SetAusg(A110,1,A_St3_A2_Enable_LC);        
    //SetAusg(A110,2,frei);         
    //SetAusg(A110,3,frei);      

// *************************
// -A147- /FLS IB M12 DO 8 Hauplüfte
// *************************
   //SetAusg(A147,0,A_MainAir[1]);
   //SetAusg(A147,1,A_MainAir[2]);
   ////SetAusg(A147,2,frei);				        
   ////SetAusg(A147,3,frei);				        			       
   ////SetAusg(A147,4,frei);				        
   ////SetAusg(A147,5,frei);				        
   ////SetAusg(A147,6,frei);				        
   // SetAusg(A141,7,A_St302_Y1_WT_abblasen);

//-----------------------------------------------------------------
//---------------------------- +SK01A -----------------------------
//-----------------------------------------------------------------
// ***********************************
// -A151/A152- /IB IL 24 DO/32 (US1)
// ***********************************
	SetAusg(A151,0,A_LED_MaOn);				// +PULT1-HO1:X1
	SetAusg(A151,1,A_LED_MaOff);		    // +PULT1-HO2:X1
	SetAusg(A151,2,A_LED_Quit);				// +PULT1-HO3:X1
	SetAusg(A151,3,A_LED_AirOn);		    // +PULT1-HO4:X1
	SetAusg(A151,4,A_LED_ConveyorOn);		// +PULT1-HO5:X1
	SetAusg(A151,5,A_LED_TipMode); // 
	SetAusg(A151,6,A_St4_Start_Coiler); 
	SetAusg(A151,7,A_St4_Controller_On_Coiler);
	SetAusg(A151,8,A_LED_Unload_Machine);          // LED für Taster im Kabelkanal
	SetAusg(A151,9,A_LED_Bridge_StandByPosition);  // LED für Taster im Kabelkanal
	SetAusg(A151,10,A_LED_Quit);               // LED für Taster im Kabelkanal
	SetAusg(A151,11,A_LED_Only_Axis_Unload);
//  SetAusg(A151,12,frei);
//	SetAusg(A151,13,SBTMaPart1.A_KeepClosed_SafetyDoors);
//	SetAusg(A151,14,frei);
//	SetAusg(A151,15,frei);

	// GATEWAY to following SPS		    // GATEWAY AN FOLGENDE SPS

	SetAusg(A152,8,A_St201_M2_Enable_WPC_accelerator); //+201 - M2
	SetAusg(A152,9,A_St201_M2_Paramtersatz_1); //+201 - M2
	SetAusg(A152,10,A_St201_M2_Paramtersatz_2); //+201 - M2
	SetAusg(A152,11,A_St201_M2_Paramtersatz_3); //+201 - M2
	SetAusg(A152,12,A_St201_M2_Paramtersatz_4); //+201 - M2
	SetAusg(A152,13,A_St8_Range_Channel_1);
//	SetAusg(A152,14,frei);
//	SetAusg(A152,15,frei);

// **********************************
// -A153/A154/A155/A156- /IB IL 24 DO/32 (US1)
// **********************************

	//WPC
	SetAusg(A154,0,A_St201_M3_Enable_WPC_accelerator); //+201 - M3
	SetAusg(A154,1,A_St201_M3_Paramtersatz_1); //+201 - M3
	SetAusg(A154,2,A_St201_M3_Paramtersatz_2); //+201 - M3
	SetAusg(A154,3,A_St201_M3_Paramtersatz_3); //+201 - M3
	SetAusg(A154,4,A_St201_M3_Paramtersatz_4); //+201 - M3

	//A1
	SetAusg(A154,5,St4_Ejector->A_Modusumschaltung); 
	SetAusg(A154,6,St4_Ejector->A_Satzselektion_4);
	SetAusg(A154,7,St4_Ejector->A_Satzselektion_1);
	SetAusg(A154,8,St4_Ejector->A_Satzselektion_3);
	SetAusg(A154,9,St4_Ejector->A_Reglerfreigabe); 
	SetAusg(A154,10,St4_Ejector->A_Stopp); 
	SetAusg(A154,11,St4_Ejector->A_Satzselektion_5);
	SetAusg(A154,12,St4_Ejector->A_Satzselektion_0);
	SetAusg(A154,13,St4_Ejector->A_Satzselektion_2);
	SetAusg(A154,14,St4_Ejector->A_Endstufenfreigabe);
	SetAusg(A154,15,St4_Ejector->A_Start_Satzausfuehrung);

	//
	SetAusg(A153,0,St4_Inserter->A_Modusumschaltung); 
	SetAusg(A153,1,St4_Inserter->A_Satzselektion_4);
	SetAusg(A153,2,St4_Inserter->A_Satzselektion_1);
	SetAusg(A153,3,St4_Inserter->A_Satzselektion_3);
	SetAusg(A153,4,St4_Inserter->A_Reglerfreigabe); 
	SetAusg(A153,5,St4_Inserter->A_Stopp); 
	SetAusg(A153,6,St4_Inserter->A_Satzselektion_5);
	SetAusg(A153,7,St4_Inserter->A_Satzselektion_0);
	SetAusg(A153,8,St4_Inserter->A_Satzselektion_2);
	SetAusg(A153,9,St4_Inserter->A_Endstufenfreigabe);
	SetAusg(A153,10,St4_Inserter->A_Start_Satzausfuehrung);

	//
	SetAusg(A156,0,St4_PositionRad->A_Modusumschaltung); 
	SetAusg(A156,1,St4_PositionRad->A_Satzselektion_4);
	SetAusg(A156,2,St4_PositionRad->A_Satzselektion_1);
	SetAusg(A156,3,St4_PositionRad->A_Satzselektion_3);
	SetAusg(A156,4,St4_PositionRad->A_Reglerfreigabe); 
//	SetAusg(A156,5,); 
	SetAusg(A156,6,St4_PositionRad->A_Stopp); 
	SetAusg(A156,7,St4_PositionRad->A_Satzselektion_5);
	SetAusg(A156,8,St4_PositionRad->A_Satzselektion_0);
	SetAusg(A156,9,St4_PositionRad->A_Satzselektion_2);
	SetAusg(A156,10,St4_PositionRad->A_Endstufenfreigabe);
	SetAusg(A156,11,St4_PositionRad->A_Start_Satzausfuehrung && E_St4_B2_Ejector_back);

//-----------------------------------------------------------------
//---------------------------- +SK02A -----------------------------
//-----------------------------------------------------------------

// ******************************
// -A157- /IB IL 24 DO/8 (US1)
// ******************************
#ifdef Axis_exist
	SetAusg(A157,0,Achse[Axis1].A_Freigabe_Servo);		//-A201.1/16
	SetAusg(A157,1,Achse[Axis1].A_Reset_Servo);			//-A201.1/17
	SetAusg(A157,2,Achse[Axis2].A_Freigabe_Servo);		//-A1.1/16
	SetAusg(A157,3,Achse[Axis2].A_Reset_Servo);			//-A1.1/17
#endif
    
	SetAusg(A157,6,A_St301_A1_FlexLink_slow);
	SetAusg(A157,7,A_St301_A1_FlexLink_fast);
//	SetAusg(A155,2,A_St302_A1_FlexLink_Enable);     // +302-K5  enable connecting conveyor belt		(Freig. Verbindungsfoerderband)

 // ******************************
 // -A191- /IB IL 24 DO/4  (US3)
 // ******************************
	SetAusg(A191,0,A_St1_M1_release_conveyor_belt);         // +1-M1
	SetAusg(A152,1,St4_Coiler->A_Freigabe);         // +4-Coiler enable
    
 // ******************************
 // -A195- /IB IL 24 DO/4  (US3)
 // ******************************
    //SetAusg(A195,0,A_St301_A1_FlexLink_Enable);         // +301-A1/K15	enable Flex Link conveyor belt	(Freig. Umlauffoerderband)   
	///SetAusg(A195,1,A_St201_M2_Enable_WPC_accelerator);  // +201-M2/K1
	//SetAusg(A195,2,A_St201_M3_Enable_WPC_accelerator);  // +201-M3/K1
//	SetAusg(A195,3,frei);

// ******************************
// Barcode Scanner
// ******************************
#ifdef Scanner_IBS_RS232
	SetAusgByte(Scanner_RS232,8,bSendData[0]);
	SetAusgByte(Scanner_RS232,0,bSendData[1]);
	SetAusgByte(Scanner_RS232+1,8,bSendData[2]);
	SetAusgByte(Scanner_RS232+1,0,bSendData[3]);
	SetAusgByte(Scanner_RS232+2,8,bSendData[4]);
	SetAusgByte(Scanner_RS232+2,0,bSendData[5]);
	SetAusgByte(Scanner_RS232+3,8,bSendData[6]);
	SetAusgByte(Scanner_RS232+3,0,bSendData[7]);
	SetAusgByte(Scanner_RS232+4,8,bSendData[8]);
	SetAusgByte(Scanner_RS232+4,0,bSendData[9]);
	SetAusgByte(Scanner_RS232+5,8,bSendData[10]);
	SetAusgByte(Scanner_RS232+5,0,bSendData[11]);
#endif


//##END_AUSGAENGE     Zeile nicht loeschen		don't delete this line

#ifdef Camera_Pipe_exist	
// TODO: Ausgaenge zur Kamera prüfen
// Pipe-Übergaben zum Kamerarechner 1
	Kameradaten_A[KameraPC_1].Start1_Kamera1			= A_Start_Sig1_Kamera[1];
	Kameradaten_A[KameraPC_1].Start2_Kamera1			= A_Start_Sig2_Kamera[1];
	Kameradaten_A[KameraPC_1].Blockbeginn_Kamera1		= A_Blockbeginn_Kamera[1];
	Kameradaten_A[KameraPC_1].Beleuchtung_ein_Kamera1	= A_Beleuchtung_einschalten_Kamera[1];
	Kameradaten_A[KameraPC_1].Stat_Kamera1_eingeschaltet= A_Kamera_ein[1];

	Kameradaten_A[KameraPC_1].Programm_beenden			= A_PRG_beenden;
	Kameradaten_A[KameraPC_1].Interbus_laeuft			= M_.IBS_RUN && Kameradaten_E[KameraPC_1].Kameraprogramm_laeuft;

	// StartSignale der angegebenen Kameras werden zusammen übergeben
	// Übergabe 1 => Startmerker Kameraschrittkette 1 (M.Start[K_StxKamera...]
	// Übergabe 2 => Startmerker Kameraschrittkette 2 (M.Start[K_StxKamera...]
	// Übergabe 3 => Startmerker Kameraschrittkette 3 (M.Start[K_StxKamera...]
	// Übergabe 4 => Startmerker Kameraschrittkette 4 (M.Start[K_StxKamera...]
	// Überbage 5 => Nr. des Kamera PC angeben
	// Wird eine NULL eingetragen so wird diese Kamera nicht berücksichtigt, der Start erfogt wie gehabt

// TODO: Kamera Startsignale eintragen
	if (!StartSignale_der_Kameras_vorhanden	( 0
											, 0
											, 0
											, 0
											, KameraPC_1))
	{
		Kameradaten_A[KameraPC_1].Start1_Kamera1 = false;
		Kameradaten_A[KameraPC_1].Start2_Kamera1 = false;
		Kameradaten_A[KameraPC_1].Blockbeginn_Kamera1 = false;
	}

	Kamera_PIPE_Sendesdaten_Eintragen(KameraPC_1);
#endif//#ifdef Camera_Pipe_exist
}

//*****************************************************************
//********************  Stationen Ablauf  ************************* 
//*****************************************************************
void  Stations_Process(void)
{

//  Stationen an der Achse
#ifdef Scanner_V24
/* TODO: Einstellungen des Scanners kontrollieren!
    Übergabewert 1 (WORD) AxisNum                       // Axis Number													// AxisNum.
    Übergabewert 2 (WORD) ErrorNum                     // Error Number													// FehlerBereich
    Übergabewert 3 (WORD) COM                          // Serial interface												// Serielle Schnittstelle
    Übergabewert 4 (WORD) Nestposition 				   // WPC Position where the scanner writh in the shift register	// Nestposition, wo der Scanner in das Schieberegister einträgt
    Übergabewert 5 (BOOL) nur_Nestnummer_eintragen     // only WPC Number , or shift register values writh?				// nur Nestnummer, oder auch Schieberegisterwerte eintragen?
    Übergabewert 6 (BOOL) Nestfreigabe_abfragen        // WPC enable request or ignore									// Nestfreigabe abfragen oder ignorieren
    Übergabewert 7 (bool) E_NestEingelaufen            // Input for WPC worn in the Axis								// Eingang für Nest eingelaufen an der Achse

*/
    if (    MACHINETYPE == FIRST_MG
        ||  MACHINETYPE == SINGLE_MG )
    {
        Barcodescanner(Axis1, 390, COM2, 0, true, true, E_St201_B4_WPC_InPosition );
    }

    if (    MACHINETYPE == MIDDLE_MG
        ||  MACHINETYPE == LAST_MG )
    {
        Barcodescanner(Axis1, 390, COM2, 0, false, true, E_St201_B4_WPC_InPosition );
    }
#endif


#ifdef Scanner_IBS_RS232
/* TODO: Einstellungen des Scanners kontrollieren!
    Übergabewert 1 (WORD) AxisNum                       // Axis Number													// AxisNum.
    Übergabewert 2 (WORD) ErrorNum                     // Error Number													// FehlerBereich
    Übergabewert 3 (WORD) Nestposition 				   // WPC Position where the scanner writh in the shift register	// Nestposition, wo der Scanner in das Schieberegister einträgt
    Übergabewert 4 (BOOL) nur_Nestnummer_eintragen     // only WPC Number , or shift register values writh?				// nur Nestnummer, oder auch Schieberegisterwerte eintragen?
    Übergabewert 5 (BOOL) Nestfreigabe_abfragen        // WPC enable request or ignore									// Nestfreigabe abfragen oder ignorieren
    Übergabewert 6 (bool) E_NestEingelaufen            // Input for WPC worn in the Axis								// Eingang für Nest eingelaufen an der Achse

*/
    if (    MACHINETYPE == FIRST_MG
        ||  MACHINETYPE == SINGLE_MG )
    {
        Barcodescanner_IBS_RS232(Axis1, 390, 0, true, false, E_St201_B4_WPC_InPosition );
    }

    if (    MACHINETYPE == MIDDLE_MG
        ||  MACHINETYPE == LAST_MG )
    {
        Barcodescanner_IBS_RS232(Axis1, 390, 0, false, false, E_St201_B4_WPC_InPosition );
    }
#endif


#ifdef HVPruefung_vorhanden
	if (!Kalibrierung[HV1].Kalibrierung_Aktiv)
		Step[K_HV_Kalibrierung] = 0;
	PC_Message[19] = (bool)Kalibrierung[HV1].Kalibrierung_Aktiv;	// F#1.494 Achtung!
															// K#1.494 Hochspannung ist eingeschaltet!
															// K#1.494 Kalibrierung ist aktiviert!
#endif

#ifdef HVPruefung_vorhanden
	if (!Kalibrierung[HV1].Kalibrierung_Aktiv)
	{
#endif

// ************************************
//        Baugruppen ohne Teile
//		  Stations without material
// ************************************

	if (PosFlanke(Fl_PosWithoutMaterial, M_.All_Stations_without_material ))
	{
		M_.St1_without_material = true;
		M_.St2_without_material = true;
		M_.St3_without_material = true;
		M_.St4_without_material = true;
		M_.St5_without_material = true;
		M_.St7_without_material = true;
		M_.St8_without_material = true;
		M_.St9_without_material = true;
		M_.St10_without_material = true;

	}
	if (NegFlanke(Fl_NegWithoutMaterial , M_.All_Stations_without_material ))
	{
		M_.St1_without_material = false;
		M_.St2_without_material = false;
		M_.St3_without_material = false;
		M_.St4_without_material = false;
		M_.St5_without_material = false;
		M_.St7_without_material = false;
		M_.St8_without_material = false;
		M_.St9_without_material = false;
		M_.St10_without_material = false;
		ArticleData();
	}

    PC_Message[5] = M_.All_Stations_without_material ;


// ************************************
// TODO: Stationsaufrufe eintragen!
// ************************************

St1_housing_and_cover_insert	( K_St1_housing_and_cover_insert	// Sequence
								, 10								// Start of error range of this function
								, 1									// Valve terminal is to be switched off in case of failure
								, DriveUnit1						// DriveUnitNum
								, 1									// Station number of BDE
								, 1									// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);

St2_check_housing				( K_St2_check_housing		// Sequence
								, 30						// Start of error range of this function
								, DriveUnit1				// DriveUnitNum
								, 2							// Station number of BDE
								, 2							// Register of the station
								, false						// Setup phase conveyors and StandBy are deactivated
								);

St3_Carrier_position_checking	( K_St3_Carrier_position_checking		// Sequence
								, 40						// Start of error range of this function
								, DriveUnit1				// DriveUnitNum
								, 3							// Station number of BDE
								, 3							// Register of the station
								, false						// Setup phase conveyors and StandBy are deactivated
								);

St4_insert_pin_main		(  K_St4_MainProcess		// Step Pin insert				//Schrittkette Stift einsetzen
					, K_St4_PositionRad		// Step Motor PositionRad		//Schrittkette Motorsteuerung Positionierrad
					, K_St4_EjectorPin		// Step Motor Motor Ejector		//Schrittkette Motorsteuerung Ausdruecker
					, K_St4_InsertPin		// Step Motor Inserter			//Schrittkette Motorsteuerung Eindruecker
					, K_St4_CuttingBelt		// Step Cutting belt			//Schrittkette der Stanze
					, 50					// Start 1 Error number for this funktion		//Start des 1.Fehlerbereichs für diese Funktion
					, 50					// Start 2 Error number for this funktion		//Start des 2.Fehlerbereichs für diese Funktion
					, 70					// Start 3 Error number for this funktion		//Start des 3.Fehlerbereichs für diese Funktion
					, 80					// Start Error number for Festo PositionRad	//Start des Fehlerbereichs für Festo Positionierrad
					, 90					// Start Error number for Festo	Ejector			//Start des Fehlerbereichs für Festo Ausdruecker
					, 100					// Start Error number for Festo Inserter		//Start des Fehlerbereichs für Festo Eindruecker
					, DriveUnit1			// AntriebsNr
              //      , Extra4				// Specialfunction for digital inputs			//Extrafunktion für Digital Eingang
            //        , Extra5				// Specialfunction for digital inputs			//Extrafunktion für Digital Eingang
					, 4						// Station in BDE								//StationsNr von BDE
					, 4						// registerposition for this station			//RegisterStelle für die Station
					, 22					// Checking fault "Pin not separatet"			//Prueffehler "Stift nicht vereinzelt"
					, 1						// MainAir should be switched off by Error		//Ventilinsel die bei Stoerung ausgeschaltet werden soll
					, M_.St4_without_material	// setup phase conveyors and StandBy are deactivated	//Einrichtphase Foerdergeraete und StandBy werden deaktiviert
												// 01_alternation and part in position are ignored		//01-Wechsel und Teil in Position werden ignoriert
					);

St5_Pin_pressing	( K_St5_Pin_pressing	// Sequence
					, 110					// Start of error range of this function
					, 2     				// Valve terminal is to be switched off in case of failure
					, DriveUnit1			// DriveUnitNum
					, 5  					// Station number of BDE
					, 5						// Register of the station
					);

St7_Carrier_position_checking	( K_St7_Carrier_position_checking		// Sequence
								, 120						// Start of error range of this function
								, DriveUnit1				// DriveUnitNum
								, 7							// Station number of BDE
								, 7							// Register of the station
								, false						// Setup phase conveyors and StandBy are deactivated
								);

St8_Stiftpruefung		( K_St8_pressure_test	// SchritteSEQ Spender
    	                , 130		            // Start des 1. Fehlerbereichs für diese Funktion
	   	                , 130		            // Start des 1. Fehlerbereichs für diese Funktion
						, 2     				//Air  Ventilinsel die bei Stoerung ausgeschaltet werden soll
			            , DriveUnit1              // DriveUnitNum
		            	, 8		                // StationsNr von BDE
			            , 8                     // RegisterStelle für die Station
		            	, 730	                // Start des Fehlerbereichs für die Servofunktion
						, Axis2                // AchsNr des Pruefers
						, Extra2                // Extrafunktion AnalogwertIn
						, Extra1                // Extrafunktion für Digitalausgang
						, 0                     // benutztes Ausgangsbit der Ausgangskarte
						, 22030                 // Schieberegisterwert der Station für nicht fertig bearbeitete Pole
												// register value of station for not finished pole
						, 12030	                // Grundwert für Ausschussinformation im Register
						, 2010                  // Wert im Schieberegister für GoodPole
						, 1                     // Prüffehler: max. zul. Prüfdruck überschritten
						, 2                     // Prüffehler: Prüfdruck nicht erreicht
						, 3                     // Prüffehler: max. Ausdrückweg überschritten
						, 4                     // Prüffehler: Kraft an falscher Position aufgetreten
						, M_.St8_without_material					// Einrichtphase
			             );

St9_reject_parts_output			( K_St9_reject_parts_output			// Sequence
								, 140								// Start of error range of this function
								, 2									// Valve terminal is to be switched off in case of failure
								, DriveUnit1						// DriveUnitNum
								, 9								// Station number of BDE
								, 9								// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);

St10_good_parts_output			( K_St10_good_parts_output			// Sequence
								, 150								// Start of error range of this function
								, 2									// Valve terminal is to be switched off in case of failure
								, DriveUnit1						// DriveUnitNum
								, 10								// Station number of BDE
								, 10								// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);

//**********************************************************************************************************************************
#ifdef HVPruefung_vorhanden
	}
	else
	{
		PC_Warning[0] = false;	// evtl. Stand By Warnung St.1 unterdrücken
		
		DriveUnit[DriveUnit1].DU_ready_for_StandBy = true;
		HV_Kalibrierung(K_HV_Kalibrierung	// Schrittkette
						,DriveUnit1			// DriveUnitNum.
						,HV1				// Nr. der HV Prüfung
						,100				// Start des Zeitwertbereiches (5 Timer werden benötigt)
						);
	}
#endif

	// Stationen_Ablauf
	//if	(	M.Save_RunTime_in_file
	//	||	IFCBIT
	//	)
	//	LaufzeitenSpeichern();

}

//*****************************************************************
//**************** Servicezeit an BDE einschalten *****************
//**************** ServiceTime on BDE switch on   *****************
//*****************************************************************
void Service_activate(bool activate)
{
	if (PosFlanke(Fl_Service_aktivieren, activate))
		PC_Service_aktiv = !PC_Service_aktiv;

	A_LED_Service_aktiv = PC_Service_aktiv && FRQ[2];

	PC_Message[20] = A_LED_Service_aktiv;
}// of void Service_activate(...)

//*****************************************************************
//********************  BDE Daten übergeben  **********************
//********************  Transfer BDE Data    **********************
//*****************************************************************
void BDE_Data_Transfer(void)
{
	// lokale Einstellungen
	WORD i,j;

	static bool Index21_senden			= false;
	static bool Ausschuss_Pol_gefunden	= false;

// TODO: Variablen prüfen
	WORD MaPartNum	= MaPart1;	// Machine Part Number for BDE						// Maschinenteil Nummer für BDE angeben
	WORD RegisterNr = 10;		// Shift Register for BDE - Dates are identify 		//Registerstelle an der die BDE - Daten ermittelt werden

	BYTE DriveUnitNum		= DriveUnit1; 
	WORD NumberOfHousings	= DriveUnit[DriveUnitNum].NumberOfHousings;
	bool Freigabe_senden	= DriveUnit[DriveUnitNum].Enable_DriveUnit;

	static CTimer *tmSaveProductionData = new CTimer(3600000);
	tmSaveProductionData->SetTimerBusy(true);

	// BDE - Daten holen nach Dateifehler
	if (IFCBIT && !M.Marker_ok) PC_NewData = true;

	// can be activated by both parts	???		// Kann von beiden Teilen aktiviert werden
	PC_SingleStep				= (MaDatum[MaPartNum].NeuStat & cEinzel)>0;
	PC_Unload					= (MaDatum[MaPartNum].NeuStat & cLeerfahren)>0;
	PC_Machine_Off				= (MaDatum[MaPartNum].NeuStat & cMaAus)>0;
	PC_delete_Register			= (MaDatum[MaPartNum].NeuStat & cRegClear)>0;
	PC_Reprocess_reject_Parts	= (MaDatum[MaPartNum].NeuStat & cAusEin)>0;
	PC_exit_Program				= (MaDatum[MaPartNum].NeuStat & cPrgBeenden)>0;
	PC_Quantity_reached			= (MaDatum[MaPartNum].NeuStat & cStueckzahl)>0;

	MaDatum[MaPartNum].NeuStat = 0;

// --------  Sonderfunktionstasten von BDE erfassen  ----------
// --------  realize the special function button of BDE  ----------

// ---  Die 16 Funktionstasten sind durch cSonder1 - cSonder16 maskierbar
// ---  und können in der Fehler.txt durch Eingabe von
// ---  SCH#1.1 TEXT -> SCH# Maschinenteil1.Funktionstaste1 + TEXT
// ---  festgelegt werden.

/*
// TODO: Sonderfunktionen eintragen?

//-----------------------------------------------------
//---------- Beispiele fuer Sonderfunktionen ----------
//------------ "Example" special function -------------
//-----------------------------------------------------
//----------------- Sonderfunktion  1 -----------------
//---------------- special function  1 ----------------
//-----------------------------------------------------
// Die Variable M.Nester_wechseln wird NUR von der
// Sonderfunktion vom BDE gesteuert

// The variable M.Nester_wechseln  ONLY from that
// special function from BDE controlled

	if	(	M_.MaSingleStepMode 
		&& ((MaDatum[MaPartNum].sonderfunktion & cSonder1) > 0)
		)
		M.Nester_wechseln = true;
	else 
		M.Nester_wechseln = false;
	
	SetBit((PLONG)&MaDatum[MaPartNum].sonderfunktion,0,M.Nester_wechseln);

//-----------------------------------------------------
//----------------- Sonderfunktion  2 -----------------
//---------------- special function  2 ----------------
//-----------------------------------------------------
// Die Variable wird von BDE gesetzt und vom Programm wieder zurueckgesetzt
// The variable is put by BDE and is put back by the programme 

	if (PosFlanke(Fl_BDE_Sonder2,(MaDatum[MaPartNum].sonderfunktion & cSonder2) > 0))
		M.Nester_wechseln = true;
	
	SetBit((PLONG)&MaDatum[MaPartNum].sonderfunktion,1,M.Nester_wechseln);

*/
	if (E_Key_311 
	||  M_.without_311_Key		// ohne 311 Schlüssel
	||  SBTMaPart1.E_SingleStepMode)
                                MaDatum[MaPartNum].Status |= cSchluessel;
	else						MaDatum[MaPartNum].Status &= ~cSchluessel;

	if (PC_release_Article)		MaDatum[MaPartNum].Status |= cFreigabe;
	else						MaDatum[MaPartNum].Status &= ~cFreigabe;

	if (!M_.MaRun)				MaDatum[MaPartNum].Status |= cMaAus;
	else						MaDatum[MaPartNum].Status &= ~cMaAus;

	if (M.PC_SingleStepMode 
	|| 	M_.MaSingleStepMode) 	MaDatum[MaPartNum].Status |= cEinzel;
	else						MaDatum[MaPartNum].Status &= ~cEinzel;

	if (!M_.MaOn)				MaDatum[MaPartNum].Status |= cMaHalt;
	else						MaDatum[MaPartNum].Status &= ~cMaHalt;

	if (PC_StandBy)				MaDatum[MaPartNum].Status |= cStandBy;
	else						MaDatum[MaPartNum].Status &= ~cStandBy;

	if (M_.MaError)				MaDatum[MaPartNum].Status |= cStoerung;
	else						MaDatum[MaPartNum].Status &= ~cStoerung;

	if (E_Print_Label)			MaDatum[MaPartNum].Status |= cDrucken;
	else						MaDatum[MaPartNum].Status &= ~cDrucken;

	if (M.Unload_Machine
	||  E_Unload_Machine)  		MaDatum[MaPartNum].Status |= cLeerfahren;
	else						MaDatum[MaPartNum].Status &= ~cLeerfahren;

	if (PC_NewData)				MaDatum[MaPartNum].Status |= cDatenAnf;
	else						MaDatum[MaPartNum].Status &= ~cDatenAnf;

	if (PC_Register0)			MaDatum[MaPartNum].Status |= cRegClear;
	else						MaDatum[MaPartNum].Status &= ~cRegClear;

	if (PC_exit_Program)		MaDatum[MaPartNum].Status |= cPrgBeenden;
	else						MaDatum[MaPartNum].Status &= ~cPrgBeenden;

	if	(PC_Service_aktiv)		MaDatum[MaPartNum].Status |= cServiceAktiv;
	else						MaDatum[MaPartNum].Status &= ~cServiceAktiv;



	MaDatum[MaPartNum].Fehler = Fehlerprg[PRG1].MW_Fehlnum;

	MaDatum[MaPartNum].fehler_index10 = FehlerprgIndex10[PRG1].MW_Fehlnum;

	for (i=0;i<=MAX_WARNING;i++)
		SetBit(&MaDatum[MaPartNum].Warn,i,PC_Warning[i]);

	for (i=0;i<=MAX_MESSAGE;i++)
		SetBit(&MaDatum[MaPartNum].Meld,i,PC_Message[i]);

/*	---------------------------------------------------------------------------------------

		Erläuterung der Registereinträge
		Es werden immer 5 stellige Nummern vergeben die sich wie folgt aufschlüsseln lassen

		Explanation of the register entries
		Always 5 numbers assigned can be broken down as follows

/*	---------------------------------------------------------------------------------------


	Guteil / Pol				Maschinenteil			Station				Prüffehler	
	Goodpart / Pole				Machinepart				Station				Check error

		0						  0 bis 9			    01 bis 99		        0
  
	Ausschussteil / Pol
	Rejektpart /Pole

		1						  0 bis 9			    01 bis 99		      0 bis 9

	Leertakt
	Emptycycle

		2						  0 bis 9			    01 bis 99		      0 bis 9

	durchgeschobene 
	Pole
	Pushed Pole

		3						  0 bis 9			    01 bis 99		      0 bis 9

	nicht fertig 
	bearbeitete Pole
	worked not ready Pole

		4						  0 bis 9			    01 bis 99			  0 bis 9


	Beispiel :
	Example:


	Ausschußpol	 MaTeil 3	 Station 7		Prüffehler 2
	Rejektpart	 MaPart 3	 Station 7		Check error 2

		  1		   3			07			2

	------------------------------------------------------------------------------------  */

//--- Produktionsdaten ermitteln und eintragen für Maschinenteil 1 ---
//--- to get the productions data and set the values for machine unit 1 ---

	if (MaDatum[MaPartNum].BDEDaten_ermitteln)
	{
		// je nach Artikel mehrere Gehäuse im Nest
		for(i=1;i<=NumberOfHousings;i++)
		{
			Ausschuss_Pol_gefunden = false;
			for(j=1;j<=MW_ArtikelTyp.Polzahl;j++)
			{
// TODO: Registerabfragen kontrollieren!

                //--- Work Cycles ------ Arbeitstakte ---
			//	if(RegisterWert_3D(RegisterNr,i,j) > 0)
					MaDatum[MaPartNum].Index_21.Arbeitstakte++;
				//--- empty Pole -------  ---
				if ((RegisterWert_3D(RegisterNr,i,j) ==  0))
						MaDatum[MaPartNum].Index_21.Leertakte++;


				//--- Good Pole ------- Gutpole ---
				if ((RegisterWert_3D(RegisterNr,i,j) >=  1000)
				&&	(RegisterWert_3D(RegisterNr,i,j) <  10000))
						MaDatum[MaPartNum].Index_21.Gutpole++;

				//--- Rejekt Pole ----- Ausschusspole ---
				if ((RegisterWert_3D(RegisterNr,i,j) >= 10000)
				&&	(RegisterWert_3D(RegisterNr,i,j) <  20000))
				{
					MaDatum[MaPartNum].Index_21.Ausschusspole++;
					Ausschuss_Pol_gefunden = true;
				}

				//--- Leertakte oder Ausschussteil vom vorherigen MG ---
				//--- Empty tacts or rejekt part of previous MG ---
				if ((RegisterWert_3D(RegisterNr,i,j) >= 20000)
				&&	(RegisterWert_3D(RegisterNr,i,j) <  30000))
					MaDatum[MaPartNum].Index_21.Leertakte++;

				//--- Pushed Pole ---- durchgeschobene Pole ---
				if ((RegisterWert_3D(RegisterNr,i,j) >= 30000)
				&&	(RegisterWert_3D(RegisterNr,i,j) <  40000))
					MaDatum[MaPartNum].Index_21.DurchgeschobenePole++;

				//--- nicht fertig bearbeitete Pole ---
				//---- worked not ready Pole ----------
				if ((RegisterWert_3D(RegisterNr,i,j) >= 40000)
				&&	(RegisterWert_3D(RegisterNr,i,j) < 50000))
					MaDatum[MaPartNum].Index_21.DurchgeschobenePole++;

			}//end j Polzähler

			//--- Good Parts ------- Gutteile ---
			if ((RegisterWert_3D(RegisterNr,i,0) > 0)
			&&	(RegisterWert_3D(RegisterNr,i,0) < 10000))
				MaDatum[MaPartNum].Index_21.Gutteile++;

			//--- Rejekt Parts ----- Ausschussteile ---
			if ((RegisterWert_3D(RegisterNr,i,0) >= 10000)
			&&	(RegisterWert_3D(RegisterNr,i,0) <  20000))
				MaDatum[MaPartNum].Index_21.Ausschussteile++;

			//--- Rejekt Block ----- Blockausschuß ---
			if ((RegisterWert_3D(RegisterNr,i,0) >= 10000)
			&&	(RegisterWert_3D(RegisterNr,i,0) <  20000)
            &&	!Ausschuss_Pol_gefunden)
				MaDatum[MaPartNum].Index_21.BlockAusschuss++;

		}//end i Blockzähler

		// Nur wenn Daten eingetragen wurden wird der Index geschickt
		Index21_senden = true;

		MaDatum[MaPartNum].Daten_uebergeben = true;
		MaDatum[MaPartNum].BDEDaten_ermitteln = false;

		M.Arbeitstakte+=MaDatum[MaPartNum].Index_21.Arbeitstakte;
		M.Ausschusspole+=MaDatum[MaPartNum].Index_21.Ausschusspole;
		M.Ausschussteile+=MaDatum[MaPartNum].Index_21.Ausschussteile;
		M.BlockAusschuss+=MaDatum[MaPartNum].Index_21.BlockAusschuss;
		M.DurchgeschobenePole+=MaDatum[MaPartNum].Index_21.DurchgeschobenePole;
		M.Gutpole+=MaDatum[MaPartNum].Index_21.Gutpole;
		M.Gutteile+=MaDatum[MaPartNum].Index_21.Gutteile;

	}//of if (M_.BDEDaten_ermitteln)

	// Produktionsdaten in Textdatei speichern
	// Save production data in textfile
	if	(	tmSaveProductionData->Time()
		&& !SaveProductionData.Save
		)
	{
		SaveProductionData.Arbeitstakte = M.Arbeitstakte;
		SaveProductionData.Ausschusspole = M.Ausschusspole;
		SaveProductionData.Ausschussteile = M.Ausschussteile;
		SaveProductionData.BlockAusschuss = M.BlockAusschuss;
		SaveProductionData.DurchgeschobenePole = M.DurchgeschobenePole;
		SaveProductionData.Gutpole = M.Gutpole;
		SaveProductionData.Gutteile = M.Gutteile;

		M.Arbeitstakte = 0;
		M.Ausschusspole = 0;
		M.Ausschussteile = 0;
		M.BlockAusschuss = 0;
		M.DurchgeschobenePole = 0;
		M.Gutpole = 0;
		M.Gutteile = 0;

		SaveProductionData.Save = true;
		tmSaveProductionData->SetTimerBusy(false);
	}

//--- Produktionsdaten an BDE übergeben ---
//--- to transfer the production data to BDE ---

	if	(	MaDatum[MaPartNum].Daten_uebergeben
		// Alle Stationen des Antriebes fertig?
		&&	Freigabe_senden
		)
	{
		if (Index21_senden)
		{
			// ProDaten zwischenspeichern, alle Block & Polinfos auf einmal übergeben
			// to buffer the production data, 
			// all the block & pole info will be transfered in one time
			CopyMemory(&BDEDatum[MaPartNum].Index_21,
					   &MaDatum[MaPartNum].Index_21,
				 sizeof(BDEDatum[MaPartNum].Index_21));

			// Alle übergebenen Daten der Maschine löschen
			// to delete the transfered machine data
			memset(&MaDatum[MaPartNum].Index_21,0,sizeof(MaDatum[MaPartNum].Index_21));
		}

		// Prüffehler zwischenspeichern, alle Prüffehler max.50
		// to buffer the check error, max. 50 check errors
		CopyMemory(&BDEDatum[MaPartNum].Index_22.Prueffehler,
				   &MaDatum[MaPartNum].Index_22.Prueffehler,
			 sizeof(BDEDatum[MaPartNum].Index_22.Prueffehler));

		// Alle übergebenen Daten der Maschine löschen
		// to delete the transfered machine data
		memset(&MaDatum[MaPartNum].Index_22.Prueffehler,0,sizeof(MaDatum[MaPartNum].Index_22.Prueffehler));

		// BDE Daten senden
		// send the BDE Data
		MaDatum[MaPartNum].Daten_uebergeben = false;
		MaDatum[MaPartNum].BDEDatenSenden   = true;

		//Index 21 senden oder nur 22 (Prüffehler)
		// send index 21 or only 22 (check errors)
		if (Index21_senden) MaDatum[MaPartNum].Index21_uebertragen = true;
		else MaDatum[MaPartNum].Index22_uebertragen = true;

		Index21_senden = false;
	}

// TODO: EPHASE > BDE_Daten_ueberbruecken
//	M_.Switch_Off_BDE = true;

	if (M_.Switch_Off_BDE) MaDatum[MaPartNum].BDEDatenSenden = false;

}//of Function


//*****************************************************************
//***********************  Artikeldaten  **************************
//*****************************************************************
void ArticleData(void)
{
// TODO: Artikeldaten einpflegen
/* ------------------------------------------------------------------
/*
/* Parameter[0] : Anzahl Gehäuse im Nest
/*	
/*	1:	1 Gehäuse im Nest
/*	2:	2 Gehäuse im Nest
/*
/* Parameter[1] : 
/*	
/*	0:  
/*	1: 
/*
/* ------------------------------------------------------------------
*/
//------------------------- Parameter  0 --------------------------
//-------------------- Anzahl Gehaeuse im Nest --------------------

	DriveUnit[DriveUnit1].NumberOfHousings = MW_ArtikelTyp.Parameter[0];


	//if (MW_ArtikelTyp.Parameter[0] == 2) 
	//	DriveUnit[DriveUnit1].NumberOfHousings = 2;

//------------------------- Parameter  1 --------------------------
//------------------------- xxxxxxxxxxxx ---------------------------
	

}// of Function

//*****************************************************************
//*************************  Maschine Ein  ************************
//*****************************************************************
void Machine_ON()
{
	if	(  (E_Button_MaOn && !E_Button_Quit)	// wenn beide gleichzeitg gedrückt werden nicht einschalten!
		&&  E_Button_MaOff
		&& !M_.Newstart
		&& !M_.MaError
		&& !M_.MaStop
		&& !PC_NewData
		&& !M_.ChangeArticle_PC
		)
	{
		#ifdef Axis_exist
			if (!Achsen_Handbetrieb_aktiv) M_.MaOn = true;
		#else
			M_.MaOn = true;
		#endif
	}

	
	// Machine running			// Maschine läuft 
	if	(	M_.MaOn
		&&	M_.PressureAirEn
		&& !M_.MaError
		&& !M_.MaStop
		&& !M_.Newstart
		&&	SBTMaPart1.SafetyCircleClosed
		)
		M_.MaRun = true;	// Maschine läuft	// Maschine läuft

	if (PosFlanke(Fl_On,M_.MaOn)) ISetTimer(T_PulsMaOn,true);

	M_.ImpulseMaOn = false;

	if (Time(T_PulsMaOn))
	{
		ISetTimer(T_PulsMaOn,false);
		M_.ImpulseMaOn = true;
	}

	A_LED_MaOn	=  (M_.MaOn && !M_.MaStand_By)
						  	|| (M_.MaOn &&  M_.MaStand_By && FRQ[2])
					 	 	||	E_Button_MaOn
							;

	if (!SBTInsel1.HighRunPhaseFinished)
		A_LED_MaOn = false;
}// of void Machine_ON()


//*****************************************************************
//**********************  Maschine Aus  ***************************
//*****************************************************************
void Machine_OFF(void)
{
	static bool maRunOld = false;

	if (!E_Button_MaOff || PC_Machine_Off) M_.MaOff_pressed = true;

	// Maschine Läuft erst einen Zyklus später ausschalten als M_.MaEin.
	// Damit haben die Stationen die möglichkeit die Endstellung bei MaAus zu erreichen
	// (Abschnitt "Maschine läuft AUS" vor "Maschine ein AUS" gezogen)
	
	// Machine Running only a cycle switch off later than M_. MaOn.
	// With it the stations have to reach the possibility the final position with MaOff
	// (Segment "Machine runs Off" before "machine on Off" pulled)

	// Maschine läuft AUS
	// Machine runs Off
	if  (   (  !M_.MaOn 
            &&  M_.EndPosition_Machine 
            )
    	||  (!M_.AirOn && M_.MaSingleStepMode && M_.MaRun)	// air switched off by hand during machine running	// Luft von Hand aus bei MaLaeuft
    	||    M_.MaError									// Error Machine Stop								// Störung -> Maschine sofort aus
        )
	{
		M_.MaRun = false;
		M_.PressureAir_switched_Off = true;
	}

	// Maschine ein AUS
	// Machine on Off
	if  (	 M_.MaOff_pressed
		||  (M.Machine_Unloaded && M_.MaRun && !M_.Change_WPC)
		|| (!M_.AirOn && M_.MaSingleStepMode && M_.MaRun)	// Luft von Hand aus bei MaLaeuft
		||   M_.MaError
		||   M_.MaStop
		||	 M_.AirOff
		)
	{
		M_.MaOn = false;
		M_.MaOff_pressed = false;
	}

	if (maRunOld && !M_.MaRun)
		M_.ImpulseMaOff = true;
	else
		M_.ImpulseMaOff = false;

	maRunOld = M_.MaRun;

	//LED Taster Maschine AUS
	A_LED_MaOff	=	!M_.MaRun
							|| (!M_.MaRun && M_.MaError)
							||  (M_.MaRun && FRQ[2] && (!M_.MaOn || M_.MaOff_pressed));

	if (!SBTInsel1.HighRunPhaseFinished)
		A_LED_MaOff = false;

}// void Machine_OFF(...)

//*****************************************************************
//*******************  Störung Maschine sofort aus  ***************
//**********  switch the machine immediately off if error  ********
//*****************************************************************
void Error_MaOff(void)
{
	bool M_Error_Motors_Rotates			= false;
	bool M_Error_CollectiveError_Servo	= false;
	bool M_Error_ReferenzDrive			= false;

	bool CollectiveError_Axis_found		= false;
	bool CollectiveError_Plate_found	= false;

	bool M_Error_FU_Motor_Ready			= false;


	#ifdef Axis_exist
		for (int i=0;i<NumOfAxis;i++)
		{
		   if (Achse[i].M_Error_ServoMotor_Rotates)
			   M_Error_Motors_Rotates = true;

		   if (Achse[i].M_CollectiveError_Servo)
			   M_Error_CollectiveError_Servo = true;

		   if (Achse[i].M_ReferenzDrive_Error)
			   M_Error_ReferenzDrive = true;
		}
	#endif

	#ifdef Plate_exist
		for (int i=0;i<NumOfPlate;i++)
		{
			if (Teller[i].M_Error_ServoMotor_Rotates)
			{
				M_Error_Motors_Rotates = true;
				break;
			}
		}
	#endif 


	#ifdef Plate_FU_exist          
		for (int i=0;i<NumOfPlate;i++)
		{
			if (!Teller[i].E_Motor_Bereit)
			{
				Teller[i].M_Error_Motor_Ready = true;
				M_Error_FU_Motor_Ready = true;
				break;	
			}
		}

	#endif 

	if (PosFlanke(Fl_Quit,M_.Quit))
	{
		M_.MaError					= false;
		M_.MaEndPosition_Error				= false;
		M_.EndPos_K_DriveUnits_Error	= false;

		M_.MaOff_pressed				= false;

		for (int i=0;i<NumOfDriveUnits;i++)
		{
			DriveUnit[i].EndPosition_Cylinder_Error = false;
			DriveUnit[i].Error_DriveUnit			= false;
		}

	#if defined(Plate_exist) || defined(Plate_FU_exist)
		for (int i=0;i<NumOfPlate;i++)
		{
			Teller[i].M_Error_Motor_Ready = false;
		}
	#endif

		M_.MaStop				  = false;
		M_.Error_Marker_OK	  = false;
		M_.Error_MovingTest = false;
	}

	// MaStop auslösen auch, wenn die Maschine nicht läuft.
	// Fehler die ohne Anlauf der Maschine entstehen können angezeigt werden
	// Diese Fehler müssen in Allgemein eingetragen werden

	// MaStop also release if the machine does not run.
	// Error without approach of the machine are able to originate are indicated
	// These mistakes must be registered in In general

	if (M_.Error_AirPressure
	||  M_.Error_IBS
#ifdef Axis_exist
	||  M_Error_Motors_Rotates
#endif
#ifdef Plate_exist
	||  M_Error_Motors_Rotates
#endif
#ifdef Plate_FU_exist 
	||  M_Error_FU_Motor_Ready
#endif
	||	M_.Error_Marker_OK
	||  M_.Error_MovingTest
	||	SBTMaPart1.ErrorMaOff
	||	SBTMaPart1.A_SoftwareEmergencyStop
	)
		M_.MaStop = true;

//****  Kontrollzeit Maschine ein  ****
//*****  ControlTime Machine On  ******
	static bool KontrollzeitAntriebAbgelaufen = false;

	for (int i=0;i<NumOfDriveUnits;i++)
	{
		if	(	M_.MaStepEn
			&& !DriveUnit[i].reset_ControlTime
			&& !DriveUnit[i].DriveUnit_in_EndPosition
			)
		{
			switch (i)
			{
			case 0:// DriveUnit1
				ISetTimer(T_ControlTime_DU1,true);
			break;
			case 1:// DriveUnit2
				ISetTimer(T_ControlTime_DU2,true);
			break;
			case 2:// DriveUnit3
				ISetTimer(T_ControlTime_DU3,true);
			break;
			case 3:// DriveUnit4
				ISetTimer(T_ControlTime_DU4,true);
			break;
			case 4:// DriveUnit5
				ISetTimer(T_ControlTime_DU5,true);
			break;
			case 5:// DriveUnit6
				ISetTimer(T_ControlTime_DU6,true);
			break;
			case 6:// DriveUnit7
				ISetTimer(T_ControlTime_DU7,true);
			break;
			case 7:// DriveUnit8
				ISetTimer(T_ControlTime_DU8,true);
			break;
			}// of switch
		}// of if()
		else
		{
			switch (i)
			{
			case 0:// DriveUnit1
				ISetTimer(T_ControlTime_DU1,false);
			break;
			case 1:// DriveUnit2
				ISetTimer(T_ControlTime_DU2,false);
			break;
			case 2:// DriveUnit3
				ISetTimer(T_ControlTime_DU3,false);
			break;
			case 3:// DriveUnit4
				ISetTimer(T_ControlTime_DU4,false);
			break;
			case 4:// DriveUnit5
				ISetTimer(T_ControlTime_DU5,false);
			break;
			case 5:// DriveUnit6
				ISetTimer(T_ControlTime_DU6,false);
			break;
			case 6:// DriveUnit7
				ISetTimer(T_ControlTime_DU7,false);
			break;
			case 7:// DriveUnit8
				ISetTimer(T_ControlTime_DU8,false);
			break;
			}// of switch
		}// of else
	}// of for

	// Maschine hält an wenn eine Kontrollzeit Abgelaufen ist
	// Machine stops if a controlling time has run off
	if	(	Time(T_ControlTime_DU1)
		||  Time(T_ControlTime_DU2)
		||  Time(T_ControlTime_DU3)
		||  Time(T_ControlTime_DU4)
		||  Time(T_ControlTime_DU5)
		||  Time(T_ControlTime_DU6)
		||  Time(T_ControlTime_DU7)
		||  Time(T_ControlTime_DU8)
		)
		KontrollzeitAntriebAbgelaufen = true;
	else
		KontrollzeitAntriebAbgelaufen = false;

	// Kontrollzeit eines Antriebes abgelaufen
	// Den anderen Antrieben melden das sie anhalten sollen
	// Controlling time of an DriveUnit Runs Off
	// Announce that the other DriveUnits should stop
	if (KontrollzeitAntriebAbgelaufen)
	{
		for (int i=0;i<NumOfDriveUnits;i++)
			DriveUnit[i].ErrorMachineOff = true;
	}
	else
	{
		for (int i=0;i<NumOfDriveUnits;i++)
			DriveUnit[i].ErrorMachineOff = false;
	}
	if	(	KontrollzeitAntriebAbgelaufen
		||	(	M_.MaStepEn
			&& !M_.EndPosition_Machine
			&&	M_.EndPos_K_DriveUnits
			&&	M_.EndPos_SK_DriveUnits
			&& !KontrollzeitAntriebAbgelaufen)
		||	(	M_.MaStepEn
			&& !M_.EndPosition_Machine
			&& (TimerWert(T_ControlTime_DU1) < 1)
			&& (TimerWert(T_ControlTime_DU2) < 1)
			&& (TimerWert(T_ControlTime_DU3) < 1)
			&& (TimerWert(T_ControlTime_DU4) < 1)
			&& (TimerWert(T_ControlTime_DU5) < 1)
			&& (TimerWert(T_ControlTime_DU6) < 1)
			&& (TimerWert(T_ControlTime_DU7) < 1)
			&& (TimerWert(T_ControlTime_DU8) < 1))
		)
		ISetTimer(T_MaschineControlTime,true);
	else
		ISetTimer(T_MaschineControlTime,false);

	for (int i=0;i<NumOfDriveUnits;i++)
	{
		// Befindet sich noch ein Antrieb in der 
		// Bearbeitungsphase dann die Maschinen Kontrollzeit zuruecksetzen
		// If on more DriveUnit in that Treatment phase 
		// then the machines controlling time put back

		if 	(	DriveUnit[i].reset_ControlTime
			||	M_.Reset_Stations_ControlTime
			)
		{
			ISetTimer(T_MaschineControlTime,false);
			break;
		}
	}

	// Kann an jeder Stelle in den Funktionen der jeweiligen Stationen gesetzt werden
	// Can be put at every place in the functions of the respective stations
	for (int i=0;i<NumOfDriveUnits;i++)
	{
		DriveUnit[i].reset_ControlTime = false;
	}

    M_.Reset_Stations_ControlTime = false;

//**************************************

	if (Time(T_MaschineControlTime)
	||	M_.MaEndPosition_Error
	|| (M_.MaStop && !M_.MaRun)
	||  M_.Error_IBS
	// Sicherheitsfunktionen
	// Safetyfunction
	||	SBTMaPart1.ErrorMaOff
	||	SBTMaPart1.A_SoftwareEmergencyStop
#ifdef Axis_exist
	||	M_Error_CollectiveError_Servo
	||	M_Error_ReferenzDrive
#endif
	)
	M_.MaError = true;	// Maschine aus


	static bool stoerungErkannt = false;

	//Nach Störung die Endstellung bei Start kontrollieren der Fehler ist vorrangig => die Luft wird ausgeschaltet
	//After Error the final position by start check the mistake(Error) is as a matter of priority =>; the Air is switched off
	if (PosFlanke(Fl_EndPos,M_.MaError))
		stoerungErkannt = true;

	if (M_.Quit)
		stoerungErkannt = false;

	if	(	stoerungErkannt
		&&	M_.PressureAirEn
		)
		EndPositionByStart();

	// 1.Zyklus Allgemeine Störungen, Servo und Endstellungen nach Fehler suchen
	// 2.Zyklus Baugruppen nach Fehler suchen
	// Keinen Endstellungs oder Sammelfehler der Servos gefunden
	// dann alle Baugruppen durchsuchen

	// 1. Cycle general Error, Servo and final positions search for Error
	// 2. Cycle assemblies look for Error
	// No final positions or collective Error of the Servos found
	// then all assemblies search

	// --- Fehlersuche 2 Zyklen aktiv ---
	if (Fehlerprg[PRG1].BG_durchsuchen)
	{
		Fehlerprg[PRG1].Fehler_suchen = false;
		Fehlerprg[PRG1].BG_durchsuchen = false;
	}

	if (Fehlerprg[PRG1].Fehler_suchen)
	{
#ifdef Axis_exist
		for (int i=0;i<NumOfAxis;i++)
		{
			if (Achse[i].M_CollectiveError_Servo)
				CollectiveError_Axis_found = true;
		}
#endif
#ifdef Plate_exist
		for (int i=0;i<NumOfPlate;i++)
		{
			if (Teller[i].M_CollectiveError_Servo)
				CollectiveError_Plate_found = true;
		}
#endif
		if	(	!M_.EndPos_K_DriveUnits_Error
			&&	!M_.MaEndPosition_Error
			&&	!CollectiveError_Axis_found
			&&	!CollectiveError_Plate_found
			)
		{
			Fehlerprg[PRG1].BG_durchsuchen = true;
		}
		else
		{
			// Wenn kein Fehler gefunden wurde einen
			// Allgemeinen Fehler melden
			Fehlerprg[PRG1].Fehler_suchen = false;
			if (Fehlerprg[PRG1].Fehlerzaehler <= 0)
				Fehler(PRG1,400,20,0);
		}
	}

	// --- Fehler Suchlauf starten ---
	// --- search for errors only active for one cycle
	for (int i=0;i<NumOfDriveUnits;i++)
	{
		// --- Fehler Suchlauf starten ---
		if	(	(	M_.MaError 
				||	DriveUnit[i].EndPosition_Cylinder_Error)
			&& !Fehlerprg[PRG1].Suchlauf_gestartet
			)
		{
			Fehlerprg[PRG1].Suchlauf_gestartet	= true;		// start error searching		// Fehler suchen gestartet
			Fehlerprg[PRG1].Fehler_suchen		= true;
		}
	}
}// of void Error_MaOff(...)

//*****************************************************************
//********************	Maschine leerfahren  **********************
//*****************************************************************
void Unload_Machine(void)
{
	if  (   MACHINETYPE == FIRST_MG )
    {
        // Merker für die Nester,die sich noch im Umlauf befinden,
        // und mit aufzuarbeitenden Gehäusen bestückt sind.
        M_.St301_WPC_worked_in_circulation_process  = false;

#ifdef Datenverwaltungs_Pipe_vorhanden
		for(int i=1; i<=MAXNESTER; i++)
        {
            if (Nesterdaten[i].Teilinformation[0][1])
                M_.St301_WPC_worked_in_circulation_process  = true;
        }
#endif
    }

	if  (   MACHINETYPE == FIRST_MG
        ||  MACHINETYPE == SINGLE_MG
		)
    {
	    if (PosFlanke(Fl_PC_Unload,PC_Unload || E_Unload_Machine))
		{
		    M.Unload_Machine = true;
		}
		A_LED_Unload_Machine = M.Unload_Machine && FRQ[2];
    }

    if  (   MACHINETYPE == MIDDLE_MG
        ||  MACHINETYPE == LAST_MG )
    {
	    // Zeitzuweisungen
	    ISetTimer( T_Before_SPS_unloaded, E_Gateway_before_SPS_Unloaded);

	    if	(	PosFlanke(Fl_PC_Unload, Time(T_Before_SPS_unloaded))
            &&  M_.IBS_IO_ok
	        && !M.Unload_Machine
	        && !M.Machine_Unloaded
			)
	    {
		    M.Impulse_UnloadMaschine = true;
	    }

        // Maschine macht 8 Nestvorschübe,bevor sie leerfährt
        // Bei kleiner Losgrösse können sich Teile zwischen
        // beiden MaTeilen befinden obwohl MG1 leer ist
        // und noch kein Gutteil in MG2 angekommen ist!
	    if ( PosFlanke( Fl_ImpulseUnloadMaschine, M.Impulse_UnloadMaschine ) )
	    {
		    M.LockUnload = true;
		    SetZaehler(Z_Lock_Unload,0);
	    }

	    if (ZaehlWert(Z_Lock_Unload)>=8)
		    M.LockUnload = false;

	    if	(	M.Impulse_UnloadMaschine
	        && !M.Machine_Unloaded
	        && !M.LockUnload
			)
	    {
		    M.Unload_Machine = true;
		    M.Impulse_UnloadMaschine = false;
	    }
    }

    // Zeit zuweisen von anderen Maschinenteilen
    if (MACHINETYPE == FIRST_MG || MACHINETYPE == MIDDLE_MG)
        ISetTimer( T_Following_SPS_unloaded, E_Gateway_following_SPS_Unloaded );
    else
        ISetTimer( T_Following_SPS_unloaded, true );

	if (M.Unload_Machine)
	{
		if  ( (!M_.St301_WPC_worked_in_circulation_process  || (MACHINETYPE != FIRST_MG) )
			&&  Time(T_Following_SPS_unloaded)	// Maschinenteile leer
			&&  DriveUnit[DriveUnit1].Unloaded		// DriveUnit 1 St201 empty?
// TODO: Wenn nötig weitere Antriebe hinzufügen!!
//			&&  DriveUnit[DriveUnit2].Unloaded		// DriveUnit 2 St202 empty?
			)
		{
			M.Machine_Unloaded	            = true;
			M.Unload_Machine		            = false;
			M.Impulse_UnloadMaschine      = false;
			M.LockUnload                = false;
			for (int i=0;i<NumOfDriveUnits;i++)
				DriveUnit[i].Unload			= false;
		}
	}

	if (    M.Machine_Unloaded
        &&  M_.EndPosition_Machine
        && !M_.MaRun
        )
		M.Machine_Unloaded_in_EndPos	= true;

	if ( M.Machine_Unloaded_in_EndPos && !M_.MaRun )
	{
		A_LED_Unload_Machine = false;
		PC_release_Article = true;
	}
	else
    {
        PC_release_Article = false;
    }

	// Maschinenteil nach leergefahren einschalten
	// to switch on the machine unit after unload
	if (    E_Button_MaOn
	    &&  M.Machine_Unloaded_in_EndPos
	    && !M_.Change_WPC
        )
	{
		M.Impulse_UnloadMaschine		= false;
		M.LockUnload				= false;
		M.Unload_Machine					= false;
		M.Machine_Unloaded				= false;
		M.Machine_Unloaded_in_EndPos	= false;
		for (int i=0;i<NumOfDriveUnits;i++)
			DriveUnit[i].Unloaded			= false;
	}

	// Meldung eintragen für BDE
	PC_Message[1] = M.Unload_Machine && !M.Machine_Unloaded_in_EndPos;
	PC_Message[2] = M.Machine_Unloaded_in_EndPos && !M_.MaRun && !M_.MaError;	

	PC_release_Article = true;  //for test
}// of void Unload_Machine(...)

//*****************************************************************
//**********************  Allgemeine Stoerung *********************
//**********************  general errors      *********************
//*****************************************************************
void General_Error(void)
{
	M_.General_Error_found = false;

	// Fehlerbereich für den Allgemeinenteil festlegen
	// to fix the error field for general errors
	Fehlerprg[PRG1].Allgemeine_Fehler = 400;

	if (Fehlerprg[PRG1].Fehler_suchen)
	{
// Allgemeine Fehler
// general errors
		if (SBTMaPart1.ErrorEmergencyStop)
		{
			Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,1,0);
			M_.General_Error_found = true;
		}

		if (SBTMaPart1.ErrorKey)			// auto/hand switch not ok
		{
			Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,2,0);
			M_.General_Error_found = true;
		}

		if (M_.Error_AirPressure)			// air pressure not enough		// Luftdruck zu gering
		{
			Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,3,0);
			M_.General_Error_found = true;
		}

		if (M_.Error_Marker_OK)				// data not saved correctly
		{
			Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,4,0);
			M_.General_Error_found = true;
		}

		if (M_.Error_IBS)					// interbus error
		{
			Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,5,0);
			M_.General_Error_found = true;
		}


#ifdef Axis_exist
		if (Achse[Axis1].M_Error_ServoMotor_Rotates)
		{
			Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,6,0);
			M_.General_Error_found = true;
		}

		if (Achse[Axis1].M_ReferenzDrive_Error)
		{	
			Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,7,0);
			M_.General_Error_found = true;
		}
#endif

#ifdef Plate_exist
		if (Teller[Plate1].M_Error_ServoMotor_Rotates)
		{
			Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,8,0);
			M_.General_Error_found = true;
		}
#endif 

#ifdef Plate_FU_exist //  FU Teller steht
		if (Teller[Plate1].M_Error_Motor_Ready)
		{
			Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,9,0);
			M_.General_Error_found = true;
		}

#endif 

// Fehler Endstellung Kolben fehlt
		for (WORD i = 0; i < NumOfDriveUnits; i++)
		{
			if (DriveUnit[i].EndPosition_Cylinder_Error)
			{
				Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,32-i,0);
			}
		}

// Fehler Schutztüren
// safety door errors
		if (SBTMaPart1.ErrorSafetyDoorCircle && !SBTMaPart1.ErrorEmergencyStop)
		{
			Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,49,0);
			M_.General_Error_found = true;
		}

		for (WORD i = 1; i <= NUMBERSAFETYDOORS; i++)
		{
			if (SBTMaPart1.ErrorSafetyDoor[i])
			{
				Fehler(PRG1,Fehlerprg[PRG1].Allgemeine_Fehler,49-i,0);
				M_.General_Error_found = true;
			}
		}

// TODO: Fehler Bewegungstest reserviert von (899) 
//! Änderungen für 3-2 Wege Ventile
//		Error MovingTest reseved from (899)

		for (WORD i=1; i<=20;i++)
		{
			// MainAir valve terminal i
			if (M_MovingTest_Error[i])
			{	
				Fehler(PRG1,897,-i,0);
				M_.General_Error_found = true;
			}
		}

		// MainAir Station 203
		if (M_MovingTest_Error[203])
		{	
			Fehler(PRG1,890,7,0);
			M_.General_Error_found = true;
		}

		// MainAir Station 202
		if (M_MovingTest_Error[202])
		{	
			Fehler(PRG1,890,8,0);
			M_.General_Error_found = true;
		}

		// MainAir Station 201
		if (M_MovingTest_Error[201])
		{	
			Fehler(PRG1,890,9,0);
			M_.General_Error_found = true;
		}

// Allgemeiner Fehler gefunden?
// general errors found?
		if (M_.General_Error_found)
		{
			M_.General_Error_found = false;
			Fehlerprg[PRG1].Fehler_suchen  = false;
		}
	}//of Fehler_suchen
}//of void General_Error(...)


//*****************************************************************
//***************  Endstellung bei Start  *************************
//***************  End Position by Start  *************************
//*****************************************************************
void EndPositionByStart()
{
	for (WORD i=0;i<NumOfDriveUnits;i++)
	{
		// Endstellungsfehler bei einem Antrieb
		// Error EndPosition by DriveUnit
		if (!DriveUnit[i].EndPosition_Cylinder && DriveUnit[i].EndPosition_Sequences)
		{
			DriveUnit[i].EndPosition_Cylinder_Error = true;
		}

		// Endstellungsfehler beim Einschalten der Maschine bevor die Anläuft
		// EndPosition Error before the Machine is turning on 
		if (!M_.EndPos_K_Machine && M_.EndPos_SK_Machine && !DriveUnit[i].EndPosition_Cylinder_Error)
			M_.MaEndPosition_Error = true;
	}
}// of void EndPositionByStart(...)

//*****************************************************************
//*********************  Fördertöpfe Ein/Aus  *********************
//************************  Conveyor ON/Off  **********************
//*****************************************************************
void Conveyor_OnOff(bool M_ConvReset, bool M_QuitReset)
{
	// Vibratoren ein-/ausschalten
	// Conveyor switch On/Off
	if  ( PosFlanke( Fl_Conveyor, E_Button_ConveyorOn ) && !M_.MaRun )    // Push button Conveyor on/off	// Taster Vibratoren ein/aus betätigen
    {
		M_.ConveyorOn = !M_.ConveyorOn;
    }

	// Vibratoren einschalten
	// Conveyor switch on
	if  (   PosFlanke( Fl_QuitConveyor, M_.Quit )               // Button Quit		// Taster Entsperren
        ||  M_.MaRun )                                          // Machine Run		// Maschine läuft
    {
		M_.ConveyorOn = true;
    }

	// Vibratoren ausschalten
	// Conveyor off
    if  ( PosFlanke( Fl_AirOff, M_.AirOff ) )                    // Air switch off	// Luft ausschalten
    {
		M_.ConveyorOn = false;
    }
    
    // Kontrollampe
	// Conrolllamp
	A_LED_ConveyorOn = M_.ConveyorOn;	                                

	if (!SBTInsel1.HighRunPhaseFinished)
		A_LED_ConveyorOn = false;

	// Vibratoren (Nachlaufzeit)
	// Conveyor (DelayTime)
	if (    (   (!M_.MaRun && !E_Button_Quit)
			||  (M_.MaStand_By && !E_Button_Quit && !E_Button_ProcessObservationMode && !E_Button_TipMode && !M_.Bridge_SingleStepMode)
			||  (M_.MaSingleStepMode && M_.MaRun && !E_Button_ProcessObservationMode && !E_Button_TipMode && !M_.Bridge_SingleStepMode && !E_Button_Quit)

            )
	    &&    !PosFlanke( Fl_T_ResetConveyor, M_ConvReset )
	    &&    !PosFlanke( Fl_T_ResetQuit, M_QuitReset )
	    )
    {
		ISetTimer( T_Conveyor, true );									// DelayTime on		// Nachlaufzeit ein
    }
	else
    {
        ISetTimer( T_Conveyor, false );									// DelayTime off	// Nachlaufzeit aus
    }

	// Freigabe Vibratoren
	// Enable Conveyor
	if  (   M_.ConveyorOn
	    && !Time(T_Conveyor)
	    )
    {
        M_.ConveyorEn = true;
    }
	else
    {
        M_.ConveyorEn = false;
    }
}

//*****************************************************************
//****   Funktion zum starten von Treibern im SPS-Programm     ****
//****       Diese Funktion wir nur 1 mal beim starten         ****
//****               des Programms aufgerufen                  ****
//*****************************************************************
//****               to start the sps program                  ****
//****        this function will be invoked only once          ****
//****            at the beginning of this program             ****
//*****************************************************************
void SPS_Programm_Start(void)
{

#ifdef Scanner_V24
	Scanner_init(COM2);
#endif

}

//*****************************************************************
//****   Funktion zum beenden von Treibern im SPS-Programm     ****
//****       Diese Funktion wir nur 1 mal beim starten         ****
//****               des Programms aufgerufen                  ****
//*****************************************************************
//****                to exit the sps program                  ****
//****         this function will be invoked only once         ****
//****          when the program is called to be exit          ****
//*****************************************************************
void SPS_Programm_Stop(void)
{

#ifdef Scanner_V24
	Scanner_close(COM2); // Scanner Maschine
#endif

}

//*****************************************************************
//****                   Maschinen - Hauptablauf               ****
//****  Der zyklische Aufruf erfolgt in Headerdatei "Thread.h" ****
//****  in einer Endlosschleife der Funktion "ProcSPS1Thread"  ****
//*****************************************************************
//*****************************************************************
//****                   machine - main process                ****
//****  The cyclic call occurs in the head file "Thread.h"     ****  
//****  in a endless loop of function "ProcSPS1Thread"         ****
//*****************************************************************
void MachineProcess1(void)
{
	// The address of bus devices						// Die Adressen der Busteilnehmer
	// will be assigned to the input variables			// werden den Eingangsvariablen zugewiesen
	Input();

	
	// Interbus RUN from the head file "ibs_ctrl.h" will be queried		// Interbus RUN aus der Headerdatei "ibs_ctrl.h" wird abgefragt
	Status_IBS();
	
	// Emergency stop switch							// Sicherheitstechnik, Schnittstelle Safetybridge V3
	// contact and lock of the safety doors
	SafetyMainProcess();

	// End positions of the machine(switchs and steps)	// Endstellungen der Maschine (Schalter und Ketten)
	// will be assigned									// wird zugewiesen,
	EndPosition();

	// End positions of the machine(switchs and steps)	// Kolbenschalter (unter M_.Endstell_K_Achse) werden
	// will be assigned									// während die Achse fährt kontrolliert
	ControlEndPosition();
	DriveUnitInEndPosition();

	// to query the switch-on condition for the variables	// Einschaltbedingungen für die Variablen
	// "M_.MaOn" and "M_.MaRunning"							// "M_.MaEin" und "M_.MaLaeuft" werden abgefragt
	Machine_ON();

	// to query the switch-off condition for the variables	// Ausschaltbedingungen für die Variablen
	// "M_.MaOn" and "M_.MaRunning"							// "M_.MaEin" und "M_.MaLaeuft" werden abgefragt
	Machine_OFF();

	// StandBy of the Drive Units are questioned 			// StandBy der Antriebe werden abgefragt
	DriveUnitStandBy();

	// to query the standby variants of the machine and 	// Standbyvarianten der Maschine werden abgefragt
	// activate the standby status as well as BDE-warning	// und der Standbystatus sowie BDE-Warnung aktiviert
	StandBy();

	// Möglichkeit SPS seitig die Servicezeit im BDE zu aktivieren
	// void Service_aktivieren(bool activate);
	Service_activate(false);
	
	// to enable the next step in the sequencer			// Freigabe zur Weiterschaltbedingung
	// according to the operational mode				// in den Schrittketten wird je nach Betriebsmodus zugewiesen
	StepEnable();

	// Reset of the controlling time is formed			// Reset der Kontrollzeit wird gebildet
	// Controlling time of the machine is activated		// Kontrollzeit der Maschine wird aktiviert
	// The variable "M_. MaError" is put				// Die Variable "M_.MaError" wird gesetzt
	// Protective door mistakes are formed				// Schutztürfehler werden gebildet
	// Error will look activated						// Fehler suchen wird aktiviert
	Error_MaOff();

	// to search for the prior and general errors					// vorrangige und allgemeine Störungen werden zugewiesen
	// e.g. emergency stop, 3 times rejects, safety door errors		// z.B. Not-Aus, 3xAusschuss, Schutztürfehler
	General_Error();

	// to set the variable "M_.Quit",								// Die Variable "M_.Entsperren" wird gesetzt,
	// so that errors and other functions will be reset				// hiermit werden Fehler und andere Funktionen zurückgesetzt
	Quit();

	// to query the "Air On" button									// Der "Luft Ein" Taster wird abgefragt
	// and assign the variable "M_.AirOn"							// Die Variable "M_.AirOn" zugewiesen
	Air_On_Off();

	// to control the airpressure on the air distributor			// Abfrage des Druckluftwächters am Luftverteiler
	Airpressure_control();

	// to assign the main air outputs										// Hauptluftausgänge werden gesetzt
	// and control the end position if errors happen						// Endstellung bei "PosFlanke Störung" kontrolliert
	// then the release of air "M_.PressureAirEn" will be assigned			// Die Freigabe der Luft "M_.PressureAirEn" wird gesetzt
	MainAir_On();

	MovingTest_End = true;
	for (WORD i=0;i<=MAX_MAINAIR;i++)
	{
		MovingTest(i);
		if (MovingTest_Start[i])
			MovingTest_End = false;
	}

	// to reset the main air outputs after errors					// Hauptluftausgänge werden je nach Störung zurückgesetzt
	MainAir_Off();
    

	// Conveyor sitch on/off													// Vibratoren Ein / Ausschalten
	// Enable Conveyor															// Freigabe der Vibratoren setzen
	// Set DelayTime															// Nachlaufzeit zuweisen
	// Transfer 1: Conveyor Reset = Set back the DelayTime from external 		// Übergabe 1: Vibratoren_Reset = Zurücksetzen der Nachlaufzeit von Außen
	// TODO: ConvReset control / complete										// TODO: Vibr_Reset kontrollieren / ergänzen?
    bool ConvReset  =   PosFlanke(Fl_ConveyorResetBefore,E_Gateway_before_SPS_Enable_Conveyor)
                    ||  PosFlanke(Fl_ConveyorResetFollowing,E_Gateway_following_SPS_Enable_Conveyor);
    bool QuitReset  =   PosFlanke(Fl_QuitResetBefore,E_Gateway_before_SPS_Quit)
                    ||  PosFlanke(Fl_QuitResetFollowing,E_Gateway_following_SPS_Quit);

    switch (MACHINETYPE)
    {
    case SINGLE_MG:
        Conveyor_OnOff(false, false);
        break;

    case FIRST_MG:
        Conveyor_OnOff(  E_Gateway_following_SPS_Enable_Conveyor,E_Gateway_following_SPS_Quit);
        break;

    case MIDDLE_MG:
        Conveyor_OnOff( ConvReset, QuitReset);
        break;

    case LAST_MG:
        Conveyor_OnOff(  E_Gateway_before_SPS_Enable_Conveyor,E_Gateway_before_SPS_Quit );
        break;
    }

	// to alarm light or bell according to the type of errors		// Leuchten und Hupen je nach Störung zuweisen
	ErrorLight();
	MachineLightning(SBTMaPart1.E_SingleStepMode, false);

	// Startmerker der Prüfstationen abfragen
	// Prüfungen fertig zuweisen
	// Ausschuss zählen durchführen
	// Funktion in SPSProg.h

	// to query the start marker of all stations at the main unit(axis)		// Startmerker aller Stationen an der Achse abfragen		
	// and then release the axis											// Freigabe der Achse zuweisen
	// Function in SPSProg.h												// Funktion in SPSProg.h
	Enable_DriveUnit();

	// to query if machine unload is activated from BDE,					// Abfrage ob leerfahren von BDE aktiviert wurde
	// control the register content in function "Machine_empty()",			// Registerinhalt kontrollieren "Maschine_leer()"
	// and assign machine unloaded, article released 						// Leergefahren, Artikelfreigabe zuweisen
	Unload_Machine();

	// to assign the sequence reset after emergency stop, IFCBit and so on	// Kettenreset zuweisen, nach Not-Aus, IFCBit etc.
	// Function in SPSProg.h												// Funktion in SPSProg.h
	Init();

#ifdef HVPruefung_vorhanden
	if (!Kalibrierung[HV1].Kalibrierung_Aktiv)
    {
#endif
	// Main process of axis				// Hauptablauf der Achse
	// Function in SPSKette.h			// Funktion in SPSKette.h
	// TODO: Check function				// TODO: Funktionen überprüfen
#if defined(DoubleAxis) || defined(SingleAxis)
		St201_MainProcess();
#endif

    // Main process of Plate			// Hauptablauf des Tellers
	// Function in St202_Kette_Teller.h	// Funktion in St202_Kette_Teller.h
	// TODO: Check function				// TODO: Funktionen überprüfen
	#ifdef Plate_exist
		St202_MainProcess();	// Plate with Servo		//Teller mit Servo
	#endif

	#ifdef Plate_FU_exist
		St203_MainProcess();	/// Plate with frequency converter	//Teller mit FU
	#endif

	#ifdef Plate_Siemens_FU_exist
		St204_MainProcess();	/// Plate with frequency converter	//Teller mit FU
	#endif



#ifdef HVPruefung_vorhanden
    }
#endif

	
	// to set the data of BDE, e.g. unload, singlestep,							// Daten von BDE zuweisen, z.B. Leerfahren, Einzelschritt
	// set the status variables for BDE,										// Statusvariablen für BDE zuweisen
	// calculate and set the machine data, e.g. clock cycle, good parts.		// Maschinendaten ermitteln und eintragen, z.B. Takte, Gutteile
	// Function in SPSProg.h													// Funktion in SPSProg.h
	BDE_Data_Transfer();

	// to call all the station processes										// Aufruf aller Stationsabläufe
	// Function in the directory "Stations"
	Stations_Process();

	// Aufruf Extraablauf, ein komplettes Hauptprogramm
	// Funktion in Extraablauf.h
	#ifdef Extraablauf
		ExtraGrundprogramm();
	#endif

	#ifdef Scanner_RFID_PN

	#endif

	// to implement the instruction of BDE: delete the shift register		// Befehl von BDE ausführen, Schieberegister der Maschine löschen

	if (PC_delete_Register) ShiftRegisterDelete();

	// It will be controlled in every cycle if one error is found.			// Es wird in jedem Zyklus kontrolliert ob ein Fehler gefunden
	// If found, the function error output will be called and 				// wurde. Sollte dieses der Fall sein, so wird die Funktion
	// error memory will be read out. 										// Fehlerausgeben aufgerufen und der Fehlerspeicher ausgelesen.
	// Through the variable "M_.MaStop und Allgemeiner_Fehler" 				// Über die Variablen "M_.MaStop und Allgemeiner_Fehler"
	// the general errors will be handled at first.							// werden die Allgemeinenfehler vorrangig behandelt.
	// Function in SPSProg.h												// Funktion in SPSProg.h
	ErrorProgram	(PRG1,							// number of the error program			// Nummer des Fehlerprogramms
				   M_.Newstart,					// new start of the machine part		// Neustart des Maschinenteils
				   M_.Quit,						// reset of the machine part			// Entsperren des Maschinenteils
				   M_.MaRun,					// run status of the machine part		// MaLaeuft des Maschinenteils
	#ifndef Error_of_BDE_display				// no Error announcement about INDEX3 of BDE		// keine Fehleranzeige über INDEX3 von BDE
				   true,						// Show Error by the internal functions 			// Fehler durch die internen Funktionen anzeigen
	#else
				   false,						// Error by BDE about INDEX 3 directly to the display program	//Fehler durch BDE über INDEX 3 direkt an das Anzeigeprg.
	#endif
				   T_Error);					// timer for error of the text display				// Zeitwerk für Fehler der Textanzeige

	// Error output over index 10											// Fehlerausgabe über Index 10
	// Erros are sent via index 10											// Fehler die über Index 10 gesendet werden
	// are not saved in BDE													// werden nicht im BDE gespeichert
	ErrorProgramIndex10(PRG1,M_.Quit);

	// to assign the article parameter and					// Nach Entsperren, Neustart oder Artikelwechsel
	// calculate the necessary positions of axis			// werden die Parameter des Artikels zugewiesen und
	// after unlock, restart or change article.				// die notwendigen Positionen der Achse berechnet
	// Function in SPSProg.h								// Funktionen in SPSProg.h
	if (NegFlanke(Fl_ChangeArticle,M_.ChangeArticle_PC)
	||  M_.Quit
	||  IFCBIT)
	{
		ArticleData();

		/********* Add by ZZH ****************/
		M.Vorgabe_Pruefzyklen = 100;
			M.Vorgabe_Ausschussquote = 100;
		// Zähler für Ausschußquote löschen
		if (!M_.Quit && !IFCBIT && M.Machine_Unloaded)
		{
			M.St8_Ausschuss_Pruefintervall	= false;

			// Werte werden durch die Abt. noch festgelegt und im Prg. hinterlegt
			M.Vorgabe_Pruefzyklen = 100;
			M.Vorgabe_Ausschussquote = 100;

			M.St8_Ausschussquote_sperren		 = FALSE;

			M.St8_Pruefzyklen = 0;
			M.St8_Ausschussquote = 0;
		}
		/**************************************/

		#if defined(DoubleAxis) || defined(SingleAxis)
// TODO: Check Setting		Einstellungen prüfen
			St201_CalculatePosition(DriveUnit1,Axis1);
		#endif
	}

	// to assign the states of output variables to			// Die Zustände der Ausgangsvariablen
	// the address of bus termials							// werden den Adressen der Busteilnehmer zugewiesen
	Output();

	// Remanentevariable "M.Marker_ok" für Speicherfehler aktivieren
	if (IFCBIT)
	{
		SetTimeValue();	// Time values of the general times	SPSPROG.h		// Zeitwerte der allgemeinen Zeiten einstellen in SPSPROG.h

		for (WORD i=1;i<=MAX_MAINAIR;i++)
		{
			T_Bewegungstest[i].SetTimerLoad(500);
			T_Verz_Hauptluft_aus[i].SetTimerLoad(500);
		}

		if (!M.Marker_ok)
		{
            WORD Offset = MAPARTNUM * 1000;

            // Einfachregister
			for (WORD i=0;i<=MAXREGISTER;i++)
			{
				for (WORD j=0;j<=MAXREGISTER_LENGTH;j++)
				{
                    // Ausschuß durch Dateifehler
					SetRegister( i, j, ( 10999 + Offset ) );
				}
			}

			// 3D Register
			for(WORD i=0;i<=MAX3DREGISTER;i++)
			{
				for(WORD j=1;j<=MAX3DREGISTER_BLOCK;j++)
				{
					for(WORD k=0;k<=MAX3DREGISTER_LENGTH;k++)
					{
                        // Ausschuß durch Dateifehler
						SetRegister_3D( i, j, k, ( 10999 + Offset ) );
					}
				}
			}

			M_.Error_Marker_OK = true;
		}//of !M.Marker_ok

		#if defined(Scanner_V24) || defined(Scanner_IBS_RS232)
			DV_Stoerungen_loeschen(TRUE);
            WPC_Data_request = true;
			WPC_Data_received = false;
		#endif

		
		// Maschinenbeleuchung
		A_Machine_Lamp = true;


	}

	StopWatchMain();

#ifdef ProfinetActive	
	ProfinetMain();
#endif

	// Startbit zurücksetzen, nur im ersten Zyklus aktiv
	IFCBIT = false;

	// Sonstige Globale Funktionen aufrufen
	AllStationsSingleStepMode();

	// Sonstige Funktionsaufrufe
	if (M_.APCIDatenAusgeben)
	{
		M_.APCIDatenAusgeben = false;
		APCISlotNummerAusgeben();
	}
}// of void MachineProcess1(...)

//*****************************************************************
//*****************  Hauptablauf 2  niedrige Priorität  ***********
//*****************************************************************

//*****************************************************************
//***************  Machine process 2: low Priority   **************
//*****************************************************************
void MachineProcess2(void)
{
	//
}
