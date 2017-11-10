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

#include "St01_1_Extra_housing_separate.h"
#include "St01_2_Extra_housing_foot_pusher.h"
#include "St01_3_Extra_housing_foot_test.h"
#include "St01_4_Extra_reject_housing_remove.h"
#include "St01_Insert_Housing_01.h"
#include "St01_Press_Cover.h"
//#include "St01_Insert_Housing_02.h"
#include "St02_Check_Housing.h"
#include "St04_Check_Pressure_Plate .h"
#include "St06_Check_Flange_Screw.h"
#include "St09_Check_Screw_Available.h"
#include "St10_Camera_Pressure_Plate.h"
#include "St11_Screw_Test.h"
#include "St13_Camera_Screw.h"
#include "St12_Screw_Test.h"
#include "St14_Screw_take_out.h"
#include "St03_Insert_Pressure_Plate.h"
#include "St05_Insert_Clamping_Sleeve.h"
#include "St08_Screw_Insert.h"
#include "St16_Reject_Take_Out.h"


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
 //   Teller[Plate1].E_Motor_SafeTorqueOff       	= Eing(A31, 6);  // 
	//Teller[Plate1].E_Motor_Bereit              	= Eing(A31, 7);
	E_Unload_Machine			                = Eing(A31, 8);						// switch in the cable canal	// Taster im Kabelkanal
  	E_Bridge_StandByPosition		            = Eing(A31, 9);						// switch in the cable canal	// Taster im Kabelkanal
    E_Button_Quit				                = Eing(A31,10) || E_Button_Quit;	// switch in the cable canal	// -B1 (Taster im Kabel-Kanal)
//  frei                                        = Eing(A31,11);
//  frei                                        = Eing(A31,12);	
//  frei                                        = Eing(A31,13);	
//  frei                                        = Eing(A31,14);	
//  frei                                        = Eing(A31,15);

//	frei										= Eing(A32, 0);
//	frei										= Eing(A32, 1);
	E_Button_ProcessObservationMode				= Eing(A32, 2);	// +M-XES5.1AN:2
//	frei										= Eing(A32, 3);
//	frei										= Eing(A32, 4);
//	frei										= Eing(A32, 5);
	SBTMaPart1.E_Door[1]				        = Eing(A33, 8);	// -S401.1
	SBTMaPart1.E_Door[2]				        = Eing(A33, 9);	// -S401.2
	SBTMaPart1.E_Door[3]				        = Eing(A33,10);	// -S401.3
	SBTMaPart1.E_Door[4]				        = Eing(A33,11);	// -S401.4
	SBTMaPart1.E_Door[5]				        = Eing(A33,12);	// -S402.1
	SBTMaPart1.E_Door[6]				        = Eing(A33,13);	// -S402.2
	SBTMaPart1.E_Door[7]				        = Eing(A33,14);	// -S402.3
	SBTMaPart1.E_Door[8]				        = Eing(A33,15);	// -S402.4
	E_PressureSwitch				            = Eing(A32,14); // -S01
//	frei										= Eing(A32,15);
	

// ******************************
// -GATEWAY- /IB IL 24 DI/32
// ******************************
    E_Gateway_following_SPS_Enable_Conveyor		= Eing(GATEWAY_CT_1_W9,0);	//<-enable conveyer of the following SPS receive		//<- Freigabe der Vibratoren von folgender SPS empfangen
    E_Gateway_following_SPS_Quit				= Eing(GATEWAY_CT_1_W9,1);	//<-E_Quit of the following SPS receive				 	//<- E_TP_Quittieren von folgender SPS empfangen
   
    E_Gateway_following_SPS_Unloaded            = Eing(GATEWAY_CT_1_W9,2) || (MACHINETYPE == SINGLE_MG) ||  (MACHINETYPE == LAST_MG);	//<-Machine unloaded of the following SPS receive //<- Maschine leergefahren von folgender SPS empfangen
    E_Gateway_following_SPS_St302_FlexLink_Run  = Eing(GATEWAY_CT_1_W9,3);	//<-Flix Link run of the following SPS receive			//<- Zwischenförderband läuft von folgender SPS empfangen
//	E_Gateway_folgende_SPS_Eingang_5			    = Eing(GATEWAY_CT_1_W9,4);	//<- 
//	E_Gateway_folgende_SPS_Eingang_6			    = Eing(GATEWAY_CT_1_W9,5);	//<- 
//	E_Gateway_folgende_SPS_Eingang_7			    = Eing(GATEWAY_CT_1_W9,6);	//<- 
//	E_Gateway_folgende_SPS_Eingang_8                = Eing(GATEWAY_CT_1_W9,7);	//<- 
// 	frei										    = Eing(GATEWAY_CT_1_W9,8);
// 	frei										    = Eing(GATEWAY_CT_1_W9,9);
// 	frei										    = Eing(GATEWAY_CT_1_W9,10);
// 	frei										    = Eing(GATEWAY_CT_1_W9,11);
// 	frei										    = Eing(GATEWAY_CT_1_W9,12);
// 	frei										    = Eing(GATEWAY_CT_1_W9,13);
//	frei										    = Eing(GATEWAY_CT_1_W9,14);
//	frei								            = Eing(GATEWAY_CT_1_W9,15);

//   E_Gateway_before_SPS_Enable_Conveyor		= Eing(GATEWAY_CT_2_W9,0);	//<- enable conveyer of previous SPS receive		//<- Freigabe der Vibratoren von vorheriger SPS empfangen
//	E_Gateway_before_SPS_Quit					= Eing(GATEWAY_CT_2_W9,1);	//<- E_Quit of previous SPS receive					//<- E_TP_Quittieren von vorheriger SPS empfangen
//	E_Gateway_before_SPS_Unloaded				= Eing(GATEWAY_CT_2_W9,2);	//<- Machine unloaded of previous SPS receive		//<- Maschine leergefahren von vorheriger SPS empfangen
//	M_Gateway_St301_FlexLink_Run                = Eing(GATEWAY_CT_2_W9,3);	//<- Flix Link run of previous SPS receive			//<- Umlaufförderband läuft von vorheriger SPS empfangen
//	E_Gateway_before_SPS_St302_FlexLink_full	= Eing(GATEWAY_CT_2_W9,4);	//<- Connecting conveyor belt full of previous SPS receive	//<- Verbindungsförderband voll von vorheriger SPS empfangen
//	E_Gateway_vorherige_SPS_Eingang_6			    = Eing(GATEWAY_CT_2_W9,5);	//<- 
//	E_Gateway_vorherige_SPS_Eingang_7			    = Eing(GATEWAY_CT_2_W9,6);	//<- 
//	E_Gateway_vorherige_SPS_Eingang_8               = Eing(GATEWAY_CT_2_W9,7);	//<- 
//	frei										    = Eing(GATEWAY_CT_2_W9,8);
//	frei										    = Eing(GATEWAY_CT_2_W9,9);
//	frei										    = Eing(GATEWAY_CT_2_W9,10);
//	frei										    = Eing(GATEWAY_CT_2_W9,11);
//	frei										    = Eing(GATEWAY_CT_2_W9,12);
//	frei										    = Eing(GATEWAY_CT_2_W9,13);
//	frei										    = Eing(GATEWAY_CT_2_W9,14);
//	frei										    = Eing(GATEWAY_CT_2_W9,15);  
//-----------------------------------------------------------------
//---------------------------- +SK02A -----------------------------
//-----------------------------------------------------------------
// ******************************
// -A40- /IB IL 24 DI/16
// ******************************
#ifdef Axis_exist
	Achse[Axis1].E_Controller_OK				    = Eing(A42,0); // -A201.1/27
	Achse[Axis1].E_Motor_stand					    = Eing(A42,1); // -A201.1/25
	Achse[Axis1].E_Pos_StopPosition				    = Eing(A42,4); // +201-B1
	Achse[Axis1].E_Neg_StopPosition				    = Eing(A42,5); // +201-B2
	Achse[Axis1].E_Ref_Switch						= Eing(A42,6); // +201-B3

	E_St201_B4_WPC_InPosition					    = Eing(A42,7); // +201-B4
	//Achse[Axis2].E_Controller_OK				    = Eing(A42,8); // -A1.1/27
	//Achse[Axis2].E_Motor_stand					    = Eing(A42,9); // -A1.1/25
	//Achse[Axis2].E_Pos_StopPosition				    = Eing(A42,12); // 
	//Achse[Axis2].E_Neg_StopPosition				    = Eing(A42,13); // 
	//Achse[Axis2].E_Ref_Switch						= Eing(A42,14); // +1-B3
