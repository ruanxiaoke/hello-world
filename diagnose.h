#ifndef _DIAGNOSE_H
#define _DIAGNOSE_H

#include"DTC.h"
#include"configuration.h"

#define DIAGNOSE_ONLINE 1
#define DIAGNOSE_OFFLINE 0

typedef enum
{
	UDS_FRAME,
	ONLY_COPY,
	FC_FRAME
}DIAG_RESPONE_MODE;

typedef enum
{
	invalidService=0x00,
	diagnosticSessionControl=0x10,
	ecuReset=0x11,
	securityAcces=0x27,
	testerPresent=0x3E,
	readDataByIdentifier=0x22,
	writeDataByIdentifier=0x2E,
	clearDiagnosticInformation=0x14,
	readDTCInformation=0x19,
	inputOutputCOntrolByIdentifier=0x2F,
	upgradeFirmware=0xBA,
	factoryTest=0xBB,
	navigation=0xBC
}DiagnosticServicesName_E;

typedef enum
{
	invalidSession=0x00,
	defaultSession=0x01,
	programSession=0x02,
	extendedDiagnosticSession=0x03,
	carltSession=0x70,
}DiagnosticSession_E;

typedef enum
{
	DENIED=0,
	ADMITTED=1
}DiagnosticSecurity_E;
typedef enum
{
	hardReset=0x01,
}EcuReset_E;

typedef enum
{
	requestSeed=0x01,
	sendSeed=0x02,
}SecurityAccessType_E;

typedef enum
{
	subFunctionNotSupported=0x12,
	incorrectMessageLength=0x13,
	conditionsNotCorrect=0x22,
	requestSequenceError=0x24,
	requestOutOfRange=0x31,
	securityAccessDenied=0x33,
	invalidKey=0x35,
	exceededNumberOfAttempts=0x36,
	requiredTimeDelayNotExpired=0x37,
	subfunctionNotSupportedInActiveSession=0x7e,
}NegativeResponeCode_E;

typedef enum
{
	ISO_15031_6DTCFormat=0x00,
	ISO_14229_1DTCFormat=0x01,
}DTCFormatIdentifier_E;

typedef enum
{
	invalidDataIdentifier=0x0000,
	ecuVersionNumberDataIdentifier=0xF189,
	configurationCalibration=0x0100,
	clearMaintain=0x0101,
	backlightLevel=0xF092,
	buzzer=0xF020,
	gages=0xF021,
	segmentDisplay=0xF022,
	Indicators=0xF024
}DID_E;

#pragma pack(1)

typedef struct
{
	u8 RequestServiceIdentifier;
	u8 SubFunctionParameter;
}RequestDiagnosticSessionControl_t;

typedef struct
{
	u8 RequestServiceIdentifier;
	u8 SubFunctionParameter;
}RequestEcuReset_t;

typedef struct
{
	u8 RequestServiceIdentifier;
	struct
	{
		u8 HighByte;
		u8 MidByte;
		u8 LowByte;
	}GroupOfDTC;
}RequestClearDianosticInformation_t;

typedef struct
{
	u8 RequestServiceIdentifier;
	u8 SubFunctionParameter;
	u8 DTCStatusMask;
}RequestReadDTCInformation_t;

typedef struct
{
	u8 RequestServiceIdentifier;
	u8 DataIdentifier[2];
}RequestReadDataByIdentifier_t;

typedef struct
{
	u8 RequestServiceIdentifier;
	u8 SecurityAccessType;
	u8 SecurityKey[4];
}RequestSecurityAcess_t;

typedef struct
{
	u8 RequestServiceIdentifier;
	u8 DataIdentifier[2];
	union
	{
		struct
		{
			u8 type;
			u8 level;
		}BacklightLevel;

		struct
		{
			u8 type;
			u8 sts;
		}Buzzer;

		struct
		{
			u8 type;
			u8 position;
		}Gages;

		struct
		{
			u8 type;
			u8 sts;
		}SegmentDisplay;

		struct
		{
			u8 led[4];
		}Indicators;
	}ControlOption;
}RequestInputOutputControlByIndentifier_t;

