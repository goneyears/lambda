/*******************************************************************************************************
**
** Dateiname          : SPSVAR.h
** Datum              : 01.01.2002
** Rev. Nr.		      : 0.1
** Rev. 膎derungen	  : siehe Verzeichnis "Standard_Prg" RevNr.xls
**
** Funktion			  : Deklaration von Flanken,Zeiten,Schrittketten,
**						Eing鋘ge,Ausg鋘ge und Merkern
**
********************************************************************************************************
**
** Projekt            : BM
**
** Maschinenteil      : SPS
** Programmierer      :
**
** Programm鋘derungen : Datum			Name				Bemerkung
**						19.11.2005		Torsten Weber		Programmerstellung, mit Grundprogramm V1.26
**						06.01.2009		M.van de Wouw		躡erarbeitet f黵 Grundprogramm V2.2
**						25.02.2010		A.Pelka				Umbau auf 3/2 Wege Ventile V2.2.02
**
**
********************************************************************************************************/

#define LANGUAGE_ENGLISH				0
#define LANGUAGE_GERMAN					1

//##########################################################
//# Achtung : Vorgabewerte entsprechen den Arraygrenzen!!! #
//# d.h. #define MAX_AXIS_OFFSET	19                     #
//# letzter zu benutzender Achsenoffset ist 19  (0 bis 19) #
//##########################################################

//**********************************************************
//********  DEFINE Zuweisungen f黵s Grundprogramm  *********
//**********************************************************

#define MAX_FLANK					254		//	flank						Flanken
#define MAX_COUNTER					254		//	counter						Zaehler
#define MAX_TIMER					400		//	timer						Timer
#define MAX_FRQTIMER				  9		//	frequence timer				Frequenztimer

#define TEXTLEN						 51		// Max.Zeichen
											// f黵 Zeiten,Z鋒ler,Schrittketten, nicht remanente Variablen,
											// Eing鋘ge, Ausg鋘ge,
#define MAXONLVAR					400		// Anzahl der nicht remaneten Variablen

#define MAX_AXIS_OFFSET				 19		//	number of offsets pro axis					Anzahl Offsets pro Achse
#define MAX_MESSAGE					 24		//	number of messages to BDE					Anzahl der Meldungen an BDE
#define MAX_WARNING					 24		//	number of warnings to BDE					Anzahl der Warnungen an BDE
#define MAX_CHECK_ERROR				 49		//	number of check errors for index 22			Anzahl der Pr黤fehler f黵 Index 22
#define MAX_SPSPARAMETER			 29		//	for Index64 Stand 08/2005					f黵 Index64 Stand 08/2005

//**********************************************************
//***********  DEFINE Zuweisungen f黵s Register  ***********
//**********************************************************

// 2 Dimensionales Schieberegister
#define MAXREGISTER					  20    //	e.g. number of nests					z.B. Anzahl der Nester
#define MAXREGISTER_LENGTH			  1		//	e.g. number of poles in one housing		z.B. Anzahl der Pole in einem Geh鋟se

// 3 Dimensionales Schieberegister
#define MAX3DREGISTER				 10		//	e.g. number of nests					z.B. Anzahl der Nester
#define MAX3DREGISTER_BLOCK			  1		//	e.g. number of housings in one nest		z.B. Anzahl der Geh鋟se in einem Nest
#define MAX3DREGISTER_LENGTH		  1		//	e.g. number of poles in one housing		z.B. Anzahl der Pole in einem Geh鋟se

//***********************************************************
//********  DEFINE Zuweisungen f黵 Allgemeinedaten  *********
//***********************************************************

#define MAX_AXIS					  1		//	number of axes									Anzahl Achsen
#define MAX_MACHINE					  1		//	number of BDE machine parts in this program		Anzahl der BDE Maschinenteile in diesem Programm
#define MAX_ERRORPRG				  1		//  number of error programms						Anzahl der Fehlerprogramme

#define WPC_LENGTH					150		//	WPC length in mm								Nestl鋘ge in mm
#define MAX_NUMBERPOLE				 24		//	maximal number of poles in one housing 			Maximale Polzahl der Gehaeuse
#define MAX_NUMBERHOUSING			  2		//	maximal number of housing in one nest 			Maximale Anzahl der Gehaeuse pro Nest

#define MAXANZSTAT					 32		//	maximal number of stations (36 stations)		Anz. Stationen
#define MAX_SEQUENCES				 60		//	sequencer										Schrittketten
#define MAX_MAINAIR					310		//	number of main air valves						Anzahl der Hauptluftventile
#define NUMBERSAFETYDOORS			  8		//	number of safety doors							Anzahl der Schutzt黵en eintragen
#define MAX_STOPWATCH				  3		//	number of stopwatches for every station			Anzahl der Stopuhren pro Station


//***********************************************************
//******  DEFINE Zuweisungen f黵 Teil Informationen  ********
//***********************************************************

#define GUTTEIL						1010	// Erkl鋜ungen der Werte wie man sie bildet stehen
#define GUTPOL						1010	// in BDE_Data_Transfer()
#define GUTPOL_SOPO					1011	// Gutpol mit Sonderbestueckung

//*********************************************************
//********  DEFINE Zuweisungen f黵 SONDERSACHEN   *********
//*********************************************************

#define VIEW_RUNTIMES			// Include view StationsRunTimes		Stationslaufzeiten (Gesamt) einbinden (Anzeigen)
#define VIEW_MinuteCycle		// Include view MinuteCycle				Stationstaktzahlen einbinden (Anzeigen)
#define VIEW_POSITION_VALUE		// Include view Set Position			Polpositionswerte einbinden (Anzeigen)
//#define VIEW_CAMERA_IO		// Inlcude view Camera Input/Output		Kamera E/As einbinden (Anzeigen)
#define VIEW_SBTDIAGNOSIS		// Include view Safety					Diagnose Variablen der einzelnen SBT Module einbinden (Anzeigen)

//*********************************************************
//*************  Datenverwaltung / Scanner   **************
//*********************************************************

#if defined(Scanner_V24) || defined(Scanner_IBS_RS232)
 #define MAXNESTER		100		// Anzahl der Nester in der Anlage
								// Wert muss identisch mit der Datenverwaltung sein
#endif

//*********************************************************
//************  Weitere Variablen einbinden   *************
//*********************************************************

#ifdef Camera_Pipe_exist
 #include "Kamera_var.h"	// Variablen der Kamera
 #include "Kamera_Daten.h"	// Daten黚ergabe zum Kamerapipe
#endif

#ifdef Axis_exist
 #include "A_var.h"			// Variablen f黵 Achsen im Allgemeinen
#endif

#ifdef Plate_exist
 #include "TellerVar.h"		// Variablen f黵 Teller im Allgemeinen
#endif

#ifdef Plate_FU_exist
 #include "TellerVar.h"		// Variablen f黵 Teller im Allgemeinen
#endif

#ifdef Plate_Siemens_FU_exist
 #include "TellerVar.h"		// Variablen f黵 Teller im Allgemeinen
#endif


#include "AntriebeVar.h"	// Variablen f黵 Antriebe im Allgemeinen

#ifdef HVPruefung_vorhanden
 #include "HochspgVar.h"
#endif

#include "spipevar.h"				// Vaiablen f黵 die Pipeverbindung
#include "SPSMess_Einstellung.h"	// Einstellungen f黵 die Elektrische Messung
#include "SPSMessVar.h"				// Variablen f黵 die Elektrische Messung

//*****************************************************************
//****************  Konstanten f黵 Flanken  ***********************
//*****************************************************************

//##  ANF_FLANKEN			Zeile nicht loeschen

//Allgemeiner Teil
#define Fl_On												 1			//Fl_Ein
#define Fl_MaReset											 2			//Fl_MaReset
#define Fl_EndPos											 3			//Fl_Endstell
#define Fl_PCSingelStepMode									 4			//Fl_PCEinzelschritt
#define Fl_MaOff											 8			//Fl_MaAus
#define Fl_Air												 9			//Fl_Luft
#define Fl_QuitConveyor										10			//Fl_Entsp
#define Fl_Conveyor											11			//Fl_Vibr
#define Fl_AirOff											12			//Fl_Luft_aus
#define Fl_PC_Unload										15			//Fl_PC_Leerfahren
#define Fl_ChangeArticle									16			//Fl_Artikelwechsel
#define Fl_Quit												21			//Fl_Entsperren
#define Fl_ConveyorResetBefore                              22			//FL_VibrResetVorherige
#define Fl_ConveyorResetFollowing                           23			//FL_VibrResetFolgende
#define Fl_QuitResetBefore								    24			//FL_EntspResetVorherige
#define Fl_QuitResetFollowing                               25			//FL_EntspResetFolgende
#define Fl_T_ResetConveyor                                  26			//Fl_T_Vibr_reset
#define Fl_ImpulseUnloadMaschine							27			//Fl_Impuls_Masch_soll_leerfahren
#define Fl_T_ResetQuit									    28			//Fl_T_Entsp_reset
#define Fl_St302_B1_LC_full                                 29			//Fl_St302_B1_FB_voll
#define Fl_PosWithoutMaterial								30
#define Fl_NegWithoutMaterial								31
#define Fl_Service_aktivieren								32

//Stationsbezogen
#define Fl_St201_WPC_passing							    50			//Fl_St201_Nest_durchgelaufen
#define Fl_St201_StationenReset								51			//Fl_St201_StationenReset
#define Fl_St202_StationenReset								52			//Fl_St202_StationenReset
#define Fl_St203_StationenReset								53			//Fl_St203_StationenReset
#define Fl_St203_PlateTurnsOff							    54			//Fl_St203_Teller_drehen_aus
#define Fl_St204_StationenReset								55			//Fl_St204_StationenReset
#define Fl_St204_PlateTurnsOff							    56			//Fl_St204_Teller_drehen_aus
#define Fl_E_Gateway_SPS_St302_FlexLink_BeforeFull			57

#define Fl_St3_Conveyor_load								60
#define Fl_St3_Conveyor_unload                              61


//##  END_FLANKEN			Zeile nicht loeschen

//*****************************************************************
//***************  Konstanten f黵 Zeitwerke  **********************
//*****************************************************************

//##ANF_ZEITEN			Zeile nicht loeschen

//-----------------------------------------------------------------------------
//                           Allgemeine Zeiten
//-----------------------------------------------------------------------------
#define T_IBS_RUN											 1			//T_IBS_RUN
#define T_Conveyor											 2			//T_Vibr
#define T_Air												 3			//T_Luft
#define T_MaschineControlTime								 4			//T_Kontroll_Maschine
#define T_Error												 5			//T_Fehler
#define T_Message											 6			//T_Meldung
#define T_Warning											 7			//T_Warnung
#define T_PulsMaOn											 8			//T_Impuls_MaEin

#define T_ControlTime_DU1									10			//T_Kontroll_Antrieb1
#define T_ControlTime_DU2									11			//T_Kontroll_Antrieb2
#define T_ControlTime_DU3									12			//T_Kontroll_Antrieb3
#define T_ControlTime_DU4									13			//T_Kontroll_DriveUnit4
#define T_ControlTime_DU5									14			//T_Kontroll_DriveUnit5
#define T_ControlTime_DU6									15			//T_Kontroll_DriveUnit6
#define T_ControlTime_DU7									16			//T_Kontroll_DriveUnit7
#define T_ControlTime_DU8									17			//T_Kontroll_DriveUnit8
#define T_Following_SPS_unloaded							18		    //T_folgende_SPS_leergefahren
#define T_Before_SPS_unloaded								19		    //T_vorherige_SPS_leergefahren
#define T_MachineLightningOff								20

//-----------------------------------------------------------------------------
//                           Zeiten f黵 Axis 1
//-----------------------------------------------------------------------------
#define T_St201_PositionTime								30			//Zeit wird gesetzt		T_St201_Positionierzeit
#define T_St201_Alarm_reset									31			//Zeit wird gesetzt		T_St201_Alarm_reset
#define T_St201_Break_solved								32			//Zeit wird gesetzt		T_St201_Bremse_loesen
#define T_St201_Break_reached								33			//Zeit wird gesetzt		T_St201_Bremse_greifen
#define T_St201_Break_relaxed								34			//Zeit wird gesetzt		T_St201_Bremse_geloest

#define T_St201_WPC_InPosition								35			//T_St201_Nest_eingelaufen
#define T_St201_pushed_WPC_passed_through					36			//T_St201_ausgeschobenes_Nest_durchgelaufen
#define T_St201_ConveyorBelt_Empty							37			//T_St201_Verbindungsfoerderband_leer
#define T_St201_ReferencePoint_Ok							38			//T_St201_Referenzpunkt_ok
#define T_St201_MotorStandStill								39			//T_St201_Motorstillstand
#define T_St201_Control_ReferenceDrive						40			//T_St201_Kontrolle_Referenzfahrt
#define T_St201_Control_ReferenceDriveMax					41			//T_St201_Kontrolle_Referenzfahrt_max
#define T_St201_WPCAccelerator_M2							42			//T_St201_Nestbeschleuniger_M2
#define T_St201_WPCAccelerator_M3							43			//T_St201_Nestbeschleuniger_M3

#define T_St201_WaitingTimeSend_DV_Date						44			//T_St201_Wartezeit_DV_Daten_schicken
#define T_St201_DelayCameraStart_Block1_Pole1				45			//T_St201_Kamera_start_verzoegern_Block1_Pol1
#define T_St201_DelayCameraStart_Pole1						46			//T_St201_Kamera_start_verzoegern_Pol1
#define T_St201_DelayCameraStart							47			//T_St201_Kamera_start_verzoegern
#define T_St301_AxisProtector_For							48			//T_St301_Achsenschoner_vor
#define T_St301_AxisProtector_Back							49			//T_St301_AxisProtectorBack
#define T_St301_AxisProtector_PulseFor						50			//T_St301_Achsenschoner_Impuls_vor

//-----------------------------------------------------------------------------
//                           Zeiten f黵 Teller
//-----------------------------------------------------------------------------
#define T_St202_PositionTime								51	//3000ms				T_St202_Positionierzeit
#define T_St202_Alarm_reset									52	//4500ms				T_St202_Alarm_reset
#define T_St202_MotorStandStill								53	//300ms					T_St202_Motorstillstand

#define T_St203_Plate_Delay_BreakOff						54	// Zeit wird gesetzt	T_St203_Verz_Bremse_Teller_aus
#define T_St203_Plate_Control_PCam							55						  //T_St203_Ueberwachung_PNocke_Teller_FU
#define T_St203_Plate_StillStand							56						  //T_St203_Teller_Stillstand

#define T_St204_Plate_Control_PCam							57						  //T_St204_Ueberwachung_PNocke_Teller_FU
#define T_St204_Plate_StillStand							58						  //T_St204_Teller_Stillstand

//-----------------------------------------------------------------------------
//                        Zeiten f黵 Barcodescanner
//-----------------------------------------------------------------------------
#define T_Scanner_Control									60		//T_Scanner_Kontrolle
#define T_Scanner_Reset										61		//T_Scanner_Reset
#define T_Scanner_Start_after_Reset							62		//T_Scanner_Start_nach_Reset
#define T_Scanner_WPC_InPosition                            63 		//T_Scanner_WT_eingelaufen
#define T_Scanner_Delay_Start								64 		//T_Scanner_Start_verzoegern


//-----------------------------------------------------------------------------
//                      Zeiten f黵 Stand-By am Flex Link
//-----------------------------------------------------------------------------
#define T_ConnectingCB_full_StandBy							70		//T_VerbindungsfoerderbandVollStandBy
#define T_ConnectingCB_full_StandByOff						71		//T_VerbindungsfoerderbandVollStandByAus
#define T_ConnectingCB_full_ShowMessage						72		//T_VerbindungsfoerderbandVoll_anzeigen

#define T_ConnectingCB_StandBy								73		//T_VerbindungsfoerderbandAusStandBy
#define T_ConnectingCB_StandByOff							74		//T_VerbindungsfoerderbandAusStandByAus

#define T_ConnectingCB_empty_StandBy						75		//T_VerbindungsfoerderbandLeerStandBy
#define T_ConnectingCB_empty_StandByOff						76		//T_VerbindungsfoerderbandLeerStandByAus
#define T_ConnectingCB_empty_StandByShowMessage				77		//T_VerbindungsfoerderbandLeerStandByAnzeigen

#define T_RotationCB_StandBy								78		//T_UmlauffoerderbandAusStandBy
#define T_RotationCB_StandByOff								79		//T_UmlauffoerderbandAusStandByAus

//-----------------------------------------------------------------------------
//                     Zeiten f黵 Stand-By an Baugruppen
//-----------------------------------------------------------------------------
#define T_St1_StandBy										80
#define T_St1_StandByOff									81
#define T_St1_StandBy_ShowMessage							82

#define T_St022_StandBy										83
#define T_St022_StandByOff									84
#define T_St022_StandBy_ShowMessage							85

#define T_St024_StandBy										86
#define T_St024_StandByOff									87
#define T_St024_StandBy_ShowMessage							87

#define T_St042_StandBy										83
#define T_St042_StandByOff									84
#define T_St042_StandBy_ShowMessage							85

#define T_St044_StandBy										86
#define T_St044_StandByOff									87
#define T_St044_StandBy_ShowMessage							87

//-----------------------------------------------------------------------------
//                        Zeiten f黵 Baugruppen
//-----------------------------------------------------------------------------

#define T_St1_Feeder_Error									    101

#define T_houisng_in_position									102
#define T_St201_Station_Start_Delay								103
#define T_Teller1_Unlock									    104
#define T_Teller1_Rotate									    105
#define T_Teller2_Unlock									    106
#define T_Teller2_Rotate									    107

#define T_St021_B1_WT_checking								    108
#define T_St021_check_max								        109

#define T_St022_gripper_open									110
#define T_St022_gripper_close									111
#define T_St022_B1_current_bar_in_position					    112
#define T_St022_gripper_turn_send					            113
#define T_St022_Feeder_Error								    114

#define T_St023_Press_Current_Bar							    115
#define T_St023_B1_current_bar_in_position					    116
#define T_St023_check_max								        117
#define T_St023_try								                118


#define T_St024_B1_clamping_sleeve_in_position                  119
#define T_St024_B2_clamping_sleeve_in_position                  120
#define T_St024_gripper_open                                    121
#define T_St024_gripper_close									122
#define T_St024_Feeder_Error								    123

#define T_St026_B1_check_clamping_sleeve_in_position			124
#define T_St026_B2_check_clamping_sleeve_in_position			125
#define T_St026_check_max										126



#define T_St027_gripper_open                                    127
#define T_St027_gripper_close									128


#define T_St028_gripper_open                                    129
#define T_St028_gripper_close									130

#define T_St003_Press_Delay										131
#define T_St005_Press_Delay										132






#define T_St041_B1_WT_checking								    133
#define T_St041_check_max								        134

