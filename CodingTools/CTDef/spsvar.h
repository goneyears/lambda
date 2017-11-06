/*******************************************************************************************************
**
** Dateiname          : SPSVAR.h
** Datum              : 01.01.2002
** Rev. Nr.		      : 0.1
** Rev. Änderungen	  : siehe Verzeichnis "Standard_Prg" RevNr.xls
**
** Funktion			  : Deklaration von Flanken,Zeiten,Schrittketten,
**						Eingänge,Ausgänge und Merkern
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
**						06.01.2009		M.van de Wouw		Überarbeitet für Grundprogramm V2.2
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
//********  DEFINE Zuweisungen fürs Grundprogramm  *********
//**********************************************************

#define MAX_FLANK					254		//	flank						Flanken					
#define MAX_COUNTER					254		//	counter						Zaehler					
#define MAX_TIMER					400		//	timer						Timer					
#define MAX_FRQTIMER				  9		//	frequence timer				Frequenztimer			

#define TEXTLEN						 51		// Max.Zeichen
											// für Zeiten,Zähler,Schrittketten, nicht remanente Variablen,
											// Eingänge, Ausgänge,
#define MAXONLVAR					400		// Anzahl der nicht remaneten Variablen

#define MAX_AXIS_OFFSET				 19		//	number of offsets pro axis					Anzahl Offsets pro Achse					
#define MAX_MESSAGE					 24		//	number of messages to BDE					Anzahl der Meldungen an BDE				
#define MAX_WARNING					 24		//	number of warnings to BDE					Anzahl der Warnungen an BDE				
#define MAX_CHECK_ERROR				 49		//	number of check errors for index 22			Anzahl der Prüffehler für Index 22		
#define MAX_SPSPARAMETER			 29		//	for Index64 Stand 08/2005					für Index64 Stand 08/2005				

//**********************************************************
//***********  DEFINE Zuweisungen fürs Register  ***********
//**********************************************************

// 2 Dimensionales Schieberegister
#define MAXREGISTER					  1		//	e.g. number of nests					z.B. Anzahl der Nester
#define MAXREGISTER_LENGTH			  60	//	e.g. number of poles in one housing		z.B. Anzahl der Pole in einem Gehäuse

// 3 Dimensionales Schieberegister
#define MAX3DREGISTER				 25		//	e.g. number of nests					z.B. Anzahl der Nester
#define MAX3DREGISTER_BLOCK			  2		//	e.g. number of housings in one nest		z.B. Anzahl der Gehäuse in einem Nest
#define MAX3DREGISTER_LENGTH		 24		//	e.g. number of poles in one housing		z.B. Anzahl der Pole in einem Gehäuse

//***********************************************************
//********  DEFINE Zuweisungen für Allgemeinedaten  *********
//***********************************************************

#define MAX_AXIS					  2		//	number of axes									Anzahl Achsen
#define MAX_MACHINE					  1		//	number of BDE machine parts in this program		Anzahl der BDE Maschinenteile in diesem Programm
#define MAX_ERRORPRG				  1		//  number of error programms						Anzahl der Fehlerprogramme

#define WPC_LENGTH					150		//	WPC length in mm								Nestlänge in mm
#define MAX_NUMBERPOLE				 24		//	maximal number of poles in one housing 			Maximale Polzahl der Gehaeuse
#define MAX_NUMBERHOUSING			  2		//	maximal number of housing in one nest 			Maximale Anzahl der Gehaeuse pro Nest

#define MAXANZSTAT					 32		//	maximal number of stations (36 stations)		Anz. Stationen
#define MAX_SEQUENCES				 60		//	sequencer										Schrittketten
#define MAX_MAINAIR					310		//	number of main air valves						Anzahl der Hauptluftventile
#define NUMBERSAFETYDOORS			  7		//	number of safety doors							Anzahl der Schutztüren eintragen
#define MAX_STOPWATCH				  3		//	number of stopwatches for every station			Anzahl der Stopuhren pro Station


//***********************************************************
//******  DEFINE Zuweisungen für Teil Informationen  ********
//***********************************************************

#define GUTTEIL						1010	// Erklärungen der Werte wie man sie bildet stehen 
#define GUTPOL						1010	// in BDE_Data_Transfer()
#define GUTPOL_SOPO					1011	// Gutpol mit Sonderbestueckung

//*********************************************************
//********  DEFINE Zuweisungen für SONDERSACHEN   *********
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
 #include "Kamera_Daten.h"	// Datenübergabe zum Kamerapipe
#endif

#ifdef Axis_exist
 #include "A_var.h"			// Variablen für Achsen im Allgemeinen
#endif

#ifdef Plate_exist 
 #include "TellerVar.h"		// Variablen für Teller im Allgemeinen
#endif

#ifdef Plate_FU_exist 
 #include "TellerVar.h"		// Variablen für Teller im Allgemeinen
#endif

#ifdef Plate_Siemens_FU_exist 
 #include "TellerVar.h"		// Variablen für Teller im Allgemeinen
#endif


#include "AntriebeVar.h"	// Variablen für Antriebe im Allgemeinen

#ifdef HVPruefung_vorhanden
 #include "HochspgVar.h"
#endif

#include "spipevar.h"				// Vaiablen für die Pipeverbindung
#include "SPSMess_Einstellung.h"	// Einstellungen für die Elektrische Messung
#include "SPSMessVar.h"				// Variablen für die Elektrische Messung


#ifndef Menue_programm

#include "HaspelStolpeBarg.h"
CHaspelStolpeBarg *St4_Coiler = new CHaspelStolpeBarg();

#include "CFesto_Step.h"
CFesto_Step *St4_PositionRad = new CFesto_Step(); // Klasse instanzieren
CFesto_Step *St4_Ejector = new CFesto_Step(); // Klasse instanzieren
CFesto_Step *St4_Inserter = new CFesto_Step(); // Klasse instanzieren

#endif

//*****************************************************************
//****************  Konstanten für Flanken  ***********************
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
#define FL_St8_Start_Pruefintervall							34

//Stationsbezogen 
#define Fl_St201_WPC_passing							    50			//Fl_St201_Nest_durchgelaufen	
#define Fl_St201_StationenReset								51			//Fl_St201_StationenReset		
#define Fl_St202_StationenReset								52			//Fl_St202_StationenReset		
#define Fl_St203_StationenReset								53			//Fl_St203_StationenReset		
#define Fl_St203_PlateTurnsOff							    54			//Fl_St203_Teller_drehen_aus	
#define Fl_St204_StationenReset								55			//Fl_St204_StationenReset		
#define Fl_St204_PlateTurnsOff							    56			//Fl_St204_Teller_drehen_aus	
#define Fl_E_Gateway_SPS_St302_FlexLink_BeforeFull			57

//#define Fl_St3_Conveyor_load								60
//#define Fl_St3_Conveyor_unload                            61

#define Fl_St4_B4_Inserter_down_Pos							81
#define Fl_St4_B4_Inserter_down_Neg							82
#define Fl_St4_Motor_fast_Pos								83
#define Fl_St4_Motor_fast_Neg								84

#define Fl_St4_Interval_SpecialFunction_On					85
#define Fl_St4_Interval_PoleCounter_On						86
#define Fl_St4_Interval_Crank_On							87
#define Fl_St4_Reset_Crank_Open								88
#define Fl_St4_Interval_ChangeArticle_On					89
#define Fl_Registers_fill_belt_ends_St4						90

#define Fl_St8_Parameter_umschalten                         100
#define Fl_St8_aus                                          101
#define Fl_St8_Start                                        102
#define Fl_St8_Messung_aus									112


//##  END_FLANKEN			Zeile nicht loeschen

//*****************************************************************
//***************  Konstanten für Zeitwerke  **********************
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
//                           Zeiten für Axis 1
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
//                           Zeiten für Teller
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
//                        Zeiten für Barcodescanner
//-----------------------------------------------------------------------------
#define T_Scanner_Control									60		//T_Scanner_Kontrolle			
#define T_Scanner_Reset										61		//T_Scanner_Reset				
#define T_Scanner_Start_after_Reset							62		//T_Scanner_Start_nach_Reset	
#define T_Scanner_WPC_InPosition                            63 		//T_Scanner_WT_eingelaufen   
#define T_Scanner_Delay_Start								64 		//T_Scanner_Start_verzoegern 


//-----------------------------------------------------------------------------
//                      Zeiten für Stand-By am Flex Link
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
//                     Zeiten für Stand-By an Baugruppen
//-----------------------------------------------------------------------------
#define T_St1_housing_StandBy								80
#define T_St1_housing_StandByOff							81
#define T_St1_housing_StandBy_ShowMessage					82

#define T_St4_StandBy_Meldung_anzeigen						90
#define T_St4_StandBy										91
#define T_St4_StandByAus									92
#define T_St4_Ref_Delay										93
#define T_St4_delay1									94
#define T_St4_delay2									95
#define T_St4_delay3									96
#define T_St4_Delay4									97
#define T_St4_delay104									98
#define T_St4_delay105									99
#define T_St4_delay106									100
#define T_delay_10                                      101
#define T_delay_11                                      102
#define T_delay_12                                      103
#define T_delay_13                                      104

//-----------------------------------------------------------------------------
//                        Zeiten für Baugruppen
//-----------------------------------------------------------------------------
#define T_St1_B1_housing_in_position						120
#define T_St1_Feeder_Error									121
#define T_St1_unload_timer									124

#define T_St2_B1_sensor_1_ok								125
#define T_St2_B2_sensor_2_ok								126
#define T_St2_check_max										127

#define T_St3_B1_sensor_1_ok								131
#define T_St3_check_max										132

#define T_St4_Delay_check_LS_B1								142
#define T_St4_Block_mounting								143
#define T_St4_Cutting_Terminal                              144
#define T_St4_ControlTime_Cutting							145

#define T_St7_B1_sensor_1_ok								171
#define T_St7_check_max										172

#define T_St8_PositionTime									180
#define T_St8_Alarm_reset						            181 
#define T_St8_Break_solved						            182
#define T_St8_Break_reached								    183
#define T_St8_Break_relaxed								    184
#define T_St8_MotorStandStill                               185
#define T_St8_Messung_bereit								186
#define T_St8_Messung_wiedereinschalten_sperren				187
#define T_St8_test_delay									188
//-----------------------------------------------------------------------------
//         Für die Fördertöpfe sind die Zeitwerke ab 200 Reserviert !!
//-----------------------------------------------------------------------------
#define T_St1_BF_ON										    200
#define T_St1_BF_OFF										201

#define T_St8_Stopuhr_Messwerte								298

#ifdef HVPruefung_vorhanden
	#define T_HV_Wartezeit_HV_ein							396
	#define T_HV_Pruefzeit									397
	#define T_HV_Pruef_Leerlaufbereich						398
	#define T_HV_Pruef_DCOffset								399
#endif

//##END_ZEITEN			Zeile nicht loeschen


//*****************************************************************
//***************  Konstanten für Schrittketten  ******************
//*****************************************************************

//##ANF_KETTEN			Zeile nicht loeschen

#define K_St201_MainProcess_Axis							 0
#define K_St1_housing_and_cover_insert			             1
#define K_St2_check_housing									 2
#define K_St3_Carrier_position_checking						 3

#define K_St4_MainProcess									 4

#define K_St5_Pin_pressing									 5
#define K_St7_Carrier_position_checking						 7
#define K_St8_pressure_test									 8
#define K_St9_reject_parts_output							9
#define K_St10_good_parts_output							10

#define K_St4_PositionRad									 41
#define K_St4_EjectorPin									 42
#define K_St4_InsertPin										 43
#define K_St4_CuttingBelt									 44


#ifdef HVPruefung_vorhanden
	#define K_HV_Kalibrierung								55
#endif

//##END_KETTEN			Zeile nicht loeschen


//*****************************************************************
//***************  Konstanten für Zähler  *************************
//*****************************************************************

//##ANF_ZAEHLER			Zeile nicht loeschen
   
// #define Z_R1_Messungen								200

#define Z_St4_IntervalControl_Power						 2
#define Z_PoleCounter_interval_start					 9

#define Z_St4_Pin_miss									11
#define Z_St4_Error_Pin_miss							12
#define Z_St4_Actual_Counter_Cutting					13
#define Z_St4_Target_Counter_Cutting					14

#define Z_St8_zu_pruefende_Pole                         30


// #define Z_R1_Messungen									200
#define Z_Lock_Unload								210

//##END_ZAEHLER			Zeile nicht loeschen


// variable for st8
char St8_chr_Gutteil[10];	// st8 goodpart or reject
char St8_temp[MAX_PATH];

WORD St8_NESTNR;
WORD St8_BlockNr;
WORD St8_PolNr;

double Log_St8_Pin_beginning_in_degree_mm;
double Log_St8_last_pos_in_degree_mm;
double Log_St8_Difference_in_degree_mm;
double Log_St8_pos_in_degree_max_mm;
static double Log_St8_Difference_change_test_in_mm;
double Log_St8_force_Max; 
double Log_St8_Last_force;


//*****************************************************************
//*************  Variablen für die BDE-Kommuniktion  **************
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

bool E_EndPosition_Machine[MAX_SEQUENCES+1];		//E_Endstell_Maschine[MAXSKETTE+1];			// Endstellung Kolben für Maschine aus
bool SK_EndPosition_Machine[MAX_SEQUENCES+1];		//SK_Endstell_Maschine[MAXSKETTE+1];			// Endstellung Schrittkette für Maschine aus

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
//*************  Variablen für Stopuhr Function  ***************
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

// Für Diagnosezwecke, jedes einzelne Modul kann einen Fehlercode ausgeben
const BYTE MAXMODULEPROINSEL = 17;

struct TSBTInsel // Safetybridge Master
{
	unsigned short ID;				// Fortlaufende Nr der einzelnen Master start bei 0
	unsigned short IDSafeConf;		// In SafeConf vergebene Insel-Nummer
	unsigned short NumberOfModuls;	// Anzahl der Module inklusive LSPDO, MAX 17!
	unsigned short SatLPSDOSlave;	// Kommunikation zur nachfolgenden Insel (Satelliten-Nummer des LPSDO_slave)
	unsigned short GatewayBefore;	// Adresse der Gateways zum vorhergehenden
	unsigned short GatewayAfter;	// und zum nachfolgenden Bussystem
	bool EQ[33];					// Eingänge MAX 32
	bool EI[33];					// Ausgänge MAX 32

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
//*******************  Eingänge Hauptmaschinenteil ****************
//*****************************************************************

//**** Allgemeine Eingänge ****
bool E_PressureSwitch								= false;		//E_Druckwaechter
bool E_Button_ProcessObservationMode				= false;		//E_Zustimmtaster

// Eingänge vom Tasterpult
bool E_Button_MaOn									= false;		//E_TP_Maschine_ein		
bool E_Button_MaOff									= false;		//E_TP_Maschine_aus		
bool E_Button_Quit									= false;		//E_TP_Quittieren		
bool E_Button_AirOn									= false;		//E_TP_Luft_Ein_Aus		
bool E_Button_ConveyorOn							= false;		//E_TP_Vibr_Ein_Aus		
bool E_Button_TipMode								= false;		//E_TP_Tipptaster

bool E_Button_Only_Axis_Unload						= false;

// Eingänge am Maschinenrahmen
bool E_Key_311										= false;		//E_Schluessel_311
bool E_Print_Label									= false;		//E_Etikett_drucken				
bool E_Unload_Machine								= false;		//E_Maschine_leerfahren			
bool E_Bridge_StandByPosition						= false;		//E_Wartestellung_ueberbruecken

//**** Eingänge für Doppel Achse ****
bool E_St201_B1_4_SwivelUnit_in_front				= false;		//E_St201_B1_4_Schwenkeinheit_vorne	
bool E_St201_B1_2_SwivelUnit_back					= false;		//E_St201_B1_2_Schwenkeinheit_hinten	
bool E_St201_B4_WPC_InPosition						= false;		//E_St201_B4_Nest_eingelaufen		
bool E_St201_B5_WPC_InPosition						= false;		//E_St201_B5_Nest_eingelaufen        
bool E_St302_B1_FB_voll								= false;		//E_St302_B1_FB_voll	
bool E_Axis1_Controller_STO_Active					= false;
bool E_Axis2_Controller_STO_Active					= false;

//**** Eingänge für Flex-Link Band ****
bool E_St301_B2_AxisProtector_in_front				= false;		//E_St301_B2_Achsenschoner_vorfahren	
bool E_St301_B3_AxisProtector_in_front				= false;		//E_St301_B3_Achsenschoner_vorfahren	

//**** Eingänge zur Kommunikation zwischen den Teilen ***
bool E_Gateway_following_SPS_Enable_Conveyor		= false;	//<- Freigabe der Vibratoren von folgender SPS empfangen			E_Gateway_folgende_SPS_Freigabe_Vibr		    
bool E_Gateway_following_SPS_Quit					= false;	//<- E_TP_Quittieren von folgender SPS empfangen					E_Gateway_folgende_SPS_Enstperren              
bool E_Gateway_following_SPS_Unloaded				= false;	//<- Maschine leergefahren von folgender SPS empfangen				E_Gateway_folgende_SPS_leergefahren            
bool E_Gateway_following_SPS_St302_FlexLink_Run		= false;	//<- Zwischenförderband läuft von folgender SPS empfangen			E_Gateway_folgende_SPS_St302_FlexLink_laeuft   
bool E_Gateway_before_SPS_Enable_Conveyor		    = false;	//<- Freigabe der Vibratoren von vorheriger SPS empfangen			E_Gateway_vorherige_SPS_Freigabe_Vibr		    
bool E_Gateway_before_SPS_Quit						= false;	//<- E_TP_Quittieren von vorheriger SPS empfangen					E_Gateway_vorherige_SPS_Entsperren			    
bool E_Gateway_before_SPS_Unloaded					= false;	//<- Maschine leergefahren von vorheriger SPS empfangen				E_Gateway_vorherige_SPS_leergefahren		    
bool E_Gateway_before_SPS_St302_FlexLink_full		= false;	//<- Verbindungsförderband voll von vorheriger SPS empfangen		E_Gateway_vorherige_SPS_St302_FlexLink_voll	

// Umlaufförderband läuft von vorheriger SPS empfangen und an folgende Weiterleiten
bool M_Gateway_St301_FlexLink_Run                = false;	

//*****************************************************************
//*******************   Stations bezogen  *************************
//*****************************************************************

//Station 1
bool E_St1_B1_4_housing_presser_in_front				 = false;
bool E_St1_B1_2_housing_presser_back					 = false;
bool E_St1_B2_4_fixture_presser1_down					 = false;
bool E_St1_B2_2_fixture_presser1_up						 = false;
bool E_St1_B3_4_fixture_presser2_down					 = false;
bool E_St1_B3_2_fixture_presser2_up						 = false;

bool E_St1_B1_housing_in_position						 = false;
bool E_St1_B2_housing_channel_empty						 = false;
bool E_St1_B3_housing_channel_full						 = false;

//Station 2
bool E_St2_B1_housing_flange_checking					 = false;
bool E_St2_B2_housing_checking							 = false;

//Station 3
bool E_St3_B1_fixture_checking							 = false;

//Station 4
bool E_St4_B1_4_Belt_crushing_in_front					 = false; //E_St4_B1_4_Belt_crushing_in_front
bool E_St4_B1_2_Belt_crushing_back						 = false; //E_St4_B1_2_Belt_crushing_back

bool E_St4_B1_Pin_available								 = false; //E_St4_B1_pin_in_position(new)
bool E_St4_B2_Ejector_back								 = false; //E_St4_B3_pin_separating_motor_position_checking
bool E_St4_B5_rapid_clamping_system_closed				 = false; //E_St4_B2_pin_guiding_mechanism_in_position	
bool E_St4_B3_Inserter_up								 = false; //E_St4_B4_pin_pressing_motor_position_checking 
bool E_St4_B4_Inserter_down								 = false; //E_St4_B5_inserter_down	
bool E_St4_B4_Inserter_down_bus							 = false; //E_St4_B5_inserter_down	
bool E_St4_B6_Inserter_down								 = false; //E_St4_B6_inserter_down

//Station 5
bool E_St5_B1_4_pin_presser_down						= false;
bool E_St5_B1_2_pin_presser_up							= false;

//Station 7
bool E_St7_B1_fixture_checking							 = false;

//Station 8
//bool E_St8_B2_motor_position_checking					 = false;

//Station 9
bool E_St9_B1_4_reject_parts_ejector_in_front			= false;
bool E_St9_B1_2_reject_parts_ejector_back				= false;
bool E_St9_B2_4_fixture_presser1_down					= false;
bool E_St9_B2_2_fixture_presser1_up						= false;
bool E_St9_B3_4_fixture_presser2_down					= false;
bool E_St9_B3_2_fixture_presser2_up						= false;

//Station 10
bool E_St10_B1_4_good_parts_ejector_in_front			= false;
bool E_St10_B1_2_good_parts_ejector_back				= false;
bool E_St10_B2_4_fixture_presser1_down					= false;
bool E_St10_B2_2_fixture_presser1_up					= false;
bool E_St10_B3_4_fixture_presser2_down					= false;
bool E_St10_B3_2_fixture_presser2_up					= false;


//*****************************************************************
//*************  Ausgänge Hauptmaschinenteil  *********************
//*****************************************************************

//**** Allgemeine Ausgänge ****
// Ausgänge vom Tasterpult
bool A_LED_MaOn										= false;			//A_TP_LED_Maschine_ein	
bool A_LED_MaOff									= false;			//A_TP_LED_Maschine_aus	
bool A_LED_AirOn									= false;			//A_TP_LED_Luft			
bool A_LED_ConveyorOn								= false;			//A_TP_LED_Vibratoren	
bool A_Horn											= false;			//A_TP_Hupe				
bool A_LED_Quit										= false;			//A_TP_LED_Quittieren	
bool A_LED_TipMode									= false;			//A_TP_LED_Tipptaster	

// Ausgänge am Maschinenrahmen
bool A_LED_Unload_Machine							= false;			//A_LED_Maschine_leerfahren			
bool A_LED_Bridge_StandByPosition					= false;			//A_LED_Wartestellung_ueberbruecken
bool A_LED_Only_Axis_Unload							= false;			//A_LED_Wartestellung_ueberbruecken

bool A_All_ErrorLamp								= false;			//A_Stoerungslampe_Gesamt
bool A_Machine_Lamp									= false;
bool A_MainAir[MAX_MAINAIR+1];
bool A_LEDError[MAXANZSTAT+1];
bool A_MachineLightningOn							= false;

bool A_LED_Service_aktiv							= false;

//**** Ausgänge für Achse ****
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

//**** Ausgänge für Flex-Link Band ****
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

//Station 1
bool A_St1_M1_release_conveyor_belt					= false;
bool A_St1_A1_bowl_feeder							= false;
bool A_St1_A2_linear_feeder							= false;
bool A_St1_A3_linear_feeder							= false;
bool A_St1_Y1_blowing_air_for_feeder				= false;
//bool A_St1_A3_Freigabe_LF							= false;  // +1-M3

//Station 4
bool A_St4_Start_Coiler								= false;
bool A_St4_Controller_On_Coiler						= false;

//Station 8
bool A_St8_A1_Enable_BF								= false;		
bool A_St8_A2_Enable_LC								= false;
bool A_St8_A3_Enable_Storage						= false;
bool A_St8_Y1_BlastAir_BF                           = false;
bool A_St8_LED_filling_Conveyor                     = false;
bool A_St8_LED_unload_Conveyor                      = false;

bool A_St8_Messung_aktiv							= false;
bool A_St8_Range_Channel_1							= false;



//****   Ausgänge zur Kommunikation zwischen den Teilen
// TODO: Zusätzliche Ausgänge für Gateway deklarieren.
// bool A_Gateway_vorherige_SPS... = false;
// bool A_Gateway_folgende_SPS...  = false;

//*****************************************************************
//*******************   Stations bezogen  *************************
//*****************************************************************
// Alle Ausgände für die Zylinder werden in dieser Struktur definiert
struct TA
{

// Ausgänge für Achse
bool St201_Y1_4_SwivelUnit_forward;
bool St201_Y1_2_SwivelUnit_backward;

// Ausgänge für Flex-Link Band
bool St301_Y1_4_AxisProtector_forward;
bool St301_Y1_2_AxisProtector_forward;

// Station 1
bool St1_Y1_4_housing_presser_forward;
bool St1_Y1_2_housing_presser_backward;
bool St1_Y2_4_fixture_presser1_downward;
bool St1_Y2_2_fixture_presser1_upward;
bool St1_Y3_4_fixture_presser2_downward;
bool St1_Y3_2_fixture_presser2_upward;

// Station 4
bool St4_Y1_2_Belt_crushing_backward;
bool St4_Y1_4_Belt_crushing_forward;

// Station 5
bool St5_Y1_4_pin_presser_downward;
bool St5_Y1_2_pin_presser_upward;

// Station 9
bool St9_Y1_4_reject_parts_ejector_forward;
bool St9_Y1_2_reject_parts_ejector_backward;
bool St9_Y2_4_fixture_presser1_downward;
bool St9_Y2_2_fixture_presser1_upward;
bool St9_Y3_4_fixture_presser2_downward;
bool St9_Y3_2_fixture_presser2_upward;

//Station 10
bool St10_Y1_4_good_parts_ejector_forward;
bool St10_Y1_2_good_parts_ejector_backward;
bool St10_Y2_4_fixture_presser1_downward;
bool St10_Y2_2_fixture_presser1_upward;
bool St10_Y3_4_fixture_presser2_downward;
bool St10_Y3_2_fixture_presser2_upward;

};
struct TA A;

//*****************************************************************
//********  Sondersachen für den jeweiligen Maschinentyp  *********
//*****************************************************************

#ifdef Scanner_RFID_PN
	#ifndef Menue_programm
		#include "PF_RFID.h"
		#include "PF_RFID_CH.h"
		#include "ScannerPN.h"
	#endif 
#endif

//GGX begin
//*****************************************************************
//********  Sondersachen für den jeweiligen Maschinentyp  *********
//*****************************************************************
//Variablen für Kraftmessung an Prüfpatrone
bool St8_TeilOK                                 = false;
bool St8_TeilOK_Intervall                       = false;
double St8_actual_Pos_in_degree		= 0.0;	// aktuelle Position der Welle in Grad
double St8_actual_Pos_in_degree_mm	= 0.0;	// aktueller Weg in mm
double St8_actual_force				= 0.0;	// aktuelle Kraft in N
double St8_last_pos_in_degree		= 0.0;	// letzter Weg der letzten Prüfung in Grad
double St8_last_pos_in_degree_mm	= 0.0;	// letzter Weg der letzten Prüfung in mm
double St8_Last_force				= 0.0;	// letzte Kraft der letzten Prüfung in N
double St8_force_Max				= 0.0;	// max. Kraft der letzten Prüfung aufgetreten ist
double St8_pos_in_degree            = 0.0;
double St8_pos_in_degree_max		= 0.0;	// max. Weg der letzten Prüfung in Grad 
double St8_pos_in_degree_max_mm		= 0.0;	// max. Weg der letzen Prüfung in mm
double St8_pos_in_degree_max_in_mm	= 0.0;
double St8_Pin_beginning_in_degree			= 0.0;	// Stiftanfang in Grad
double St8_Pin_beginning_in_degree_mm		= 0.0;	// Stiftanfang in mm
double St8_Stift_Anfposition	= 0.0;	// Stiftanfang in Grad
double St8_Difference_in_degree_mm			= 0.0;	// Weg zwischen Stiftanfang und letzter Weg in mm
double St8_Max_test_Pos_in_degree_mm		= 0.0;	// max. der nach der Prüfung gefahren wurde (überschwingen) in mm
double St8_Difference_change_test_in_mm	= 0.0;	// Differenz zwischen letzter Weg und dem Überschwinger in mm
//double d_St8_pos_in_degree_in_mm                      = 0.0;
//double d_St8_pos_in_degree_min_in_mm                  = 0.0;
//double d_St8_target_pos                   = 0.0;
double St8_target_pos						= 0.0;

#define MaxMessungen 10

typedef struct
{
	double Stiftanfang;
	double Stiftanfang_mm;
	double Kraft_max;
	double Weg_max;
	double Weg_max_mm;
	double Ausdrueck_Weg_mm;
	bool Gutteil;
}TMessdaten;		// Daten-Struktur-Typ
TMessdaten St8_Messung[MaxMessungen];

#define MAXMESSUNGEN20NPRUEFUNG 1000
struct TMesswerte20NPruefung
{
	bool StiftanfangGefunden;
	bool LetztePruefkraftGefunden;
	// -5 Gutteil
	// -6 Kraft an falscher Position aufgetreten
	// -7 Prüfdruck nicht erreicht
	// -8 Max. zul. Prüfdruck überschritten
	// -9 max. Ausdrückweg überschritten
	// -10 max. Ausdrückweg nach der Prüfung überschritten
	//     Motor eventuell überschwungen
	int Prueffehler;

	int AnzahlMessungen;
	char PfadDateiName[200];

	char Zeit[MAXMESSUNGEN20NPRUEFUNG][50];
	double IstPositionMM[MAXMESSUNGEN20NPRUEFUNG];
	double IstPosition[MAXMESSUNGEN20NPRUEFUNG];
	double SollPosition[MAXMESSUNGEN20NPRUEFUNG];
	double AktuelleKraft[MAXMESSUNGEN20NPRUEFUNG];
	int Parametersatz[MAXMESSUNGEN20NPRUEFUNG];
	int StatusSchrittkette[MAXMESSUNGEN20NPRUEFUNG];
	double Pruefkraft[MAXMESSUNGEN20NPRUEFUNG];
	double StiftanfangMM[MAXMESSUNGEN20NPRUEFUNG];
	double LetztePruefkraft[MAXMESSUNGEN20NPRUEFUNG];
	int TeilInfo[MAXMESSUNGEN20NPRUEFUNG];
	int Pol[MAXMESSUNGEN20NPRUEFUNG];
	int Block[MAXMESSUNGEN20NPRUEFUNG];
	int WT[MAXMESSUNGEN20NPRUEFUNG];
	char Baugruppe[MAXMESSUNGEN20NPRUEFUNG][20];
	double DifferenzMM[MAXMESSUNGEN20NPRUEFUNG];
};

TMesswerte20NPruefung St8_20N_Messdaten;

//GGX end

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

	// Größe der Arrays der Variablen die zu den TCP Modulen übertragen werden sollen einstellen 
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
		// Variablen für dieKommunikation deklarieren
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
		//Eingänge
		BYTE EB_PN_Siemens_IO_Data[4];
		BYTE EB_PN_Siemens_Data[28];
		//Ausgänge
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
//     Bedeutet: Bool´sch Variable die nur 1 Bit belegt
// Diese Variablen werden automatisch eingelesen und angezeigt
// sie brauchnen nicht mit OnlVarEintrag eingetragen werden!!
// !Achtung die Bemerkungen mit # müssen stehen bleiben

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

// Merker für Freigaben
unsigned _____Variablen_Freigaben___________:1;
unsigned OutputEn:1;
unsigned MaStepEn:1;		//SKFrei
unsigned PressureAirEn:1;
unsigned ConveyorEn:1;
unsigned SafetyDoorEn:1;
unsigned MaSingleStepSwitch:1;
unsigned Bridge_SingleStepMode:1;
unsigned Quit_by_SingleStepMode:1;

// Merker für Stoerung Maschine aus
unsigned _____Variablen_Stoerung_Aus________:1;
unsigned Reset_Stations_ControlTime:1;
unsigned MaStop:1;
unsigned MaOff_pressed:1;
unsigned General_Error_found:1;
unsigned Error_IBS:1;
unsigned Error_AirPressure:1;
unsigned Error_Marker_OK:1;

// Merker für Endstellungen
unsigned _____Variablen_Endstellung_________:1;
unsigned EndPos_SK_Machine:1;
unsigned EndPos_K_Machine:1;
unsigned EndPos_SK_DriveUnits:1;
unsigned EndPos_K_DriveUnits:1;
unsigned EndPosition_Machine:1;
unsigned MaEndPosition_Error:1;
unsigned EndPos_K_DriveUnits_Error:1;

// Merker für Achse
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

// Merker für BDE
unsigned _____Variablen_BDE_________________:1;
unsigned Switch_Off_BDE:1;
unsigned ChangeArticle_PC:1;
unsigned Change_WPC:1;								//Nester_wechseln

// Maschinenspezifische Merker
unsigned _____Variablen_Stationsbezogen_____:1;
unsigned _____Station_1_____________________:1;
unsigned St1_conveyor_load:1;						
unsigned St1_conveyor_unload:1;							

unsigned _____Station_4_____________________:1;
unsigned St4_ejector_in_front:1;
unsigned St4_Error_Cutting:1;
unsigned St4_Error_belt:1;
unsigned St4_PositionRad_fast:1;
unsigned St4_Ejector_fast:1;
unsigned St4_Inserter_fast:1;
unsigned St4_all_Motors_fast:1;
unsigned St4_Complete_in_EndPosition:1;
unsigned _____Station_4_Ejector_________:1;
unsigned St4_Ejector_Works:1;
unsigned St4_Ejector_Ready:1;
unsigned St4_Ejector_ZeroPosition:1;
unsigned St4_Ejector_InPosition:1;
unsigned St4_Ejector_Error:1;
unsigned _____Station_4_PositionRad_______:1;
unsigned St4_PositionRad_Works:1;
unsigned St4_PositionRad_Ready:1;
unsigned St4_PositionRad_ZeroPosition:1;
unsigned St4_PositionRad_InPosition:1;
unsigned St4_PositionRad_Error:1;
unsigned _____Station_4_Inserter_________:1;
unsigned St4_Inserter_Works:1;
unsigned St4_Inserter_Ready:1;
unsigned St4_Inserter_ZeroPosition:1;
unsigned St4_Inserter_InPosition:1;
unsigned St4_Inserter_Error:1;

unsigned St4_01_alternation:1;
unsigned St4_Pin_in_cave_available:1;
unsigned St4_Gurtende_erkannt:1;
unsigned St4_Block_mounting:1;
//unsigned St4_Pin_inserter_Jamed:1;
//

unsigned _____Station_8_____________________:1;
unsigned St8_Online:1;
unsigned St8_Save_all_measured_values:1;
unsigned St8_nur_Stifte_pruefen_Register2:1;
unsigned St8_Stift_Register2_nicht_eingedrueckt:1;
unsigned St8_Detaillierte_Messwerte_speichern:1;
unsigned St8_Messdaten_speichern:1;
unsigned Pruefer_einrichten:1;
unsigned St8_test_value_save:1;
unsigned Pruefung_20N_Stopp_bei_Ausschuss:1;

unsigned _____EPHASE________________________:1;
unsigned All_Stations_without_material :1;
unsigned St1_without_material:1; //St1_ohne_Teil
unsigned St2_without_material:1;
unsigned St3_without_material:1;
unsigned St4_without_material:1;
unsigned St5_without_material:1;
unsigned St7_without_material:1;
unsigned St8_without_material:1;						//St8_ohne_Teil
unsigned St8_without_sensor:1;
unsigned St9_without_material:1;
unsigned St10_without_material:1;


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

BYTE St4_Ejector_Positioning_Block;
BYTE St4_PositionRad_Positioning_Block;
BYTE St4_Inserter_Positioning_Block;

};
struct TM_ M_;


//*****************************************************************
//*************  Remanente Merker  ********************************
//*****************************************************************

// Remanente Merker müssen für die Anzeige mit der Function
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
bool Unload_Turntable;
bool Machine_Unloaded;
bool Machine_Unloaded_in_EndPos;
double Sollpositionswert[20];

// Merker für Achse
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
//Article Type
bool ArticleType_Male;

// Station 1
bool St1_01_B1_alternation;
bool St1_01_B2_alternation;
bool St1_01_B3_alternation;
bool St1_Unloaded;

// Station 2
bool St2_01_B1_alternation;
bool St2_01_B2_alternation;

// Station 3
bool St3_01_B1_alternation;

// Station 4
bool St4_01_B1_alternation;
bool St4_01_B2_alternation;
bool St4_01_B3_alternation;
bool St4_01_B4_alternation;

bool St4_without_light_barrier_control;
bool St4_IntervalControl_Start_Power;

WORD St4_PositionRad_ActualPosition;
WORD St4_PositionRad_TargetPosition;

WORD St4_Target_Counter_Cutting;                           // max. Wert zum Stanzen
WORD St4_Actual_Counter_Cutting;                            // akt. Wert zum Stanzen
WORD St4_Cuttingtests;
WORD APCI_3120_INPUTS_WORD;

bool Special_only_St4_equip;
bool Special_IntervalPrg_start;

// Station 7
bool St7_01_B1_alternation;

// Station 8
bool St8_01_B1_alternation;
bool St8_01_B2_alternation;

// Station 10
bool ArticleType_good;

//--------------------------------------------
bool TestLoad_10N;
bool St8_without_correct_start_pos;
double St8_Pin_beginning_Pos_average;
bool St8_Ausschuss_Pruefintervall;
bool Stiftpruefung_immer_aktiv;

bool Pruefkraft_10N;
bool Intervallpruefung_gestartet;
bool Artikel_Alt_RN;

bool St8_Ausschussquote_sperren;
WORD Vorgabe_Pruefzyklen;
WORD Vorgabe_Ausschussquote;
WORD St8_Pruefzyklen;
WORD St8_Ausschussquote;
WORD St8_CounterNoPole;


//***  Packmodul remanente Variablen  ***
//TVerpack Verpack;					// Einstellvariable
//TVerpack BDEVerpackung;			// Einstellvariable

//Hauptmaschinenspezifische Merker
double AN_Sensor;
double AN_Sensor_Min;
double AN_Sensor_Max;
};
struct TM M;//  remanente Merker z.b. M.Start[1]

//
//
#ifndef Menue_programm
#include "cme.h"
CCME CME;
#endif


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
	// Der Sicherheitsschlüssel abgefragt
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

	OnlineVarEintragen()		altes Fenster "Online Einträge"
	OnlineVarEndstellung()		neues Fenster "Endstellung" dort kann man die Variablen nur lesen nicht ändern!
	OnlineVarLaufzeiten()		neues Fenster "Laufzeiten"
	OnlineVarStationEinAus()	neues Fenster "Station Ein/Aus" (kleines Fenster)

	Die Übergabewerte sind die gleichen wie bei der alten Funktion "OnlineVarEintragen".
	Man kann wie vorher alles in die "Online Einträge" eintragen. Die weiteren Funktionen
	dienen allein zur Übersichtlichkeit.
*/
		
		
	char buf[200];
	char buf1[200];
	char buf2[200];

	// Texte für remanente Variablen und sonstigen Variablen
	// die im Fenster Einträge angezeigt werden sollen

	// Stationen Ein
    // Max. 60 Zeichen      1.......10........20........30........40........50........60	
	OnlineVarStationEinAus("Station  1 On									",1,&M.StationEin[MaPart1][1]);
	OnlineVarStationEinAus("Station  2 On									",1,&M.StationEin[MaPart1][2]);
	OnlineVarStationEinAus("Station  3 On									",1,&M.StationEin[MaPart1][3]);
	OnlineVarStationEinAus("Station  4 On									",1,&M.StationEin[MaPart1][4]);
	OnlineVarStationEinAus("Station  5 On									",1,&M.StationEin[MaPart1][5]);
	OnlineVarStationEinAus("Station  7 On									",1,&M.StationEin[MaPart1][7]);
	OnlineVarStationEinAus("Station  8 On									",1,&M.StationEin[MaPart1][8]);
	OnlineVarStationEinAus("Station  9 On									",1,&M.StationEin[MaPart1][9]);
	OnlineVarStationEinAus("Station  10 On									",1,&M.StationEin[MaPart1][10]);


	OnlineVarEintragen("E_St1_B2_4_fixture_presser1_down							",1,&E_St1_B2_4_fixture_presser1_down);
	OnlineVarEintragen("E_St1_B2_2_fixture_presser1_up							",1,&E_St1_B2_2_fixture_presser1_up);
	OnlineVarEintragen("E_St1_B3_4_fixture_presser2_down							",1,&E_St1_B3_4_fixture_presser2_down);
	OnlineVarEintragen("E_St1_B3_2_fixture_presser2_up							",1,&E_St1_B3_2_fixture_presser2_up);

	// DriveUnit 1
	OnlineVarEintragen("----- DriveUnit 1 - AXIS 1 - STATION 201 -------------",1,&ANZEIGE);

	OnlineVarEintragen("DriveUnit 1 - Start[St. 1]							",1,&DriveUnit[DriveUnit1].Start[K_St1_housing_and_cover_insert]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 2]							",1,&DriveUnit[DriveUnit1].Start[K_St2_check_housing]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 3]							",1,&DriveUnit[DriveUnit1].Start[K_St3_Carrier_position_checking]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 4]	St4_MainProcess			",1,&DriveUnit[DriveUnit1].Start[K_St4_MainProcess]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 4]	St4_PositionRad			",1,&DriveUnit[DriveUnit1].Start[K_St4_PositionRad]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 4]	St4_EjectorPin			",1,&DriveUnit[DriveUnit1].Start[K_St4_EjectorPin]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 4]	St4_InsertPin			",1,&DriveUnit[DriveUnit1].Start[K_St4_InsertPin]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 4]	St4_CuttingBelt			",1,&DriveUnit[DriveUnit1].Start[K_St4_CuttingBelt]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 5]							",1,&DriveUnit[DriveUnit1].Start[K_St5_Pin_pressing]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 7]							",1,&DriveUnit[DriveUnit1].Start[K_St7_Carrier_position_checking]);
	OnlineVarEintragen("DriveUnit 1 - Start[St. 8]							",1,&DriveUnit[DriveUnit1].Start[K_St8_pressure_test]);
	OnlineVarEintragen("DriveUnit 1 - Start[St.9]							",1,&DriveUnit[DriveUnit1].Start[K_St9_reject_parts_output]);
	OnlineVarEintragen("DriveUnit 1 - Start[St.10]							",1,&DriveUnit[DriveUnit1].Start[K_St10_good_parts_output]);

	OnlineVarEintragen("",1,&ANZEIGE);