#endif
//	frei										    = Eing(A40,5);
//	frei										    = Eing(A40,6);
//	frei										    = Eing(A40,7);
//	frei										    = Eing(A40,8);
//	frei										    = Eing(A40,9);
//	frei										    = Eing(A40,10);
//	frei										    = Eing(A40,11);
//	frei										    = Eing(A40,12);
//	frei										    = Eing(A40,13);
//	frei										    = Eing(A40,14);


//Steuerwort KEB-Servo St.1
	St_1_KEB_Einsetzen.E_Reglerfreigabe						=Eing(A800,0);	
	St_1_KEB_Einsetzen.E_Fehler								=Eing(A800,1);	
	St_1_KEB_Einsetzen.E_Run								=Eing(A800,2);	
	St_1_KEB_Einsetzen.E_Drehrichtung						=Eing(A800,3);	
	St_1_KEB_Einsetzen.E_Aktuelle_Parametersatz_Bit1		=Eing(A800,4);	
	St_1_KEB_Einsetzen.E_Aktuelle_Parametersatz_Bit2		=Eing(A800,5);	
	St_1_KEB_Einsetzen.E_Aktuelle_Parametersatz_Bit3		=Eing(A800,6);	
	St_1_KEB_Einsetzen.E_Schnellhalt_aktiv					=Eing(A800,8);	
	St_1_KEB_Einsetzen.E_Referenzpunktfahrt_abgeschlossen	=Eing(A800,10);	
	St_1_KEB_Einsetzen.E_Position_erreicht					=Eing(A800,11);	
	St_1_KEB_Einsetzen.E_Betriebsart_Bit1					=Eing(A800,12);	
	St_1_KEB_Einsetzen.E_Betriebsart_Bit2					=Eing(A800,13);	
	St_1_KEB_Einsetzen.E_Position_uebernommen				=Eing(A800,14);	
	St_1_KEB_Einsetzen.Istposition_high						=EingWortEx(A800,1);
	St_1_KEB_Einsetzen.Istposition_low						=EingWortEx(A800,2);
// *************************
// -A43- /FLS IB M12 DI 8 
// *************************
#ifdef Plate_Siemens_FU_exist 
//	Teller[Plate1].E_P_Nocke					    = Eing(A43,0);		// St.204
//	Teller[Plate2].E_P_Nocke					    = Eing(A43,1);		// St.??
//	Teller[Plate3].E_P_Nocke					    = Eing(A43,2);		// St.??
//	frei										    = Eing(A43,3);		
//	frei											= Eing(A43,4);		
//	frei											= Eing(A43,5);		
//	frei										    = Eing(A43,6);
//	frei										    = Eing(A43,7);
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
	//free											= Eing(A50,0);
	//free											= Eing(A50,1);
	//free											= Eing(A50,2);
	//free											= Eing(A50,3);
	E_St1_B8_4_gripper_lifter_down					= Eing(A50,4);
	E_St1_B8_2_gripper_lifter_up					= Eing(A50,5);
	E_St1_B10_4_housing_foot_test_driver_in_front	= Eing(A50,6);
	E_St1_B10_2_housing_foot_test_driver_back		= Eing(A50,7);
	
// *************************
// -A51- /FLS IB M12 DI 8 
// *************************
	E_St1_B11_4_fork_driver_down					= Eing(A51,0);
	E_St1_B11_2_fork_driver_up						= Eing(A51,1);
	E_St1_B12_4_fork_position_driver_in_front		= Eing(A51,2);
	E_St1_B12_2_fork_position_driver_back			= Eing(A51,3);
	E_St1_B13_4_fork_position_driver_in_front		= Eing(A51,4);
	E_St1_B13_2_fork_position_driver_back			= Eing(A51,5);
	E_St1_B14_4_housing_guider_switcher_up			= Eing(A51,6);
	E_St1_B14_2_housing_guider_switcher_down		= Eing(A51,7);

// *************************
// -A52- /FLS IB M12 DI 8 
// *************************
	E_St1_B15_4_housing_presser_down		    	= Eing(A52,0);
	E_St1_B15_2_housing_presser_up			    	= Eing(A52,1);
	//free											= Eing(A52,2);
	//free											= Eing(A52,3);
	E_St1_B5_4_carrier_pos_switcher_driver_in_front	= Eing(A52,4);
	E_St1_B5_2_carrier_pos_switcher_driver_back		= Eing(A52,5);
	E_St1_B16_4_carrier_opener_in_front				= Eing(A52,6);
	E_St1_B16_2_carrier_opener_back      			= Eing(A52,7);		

// *************************
// -A53- /FLS IB M12 DI 8 
// *************************
	E_St1_B17_4_carrier_opener_in_front				= Eing(A53,0);
	E_St1_B17_2_carrier_opener_back					= Eing(A53,1);
	E_St1_B18_4_carrier_opener_in_front				= Eing(A53,2);
	E_St1_B18_2_carrier_opener_back					= Eing(A53,3);
	E_St1_B19_4_carrier_opener_in_front				= Eing(A53,4);
	E_St1_B19_2_carrier_opener_back					= Eing(A53,5);
	E_St1_B9_4_gripper_lifter_driver_in_front		= Eing(A53,6);
	E_St1_B9_2_gripper_lifter_driver_back			= Eing(A53,7);	

	EW_St1_B2_carrier_switcher_position		= EingWortEx(A400,0);
// *************************
// -A54- /FLS IB M12 DI 8 
// *************************
	E_St8_B1_4_screw_inserter_driver_in_front		= Eing(A54,0);
	E_St8_B1_2_screw_inserter_driver_back			= Eing(A54,1);
	E_St8_B2_4_screw_inserter_in_right				= Eing(A54,2);
	E_St8_B2_2_screw_inserter_in_left				= Eing(A54,3);
	E_St8_B3_4_metal_parts_holder_down	            = Eing(A54,4);
	E_St8_B3_2_metal_parts_holder_up	            = Eing(A54,5);
	E_St5_B1_4_clamping_sleeve_inserter_holder_down	= Eing(A54,6);
	E_St5_B1_2_clamping_sleeve_inserter_holder_up	= Eing(A54,7);

// *************************
// -A55- /FLS IB M12 DI 8 
// *************************
	E_St5_B2_4_clamping_sleeve_inserter_down		= Eing(A55,0);
	E_St5_B2_2_clamping_sleeve_inserter_up			= Eing(A55,1);
	E_St3_B1_4_pressure_plate_separator_in_left		= Eing(A55,2);
	E_St3_B1_2_pressure_plate_separator_in_right	= Eing(A55,3);
	//free											= Eing(A55,4);
	//free											= Eing(A55,5);
	//free											= Eing(A55,6);
	//free											= Eing(A55,7);

// *************************
// -A56- /FLS IB M12 DI 8 
// *************************
	E_St12_B1_4_screw_test_in_front					= Eing(A56,0);
	E_St12_B1_2_screw_test_back						= Eing(A56,1);
	E_St12_B2_4_metal_parts_holder_down				= Eing(A56,2);
	E_St12_B2_2_metal_parts_holder_up				= Eing(A56,3);
	E_St11_B1_4_screw_test_in_front					= Eing(A56,4);
	E_St11_B1_2_screw_test_back						= Eing(A56,5);
	E_St11_B2_4_hook_driver_down					= Eing(A56,6);
	E_St11_B2_2_hook_driver_up						= Eing(A56,7);

// *************************
// -A57- /FLS IB M12 DI 8 
// *************************
	E_St10_B1_4_metal_parts_holder_down				= Eing(A57,0);
	E_St10_B1_2_metal_parts_holder_up				= Eing(A57,1);
	E_St9_B1_4_screw_tester_driver_in_front			= Eing(A57,2);
	E_St9_B1_2_screw_tester_driver_back				= Eing(A57,3);
	E_St8_B4B_4_screw_seperate_up					= Eing(A57,4);
	E_St8_B4B_2_screw_seperate_down					= Eing(A57,5);
	E_St8_B4A_4_screw_seperate_up					= Eing(A57,6);
	E_St8_B4A_2_screw_seperate_down					= Eing(A57,7);