typedef struct
{
	u8 RequestServiceIdentifier;
	u8 DataIdentifier[2];
	u8 DataRecord[4];
}RequestWriteDataByIdentifier_t;

typedef struct
{
	u8 RequestServiceIdentifier;
	u8 SubFunctionParameter;
}RequestTesterPresent_t;

typedef struct
{
	u8 RequestServiceIdentifier;
	u8 SubFunctionParameter;
}RequestUpgradeFirmware_t;

typedef struct
{
	u8 RequestServiceIdentifier;
	u8 SubFunctionParameter;
	u8 data[5];
}RequestFactoryTest_t;

typedef struct
{
	u8 RequestServiceIdentifier;
	u8 SubFunctionParameter;
}RequestNavigation_t;


typedef union
{
		RequestDiagnosticSessionControl_t DiagnosticSessionControl;
		RequestEcuReset_t EcuReset;
		RequestClearDianosticInformation_t ClearDianosticInformation;
		RequestReadDTCInformation_t ReadDTCInformation;
		RequestReadDataByIdentifier_t ReadDataByIdentifier;
		RequestSecurityAcess_t SecurityAcess;
		RequestInputOutputControlByIndentifier_t InputOutputControlByIndentifier;
		RequestWriteDataByIdentifier_t WriteDataByIdentifier;
		RequestTesterPresent_t TesterPresent;
		RequestUpgradeFirmware_t UpgradeFirmwarel;
		RequestFactoryTest_t FactoryTest;
		RequestNavigation_t RequestNavigation;
}DiagnosticRequest_t;

typedef struct
{
	u8 PositiveResponseServiceID;
	u8 SubFunctionParameter;
	u8 P2Hibyte;
	u8 P2Lobyte;
	u8 P2extHibyte;
	u8 P2extLobyte;
}PositiveResponeDiagnosticSessionControl_t;

typedef struct
{
	u8 reserved[1];
}PositiveResponeEcuReset_t;

typedef struct
{
	u8 PositiveResponseServiceID;
}PositiveResponeClearDiagnosticInformation_t;

typedef union
{
	struct
	{
		u8 PositiveResponseServiceID;
		u8 ReportType;
		u8 DTCStatusMask;
		u8 DTCFormatIdentifier;
		u8 DTCCountHighByte;
		u8 DTCCountLowByte;
	}ReportNumberOfDTCByStatusMask;
	
	struct
	{
		u8 PositiveResponseServiceID;
		u8 ReportType;
		u8 DTCStatusAvailabilityMask;
		struct
		{
			u8 hig;
			u8 mid;
			u8 low;
			u8 status;
		}DTC[DTC_TYPE_MAX];
	}ReportDTCByStatusMask;
}PositiveResponeReadDTCInformation_t;

typedef union
{
	u32 word;
	struct
	{
		u16 TCU_fault:1;
		u16 EPS:1;
		u16 PassengerSeatBelt:1;
		u16 CRUISE:1;
		u16 PEPS:1;
		u16 ESC:1;
		u16 :1;
		u16 TPMS:1;
		u16 DRL:1;
		u16 ENGINEGUARD:1;
		u16 EPB:1;
		u16 :5;
		u16 reserved;
	}bit;
}configurationInfo_t;

typedef struct
{
	union
	{
		struct
		{
			u8 PositiveResponseServiceID;
			u8 DataIdentifier[2];
			u8 year;
			u8 month;
			u8 day;
			u8 hardver[2];
			u8 softver[2];
		}ECUVersionNumber;
		struct
		{
			u8 PositiveResponseServiceID;
			u8 DataIdentifier[2];
			configurationInfo_t info;
		}Configuration;
	}DID;
}PositiveResponeReadDataByIdentifier_t;

typedef union
{
	struct
	{
		u8 PositiveResponseServiceID;
		u8 SecurityAccessType;
		u8 securitySeed[4];
	}RequestSeed;
	struct
	{
		u8 PositiveResponseServiceID;
		u8 SecurityAccessType;
	}SendSeed;
}PositiveResponeSecurityAccess_t;