//	OnlineVarEintragen("DriveUnit 1 - Station_StandBy[St. 3]				",1,&DriveUnit[DriveUnit1].Station_StandBy[K_St3_Zufuehren_Einsetzen_Kontaktblock]);
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
	OnlineVarEintragen("Achse[Axis1].Ref_Kette								",4,&Achse[Axis1].Ref_Kette);


	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("Axis 2 - M_IFC_Servo                   ",1,&Achse[Axis2].M_IFC_Servo);
	OnlineVarEintragen("Axis 2 - M_Reset_Servo                 ",1,&Achse[Axis2].M_Reset_Servo);
	OnlineVarEintragen("Axis 2 - M_Alarm_Servo                 ",1,&Achse[Axis2].M_Alarm_Servo);
	OnlineVarEintragen("Axis 2 - M_Pos_StopPosition            ",1,&Achse[Axis2].M_Pos_StopPosition);
	OnlineVarEintragen("Axis 2 - M_Neg_StopPosition            ",1,&Achse[Axis2].M_Neg_StopPosition);
	OnlineVarEintragen("Axis 2 - M_CollectiveError_Servo       ",1,&Achse[Axis2].M_CollectiveError_Servo);
	OnlineVarEintragen("Axis 2 - M_Strom_Servo                 ",1,&Achse[Axis2].M_Strom_Servo);
	OnlineVarEintragen("Axis 2 - ReferenzPoint_OK				",1,&Achse[Axis2].ReferenzPoint_OK);
	OnlineVarEintragen("Axis 2 - M_ReferenzDrive_Finished		",1,&Achse[Axis2].M_ReferenzDrive_Finished);
	OnlineVarEintragen("Axis 2 - M_ReferenzDrive_Error			",1,&Achse[Axis2].M_ReferenzDrive_Error);
	OnlineVarEintragen("Axis 2 - M_ReferenzDrive_Start			",1,&Achse[Axis2].M_ReferenzDrive_Start);
	OnlineVarEintragen("Axis 2 - M_Error_ServoMotor_Rotates		",1,&Achse[Axis2].M_Error_ServoMotor_Rotates);
	OnlineVarEintragen("Axis 2 - M_ReferenzDrive_Swing_Positiv	",1,&Achse[Axis2].M_ReferenzDrive_Swing_Positiv);
	OnlineVarEintragen("Axis 2 - M_ReferenzDrive_Swing_Negativ	",1,&Achse[Axis2].M_ReferenzDrive_Swing_Negativ);
	OnlineVarEintragen("Axis 2 - Negativ_drive					",1,&Achse[Axis2].Negativ_drive);
	OnlineVarEintragen("Axis 2 - WPC_End						",1,&Achse[Axis2].WPC_End);
	OnlineVarEintragen("Axis 2 - Housing_End					",1,&Achse[Axis2].Housing_End);
	OnlineVarEintragen("Axis 2 - MW_Sollposition				",7,&Achse[Axis2].MW_Sollposition);


	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("Axis 2 - Position_verlassen				",1,&Achse[Axis2].Position_verlassen);
	OnlineVarEintragen("Axis 2 - Programm_start					",1,&Achse[Axis2].Programm_start);
	OnlineVarEintragen("Axis 2 - E_Ref_Switch					",1,&Achse[Axis2].E_Ref_Switch);
	OnlineVarEintragen("Axis 2 - Position_erreicht				",1,&Achse[Axis2].Position_erreicht);
	OnlineVarEintragen("Axis 2 - Fl_AxisRun						",1,&Achse[Axis2].Fl_AxisRun);
	OnlineVarEintragen("Axis 2 - A_Freigabe_Servo				",1,&Achse[Axis2].A_Freigabe_Servo);
	OnlineVarEintragen("Achse[Axis2].Ref_Kette					",4,&Achse[Axis2].Ref_Kette);
	OnlineVarEintragen("Achse[Axis2].Stoerung					",4,&Achse[Axis2].Stoerung);
	
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
	
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarEintragen("----- STATIONS ---------------------------------------",1,&ANZEIGE);
	OnlineVarEintragen("----- STATION 1 --------------------------------------",1,&ANZEIGE);
	OnlineVarEintragen("----- STATION 2 --------------------------------------",1,&ANZEIGE);
	OnlineVarEintragen("----- STATION 4 --------------------------------------",1,&ANZEIGE);
	OnlineVarEintragen("M.APCI_3120_INPUTS_WORD						",4,&M.APCI_3120_INPUTS_WORD);
	OnlineVarEintragen("E_St4_B4_Inserter_down",1,&E_St4_B4_Inserter_down);
	OnlineVarEintragen("E_St4_B1_Pin_available",1,&E_St4_B1_Pin_available);
	OnlineVarEintragen("M.St4_PositionRad_ActualPosition					",4,&M.St4_PositionRad_ActualPosition);
	OnlineVarEintragen("M.St4_PositionRad_TargetPosition				",4,&M.St4_PositionRad_TargetPosition);
	OnlineVarEintragen("M.St4_Actual_Counter_Cutting				",4,&M.St4_Actual_Counter_Cutting);
	OnlineVarEintragen("M.St4_Target_Counter_Cutting				",4,&M.St4_Target_Counter_Cutting);

	
	
	OnlineVarEintragen("----- STATION 8 --------------------------------------",1,&ANZEIGE);
	OnlineVarEintragen("M.St8_Pruefzyklen						",4,&M.St8_Pruefzyklen);
	OnlineVarEintragen("M.St8_Ausschussquote					",4,&M.St8_Ausschussquote);
	OnlineVarEintragen("M.Vorgabe_Pruefzyklen					",4,&M.Vorgabe_Pruefzyklen);
	OnlineVarEintragen("M.Vorgabe_Ausschussquote				",4,&M.Vorgabe_Ausschussquote);

	OnlineVarEintragen("----- Stiftprüfung allgemein ---------------",1,&ANZEIGE);
 	OnlineVarEintragen("M.St8_CounterNoPole				",4,&M.St8_CounterNoPole);
	
    OnlineVarEintragen("A_St8_Messung_aktiv									",1,&A_St8_Messung_aktiv);
 	OnlineVarEintragen("",1,&ANZEIGE);
    OnlineVarEintragen("----- St.8 Stiftpruefung -----------------------------",1,&ANZEIGE);
    OnlineVarEintragen("St8_20N_Messdaten.Prueffehler					",3,&St8_20N_Messdaten.Prueffehler);


	
    OnlineVarEintragen("St8 without correct start pos						",1,&M.St8_without_correct_start_pos);
    OnlineVarEintragen("St8_Pin_beginning_Pos_average						",7,&M.St8_Pin_beginning_Pos_average);
    OnlineVarEintragen("St8_TeilOK											",1,&St8_TeilOK);
    OnlineVarEintragen("St8_actual_force									",7,&St8_actual_force);
    OnlineVarEintragen("St8_force_Max										",7,&St8_force_Max);
    OnlineVarEintragen("Achse[Axis2].Ist_pos_mm								",7,&Achse[Axis2].Ist_pos_mm);
    OnlineVarEintragen("St8_actual_Pos_in_degree							",7,&St8_actual_Pos_in_degree);
	OnlineVarEintragen("St8_actual pos in mm								",7,&St8_actual_Pos_in_degree_mm);
    OnlineVarEintragen("St8_pos_in_degree_max								",7,&St8_pos_in_degree_max);
    OnlineVarEintragen("St8_last_pos_in_degree								",7,&St8_last_pos_in_degree);
    OnlineVarEintragen("St8_Last_force										",7,&St8_Last_force);
    OnlineVarEintragen("St8_last_pos_in_degree_mm							",7,&St8_last_pos_in_degree_mm);
    OnlineVarEintragen("St8_last_target_pos									",7,&St8_target_pos);
	OnlineVarEintragen("St8_last Pin_beginning_in_degree					",7,&St8_Pin_beginning_in_degree);
    OnlineVarEintragen("St8_last Pin_beginning_in_degree_mm					",7,&St8_Pin_beginning_in_degree_mm);
    OnlineVarEintragen("St8_Difference_in_degree_mm							",7,&St8_Difference_in_degree_mm);
    OnlineVarEintragen("St8_Difference_change_test_in_mm					",7,&St8_Difference_change_test_in_mm);
    OnlineVarEintragen("St8_Max_test_Pos_in_degree_mm						",7,&St8_Max_test_Pos_in_degree_mm);

	


	

	OnlineVarEintragen("----- St.8 Stiftprüfung - letzte Messung -------------",1,&ANZEIGE);
    OnlineVarEintragen("St8_Messung[0].Stiftanfang							",7,&St8_Messung[0].Stiftanfang);
    OnlineVarEintragen("St8_Messung[0].Stiftanfang_mm						",7,&St8_Messung[0].Stiftanfang_mm);
    OnlineVarEintragen("St8_Messung[0].Kraft_max							",7,&St8_Messung[0].Kraft_max);
    OnlineVarEintragen("St8_Messung[0].Weg_max								",7,&St8_Messung[0].Weg_max);
    OnlineVarEintragen("St8_Messung[0].Weg_max_mm							",7,&St8_Messung[0].Weg_max_mm);
    OnlineVarEintragen("St8_Messung[0].Ausdrueck_Weg_mm						",7,&St8_Messung[0].Ausdrueck_Weg_mm);
    OnlineVarEintragen("St8_Messung[0].Gutteil								",1,&St8_Messung[0].Gutteil);
	OnlineVarEintragen("----- St.8 Stiftprüfung - 2. Messung -----------------",1,&ANZEIGE);
    OnlineVarEintragen("St8_Messung[1].Stiftanfang							",7,&St8_Messung[1].Stiftanfang);
    OnlineVarEintragen("St8_Messung[1].Stiftanfang_mm						",7,&St8_Messung[1].Stiftanfang_mm);
    OnlineVarEintragen("St8_Messung[1].Kraft_max							",7,&St8_Messung[1].Kraft_max);
    OnlineVarEintragen("St8_Messung[1].Weg_max								",7,&St8_Messung[1].Weg_max);
    OnlineVarEintragen("St8_Messung[1].Weg_max_mm							",7,&St8_Messung[1].Weg_max_mm);
    OnlineVarEintragen("St8_Messung[1].Ausdrueck_Weg_mm						",7,&St8_Messung[1].Ausdrueck_Weg_mm);
    OnlineVarEintragen("St8_Messung[1].Gutteil								",1,&St8_Messung[1].Gutteil);
	OnlineVarEintragen("----- St.8 Stiftprüfung - 3. Messung -----------------",1,&ANZEIGE);
    OnlineVarEintragen("St8_Messung[2].Stiftanfang							",7,&St8_Messung[2].Stiftanfang);
    OnlineVarEintragen("St8_Messung[2].Stiftanfang_mm						",7,&St8_Messung[2].Stiftanfang_mm);
    OnlineVarEintragen("St8_Messung[2].Kraft_max							",7,&St8_Messung[2].Kraft_max);
    OnlineVarEintragen("St8_Messung[2].Weg_max								",7,&St8_Messung[2].Weg_max);
    OnlineVarEintragen("St8_Messung[2].Weg_max_mm							",7,&St8_Messung[2].Weg_max_mm);
    OnlineVarEintragen("St8_Messung[2].Ausdrueck_Weg_mm						",7,&St8_Messung[2].Ausdrueck_Weg_mm);
    OnlineVarEintragen("St8_Messung[2].Gutteil								",1,&St8_Messung[2].Gutteil);
	OnlineVarEintragen("----- St.8 Stiftprüfung - 4. Messung -----------------",1,&ANZEIGE);
    OnlineVarEintragen("St8_Messung[3].Stiftanfang							",7,&St8_Messung[3].Stiftanfang);
    OnlineVarEintragen("St8_Messung[3].Stiftanfang_mm						",7,&St8_Messung[3].Stiftanfang_mm);
    OnlineVarEintragen("St8_Messung[3].Kraft_max							",7,&St8_Messung[3].Kraft_max);
    OnlineVarEintragen("St8_Messung[3].Weg_max								",7,&St8_Messung[3].Weg_max);
    OnlineVarEintragen("St8_Messung[3].Weg_max_mm							",7,&St8_Messung[3].Weg_max_mm);
    OnlineVarEintragen("St8_Messung[3].Ausdrueck_Weg_mm						",7,&St8_Messung[3].Ausdrueck_Weg_mm);
    OnlineVarEintragen("St8_Messung[3].Gutteil								",1,&St8_Messung[3].Gutteil);
	OnlineVarEintragen("----- St.8 Stiftprüfung - 5. Messung -----------------",1,&ANZEIGE);
    OnlineVarEintragen("St8_Messung[4].Stiftanfang							",7,&St8_Messung[4].Stiftanfang);
    OnlineVarEintragen("St8_Messung[4].Stiftanfang_mm						",7,&St8_Messung[4].Stiftanfang_mm);
    OnlineVarEintragen("St8_Messung[4].Kraft_max							",7,&St8_Messung[4].Kraft_max);
    OnlineVarEintragen("St8_Messung[4].Weg_max								",7,&St8_Messung[4].Weg_max);
    OnlineVarEintragen("St8_Messung[4].Weg_max_mm							",7,&St8_Messung[4].Weg_max_mm);
    OnlineVarEintragen("St8_Messung[4].Ausdrueck_Weg_mm						",7,&St8_Messung[4].Ausdrueck_Weg_mm);
    OnlineVarEintragen("St8_Messung[4].Gutteil								",1,&St8_Messung[4].Gutteil);
	OnlineVarEintragen("----- St.8 Stiftprüfung - 6. Messung -----------------",1,&ANZEIGE);
    OnlineVarEintragen("St8_Messung[5].Stiftanfang							",7,&St8_Messung[5].Stiftanfang);
    OnlineVarEintragen("St8_Messung[5].Stiftanfang_mm						",7,&St8_Messung[5].Stiftanfang_mm);
    OnlineVarEintragen("St8_Messung[5].Kraft_max							",7,&St8_Messung[5].Kraft_max);
    OnlineVarEintragen("St8_Messung[5].Weg_max								",7,&St8_Messung[5].Weg_max);
    OnlineVarEintragen("St8_Messung[5].Weg_max_mm							",7,&St8_Messung[5].Weg_max_mm);
    OnlineVarEintragen("St8_Messung[5].Ausdrueck_Weg_mm						",7,&St8_Messung[5].Ausdrueck_Weg_mm);
    OnlineVarEintragen("St8_Messung[5].Gutteil								",1,&St8_Messung[5].Gutteil);
	OnlineVarEintragen("----- St.8 Stiftprüfung - 7. Messung -----------------",1,&ANZEIGE);
    OnlineVarEintragen("St8_Messung[6].Stiftanfang							",7,&St8_Messung[6].Stiftanfang);
    OnlineVarEintragen("St8_Messung[6].Stiftanfang_mm						",7,&St8_Messung[6].Stiftanfang_mm);
    OnlineVarEintragen("St8_Messung[6].Kraft_max							",7,&St8_Messung[6].Kraft_max);
    OnlineVarEintragen("St8_Messung[6].Weg_max								",7,&St8_Messung[6].Weg_max);
    OnlineVarEintragen("St8_Messung[6].Weg_max_mm							",7,&St8_Messung[6].Weg_max_mm);
    OnlineVarEintragen("St8_Messung[6].Ausdrueck_Weg_mm						",7,&St8_Messung[6].Ausdrueck_Weg_mm);
    OnlineVarEintragen("St8_Messung[6].Gutteil								",1,&St8_Messung[6].Gutteil);
	OnlineVarEintragen("----- St.8 Stiftprüfung - 8. Messung -----------------",1,&ANZEIGE);
    OnlineVarEintragen("St8_Messung[7].Stiftanfang							",7,&St8_Messung[7].Stiftanfang);
    OnlineVarEintragen("St8_Messung[7].Stiftanfang_mm						",7,&St8_Messung[7].Stiftanfang_mm);
    OnlineVarEintragen("St8_Messung[7].Kraft_max							",7,&St8_Messung[7].Kraft_max);
    OnlineVarEintragen("St8_Messung[7].Weg_max								",7,&St8_Messung[7].Weg_max);
    OnlineVarEintragen("St8_Messung[7].Weg_max_mm							",7,&St8_Messung[7].Weg_max_mm);
    OnlineVarEintragen("St8_Messung[7].Ausdrueck_Weg_mm						",7,&St8_Messung[7].Ausdrueck_Weg_mm);
    OnlineVarEintragen("St8_Messung[7].Gutteil								",1,&St8_Messung[7].Gutteil);
	OnlineVarEintragen("----- St.8 Stiftprüfung - 9. Messung -----------------",1,&ANZEIGE);
    OnlineVarEintragen("St8_Messung[8].Stiftanfang							",7,&St8_Messung[8].Stiftanfang);
    OnlineVarEintragen("St8_Messung[8].Stiftanfang_mm						",7,&St8_Messung[8].Stiftanfang_mm);
    OnlineVarEintragen("St8_Messung[8].Kraft_max							",7,&St8_Messung[8].Kraft_max);
    OnlineVarEintragen("St8_Messung[8].Weg_max								",7,&St8_Messung[8].Weg_max);
    OnlineVarEintragen("St8_Messung[8].Weg_max_mm							",7,&St8_Messung[8].Weg_max_mm);
    OnlineVarEintragen("St8_Messung[8].Ausdrueck_Weg_mm						",7,&St8_Messung[8].Ausdrueck_Weg_mm);
    OnlineVarEintragen("St8_Messung[8].Gutteil								",1,&St8_Messung[8].Gutteil);
	OnlineVarEintragen("----- St.8 Stiftprüfung - 10. Messung ----------------",1,&ANZEIGE);
    OnlineVarEintragen("St8_Messung[9].Stiftanfang							",7,&St8_Messung[9].Stiftanfang);
    OnlineVarEintragen("St8_Messung[9].Stiftanfang_mm						",7,&St8_Messung[9].Stiftanfang_mm);
    OnlineVarEintragen("St8_Messung[9].Kraft_max							",7,&St8_Messung[9].Kraft_max);
    OnlineVarEintragen("St8_Messung[9].Weg_max								",7,&St8_Messung[9].Weg_max);
    OnlineVarEintragen("St8_Messung[9].Weg_max_mm							",7,&St8_Messung[9].Weg_max_mm);
    OnlineVarEintragen("St8_Messung[9].Ausdrueck_Weg_mm						",7,&St8_Messung[9].Ausdrueck_Weg_mm);
    OnlineVarEintragen("St8_Messung[9].Gutteil								",1,&St8_Messung[9].Gutteil);

	OnlineVarEndstellung("----- DriveUnit 1 - AXIS 1 - STATION 201 -----------",1,&ANZEIGE);
	OnlineVarEndstellung("DriveUnit 1 -E_EndPosition[St. 1]		",1,&DriveUnit[DriveUnit1].E_EndPosition[K_St1_housing_and_cover_insert]);
	OnlineVarEndstellung("DriveUnit 1 -E_EndPosition[St. 4]		",1,&DriveUnit[DriveUnit1].E_EndPosition[K_St4_MainProcess]);
	OnlineVarEndstellung("DriveUnit 1 -E_EndPosition[St. 5]		",1,&DriveUnit[DriveUnit1].E_EndPosition[K_St5_Pin_pressing]);
	OnlineVarEndstellung("DriveUnit 1 -E_EndPosition[St. 8]		",1,&DriveUnit[DriveUnit1].E_EndPosition[K_St8_pressure_test]);
	OnlineVarEndstellung("DriveUnit 1 -E_EndPosition[St. 9]		",1,&DriveUnit[DriveUnit1].E_EndPosition[K_St9_reject_parts_output]);
	OnlineVarEndstellung("DriveUnit 1 -E_EndPosition[St.10]		",1,&DriveUnit[DriveUnit1].E_EndPosition[K_St10_good_parts_output]);
	OnlineVarEndstellung("DriveUnit 1 - SK_EndPosition[St 1]		",1,&DriveUnit[DriveUnit1].SK_EndPosition[K_St1_housing_and_cover_insert]);
	OnlineVarEndstellung("DriveUnit 1 - SK_EndPosition[St 4]		",1,&DriveUnit[DriveUnit1].SK_EndPosition[K_St4_MainProcess]);
	OnlineVarEndstellung("DriveUnit 1 - SK_EndPosition[St 5]		",1,&DriveUnit[DriveUnit1].SK_EndPosition[K_St5_Pin_pressing]);
	OnlineVarEndstellung("DriveUnit 1 - SK_EndPosition[St 8]		",1,&DriveUnit[DriveUnit1].SK_EndPosition[K_St8_pressure_test]);
	OnlineVarEndstellung("DriveUnit 1 - SK_EndPosition[St 9]		",1,&DriveUnit[DriveUnit1].SK_EndPosition[K_St9_reject_parts_output]);
	OnlineVarEndstellung("DriveUnit 1 - SK_EndPosition[St10]		",1,&DriveUnit[DriveUnit1].SK_EndPosition[K_St10_good_parts_output]);

	// Polpositionswerte negativ
	//for (int x=0; x<=MAX_SEQUENCES; x++)
	//{
	//	sprintf(buf1,"DriveUnit 1 -E_EndPosition[%d]      ",x);
	//	sprintf(buf2,"DriveUnit 1 -SK_EndPosition[%d]     ",x);
	//	OnlineVarEndstellung(buf1,1,&DriveUnit[DriveUnit1].E_EndPosition[x]);
	//	OnlineVarEndstellung(buf2,1,&DriveUnit[DriveUnit1].SK_EndPosition[x]);
	//}


	OnlineVarEndstellung("",1,&ANZEIGE);
	OnlineVarEndstellung("----- ENDSTELLUNGEN MASCHINE -----------------------",1,&ANZEIGE);
	OnlineVarEndstellung("E_EndPosition_Machine [St. 1]				",1,&E_EndPosition_Machine	[K_St1_housing_and_cover_insert]);
	OnlineVarEndstellung("E_EndPosition_Machine [St. 4]				",1,&E_EndPosition_Machine	[K_St4_MainProcess]);
	OnlineVarEndstellung("E_EndPosition_Machine [St.4] ejector pin		",1,&E_EndPosition_Machine[K_St4_EjectorPin]);
	OnlineVarEndstellung("E_EndPosition_Machine [St.4] position pin		",1,&E_EndPosition_Machine[K_St4_PositionRad]);
	OnlineVarEndstellung("E_EndPosition_Machine [St.4] insert pin		",1,&E_EndPosition_Machine[K_St4_InsertPin]);
	OnlineVarEndstellung("E_EndPosition_Machine [St.4] cutting belt		",1,&E_EndPosition_Machine[K_St4_CuttingBelt]);
	OnlineVarEndstellung("E_EndPosition_Machine [St. 5]				",1,&E_EndPosition_Machine	[K_St5_Pin_pressing]);
	OnlineVarEndstellung("E_EndPosition_Machine [St. 8]				",1,&E_EndPosition_Machine	[K_St8_pressure_test]);
	OnlineVarEndstellung("E_EndPosition_Machine [St. 9]				",1,&E_EndPosition_Machine	[K_St9_reject_parts_output]);
	OnlineVarEndstellung("E_EndPosition_Machine [St.10]				",1,&E_EndPosition_Machine	[K_St10_good_parts_output]);
	OnlineVarEndstellung("",1,&ANZEIGE);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 1]				",1,&SK_EndPosition_Machine	[K_St1_housing_and_cover_insert]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 4]				",1,&SK_EndPosition_Machine	[K_St4_MainProcess]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St.4] ejector pin			",1,&SK_EndPosition_Machine[K_St4_EjectorPin]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St.4] position pin			",1,&SK_EndPosition_Machine[K_St4_PositionRad]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St.4] insert pin			",1,&SK_EndPosition_Machine[K_St4_InsertPin]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St.4] cutting belt			",1,&SK_EndPosition_Machine[K_St4_CuttingBelt]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 5]				",1,&SK_EndPosition_Machine	[K_St5_Pin_pressing]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 8]				",1,&SK_EndPosition_Machine	[K_St8_pressure_test]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St. 9]				",1,&SK_EndPosition_Machine	[K_St9_reject_parts_output]);
	OnlineVarEndstellung("SK_EndPosition_Machine[St.10]				",1,&SK_EndPosition_Machine	[K_St10_good_parts_output]);

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
	OnlineVarLaufzeiten("----- RUNTIME RESET ST.1 ----------------------------",1,&RunTimes_Reset_Station	[K_St1_housing_and_cover_insert]);
	OnlineVarLaufzeiten("St. 1 RunTime              (Gesamtzeit)			",5,&RunTime					[K_St1_housing_and_cover_insert][0]);
	OnlineVarLaufzeiten("St. 1 RunTime max									",5,&RunTime_max				[K_St1_housing_and_cover_insert][0]);
	OnlineVarLaufzeiten("St. 1 RunTime min									",5,&RunTime_min				[K_St1_housing_and_cover_insert][0]);
	OnlineVarLaufzeiten("St. 1 RunTime AxisOperation						",5,&RunTime					[K_St1_housing_and_cover_insert][1]);
	OnlineVarLaufzeiten("St. 1 RunTime AxisOperation max					",5,&RunTime_max				[K_St1_housing_and_cover_insert][1]);
	OnlineVarLaufzeiten("St. 1 RunTime AxisOperation min					",5,&RunTime_min				[K_St1_housing_and_cover_insert][1]);

	OnlineVarLaufzeiten("----- RUNTIME RESET ST.4 ----------------------------",1,&RunTimes_Reset_Station	[K_St4_MainProcess]);
	OnlineVarLaufzeiten("St. 4 RunTime              (Gesamtzeit)			",5,&RunTime					[K_St4_MainProcess][0]);
	OnlineVarLaufzeiten("St. 4 RunTime max									",5,&RunTime_max				[K_St4_MainProcess][0]);
	OnlineVarLaufzeiten("St. 4 RunTime min									",5,&RunTime_min				[K_St4_MainProcess][0]);
	OnlineVarLaufzeiten("St. 4 RunTime AxisOperation						",5,&RunTime					[K_St4_MainProcess][1]);
	OnlineVarLaufzeiten("St. 4 RunTime AxisOperation max					",5,&RunTime_max				[K_St4_MainProcess][1]);
	OnlineVarLaufzeiten("St. 4 RunTime AxisOperation min					",5,&RunTime_min				[K_St4_MainProcess][1]);
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarLaufzeiten("St.4 put out drive for								",5,&RunTime					[K_St4_EjectorPin][1]);
	OnlineVarLaufzeiten("St.4 put out drive for								",5,&RunTime_max				[K_St4_EjectorPin][1]);
	OnlineVarLaufzeiten("St.4 put out drive for								",5,&RunTime_min				[K_St4_EjectorPin][1]);
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarLaufzeiten("St.4 Inserter 0-120° (ejector Start)				",5,&RunTime					[K_St4_MainProcess][2]);
	OnlineVarLaufzeiten("St.4 Inserter 0-120° (ejector Start)				",5,&RunTime_max				[K_St4_MainProcess][2]);
	OnlineVarLaufzeiten("St.4 Inserter 0-120° (ejector Start)				",5,&RunTime_min				[K_St4_MainProcess][2]);
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarLaufzeiten("St.4 Inserter 0-240° (EnableDriveUnit)				",5,&RunTime					[K_St4_MainProcess][3]);
	OnlineVarLaufzeiten("St.4 Inserter 0-240° (EnableDriveUnit)				",5,&RunTime_max				[K_St4_MainProcess][3]);
	OnlineVarLaufzeiten("St.4 Inserter 0-240° (EnableDriveUnit)				",5,&RunTime_min				[K_St4_MainProcess][3]);
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarLaufzeiten("St.4 WartingTime ejector (steht vorne)				",5,&RunTime					[K_St4_EjectorPin][2]);
	OnlineVarLaufzeiten("St.4 WartingTime ejector (steht vorne)				",5,&RunTime_max				[K_St4_EjectorPin][2]);
	OnlineVarLaufzeiten("St.4 WartingTime ejector (steht vorne)				",5,&RunTime_min				[K_St4_EjectorPin][2]);
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarLaufzeiten("St.4 put out drive back							",5,&RunTime					[K_St4_EjectorPin][3]);
	OnlineVarLaufzeiten("St.4 put out drive back							",5,&RunTime_max				[K_St4_EjectorPin][3]);
	OnlineVarLaufzeiten("St.4 put out drive back							",5,&RunTime_min				[K_St4_EjectorPin][3]);
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarLaufzeiten("St.4 positionwheel complete						",5,&RunTime					[K_St4_PositionRad][0]);
	OnlineVarLaufzeiten("St.4 positionwheel complete						",5,&RunTime_max				[K_St4_PositionRad][0]);
	OnlineVarLaufzeiten("St.4 positionwheel complete						",5,&RunTime_min				[K_St4_PositionRad][0]);
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarLaufzeiten("St.4 push in comlete								",5,&RunTime					[K_St4_InsertPin][0]);
	OnlineVarLaufzeiten("St.4 push in comlete								",5,&RunTime_max				[K_St4_InsertPin][0]);
	OnlineVarLaufzeiten("St.4 push in comlete								",5,&RunTime_min				[K_St4_InsertPin][0]);
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarLaufzeiten("St.4 put out comlete								",5,&RunTime					[K_St4_EjectorPin][0]);
	OnlineVarLaufzeiten("St.4 put out comlete								",5,&RunTime_max				[K_St4_EjectorPin][0]);
	OnlineVarLaufzeiten("St.4 put out comlete								",5,&RunTime_min				[K_St4_EjectorPin][0]);
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarLaufzeiten("St.4 cutting belt compelte							",5,&RunTime					[K_St4_CuttingBelt][0]);
	OnlineVarLaufzeiten("St.4 cutting belt compelte max						",5,&RunTime_max				[K_St4_CuttingBelt][0]);
	OnlineVarLaufzeiten("St.4 cutting belt compelte min						",5,&RunTime_min				[K_St4_CuttingBelt][0]);
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarLaufzeiten("St.5 press pin compelte							",5,&RunTime					[K_St5_Pin_pressing][0]);
	OnlineVarLaufzeiten("St.5 press pin compelte max						",5,&RunTime_max				[K_St5_Pin_pressing][0]);
	OnlineVarLaufzeiten("St.5 press pin compelte min						",5,&RunTime_min				[K_St5_Pin_pressing][0]);
	OnlineVarEintragen("",1,&ANZEIGE);
	OnlineVarLaufzeiten("St.5 press pin axisoperation						",5,&RunTime					[K_St5_Pin_pressing][1]);
	OnlineVarLaufzeiten("St.5 press pin axisoperation max					",5,&RunTime_max				[K_St5_Pin_pressing][1]);
	OnlineVarLaufzeiten("St.5 press pin axisoperation min					",5,&RunTime_min				[K_St5_Pin_pressing][1]);