// *************************
// -A58- /FLS IB M12 DI 8 
// *************************
	E_St16_B8_4_carrier_opener_in_front				= Eing(A58,0);
	E_St16_B8_2_carrier_opener_back					= Eing(A58,1);
	E_St16_B9_4_carrier_opener_in_front				= Eing(A58,2);
	E_St16_B9_2_carrier_opener_back					= Eing(A58,3);
	E_St16_B10_4_carrier_opener_in_front			= Eing(A58,4);
	E_St16_B10_2_carrier_opener_back				= Eing(A58,5);
	E_St14_B1_4_screw_tester_driver_in_front		= Eing(A58,6);
	E_St14_B1_2_screw_tester_driver_back			= Eing(A58,7);

// *************************
// -A59- /FLS IB M12 DI 8 
// *************************
	E_St14_B2_4_gripper_driver_in_front				= Eing(A59,0);
	E_St14_B2_2_gripper_driver_back					= Eing(A59,1);
	//free											= Eing(A59,2);
	//free											= Eing(A59,3);
	E_St14_B4_4_metal_parts_presser_in_front		= Eing(A59,4);
	E_St14_B4_2_metal_parts_presser_back			= Eing(A59,5);
	E_St14_B5_4_housing_holder_up					= Eing(A59,6);
	E_St14_B5_2_housing_holder_down					= Eing(A59,7);

//**************************
// -A60- /FLS IB M12 DI 8 
// *************************
	E_St16_B1_4_reject_parts_driver_in_front		= Eing(A60,0);
	E_St16_B1_2_reject_parts_driver_back			= Eing(A60,1);
	E_St16_B2_4_reject_parts_stopper_up				= Eing(A60,2);
	E_St16_B2_2_reject_parts_stopper_down			= Eing(A60,3);
	E_St16_B3_4_reject_parts_stopper_up				= Eing(A60,4);
	E_St16_B3_2_reject_parts_stopper_down			= Eing(A60,5);
	E_St16_B4_4_reject_parts_stopper_up				= Eing(A60,6);
	E_St16_B4_2_reject_parts_stopper_down			= Eing(A60,7);
	

// *************************
// -A61- /FLS IB M12 DI 8 
// *************************
	E_St16_B5_4_gripper_lifter_down					= Eing(A61,0);
	E_St16_B5_2_gripper_lifter_up					= Eing(A61,1);
	E_St16_B1_4A									= Eing(A61,2);
	E_St16_B1_4B									= Eing(A61,3);
	E_St16_B1_4C									= Eing(A61,4);
	//free											= Eing(A61,5);
	//free											= Eing(A61,6);
	//free											= Eing(A61,7);	

// **************************************
// -A110- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************
	E_St3_B1_pressure_plate_in_position             = Eing(A110,0);
	E_St3_B2_linear_feeder_empty	                = Eing(A110,1);
	E_St3_B3_linear_feeder_full		             	= Eing(A110,2); 
	//free									     	= Eing(A110,3);
											     
											     
											     
// **************************************	     
// -A111- /FLS IB M12 DIO 4/4 (US3/US3)		     
// **************************************	     
	E_St8_B2B_screw_in_position                     = Eing(A111,0);
	E_St8_B3B_screw_channel_full                    = Eing(A111,1);
	E_St8_B4B_screw_bunker_empty			     	= Eing(A111,2); 
	//free									     	= Eing(A120,3);
// **************************************	     
// -A112- /FLS IB M12 DIO 4/4 (US3/US3)		     
// **************************************	     
	E_St8_B2A_screw_in_position                     = Eing(A112,0);
	E_St8_B3A_screw_channel_full                    = Eing(A112,1);
	E_St8_B4A_screw_bunker_empty			     	= Eing(A112,2); 
	//free									     	= Eing(A112,3); 
// **************************************	     
// -A113- /FLS IB M12 DIO 4/4 (US3/US3)		     
// **************************************	     
	E_St8_B1_screw_in_separated_position            = Eing(A113,0);
	//E_St6_B1_clamping_sleeve_available	     	= Eing(A113,1);
	E_St6_B1_flange_screw_available	         	= Eing(A113,2); 
	E_St6_B2_flange_screw_available	         	= Eing(A113,3); 

// *************************
// -A114- /FLS IB M12 DI 8 
// *************************
    E_St9_B1_screw_available						= Eing(A114,0);
	E_St4_B1_cover_hole_checking   	     	            = Eing(A114,1);
	E_St4_B2_clip_available				    = Eing(A114,2);
 //	E_St1_B6_housing_foot_checking					= Eing(A114,3); 
	E_St2_B1_Housing_with_flange_front_position		= Eing(A114,4);
	E_St2_B2_Housing_empty_checking					= Eing(A114,5);
    E_St2_B3_Houisng_poles_checking					= Eing(A114,6);
	E_St2_B4_Housing_with_flange_back_position      = Eing(A114,7);

// *************************
// -A115- /FLS IB M12 DI 8 
// *************************
	E_St201_B1_4_SwivelUnit_in_front				= Eing(A115,0); // +201-B1/4
	E_St201_B1_2_SwivelUnit_back					= Eing(A115,1); // +201-B1/2
    E_St302_B1_FB_voll								= Eing(A115,2);
	//E_St4_B1_cover_hole_checking	     	        = Eing(A115,1);
	//E_St4_B2_clip_available				        = Eing(A115,2);
 //	E_St1_B6_housing_foot_checking					= Eing(A115,3); 

// *************************
// -A116- /FLS IB M12 DI 8 
// *************************
	E_St1_Bunknown								    = Eing(A116,1);//remarkremark unused
	E_St1_B7_housing_position_checking	     	    = Eing(A116,0);
	E_St1_B5_housing_foot_checking				    = Eing(A116,2);
 	E_St1_B6_housing_foot_checking					= Eing(A116,3); 
	E_St1_B8_housing_in_position				    = Eing(A116,4);
	E_St1_B2_carrier_switcher_position_Check	    = Eing(A116,5);
//	frei										    = Eing(A116,6);
//	frei										    = Eing(A116,7);

// *************************
// -A117- /FLS IB M12  DIO 4/4 (US3/US3)
// *************************
	E_St5_B1_Clamping_sleeve_in_position			= Eing(A117,0);
	E_St5_B2_Clamping_sleeve_channel_empty			= Eing(A117,1);
	E_St5_B3_Clamping_sleeve_channel_full			= Eing(A117,2);
 	E_St5_B4_bunker_empty								= Eing(A117,3); 


// **************************************
// -A118- /FLS IB M12 DIO 4/4 (US2/US3)
// **************************************
	E_St1_B15_short_housing_selected				= Eing(A118,0); 
	E_St1_B16_long_housing_selected					= Eing(A118,1); 
	E_St1_B17_short_BF_empty             			= Eing(A118,2);
	E_St1_B18_short_bunker_jammed			        = Eing(A118,3);

// **************************************
// -A119- /FLS IB M12 DIO 4/4 (US2/US3)
// **************************************
	E_St1_B1_housing_in_position     				= Eing(A119,0); 
	E_St1_B3_housing_channel_empty					= Eing(A119,1); 
	E_St1_B4_housing_channel_full                   = Eing(A119,2);
	E_St1_B9_housing_channel_empty                  = Eing(A119,3);


// **************************************
// -A120- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************

	E_St1_B11_housing_channel_full                  = Eing(A120,0);
	E_St1_B19_long_BF_empty                         = Eing(A120,1);
	E_St1_B20_long_bunker_jammed				    = Eing(A120,2); 
	//E_St301_B3_AxisProtector_in_front				= Eing(A120,3); 

// **************************************
// -A121- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************

//	frei                                            = Eing(A121,0);
//	frei                                            = Eing(A121,1);
//	E_St301_B2_AxisProtector_in_front				= Eing(A121,2); 
//	E_St301_B3_AxisProtector_in_front				= Eing(A121,3); 



//##END_EINGAENGE      Zeile nicht loeschen		don't delete this line