#define T_St042_gripper_open									135
#define T_St042_gripper_close									136
#define T_St042_B1_current_bar_in_position					    137
#define T_St042_gripper_turn_send					            138
#define T_St042_gripper_turn_send_A					            139
#define T_St042_Feeder_Error								    140

#define T_St043_Press_Current_Bar							    141
#define T_St043_B1_current_bar_in_position					    142
#define T_St043_check_max								        143
#define T_St043_try								                144


#define T_St044_B1_clamping_sleeve_in_position                  145
#define T_St044_B2_clamping_sleeve_in_position                  146
#define T_St044_gripper_open                                    147
#define T_St044_gripper_close									148
#define T_St044_Feeder_Error								    149

#define T_St046_B1_check_clamping_sleeve_in_position			150
#define T_St046_B2_check_clamping_sleeve_in_position			151
#define T_St046_check_max										152



#define T_St047_gripper_open                                    153
#define T_St047_gripper_close									154

#define T_St048_gripper_open                                    155
#define T_St048_gripper_close									156
#define T_St028_gripper_down                                    157
#define T_St048_gripper_down                                    158

#define T_Teller1_lock									    160
#define T_Teller2_lock									    161
#define T_houisng_not_in_MAX									    162






//-----------------------------------------------------------------------------
//         F黵 die F鰎dert鰌fe sind die Zeitwerke ab 200 Reserviert !!
//-----------------------------------------------------------------------------

#define T_St1_BF_ON										    200
#define T_St1_BF_OFF										201
#define T_St1_BlastAir_ON									202
#define T_St1_BlastAir_OFF									203
#define T_St1_Warning_ON									204
#define T_St1_Warning_OFF									205
#define T_St1_CoverOpen_BF_OFF								206
#define T_St1_CoverOpen_BlastAir_OFF						207
#define T_St1_CoverOpen_Warning_ON							208
#define T_St1_Storage_ON_OFF								209

#define T_St022_BF_ON										210
#define T_St022_BF_OFF										211
#define T_St022_BlastAir_ON									212
#define T_St022_BlastAir_OFF							    213
#define T_St022_Warning_ON									214
#define T_St022_Warning_OFF									215
#define T_St022_CoverOpen_BF_OFF							216
#define T_St022_CoverOpen_BlastAir_OFF						217
#define T_St022_CoverOpen_Warning_ON						218
#define T_St022_Storage_ON_OFF								219

#define T_St024_BF_ON										220
#define T_St024_BF_OFF										221
#define T_St024_BlastAir_ON									222
#define T_St024_BlastAir_OFF							    223
#define T_St024_Warning_ON									224
#define T_St024_Warning_OFF									225
#define T_St024_CoverOpen_BF_OFF							226
#define T_St024_CoverOpen_BlastAir_OFF						227
#define T_St024_CoverOpen_Warning_ON						228
#define T_St024_Storage_ON_OFF								229

#define T_St042_BF_ON										230
#define T_St042_BF_OFF										231
#define T_St042_BlastAir_ON									232
#define T_St042_BlastAir_OFF							    233
#define T_St042_Warning_ON									234
#define T_St042_Warning_OFF									235
#define T_St042_CoverOpen_BF_OFF							236
#define T_St042_CoverOpen_BlastAir_OFF						237
#define T_St042_CoverOpen_Warning_ON						238
#define T_St042_Storage_ON_OFF								239

#define T_St044_BF_ON										240
#define T_St044_BF_OFF										241
#define T_St044_BlastAir_ON									242
#define T_St044_BlastAir_OFF							    243
#define T_St044_Warning_ON									244
#define T_St044_Warning_OFF									245
#define T_St044_CoverOpen_BF_OFF							246
#define T_St044_CoverOpen_BlastAir_OFF						247
#define T_St044_CoverOpen_Warning_ON						248
#define T_St044_Storage_ON_OFF								249

#ifdef HVPruefung_vorhanden
	#define T_HV_Wartezeit_HV_ein							396
	#define T_HV_Pruefzeit									397
	#define T_HV_Pruef_Leerlaufbereich						398
	#define T_HV_Pruef_DCOffset								399
#endif

//##END_ZEITEN			Zeile nicht loeschen


//*****************************************************************
//***************  Konstanten f黵 Schrittketten  ******************
//*****************************************************************

//##ANF_KETTEN			Zeile nicht loeschen

#define K_St201_MainDriveUnit_Line					         10
#define K_St001_Housing_Separating	                         1
#define K_St003_Housing_Press1	                             3
#define K_St005_Housing_Press2	                             5

#define K_St202_MainDriveUnit_Rotate1					     20
#define K_St021_Check_Carrier_Empty	                         21
#define K_St022_Current_Bar_Feeding_A                        22
#define K_St023_Check_Press_Current_Bar                      23
#define K_St022_Current_Bar_Feeding_S                        35
#define K_St024_Clamping_Sleeve_Feeding                      24
#define K_St025_Metal_Parts_Assembly                         25
#define K_St026_Clamping_Sleeve_Checking                     26
#define K_St027_Reject_Parts_Eject                           27
#define K_St028_Pre_Assembled_Parts_Eject                    28

#define K_St203_MainDriveUnit_Rotate2					     40
#define K_St041_Check_Carrier_Empty	                         41
#define K_St042_Current_Bar_Feeding_A                        42
#define K_St043_Check_Press_Current_Bar                      43
#define K_St042_Current_Bar_Feeding_S                        55
#define K_St044_Clamping_Sleeve_Feeding                      44
#define K_St045_Metal_Parts_Assembly                         45
#define K_St046_Clamping_Sleeve_Checking                     46
#define K_St047_Reject_Parts_Eject                           47
#define K_St048_Pre_Assembled_Parts_Eject                    48

#define K_St202_Hauptablauf_Teller							50
#define K_St203_Hauptablauf_Teller							51
#define K_St204_Hauptablauf_Teller							52



#ifdef HVPruefung_vorhanden
	#define K_HV_Kalibrierung								41
#endif

//##END_KETTEN			Zeile nicht loeschen


//*****************************************************************
//***************  Konstanten f黵 Z鋒ler  *************************
//*****************************************************************

//##ANF_ZAEHLER			Zeile nicht loeschen

// #define Z_R1_Messungen									200
#define Z_Lock_Unload								210

//##END_ZAEHLER			Zeile nicht loeschen

//*****************************************************************
//*************  Variablen f黵 die BDE-Kommuniktion  **************
//*****************************************************************

bool PC_Warning[MAX_WARNING+1];		// Warnungen[0..21]
bool PC_Message[MAX_MESSAGE+1];		// Meldungen[0..21]

bool PC_release_Article		= false;	// Host <- release article						bool PC_Artikelfreigabe		= false;	// Host <- Artikelfreigabe
bool PC_Quantity_reached	= false;	// Host <- quantity reached						bool PC_Stueckzahl_erreicht	= false;	// Host <- Stueckzahlvorgabe erreicht
bool PC_AchsenEingabe		= false;	// Host <- Achsenfreigabe ???					bool PC_AchsenEingabe		= false;	// Host <- Achsenfreigabe
bool PC_StandBy				= false;	// Host <- Ma. in Standby						bool PC_StandBy				= false;	// Host <- Ma. in Standby
bool PC_Register0			= false;	// Host <- Register leer ???					bool PC_Register0			= false;	// Host <- Register leer
bool PC_NewData				= false;	// Host <- retrieve data						bool PC_DatenNeu			= false;	// Host <- Daten neu anfordern
bool PC_Service_aktiv		= false;	//												bool PC_Service_aktiv		= false;	// Host <- Service akivieren

bool PC_Machine_Off			= false;	// Host -> machine off							bool PC_MaAus				= false;	// Host -> Maschine Aus
bool PC_Unload				= false;	// Host -> unload machine						bool PC_Leerfahren			= false;	// Host -> Maschine leerfahren
bool PC_SingleStep			= false;	// Host -> single step on/off					bool PC_Einzelschritt		= false;	// Host -> Einzelschritt ein/aus
bool PC_delete_Register		= false;	// Host -> delete Register 						bool PC_Register_Loesch		= false;	// Host -> Register loeschen
bool PC_Reprocess_reject_Parts		= false;	// Host -> Ausschuss aufarbeiten		bool PC_Ausschuss			= false;	// Host -> Ausschuss aufarbeiten
bool PC_exit_Program		= false;	// Host -> to exit program						bool PC_Programm_beenden	= false;	// Host -> Programm beenden

//**************************************************************
//***************  Array Variablen Hauptmaschine  **************
//**************************************************************

bool E_EndPosition_Machine[MAX_SEQUENCES+1];		//E_Endstell_Maschine[MAXSKETTE+1];			// Endstellung Kolben f黵 Maschine aus
bool SK_EndPosition_Machine[MAX_SEQUENCES+1];		//SK_Endstell_Maschine[MAXSKETTE+1];			// Endstellung Schrittkette f黵 Maschine aus

bool MainAir[MAX_MAINAIR+1];						// Hauptluft Ventile ausschalten

bool M_Error_Air_Off[MAX_MAINAIR+1];
bool MovingTest_Start[MAX_MAINAIR+1];
bool M_MovingTest_Error[MAX_MAINAIR+1];
bool MovingTest_Begin[MAX_MAINAIR+1];
bool MovingTest_End = false;

bool E_MovingTest_back[MAX_MAINAIR+1];
bool E_MovingTest_in_front[MAX_MAINAIR+1];

bool A_MovingTest_backward[MAX_MAINAIR+1];
bool A_MovingTest_forward[MAX_MAINAIR+1];

//**************************************************************
//*************  Variablen f黵 Stopuhr Function  ***************
//**************************************************************

long StartTime[MAX_SEQUENCES+1][MAX_STOPWATCH+1];
long StopTime[MAX_SEQUENCES+1][MAX_STOPWATCH+1];
long RunTime[MAX_SEQUENCES+1][MAX_STOPWATCH+1];
long RunTime_max[MAX_SEQUENCES+1][MAX_STOPWATCH+1];
long RunTime_min[MAX_SEQUENCES+1][MAX_STOPWATCH+1];

WORD MinuteCycle[MAX_SEQUENCES+1][MAX_STOPWATCH+1];
long MinuteCycle_actual[MAX_SEQUENCES+1][MAX_STOPWATCH+1];
long MinuteCycle_max[MAX_SEQUENCES+1][MAX_STOPWATCH+1];

bool RunTimes_Reset_Station[MAX_SEQUENCES+1];
bool All_RunTimes_Reset = false;

struct TLaufzeiten
{
	char Dateiname[100];
	char Text[1000];
	bool Speichern;
	bool Gespeichert;
};
struct TLaufzeiten Laufzeiten[MAX_SEQUENCES+1];

//****************************************************************
//*****************  Safetybridge Variablen  *********************
//****************************************************************

#include "klassen\\FuncTimer.h"

struct TSBT
{
	bool E_Quit;								//E_Quittieren;
	bool E_Door[NUMBERSAFETYDOORS+1];			//E_Schutztuer[ANZAHLSCHUTZTUEREN+1];
	bool E_SafetyDoorCircleClosed;				//E_SchutztuerkreisGeschlossen;
	bool E_EmergencyStopCircleClosed;			//E_NotHaltKreisGeschlossen;
	bool E_SingleStepMode;						//E_Prozessbeobachtung;
	bool E_Automatic;							//E_Automatik;
	bool E_ErrorKey;							//E_StoerungSchluessel;

	bool A_KeepClosed_SafetyDoors;				//A_SchutztuerenZuhalten;
	bool A_MotorStandStill;						//A_MotorenStehen;
	bool A_SoftwareEmergencyStop;				//A_SoftwareNotHalt;

	bool SafetyCircleClosed;					//SicherheitskreiseGeschlossen;
	bool ErrorMaOff;							//StoerungMaAus;
	bool ErrorEmergencyStop;					//StoerungNotHalt;
	bool ErrorSafetyDoorCircle;					//StoerungSchutztuerKreis;
	bool ErrorDoorsNotClosed;					//StoerungSchutztuerenNichtZu;
	bool ErrorSafetyDoor[NUMBERSAFETYDOORS+1];	//FehlerSchutztuer[ANZAHLSCHUTZTUEREN+1]
	bool ErrorKey;								//StoerungSchluessel;

	CTimer *TmEinschaltvorgang;
	CTimer *TmEinzel;
	CTimer *TmMaTipp;
};

struct TSBT SBTMaPart1;
struct TSBT SBTMaPart2;

// F黵 Diagnosezwecke, jedes einzelne Modul kann einen Fehlercode ausgeben
const BYTE MAXMODULEPROINSEL = 17;

struct TSBTInsel // Safetybridge Master
{
	unsigned short ID;				// Fortlaufende Nr der einzelnen Master start bei 0
	unsigned short IDSafeConf;		// In SafeConf vergebene Insel-Nummer
	unsigned short NumberOfModuls;	// Anzahl der Module inklusive LSPDO, MAX 17!
	unsigned short SatLPSDOSlave;	// Kommunikation zur nachfolgenden Insel (Satelliten-Nummer des LPSDO_slave)
	unsigned short GatewayBefore;	// Adresse der Gateways zum vorhergehenden
	unsigned short GatewayAfter;	// und zum nachfolgenden Bussystem
	bool EQ[33];					// Eing鋘ge MAX 32
	bool EI[33];					// Ausg鋘ge MAX 32

	bool AutomaticQuit;
	bool HighRunPhaseFinished;
	int Status;

	struct TSBTModul
	{
		WORD ErrorCode;
	};
	TSBTModul Modul[MAXMODULEPROINSEL+1];

	char PfadBinDatei[256];
};

struct TSBTInsel SBTInsel1;	// Master 1
struct TSBTInsel SBTInsel2;	// Master 2


//*****************************************************************
//*******************  Eing鋘ge Hauptmaschinenteil ****************
//*****************************************************************

//**** Allgemeine Eing鋘ge ****
bool E_PressureSwitch								= false;		//E_Druckwaechter
bool E_Button_ProcessObservationMode				= false;		//E_Zustimmtaster

// Eing鋘ge vom Tasterpult
bool E_Button_MaOn									= false;		//E_TP_Maschine_ein
bool E_Button_MaOff									= false;		//E_TP_Maschine_aus
bool E_Button_Quit									= false;		//E_TP_Quittieren
bool E_Button_AirOn									= false;		//E_TP_Luft_Ein_Aus
bool E_Button_ConveyorOn							= false;		//E_TP_Vibr_Ein_Aus
bool E_Button_TipMode								= false;		//E_TP_Tipptaster

// Eing鋘ge am Maschinenrahmen
bool E_Key_311										= false;		//E_Schluessel_311
bool E_Print_Label									= false;		//E_Etikett_drucken
bool E_Unload_Machine								= false;		//E_Maschine_leerfahren
bool E_Bridge_StandByPosition						= false;		//E_Wartestellung_ueberbruecken

//**** Eing鋘ge f黵 Doppel Achse ****
bool E_St201_B1_4_SwivelUnit_in_front				= false;		//E_St201_B1_4_Schwenkeinheit_vorne
bool E_St201_B1_2_SwivelUnit_back					= false;		//E_St201_B1_2_Schwenkeinheit_hinten
bool E_St201_B4_WPC_InPosition						= false;		//E_St201_B4_Nest_eingelaufen
bool E_St201_B5_WPC_InPosition						= false;		//E_St201_B5_Nest_eingelaufen
bool E_St302_B1_FB_voll								= false;		//E_St302_B1_FB_voll

//**** Eing鋘ge f黵 Flex-Link Band ****
bool E_St301_B2_AxisProtector_in_front				= false;		//E_St301_B2_Achsenschoner_vorfahren
bool E_St301_B3_AxisProtector_in_front				= false;		//E_St301_B3_Achsenschoner_vorfahren

//**** Eing鋘ge zur Kommunikation zwischen den Teilen ***
bool E_Gateway_following_SPS_Enable_Conveyor		= false;	//<- Freigabe der Vibratoren von folgender SPS empfangen			E_Gateway_folgende_SPS_Freigabe_Vibr
bool E_Gateway_following_SPS_Quit					= false;	//<- E_TP_Quittieren von folgender SPS empfangen					E_Gateway_folgende_SPS_Enstperren
bool E_Gateway_following_SPS_Unloaded				= false;	//<- Maschine leergefahren von folgender SPS empfangen				E_Gateway_folgende_SPS_leergefahren
bool E_Gateway_following_SPS_St302_FlexLink_Run		= false;	//<- Zwischenf鰎derband l鋟ft von folgender SPS empfangen			E_Gateway_folgende_SPS_St302_FlexLink_laeuft
bool E_Gateway_before_SPS_Enable_Conveyor		    = false;	//<- Freigabe der Vibratoren von vorheriger SPS empfangen			E_Gateway_vorherige_SPS_Freigabe_Vibr
bool E_Gateway_before_SPS_Quit						= false;	//<- E_TP_Quittieren von vorheriger SPS empfangen					E_Gateway_vorherige_SPS_Entsperren
bool E_Gateway_before_SPS_Unloaded					= false;	//<- Maschine leergefahren von vorheriger SPS empfangen				E_Gateway_vorherige_SPS_leergefahren
bool E_Gateway_before_SPS_St302_FlexLink_full		= false;	//<- Verbindungsf鰎derband voll von vorheriger SPS empfangen		E_Gateway_vorherige_SPS_St302_FlexLink_voll

// Umlauff鰎derband l鋟ft von vorheriger SPS empfangen und an folgende Weiterleiten
bool M_Gateway_St301_FlexLink_Run                = false;

bool M_CurrentSlection_MB2_5 = false;
bool M_CurrentSlection_MB3_0 = false;

//*****************************************************************
//*******************       Conveyor      *************************
//*****************************************************************
//Station 1
bool E_St1_B1_MBK_3_houisng_in_position				= false;
bool E_St1_B2_MBK_2p5_houisng_in_position			= false;
bool E_St1_B3_housing_channel_empty		            = false;
bool E_St1_B4_housing_channel_full		            = false;



bool A_St1_MBK_2p5_A1_bowl_feeder_enable			= false;
bool A_St1_MBK_3_A2_bowl_feeder_enable				= false;
bool A_St1_MBK_linear_A3_enable      				= false;
bool A_St1_MBK_linear_A4_enable						= false;
bool A_St1_MBK_3_Y1_blowing_air_for_bowl_feeder		= false;
bool A_St1_MBK_2p5_Y2_blowing_air_for_bowl_feeder	= false;




bool A_St1_A1_Enable_BF								= false;
bool A_St1_A11_Enable_BF								= false;
bool A_St1_A2_Enable_LC								= false;
bool A_St1_Y1_BlastAir_BF                           = false;