#endif

#ifdef VIEW_MinuteCycle	
	OnlineVarLaufzeiten("-------- ANTRIEB 1 ----------------------------------",1,&ANZEIGE);
	OnlineVarLaufzeiten("----- MINUTECYCLE RESET ST.4 - MainProcess ------",1,&RunTimes_Reset_Station	[K_St4_MainProcess]);
	OnlineVarLaufzeiten("St.4 MINUTECYCLE actual						",5,&MinuteCycle_actual	[K_St4_MainProcess][0]);
	OnlineVarLaufzeiten("St.4 MINUTECYCLE Max							",5,&MinuteCycle_max	[K_St4_MainProcess][0]);
	OnlineVarLaufzeiten("----- MINUTECYCLE RESET ST.4 - ejector pin ------",1,&RunTimes_Reset_Station	[K_St4_MainProcess]);
	OnlineVarLaufzeiten("St.4 MINUTECYCLE actual						",5,&MinuteCycle_actual	[K_St4_MainProcess][0]);
	OnlineVarLaufzeiten("St.4 MINUTECYCLE Max							",5,&MinuteCycle_max	[K_St4_MainProcess][0]);
	OnlineVarLaufzeiten("----- MINUTECYCLE RESET ST.4 - position pin ----",1,&RunTimes_Reset_Station	[K_St4_PositionRad]);
	OnlineVarLaufzeiten("St.4 MINUTECYCLE actual						",5,&MinuteCycle_actual	[K_St4_PositionRad][0]);
	OnlineVarLaufzeiten("St.4 MINUTECYCLE Max							",5,&MinuteCycle_max	[K_St4_PositionRad][0]);
	OnlineVarLaufzeiten("----- MINUTECYCLE RESET ST.4 - insert pin ------",1,&RunTimes_Reset_Station	[K_St4_InsertPin]);
	OnlineVarLaufzeiten("St.4 MINUTECYCLE actual						",5,&MinuteCycle_actual	[K_St4_InsertPin][0]);
	OnlineVarLaufzeiten("St.4 MINUTECYCLE Max							",5,&MinuteCycle_max	[K_St4_InsertPin][0]);
	OnlineVarLaufzeiten("----- MINUTECYCLE RESET ST.4 - cutting belt -----",1,&RunTimes_Reset_Station	[K_St4_CuttingBelt]);
	OnlineVarLaufzeiten("St.4 MINUTECYCLE actual						",5,&MinuteCycle_actual	[K_St4_CuttingBelt][0]);
	OnlineVarLaufzeiten("St.4 MINUTECYCLE Max							",5,&MinuteCycle_max	[K_St4_CuttingBelt][0]);
#endif 

#ifdef HVPruefung_vorhanden
	OnlineVarEintragen("----- Hochspannungsprüfung ---------------------------",1,&ANZEIGE);
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

	//OnlineVarEintragen("St4_PositionRad_TargetPosition					",4,&St4_PositionRad_TargetPosition);
	//OnlineVarEintragen("St4_PositionRad_ActualPosition						",4,&St4_PositionRad_ActualPosition);

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