#ifdef Camera_Pipe_exist
// TODO: Eingaenge von der Kamera prüfen
// Pipe-Übergaben zum Kamerarechner 1
	E_Kamera_fertig[1]			= Kameradaten_E[KameraPC_1].Fertigmeldung_Kamera1;
	E_Kamera_Gutmeldung[1]		= Kameradaten_E[KameraPC_1].Gutmeldung_Kamera1;
	E_Kamera_Beleuchtung_OK[1]	= Kameradaten_E[KameraPC_1].Beleuchtung_Kamera1_ok;
	E_Kamera_Beleuchtung_ein[1]	= Kameradaten_E[KameraPC_1].Beleuchtung_Kamera1_ein;

	E_Kamera_fertig[2]			= Kameradaten_E[KameraPC_1].Fertigmeldung_Kamera2;
	E_Kamera_Gutmeldung[2]		= Kameradaten_E[KameraPC_1].Gutmeldung_Kamera2;
	E_Kamera_Beleuchtung_OK[2]	= Kameradaten_E[KameraPC_1].Beleuchtung_Kamera2_ok;
	E_Kamera_Beleuchtung_ein[2]	= Kameradaten_E[KameraPC_1].Beleuchtung_Kamera2_ein;

	E_Kameraprogramm_RUN[KameraPC_1]		= Kameradaten_E[KameraPC_1].Kameraprogramm_laeuft;
#endif//#ifdef Camera_Pipe_exist



//TODO: Zuweisen der Zylindervariablen, die als Bewegungstest dienen sollen
//		Assign to the cylinder variable who should serve as a movement test

	//E_MovingTest_in_front[1]	= E_St3_B5_4_WT_Oeffner_vorne;
	//E_MovingTest_back[1]		= E_St3_B5_2_WT_Oeffner_hinten;


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
	SetAusg(A1,0,A.St1_Y11_4_fork_driver_downward);			
	SetAusg(A1,1,A.St1_Y11_2_fork_driver_upward);			
	SetAusg(A1,2,A.St1_Y12_4_fork_position_driver_forward);		
	SetAusg(A1,3,A.St1_Y12_2_fork_position_driver_backward);		
	SetAusg(A1,4,A.St1_Y13_4_fork_position_driver_forward);
	SetAusg(A1,5,A.St1_Y13_2_fork_position_driver_backward);				
	SetAusg(A1,6,A.St1_Y14_4_housing_guider_switcher_upward);					
	SetAusg(A1,7,A.St1_Y14_2_housing_guider_switcher_downward);					
	SetAusg(A1,8,A.St1_Y6_4_housing_gripper_close);			
	SetAusg(A1,9,A.St1_Y6_2_housing_gripper_open);			
	SetAusg(A1,10,A.St1_Y7_4_housing_gripper_close);		
	SetAusg(A1,11,A.St1_Y7_2_housing_gripper_open);			
	SetAusg(A1,12,A.St1_Y8_4_gripper_lifter_downward);		
	SetAusg(A1,13,A.St1_Y8_2_gripper_lifter_upward);			
	SetAusg(A1,14,A.St1_Y10_4_housing_foot_test_driver_forward);		
	SetAusg(A1,15,A.St1_Y10_2_housing_foot_test_driver_backward);		
}
else
{
	SetAusg (A1,0,false);
	SetAusg (A1,1,false);
	SetAusg (A1,2,false);
	SetAusg (A1,3,false);
	SetAusg (A1,4,false);
	SetAusg (A1,5,false);
	SetAusg (A1,6,A_MovingTest_forward[1]);
	SetAusg (A1,7,A_MovingTest_backward[1]);
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
	SetAusg(A2,0,A.St1_Y17_4_carrier_opener_forward);					
	SetAusg(A2,1,A.St1_Y17_2_carrier_opener_backward);						
	SetAusg(A2,2,A.St1_Y18_4_carrier_opener_forward);					
	SetAusg(A2,3,A.St1_Y18_2_carrier_opener_backward);				
	SetAusg(A2,4,A.St1_Y19_4_carrier_opener_forward);				
	SetAusg(A2,5,A.St1_Y19_2_carrier_opener_backward);				
	SetAusg(A2,6,A.St1_Y9_4_gripper_lifter_driver_forward);		
	SetAusg(A2,7,A.St1_Y9_2_gripper_lifter_driver_backward);	
	SetAusg(A2,8,A.St1_Y1_4_housing_gripper_close);		
	SetAusg(A2,9,A.St1_Y1_2_housing_gripper_open);	
	SetAusg(A2,10,A.St1_Y4_4_carrier_pos_switcher_forward );	
	SetAusg(A2,11,A.St1_Y4_2_carrier_pos_switcher_backward);
	SetAusg(A2,12,A.St1_Y5_4_carrier_pos_switcher_driver_forward );		
	SetAusg(A2,13,A.St1_Y5_2_carrier_pos_switcher_driver_backward);			
	SetAusg(A2,14,A.St1_Y16_4_carrier_opener_forward);			
	SetAusg(A2,15,A.St1_Y16_2_carrier_opener_backward);			
}
else
{
	SetAusg (A2,0,false);
	SetAusg (A2,1,false);
	SetAusg (A2,2,false);
	SetAusg (A2,3,false);
	SetAusg (A2,4,false);
	SetAusg (A2,5,false);
	SetAusg (A2,6,A_MovingTest_forward[2]);
	SetAusg (A2,7,A_MovingTest_backward[2]);
	SetAusg (A2,8,false);
	SetAusg (A2,9,false);
	SetAusg (A2,10,false);
	SetAusg (A2,11,false);
	SetAusg (A2,12,false);
	SetAusg (A2,13,false);
	SetAusg (A2,14,false);
	SetAusg (A2,15,false);

}

if (!M_Error_Air_Off[3])
{
	SetAusg(A3,0,A.St5_Y2_4_clamping_sleeve_inserter_downward);			
	SetAusg(A3,1,A.St5_Y2_2_clamping_sleeve_inserter_upward);			
	SetAusg(A3,2,A.St3_Y1_4_pressure_plate_separator_leftward);			
	SetAusg(A3,3,A.St3_Y1_2_pressure_plate_separator_rightward);			
	SetAusg(A3,4,A.St1_Y15_4_housing_presser_downward);				
	SetAusg(A3,5,A.St1_Y15_2_housing_presser_upward);			
	SetAusg(A3,6,A.St1_Y3_4_end_position_exchanger_forward);					
	SetAusg(A3,7,A.St1_Y3_2_end_position_exchanger_backward);			
	SetAusg(A3,8,A.St8_Y1_4_screw_inserter_driver_forward);	
	SetAusg(A3,9,A.St8_Y1_2_screw_inserter_driver_backward);	
	SetAusg(A3,10,A.St8_Y2_4_screw_inserter_rightward);		
	SetAusg(A3,11,A.St8_Y2_2_screw_inserter_leftward);			
	SetAusg(A3,12,A.St8_Y3_4_metal_parts_holder_downward);	
	SetAusg(A3,13,A.St8_Y3_2_metal_parts_holder_upward);
	SetAusg(A3,14,A.St5_Y1_4_clamping_sleeve_inserter_holder_downward);		  
	SetAusg(A3,15,A.St5_Y1_2_clamping_sleeve_inserter_holder_upward);		  
}
else
{
	SetAusg (A3,0,false);
	SetAusg (A3,1,false);
	SetAusg (A3,2,false);
	SetAusg (A3,3,false);
	SetAusg (A3,4,false);
	SetAusg (A3,5,false);
	SetAusg (A3,6,A_MovingTest_forward[3]);
	SetAusg (A3,7,A_MovingTest_backward[3]);
	SetAusg (A3,8,false);
	SetAusg (A3,9,false);
	SetAusg (A3,10,false);
	SetAusg (A3,11,false);
	SetAusg (A3,12,false);
	SetAusg (A3,13,false);
	SetAusg (A3,14,false);
	SetAusg (A3,15,false);

}