bool E_St022_B1_current_bar_in_position			      = false;
bool E_St022_B2_housing_channel_empty		          = false;
bool E_St022_B3_housing_channel_full		          = false;
bool A_St022_A1_Enable_BF						      = false;
bool A_St022_A2_Enable_LC							  = false;
bool A_St022_Y1_BlastAir_BF                           = false;

bool E_St024_B2_material_empty                        = false;
bool E_St024_B3_housing_channel1_empty		          = false;
bool E_St024_B4_housing_channel2_empty		          = false;
bool E_St024_B5_housing_channel1_full		          = false;
bool E_St024_B6_housing_channel2_full		          = false;
bool A_St024_A1_Enable_BF						      = false;
bool A_St024_A2_Enable_LC							  = false;
bool A_St024_Y1_BlastAir1_BF                           = false;
bool A_St024_Y2_BlastAir2_BF                           = false;

bool E_St042_B1_current_bar_in_position				  = false;
bool E_St042_B2_housing_channel_empty		          = false;
bool E_St042_B3_housing_channel_full		          = false;
bool A_St042_A1_Enable_BF						      = false;
bool A_St042_A2_Enable_LC							  = false;
bool A_St042_Y1_BlastAir_BF                           = false;


bool E_St044_B1_clamping_sleeve1_in_position	       = false;
bool E_St044_B2_clamping_sleeve2_in_position	       = false;
bool E_St044_B3_housing_channel1_empty					 = false;
bool E_St044_B4_housing_channel2_empty					 = false;

bool E_St044_B5_housing_channel1_full		          = false;
bool E_St044_B6_housing_channel2_full		          = false;
bool A_St044_A1_Enable_BF						      = false;
bool A_St044_A2_Enable_LC							  = false;
bool A_St044_Y1_BlastAir_BF                           = false;







//*****************************************************************
//*******************   Stations bezogen  *************************
//*****************************************************************

//Station 1
bool E_St1_B1_4_housing_stopper_downward						     = false;
bool E_St1_B1_2_housing_stopper_upward								 = false;
bool E_St1_B2_4_housing_separator_downward						     = false;
bool E_St1_B2_2_housing_separator_upward							 = false;
bool E_St1_B3_4_housing_separator_driver_forward					 = false;
bool E_St1_B3_2_housing_separator_driver_backward				     = false;


//Station 201
bool E_St201_B1_4_houisng_carrier_driver_forward					     = false;
bool E_St201_B1_2_houisng_carrier_driver_backward					     = false;
bool E_St201_B2_4_houisng_pin_driver1_forward						     = false;
bool E_St201_B2_2_houisng_pin_driver1_backward						     = false;
bool E_St201_B3_4_houisng_pin_driver2_forward						     = false;
bool E_St201_B3_2_houisng_pin_driver2_backward				             = false;
bool E_St201_B4_4_houisng_pin_driver3_forward						     = false;
bool E_St201_B4_2_houisng_pin_driver3_backward				             = false;
bool E_St201_B5_4_housing_carrier_lifterZ6_upward					     = false;
bool E_St201_B5_2_housing_carrier_lifterZ6_downward				         = false;
bool E_St201_B6_4_housing_carrier_lifterZ8_upward					     = false;
bool E_St201_B6_2_housing_carrier_lifterZ8_downward				         = false;
bool E_St201_B7_4_housing_carrier_lifterZ5_upward					     = false;
bool E_St201_B7_2_housing_carrier_lifterZ5_downward				         = false;
bool E_St201_B8_4_housing_carrier_lifterZ7_upward					     = false;
bool E_St201_B8_2_housing_carrier_lifterZ7_downward				         = false;


bool E_St201_B3_houisng_pin_in_position1			                     = false;
bool E_St201_B4_houisng_pin_in_position2			                     = false;

bool E_St202_B1_Teller_Ready	                 = false;
bool E_St202_B2_Teller_Rotating                  = false;
bool E_St202_B3_Teller_Lock	                     = false;

bool E_St203_B1_Teller_Ready	                 = false;
bool E_St203_B2_Teller_Rotating                  = false;
bool E_St203_B3_Teller_Lock	                     = false;

//Station 021
bool E_St021_B1_WT_checking					     = false;

//Station 022
bool E_St022_B1_4_current_bar_inserter_forward						     = false;
bool E_St022_B1_2_current_bar_inserter_backward						     = false;
bool E_St022_B2_4_current_bar_rotating_take						     = false;
bool E_St022_B2_2_current_bar_rotating_send							     = false;
bool E_St022_B3_4_current_bar_gripper_close 						     = false;
bool E_St022_B3_2_current_bar_gripper_open							     = false;
bool E_St022_B4_4_gripper_lifter_upward 							     = false;
bool E_St022_B4_2_gripper_lifter_downward							     = false;
bool E_St022_B5_4_current_bar_driver_forward 							 = false;
bool E_St022_B5_2_current_bar_driver_backward 							 = false;


//Station 023
bool E_St023_B1_4_current_bar_presser_downward						     = false;
bool E_St023_B1_2_current_bar_presser_upward						     = false;

bool E_St023_B1_current_bar_in_position								     = false;


//Station 024
bool E_St024_B1_4_clamping_sleeve_presser_forward							 = false;
bool E_St024_B1_2_clamping_sleeve_presser_backward						     = false;
bool E_St024_B2_4_clamping_sleeve_presser_forward						     = false;
bool E_St024_B2_2_clamping_sleeve_presser_backward						     = false;
bool E_St024_B3_4_gripper_lifter_downward								     = false;
bool E_St024_B3_2_gripper_lifter_upward									     = false;
bool E_St024_B4_4_clamping_sleeve_gripper_close 						     = false;
bool E_St024_B4_2_clamping_sleeve_gripper_open							     = false;
bool E_St024_B5_4_clamping_sleeve_gripper_close 						     = false;
bool E_St024_B5_2_clamping_sleeve_gripper_open							     = false;
bool E_St024_B6_4_clamping_sleeve_driver_forward 						     = false;
bool E_St024_B6_2_clamping_sleeve_driver_backward 						     = false;


bool E_St024_B1_clamping_sleeve_in_position								     = false;
bool E_St024_B2_clamping_sleeve_in_position								     = false;
bool E_St024_B3_material_empty												 = false;
bool E_St024_B4_material_empty												 = false;


//Station 025
bool E_St025_B1_4_metal_parts_assembling_close							     = false;
bool E_St025_B1_2_metal_parts_assembling_open							     = false;
bool E_St025_B2_4_gripper_lifter_upward 								     = false;
bool E_St025_B2_2_gripper_lifter_downward 								     = false;

//Station 026
bool E_St026_B1_check_clamping_sleeve_in_position							 = false;
bool E_St026_B2_check_clamping_sleeve_in_position	 					     = false;

//Station 027
bool E_St027_B1_4_reject_parts_gripper_close 							     = false;
bool E_St027_B1_2_reject_parts_gripper_open								     = false;
bool E_St027_B2_4_gripper_lifter_upward 								     = false;
bool E_St027_B2_2_gripper_lifter_downward 								     = false;
bool E_St027_B3_4_reject_parts_ejector_forward							     = false;
bool E_St027_B3_2_reject_parts_ejector_backward							     = false;

//Station 028
bool E_St028_B1_4_pre_assembled_parts_gripper_close 					     = false;
bool E_St028_B1_2_pre_assembled_parts_gripper_open 						     = false;
bool E_St028_B2_4_gripper_lifter_upward 								     = false;
bool E_St028_B2_2_gripper_lifter_downward 								     = false;
bool E_St028_B3_4_pre_assembled_parts_ejector_forward					     = false;
bool E_St028_B3_2_pre_assembled_parts_ejector_backward					     = false;
bool E_St028_B4_4_pre_assembled_parts_ejector_forward						 = false;
bool E_St028_B4_2_pre_assembled_parts_ejector_backward						 = false;

//Station 003
bool E_St003_B1_4_metal_parts_blocking_downward 					     = false;
bool E_St003_B1_2_metal_parts_blocking_upward  						     = false;

//Station 041
bool E_St041_B1_WT_checking		= false;

//Station 042
bool E_St042_B1_4_current_bar_separator_forward					         = false;
bool E_St042_B1_2_current_bar_separator_backward						 = false;
bool E_St042_B2_4_current_bar_inserter_forward					         = false;
bool E_St042_B2_2_current_bar_inserter_backward							 = false;
bool E_St042_B3_4_current_bar_rotating_take						         = false;
bool E_St042_B3_2_current_bar_rotating_send								 = false;
bool E_St042_B4_4_current_bar_gripper_close								 = false;
bool E_St042_B4_2_current_bar_gripper_open								 = false;
bool E_St042_B5_4_gripper_rotating_take								     = false;
bool E_St042_B5_2_gripper_rotating_send									 = false;
bool E_St042_B6_4_gripper_rotating_upward								 = false;
bool E_St042_B6_2_gripper_rotating_downward								 = false;
bool E_St042_B7_4_current_bar_driver_forward							 = false;
bool E_St042_B7_2_current_bar_driver_backward							 = false;


//Station 043
bool E_St043_B1_4_current_bar_presser_downward					         = false;
bool E_St043_B1_2_current_bar_presser_upward							 = false;

bool E_St043_B1_current_bar_in_position							         = false;



//Station 044
bool E_St044_B1_4_clamping_sleeve_presser_forward					         = false;
bool E_St044_B1_2_clamping_sleeve_presser_backward							 = false;
bool E_St044_B2_4_clamping_sleeve_presser_forward					         = false;
bool E_St044_B2_2_clamping_sleeve_presser_backward							 = false;
bool E_St044_B3_4_gripper_lifter_downward					                     = false;
bool E_St044_B3_2_gripper_lifter_upward								     = false;
bool E_St044_B4_4_clamping_sleeve_gripper_close					             = false;
bool E_St044_B4_2_clamping_sleeve_gripper_open							     = false;
bool E_St044_B5_4_clamping_sleeve_gripper_close					             = false;
bool E_St044_B5_2_clamping_sleeve_gripper_open							     = false;
bool E_St044_B6_4_clamping_sleeve_driver_forward					         = false;
bool E_St044_B6_2_clamping_sleeve_driver_backward						     = false;

bool E_St044_B1_clamping_sleeve_in_position							         = false;
bool E_St044_B2_clamping_sleeve_in_position							         = false;

//Station 045
bool E_St045_B1_4_metal_parts_assembling_close							     = false;
bool E_St045_B1_2_metal_parts_assembling_open							     = false;
bool E_St045_B2_4_gripper_lifter_upward 								     = false;
bool E_St045_B2_2_gripper_lifter_downward 								     = false;

//Station 046
bool E_St046_B1_check_clamping_sleeve_in_position							 = false;
bool E_St046_B2_check_clamping_sleeve_in_position	 					     = false;

//Station 047
bool E_St047_B1_4_reject_parts_gripper_close 							     = false;
bool E_St047_B1_2_reject_parts_gripper_open								     = false;
bool E_St047_B2_4_gripper_lifter_upward 								     = false;
bool E_St047_B2_2_gripper_lifter_downward 								     = false;
bool E_St047_B3_4_reject_parts_ejector_forward							     = false;
bool E_St047_B3_2_reject_parts_ejector_backward							     = false;

//Station 048
bool E_St048_B1_4_pre_assembled_parts_gripper_close 					     = false;
bool E_St048_B1_2_pre_assembled_parts_gripper_open 						     = false;
bool E_St048_B2_4_gripper_lifter_upward 								     = false;
bool E_St048_B2_2_gripper_lifter_downward 								     = false;
bool E_St048_B3_4_pre_assembled_parts_ejector_forward					     = false;
bool E_St048_B3_2_pre_assembled_parts_ejector_backward					     = false;
bool E_St048_B4_4_pre_assembled_parts_ejector_forward						 = false;
bool E_St048_B4_2_pre_assembled_parts_ejector_backward						 = false;

//Station 005
bool E_St005_B1_4_metal_parts_blocking_downward 					     = false;
bool E_St005_B1_2_metal_parts_blocking_upward  						     = false;

//Station 301
bool E_St301_B1_housing_channel_empty								     = false;
bool E_St301_B2_housing_channel_empty 								     = false;


//*****************************************************************
//*************  Ausg鋘ge Hauptmaschinenteil  *********************
//*****************************************************************

//**** Allgemeine Ausg鋘ge ****
// Ausg鋘ge vom Tasterpult
bool A_LED_MaOn										= false;			//A_TP_LED_Maschine_ein
bool A_LED_MaOff									= false;			//A_TP_LED_Maschine_aus
bool A_LED_AirOn									= false;			//A_TP_LED_Luft
bool A_LED_ConveyorOn								= false;			//A_TP_LED_Vibratoren
bool A_Horn											= false;			//A_TP_Hupe
bool A_LED_Quit										= false;			//A_TP_LED_Quittieren
bool A_LED_TipMode									= false;			//A_TP_LED_Tipptaster

// Ausg鋘ge am Maschinenrahmen
bool A_LED_Unload_Machine							= false;			//A_LED_Maschine_leerfahren
bool A_LED_Bridge_StandByPosition					= false;			//A_LED_Wartestellung_ueberbruecken

bool A_All_ErrorLamp								= false;			//A_Stoerungslampe_Gesamt
bool A_Machine_Lamp									= false;
bool A_MainAir[MAX_MAINAIR+1];
bool A_LEDError[MAXANZSTAT+1];
bool A_MachineLightningOn							= false;

bool A_LED_Service_aktiv							= false;

//**** Ausg鋘ge f黵 Achse ****
bool A_St201_M2_Enable_WPC_accelerator				= false;
bool A_St201_M2_Paramtersatz_1						= false;
bool A_St201_M2_Paramtersatz_2						= false;
bool A_St201_M2_Paramtersatz_3						= false;
bool A_St201_M2_Paramtersatz_4						= false;

bool A_St201_M3_Enable_WPC_accelerator				= false;
bool A_St201_M3_Paramtersatz_1						= false;
bool A_St201_M3_Paramtersatz_2						= false;
bool A_St201_M3_Paramtersatz_3						= false;
bool A_St201_M3_Paramtersatz_4						= false;

//**** Ausg鋘ge f黵 Flex-Link Band ****
bool A_St301_A1_FlexLink_Enable						= false;
bool A_St301_A1_FlexLink_slow						= false;
bool A_St301_A1_FlexLink_fast						= false;

bool A_St302_A1_FlexLink_Enable						= false;
bool A_St302_A1_FlexLink_slow						= false;
bool A_St302_A1_FlexLink_fast						= false;

bool A_St302_Y1_WT_abblasen							= false;

//*****************************************************************
//*******************   Stations bezogen  *************************
//*****************************************************************





//****   Ausg鋘ge zur Kommunikation zwischen den Teilen
// TODO: Zus鋞zliche Ausg鋘ge f黵 Gateway deklarieren.
// bool A_Gateway_vorherige_SPS... = false;
// bool A_Gateway_folgende_SPS...  = false;