typedef struct
{
	u8 PositiveResponseServiceID;
	u8 DataIdentifier[2];
	u8 reserved;
}PositiveResponeInputOutputControlByIdentifier_t;

typedef struct
{
	u8 PositiveResponseServiceID;
	u8 DataIdentifier[2];
}PositiveResponeWriteDataByIdentifier_t;

typedef struct
{
	u8 PositiveResponseServiceID;
	u8 ZeroSubFunction;
}PositiveResponeTestPresent_t;

typedef struct
{
	u8 PositiveResponseServiceID;
	u8 SubFunctionParameter;
}PositiveResponeUpgradeFirmware_t;

typedef struct
{
	u8 PositiveResponseServiceID;
	u8 SubFunctionParameter;
}PositiveResponeFactoryTest_t;

typedef struct
{
	u8 PositiveResponseServiceID;
	u8 SubFunctionParameter;
}PositiveResponeNavigation_t;

typedef union
{
	PositiveResponeDiagnosticSessionControl_t DiagnosticSessionControl;
	PositiveResponeEcuReset_t EcuReset;
	PositiveResponeClearDiagnosticInformation_t ClearDiagnosticInformation;
	PositiveResponeReadDTCInformation_t ReadDTCInformation;
	PositiveResponeReadDataByIdentifier_t ReadDataByIdentifier;
	PositiveResponeSecurityAccess_t SecurityAccess;
	PositiveResponeInputOutputControlByIdentifier_t InputOutputControlByIdentifier;
	PositiveResponeWriteDataByIdentifier_t WriteDataByIdentifier;
	PositiveResponeTestPresent_t TestPresent;
	PositiveResponeUpgradeFirmware_t UpgradeFirmware;
	PositiveResponeFactoryTest_t FactoryTest;
	PositiveResponeNavigation_t Navigation;
}PositiveDiagnosticRespone_t;

typedef struct
{
	u8 NegativeResponseServiceID;
	u8 OriginalRequestServiceIdentifier;
	u8 NegativeResponeCode;
}NegativeDiagnosticRespone_t;

typedef union
{
	PositiveDiagnosticRespone_t PositiveDiagnosticRespone;
	NegativeDiagnosticRespone_t NegativeDiagnosticRespone;
}DiagnosticRespone_t;



typedef struct
{
	u16 DataIdentifier;
	union
	{
		struct
		{
			u8 type;
			u8 level;
		}BacklightLevel;

		struct
		{
			u8 type;
			u8 sts;
		}Buzzer;

		struct
		{
			u8 type;
			u8 position;
		}Gages;

		struct
		{
			u8 type;
			u8 sts;
		}SegmentDisplay;

		struct
		{
			u32 FuelLamp:1;
			u32 :1;
			u32 PassengerSafetyBeltLamp:1;
			u32 SRSLamp:1;
			u32 EPCLamp:1;
			u32 EPSLamp:1;
			u32 MILLamp:1;
			u32 ESPLamp:1;
			u32 DriveSafetyBeltLamp:1;
			u32 FrontFogLamp:1;
			u32 PositionLamp:1;
			u32 RearFogLamp:1;
			u32 TurnLeftLamp:1;
			u32 ParkingBrakeLamp:1;
			u32 OilPressureLamp:1;
			u32 HighBeamLamp:1;
			u32 EPBLamp:1;
			u32 TurnRightLamp:1;
			u32 BreakFailLamp:1;
			u32 ESP_OffLamp:1;
			u32 DoorOpenLamp:1;
			u32 TirePressureLamp:1;
			u32 ALSLamp:1;
			u32 MaintainLamp:1;
			u32 ABSLamp:1;
			u32 CruiseLamp:1;
			u32 DRLLamp:1;
			u32 TCULamp:1;
			u32 :1;
			u32 IMMO:1;
			u32 CoolantTemperatureLamp:1;
			u32 PEPSLamp:1;
		}Indicators;
	}ControlOption;
}IuputOutputControl_t;
#pragma pack()

extern u8 DiagnosticMode;
extern IuputOutputControl_t IuputOutputControl;
Status Diagnose(u8 *DiagnosticRequestbuf,u8 **p_DiagnosticResponebuf);


#endif