if (!M_Error_Air_Off[4])
{
	SetAusg(A4,0,A.St10_Y1_4_metal_parts_holder_downward);					
	SetAusg(A4,1,A.St10_Y1_2_metal_parts_holder_upward);		
	SetAusg(A4,2,A.St9_Y1_4_screw_tester_driver_forward);			
	SetAusg(A4,3,A.St9_Y1_2_screw_tester_driver_backward);		
	SetAusg(A4,4,A.St8_Y4B_4_screw_seperate_upward);			
	SetAusg(A4,5,A.St8_Y4B_2_screw_seperate_downward);			
	SetAusg(A4,6,A.St8_Y4A_4_screw_seperate_upward);		
	SetAusg(A4,7,A.St8_Y4A_2_screw_seperate_downward);					
	SetAusg(A4,8,A.St12_Y1_4_screw_test_forward);			
	SetAusg(A4,9,A.St12_Y1_2_screw_test_backward);			
	SetAusg(A4,10,A.St12_Y2_4_metal_parts_holder_downward);		
	SetAusg(A4,11,A.St12_Y2_2_metal_parts_holder_upward);			
	SetAusg(A4,12,A.St11_Y1_4_screw_test_forward);		
	SetAusg(A4,13,A.St11_Y1_2_screw_test_backward);			
	SetAusg(A4,14,A.St11_Y2_4_hook_driver_downward);		
	SetAusg(A4,15,A.St11_Y2_2_hook_driver_upward);		
}
else
{
	SetAusg (A4,0,false);
	SetAusg (A4,1,false);
	SetAusg (A4,2,false);
	SetAusg (A4,3,false);
	SetAusg (A4,4,false);
	SetAusg (A4,5,false);
	SetAusg (A4,6,false);
	SetAusg (A4,7,false);
	SetAusg (A4,8,false);
	SetAusg (A4,9,false);
	SetAusg (A4,10,false);
	SetAusg (A4,11,false);
	SetAusg (A4,12,false);
	SetAusg (A4,13,false);
	SetAusg (A4,14,false);
	SetAusg (A4,15,false);

}

if (!M_Error_Air_Off[5])
{
	SetAusg(A5,0,A.St14_Y2_4_gripper_driver_forward);			
	SetAusg(A5,1,A.St14_Y2_2_gripper_driver_backward);			
	SetAusg(A5,2,A.St14_Y3_4_screw_gripper_close);		
	SetAusg(A5,3,A.St14_Y3_2_screw_gripper_open);		
	SetAusg(A5,4,A.St14_Y4_4_metal_parts_presser_forward);		
	SetAusg(A5,5,A.St14_Y4_2_metal_parts_presser_backward);		
	SetAusg(A5,6,A.St14_Y5_4_housing_holder_upward);
	SetAusg(A5,7,A.St14_Y5_2_housing_holder_downward);
	SetAusg(A5,8,A.St16_Y8_4_carrier_opener_forward);		
	SetAusg(A5,9,A.St16_Y8_2_carrier_opener_backward);		
	SetAusg(A5,10,A.St16_Y9_4_carrier_opener_forward);			
	SetAusg(A5,11,A.St16_Y9_2_carrier_opener_backward);			
	SetAusg(A5,12,A.St16_Y10_4_carrier_opener_forward);		
	SetAusg(A5,13,A.St16_Y10_2_carrier_opener_backward);			
	SetAusg(A5,14,A.St14_Y1_4_screw_tester_driver_forward);		
	SetAusg(A5,15,A.St14_Y1_2_screw_tester_driver_backward);		
}
else
{
	SetAusg (A5,0,false);
	SetAusg (A5,1,false);
	SetAusg (A5,2,false);
	SetAusg (A5,3,false);
	SetAusg (A5,4,false);
	SetAusg (A5,5,false);
	SetAusg (A5,6,A_MovingTest_forward[5]);
	SetAusg (A5,7,A_MovingTest_backward[5]);
	SetAusg (A5,8,false);
	SetAusg (A5,9,false);
	SetAusg (A5,10,false);
	SetAusg (A5,11,false);
	SetAusg (A5,12,false);
	SetAusg (A5,13,false);
	SetAusg (A5,14,false);
	SetAusg (A5,15,false);

}

if (!M_Error_Air_Off[6])
{
	SetAusg(A6,0,A.St16_Y5_4_gripper_lifter_downward);				
	SetAusg(A6,1,A.St16_Y5_2_gripper_lifter_upward);				
	SetAusg(A6,2,A.St16_Y6_4_reject_parts_gripper_close);				
	SetAusg(A6,3,A.St16_Y6_2_reject_parts_gripper_open);				
	SetAusg(A6,4,A.St16_Y7_4_reject_parts_gripper_close);			
	SetAusg(A6,5,A.St16_Y7_2_reject_parts_gripper_open);			
//	SetAusg(A6,6,A.);		
//	SetAusg(A6,7,A.);
	SetAusg(A6,8,A.St16_Y1_4_reject_parts_driver_forward);		
	SetAusg(A6,9,A.St16_Y1_2_reject_parts_driver_backward);		
	SetAusg(A6,10,A.St16_Y2_4_reject_parts_driver_stopper_upward);			
	SetAusg(A6,11,A.St16_Y2_2_reject_parts_driver_stopper_downward);			
	SetAusg(A6,12,A.St16_Y3_4_reject_parts_driver_stopper_upward);			
	SetAusg(A6,13,A.St16_Y3_2_reject_parts_driver_stopper_downward);			
	SetAusg(A6,14,A.St16_Y4_4_reject_parts_driver_stopper_upward);			
	SetAusg(A6,15,A.St16_Y4_2_reject_parts_driver_stopper_downward);		
}
else
{
	SetAusg (A6,0,false);
	SetAusg (A6,1,false);
	SetAusg (A6,2,false);
	SetAusg (A6,3,false);
	SetAusg (A6,4,false);
	SetAusg (A6,5,false);
	SetAusg (A6,6,A_MovingTest_forward[6]);
	SetAusg (A6,7,A_MovingTest_backward[6]);
	SetAusg (A6,8,false);
	SetAusg (A6,9,false);
	SetAusg (A6,10,false);
	SetAusg (A6,11,false);
	SetAusg (A6,12,false);
	SetAusg (A6,13,false);
	SetAusg (A6,14,false);
	SetAusg (A6,15,false);

}



// **************************************
// -A118- /FLS IB M12 DIO 4/4 (US2/US3)
// -A119- /FLS IB M12 DIO 4/4 (US2/US3)
// **************************************

#ifdef Axis_exist

	if (!M_Error_Air_Off[201])
	{
		SetAusg(A115,2,A.St201_Y1_4_SwivelUnit_forward);
		SetAusg(A115,3,A.St201_Y1_2_SwivelUnit_backward);

		//SetAusg(A119,0,A.St201_Y1_4_SwivelUnit_forward);
		//SetAusg(A119,1,A.St201_Y1_2_SwivelUnit_backward);
	}
	else
	{
		SetAusg (A118,0,false);	
		SetAusg (A118,1,false);
	
		//SetAusg (A119,0,false);
		//SetAusg (A119,1,false);
	}

	SetAusg(A115,0,A_MainAir[201]);
	//SetAusg(A119,2,A_MainAir[201]);

#endif

// **************************************
// -A110- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************
    SetAusg(A110,0,A_St3_A1_release_bowl_feeder);         
    SetAusg(A110,1,A_St3_A2_release_linear_feeder);         
    SetAusg(A110,2,A_St3_A3_release_linear_feeder);         
    SetAusg(A110,3,A_St3_Y1_blowing_air_for_feeder);      


// **************************************
// -A111- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************
    SetAusg(A111,0,A_St8_A1B_release_bowl_feeder);         
    SetAusg(A111,1,A_St8_A2B_release_linear_feeder);         
    SetAusg(A111,2,A_St8_A3B_release_bunker);         
    SetAusg(A111,3,A_St8_Y1B_blowing_air_for_screw);      
// **************************************
// -A112- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************
    SetAusg(A112,0,A_St8_A1A_release_bowl_feeder);         
    SetAusg(A112,1,A_St8_A2A_release_linear_feeder);         
    SetAusg(A112,2,A_St8_A3A_release_bunker);         
    SetAusg(A112,3,A_St8_Y1A_blowing_air_for_screw);
// **************************************
// -A113- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************
    SetAusg(A113,0,A_St8_Y2B_blowing_air_for_screw_pos);         
    SetAusg(A113,1,A_St8_Y2A_blowing_air_for_screw_pos);         
    //SetAusg(A113,2,free);         
    SetAusg(A113,3,A_St7_Y1_blowing_air_for_heat);