//*****************************************************************
//*******************   Stations bezogen  *************************
//*****************************************************************
// Alle Ausg鋘de f黵 die Zylinder werden in dieser Struktur definiert
struct TA
{

bool St1_Y1_4_housing_stopper_downward;
bool St1_Y1_2_housing_stopper_upward;
bool St1_Y2_4_housing_separator_downward;
bool St1_Y2_2_housing_separator_upward;
bool St1_Y3_4_housing_separator_driver_forward;
bool St1_Y3_2_housing_separator_driver_backward;

bool St201_A1_4_houisng_carrier_driver_forward                       ;
bool St201_A1_2_houisng_carrier_driver_backward					     ;
bool St201_A2_4_houisng_pin_driver1_2_forward						 ;
bool St201_A2_2_houisng_pin_driver1_2_backward						 ;
//bool St201_A3_4_houisng_pin_driver2_forward						     ;
//bool St201_A3_2_houisng_pin_driver2_backward				         ;
bool St201_A4_4_houisng_pin_driver3_forward						     ;
bool St201_A4_2_houisng_pin_driver3_backward				         ;
bool St201_A5_4_housing_carrier_lifter1_upward					     ;
bool St201_A5_2_housing_carrier_lifter1_downward				     ;
bool St201_A6_4_housing_carrier_lifter2_upward					     ;
bool St201_A6_2_housing_carrier_lifter2_downward				     ;
bool St201_A7_4_housing_carrier_lifterZ57_upward					 ;
bool St201_A7_2_housing_carrier_lifterZ57_downward				     ;
bool St201_A8_4_housing_carrier_lifterZ68_upward					 ;
bool St201_A8_2_housing_carrier_lifterZ68_downward				     ;

bool St201_Y1_MBK_3_houisng_in_position				                 ;
bool St201_Y2_MBK_2p5_houisng_in_position				             ;
bool St201_Y3_houisng_pin_in_position1			                     ;
bool St201_Y4_houisng_pin_in_position2			                     ;


bool St202_A1_4_Rotate ;
bool St202_A1_2_Lock   ;
bool St203_A1_4_Rotate ;
bool St203_A1_2_Lock   ;
bool St202_A1_MainAir  ;
bool St203_A1_MainAir  ;














//Station 022
bool St022_Y1_4_current_bar_inserter_forward						 ;
bool St022_Y1_2_current_bar_inserter_backward						 ;
bool St022_Y2_4_current_bar_rotating_take						     ;
bool St022_Y2_2_current_bar_rotating_send							 ;
bool St022_Y3_4_current_bar_gripper_close 						     ;
bool St022_Y3_2_current_bar_gripper_open							 ;
bool St022_Y4_4_gripper_lifter_upward 							     ;
bool St022_Y4_2_gripper_lifter_downward							     ;
bool St022_Y5_4_current_bar_driver_forward 							 ;
bool St022_Y5_2_current_bar_driver_backward 					     ;


//Station 023
bool St023_Y1_4_current_bar_presser_downward						 ;
bool St023_Y1_2_current_bar_presser_upward						     ;


//Station 024
bool St024_Y1_4_clamping_sleeve_presser_forward							;
bool St024_Y1_2_clamping_sleeve_presser_backward						;
bool St024_Y2_4_clamping_sleeve_presser_forward						    ;
bool St024_Y2_2_clamping_sleeve_presser_backward						;
bool St024_Y3_4_gripper_lifter_downward								    ;
bool St024_Y3_2_gripper_lifter_upward									;
bool St024_Y4_4_clamping_sleeve_gripper_close 						    ;
bool St024_Y4_2_clamping_sleeve_gripper_open							;
bool St024_Y5_4_clamping_sleeve_gripper_close 						    ;
bool St024_Y5_2_clamping_sleeve_gripper_open							;
bool St024_Y6_4_clamping_sleeve_driver_forward 						    ;
bool St024_Y6_2_clamping_sleeve_driver_backward 						;


//Station 025
bool St025_Y1_4_metal_parts_assembling_close							;
bool St025_Y1_2_metal_parts_assembling_open							    ;
bool St025_Y2_4_gripper_lifter_upward 								    ;
bool St025_Y2_2_gripper_lifter_downward 								;

//Station 026


//Station 027
bool St027_Y1_4_reject_parts_gripper_close 							    ;
bool St027_Y1_2_reject_parts_gripper_open								;
bool St027_Y2_4_gripper_lifter_upward 								    ;
bool St027_Y2_2_gripper_lifter_downward 								;
bool St027_Y3_4_reject_parts_ejector_forward							;
bool St027_Y3_2_reject_parts_ejector_backward							;

//Station 028
bool St028_Y1_4_pre_assembled_parts_gripper_close 					    ;
bool St028_Y1_2_pre_assembled_parts_gripper_open 						;
bool St028_Y2_4_gripper_lifter_upward 								    ;
bool St028_Y2_2_gripper_lifter_downward 							    ;
bool St028_Y3_4_pre_assembled_parts_ejector_forward					    ;
bool St028_Y3_2_pre_assembled_parts_ejector_backward				    ;
bool St028_Y4_4_pre_assembled_parts_ejector_forward						;
bool St028_Y4_2_pre_assembled_parts_ejector_backward				    ;

//Station 003
bool St003_Y1_4_metal_parts_blocking_downward 					     ;
bool St003_Y1_2_metal_parts_blocking_upward  						 ;
//Station 041

//Station 042
bool St042_Y1_4_current_bar_separator_forward					     ;
bool St042_Y1_2_current_bar_separator_backward						 ;
bool St042_Y2_4_current_bar_inserter_forward					     ;
bool St042_Y2_2_current_bar_inserter_backward					     ;
bool St042_Y3_4_current_bar_rotating_take						     ;
bool St042_Y3_2_current_bar_rotating_send						     ;
bool St042_Y4_4_current_bar_gripper_close						     ;
bool St042_Y4_2_current_bar_gripper_open							 ;
bool St042_Y5_4_gripper_rotating_take								 ;
bool St042_Y5_2_gripper_rotating_send								 ;
bool St042_Y6_4_gripper_rotating_upward								 ;
bool St042_Y6_2_gripper_rotating_downward						     ;
bool St042_Y7_4_current_bar_driver_forward							 ;
bool St042_Y7_2_current_bar_driver_backward							 ;


//Station 043
bool St043_Y1_4_current_bar_presser_downward					     ;
bool St043_Y1_2_current_bar_presser_upward							 ;

//Station 044
bool St044_Y1_4_clamping_sleeve_presser_forward					             ;
bool St044_Y1_2_clamping_sleeve_presser_backward							 ;
bool St044_Y2_4_clamping_sleeve_presser_forward					             ;
bool St044_Y2_2_clamping_sleeve_presser_backward							 ;
bool St044_Y3_4_gripper_lifter_downward					                     ;
bool St044_Y3_2_gripper_lifter_upward								         ;
bool St044_Y4_4_clamping_sleeve_gripper_close					             ;
bool St044_Y4_2_clamping_sleeve_gripper_open							     ;
bool St044_Y5_4_clamping_sleeve_gripper_close					             ;
bool St044_Y5_2_clamping_sleeve_gripper_open							     ;
bool St044_Y6_4_clamping_sleeve_driver_forward					             ;
bool St044_Y6_2_clamping_sleeve_driver_backward						         ;

//Station 045
bool St045_Y1_4_metal_parts_assembling_close							     ;
bool St045_Y1_2_metal_parts_assembling_open							         ;
bool St045_Y2_4_gripper_lifter_upward 								         ;
bool St045_Y2_2_gripper_lifter_downward 								     ;

//Station 046


//Station 047
bool St047_Y1_4_reject_parts_gripper_close 							        ;
bool St047_Y1_2_reject_parts_gripper_open								    ;
bool St047_Y2_4_gripper_lifter_upward 								        ;
bool St047_Y2_2_gripper_lifter_downward 								    ;
bool St047_Y3_4_reject_parts_ejector_forward							    ;
bool St047_Y3_2_reject_parts_ejector_backward							    ;

//Station 048
bool St048_Y1_4_pre_assembled_parts_gripper_close 					 ;
bool St048_Y1_2_pre_assembled_parts_gripper_open 					 ;
bool St048_Y2_4_gripper_lifter_upward 								 ;
bool St048_Y2_2_gripper_lifter_downward 							 ;
bool St048_Y3_4_pre_assembled_parts_ejector_forward					 ;
bool St048_Y3_2_pre_assembled_parts_ejector_backward				 ;
bool St048_Y4_4_pre_assembled_parts_ejector_forward					 ;
bool St048_Y4_2_pre_assembled_parts_ejector_backward				 ;

//Station 005
bool St005_Y1_4_metal_parts_blocking_downward 					     ;
bool St005_Y1_2_metal_parts_blocking_upward                          ;

};
struct TA A;

//*****************************************************************
//********  Sondersachen f黵 den jeweiligen Maschinentyp  *********
//*****************************************************************

#ifdef Scanner_RFID_PN
	#ifndef Menue_programm
		#include "PF_RFID.h"
		#include "PF_RFID_CH.h"
		#include "ScannerPN.h"
	#endif
#endif

#ifdef Messpipe_vorhanden

	#define MaxMessungen 50
	typedef struct
	{
		double Stiftanfang;
		double Kraft_max;
		double Weg_max;
		bool Gutteil;
	}TMessdaten;		// Daten-Struktur-Typ

	TMessdaten Messung[MaxMessungen];

#endif

//---------------------------------------------------------------------------

#ifdef TCPCOM
	//--- Einstellungen TCP Kommunikation ---

	// Anzahl der Module eintragen
	#define MAXTCPMODULE 10

	#define ANZTCPMODULE 1

	// Gr鲞e der Arrays der Variablen die zu den TCP Modulen 黚ertragen werden sollen einstellen
	#define TCPANZINT	100
	#define TCPANZFLOAT 20
	#define TCPANZWORD	30
	#define TCPANZDWORD 30

	#ifndef Menue_programm
		#include "klassen\\socketclient.h"
		#include "klassen\\socketserver.h"
		// Threads Deklarieren
		HANDLE h_TCP_COMThread[MAXTCPMODULE];
		DWORD  d_TCP_COMThread_ID[MAXTCPMODULE];
		SOCKET SOCKET_TCP_COM[MAXTCPMODULE];
		// IP Adressen der Module eintragen
		const char *IP_TCP_COM[MAXTCPMODULE] = {"0.0.0.0","172.16.19.39","172.16.14.205"};
		const char *Port_TCP_COM[MAXTCPMODULE] ={"2001","2000","2000"};
		// Variablen f黵 dieKommunikation deklarieren
	#endif

	typedef struct
	{
		WORD SendedatenWORD[TCPANZWORD];
		float SendedatenFLOAT[TCPANZFLOAT];
		short int SendedatenINT[TCPANZINT];
		DWORD SendedatenDWORD[TCPANZDWORD];
		WORD EmpfangsdatenWORD[500];
		float EmpfangsdatenFLOAT[250];
		short int EmpfangsdatenINT[500];
		DWORD EmpfangsdatenDWORD[250];

		WORD AW[3];
		WORD IW[3];
		BOOL Activ;
	}tDatenTCP_COM;

	typedef struct
	{
		tDatenTCP_COM Modul[MAXTCPMODULE];
	}tTCP_COM;

	tTCP_COM TCP_COM;
#endif

//---------------------------------------------------------------------------

#ifndef Menue_programm
	#ifdef Canbus_vorhanden
		// IXXAT funktionen einbinden
		#include "Canbus\CanIXXAT_VCI.h"
		CanIXXAT_VCI CanCom;
		struct StrCanReceiveBuffer ArrMultiCanReceiveBufferSDO[8][100];
		struct StrCanReceiveBuffer ArrMultiCanReceiveBufferPDO[8][100];
	#endif
#endif // of Menue_programm

//---------------------------------------------------------------------------

typedef struct Verpackung	// Einstellen des Packmoduls
{
	char Str[3][35];		// Text 25St./50St. / Kiste
	long State;				// Einstellstatus
	WORD Anzahl;			// Anzahl der Teile
} TVerpack;

// Aktueller Inhalt
long VerpStueck;

//*****************************************************************
//*********************  Profinet Siemens FU  *********************
//*****************************************************************
#ifdef ProfinetActive

	bool bPN_M1_Run;
	bool bPN_M2_Run;
	bool bPN_M3_Run;
	BYTE EB_PN_Siemens_TrennData[3];

	struct TSiemensFU
	{
		//Eing鋘ge
		BYTE EB_PN_Siemens_IO_Data[4];
		BYTE EB_PN_Siemens_Data[28];
		//Ausg鋘ge
		BYTE AB_PN_Siemens_IO_Data[4];

		//Manuelle Betriebsart
		bool xManEnable;
		bool xManCycleCW;
		bool xManCycleCCW;
		//bool xManJogCW;
		//bool xManJogCCW;
		//Automatik
		bool xAutoEnable;
		bool xStartCycle;
		bool xReadyToStart;
		bool xStopCycle;
		bool xReset;
		bool xParam2;
		bool xDirection;
		int iErrorNo;
		bool xTableInPosition;
	};
	struct TSiemensFU SiemensFU_Data[3];
	#define SFU1 0
	#define SFU2 1
	#define SFU3 2

#endif // of #define ProfinetActive

//*****************************************************************
//*************  nicht Remanente Merker ***************************
//*****************************************************************

struct TAnzeigevari
{
	char bool_		[TEXTLEN];// 30 Variablen
	char double_	[TEXTLEN];
	char LONG_		[TEXTLEN];
};
struct TAnzeigevari Anzeigevari[MAXONLVAR];

int OnlineVarBool=0;
int OnlineVarDouble=0;
int OnlineVarLONG=0;

// !INFO:  unsigned Achse_Neg_Endlage:1;
//     Bedeutet: Bool磗ch Variable die nur 1 Bit belegt
// Diese Variablen werden automatisch eingelesen und angezeigt
// sie brauchnen nicht mit OnlVarEintrag eingetragen werden!!
// !Achtung die Bemerkungen mit # m黶sen stehen bleiben

struct TM_
{
//##ANF_MERKERBIT		Zeile nicht loeschen

//*****************************************************************
//****************  Hauptmaschinenteil  ***************************
//*****************************************************************

// Allgemeine Merker
unsigned _____Variablen_Artikel_____________:1;
unsigned _____Variablen_Status_Maschine_____:1;
unsigned Quit:1;
unsigned MaOn:1;
unsigned MaRun:1;
unsigned AirOn:1;
unsigned AirOff:1;
unsigned ConveyorOn:1;
unsigned MaError:1;
unsigned MaSingleStepMode:1;
unsigned MaStand_By:1;
unsigned All_Stations_SingleStepMode:1;

// Merker f黵 Freigaben
unsigned _____Variablen_Freigaben___________:1;
unsigned OutputEn:1;
unsigned MaStepEn:1;		//SKFrei
unsigned PressureAirEn:1;
unsigned ConveyorEn:1;
unsigned SafetyDoorEn:1;
unsigned MaSingleStepSwitch:1;
unsigned Bridge_SingleStepMode:1;
unsigned Quit_by_SingleStepMode:1;

// Merker f黵 Stoerung Maschine aus
unsigned _____Variablen_Stoerung_Aus________:1;
unsigned Reset_Stations_ControlTime:1;
unsigned MaStop:1;
unsigned MaOff_pressed:1;
unsigned General_Error_found:1;
unsigned Error_IBS:1;
unsigned Error_AirPressure:1;
unsigned Error_Marker_OK:1;

// Merker f黵 Endstellungen
unsigned _____Variablen_Endstellung_________:1;
unsigned EndPos_SK_Machine:1;
unsigned EndPos_K_Machine:1;
unsigned EndPos_SK_DriveUnits:1;
unsigned EndPos_K_DriveUnits:1;
unsigned EndPosition_Machine:1;
unsigned MaEndPosition_Error:1;
unsigned EndPos_K_DriveUnits_Error:1;

// Merker f黵 Achse
unsigned _____Variablen_Achse_St201_________:1;
unsigned St201_Online_Pole_to_Pole:1;
unsigned St201_Online_Blockend:1;
unsigned St201_AxisInPos_Camera:1;
unsigned St301_Axis_protector_forward:1;
unsigned St301_WPC_worked_in_circulation_process :1;

unsigned _____Variablen_Teller_________:1;
unsigned St203_Lock_shift_Register:1;					//St203_Register_schieben_sperren
unsigned St204_Plate1_fast:1;
unsigned St204_Lock_shift_Register:1;					//St204_Register_schieben_sperren
unsigned St204_Stop_Table:1;

// Merker Sicherheitsfunktion
unsigned _____Variablen_Sicherheit__________:1;
unsigned Error_MovingTest:1;
unsigned without_311_Key:1;

// Allgemeine Merker
unsigned _____Variablen_Allgemein___________:1;
unsigned Newstart:1;
unsigned MaReset:1;
unsigned ImpulseMaOn:1;
unsigned ImpulseMaOff:1;
unsigned IBS_IO_ok:1;
unsigned IBS_RUN:1;
unsigned MaOff_Keyswitch:1;
unsigned Pushed_ButtonMaOn:1;
unsigned PressureAir_switched_Off:1;				//Luft_wurde_ausgeschaltet
unsigned APCIDatenAusgeben:1;

// Merker f黵 BDE
unsigned _____Variablen_BDE_________________:1;
unsigned Switch_Off_BDE:1;
unsigned ChangeArticle_PC:1;
unsigned Change_WPC:1;								//Nester_wechseln

// Maschinenspezifische Merker
unsigned _____Variablen_Stationsbezogen_____:1;
unsigned _____Station_3_____________________:1;
unsigned St3_B1_01_alternation:1;						//St3_B1_01_Wechsel
unsigned St3_final_position_bridge:1;					//St3_Endstell_ueberbruecken
unsigned St1_conveyor_load:1;							//St3_Rinne_befuellen
unsigned St1_conveyor_unload:1;							//St3_Topf_leerfahren

unsigned _____EPHASE________________________:1;
unsigned All_Stations_without_material :1;


//Station 1
unsigned St1_fill_channel:1;
unsigned St1_feeder_unload:1;

//Station 021

//Station 022
unsigned st022_Separate_Done:1;
unsigned st022_Take_Done:1;
unsigned St022_fill_channel:1;
unsigned St022_feeder_unload:1;

//Station 023

//Station 024
unsigned St024_fill_channel:1;
unsigned St024_feeder_unload:1;

//Station 042
unsigned st042_Separate_Done:1;
unsigned st042_Take_Done:1;
unsigned St042_fill_channel:1;
unsigned St042_feeder_unload:1;

//Station 043

//Station 044
unsigned St044_fill_channel:1;
unsigned St044_feeder_unload:1;





//without material
unsigned St1_without_material:1;
unsigned St021_without_material:1;
unsigned St022_without_material:1;
unsigned St023_without_material:1;
unsigned St024_without_material:1;
unsigned St025_without_material:1;
unsigned St026_without_material:1;
unsigned St027_without_material:1;
unsigned St028_without_material:1;

unsigned St3_without_material:1;
unsigned St5_without_material:1;

unsigned St041_without_material:1;
unsigned St042_without_material:1;
unsigned St043_without_material:1;
unsigned St044_without_material:1;
unsigned St045_without_material:1;
unsigned St046_without_material:1;
unsigned St047_without_material:1;
unsigned St048_without_material:1;

unsigned St001_separate_done:1;
unsigned St001_allow_go:1;
unsigned St201_up_done:1;
unsigned St201_forward_done:1;





//##END_MERKERBIT			Zeile nicht loeschen

//##ANF_MERKERDOUBLE		Zeile nicht loeschen
double double1;
double double2;
double double3;
double double4;
//##END_MERKERDOUBLE		Zeile nicht loeschen

//##ANF_MERKERLONG			Zeile nicht loeschen
LONG LONG1;
LONG LONG2;
LONG LONG3;
//##END_MERKERLONG			Zeile nicht loeschen

};
struct TM_ M_;




//*****************************************************************
//*************  Remanente Merker  ********************************
//*****************************************************************

// Remanente Merker m黶sen f黵 die Anzeige mit der Function
// OnlineVarEintragen("M.Start[6]",1,&M.Start[6]) eingetragen
// werden

struct TM
{
// Allgemeine Merker
bool Marker_ok;
bool PC_SingleStepMode;
bool Impulse_UnloadMaschine;
bool LockUnload;
bool Unload_Machine;
bool Machine_Unloaded;
bool Machine_Unloaded_in_EndPos;
double Sollpositionswert[20];

// Merker f黵 Achse
WORD St201_StepSequence_MainProcess;
bool St201_WPC_eject;
bool St201_Y1_4_SwivelUnit_forward;
bool St201_Y1_2_SwivelUnit_backward;
bool St201_DriveNegativ;

bool St202_Plate_InPos;
bool St203_Plate_InPos;
bool St204_Plate_InPos;

// Stationen ein von BDE
bool StationEin[MAX_MACHINE+1][MAXANZSTAT+1];

long Arbeitstakte;
long Gutpole;
long Ausschusspole;
long Leertakte;
long DurchgeschobenePole;
long Gutteile;
long Ausschussteile;
long BlockAusschuss;

bool Save_RunTime_in_file;

bool St1_Unloaded;

bool St021_01_B1_alternation;
bool St022_01_B1_alternation;
bool St023_01_B1_alternation;
bool St024_01_B1_alternation;
bool St024_01_B2_alternation;
bool St026_01_B1_alternation;
bool St026_01_B2_alternation;

bool St041_01_B1_alternation;
bool St042_01_B1_alternation;
bool St043_01_B1_alternation;
bool St044_01_B1_alternation;
bool St044_01_B2_alternation;
bool St046_01_B1_alternation;
bool St046_01_B2_alternation;

bool ArticleType_MBK2p5;
bool ArticleType_MBK3p0;






//***  Packmodul remanente Variablen  ***
//TVerpack Verpack;					// Einstellvariable
//TVerpack BDEVerpackung;			// Einstellvariable

//Hauptmaschinenspezifische Merker

};
struct TM M;//  remanente Merker z.b. M.Start[1]


//*****************************************************************
//***********  Variablen initialisieren  **************************
//*****************************************************************

#include "varisps.h"

