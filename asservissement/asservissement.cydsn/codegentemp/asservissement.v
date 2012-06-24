// ======================================================================
// asservissement.v generated from TopDesign.cysch
// 05/13/2012 at 22:25
// ======================================================================

/* -- WARNING: The following section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_DIE_LEOPARD 1
`define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3
`define CYDEV_CHIP_REV_LEOPARD_ES3 3
`define CYDEV_CHIP_REV_LEOPARD_ES2 1
`define CYDEV_CHIP_REV_LEOPARD_ES1 0
`define CYDEV_CHIP_DIE_PANTHER 2
`define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1
`define CYDEV_CHIP_REV_PANTHER_ES1 1
`define CYDEV_CHIP_REV_PANTHER_ES0 0
`define CYDEV_CHIP_DIE_EXPECT 1
`define CYDEV_CHIP_REV_EXPECT 3
`define CYDEV_CHIP_DIE_ACTUAL 1
/* -- WARNING: The previous section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_FAMILY_PSOC5 2
`define CYDEV_CHIP_MEMBER_5A 2
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_FAMILY_USED 1
`define CYDEV_CHIP_MEMBER_USED 1
`define CYDEV_CHIP_REVISION_USED 3
// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// Component: B_UART_v2_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v2_0"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v2_0\B_UART_v2_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v2_0"
`include "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v2_0\B_UART_v2_0.v"
`endif

// UART_v2_0(Address1=0, Address2=0, BaudRate=115200, BreakBitsRX=13, BreakBitsTX=13, BreakDetect=false, CRCoutputsEn=false, CtrlModeReplacementString=SyncCtl, Enable_RX=1, Enable_RXIntInterrupt=1, Enable_TX=1, Enable_TXIntInterrupt=0, EnableHWAddress=0, EnIntRXInterrupt=true, EnIntTXInterrupt=false, FlowControl=0, HalfDuplexEn=false, HwTXEnSignal=true, InternalClock=true, InternalClockUsed=1, InterruptOnAddDetect=0, InterruptOnAddressMatch=0, InterruptOnBreak=0, InterruptOnByteRcvd=1, InterruptOnOverrunError=0, InterruptOnParityError=0, InterruptOnStopError=0, InterruptOnTXComplete=false, InterruptOnTXFifoEmpty=true, InterruptOnTXFifoFull=false, InterruptOnTXFifoNotFull=false, IntOnAddressDetect=false, IntOnAddressMatch=false, IntOnBreak=false, IntOnByteRcvd=true, IntOnOverrunError=false, IntOnParityError=false, IntOnStopError=false, NumDataBits=8, NumStopBits=1, OverSamplingRate=8, ParityType=0, ParityTypeSw=false, RequiredClock=921600, RXAddressMode=0, RXBufferSize=50, RxBuffRegSizeReplacementString=uint8, RXEnable=true, TXBitClkGenDP=true, TXBufferSize=1, TxBuffRegSizeReplacementString=uint8, TXEnable=true, Use23Polling=true, CY_COMPONENT_NAME=UART_v2_0, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=uart_pc, CY_INSTANCE_SHORT_NAME=uart_pc, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=uart_pc, )
module UART_v2_0_0 (rx_clk, rx_data, tx_clk, tx_data, rx_interrupt, tx_interrupt, tx, tx_en, rts_n, reset, cts_n, clock, rx);
    output  rx_clk;
    output  rx_data;
    output  tx_clk;
    output  tx_data;
    output  rx_interrupt;
    output  tx_interrupt;
    output  tx;
    output  tx_en;
    output  rts_n;
    input   reset;
    input   cts_n;
    input   clock;
    input   rx;

    parameter Address1 = 0;
    parameter Address2 = 0;
    parameter EnIntRXInterrupt = 1;
    parameter EnIntTXInterrupt = 0;
    parameter FlowControl = 0;
    parameter HalfDuplexEn = 0;
    parameter HwTXEnSignal = 1;
    parameter NumDataBits = 8;
    parameter NumStopBits = 1;
    parameter ParityType = 0;
    parameter RXEnable = 1;
    parameter TXEnable = 1;

    wire  Net_289;
    wire  Net_9;
    wire  Net_61;


	cy_clock_v1_0
		#(.id("b0162966-0060-4af5-82d1-fcb491ad7619/be0a0e37-ad17-42ca-b5a1-1a654d736358"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("1085069444.44444"),
		  .is_direct(0),
		  .is_digital(1))
		IntClock
		 (.clock_out(Net_9));



	cy_isr_v1_0
		#(.int_type(2'b10))
		RXInternalInterrupt
		 (.int_signal(rx_interrupt));


	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_61 = Net_9;

    B_UART_v2_0 BUART (
        .cts_n(cts_n),
        .tx(tx),
        .rts_n(rts_n),
        .tx_en(tx_en),
        .clock(Net_61),
        .reset(reset),
        .rx(rx),
        .tx_interrupt(tx_interrupt),
        .rx_interrupt(rx_interrupt),
        .tx_data(tx_data),
        .tx_clk(tx_clk),
        .rx_data(rx_data),
        .rx_clk(rx_clk));
    defparam BUART.Address1 = 0;
    defparam BUART.Address2 = 0;
    defparam BUART.BreakBitsRX = 13;
    defparam BUART.BreakBitsTX = 13;
    defparam BUART.BreakDetect = 0;
    defparam BUART.CRCoutputsEn = 0;
    defparam BUART.FlowControl = 0;
    defparam BUART.HalfDuplexEn = 0;
    defparam BUART.HwTXEnSignal = 1;
    defparam BUART.NumDataBits = 8;
    defparam BUART.NumStopBits = 1;
    defparam BUART.OverSampleCount = 8;
    defparam BUART.ParityType = 0;
    defparam BUART.ParityTypeSw = 0;
    defparam BUART.RXAddressMode = 0;
    defparam BUART.RXEnable = 1;
    defparam BUART.RXStatusIntEnable = 1;
    defparam BUART.TXBitClkGenDP = 1;
    defparam BUART.TXEnable = 1;
    defparam BUART.Use23Polling = 1;



endmodule

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// Component: OneTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal\OneTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal"
`include "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal\OneTerminal.v"
`endif

// Component: B_Counter_v1_50
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Counter_v1_50"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Counter_v1_50\B_Counter_v1_50.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Counter_v1_50"
`include "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Counter_v1_50\B_Counter_v1_50.v"
`endif

// Counter_v1_50(CaptureMode=0, CaptureModeSoftware=0, ClockMode=1, CompareMode=0, CompareModeSoftware=0, CompareStatusEdgeSense=true, CompareValue=32768, ControlRegRemoved=0, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, EnableMode=2, FixedFunction=false, FixedFunctionUsed=0, InitCounterValue=32768, InterruptOnCapture=false, InterruptOnCompare=false, InterruptOnOverUnderFlow=false, InterruptOnTC=false, Period=32768, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, ReloadOnCapture=false, ReloadOnCompare=false, ReloadOnOverUnder=true, ReloadOnReset=true, Resolution=16, RstStatusReplacementString=sSTSReg_rstSts, RunMode=0, UseInterrupt=true, VerilogSectionReplacementString=sC16, CY_COMPONENT_NAME=Counter_v1_50, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=Cnt16, CY_INSTANCE_SHORT_NAME=Cnt16, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=50, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=quaddec_left_Cnt16, )
module Counter_v1_50_1 (clock, comp, tc, reset, interrupt, enable, capture, upCnt, downCnt, up_ndown, count);
    input   clock;
    output  comp;
    output  tc;
    input   reset;
    output  interrupt;
    input   enable;
    input   capture;
    input   upCnt;
    input   downCnt;
    input   up_ndown;
    input   count;

    parameter CaptureMode = 0;
    parameter ClockMode = 1;
    parameter CompareMode = 0;
    parameter CompareStatusEdgeSense = 1;
    parameter EnableMode = 2;
    parameter ReloadOnCapture = 0;
    parameter ReloadOnCompare = 0;
    parameter ReloadOnOverUnder = 1;
    parameter ReloadOnReset = 1;
    parameter Resolution = 16;
    parameter RunMode = 0;
    parameter UseInterrupt = 1;

    wire  Net_1;
    wire  Net_4;
    wire  Net_102;
    wire  Net_95;
    wire  Net_82;
    wire  Net_91;
    wire  Net_89;
    wire  Net_60;
    wire  Net_55;
    wire  Net_54;
    wire  Net_49;
    wire  Net_48;
    wire  Net_42;
    wire  Net_43;

	// int_vm (cy_virtualmux_v1_0)
	assign interrupt = Net_43;

	// TC_vm (cy_virtualmux_v1_0)
	assign tc = Net_49;

	// compare_vm (cy_virtualmux_v1_0)
	assign comp = Net_55;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_82));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_89 = up_ndown;

    ZeroTerminal ZeroTerminal_2 (
        .z(Net_95));

	// vmEnableMode (cy_virtualmux_v1_0)
	assign Net_91 = enable;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign Net_60 = count;

    B_Counter_v1_50 CounterUDB (
        .reset(reset),
        .tc_out(Net_49),
        .cmp_out(Net_55),
        .clock(Net_60),
        .irq_out(Net_43),
        .up_ndown(Net_89),
        .upcnt(upCnt),
        .dwncnt(downCnt),
        .enable(enable),
        .capture(capture),
        .bus_clk(Net_4));
    defparam CounterUDB.CaptureMode = 0;
    defparam CounterUDB.ClockMode = 1;
    defparam CounterUDB.CompareMode = 0;
    defparam CounterUDB.CompareStatusEdgeSense = 1;
    defparam CounterUDB.EnableMode = 2;
    defparam CounterUDB.ReloadOnCapture = 0;
    defparam CounterUDB.ReloadOnCompare = 0;
    defparam CounterUDB.ReloadOnOverUnder = 1;
    defparam CounterUDB.ReloadOnReset = 1;
    defparam CounterUDB.Resolution = 16;
    defparam CounterUDB.RunMode = 0;
    defparam CounterUDB.UseInterrupt = 1;


	cy_clock_v1_0
		#(.id("4feec6c5-a740-463e-a92e-a0f8eb25cfad/e82e85c3-0b0f-4a80-a973-612f6021fb44/c7c0a6ca-d157-41d9-b46f-4dabf3b469c4"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_1
		 (.clock_out(Net_4));




endmodule

// Component: bQuadDec_v1_50
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\bQuadDec_v1_50"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\bQuadDec_v1_50\bQuadDec_v1_50.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\bQuadDec_v1_50"
`include "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\bQuadDec_v1_50\bQuadDec_v1_50.v"
`endif

// Component: not_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0\not_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0\not_v1_0.v"
`endif

// Component: and_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\and_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\and_v1_0\and_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\and_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\and_v1_0\and_v1_0.v"
`endif

// QuadDec_v1_50(CounterResolution=1, CounterSize=32, CounterSizeReplacementString=int32, CounterSizeReplacementStringUnsigned=uint16, UsingGlitchFiltering=true, UsingIndexInput=false, CY_COMPONENT_NAME=QuadDec_v1_50, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=quaddec_left, CY_INSTANCE_SHORT_NAME=quaddec_left, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=50, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=quaddec_left, )
module QuadDec_v1_50_2 (quad_A, quad_B, index, clock, interrupt);
    input   quad_A;
    input   quad_B;
    input   index;
    input   clock;
    output  interrupt;

    parameter CounterResolution = 1;
    parameter UsingGlitchFiltering = 1;
    parameter UsingIndexInput = 0;

    wire  Net_1127;
    wire  Net_1128;
    wire  Net_1129;
    wire  Net_1130;
    wire  Net_1131;
    wire  Net_1132;
    wire  Net_1121;
    wire  Net_1122;
    wire  Net_1123;
    wire  Net_1124;
    wire  Net_1125;
    wire  Net_1126;
    wire  Net_1232;
    wire  Net_1229;
    wire  Net_1195;
    wire  Net_1203;
    wire  Net_1163;
    wire  Net_283;
    wire  Net_1210;
    wire  Net_611;
    wire  Net_1176;
    wire  Net_1151;
    wire  Net_530;


	cy_isr_v1_0
		#(.int_type(2'b10))
		isr
		 (.int_signal(interrupt));


    Counter_v1_50_1 Cnt16 (
        .reset(Net_1195),
        .tc(Net_1210),
        .comp(Net_1127),
        .clock(1'b0),
        .interrupt(Net_1129),
        .enable(Net_1203),
        .capture(1'b0),
        .upCnt(1'b0),
        .downCnt(1'b0),
        .up_ndown(Net_1163),
        .count(clock));
    defparam Cnt16.CaptureMode = 0;
    defparam Cnt16.ClockMode = 1;
    defparam Cnt16.CompareMode = 0;
    defparam Cnt16.CompareStatusEdgeSense = 1;
    defparam Cnt16.EnableMode = 2;
    defparam Cnt16.ReloadOnCapture = 0;
    defparam Cnt16.ReloadOnCompare = 0;
    defparam Cnt16.ReloadOnOverUnder = 1;
    defparam Cnt16.ReloadOnReset = 1;
    defparam Cnt16.Resolution = 16;
    defparam Cnt16.RunMode = 0;
    defparam Cnt16.UseInterrupt = 1;

	// VirtualMux_3 (cy_virtualmux_v1_0)
	assign Net_1151 = Net_1210;

    bQuadDec_v1_50 bQuadDec (
        .quad_A(quad_A),
        .quad_B(quad_B),
        .index(Net_1232),
        .clock(clock),
        .dir(Net_1163),
        .reset(Net_1195),
        .enable(Net_1203),
        .overflow(Net_530),
        .underflow(Net_611),
        .interrupt(interrupt));
    defparam bQuadDec.CounterResolution = 1;
    defparam bQuadDec.UsingGlitchFiltering = 1;
    defparam bQuadDec.UsingIndexInput = 0;


    assign Net_1176 = ~Net_1163;


    assign Net_530 = Net_1163 & Net_1151;


    assign Net_611 = Net_1176 & Net_1151;

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_1232 = Net_1229;

    OneTerminal OneTerminal_1 (
        .o(Net_1229));



endmodule

// Component: B_Timer_v2_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_0"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_0\B_Timer_v2_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_0"
`include "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_0\B_Timer_v2_0.v"
`endif

// Timer_v2_0(CaptureAlternatingFall=false, CaptureAlternatingRise=false, CaptureCount=2, CaptureCounterEnabled=false, CaptureInputEnabled=false, CaptureMode=0, ControlRegRemoved=0, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG24, CySetRegReplacementString=CY_SET_REG24, DeviceFamily=PSoC3, EnableMode=0, FF16=false, FF8=false, FixedFunction=false, FixedFunctionUsed=0, HWCaptureCounterEnabled=false, InterruptOnCapture=false, InterruptOnFIFOFull=false, InterruptOnTC=true, IntOnCapture=0, IntOnFIFOFull=0, IntOnTC=1, NumberOfCaptures=1, param45=1, Period=119999, RegDefReplacementString=reg32, RegSizeReplacementString=uint32, Resolution=24, RstStatusReplacementString=rstSts, RunMode=0, SiliconRevision=3, SoftwareCaptureModeEnabled=false, SoftwareTriggerModeEnabled=false, TriggerInputEnabled=false, TriggerMode=0, UDB16=false, UDB24=true, UDB32=false, UDB8=false, UsesHWEnable=0, VerilogSectionReplacementString=sT24, CY_COMPONENT_NAME=Timer_v2_0, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=timer_asserv, CY_INSTANCE_SHORT_NAME=timer_asserv, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=timer_asserv, )
module Timer_v2_0_3 (clock, reset, interrupt, enable, capture, trigger, capture_out, tc);
    input   clock;
    input   reset;
    output  interrupt;
    input   enable;
    input   capture;
    input   trigger;
    output  capture_out;
    output  tc;

    parameter CaptureCount = 2;
    parameter CaptureCounterEnabled = 0;
    parameter DeviceFamily = "PSoC3";
    parameter InterruptOnCapture = 0;
    parameter InterruptOnTC = 1;
    parameter Resolution = 24;
    parameter SiliconRevision = "3";

    wire  Net_260;
    wire  Net_261;
    wire  Net_266;
    wire  Net_102;
    wire  Net_55;
    wire  Net_57;
    wire  Net_53;
    wire  Net_51;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_260));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign interrupt = Net_55;

	// VirtualMux_3 (cy_virtualmux_v1_0)
	assign tc = Net_53;

    B_Timer_v2_0 TimerUDB (
        .reset(reset),
        .interrupt(Net_55),
        .enable(enable),
        .trigger(trigger),
        .capture_in(capture),
        .capture_out(capture_out),
        .tc(Net_53),
        .clock(clock));
    defparam TimerUDB.Capture_Count = 2;
    defparam TimerUDB.CaptureCounterEnabled = 0;
    defparam TimerUDB.CaptureMode = 0;
    defparam TimerUDB.EnableMode = 0;
    defparam TimerUDB.InterruptOnCapture = 0;
    defparam TimerUDB.Resolution = 24;
    defparam TimerUDB.RunMode = 0;
    defparam TimerUDB.TriggerMode = 0;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_266 = Net_102;



endmodule

// Counter_v1_50(CaptureMode=0, CaptureModeSoftware=0, ClockMode=1, CompareMode=0, CompareModeSoftware=0, CompareStatusEdgeSense=true, CompareValue=32768, ControlRegRemoved=0, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, EnableMode=2, FixedFunction=false, FixedFunctionUsed=0, InitCounterValue=32768, InterruptOnCapture=false, InterruptOnCompare=false, InterruptOnOverUnderFlow=false, InterruptOnTC=false, Period=32768, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, ReloadOnCapture=false, ReloadOnCompare=false, ReloadOnOverUnder=true, ReloadOnReset=true, Resolution=16, RstStatusReplacementString=sSTSReg_rstSts, RunMode=0, UseInterrupt=true, VerilogSectionReplacementString=sC16, CY_COMPONENT_NAME=Counter_v1_50, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=quaddec_right:Cnt16, CY_INSTANCE_SHORT_NAME=Cnt16, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=50, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=quaddec_right_Cnt16, )
module Counter_v1_50_4 (clock, comp, tc, reset, interrupt, enable, capture, upCnt, downCnt, up_ndown, count);
    input   clock;
    output  comp;
    output  tc;
    input   reset;
    output  interrupt;
    input   enable;
    input   capture;
    input   upCnt;
    input   downCnt;
    input   up_ndown;
    input   count;

    parameter CaptureMode = 0;
    parameter ClockMode = 1;
    parameter CompareMode = 0;
    parameter CompareStatusEdgeSense = 1;
    parameter EnableMode = 2;
    parameter ReloadOnCapture = 0;
    parameter ReloadOnCompare = 0;
    parameter ReloadOnOverUnder = 1;
    parameter ReloadOnReset = 1;
    parameter Resolution = 16;
    parameter RunMode = 0;
    parameter UseInterrupt = 1;

    wire  Net_1;
    wire  Net_4;
    wire  Net_102;
    wire  Net_95;
    wire  Net_82;
    wire  Net_91;
    wire  Net_89;
    wire  Net_60;
    wire  Net_55;
    wire  Net_54;
    wire  Net_49;
    wire  Net_48;
    wire  Net_42;
    wire  Net_43;

	// int_vm (cy_virtualmux_v1_0)
	assign interrupt = Net_43;

	// TC_vm (cy_virtualmux_v1_0)
	assign tc = Net_49;

	// compare_vm (cy_virtualmux_v1_0)
	assign comp = Net_55;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_82));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_89 = up_ndown;

    ZeroTerminal ZeroTerminal_2 (
        .z(Net_95));

	// vmEnableMode (cy_virtualmux_v1_0)
	assign Net_91 = enable;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign Net_60 = count;

    B_Counter_v1_50 CounterUDB (
        .reset(reset),
        .tc_out(Net_49),
        .cmp_out(Net_55),
        .clock(Net_60),
        .irq_out(Net_43),
        .up_ndown(Net_89),
        .upcnt(upCnt),
        .dwncnt(downCnt),
        .enable(enable),
        .capture(capture),
        .bus_clk(Net_4));
    defparam CounterUDB.CaptureMode = 0;
    defparam CounterUDB.ClockMode = 1;
    defparam CounterUDB.CompareMode = 0;
    defparam CounterUDB.CompareStatusEdgeSense = 1;
    defparam CounterUDB.EnableMode = 2;
    defparam CounterUDB.ReloadOnCapture = 0;
    defparam CounterUDB.ReloadOnCompare = 0;
    defparam CounterUDB.ReloadOnOverUnder = 1;
    defparam CounterUDB.ReloadOnReset = 1;
    defparam CounterUDB.Resolution = 16;
    defparam CounterUDB.RunMode = 0;
    defparam CounterUDB.UseInterrupt = 1;


	cy_clock_v1_0
		#(.id("abe963bd-e744-42f8-9493-041a5b5fe1b3/e82e85c3-0b0f-4a80-a973-612f6021fb44/c7c0a6ca-d157-41d9-b46f-4dabf3b469c4"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_1
		 (.clock_out(Net_4));




endmodule

// QuadDec_v1_50(CounterResolution=1, CounterSize=32, CounterSizeReplacementString=int32, CounterSizeReplacementStringUnsigned=uint16, UsingGlitchFiltering=true, UsingIndexInput=false, CY_COMPONENT_NAME=QuadDec_v1_50, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=quaddec_right, CY_INSTANCE_SHORT_NAME=quaddec_right, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=50, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=quaddec_right, )
module QuadDec_v1_50_5 (quad_A, quad_B, index, clock, interrupt);
    input   quad_A;
    input   quad_B;
    input   index;
    input   clock;
    output  interrupt;

    parameter CounterResolution = 1;
    parameter UsingGlitchFiltering = 1;
    parameter UsingIndexInput = 0;

    wire  Net_1127;
    wire  Net_1128;
    wire  Net_1129;
    wire  Net_1130;
    wire  Net_1131;
    wire  Net_1132;
    wire  Net_1121;
    wire  Net_1122;
    wire  Net_1123;
    wire  Net_1124;
    wire  Net_1125;
    wire  Net_1126;
    wire  Net_1232;
    wire  Net_1229;
    wire  Net_1195;
    wire  Net_1203;
    wire  Net_1163;
    wire  Net_283;
    wire  Net_1210;
    wire  Net_611;
    wire  Net_1176;
    wire  Net_1151;
    wire  Net_530;


	cy_isr_v1_0
		#(.int_type(2'b10))
		isr
		 (.int_signal(interrupt));


    Counter_v1_50_4 Cnt16 (
        .reset(Net_1195),
        .tc(Net_1210),
        .comp(Net_1127),
        .clock(1'b0),
        .interrupt(Net_1129),
        .enable(Net_1203),
        .capture(1'b0),
        .upCnt(1'b0),
        .downCnt(1'b0),
        .up_ndown(Net_1163),
        .count(clock));
    defparam Cnt16.CaptureMode = 0;
    defparam Cnt16.ClockMode = 1;
    defparam Cnt16.CompareMode = 0;
    defparam Cnt16.CompareStatusEdgeSense = 1;
    defparam Cnt16.EnableMode = 2;
    defparam Cnt16.ReloadOnCapture = 0;
    defparam Cnt16.ReloadOnCompare = 0;
    defparam Cnt16.ReloadOnOverUnder = 1;
    defparam Cnt16.ReloadOnReset = 1;
    defparam Cnt16.Resolution = 16;
    defparam Cnt16.RunMode = 0;
    defparam Cnt16.UseInterrupt = 1;

	// VirtualMux_3 (cy_virtualmux_v1_0)
	assign Net_1151 = Net_1210;

    bQuadDec_v1_50 bQuadDec (
        .quad_A(quad_A),
        .quad_B(quad_B),
        .index(Net_1232),
        .clock(clock),
        .dir(Net_1163),
        .reset(Net_1195),
        .enable(Net_1203),
        .overflow(Net_530),
        .underflow(Net_611),
        .interrupt(interrupt));
    defparam bQuadDec.CounterResolution = 1;
    defparam bQuadDec.UsingGlitchFiltering = 1;
    defparam bQuadDec.UsingIndexInput = 0;


    assign Net_1176 = ~Net_1163;


    assign Net_530 = Net_1163 & Net_1151;


    assign Net_611 = Net_1176 & Net_1151;

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_1232 = Net_1229;

    OneTerminal OneTerminal_1 (
        .o(Net_1229));



endmodule

// PWM_v2_0(CaptureMode=0, CompareStatusEdgeSense=true, CompareType1=1, CompareType1Software=0, CompareType2=1, CompareType2Software=0, CompareValue1=0, CompareValue2=63, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, DeadBand=0, DeadBand2_4=0, DeadBandUsed=0, DeadTime=1, DitherOffset=0, EnableMode=0, FixedFunction=true, FixedFunctionUsed=1, InterruptOnCMP1=false, InterruptOnCMP2=false, InterruptOnKill=false, InterruptOnTC=false, IntOnCMP1=0, IntOnCMP2=0, IntOnKill=0, IntOnTC=0, KillMode=1, KillModeMinTime=0, MinimumKillTime=1, OneCompare=true, Period=1024, PWMMode=0, PWMModeCenterAligned=0, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, Resolution=16, RstStatusReplacementString=sSTSReg_rstSts, RunMode=0, TriggerMode=0, UseControl=true, UseInterrupt=false, UseStatus=false, VerilogSectionReplacementString=sP16, CY_COMPONENT_NAME=PWM_v2_0, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=pwm_right, CY_INSTANCE_SHORT_NAME=pwm_right, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=pwm_right, )
module PWM_v2_0_6 (pwm2, tc, clock, reset, pwm1, interrupt, capture, kill, enable, trigger, cmp_sel, pwm, ph1, ph2);
    output  pwm2;
    output  tc;
    input   clock;
    input   reset;
    output  pwm1;
    output  interrupt;
    input   capture;
    input   kill;
    input   enable;
    input   trigger;
    input   cmp_sel;
    output  pwm;
    output  ph1;
    output  ph2;

    parameter Resolution = 16;

    wire  Net_113;
    wire  Net_114;
    wire  Net_107;
    wire  Net_96;
    wire  Net_55;
    wire  Net_57;
    wire  Net_101;
    wire  Net_54;
    wire  Net_63;

    cy_psoc3_timer_v1_0 PWMHW (
        .timer_reset(reset),
        .capture(capture),
        .enable(Net_113),
        .kill(Net_107),
        .clock(clock),
        .tc(Net_63),
        .compare(Net_57),
        .interrupt(Net_54));

	// vmCompare (cy_virtualmux_v1_0)
	assign pwm = Net_57;

	// vmIRQ (cy_virtualmux_v1_0)
	assign interrupt = Net_54;

	// vmTC (cy_virtualmux_v1_0)
	assign tc = Net_63;

    OneTerminal OneTerminal_1 (
        .o(Net_113));

	// FFKillMux (cy_virtualmux_v1_0)
	assign Net_107 = kill;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_114));



endmodule

// PWM_v2_0(CaptureMode=0, CompareStatusEdgeSense=true, CompareType1=1, CompareType1Software=0, CompareType2=1, CompareType2Software=0, CompareValue1=0, CompareValue2=63, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, DeadBand=0, DeadBand2_4=0, DeadBandUsed=0, DeadTime=1, DitherOffset=0, EnableMode=0, FixedFunction=true, FixedFunctionUsed=1, InterruptOnCMP1=false, InterruptOnCMP2=false, InterruptOnKill=false, InterruptOnTC=false, IntOnCMP1=0, IntOnCMP2=0, IntOnKill=0, IntOnTC=0, KillMode=1, KillModeMinTime=0, MinimumKillTime=1, OneCompare=true, Period=1024, PWMMode=0, PWMModeCenterAligned=0, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, Resolution=16, RstStatusReplacementString=sSTSReg_rstSts, RunMode=0, TriggerMode=0, UseControl=true, UseInterrupt=false, UseStatus=false, VerilogSectionReplacementString=sP16, CY_COMPONENT_NAME=PWM_v2_0, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=pwm_left, CY_INSTANCE_SHORT_NAME=pwm_left, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=pwm_left, )
module PWM_v2_0_7 (pwm2, tc, clock, reset, pwm1, interrupt, capture, kill, enable, trigger, cmp_sel, pwm, ph1, ph2);
    output  pwm2;
    output  tc;
    input   clock;
    input   reset;
    output  pwm1;
    output  interrupt;
    input   capture;
    input   kill;
    input   enable;
    input   trigger;
    input   cmp_sel;
    output  pwm;
    output  ph1;
    output  ph2;

    parameter Resolution = 16;

    wire  Net_113;
    wire  Net_114;
    wire  Net_107;
    wire  Net_96;
    wire  Net_55;
    wire  Net_57;
    wire  Net_101;
    wire  Net_54;
    wire  Net_63;

    cy_psoc3_timer_v1_0 PWMHW (
        .timer_reset(reset),
        .capture(capture),
        .enable(Net_113),
        .kill(Net_107),
        .clock(clock),
        .tc(Net_63),
        .compare(Net_57),
        .interrupt(Net_54));

	// vmCompare (cy_virtualmux_v1_0)
	assign pwm = Net_57;

	// vmIRQ (cy_virtualmux_v1_0)
	assign interrupt = Net_54;

	// vmTC (cy_virtualmux_v1_0)
	assign tc = Net_63;

    OneTerminal OneTerminal_1 (
        .o(Net_113));

	// FFKillMux (cy_virtualmux_v1_0)
	assign Net_107 = kill;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_114));



endmodule

// Component: demux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\demux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\demux_v1_0\demux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\demux_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\demux_v1_0\demux_v1_0.v"
`endif

// Component: CyControlReg_v1_50
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_50"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_50\CyControlReg_v1_50.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_50"
`include "C:\Program Files\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_50\CyControlReg_v1_50.v"
`endif

// top
module top ;

    wire  Net_72;
    wire  Net_68;
    wire  Net_67;
    wire  Net_66;
    wire  Net_65;
    wire  Net_64;
    wire  Net_63;
    wire  Net_62;
    wire  Net_61;
    wire  Net_60;
    wire  Net_59;
    wire  Net_58;
    wire  Net_57;
    wire  Net_56;
    wire  Net_55;
    wire  Net_54;
    wire  Net_52;
    wire  Net_51;
    wire  Net_50;
    wire  Net_49;
    wire  Net_48;
    wire  Net_47;
    wire  Net_46;
    wire  Net_45;
    wire  Net_44;
    wire  Net_43;
    wire  Net_42;
    wire  Net_41;
    wire  Net_40;
    wire  Net_39;
    wire  Net_35;
    wire  Net_34;
    wire  Net_33;
    wire  Net_32;
    wire  Net_31;
    wire  Net_30;
    wire  Net_28;
    wire  Net_27;
    wire  Net_26;
    wire  Net_25;
    wire  Net_24;
    wire  Net_71;
    wire  Net_21;
    wire  Net_20;
    wire  Net_18;
    wire  Net_17;
    wire  Net_16;
    wire  Net_70;
    wire  Net_14;
    wire  Net_13;
    wire  Net_12;
    wire  Net_11;
    wire  Net_10;
    wire  Net_9;
    wire  Net_8;
    wire  Net_6;
    wire  Net_5;
    wire  Net_4;
    wire  Net_3;
    wire  Net_1;
    wire  Net_128;
    wire  Net_118;
    wire  Net_133;
    wire  Net_98;
    wire  Net_112;
    wire  Net_203;
    wire  Net_204;
    wire  Net_206;
    wire  Net_205;
    wire  Net_148;
    wire  Net_153;
    wire  Net_149;
    wire  Net_152;
    wire  Net_38;
    wire  Net_37;
    wire  Net_36;
    wire  Net_22;
    wire  Net_29;
    wire  Net_19;
    wire  Net_361;
    wire  Net_164;
    wire  Net_53;
    wire  Net_2;
    wire  Net_7;

    UART_v2_0_0 uart_pc (
        .cts_n(1'b0),
        .tx(Net_2),
        .rts_n(Net_3),
        .tx_en(Net_4),
        .clock(1'b0),
        .reset(Net_53),
        .rx(Net_7),
        .tx_interrupt(Net_6),
        .rx_interrupt(Net_8),
        .tx_data(Net_9),
        .tx_clk(Net_10),
        .rx_data(Net_11),
        .rx_clk(Net_12));
    defparam uart_pc.Address1 = 0;
    defparam uart_pc.Address2 = 0;
    defparam uart_pc.EnIntRXInterrupt = 1;
    defparam uart_pc.EnIntTXInterrupt = 0;
    defparam uart_pc.FlowControl = 0;
    defparam uart_pc.HalfDuplexEn = 0;
    defparam uart_pc.HwTXEnSignal = 1;
    defparam uart_pc.NumDataBits = 8;
    defparam uart_pc.NumStopBits = 1;
    defparam uart_pc.ParityType = 0;
    defparam uart_pc.RXEnable = 1;
    defparam uart_pc.TXEnable = 1;

	wire [0:0] tmpOE__rx_pc_net;
	wire [0:0] tmpIO_0__rx_pc_net;
	wire [0:0] tmpINTERRUPT_0__rx_pc_net;
	electrical [0:0] tmpSIOVREF__rx_pc_net;

	cy_psoc3_pins_v1_10
		#(.id("1425177d-0d0e-4468-8bcc-e638e5509a9b"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		rx_pc
		 (.oe(tmpOE__rx_pc_net),
		  .y({1'b0}),
		  .fb({Net_7}),
		  .io({tmpIO_0__rx_pc_net[0:0]}),
		  .siovref(tmpSIOVREF__rx_pc_net),
		  .interrupt({tmpINTERRUPT_0__rx_pc_net[0:0]}));

	assign tmpOE__rx_pc_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__tx_pc_net;
	wire [0:0] tmpFB_0__tx_pc_net;
	wire [0:0] tmpIO_0__tx_pc_net;
	wire [0:0] tmpINTERRUPT_0__tx_pc_net;
	electrical [0:0] tmpSIOVREF__tx_pc_net;

	cy_psoc3_pins_v1_10
		#(.id("ed092b9b-d398-4703-be89-cebf998501f6"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		tx_pc
		 (.oe(tmpOE__tx_pc_net),
		  .y({Net_2}),
		  .fb({tmpFB_0__tx_pc_net[0:0]}),
		  .io({tmpIO_0__tx_pc_net[0:0]}),
		  .siovref(tmpSIOVREF__tx_pc_net),
		  .interrupt({tmpINTERRUPT_0__tx_pc_net[0:0]}));

	assign tmpOE__tx_pc_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_53));

    QuadDec_v1_50_2 quaddec_left (
        .quad_A(Net_19),
        .quad_B(Net_361),
        .index(1'b0),
        .clock(Net_164),
        .interrupt(Net_14));
    defparam quaddec_left.CounterResolution = 1;
    defparam quaddec_left.UsingGlitchFiltering = 1;
    defparam quaddec_left.UsingIndexInput = 0;


	cy_clock_v1_0
		#(.id("b80c67bd-1d96-46cf-b3f1-4a116d47b25a"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_3
		 (.clock_out(Net_164));


	wire [0:0] tmpOE__encoder_left_sig_a_net;
	wire [0:0] tmpIO_0__encoder_left_sig_a_net;
	wire [0:0] tmpINTERRUPT_0__encoder_left_sig_a_net;
	electrical [0:0] tmpSIOVREF__encoder_left_sig_a_net;

	cy_psoc3_pins_v1_10
		#(.id("1cf69dcb-8a5a-423e-b205-610fb75f434b"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		encoder_left_sig_a
		 (.oe(tmpOE__encoder_left_sig_a_net),
		  .y({1'b0}),
		  .fb({Net_19}),
		  .io({tmpIO_0__encoder_left_sig_a_net[0:0]}),
		  .siovref(tmpSIOVREF__encoder_left_sig_a_net),
		  .interrupt({tmpINTERRUPT_0__encoder_left_sig_a_net[0:0]}));

	assign tmpOE__encoder_left_sig_a_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__encoder_left_sig_b_net;
	wire [0:0] tmpIO_0__encoder_left_sig_b_net;
	wire [0:0] tmpINTERRUPT_0__encoder_left_sig_b_net;
	electrical [0:0] tmpSIOVREF__encoder_left_sig_b_net;

	cy_psoc3_pins_v1_10
		#(.id("aac34552-a717-4832-9b98-de88ad533d29"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		encoder_left_sig_b
		 (.oe(tmpOE__encoder_left_sig_b_net),
		  .y({1'b0}),
		  .fb({Net_361}),
		  .io({tmpIO_0__encoder_left_sig_b_net[0:0]}),
		  .siovref(tmpSIOVREF__encoder_left_sig_b_net),
		  .interrupt({tmpINTERRUPT_0__encoder_left_sig_b_net[0:0]}));

	assign tmpOE__encoder_left_sig_b_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    Timer_v2_0_3 timer_asserv (
        .reset(Net_22),
        .interrupt(Net_16),
        .enable(1'b1),
        .trigger(1'b0),
        .capture(1'b0),
        .capture_out(Net_21),
        .tc(Net_36),
        .clock(Net_29));
    defparam timer_asserv.CaptureCount = 2;
    defparam timer_asserv.CaptureCounterEnabled = 0;
    defparam timer_asserv.DeviceFamily = "PSoC3";
    defparam timer_asserv.InterruptOnCapture = 0;
    defparam timer_asserv.InterruptOnTC = 1;
    defparam timer_asserv.Resolution = 24;
    defparam timer_asserv.SiliconRevision = "3";


	cy_clock_v1_0
		#(.id("920ac626-75fc-42be-bddc-386ba9cec7f2"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		timer_clock
		 (.clock_out(Net_29));


    ZeroTerminal ZeroTerminal_2 (
        .z(Net_22));


	cy_isr_v1_0
		#(.int_type(2'b10))
		isr_positionning
		 (.int_signal(Net_36));


    QuadDec_v1_50_5 quaddec_right (
        .quad_A(Net_37),
        .quad_B(Net_38),
        .index(1'b0),
        .clock(Net_164),
        .interrupt(Net_25));
    defparam quaddec_right.CounterResolution = 1;
    defparam quaddec_right.UsingGlitchFiltering = 1;
    defparam quaddec_right.UsingIndexInput = 0;

	wire [0:0] tmpOE__encoder_right_sig_a_net;
	wire [0:0] tmpIO_0__encoder_right_sig_a_net;
	wire [0:0] tmpINTERRUPT_0__encoder_right_sig_a_net;
	electrical [0:0] tmpSIOVREF__encoder_right_sig_a_net;

	cy_psoc3_pins_v1_10
		#(.id("ae008a53-d4e2-41bf-9699-6defc9031027"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		encoder_right_sig_a
		 (.oe(tmpOE__encoder_right_sig_a_net),
		  .y({1'b0}),
		  .fb({Net_37}),
		  .io({tmpIO_0__encoder_right_sig_a_net[0:0]}),
		  .siovref(tmpSIOVREF__encoder_right_sig_a_net),
		  .interrupt({tmpINTERRUPT_0__encoder_right_sig_a_net[0:0]}));

	assign tmpOE__encoder_right_sig_a_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__encoder_right_sig_b_net;
	wire [0:0] tmpIO_0__encoder_right_sig_b_net;
	wire [0:0] tmpINTERRUPT_0__encoder_right_sig_b_net;
	electrical [0:0] tmpSIOVREF__encoder_right_sig_b_net;

	cy_psoc3_pins_v1_10
		#(.id("555a0703-d391-494e-aac3-c22c3af2b6b8"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		encoder_right_sig_b
		 (.oe(tmpOE__encoder_right_sig_b_net),
		  .y({1'b0}),
		  .fb({Net_38}),
		  .io({tmpIO_0__encoder_right_sig_b_net[0:0]}),
		  .siovref(tmpSIOVREF__encoder_right_sig_b_net),
		  .interrupt({tmpINTERRUPT_0__encoder_right_sig_b_net[0:0]}));

	assign tmpOE__encoder_right_sig_b_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    PWM_v2_0_6 pwm_right (
        .reset(Net_98),
        .clock(Net_128),
        .tc(Net_26),
        .pwm1(Net_27),
        .pwm2(Net_28),
        .interrupt(Net_30),
        .capture(1'b0),
        .kill(Net_133),
        .enable(1'b1),
        .trigger(1'b0),
        .cmp_sel(1'b0),
        .pwm(Net_148),
        .ph1(Net_35),
        .ph2(Net_39));
    defparam pwm_right.Resolution = 16;

    PWM_v2_0_7 pwm_left (
        .reset(Net_112),
        .clock(Net_128),
        .tc(Net_40),
        .pwm1(Net_41),
        .pwm2(Net_42),
        .interrupt(Net_43),
        .capture(1'b0),
        .kill(Net_118),
        .enable(1'b1),
        .trigger(1'b0),
        .cmp_sel(1'b0),
        .pwm(Net_152),
        .ph1(Net_48),
        .ph2(Net_49));
    defparam pwm_left.Resolution = 16;

    // -- De Mux start --
    if (1)
    begin : demux_1
        reg  tmp__demux_1_0_reg;
        reg  tmp__demux_1_1_reg;
        always @(Net_148 or Net_149)
        begin
            case (Net_149)
                1'b0:
                begin
                    tmp__demux_1_0_reg = Net_148;
                    tmp__demux_1_1_reg = 1'b0;
                end
                1'b1:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = Net_148;
                end
            endcase
        end
        assign Net_203 = tmp__demux_1_0_reg;
        assign Net_204 = tmp__demux_1_1_reg;
    end
    // -- De Mux end --

    // -- De Mux start --
    if (1)
    begin : demux_2
        reg  tmp__demux_2_0_reg;
        reg  tmp__demux_2_1_reg;
        always @(Net_152 or Net_153)
        begin
            case (Net_153)
                1'b0:
                begin
                    tmp__demux_2_0_reg = Net_152;
                    tmp__demux_2_1_reg = 1'b0;
                end
                1'b1:
                begin
                    tmp__demux_2_0_reg = 1'b0;
                    tmp__demux_2_1_reg = Net_152;
                end
            endcase
        end
        assign Net_205 = tmp__demux_2_0_reg;
        assign Net_206 = tmp__demux_2_1_reg;
    end
    // -- De Mux end --

    CyControlReg_v1_50 pwm_right_control_reg (
        .control_1(Net_50),
        .control_2(Net_51),
        .control_3(Net_52),
        .control_0(Net_149),
        .control_4(Net_54),
        .control_5(Net_55),
        .control_6(Net_56),
        .control_7(Net_57),
        .clock(1'b0),
        .reset(1'b0));
    defparam pwm_right_control_reg.Bit0Mode = 0;
    defparam pwm_right_control_reg.Bit1Mode = 0;
    defparam pwm_right_control_reg.Bit2Mode = 0;
    defparam pwm_right_control_reg.Bit3Mode = 0;
    defparam pwm_right_control_reg.Bit4Mode = 0;
    defparam pwm_right_control_reg.Bit5Mode = 0;
    defparam pwm_right_control_reg.Bit6Mode = 0;
    defparam pwm_right_control_reg.Bit7Mode = 0;
    defparam pwm_right_control_reg.BitValue = 0;
    defparam pwm_right_control_reg.DeviceFamily = "PSoC3";
    defparam pwm_right_control_reg.ExternalReset = 0;
    defparam pwm_right_control_reg.NumOutputs = 1;
    defparam pwm_right_control_reg.SiliconRevision = "3  ";

    CyControlReg_v1_50 pwm_left_control_reg (
        .control_1(Net_60),
        .control_2(Net_61),
        .control_3(Net_62),
        .control_0(Net_153),
        .control_4(Net_63),
        .control_5(Net_64),
        .control_6(Net_65),
        .control_7(Net_66),
        .clock(1'b0),
        .reset(1'b0));
    defparam pwm_left_control_reg.Bit0Mode = 0;
    defparam pwm_left_control_reg.Bit1Mode = 0;
    defparam pwm_left_control_reg.Bit2Mode = 0;
    defparam pwm_left_control_reg.Bit3Mode = 0;
    defparam pwm_left_control_reg.Bit4Mode = 0;
    defparam pwm_left_control_reg.Bit5Mode = 0;
    defparam pwm_left_control_reg.Bit6Mode = 0;
    defparam pwm_left_control_reg.Bit7Mode = 0;
    defparam pwm_left_control_reg.BitValue = 0;
    defparam pwm_left_control_reg.DeviceFamily = "PSoC3";
    defparam pwm_left_control_reg.ExternalReset = 0;
    defparam pwm_left_control_reg.NumOutputs = 1;
    defparam pwm_left_control_reg.SiliconRevision = "3  ";

	wire [0:0] tmpOE__mot_right_backward_net;
	wire [0:0] tmpFB_0__mot_right_backward_net;
	wire [0:0] tmpIO_0__mot_right_backward_net;
	wire [0:0] tmpINTERRUPT_0__mot_right_backward_net;
	electrical [0:0] tmpSIOVREF__mot_right_backward_net;

	cy_psoc3_pins_v1_10
		#(.id("69fd2025-4e50-4eb7-a5df-e041e4c0ad77"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		mot_right_backward
		 (.oe(tmpOE__mot_right_backward_net),
		  .y({Net_203}),
		  .fb({tmpFB_0__mot_right_backward_net[0:0]}),
		  .io({tmpIO_0__mot_right_backward_net[0:0]}),
		  .siovref(tmpSIOVREF__mot_right_backward_net),
		  .interrupt({tmpINTERRUPT_0__mot_right_backward_net[0:0]}));

	assign tmpOE__mot_right_backward_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__mot_right_forward_net;
	wire [0:0] tmpFB_0__mot_right_forward_net;
	wire [0:0] tmpIO_0__mot_right_forward_net;
	wire [0:0] tmpINTERRUPT_0__mot_right_forward_net;
	electrical [0:0] tmpSIOVREF__mot_right_forward_net;

	cy_psoc3_pins_v1_10
		#(.id("46ad97d5-e30f-4214-b8bc-964191636993"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		mot_right_forward
		 (.oe(tmpOE__mot_right_forward_net),
		  .y({Net_204}),
		  .fb({tmpFB_0__mot_right_forward_net[0:0]}),
		  .io({tmpIO_0__mot_right_forward_net[0:0]}),
		  .siovref(tmpSIOVREF__mot_right_forward_net),
		  .interrupt({tmpINTERRUPT_0__mot_right_forward_net[0:0]}));

	assign tmpOE__mot_right_forward_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__mot_left_backward_net;
	wire [0:0] tmpFB_0__mot_left_backward_net;
	wire [0:0] tmpIO_0__mot_left_backward_net;
	wire [0:0] tmpINTERRUPT_0__mot_left_backward_net;
	electrical [0:0] tmpSIOVREF__mot_left_backward_net;

	cy_psoc3_pins_v1_10
		#(.id("301556c4-ced9-4256-bb99-5865cc34c281"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		mot_left_backward
		 (.oe(tmpOE__mot_left_backward_net),
		  .y({Net_205}),
		  .fb({tmpFB_0__mot_left_backward_net[0:0]}),
		  .io({tmpIO_0__mot_left_backward_net[0:0]}),
		  .siovref(tmpSIOVREF__mot_left_backward_net),
		  .interrupt({tmpINTERRUPT_0__mot_left_backward_net[0:0]}));

	assign tmpOE__mot_left_backward_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__mot_left_forward_net;
	wire [0:0] tmpFB_0__mot_left_forward_net;
	wire [0:0] tmpIO_0__mot_left_forward_net;
	wire [0:0] tmpINTERRUPT_0__mot_left_forward_net;
	electrical [0:0] tmpSIOVREF__mot_left_forward_net;

	cy_psoc3_pins_v1_10
		#(.id("fd4e35b5-5175-428e-87ef-586371104ccf"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		mot_left_forward
		 (.oe(tmpOE__mot_left_forward_net),
		  .y({Net_206}),
		  .fb({tmpFB_0__mot_left_forward_net[0:0]}),
		  .io({tmpIO_0__mot_left_forward_net[0:0]}),
		  .siovref(tmpSIOVREF__mot_left_forward_net),
		  .interrupt({tmpINTERRUPT_0__mot_left_forward_net[0:0]}));

	assign tmpOE__mot_left_forward_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    ZeroTerminal ZeroTerminal_3 (
        .z(Net_98));

    ZeroTerminal ZeroTerminal_4 (
        .z(Net_112));


	cy_clock_v1_0
		#(.id("2a3c9bd1-45f4-47dd-8d47-1fe1b97b5ab3"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_PWM
		 (.clock_out(Net_128));


    ZeroTerminal ZeroTerminal_5 (
        .z(Net_118));

    ZeroTerminal ZeroTerminal_6 (
        .z(Net_133));



endmodule