// **************************************
// -A117- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************
    SetAusg(A117,0,A_St5_A1_release_bowl_feeder);         
    //SetAusg(A117,1,A_St5_A3_release_bunker);         
    SetAusg(A117,2,A_St5_A3_release_bunker);         
    SetAusg(A117,3,A_St5_Y1_blowing_air_for_feeder);

// **************************************
// -A118- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************
    //SetAusg(A118,0,A_St5_A1_release_bowl_feeder);         
    SetAusg(A118,1,A_St1_Y1_blowing_air_for_linear);         
    SetAusg(A118,2,A_St1_Y2_BlastAir_long_housing_BF);         
    SetAusg(A118,3,A_St1_Y1_BlastAir_short_housing_BF);

// **************************************
// -A119- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************
    SetAusg(A119,0,A_St1_A7_short_housing_BF);         
    SetAusg(A119,1,A_St1_A9_release_short_housing_bunker);         
    SetAusg(A119,2,A_St1_A2_release_linear_feeder);         
    SetAusg(A119,3,A_St1_A3_release_linear_feeder);

// **************************************
// -A120- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************
    SetAusg(A120,0,A_St1_A8_long_housing_BF);         
    SetAusg(A120,1,A_St1_A10_release_long_housing_bunker);         
    SetAusg(A120,2,A_St1_A4_release_linear_feeder);         
    SetAusg(A120,3,A_St1_A5_release_linear_feeder);
// **************************************
// -A121- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************
    SetAusg(A121,0,A_St1_Y3_BlastAir_flange);         
    SetAusg(A121,1,A_St1_Y4_BlastAir_long_housing_A_select_BF);         
    SetAusg(A121,2,A_St1_Y5_BlastAir_long_housing_B_select_BF);         
    //SetAusg(A121,3,A_St1_Y3_BlastAir_flange);
// **************************************
// -A121- /FLS IB M12 DIO 4/4 (US3/US3)
// **************************************

//if (!M_Error_Air_Off[301])
//{
//	SetAusg(A120,0,A.St301_Y1_4_AxisProtector_forward);
//	SetAusg(A120,1,A.St301_Y1_2_AxisProtector_forward);
////	SetAusg(A120,2,frei);
////	SetAusg(A120,3,frei);
//}
//else
//{
//	SetAusg (A120,0,false);
//	SetAusg (A120,1,false);
//}



// *************************
// -A125- /FLS IB M12 DO 8 Hauplüfte
// *************************
   SetAusg(A125,0,A_MainAir[1]);
   SetAusg(A125,1,A_MainAir[2]);
   SetAusg(A125,2,A_MainAir[3]);				        
   SetAusg(A125,3,A_MainAir[4]);				        			       
   SetAusg(A125,4,A_MainAir[5]);				        
   SetAusg(A125,5,A_MainAir[6]);				        
   SetAusg(A125,6,A_MainAir[7]);			        
   //SetAusg(A125,7,A_St302_Y1_WT_abblasen);

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
	SetAusg(A151,6,A_All_ErrorLamp);	    // -K01/A1
	SetAusg(A151,7,A_Machine_Lamp);			// K017/K017
	SetAusg(A151,8,A_LED_Unload_Machine);          // LED für Taster im Kabelkanal
	SetAusg(A151,9,A_LED_Bridge_StandByPosition);  // LED für Taster im Kabelkanal
	SetAusg(A151,10,A_LED_Quit);               // LED für Taster im Kabelkanal
//	SetAusg(A151,11,frei);
//  SetAusg(A151,12,frei);
//	SetAusg(A151,13,frei);
//	SetAusg(A151,14,frei);
//	SetAusg(A151,15,frei);

	// GATEWAY to following SPS		    // GATEWAY AN FOLGENDE SPS
	SetAusg(GATEWAY_CT_1_W9,0,M_.ConveyorEn);										// -> Conveyor enable to the following SPS send		// -> Freigabe Vibratoren an folgende SPS senden
	SetAusg(GATEWAY_CT_1_W9,1,E_Button_Quit);										// -> E_Quit to the following SPS send				// -> E_TP_Quittieren an folgende SPS senden
    SetAusg(GATEWAY_CT_1_W9,2,DriveUnit[DriveUnit1].Unloaded && M.Unload_Machine);	// -> Machine unladed to the following SPS send		// -> Maschinenteil leergefahren an folgende SPS senden
	SetAusg(GATEWAY_CT_1_W9,3,M_Gateway_St301_FlexLink_Run);						// -> Enable Flex Link conveyor belt to the following SPS send	// -> Freigabe Flex Link Umlaufförderband an folgende SPS senden
	SetAusg(GATEWAY_CT_1_W9,4,E_St302_B1_FB_voll);									// -> WPC on connecting conveyor belt to the following SPS send	// -> Nest auf Zwischenförderband an folgende SPSS senden
//	SetAusg(GATEWAY_CT_1_W9,5,Gateway_folgende_SPS_Ausgang_6);		// -> 
//	SetAusg(GATEWAY_CT_1_W9,6,Gateway_folgende_SPS_Ausgang_7);		// -> 
//	SetAusg(GATEWAY_CT_1_W9,7,Gateway_folgende_SPS_Ausgang_8);		// -> 
	SetAusg(A152,8, A_St201_M2_Paramtersatz_1);
	SetAusg(A152,9, A_St201_M2_Paramtersatz_2);
	SetAusg(A152,10,A_St201_M2_Paramtersatz_3);
	SetAusg(A152,11,A_St201_M2_Paramtersatz_4);
//	SetAusg(A152,12,frei);
//	SetAusg(A152,13,frei);
//	SetAusg(A152,14,frei);
//	SetAusg(A152,15,frei);

// **********************************
// -A153/A154- /IB IL 24 DO/32 (US1)
// **********************************
//	SetAusg(A153,0,frei);
//	SetAusg(A153,1,frei);
//	SetAusg(A153,2,frei);
//	SetAusg(A153,3,frei);
//	SetAusg(A153,4,frei);
//	SetAusg(A153,5,frei);
//	SetAusg(A153,6,frei);
//	SetAusg(A153,7,frei);
//	SetAusg(A153,8,frei);
//	SetAusg(A153,9,frei);
//	SetAusg(A153,10,frei);
//	SetAusg(A153,11,frei);
//	SetAusg(A153,12,frei);
//	SetAusg(A153,13,frei);
//	SetAusg(A153,14,frei);
//	SetAusg(A153,15,frei); 

    // GATEWAY AN VORHERIGE SPS
	//SetAusg(A154,0,M_.ConveyorEn);					      // ->	Conveyor enable to previous SPS send			// -> Freigabe Vibratoren an vorherige SPS senden
	//SetAusg(A154,1,E_Button_Quit);						  // ->	Quit to previous SPS send						// -> E_TP_Quittieren an vorherige SPS senden
	//SetAusg(A154,2,M.Machine_Unloaded);				      // ->	Machine unloaded to previous SPS send			// -> Maschinenteil leergefahren an vorherige SPS senden
	//SetAusg(A154,3,A_St302_A1_FlexLink_Enable);			  // ->	connecting conveyor belt to previous SPS send	// -> Zwischenförderband läuft an vorherige SPS senden
	SetAusg(A154,0,A_St201_M3_Paramtersatz_1);  //+201 - M3
	SetAusg(A154,1,A_St201_M3_Paramtersatz_2);			//+201 - M3
	SetAusg(A154,2,A_St201_M3_Paramtersatz_3);			//+201 - M3
	SetAusg(A154,3,A_St201_M3_Paramtersatz_4);			//+201 - M3
	//SetAusg(A154,4,A_St201_M3_Paramtersatz_4);			//+201 - M3
	
	SetAusg(A157,0,A_St11_screw_driver_reset);			
	SetAusg(A157,1,A_St12_screw_driver_reset);
	SetAusg(A157,2,A_St14_screw_driver_reset);
	
	//	SetAusg(A154,4,A_Gateway_vorherige_SPS_Ausgang_5);			// -> 