void Init_SPS_Variablen(void)
{
	bool ANZEIGE = false;

	Init_Variablen_Varisps();

	M_.Newstart = true;

	// Einzelschrittstatus von BDE wird abgefragt
	// Der Sicherheitsschl黶sel abgefragt
	// Einzelschrittbetrieb zugewiesen / Tipptaster abgefragt
	#ifdef without_Key
		M_.without_311_Key = true;
	#else
		M_.without_311_Key = false;
	#endif

#ifdef Menue_programm
#pragma message("-------------------------------------------------------------------")
#ifdef VIEW_RUNTIMES
    #pragma message("-----  SPSVAR: LAUFZEITEN DER STATIONEN WERDEN AUSGEGEBEN     -----")
#endif
#ifdef VIEW_MinuteCycle
    #pragma message("-----  SPSVAR: TAKTZAHLEN DER STATIONEN WERDEN AUSGEGEBEN     -----")
#endif
#ifdef VIEW_POSITION_VALUE
    #pragma message("-----  SPSVAR: POLPOSITIONSWERTE WERDEN AUSGEGEBEN            -----")
#endif
#ifdef VIEW_CAMERA_IO
    #pragma message("-----  SPSVAR: E/As DER KAMERAS  WERDEN AUSGEGEBEN            -----")
#endif
#ifdef VIEW_SBTDIAGNOSIS
    #pragma message("-----  SPSVAR: SBT DIAGNOSE VARIABLEN WERDEN AUSGEGEBEN       -----")
#endif
#pragma message("-------------------------------------------------------------------")
#endif // of #ifdef Menue_programm

	/*
							Bytes
	  Typen :	1: bool     1
				2: BYTE		1
				3: int		2
				4: WORD		2
				5: LONG		4
				6: float	4
				7: Double	8
	*/
/*
ACHTUNG: Neue Fenster fuer die Merker

	OnlineVarEintragen()		altes Fenster "Online Eintr鋑e"
	OnlineVarEndstellung()		neues Fenster "Endstellung" dort kann man die Variablen nur lesen nicht 鋘dern!
	OnlineVarLaufzeiten()		neues Fenster "Laufzeiten"
newnddddddlddddineline
	OnlineVarStationEinAus()	neues Fenster "Station Ein/Aus" (kleines Fenster)
newnddddddlddddineline

	Die 躡ergabewerte sind die gleichen wie bei der alten Funktion "OnlineVarEintragen".
	Man kann wie vorher alles in die "Online Eintr鋑e" eintragen. Die weiteren Funktionen
	dienen allein zur 躡ersichtlichkeit.
*/


	char buf[200];

	// Texte f黵 remanente Variablen und sonstigen Variablen
	// die im Fenster Eintr鋑e angezeigt werden sollen

	// Stationen Ein
    // Max. 60 Zeichen      1.......10........20........30........40........50........60
newnddddddlddddineline
newnddddddlddddineline
newnddddddlddddineline
newnddddddlddddineline
newnddddddlddddineline
newnddddddlddddineline
newnddddddlddddineline
newnddddddlddddineline1
newnddddddlddddineline2
    OnlineVarStationEinAus("St022_Y5_2_current_bar_driver_backward",1, &St022_Y5_2_current_bar_driver_backward);
    OnlineVarStationEinAus("St022_Y5_4_current_bar_driver_forward",1, &St022_Y5_4_current_bar_driver_forward);
    OnlineVarStationEinAus("St022_Y4_2_gripper_lifter_downward",1, &St022_Y4_2_gripper_lifter_downward);
    OnlineVarStationEinAus("St022_Y3_2_current_bar_gripper_open",1, &St022_Y3_2_current_bar_gripper_open);
    OnlineVarStationEinAus("St022_Y3_4_current_bar_gripper_close",1, &St022_Y3_4_current_bar_gripper_close);
    OnlineVarStationEinAus("St022_Y2_2_current_bar_rotating_send",1, &St022_Y2_2_current_bar_rotating_send);
    OnlineVarStationEinAus("St022_Y2_4_current_bar_rotating_take",1, &St022_Y2_4_current_bar_rotating_take);
    OnlineVarStationEinAus("St022_Y1_2_current_bar_inserter_backward",1, &St022_Y1_2_current_bar_inserter_backward);
    OnlineVarStationEinAus("St022_Y1_4_current_bar_inserter_forward",1, &St022_Y1_4_current_bar_inserter_forward);
    OnlineVarStationEinAus("St022_Y5_2_current_bar_driver_backward",1, &St022_Y5_2_current_bar_driver_backward);
    OnlineVarStationEinAus("St022_Y5_4_current_bar_driver_forward",1, &St022_Y5_4_current_bar_driver_forward);
    OnlineVarStationEinAus("St022_Y4_2_gripper_lifter_downward",1, &St022_Y4_2_gripper_lifter_downward);
    OnlineVarStationEinAus("St022_Y4_4_gripper_lifter_upward",1, &St022_Y4_4_gripper_lifter_upward);
    OnlineVarStationEinAus("St022_Y3_2_current_bar_gripper_open",1, &St022_Y3_2_current_bar_gripper_open);
    OnlineVarStationEinAus("St022_Y3_4_current_bar_gripper_close",1, &St022_Y3_4_current_bar_gripper_close);
    OnlineVarStationEinAus("St022_Y2_2_current_bar_rotating_send",1, &St022_Y2_2_current_bar_rotating_send);
    OnlineVarStationEinAus("St022_Y2_4_current_bar_rotating_take",1, &St022_Y2_4_current_bar_rotating_take);
    OnlineVarStationEinAus("St022_Y1_2_current_bar_inserter_backward",1, &St022_Y1_2_current_bar_inserter_backward);
    OnlineVarStationEinAus("St022_Y1_4_current_bar_inserter_forward",1, &St022_Y1_4_current_bar_inserter_forward);
    OnlineVarStationEinAus("St044_Y1_4_clamping_sleeve_presser_forward",1, &St044_Y1_4_clamping_sleeve_presser_forward);
    OnlineVarStationEinAus("St044_Y1_4_clamping_sleeve_presser_forward",1, &St044_Y1_4_clamping_sleeve_presser_forward);
    OnlineVarStationEinAus("St044_Y1_4_clamping_sleeve_presser_forward",1, &St044_Y1_4_clamping_sleeve_presser_forward);
    OnlineVarStationEinAus("St044_Y1_4_clamping_sleeve_presser_forward",1, &St044_Y1_4_clamping_sleeve_presser_forward);
    OnlineVarStationEinAus("St044_Y1_4_clamping_sleeve_presser_forward",1, &St044_Y1_4_clamping_sleeve_presser_forward);
    OnlineVarStationEinAus("St044_Y1_4_clamping_sleeve_presser_forward",1, &St044_Y1_4_clamping_sleeve_presser_forward);
    OnlineVarStationEinAus("St044_Y1_4_clamping_sleeve_presser_forward",1, &St044_Y1_4_clamping_sleeve_presser_forward);
	OnlineVarStationEinAus("Station  1 On									",1,&M.StationEin[MaPart1][1]);
	OnlineVarStationEinAus("Station  3 On									",1,&M.StationEin[MaPart1][3]);
	OnlineVarStationEinAus("Station  5 On									",1,&M.StationEin[MaPart1][5]);
	OnlineVarStationEinAus("Station  21 On									",1,&M.StationEin[MaPart1][11]);
	OnlineVarStationEinAus("Station  22 On									",1,&M.StationEin[MaPart1][12]);
	OnlineVarStationEinAus("Station  23 On									",1,&M.StationEin[MaPart1][13]);
	OnlineVarStationEinAus("Station  24 On									",1,&M.StationEin[MaPart1][14]);
	OnlineVarStationEinAus("Station  25 On									",1,&M.StationEin[MaPart1][15]);
	OnlineVarStationEinAus("Station  26 On									",1,&M.StationEin[MaPart1][16]);
	OnlineVarStationEinAus("Station  27 On									",1,&M.StationEin[MaPart1][17]);
	OnlineVarStationEinAus("Station  28 On									",1,&M.StationEin[MaPart1][18]);
	OnlineVarStationEinAus("Station  41 On									",1,&M.StationEin[MaPart1][21]);
	OnlineVarStationEinAus("Station  42 On									",1,&M.StationEin[MaPart1][22]);
	OnlineVarStationEinAus("Station  43 On									",1,&M.StationEin[MaPart1][23]);
	OnlineVarStationEinAus("Station  44 On									",1,&M.StationEin[MaPart1][24]);
	OnlineVarStationEinAus("Station  45 On									",1,&M.StationEin[MaPart1][25]);
	OnlineVarStationEinAus("Station  46 On									",1,&M.StationEin[MaPart1][26]);
	OnlineVarStationEinAus("Station  47 On									",1,&M.StationEin[MaPart1][27]);
	OnlineVarStationEinAus("Station  48 On									",1,&M.StationEin[MaPart1][28]);

	// DriveUnit 1
    OnlineVarEintragen("M.ArticleType_MBK2p5",1, &M.ArticleType_MBK2p5);
    OnlineVarEintragen("M.ArticleType_MBK2p5",1, &M.ArticleType_MBK2p5);
    OnlineVarEintragen("Sollpositionswert[20]",8, &Sollpositionswert[20]);
    OnlineVarEintragen("St1_Y1_4_housing_stopper_downward",1, &St1_Y1_4_housing_stopper_downward);
	OnlineVarEintragen("----- DriveUnit 1 - AXIS 1 - STATION 201 -------------",1,&ANZEIGE);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 1]							",1,&DriveUnit[DriveUnit1].Start[K_St001_Housing_Separating]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 2]							",1,&DriveUnit[DriveUnit1].Start[2]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 3]							",1,&DriveUnit[DriveUnit1].Start[K_St003_Housing_Press1]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 4]							",1,&DriveUnit[DriveUnit1].Start[4]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 5]							",1,&DriveUnit[DriveUnit1].Start[K_St005_Housing_Press2]);

	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("DriveUnit 1 - Station_StandBy[St. 1]				",1,&DriveUnit[DriveUnit1].Station_StandBy[K_St001_Housing_Separating]);
	OnlineVarEintragen("DriveUnit 1 - Station_StandBy[St. 2]				",1,&DriveUnit[DriveUnit1].Station_StandBy[2]);
	OnlineVarEintragen("DriveUnit 1 - Station_StandBy[St. 3]				",1,&DriveUnit[DriveUnit1].Station_StandBy[K_St003_Housing_Press1]);
	OnlineVarEintragen("DriveUnit 1 - Station_StandBy[St. 4]				",1,&DriveUnit[DriveUnit1].Station_StandBy[4]);
	OnlineVarEintragen("DriveUnit 1 - Station_StandBy[St. 5]				",1,&DriveUnit[DriveUnit1].Station_StandBy[K_St005_Housing_Press2]);

	OnlineVarEintragen("DriveUnit 1 - StandBy								",1,&DriveUnit[DriveUnit1].StandBy);
	OnlineVarEintragen("DriveUnit 1 - found_StandBy							",1,&DriveUnit[DriveUnit1].found_StandBy);
	OnlineVarEintragen("DriveUnit 1 - DU_ready_for_StandBy					",1,&DriveUnit[DriveUnit1].DU_ready_for_StandBy);

	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("DriveUnit 1 - ControlTime reset						",1,&DriveUnit[DriveUnit1].reset_ControlTime);
	OnlineVarEintragen("DriveUnit 1 - DriveUnit_in_EndPosition				",1,&DriveUnit[DriveUnit1].DriveUnit_in_EndPosition);
	OnlineVarEintragen("DriveUnit 1 - EndPosition_Cylinder					",1,&DriveUnit[DriveUnit1].EndPosition_Cylinder);
	OnlineVarEintragen("DriveUnit 1 - EndPosition_Cylinder_Error			",1,&DriveUnit[DriveUnit1].EndPosition_Cylinder_Error);
	OnlineVarEintragen("DriveUnit 1 - EndPosition_Sequences					",1,&DriveUnit[DriveUnit1].EndPosition_Sequences);
	OnlineVarEintragen("DriveUnit 1 - Enable_DriveUnit						",1,&DriveUnit[DriveUnit1].Enable_DriveUnit);
	OnlineVarEintragen("DriveUnit 1 - InPosition							",1,&DriveUnit[DriveUnit1].InPosition);
	OnlineVarEintragen("DriveUnit 1 - Error_DriveUnit						",1,&DriveUnit[DriveUnit1].Error_DriveUnit);
	OnlineVarEintragen("DriveUnit 1 - Station_TestMode						",1,&DriveUnit[DriveUnit1].Station_TestMode);

	OnlineVarEintragen("DriveUnit 1 - Unload								",1,&DriveUnit[DriveUnit1].Unload);
	OnlineVarEintragen("DriveUnit 1 - Unloaded								",1,&DriveUnit[DriveUnit1].Unloaded);

	OnlineVarEintragen("DriveUnit 1 - BlockCounter							",4,&DriveUnit[DriveUnit1].BlockCounter);
	OnlineVarEintragen("DriveUnit 1 - PoleCounter							",4,&DriveUnit[DriveUnit1].PoleCounter);
	OnlineVarEintragen("DriveUnit 1 - NumberOfHousings						",4,&DriveUnit[DriveUnit1].NumberOfHousings);
	OnlineVarEintragen("DriveUnit 1 - Station Reset							",1,&DriveUnit[DriveUnit1].Station_Reset);
	OnlineVarEintragen("DriveUnit 1 - ErrorMachineOff						",1,&DriveUnit[DriveUnit1].ErrorMachineOff);

	// DriveUnit 2
	OnlineVarEintragen("----- DriveUnit 2  - STATION 202 -------------",1,&ANZEIGE);

	OnlineVarEintragen("DriveUnit 2 - Start[St. 21]							",1,&DriveUnit[DriveUnit2].Start[K_St021_Check_Carrier_Empty]);
	OnlineVarEintragen("DriveUnit 2 - Start[St. 22]							",1,&DriveUnit[DriveUnit2].Start[K_St022_Current_Bar_Feeding_A]);
	OnlineVarEintragen("DriveUnit 2 - Start[St. 23]							",1,&DriveUnit[DriveUnit2].Start[K_St023_Check_Press_Current_Bar]);
	OnlineVarEintragen("DriveUnit 2 - Start[St. 24]							",1,&DriveUnit[DriveUnit2].Start[K_St024_Clamping_Sleeve_Feeding]);
	OnlineVarEintragen("DriveUnit 2 - Start[St. 25]							",1,&DriveUnit[DriveUnit2].Start[K_St025_Metal_Parts_Assembly]);
	OnlineVarEintragen("DriveUnit 2 - Start[St. 26]							",1,&DriveUnit[DriveUnit2].Start[K_St026_Clamping_Sleeve_Checking]);
	OnlineVarEintragen("DriveUnit 2 - Start[St. 27]							",1,&DriveUnit[DriveUnit2].Start[K_St027_Reject_Parts_Eject]);
	OnlineVarEintragen("DriveUnit 2 - Start[St. 28]							",1,&DriveUnit[DriveUnit2].Start[K_St028_Pre_Assembled_Parts_Eject]);


	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("DriveUnit 2 - Station_StandBy[St. 21]				",1,&DriveUnit[DriveUnit2].Station_StandBy[K_St021_Check_Carrier_Empty]);
	OnlineVarEintragen("DriveUnit 2 - Station_StandBy[St. 22]				",1,&DriveUnit[DriveUnit2].Station_StandBy[K_St022_Current_Bar_Feeding_A]);
	OnlineVarEintragen("DriveUnit 2 - Station_StandBy[St. 23]				",1,&DriveUnit[DriveUnit2].Station_StandBy[K_St023_Check_Press_Current_Bar]);
	OnlineVarEintragen("DriveUnit 2 - Station_StandBy[St. 24]				",1,&DriveUnit[DriveUnit2].Station_StandBy[K_St024_Clamping_Sleeve_Feeding]);
	OnlineVarEintragen("DriveUnit 2 - Station_StandBy[St. 25]				",1,&DriveUnit[DriveUnit2].Station_StandBy[K_St025_Metal_Parts_Assembly]);
	OnlineVarEintragen("DriveUnit 2 - Station_StandBy[St. 26]				",1,&DriveUnit[DriveUnit2].Station_StandBy[K_St026_Clamping_Sleeve_Checking]);
	OnlineVarEintragen("DriveUnit 2 - Station_StandBy[St. 27]				",1,&DriveUnit[DriveUnit2].Station_StandBy[K_St027_Reject_Parts_Eject]);
	OnlineVarEintragen("DriveUnit 2 - Station_StandBy[St. 28]				",1,&DriveUnit[DriveUnit2].Station_StandBy[K_St028_Pre_Assembled_Parts_Eject]);

	OnlineVarEintragen("DriveUnit 2 - StandBy								",1,&DriveUnit[DriveUnit2].StandBy);
	OnlineVarEintragen("DriveUnit 2 - found_StandBy							",1,&DriveUnit[DriveUnit2].found_StandBy);
	OnlineVarEintragen("DriveUnit 2 - DU_ready_for_StandBy					",1,&DriveUnit[DriveUnit2].DU_ready_for_StandBy);

	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("DriveUnit 2 - ControlTime reset						",1,&DriveUnit[DriveUnit2].reset_ControlTime);
	OnlineVarEintragen("DriveUnit 2 - DriveUnit_in_EndPosition				",1,&DriveUnit[DriveUnit2].DriveUnit_in_EndPosition);
	OnlineVarEintragen("DriveUnit 2 - EndPosition_Cylinder					",1,&DriveUnit[DriveUnit2].EndPosition_Cylinder);
	OnlineVarEintragen("DriveUnit 2 - EndPosition_Cylinder_Error			",1,&DriveUnit[DriveUnit2].EndPosition_Cylinder_Error);
	OnlineVarEintragen("DriveUnit 2 - EndPosition_Sequences					",1,&DriveUnit[DriveUnit2].EndPosition_Sequences);
	OnlineVarEintragen("DriveUnit 2 - Enable_DriveUnit						",1,&DriveUnit[DriveUnit2].Enable_DriveUnit);
	OnlineVarEintragen("DriveUnit 2 - InPosition							",1,&DriveUnit[DriveUnit2].InPosition);
	OnlineVarEintragen("DriveUnit 2 - Error_DriveUnit						",1,&DriveUnit[DriveUnit2].Error_DriveUnit);
	OnlineVarEintragen("DriveUnit 2 - Station_TestMode						",1,&DriveUnit[DriveUnit2].Station_TestMode);

	OnlineVarEintragen("DriveUnit 2 - Unload								",1,&DriveUnit[DriveUnit2].Unload);
	OnlineVarEintragen("DriveUnit 2 - Unloaded								",1,&DriveUnit[DriveUnit2].Unloaded);

	OnlineVarEintragen("DriveUnit 2 - BlockCounter							",4,&DriveUnit[DriveUnit2].BlockCounter);
	OnlineVarEintragen("DriveUnit 2 - PoleCounter							",4,&DriveUnit[DriveUnit2].PoleCounter);
	OnlineVarEintragen("DriveUnit 2 - NumberOfHousings						",4,&DriveUnit[DriveUnit2].NumberOfHousings);
	OnlineVarEintragen("DriveUnit 2 - Station Reset							",1,&DriveUnit[DriveUnit2].Station_Reset);
	OnlineVarEintragen("DriveUnit 2 - ErrorMachineOff						",1,&DriveUnit[DriveUnit2].ErrorMachineOff);

	// DriveUnit 3
	OnlineVarEintragen("----- DriveUnit 3  - STATION 203 -------------",1,&ANZEIGE);

	OnlineVarEintragen("DriveUnit 3 - Start[St. 41]							",1,&DriveUnit[DriveUnit3].Start[K_St041_Check_Carrier_Empty]);
	OnlineVarEintragen("DriveUnit 3 - Start[St. 42]							",1,&DriveUnit[DriveUnit3].Start[K_St042_Current_Bar_Feeding_A]);
	OnlineVarEintragen("DriveUnit 3 - Start[St. 43]							",1,&DriveUnit[DriveUnit3].Start[K_St043_Check_Press_Current_Bar]);
	OnlineVarEintragen("DriveUnit 3 - Start[St. 44]							",1,&DriveUnit[DriveUnit3].Start[K_St044_Clamping_Sleeve_Feeding]);
	OnlineVarEintragen("DriveUnit 3 - Start[St. 45]							",1,&DriveUnit[DriveUnit3].Start[K_St045_Metal_Parts_Assembly]);
	OnlineVarEintragen("DriveUnit 3 - Start[St. 46]							",1,&DriveUnit[DriveUnit3].Start[K_St046_Clamping_Sleeve_Checking]);
	OnlineVarEintragen("DriveUnit 3 - Start[St. 47]							",1,&DriveUnit[DriveUnit3].Start[K_St047_Reject_Parts_Eject]);
	OnlineVarEintragen("DriveUnit 3 - Start[St. 48]							",1,&DriveUnit[DriveUnit3].Start[K_St048_Pre_Assembled_Parts_Eject]);


	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("DriveUnit 3 - Station_StandBy[St. 41]				",1,&DriveUnit[DriveUnit3].Station_StandBy[K_St041_Check_Carrier_Empty]);
	OnlineVarEintragen("DriveUnit 3 - Station_StandBy[St. 42]				",1,&DriveUnit[DriveUnit3].Station_StandBy[K_St042_Current_Bar_Feeding_A]);
	OnlineVarEintragen("DriveUnit 3 - Station_StandBy[St. 43]				",1,&DriveUnit[DriveUnit3].Station_StandBy[K_St043_Check_Press_Current_Bar]);
	OnlineVarEintragen("DriveUnit 3 - Station_StandBy[St. 44]				",1,&DriveUnit[DriveUnit3].Station_StandBy[K_St044_Clamping_Sleeve_Feeding]);
	OnlineVarEintragen("DriveUnit 3 - Station_StandBy[St. 45]				",1,&DriveUnit[DriveUnit3].Station_StandBy[K_St045_Metal_Parts_Assembly]);
	OnlineVarEintragen("DriveUnit 3 - Station_StandBy[St. 46]				",1,&DriveUnit[DriveUnit3].Station_StandBy[K_St046_Clamping_Sleeve_Checking]);
	OnlineVarEintragen("DriveUnit 3 - Station_StandBy[St. 47]				",1,&DriveUnit[DriveUnit3].Station_StandBy[K_St047_Reject_Parts_Eject]);
	OnlineVarEintragen("DriveUnit 3 - Station_StandBy[St. 48]				",1,&DriveUnit[DriveUnit3].Station_StandBy[K_St048_Pre_Assembled_Parts_Eject]);

	OnlineVarEintragen("DriveUnit 3 - StandBy								",1,&DriveUnit[DriveUnit3].StandBy);
	OnlineVarEintragen("DriveUnit 3 - found_StandBy							",1,&DriveUnit[DriveUnit3].found_StandBy);
	OnlineVarEintragen("DriveUnit 3 - DU_ready_for_StandBy					",1,&DriveUnit[DriveUnit3].DU_ready_for_StandBy);

	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("DriveUnit 3 - ControlTime reset						",1,&DriveUnit[DriveUnit3].reset_ControlTime);
	OnlineVarEintragen("DriveUnit 3 - DriveUnit_in_EndPosition				",1,&DriveUnit[DriveUnit3].DriveUnit_in_EndPosition);
	OnlineVarEintragen("DriveUnit 3 - EndPosition_Cylinder					",1,&DriveUnit[DriveUnit3].EndPosition_Cylinder);
	OnlineVarEintragen("DriveUnit 3 - EndPosition_Cylinder_Error			",1,&DriveUnit[DriveUnit3].EndPosition_Cylinder_Error);
	OnlineVarEintragen("DriveUnit 3 - EndPosition_Sequences					",1,&DriveUnit[DriveUnit3].EndPosition_Sequences);
	OnlineVarEintragen("DriveUnit 3 - Enable_DriveUnit						",1,&DriveUnit[DriveUnit3].Enable_DriveUnit);
	OnlineVarEintragen("DriveUnit 3 - InPosition							",1,&DriveUnit[DriveUnit3].InPosition);
	OnlineVarEintragen("DriveUnit 3 - Error_DriveUnit						",1,&DriveUnit[DriveUnit3].Error_DriveUnit);
	OnlineVarEintragen("DriveUnit 3 - Station_TestMode						",1,&DriveUnit[DriveUnit3].Station_TestMode);

	OnlineVarEintragen("DriveUnit 3 - Unload								",1,&DriveUnit[DriveUnit3].Unload);
	OnlineVarEintragen("DriveUnit 3 - Unloaded								",1,&DriveUnit[DriveUnit3].Unloaded);

	OnlineVarEintragen("DriveUnit 3 - BlockCounter							",4,&DriveUnit[DriveUnit3].BlockCounter);
	OnlineVarEintragen("DriveUnit 3 - PoleCounter							",4,&DriveUnit[DriveUnit3].PoleCounter);
	OnlineVarEintragen("DriveUnit 3 - NumberOfHousings						",4,&DriveUnit[DriveUnit3].NumberOfHousings);
	OnlineVarEintragen("DriveUnit 3 - Station Reset							",1,&DriveUnit[DriveUnit3].Station_Reset);
	OnlineVarEintragen("DriveUnit 3 - ErrorMachineOff						",1,&DriveUnit[DriveUnit3].ErrorMachineOff);