//	SetAusg(A154,5,A_Gateway_vorherige_SPS_Ausgang_6);			// -> 
//	SetAusg(A154,6,A_Gateway_vorherige_SPS_Ausgang_7);			// -> 
//	SetAusg(A154,7,A_Gateway_vorherige_SPS_Ausgang_8);			// -> 
//	SetAusg(A154,8,frei);
//	SetAusg(A154,9,frei);
//	SetAusg(A154,10,frei);
//	SetAusg(A154,11,frei);
//	SetAusg(A154,12,frei);
//	SetAusg(A154,13,frei);
//	SetAusg(A154,14,frei);
//	SetAusg(A154,15,frei);  
// ******************************
// -A191- /IB IL 24 DO/4 (US3)
// ******************************
	SetAusg(A191,0,A_St201_M2_Enable_WPC_accelerator);	// +301-A1/E1   speed Flex Link conveyor belt		(Geschw. Umlaufförderband)
	SetAusg(A191,1,A_St201_M3_Enable_WPC_accelerator);	// +301-A1/E2   speed Flex Link conveyor belt		(Geschw. Umlaufförderband)
	SetAusg(A191,2,true);     // +302-K5  enable connecting conveyor belt		(Freig. Verbindungsfoerderband)
	SetAusg(A191,3,A_St5_A2_belt_enable); 

//-----------------------------------------------------------------
//---------------------------- +SK02A -----------------------------
//-----------------------------------------------------------------
// ******************************
// -A155- /IB IL 24 DO/4 (US1)
// ******************************
	//SetAusg(A155,0,A_St301_A1_FlexLink_slow);	// +301-A1/E1   speed Flex Link conveyor belt		(Geschw. Umlaufförderband)
	//SetAusg(A155,1,A_St301_A1_FlexLink_fast);	// +301-A1/E2   speed Flex Link conveyor belt		(Geschw. Umlaufförderband)
	//SetAusg(A155,2,A_St302_A1_FlexLink_Enable);     // +302-K5  enable connecting conveyor belt		(Freig. Verbindungsfoerderband)
//	SetAusg(A155,3,frei); 

// ******************************
// -A175- /IB IL 24 DO/4 (US2)
// ******************************
#ifdef Axis_exist
	SetAusg(A155,0,Achse[Axis1].A_Freigabe_Servo);		//-A201.1/16
	SetAusg(A155,1,Achse[Axis1].A_Reset_Servo);			//-A201.1/17


	//SetAusg(A155,2,Achse[Axis2].A_Freigabe_Servo);		//-A1.1/16
	//SetAusg(A155,3,Achse[Axis2].A_Reset_Servo);			//-A1.1/17
	SetAusg(A156,0,A_St1_HSP_Freigabe_Servo_A2_16);		//-A1.1/16
	SetAusg(A156,1,A_St1_HSP_Reset_Servo_A2_17);			//-A1.1/17
#endif
    
 // ******************************
 // -A195- /IB IL 24 DO/4  (US3)
 // ******************************
    SetAusg(A195,0,A_St301_A1_FlexLink_Enable);         // +301-A1/K15	enable Flex Link conveyor belt	(Freig. Umlauffoerderband)   
	//SetAusg(A195,1,A_St201_M2_Enable_WPC_accelerator);  // +201-M2/K1
	SetAusg(A195,2,A_St201_M3_Enable_WPC_accelerator);  // +201-M3/K1
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
//Steuerwort KEB-Servo St.1
	SetAusg(KEB_SERVO_1,0,St_1_KEB_Einsetzen.A_Reglerfreigabe);
	SetAusg(KEB_SERVO_1,1,St_1_KEB_Einsetzen.A_Reset);
	SetAusg(KEB_SERVO_1,2,St_1_KEB_Einsetzen.A_Start);
	SetAusg(KEB_SERVO_1,3,St_1_KEB_Einsetzen.A_Drehrichtung);
	SetAusg(KEB_SERVO_1,4,St_1_KEB_Einsetzen.A_Parametersatz_Bit1);
	SetAusg(KEB_SERVO_1,5,St_1_KEB_Einsetzen.A_Parametersatz_Bit2);
	SetAusg(KEB_SERVO_1,6,St_1_KEB_Einsetzen.A_Parametersatz_Bit3);
	SetAusg(KEB_SERVO_1,8,St_1_KEB_Einsetzen.A_Schnellhalt);
	SetAusg(KEB_SERVO_1,9,St_1_KEB_Einsetzen.A_Start_Referenzpunktfahrt);
	SetAusg(KEB_SERVO_1,10,St_1_KEB_Einsetzen.A_Start_Positionierung);
	SetAusg(KEB_SERVO_1,12,St_1_KEB_Einsetzen.A_Betriebsart_Bit1);
	SetAusg(KEB_SERVO_1,13,St_1_KEB_Einsetzen.A_Betriebsart_Bit2);
	
			//St_1_KEB_Einsetzen.Sollposition_low =LOWORD(M.Sollpos);
			//St_1_KEB_Einsetzen.Sollposition_high=HIWORD(M.Sollpos);

	SetAusgWortEx(KEB_SERVO_1,1,St_1_KEB_Einsetzen.Sollposition_high);
	SetAusgWortEx(KEB_SERVO_1,2,St_1_KEB_Einsetzen.Sollposition_low);



//##END_AUSGAENGE     Zeile nicht loeschen		don't delete this line

#ifdef Camera_Pipe_exist	
// TODO: Ausgaenge zur Kamera prüfen
// Pipe-Übergaben zum Kamerarechner 1
	Kameradaten_A[KameraPC_1].Start1_Kamera1			= A_Start_Sig1_Kamera[1];
	Kameradaten_A[KameraPC_1].Start2_Kamera1			= A_Start_Sig2_Kamera[1];
	Kameradaten_A[KameraPC_1].Blockbeginn_Kamera1		= A_Blockbeginn_Kamera[1];
	Kameradaten_A[KameraPC_1].Beleuchtung_ein_Kamera1	= A_Beleuchtung_einschalten_Kamera[1];
	Kameradaten_A[KameraPC_1].Stat_Kamera1_eingeschaltet= A_Kamera_ein[1];

	Kameradaten_A[KameraPC_1].Start1_Kamera2			= A_Start_Sig1_Kamera[2];
	Kameradaten_A[KameraPC_1].Start2_Kamera2			= A_Start_Sig2_Kamera[2];
	Kameradaten_A[KameraPC_1].Blockbeginn_Kamera2		= A_Blockbeginn_Kamera[2];
	Kameradaten_A[KameraPC_1].Beleuchtung_ein_Kamera2	= A_Beleuchtung_einschalten_Kamera[2];
	Kameradaten_A[KameraPC_1].Stat_Kamera1_eingeschaltet= A_Kamera_ein[2];

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
	if (!StartSignale_der_Kameras_vorhanden	( DriveUnit[DriveUnit1].Start[K_St10_Camera_Pressure_Plate] 
											, DriveUnit[DriveUnit1].Start[K_St13_Camera_Screw]
											, 0
											, 0
											, KameraPC_1))
	{
		Kameradaten_A[KameraPC_1].Start1_Kamera1 = false;
		Kameradaten_A[KameraPC_1].Start2_Kamera1 = false;
		Kameradaten_A[KameraPC_1].Blockbeginn_Kamera1 = false;

		Kameradaten_A[KameraPC_1].Start1_Kamera2 = false;
		Kameradaten_A[KameraPC_1].Start2_Kamera2 = false;
		Kameradaten_A[KameraPC_1].Blockbeginn_Kamera2 = false;

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
        Barcodescanner(Axis1, 390, COM4, 0, true, true, E_St201_B4_WPC_InPosition );
    }

    if (    MACHINETYPE == MIDDLE_MG
        ||  MACHINETYPE == LAST_MG )
    {
        Barcodescanner(Axis1, 390, COM4, 0, false, true, E_St201_B4_WPC_InPosition );
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
		M_.Extra_St1_without_material = true;
		M_.St2_without_material = true;
		M_.St3_without_material = true;
		M_.St4_without_material = true;
		M_.St5_without_material = true;
		M_.St6_without_material = true;
		M_.St7_without_material = true;
		M_.St8_without_material = true;
		M_.St9_without_material = true;
		M_.St10_without_material = true;
		M_.St11_without_material = true;
		M_.St12_without_material = true;
		M_.St13_without_material = true;
		M_.St14_without_material = true;
		M_.St16_without_material = true;
		M_.St201_without_material = true;
	}
	if (NegFlanke(Fl_NegWithoutMaterial , M_.All_Stations_without_material ))
	{
		M_.St1_without_material = false;
		M_.Extra_St1_without_material = false;
		M_.St2_without_material = false;
		M_.St3_without_material = false;
		M_.St4_without_material = false;
		M_.St5_without_material = false;
		M_.St6_without_material = false;
		M_.St7_without_material = false;
		M_.St8_without_material = false;
		M_.St9_without_material = false;
		M_.St10_without_material = false;
		M_.St11_without_material = false;
		M_.St12_without_material = false;
		M_.St13_without_material = false;
		M_.St14_without_material = false;
		M_.St16_without_material = false;
		M_.St201_without_material = false;
		ArticleData();
	}

    PC_Message[8] = M_.All_Stations_without_material ;



// ************************************
// TODO: Stationsaufrufe eintragen!
// ************************************
St1_Extra_housing_seperate		( K_St1_Extra_Housing_seperate		// Sequence
								, 10								// Start of error range of this function
								, 1									// Valve terminal is to be switched off in case of failure
								, 2									// Valve terminal is to be switched off in case of failure
								, DriveUnit2						// DriveUnitNum
								, 21								// Station number of BDE
								, 21								// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);

St1_Extra_housing_foot_pusher	( K_St1_Extra_Housing_foot_pusher	// Sequence
								, 10								// Start of error range of this function
								, 1									// Valve terminal is to be switched off in case of failure
								, 2									// Valve terminal is to be switched off in case of failure
								, DriveUnit2						// DriveUnitNum
								, 22								// Station number of BDE
								, 22								// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);

St1_Extra_housing_foot_test		( K_St1_Extra_Housing_foot_test			// Sequence
								, 10									// Start of error range of this function
								, 1										// Valve terminal is to be switched off in case of failure
								, 2										// Valve terminal is to be switched off in case of failure
								, DriveUnit2							// DriveUnitNum
								, 25									// Station number of BDE
								, 25									// Register of the station
								, false									// Setup phase conveyors and StandBy are deactivated
								);


St1_Extra_reject_housing_remove	( K_St1_Extra_Reject_Housing_remove		// Sequence
								, 10									// Start of error range of this function
								, 1										// Valve terminal is to be switched off in case of failure
								, 2										// Valve terminal is to be switched off in case of failure
								, DriveUnit2							// DriveUnitNum
								, 26									// Station number of BDE
								, 26									// Register of the station
								, false									// Setup phase conveyors and StandBy are deactivated
								);

 St01_Insert_Housing_01			( K_St1_Insert_Housing				// Sequence
								, 10			// Start of error range of this function
								, 2		// Valve terminal is to be switched off in case of failure
								, DriveUnit1		// DriveUnitNum
								, 1		// Station number of BDE
								, 1		// Register of the station
								, false			// Setup phase conveyors and StandBy are deactivated
					
								);
 St01_Press_Cover	  ( K_St1_Press_Cover				// Sequence
						, 10								// Start of error range of this function
						, 2 								// Valve terminal is to be switched off in case of failure
						, DriveUnit1						// DriveUnitNum
						, 1									// Station number of BDE
						, 1									// Register of the station
						, false								// Setup phase conveyors and StandBy are deactivated
						);
//St1_Gehaeuse_einsetzen();
//

St2_Check_Housing				( K_St2_Check_Housing					// Sequence
								, 70								// Start of error range of this function
								, DriveUnit1						// DriveUnitNum
								, 2							// Station number of BDE
								, 2								// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);

St3_Insert_Pressure_Plate		( K_St3_Insert_Pressure_Plate					// Sequence
								, 80								// Start of error range of this function
								, 2									// Valve terminal is to be switched off in case of failure
								, DriveUnit1						// DriveUnitNum
								, 3								// Station number of BDE
								, 3								// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);

St4_Check_Pressure_Plate		( K_St4_Check_Pressure_Plate					// Sequence
								, 90								// Start of error range of this function
								, DriveUnit1						// DriveUnitNum
								, 4								// Station number of BDE
								, 4								// Register of the station
								, false
								);


St5_Insert_Clamping_Sleeve		( K_St5_Insert_Clamping_Sleeve					// Sequence
								, 100								// Start of error range of this function
								, 3									// Valve terminal is to be switched off in case of failure
								, DriveUnit1						// DriveUnitNum
								, 5								// Station number of BDE
								, 5								// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);
St6_Check_Flange_Screw		( K_St6_Check_Flange_Screw					// Sequence
								, 120								// Start of error range of this function
								, DriveUnit1						// DriveUnitNum
								, 6								// Station number of BDE
								, 6								// Register of the station
								,false
								);
//

St8_screw_insert				( K_St8_Insert_Screw				// Sequence
								, 260								// Start of error range of this function
								, 4 								// Valve terminal is to be switched off in case of failure
								, DriveUnit1						// DriveUnitNum
								, 8									// Station number of BDE
								, 8									// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);
St09_Check_Screw_Available		( K_St9_Check_screw				// Sequence
								, 280								// Start of error range of this function
								, 4 								// Valve terminal is to be switched off in case of failure
								, DriveUnit1						// DriveUnitNum
								, 9									// Station number of BDE
								, 9									// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);
St10_camera_check				( K_St10_Camera_Pressure_Plate		// Sequence
								, 120								// Start of error range of this function
								, 4									// Valve terminal is to be switched off in case of failure
								, DriveUnit1						// DriveUnitNum
								, 10								// Station number of BDE
								, 10								// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);

St11_Screwdriver_close			( K_St11_Screwdriver_close				// Sequence
								, 170									// Start of error range of this function
								, 4										// Valve terminal is to be switched off in case of failure
								, DriveUnit1							// DriveUnitNum
								, 11									// Station number of BDE
								, 11									// Register of the station
								, false									// Setup phase conveyors and StandBy are deactivated
								);

St12_Screwdriver_open			( K_St12_Screwdriver_open				// Sequence
								, 190									// Start of error range of this function
								, 4										// Valve terminal is to be switched off in case of failure
								, DriveUnit1							// DriveUnitNum
								, 12									// Station number of BDE
								, 12									// Register of the station
								, false									// Setup phase conveyors and StandBy are deactivated
								);
St13_camera_check				( K_St13_Camera_Screw				// Sequence
								, 140								// Start of error range of this function
								, DriveUnit1						// DriveUnitNum
								, 13								// Station number of BDE
								, 13								// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);

St14_Screw_take_out				( K_St14_Screw_take_out				// Sequence
								, 220								// Start of error range of this function
								, 5									// Valve terminal is to be switched off in case of failure
								, DriveUnit1						// DriveUnitNum
								, 14								// Station number of BDE
								, 14								// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								//, true							// true = Nebenantrieb, false = Hauptantrieb
								);

St16_reject_out					( K_St16_Reject_take_out					// Sequence
								, 280								// Start of error range of this function
								, 5									// Valve terminal is to be switched off in case of failure
								, 6									// Valve terminal is to be switched off in case of failure
								, DriveUnit1						// DriveUnitNum
								, 16								// Station number of BDE
								, 16								// Register of the station
								, false								// Setup phase conveyors and StandBy are deactivated
								);


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
	if	(	M.Save_RunTime_in_file
		||	IFCBIT
		)
		LaufzeitenSpeichern();

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
	WORD RegisterNr = 16;		// Shift Register for BDE - Dates are identify 		//Registerstelle an der die BDE - Daten ermittelt werden

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
				if(RegisterWert_3D(RegisterNr,i,j) > 0)
					MaDatum[MaPartNum].Index_21.Arbeitstakte++;

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

	//DriveUnit[DriveUnit1].NumberOfHousings = 1;

	//if (MW_ArtikelTyp.Parameter[0] == 2) 
	//	DriveUnit[DriveUnit1].NumberOfHousings = 2;
	DriveUnit[DriveUnit1].NumberOfHousings = MW_ArtikelTyp.Parameter[0];
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

	PC_release_Article = true; //for test
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
	M.scanner_init = Scanner_init(COM4);
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
	Scanner_close(COM4); // Scanner Maschine
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
	ErrorProgram(PRG1,							// number of the error program			// Nummer des Fehlerprogramms
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
}