#ifdef Axis_exist
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("----- VARIABLEN STATION 201 AXIS 1 -------------------",1,&ANZEIGE);
	OnlineVarEintragen("M.St201_StepSequence_MainProcess					",4,&M.St201_StepSequence_MainProcess);
	OnlineVarEintragen("M.St201_Y1_4_SwivelUnit_forward						",1,&M.St201_Y1_4_SwivelUnit_forward);
	OnlineVarEintragen("M.St201_Y1_2_SwivelUnit_backward					",1,&M.St201_Y1_2_SwivelUnit_backward);

	OnlineVarEintragen("Axis 1 - M_IFC_Servo								",1,&Achse[Axis1].M_IFC_Servo);
	OnlineVarEintragen("Axis 1 - M_Reset_Servo								",1,&Achse[Axis1].M_Reset_Servo);
	OnlineVarEintragen("Axis 1 - M_Alarm_Servo								",1,&Achse[Axis1].M_Alarm_Servo);
	OnlineVarEintragen("Axis 1 - M_Pos_StopPosition							",1,&Achse[Axis1].M_Pos_StopPosition);
	OnlineVarEintragen("Axis 1 - M_Neg_StopPosition							",1,&Achse[Axis1].M_Neg_StopPosition);
	OnlineVarEintragen("Axis 1 - M_CollectiveError_Servo					",1,&Achse[Axis1].M_CollectiveError_Servo);
	OnlineVarEintragen("Axis 1 - M_Strom_Servo								",1,&Achse[Axis1].M_Strom_Servo);

	OnlineVarEintragen("Axis 1 - ReferenzPoint_OK							",1,&Achse[Axis1].ReferenzPoint_OK);
	OnlineVarEintragen("Axis 1 - M_ReferenzDrive_Finished					",1,&Achse[Axis1].M_ReferenzDrive_Finished);
	OnlineVarEintragen("Axis 1 - M_ReferenzDrive_Error						",1,&Achse[Axis1].M_ReferenzDrive_Error);
	OnlineVarEintragen("Axis 1 - M_ReferenzDrive_Start						",1,&Achse[Axis1].M_ReferenzDrive_Start);
	OnlineVarEintragen("Axis 1 - M_Error_ServoMotor_Rotates					",1,&Achse[Axis1].M_Error_ServoMotor_Rotates);
	OnlineVarEintragen("Axis 1 - M_ReferenzDrive_Swing_Positiv				",1,&Achse[Axis1].M_ReferenzDrive_Swing_Positiv);
	OnlineVarEintragen("Axis 1 - M_ReferenzDrive_Swing_Negativ				",1,&Achse[Axis1].M_ReferenzDrive_Swing_Negativ);
	OnlineVarEintragen("Axis 1 - Negativ_drive								",1,&Achse[Axis1].Negativ_drive);
	OnlineVarEintragen("Axis 1 - WPC_End									",1,&Achse[Axis1].WPC_End);
	OnlineVarEintragen("Axis 1 - Housing_End								",1,&Achse[Axis1].Housing_End);
	OnlineVarEintragen("Axis 1 - MW_Sollposition							",7,&Achse[Axis1].MW_Sollposition);
#endif

#ifdef Plate_exist
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("----- VARIABLEN STATION 201 Servo PLATE 1 ------------",1,&ANZEIGE);
	OnlineVarEintragen("Plate 1 - M_Alarm_Servo								",1,&Teller[Plate1].M_Alarm_Servo);
	OnlineVarEintragen("Plate 1 - M_EndPosition_Cylinder					",1,&Teller[Plate1].M_EndPosition_Cylinder);
	OnlineVarEintragen("Plate 1 - M_Flag_Unit_Start							",1,&Teller[Plate1].M_Flag_Unit_Start);
	OnlineVarEintragen("Plate 1 - M_IFC_Servo								",1,&Teller[Plate1].M_IFC_Servo);
	OnlineVarEintragen("Plate 1 - M_InPosition								",1,&Teller[Plate1].M_InPosition);
	OnlineVarEintragen("Plate 1 - M_EmergencyStop_Plate						",1,&Teller[Plate1].M_EmergencyStop_Plate);
	OnlineVarEintragen("Plate 1 - M_Reset_Servo								",1,&Teller[Plate1].M_Reset_Servo);
	OnlineVarEintragen("Plate 1 - M_CollectiveError_Servo					",1,&Teller[Plate1].M_CollectiveError_Servo);
	OnlineVarEintragen("Plate 1 - M_Error_ServoMotor_Rotates				",1,&Teller[Plate1].M_Error_ServoMotor_Rotates);
	OnlineVarEintragen("Plate 1 - M_Strom_Servo								",1,&Teller[Plate1].M_Strom_Servo);
#endif

#ifdef Plate_FU_exist
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("----- VARIABLEN STATION 203 FU TELLER 1 --------------",1,&ANZEIGE);
	OnlineVarEintragen("Plate 1 - M_InPosition								",1,&Teller[Plate1].M_InPosition);
	OnlineVarEintragen("Plate 1 - M_Flag_Unit_Start							",1,&Teller[Plate1].M_Flag_Unit_Start);
	OnlineVarEintragen("Plate 1 - M_EmergencyStop_Plate						",1,&Teller[Plate1].M_EmergencyStop_Plate);
	OnlineVarEintragen("Plate 1 - M_EndPosition_Cylinder					",1,&Teller[Plate1].M_EndPosition_Cylinder);
	OnlineVarEintragen("Plate 1 - M_Turn_Off								",1,&Teller[Plate1].M_Turn_Off);
	OnlineVarEintragen("Plate 1 - M_Error_Motor_Ready						",1,&Teller[Plate1].M_Error_Motor_Ready);
#endif


#ifdef Plate_Siemens_FU_exist
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("----- VARIABLEN STATION 204 FU TELLER 1 --------------",1,&ANZEIGE);
	OnlineVarEintragen("Plate1 1 - M_InPosition								",1,&Teller[Plate1].M_InPosition);
	OnlineVarEintragen("Plate1 1 - M_EmergencyStop_Plate					",1,&Teller[Plate1].M_EmergencyStop_Plate);
#endif
	// Maschinenspezifische Merker
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("----- ALLGEMEINE VARIABLEN ---------------------------",1,&ANZEIGE);
	OnlineVarEintragen("Marker_ok											",1,&M.Marker_ok);
	OnlineVarEintragen("PC_NewData											",1,&PC_NewData);
	OnlineVarEintragen("M.PC_SingleStepMode									",1,&M.PC_SingleStepMode);

	OnlineVarEintragen("M.Impulse_UnloadMaschine							",1,&M.Impulse_UnloadMaschine);
	OnlineVarEintragen("M.LockUnload										",1,&M.LockUnload);
	OnlineVarEintragen("M.Unload_Machine									",1,&M.Unload_Machine);
	OnlineVarEintragen("M.Machine_Unloaded									",1,&M.Machine_Unloaded);
	OnlineVarEintragen("M.Machine_Unloaded_in_EndPos						",1,&M.Machine_Unloaded_in_EndPos);
	bool LockUnload;

	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("----- STATIONS ---------------------------------------",1,&ANZEIGE);
	OnlineVarEintragen("M.ArticleType_MBK2p5					         ",1,&M.ArticleType_MBK2p5);
	OnlineVarEintragen("M.ArticleType_MBK3p0				             ",1,&M.ArticleType_MBK3p0);
	OnlineVarEintragen("M.Unload_Machine							     ",1,&M.Unload_Machine);
	OnlineVarEintragen("M.Machine_Unloaded				                 ",1,&M.Machine_Unloaded);
	OnlineVarEintragen("M.Machine_Unloaded_in_EndPos				     ",1,&M.Machine_Unloaded_in_EndPos);
	OnlineVarEintragen("----- STATION 1 --------------------------------------",1,&ANZEIGE);
	OnlineVarEintragen("----- STATION 2 --------------------------------------",1,&ANZEIGE);
	OnlineVarEintragen("----- STATION 3 --------------------------------------",1,&ANZEIGE);


	OnlineVarEndstellung("----- DriveUnit 1 - AXIS 1 - STATION 201 -----------",1,&ANZEIGE);
	OnlineVarEndstellung("DriveUnit 1 - E_EndPosition [St. 1]				",1,&DriveUnit[DriveUnit1].E_EndPosition [K_St001_Housing_Separating]);
	OnlineVarEndstellung("DriveUnit 1 - SK_EndPosition[St. 1]				",1,&DriveUnit[DriveUnit1].SK_EndPosition[K_St001_Housing_Separating]);
	OnlineVarEndstellung("DriveUnit 1 - E_EndPosition [St. 3]				",1,&DriveUnit[DriveUnit1].E_EndPosition [K_St003_Housing_Press1]);
	OnlineVarEndstellung("DriveUnit 1 - SK_EndPosition[St. 3]				",1,&DriveUnit[DriveUnit1].SK_EndPosition[K_St003_Housing_Press1]);
	OnlineVarEndstellung("DriveUnit 1 - E_EndPosition [St. 5]				",1,&DriveUnit[DriveUnit1].E_EndPosition [K_St005_Housing_Press2]);
	OnlineVarEndstellung("DriveUnit 1 - SK_EndPosition[St. 5]				",1,&DriveUnit[DriveUnit1].SK_EndPosition[K_St005_Housing_Press2]);
    OnlineVarEndstellung("----- DriveUnit 2 - Teller 1 - STATION 202 -----------",1,&ANZEIGE);
	OnlineVarEndstellung("DriveUnit 2 - E_EndPosition [St. 21]				",1,&DriveUnit[DriveUnit2].E_EndPosition [K_St021_Check_Carrier_Empty]);
	OnlineVarEndstellung("DriveUnit 2 - SK_EndPosition[St. 21]				",1,&DriveUnit[DriveUnit2].SK_EndPosition[K_St021_Check_Carrier_Empty]);
	OnlineVarEndstellung("DriveUnit 2 - E_EndPosition [St. 22]				",1,&DriveUnit[DriveUnit2].E_EndPosition [K_St022_Current_Bar_Feeding_A]);
	OnlineVarEndstellung("DriveUnit 2 - SK_EndPosition[St. 22]				",1,&DriveUnit[DriveUnit2].SK_EndPosition[K_St022_Current_Bar_Feeding_A]);
	OnlineVarEndstellung("DriveUnit 2 - E_EndPosition [St. 23]				",1,&DriveUnit[DriveUnit2].E_EndPosition [K_St023_Check_Press_Current_Bar]);
	OnlineVarEndstellung("DriveUnit 2 - SK_EndPosition[St. 23]				",1,&DriveUnit[DriveUnit2].SK_EndPosition[K_St023_Check_Press_Current_Bar]);
	OnlineVarEndstellung("DriveUnit 2 - E_EndPosition [St. 24]				",1,&DriveUnit[DriveUnit2].E_EndPosition [K_St024_Clamping_Sleeve_Feeding]);
	OnlineVarEndstellung("DriveUnit 2 - SK_EndPosition[St. 24]				",1,&DriveUnit[DriveUnit2].SK_EndPosition[K_St024_Clamping_Sleeve_Feeding]);
	OnlineVarEndstellung("DriveUnit 2 - E_EndPosition [St. 25]				",1,&DriveUnit[DriveUnit2].E_EndPosition [K_St025_Metal_Parts_Assembly]);
	OnlineVarEndstellung("DriveUnit 2 - SK_EndPosition[St. 25]				",1,&DriveUnit[DriveUnit2].SK_EndPosition[K_St025_Metal_Parts_Assembly]);
	OnlineVarEndstellung("DriveUnit 2 - E_EndPosition [St. 26]				",1,&DriveUnit[DriveUnit2].E_EndPosition [K_St026_Clamping_Sleeve_Checking]);
	OnlineVarEndstellung("DriveUnit 2 - SK_EndPosition[St. 26]				",1,&DriveUnit[DriveUnit2].SK_EndPosition[K_St026_Clamping_Sleeve_Checking]);
	OnlineVarEndstellung("DriveUnit 2 - E_EndPosition [St. 27]				",1,&DriveUnit[DriveUnit2].E_EndPosition [K_St027_Reject_Parts_Eject]);
	OnlineVarEndstellung("DriveUnit 2 - SK_EndPosition[St. 27]				",1,&DriveUnit[DriveUnit2].SK_EndPosition[K_St027_Reject_Parts_Eject]);
	OnlineVarEndstellung("DriveUnit 2 - E_EndPosition [St. 28]				",1,&DriveUnit[DriveUnit2].E_EndPosition [K_St028_Pre_Assembled_Parts_Eject]);
	OnlineVarEndstellung("DriveUnit 2 - SK_EndPosition[St. 28]				",1,&DriveUnit[DriveUnit2].SK_EndPosition[K_St028_Pre_Assembled_Parts_Eject]);

    OnlineVarEndstellung("----- DriveUnit 2 - Teller 1 - STATION 203 -----------",1,&ANZEIGE);
	OnlineVarEndstellung("DriveUnit 3 - E_EndPosition [St. 41]				",1,&DriveUnit[DriveUnit3].E_EndPosition [K_St041_Check_Carrier_Empty]);
	OnlineVarEndstellung("DriveUnit 3 - SK_EndPosition[St. 41]				",1,&DriveUnit[DriveUnit3].SK_EndPosition[K_St041_Check_Carrier_Empty]);
	OnlineVarEndstellung("DriveUnit 3 - E_EndPosition [St. 42]				",1,&DriveUnit[DriveUnit3].E_EndPosition [K_St042_Current_Bar_Feeding_A]);
	OnlineVarEndstellung("DriveUnit 3 - SK_EndPosition[St. 42]				",1,&DriveUnit[DriveUnit3].SK_EndPosition[K_St042_Current_Bar_Feeding_A]);
	OnlineVarEndstellung("DriveUnit 3 - E_EndPosition [St. 43]				",1,&DriveUnit[DriveUnit3].E_EndPosition [K_St043_Check_Press_Current_Bar]);
	OnlineVarEndstellung("DriveUnit 3 - SK_EndPosition[St. 43]				",1,&DriveUnit[DriveUnit3].SK_EndPosition[K_St043_Check_Press_Current_Bar]);
	OnlineVarEndstellung("DriveUnit 3 - E_EndPosition [St. 44]				",1,&DriveUnit[DriveUnit3].E_EndPosition [K_St044_Clamping_Sleeve_Feeding]);
	OnlineVarEndstellung("DriveUnit 3 - SK_EndPosition[St. 44]				",1,&DriveUnit[DriveUnit3].SK_EndPosition[K_St044_Clamping_Sleeve_Feeding]);
	OnlineVarEndstellung("DriveUnit 3 - E_EndPosition [St. 45]				",1,&DriveUnit[DriveUnit3].E_EndPosition [K_St045_Metal_Parts_Assembly]);
	OnlineVarEndstellung("DriveUnit 3 - SK_EndPosition[St. 45]				",1,&DriveUnit[DriveUnit3].SK_EndPosition[K_St045_Metal_Parts_Assembly]);
	OnlineVarEndstellung("DriveUnit 3 - E_EndPosition [St. 46]				",1,&DriveUnit[DriveUnit3].E_EndPosition [K_St046_Clamping_Sleeve_Checking]);
	OnlineVarEndstellung("DriveUnit 3 - SK_EndPosition[St. 46]				",1,&DriveUnit[DriveUnit3].SK_EndPosition[K_St046_Clamping_Sleeve_Checking]);
	OnlineVarEndstellung("DriveUnit 3 - E_EndPosition [St. 47]				",1,&DriveUnit[DriveUnit3].E_EndPosition [K_St047_Reject_Parts_Eject]);
	OnlineVarEndstellung("DriveUnit 3 - SK_EndPosition[St. 47]				",1,&DriveUnit[DriveUnit3].SK_EndPosition[K_St047_Reject_Parts_Eject]);
	OnlineVarEndstellung("DriveUnit 3 - E_EndPosition [St. 48]				",1,&DriveUnit[DriveUnit3].E_EndPosition [K_St048_Pre_Assembled_Parts_Eject]);
	OnlineVarEndstellung("DriveUnit 3 - SK_EndPosition[St. 48]				",1,&DriveUnit[DriveUnit3].SK_EndPosition[K_St048_Pre_Assembled_Parts_Eject]);

	OnlineVarEndstellung("----- ENDSTELLUNGEN MASCHINE -----------------------",1,&ANZEIGE);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 1]						",1,&E_EndPosition_Machine	[K_St001_Housing_Separating]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 2]						",1,&E_EndPosition_Machine	[2]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 3]						",1,&E_EndPosition_Machine	[K_St003_Housing_Press1]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 4]						",1,&E_EndPosition_Machine	[4]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 5]						",1,&E_EndPosition_Machine	[K_St005_Housing_Press2]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 1]						",1,&SK_EndPosition_Machine	[K_St001_Housing_Separating]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 2]						",1,&SK_EndPosition_Machine	[2]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 3]						",1,&SK_EndPosition_Machine	[K_St003_Housing_Press1]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 4]						",1,&SK_EndPosition_Machine	[4]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 5]						",1,&SK_EndPosition_Machine	[K_St005_Housing_Press2]);

	OnlineVarEndstellung("E_EndPosition_Machine[St. 21]						",1,&E_EndPosition_Machine	[K_St021_Check_Carrier_Empty]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 22]						",1,&E_EndPosition_Machine	[K_St022_Current_Bar_Feeding_A]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 23]						",1,&E_EndPosition_Machine	[K_St023_Check_Press_Current_Bar]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 24]						",1,&E_EndPosition_Machine	[K_St024_Clamping_Sleeve_Feeding]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 25]						",1,&E_EndPosition_Machine	[K_St025_Metal_Parts_Assembly]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 26]						",1,&E_EndPosition_Machine	[K_St026_Clamping_Sleeve_Checking]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 27]						",1,&E_EndPosition_Machine	[K_St027_Reject_Parts_Eject]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 28]						",1,&E_EndPosition_Machine	[K_St028_Pre_Assembled_Parts_Eject]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 21]						",1,&SK_EndPosition_Machine	[K_St021_Check_Carrier_Empty]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 22]						",1,&SK_EndPosition_Machine	[K_St022_Current_Bar_Feeding_A]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 23]						",1,&SK_EndPosition_Machine	[K_St023_Check_Press_Current_Bar]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 24]						",1,&SK_EndPosition_Machine	[K_St024_Clamping_Sleeve_Feeding]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 25]						",1,&SK_EndPosition_Machine	[K_St025_Metal_Parts_Assembly]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 26]						",1,&SK_EndPosition_Machine	[K_St026_Clamping_Sleeve_Checking]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 27]						",1,&SK_EndPosition_Machine	[K_St027_Reject_Parts_Eject]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 28]						",1,&SK_EndPosition_Machine	[K_St028_Pre_Assembled_Parts_Eject]);

	OnlineVarEndstellung("E_EndPosition_Machine[St. 41]						",1,&E_EndPosition_Machine	[K_St041_Check_Carrier_Empty]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 42]						",1,&E_EndPosition_Machine	[K_St042_Current_Bar_Feeding_A]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 43]						",1,&E_EndPosition_Machine	[K_St043_Check_Press_Current_Bar]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 44]						",1,&E_EndPosition_Machine	[K_St044_Clamping_Sleeve_Feeding]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 45]						",1,&E_EndPosition_Machine	[K_St045_Metal_Parts_Assembly]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 46]						",1,&E_EndPosition_Machine	[K_St046_Clamping_Sleeve_Checking]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 47]						",1,&E_EndPosition_Machine	[K_St047_Reject_Parts_Eject]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 48]						",1,&E_EndPosition_Machine	[K_St048_Pre_Assembled_Parts_Eject]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 35]						",1,&E_EndPosition_Machine	[35]);
	OnlineVarEndstellung("E_EndPosition_Machine[St. 55]						",1,&E_EndPosition_Machine	[55]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 41]						",1,&SK_EndPosition_Machine	[K_St041_Check_Carrier_Empty]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 42]						",1,&SK_EndPosition_Machine	[K_St042_Current_Bar_Feeding_A]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 43]						",1,&SK_EndPosition_Machine	[K_St043_Check_Press_Current_Bar]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 44]						",1,&SK_EndPosition_Machine	[K_St044_Clamping_Sleeve_Feeding]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 45]						",1,&SK_EndPosition_Machine	[K_St045_Metal_Parts_Assembly]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 46]						",1,&SK_EndPosition_Machine	[K_St046_Clamping_Sleeve_Checking]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 47]						",1,&SK_EndPosition_Machine	[K_St047_Reject_Parts_Eject]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 48]						",1,&SK_EndPosition_Machine	[K_St048_Pre_Assembled_Parts_Eject]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 35]						",1,&SK_EndPosition_Machine	[35]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 55]						",1,&SK_EndPosition_Machine	[55]);

	//OnlineVarEndstellung("SK_EndPosition_Machine[t1 ]						",1,&SK_EndPosition_Machine	[1  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t2 ]						",1,&SK_EndPosition_Machine	[2  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t3 ]						",1,&SK_EndPosition_Machine	[3  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t4 ]						",1,&SK_EndPosition_Machine	[4  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t5 ]						",1,&SK_EndPosition_Machine	[5  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t6 ]						",1,&SK_EndPosition_Machine	[6  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t7 ]						",1,&SK_EndPosition_Machine	[7  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t8 ]						",1,&SK_EndPosition_Machine	[8  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t9 ]						",1,&SK_EndPosition_Machine	[9  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t10]						",1,&SK_EndPosition_Machine	[10 ]);
	//
	//OnlineVarEndstellung("SK_EndPosition_Machine[t11 ]						",1,&SK_EndPosition_Machine	[11  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t12 ]						",1,&SK_EndPosition_Machine	[12  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t13 ]						",1,&SK_EndPosition_Machine	[13  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t14 ]						",1,&SK_EndPosition_Machine	[14  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t15 ]						",1,&SK_EndPosition_Machine	[15  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t16 ]						",1,&SK_EndPosition_Machine	[16  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t17 ]						",1,&SK_EndPosition_Machine	[17  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t18 ]						",1,&SK_EndPosition_Machine	[18  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t19 ]						",1,&SK_EndPosition_Machine	[19  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t20]						",1,&SK_EndPosition_Machine	[20 ]);
	//
	//OnlineVarEndstellung("SK_EndPosition_Machine[t21 ]						",1,&SK_EndPosition_Machine	[21  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t22 ]						",1,&SK_EndPosition_Machine	[22  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t23 ]						",1,&SK_EndPosition_Machine	[23  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t24 ]						",1,&SK_EndPosition_Machine	[24  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t25 ]						",1,&SK_EndPosition_Machine	[25  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t26 ]						",1,&SK_EndPosition_Machine	[26  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t27 ]						",1,&SK_EndPosition_Machine	[27  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t28 ]						",1,&SK_EndPosition_Machine	[28  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t29 ]						",1,&SK_EndPosition_Machine	[29  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t30]						",1,&SK_EndPosition_Machine	[30 ]);
	//
	//OnlineVarEndstellung("SK_EndPosition_Machine[t31 ]						",1,&SK_EndPosition_Machine	[31  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t32 ]						",1,&SK_EndPosition_Machine	[32  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t33 ]						",1,&SK_EndPosition_Machine	[33  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t34 ]						",1,&SK_EndPosition_Machine	[34  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t35 ]						",1,&SK_EndPosition_Machine	[35  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t36 ]						",1,&SK_EndPosition_Machine	[36  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t37 ]						",1,&SK_EndPosition_Machine	[37  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t38 ]						",1,&SK_EndPosition_Machine	[38  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t39 ]						",1,&SK_EndPosition_Machine	[39  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t40]						",1,&SK_EndPosition_Machine	[40 ]);
	//
	//OnlineVarEndstellung("SK_EndPosition_Machine[t41 ]						",1,&SK_EndPosition_Machine	[41  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t42 ]						",1,&SK_EndPosition_Machine	[42  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t43 ]						",1,&SK_EndPosition_Machine	[43  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t44 ]						",1,&SK_EndPosition_Machine	[44  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t45 ]						",1,&SK_EndPosition_Machine	[45  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t46 ]						",1,&SK_EndPosition_Machine	[46  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t47 ]						",1,&SK_EndPosition_Machine	[47  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t48 ]						",1,&SK_EndPosition_Machine	[48  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t49 ]						",1,&SK_EndPosition_Machine	[49  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t50]						",1,&SK_EndPosition_Machine	[50 ]);
	//
	//OnlineVarEndstellung("SK_EndPosition_Machine[t51 ]						",1,&SK_EndPosition_Machine	[51  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t52 ]						",1,&SK_EndPosition_Machine	[52  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t53 ]						",1,&SK_EndPosition_Machine	[53  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t54 ]						",1,&SK_EndPosition_Machine	[54  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t55 ]						",1,&SK_EndPosition_Machine	[55  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t56 ]						",1,&SK_EndPosition_Machine	[56  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t57 ]						",1,&SK_EndPosition_Machine	[57  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t58 ]						",1,&SK_EndPosition_Machine	[58  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t59 ]						",1,&SK_EndPosition_Machine	[59  ]);
	//OnlineVarEndstellung("SK_EndPosition_Machine[t60]						",1,&SK_EndPosition_Machine	[60 ]);


#ifdef Scanner_V24
	OnlineVarEintragen("----- BARCODESCANNER ---------------------------------",1,&ANZEIGE);
	OnlineVarEintragen("Scannerfreigabe										",1,&Scannerfreigabe[COM2]);
	OnlineVarEintragen("Scannerrueckmeldung									",1,&Scannerrueckmeldung[COM2]);
	OnlineVarEintragen("ScannerfreigabeHand									",1,&ScannerfreigabeHand[COM2]);
	OnlineVarEintragen("V24_Barcodenummer									",5,&V24_Barcodenummer[COM2]);

	OnlineVarEintragen("----- EMPFANGENE NESTDATEN ---------------------------",1,&ANZEIGE);
	OnlineVarEintragen("WPC_Data_request									",1,&WPC_Data_request);			//Nestdaten_anfordern
	OnlineVarEintragen("WPC_Data_requested									",1,&WPC_Data_requested);		//Nestdaten_angefordert
	OnlineVarEintragen("WPC_Data_received									",1,&WPC_Data_received);		//Nesterdaten_erhalten

#endif

#ifdef Scanner_IBS_RS232
	OnlineVarEintragen("----- BARCODESCANNER RS232 ---------------------------",1,&ANZEIGE);
	OnlineVarEintragen("MW_Barcodenummer									",5,&MW_Barcodenummer);

	OnlineVarEintragen("bSendData[0]										",1,&bSendData[0]);
	OnlineVarEintragen("bSendData[1]										",1,&bSendData[1]);
	OnlineVarEintragen("bSendData[2]										",1,&bSendData[2]);
	OnlineVarEintragen("bSendData[3]										",1,&bSendData[3]);
	OnlineVarEintragen("bSendData[4]										",1,&bSendData[4]);
	OnlineVarEintragen("bSendData[5]										",1,&bSendData[5]);
	OnlineVarEintragen("bSendData[6]										",1,&bSendData[6]);
	OnlineVarEintragen("bSendData[7]										",1,&bSendData[7]);
	OnlineVarEintragen("bSendData[8]										",1,&bSendData[8]);
	OnlineVarEintragen("bSendData[9]										",1,&bSendData[9]);
	OnlineVarEintragen("bSendData[10]										",1,&bSendData[10]);
	OnlineVarEintragen("bSendData[11]										",1,&bSendData[11]);

	OnlineVarEintragen("bReadData[0]										",1,&bReadData[0]);
	OnlineVarEintragen("bReadData[1]										",1,&bReadData[1]);
	OnlineVarEintragen("bReadData[2]										",1,&bReadData[2]);
	OnlineVarEintragen("bReadData[3]										",1,&bReadData[3]);
	OnlineVarEintragen("bReadData[4]										",1,&bReadData[4]);
	OnlineVarEintragen("bReadData[5]										",1,&bReadData[5]);
	OnlineVarEintragen("bReadData[6]										",1,&bReadData[6]);
	OnlineVarEintragen("bReadData[7]										",1,&bReadData[7]);
	OnlineVarEintragen("bReadData[8]										",1,&bReadData[8]);
	OnlineVarEintragen("bReadData[9]										",1,&bReadData[9]);
	OnlineVarEintragen("bReadData[10]										",1,&bReadData[10]);
	OnlineVarEintragen("bReadData[11]										",1,&bReadData[11]);

	OnlineVarEintragen("----- EMPFANGENE NESTDATEN -------------------------",1,&ANZEIGE);
	OnlineVarEintragen("WPC_Data_request									",1,&WPC_Data_request);		// Nestdaten_anfordern
	OnlineVarEintragen("WPC_Data_requested									",1,&WPC_Data_requested);	// Nestdaten_angefordert
	OnlineVarEintragen("WPC_Data_received									",1,&WPC_Data_received);	// Nesterdaten_erhalten
#endif

#ifdef VIEW_RUNTIMES
	OnlineVarLaufzeiten("----- Sonstige Variablen ----------------------------",1,&ANZEIGE);
	OnlineVarLaufzeiten("M.Save_RunTime_in_file								",1,&M.Save_RunTime_in_file);
	OnlineVarLaufzeiten("----- RUNTIME OF STATIONS ---------------------------",1,&ANZEIGE);
	OnlineVarLaufzeiten("All_RunTimes_Reset									",1,&All_RunTimes_Reset);
	#ifdef Axis_exist
	OnlineVarLaufzeiten("----- RUNTIME RESET ST.201 ACHSE --------------------",1,&RunTimes_Reset_Station	[K_St201_MainProcess_Axis]);
	OnlineVarLaufzeiten("actual RunTime Blockend							",5,&RunTime					[K_St201_MainProcess_Axis][0]);
	OnlineVarLaufzeiten("max RunTime Blockend								",5,&RunTime_max				[K_St201_MainProcess_Axis][0]);
	OnlineVarLaufzeiten("min RunTime Blockend								",5,&RunTime_min				[K_St201_MainProcess_Axis][0]);
	OnlineVarLaufzeiten("-----------------------------------------------------",1,&RunTimes_Reset_Station	[K_St201_MainProcess_Axis]);
	OnlineVarLaufzeiten("actual RunTime Housing_End							",5,&RunTime					[K_St201_MainProcess_Axis][1]);
	OnlineVarLaufzeiten("max RunTime Housing_End							",5,&RunTime_max				[K_St201_MainProcess_Axis][1]);
	OnlineVarLaufzeiten("min RunTime Housing_End							",5,&RunTime_min				[K_St201_MainProcess_Axis][1]);
	OnlineVarLaufzeiten("-----------------------------------------------------",1,&RunTimes_Reset_Station	[K_St201_MainProcess_Axis]);
	OnlineVarLaufzeiten("actual RunTime Pole to Pole						",5,&RunTime					[K_St201_MainProcess_Axis][2]);
	OnlineVarLaufzeiten("max RunTime Pole to Pole							",5,&RunTime_max				[K_St201_MainProcess_Axis][2]);
	OnlineVarLaufzeiten("min RunTime Pole to Pole							",5,&RunTime_min				[K_St201_MainProcess_Axis][2]);
	OnlineVarLaufzeiten("-----------------------------------------------------",1,&RunTimes_Reset_Station	[K_St201_MainProcess_Axis]);
	#endif
	#ifdef Plate_exist
	OnlineVarLaufzeiten("----- RUNTIME RESET ST.202 PLATE --------------------",1,&RunTimes_Reset_Station	[K_St202_Hauptablauf_Teller]);
	OnlineVarLaufzeiten("actual RunTime Plate 								",5,&RunTime					[K_St202_Hauptablauf_Teller][0]);
	OnlineVarLaufzeiten("max RunTime Plate 									",5,&RunTime_max				[K_St202_Hauptablauf_Teller][0]);
	OnlineVarLaufzeiten("min RunTime Plate 									",5,&RunTime_min				[K_St202_Hauptablauf_Teller][0]);
	#endif
	#ifdef Plate_FU_exist
	OnlineVarLaufzeiten("----- RUNTIME RESET ST.203 TELLER -------------------",1,&RunTimes_Reset_Station	[K_St203_Hauptablauf_Teller]);
	OnlineVarLaufzeiten("actual  RunTime Plate 								",5,&RunTime					[K_St203_Hauptablauf_Teller][0]);
	OnlineVarLaufzeiten("max RunTime Plate 									",5,&RunTime_max				[K_St203_Hauptablauf_Teller][0]);
	OnlineVarLaufzeiten("min RunTime Plate 									",5,&RunTime_min				[K_St203_Hauptablauf_Teller][0]);
	#endif
	#ifdef Plate_Siemens_FU_exist
	OnlineVarLaufzeiten("----- RUNTIME RESET ST.204 TELLER -------------------",1,&RunTimes_Reset_Station	[K_St204_Hauptablauf_Teller]);
	OnlineVarLaufzeiten("actual  RunTime Plate 								",5,&RunTime					[K_St204_Hauptablauf_Teller][0]);
	OnlineVarLaufzeiten("max RunTime Plate 									",5,&RunTime_max				[K_St204_Hauptablauf_Teller][0]);
	OnlineVarLaufzeiten("min RunTime Plate 									",5,&RunTime_min				[K_St204_Hauptablauf_Teller][0]);
	#endif
	#if defined(Scanner_V24) || defined(Scanner_IBS_RS232)
	OnlineVarLaufzeiten("----- RUNTIME RESET BARCODESCANNER ------------------",1,&RunTimes_Reset_Station	[K_Barcodescanner]);
	OnlineVarLaufzeiten("Barcodescanner RunTime								",5,&RunTime					[K_Barcodescanner][0]);
	OnlineVarLaufzeiten("Barcodescanner RunTime max							",5,&RunTime_max				[K_Barcodescanner][0]);
	OnlineVarLaufzeiten("Barcodescanner RunTime min							",5,&RunTime_min				[K_Barcodescanner][0]);
	#endif
	//OnlineVarLaufzeiten("----- RUNTIME RESET ST.3 ----------------------------",1,&RunTimes_Reset_Station	[K_St3_Zufuehren_Einsetzen_Kontaktblock]);
	//OnlineVarLaufzeiten("St. 3 RunTime              (Gesamtzeit)			",5,&RunTime					[K_St3_Zufuehren_Einsetzen_Kontaktblock][0]);
	//OnlineVarLaufzeiten("St. 3 RunTime max									",5,&RunTime_max				[K_St3_Zufuehren_Einsetzen_Kontaktblock][0]);
	//OnlineVarLaufzeiten("St. 3 RunTime min									",5,&RunTime_min				[K_St3_Zufuehren_Einsetzen_Kontaktblock][0]);
	//OnlineVarLaufzeiten("St. 3 RunTime AxisOperation						",5,&RunTime					[K_St3_Zufuehren_Einsetzen_Kontaktblock][1]);
	//OnlineVarLaufzeiten("St. 3 RunTime AxisOperation max					",5,&RunTime_max				[K_St3_Zufuehren_Einsetzen_Kontaktblock][1]);
	//OnlineVarLaufzeiten("St. 3 RunTime AxisOperation min					",5,&RunTime_min				[K_St3_Zufuehren_Einsetzen_Kontaktblock][1]);
#endif

#ifdef VIEW_MinuteCycle
	OnlineVarLaufzeiten("-------- ANTRIEB 1 ----------------------------------",1,&ANZEIGE);
	OnlineVarLaufzeiten("----- MINUTECYCLE RESET ST.204 Teller  --------------",1,&RunTimes_Reset_Station	[K_St204_Hauptablauf_Teller]);
	OnlineVarLaufzeiten("St.204 actual Taktzahl								",5,&MinuteCycle_actual			[K_St204_Hauptablauf_Teller][0]);
	OnlineVarLaufzeiten("St.204 Taktzahl Max								",5,&MinuteCycle_max			[K_St204_Hauptablauf_Teller][0]);
	//OnlineVarLaufzeiten("----- MINUTECYCLE RESET ST.3 EINSETZEN --------------",1,&RunTimes_Reset_Station	[K_St3_Zufuehren_Einsetzen_Kontaktblock]);
	//OnlineVarLaufzeiten("St. 3 actual Taktzahl								",5,&MinuteCycle_actual			[K_St3_Zufuehren_Einsetzen_Kontaktblock][0]);
	//OnlineVarLaufzeiten("St. 3 Taktzahl Max									",5,&MinuteCycle_max			[K_St3_Zufuehren_Einsetzen_Kontaktblock][0]);
#endif

#ifdef HVPruefung_vorhanden
	OnlineVarEintragen("----- Hochspannungspr黤ung ---------------------------",1,&ANZEIGE);
	OnlineVarEintragen("HV_Leerlauf_start[HV1]								",1,&HV_Leerlauf_start[HV1]);
	OnlineVarEintragen("HV_Pruefung_start[HV1]								",1,&HV_Pruefung_start[HV1]);
	OnlineVarEintragen("HV_Sampels_U[HV1]									",3,&HV_Sampels_U[HV1]);
	OnlineVarEintragen("HV_Sampels_I[HV1]									",3,&HV_Sampels_I[HV1]);
	OnlineVarEintragen("Kalibrierung[HV1].Kalibrierung_Aktiv				",1,&Kalibrierung[HV1].Kalibrierung_Aktiv);
	OnlineVarEintragen("Vorgaben[HV1].U_min									",7,&Hochspg_Vorgaben[HV1].U_min);
	OnlineVarEintragen("Vorgaben[HV1].U_max									",7,&Hochspg_Vorgaben[HV1].U_max);
	OnlineVarEintragen("Vorgaben[HV1].U_min_Pruef							",7,&Hochspg_Vorgaben[HV1].U_min_Pruef);
	OnlineVarEintragen("Vorgaben[HV1].Summand_Pruefspannung					",7,&Hochspg_Vorgaben[HV1].Summand_Pruefspannung);
	OnlineVarEintragen("Vorgaben[HV1].Summand_Imin							",7,&Hochspg_Vorgaben[HV1].Summand_Imin);
	OnlineVarEintragen("Vorgaben[HV1].I_MultiMittel							",7,&Hochspg_Vorgaben[HV1].I_MultiMittel);
	OnlineVarEintragen("Vorgaben[HV1].I_MultiSpitze							",7,&Hochspg_Vorgaben[HV1].I_MultiSpitze);
	OnlineVarEintragen("Vorgaben[HV1].SollTime								",3,&Hochspg_Vorgaben[HV1].SollTime);
#endif



#ifdef VIEW_CAMERA_IO
	OnlineVarEintragen("----- KAMERA 1 STATION  4 --------------------------",1,&ANZEIGE);
	OnlineVarEintragen("E_Kamera_fertig[1]									",1,&E_Kamera_fertig[1]);
	OnlineVarEintragen("E_Kamera_Gutmeldung[1]								",1,&E_Kamera_Gutmeldung[1]);
	OnlineVarEintragen("E_Kamera_Beleuchtung_OK[1]							",1,&E_Kamera_Beleuchtung_OK[1]);
	OnlineVarEintragen("E_Kamera_Beleuchtung_ein[1]							",1,&E_Kamera_Beleuchtung_ein[1]);
	OnlineVarEintragen("A_Start_Sig1_Kamera[1]								",1,&A_Start_Sig1_Kamera[1]);
	OnlineVarEintragen("A_Start_Sig2_Kamera[1]								",1,&A_Start_Sig2_Kamera[1]);
	OnlineVarEintragen("A_Blockbeginn_Kamera[1]								",1,&A_Blockbeginn_Kamera[1]);
	OnlineVarEintragen("A_Beleuchtung_einschalten_Kamera[1]					",1,&A_Beleuchtung_einschalten_Kamera[1]);
	OnlineVarEintragen("A_Kamera_ein[1]										",1,&A_Kamera_ein[1]);

	OnlineVarEintragen("----- KAMERA 2 STATION  5 --------------------------",1,&ANZEIGE);
	OnlineVarEintragen("E_Kamera_fertig[2]									",1,&E_Kamera_fertig[2]);
	OnlineVarEintragen("E_Kamera_Gutmeldung[2]								",1,&E_Kamera_Gutmeldung[2]);
	OnlineVarEintragen("E_Kamera_Beleuchtung_OK[2]							",1,&E_Kamera_Beleuchtung_OK[2]);
	OnlineVarEintragen("E_Kamera_Beleuchtung_ein[2]							",1,&E_Kamera_Beleuchtung_ein[2]);
	OnlineVarEintragen("A_Start_Sig1_Kamera[2]								",1,&A_Start_Sig1_Kamera[2]);
	OnlineVarEintragen("A_Start_Sig2_Kamera[2]								",1,&A_Start_Sig2_Kamera[2]);
	OnlineVarEintragen("A_Blockbeginn_Kamera[2]								",1,&A_Blockbeginn_Kamera[2]);
	OnlineVarEintragen("A_Beleuchtung_einschalten_Kamera[2]					",1,&A_Beleuchtung_einschalten_Kamera[2]);
	OnlineVarEintragen("A_Kamera_ein[2]										",1,&A_Kamera_ein[2]);

	OnlineVarEintragen("E_Kameraprogramm_RUN[KameraPC_1]					",1,&E_Kameraprogramm_RUN[KameraPC_1]);
	OnlineVarEintragen("E_Kameraprogramm_RUN[KameraPC_2]					",1,&E_Kameraprogramm_RUN[KameraPC_2]);
	OnlineVarEintragen("A_PRG_beenden										",1,&A_PRG_beenden);
#endif

#ifdef Plate_Siemens_FU_exist
	OnlineVarEintragen("------- Profinet Siemens Antrieb ---------------------",1,&ANZEIGE);
	// Antrieb 1
	OnlineVarEintragen("AB_PN1_Siemens_IO_Data1								",2,&SiemensFU_Data[SFU1].AB_PN_Siemens_IO_Data[0]);
	OnlineVarEintragen("AB_PN1_Siemens_IO_Data2								",2,&SiemensFU_Data[SFU1].AB_PN_Siemens_IO_Data[1]);
	OnlineVarEintragen("AB_PN1_Siemens_IO_Data3								",2,&SiemensFU_Data[SFU1].AB_PN_Siemens_IO_Data[2]);
	OnlineVarEintragen("AB_PN1_Siemens_IO_Data4								",2,&SiemensFU_Data[SFU1].AB_PN_Siemens_IO_Data[3]);

	OnlineVarEintragen("EB_PN1_Siemens_IO 1									",2,&SiemensFU_Data[SFU1].EB_PN_Siemens_IO_Data[0]);
	OnlineVarEintragen("EB_PN1_Siemens_IO 2									",2,&SiemensFU_Data[SFU1].EB_PN_Siemens_IO_Data[1]);
	OnlineVarEintragen("EB_PN1_Siemens_IO 3									",2,&SiemensFU_Data[SFU1].EB_PN_Siemens_IO_Data[2]);
	OnlineVarEintragen("EB_PN1_Siemens_IO 4									",2,&SiemensFU_Data[SFU1].EB_PN_Siemens_IO_Data[3]);
	OnlineVarEintragen("EB_PN1_Siemens_TrennData							",2,&EB_PN_Siemens_TrennData[SFU1]);

	memset(&buf,0,sizeof(buf));
	for (int i=0; i<2;i++)
	{
		sprintf(buf,"PN1 Siemens Data[%d] ",i);
		OnlineVarEintragen(buf,2,&SiemensFU_Data[SFU1].EB_PN_Siemens_Data[i]);
	}
//	OnlineVarEintragen("xSiemensFU1_xManEnable",  1,&SiemensFU_Data[SFU1].xManEnable);
//	OnlineVarEintragen("xSiemensFU1_xManCycleCW", 1,&SiemensFU_Data[SFU1].xManCycleCW);
//	OnlineVarEintragen("xSiemensFU1_xManCycleCCW",1,&SiemensFU_Data[SFU1].xManCycleCCW);
//	OnlineVarEintragen("xSiemensFU1_xManJogCW",   1,&SiemensFU_Data[SFU1].xManJogCW);
//	OnlineVarEintragen("xSiemensFU1_xManJogCCW",  1,&SiemensFU_Data[SFU1].xManJogCCW);
	OnlineVarEintragen("xSiemensFU1_xReadyToStart							",1,&SiemensFU_Data[SFU1].xReadyToStart);
	OnlineVarEintragen("xSiemensFU1_xAutoEnable								",1,&SiemensFU_Data[SFU1].xAutoEnable);
	OnlineVarEintragen("xSiemensFU1_xStartCycle								",1,&SiemensFU_Data[SFU1].xStartCycle);
	OnlineVarEintragen("xSiemensFU1_iErrorNo								",3,&SiemensFU_Data[SFU1].iErrorNo);
	OnlineVarEintragen("xSiemensFU1_xTableInPosition						",1,&SiemensFU_Data[SFU1].xTableInPosition);
	OnlineVarEintragen("xSiemensFU1_xDirection								",1,&SiemensFU_Data[SFU1].xDirection);

#endif


#ifdef VIEW_POSITION_VALUE
#ifdef Axis_exist
	memset(&buf,0,sizeof(buf));

	OnlineVarEintragen("----- POLEPOSITIONSVALUE DriveUnit 1 -----------------",1,&ANZEIGE);
	// Polpositionswerte positiv
	for (int x=1; x<=MAX_NUMBERHOUSING; x++)
	{
		for (int y=1; y<=MAX_NUMBERPOLE; y++)
		{
			if (y < 10)	sprintf(buf,"Axis 1 - PolePositionValue pos[%d][%d]      ",x,y);
			else		sprintf(buf,"Axis 1 - PolePositionValue pos[%d][%d]     ",x,y);
			OnlineVarEintragen(buf,7,&Achse[Axis1].PolePositionValue_positiv[x][y]);
		}
	}

	// Polpositionswerte negativ
	for (int x=1; x<=MAX_NUMBERHOUSING; x++)
	{
		for (int y=1; y<=MAX_NUMBERPOLE; y++)
		{
			if (y < 10)	sprintf(buf,"Axis 1 - PolePositionValue neg[%d][%d]      ",x,y);
			else		sprintf(buf,"Axis 1 - PolePositionValue neg[%d][%d]     ",x,y);
			OnlineVarEintragen(buf,7,&Achse[Axis1].PolePositionValue_negativ[x][y]);
		}
	}
#endif
#endif

	OnlineVarEintragen("----- SAFETYBRIDGE -----------------------------------",1,&ANZEIGE);
	OnlineVarEintragen("SBTMaPart1.E_Quit									",1,&SBTMaPart1.E_Quit);
	OnlineVarEintragen("SBTMaPart1.E_SafetyDoorCircleClosed					",1,&SBTMaPart1.E_SafetyDoorCircleClosed);
	OnlineVarEintragen("SBTMaPart1.E_EmergencyStopCircleClosed				",1,&SBTMaPart1.E_EmergencyStopCircleClosed);
	OnlineVarEintragen("SBTMaPart1.E_SingleStepMode							",1,&SBTMaPart1.E_SingleStepMode);
	OnlineVarEintragen("SBTMaPart1.E_ErrorKey								",1,&SBTMaPart1.E_ErrorKey);

	OnlineVarEintragen("SBTMaPart1.A_KeepClosed_SafetyDoors					",1,&SBTMaPart1.A_KeepClosed_SafetyDoors);
	OnlineVarEintragen("SBTMaPart1.A_MotorStandStill						",1,&SBTMaPart1.A_MotorStandStill);
	OnlineVarEintragen("SBTMaPart1.A_SoftwareEmergencyStop					",1,&SBTMaPart1.A_SoftwareEmergencyStop);
	OnlineVarEintragen("SBTMaPart1.SafetyCircleClosed						",1,&SBTMaPart1.SafetyCircleClosed);
	OnlineVarEintragen("SBTMaPart1.ErrorMaOff								",1,&SBTMaPart1.ErrorMaOff);
	OnlineVarEintragen("SBTMaPart1.ErrorEmergencyStop						",1,&SBTMaPart1.ErrorEmergencyStop);
	OnlineVarEintragen("SBTMaPart1.ErrorSafetyDoorCircle					",1,&SBTMaPart1.ErrorSafetyDoorCircle);
	OnlineVarEintragen("SBTMaPart1.ErrorDoorsNotClosed						",1,&SBTMaPart1.ErrorDoorsNotClosed);

	memset(&buf,0,sizeof(buf));
	for (int x=1; x<=NUMBERSAFETYDOORS; x++)
	{
		sprintf(buf,"SBTMaPart1.ErrorSafetyDoor[%d]",x);
		OnlineVarEintragen(buf,1,&SBTMaPart1.ErrorSafetyDoor[x]);
	}
	OnlineVarEintragen("SBTMaPart1.ErrorKey									",1,&SBTMaPart1.ErrorKey);

#ifdef VIEW_SBTDIAGNOSIS
	memset(&buf,0,sizeof(buf));

	OnlineVarEintragen("----- SAFETYBRIDGE - DIAGNOSE - INSEL 1	--------------",1,&ANZEIGE);
	OnlineVarEintragen("SBTInsel1.Status									",3,&SBTInsel1.Status);

	for (int x=1; x<=32; x++)
	{
		if (x < 10)	sprintf(buf,"SBTInsel1.EQ[ %i]                          ",x);
		else		sprintf(buf,"SBTInsel1.EQ[%i]                           ",x);
		OnlineVarEintragen(buf,1,&SBTInsel1.EQ[x]);
	}
	for (int x=1; x<=32; x++)
	{
		if (x < 10)	sprintf(buf,"SBTInsel1.EI[ %i]                          ",x);
		else		sprintf(buf,"SBTInsel1.EI[%i]                           ",x);
		OnlineVarEintragen(buf,1,&SBTInsel1.EI[x]);
	}
	for (int x=0; x<=MAXMODULEPROINSEL; x++)
	{
		if (x < 10)	sprintf(buf,"SBTInsel1.Modul[ %i].ErrorCode             ",x);
		else		sprintf(buf,"SBTInsel1.Modul[%i].ErrorCode              ",x);
		OnlineVarEintragen(buf,4,&SBTInsel1.Modul[x].ErrorCode);
	}
#endif
	
}// Init SPS Variablen


