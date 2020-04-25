// niosSys_mm_interconnect_2.v

// This file was auto-generated from altera_mm_interconnect_hw.tcl.  If you edit it your changes
// will probably be lost.
// 
// Generated using ACDS version 16.1 196

`timescale 1 ps / 1 ps
module niosSys_mm_interconnect_2 (
		input  wire        clk_0_clk_clk,                                                   //                                         clk_0_clk.clk
		input  wire        nios2_qsys_0_reset_n_reset_bridge_in_reset_reset,                //        nios2_qsys_0_reset_n_reset_bridge_in_reset.reset
		input  wire [10:0] nios2_qsys_0_tightly_coupled_instruction_master_0_address,       // nios2_qsys_0_tightly_coupled_instruction_master_0.address
		output wire        nios2_qsys_0_tightly_coupled_instruction_master_0_waitrequest,   //                                                  .waitrequest
		input  wire        nios2_qsys_0_tightly_coupled_instruction_master_0_read,          //                                                  .read
		output wire [31:0] nios2_qsys_0_tightly_coupled_instruction_master_0_readdata,      //                                                  .readdata
		output wire        nios2_qsys_0_tightly_coupled_instruction_master_0_readdatavalid, //                                                  .readdatavalid
		input  wire        nios2_qsys_0_tightly_coupled_instruction_master_0_clken,         //                                                  .clken
		output wire [8:0]  TCM_s1_address,                                                  //                                            TCM_s1.address
		output wire        TCM_s1_write,                                                    //                                                  .write
		input  wire [31:0] TCM_s1_readdata,                                                 //                                                  .readdata
		output wire [31:0] TCM_s1_writedata,                                                //                                                  .writedata
		output wire [3:0]  TCM_s1_byteenable,                                               //                                                  .byteenable
		output wire        TCM_s1_chipselect,                                               //                                                  .chipselect
		output wire        TCM_s1_clken                                                     //                                                  .clken
	);

	wire         nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_waitrequest;   // TCM_s1_translator:uav_waitrequest -> nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_waitrequest
	wire  [31:0] nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_readdata;      // TCM_s1_translator:uav_readdata -> nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_readdata
	wire         nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_debugaccess;   // nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_debugaccess -> TCM_s1_translator:uav_debugaccess
	wire  [10:0] nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_address;       // nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_address -> TCM_s1_translator:uav_address
	wire         nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_read;          // nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_read -> TCM_s1_translator:uav_read
	wire   [3:0] nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_byteenable;    // nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_byteenable -> TCM_s1_translator:uav_byteenable
	wire         nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_readdatavalid; // TCM_s1_translator:uav_readdatavalid -> nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_readdatavalid
	wire         nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_lock;          // nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_lock -> TCM_s1_translator:uav_lock
	wire         nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_write;         // nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_write -> TCM_s1_translator:uav_write
	wire  [31:0] nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_writedata;     // nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_writedata -> TCM_s1_translator:uav_writedata
	wire         nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_clken;         // nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_clken -> TCM_s1_translator:uav_clken
	wire   [2:0] nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_burstcount;    // nios2_qsys_0_tightly_coupled_instruction_master_0_translator:uav_burstcount -> TCM_s1_translator:uav_burstcount

	altera_merlin_master_translator #(
		.AV_ADDRESS_W                (11),
		.AV_DATA_W                   (32),
		.AV_BURSTCOUNT_W             (1),
		.AV_BYTEENABLE_W             (4),
		.UAV_ADDRESS_W               (11),
		.UAV_BURSTCOUNT_W            (3),
		.USE_READ                    (1),
		.USE_WRITE                   (0),
		.USE_BEGINBURSTTRANSFER      (0),
		.USE_BEGINTRANSFER           (0),
		.USE_CHIPSELECT              (0),
		.USE_BURSTCOUNT              (0),
		.USE_READDATAVALID           (1),
		.USE_WAITREQUEST             (1),
		.USE_READRESPONSE            (0),
		.USE_WRITERESPONSE           (0),
		.AV_SYMBOLS_PER_WORD         (4),
		.AV_ADDRESS_SYMBOLS          (1),
		.AV_BURSTCOUNT_SYMBOLS       (0),
		.AV_CONSTANT_BURST_BEHAVIOR  (0),
		.UAV_CONSTANT_BURST_BEHAVIOR (0),
		.AV_LINEWRAPBURSTS           (0),
		.AV_REGISTERINCOMINGSIGNALS  (0)
	) nios2_qsys_0_tightly_coupled_instruction_master_0_translator (
		.clk                    (clk_0_clk_clk),                                                                                        //                       clk.clk
		.reset                  (nios2_qsys_0_reset_n_reset_bridge_in_reset_reset),                                                     //                     reset.reset
		.uav_address            (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_address),       // avalon_universal_master_0.address
		.uav_burstcount         (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_burstcount),    //                          .burstcount
		.uav_read               (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_read),          //                          .read
		.uav_write              (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_write),         //                          .write
		.uav_waitrequest        (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_waitrequest),   //                          .waitrequest
		.uav_readdatavalid      (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_readdatavalid), //                          .readdatavalid
		.uav_byteenable         (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_byteenable),    //                          .byteenable
		.uav_readdata           (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_readdata),      //                          .readdata
		.uav_writedata          (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_writedata),     //                          .writedata
		.uav_lock               (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_lock),          //                          .lock
		.uav_debugaccess        (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_debugaccess),   //                          .debugaccess
		.uav_clken              (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_clken),         //                          .clken
		.av_address             (nios2_qsys_0_tightly_coupled_instruction_master_0_address),                                            //      avalon_anti_master_0.address
		.av_waitrequest         (nios2_qsys_0_tightly_coupled_instruction_master_0_waitrequest),                                        //                          .waitrequest
		.av_read                (nios2_qsys_0_tightly_coupled_instruction_master_0_read),                                               //                          .read
		.av_readdata            (nios2_qsys_0_tightly_coupled_instruction_master_0_readdata),                                           //                          .readdata
		.av_readdatavalid       (nios2_qsys_0_tightly_coupled_instruction_master_0_readdatavalid),                                      //                          .readdatavalid
		.av_clken               (nios2_qsys_0_tightly_coupled_instruction_master_0_clken),                                              //                          .clken
		.av_burstcount          (1'b1),                                                                                                 //               (terminated)
		.av_byteenable          (4'b1111),                                                                                              //               (terminated)
		.av_beginbursttransfer  (1'b0),                                                                                                 //               (terminated)
		.av_begintransfer       (1'b0),                                                                                                 //               (terminated)
		.av_chipselect          (1'b0),                                                                                                 //               (terminated)
		.av_write               (1'b0),                                                                                                 //               (terminated)
		.av_writedata           (32'b00000000000000000000000000000000),                                                                 //               (terminated)
		.av_lock                (1'b0),                                                                                                 //               (terminated)
		.av_debugaccess         (1'b0),                                                                                                 //               (terminated)
		.uav_response           (2'b00),                                                                                                //               (terminated)
		.av_response            (),                                                                                                     //               (terminated)
		.uav_writeresponsevalid (1'b0),                                                                                                 //               (terminated)
		.av_writeresponsevalid  ()                                                                                                      //               (terminated)
	);

	altera_merlin_slave_translator #(
		.AV_ADDRESS_W                   (9),
		.AV_DATA_W                      (32),
		.UAV_DATA_W                     (32),
		.AV_BURSTCOUNT_W                (1),
		.AV_BYTEENABLE_W                (4),
		.UAV_BYTEENABLE_W               (4),
		.UAV_ADDRESS_W                  (11),
		.UAV_BURSTCOUNT_W               (3),
		.AV_READLATENCY                 (1),
		.USE_READDATAVALID              (0),
		.USE_WAITREQUEST                (0),
		.USE_UAV_CLKEN                  (1),
		.USE_READRESPONSE               (0),
		.USE_WRITERESPONSE              (0),
		.AV_SYMBOLS_PER_WORD            (4),
		.AV_ADDRESS_SYMBOLS             (0),
		.AV_BURSTCOUNT_SYMBOLS          (0),
		.AV_CONSTANT_BURST_BEHAVIOR     (0),
		.UAV_CONSTANT_BURST_BEHAVIOR    (0),
		.AV_REQUIRE_UNALIGNED_ADDRESSES (0),
		.CHIPSELECT_THROUGH_READLATENCY (0),
		.AV_READ_WAIT_CYCLES            (0),
		.AV_WRITE_WAIT_CYCLES           (0),
		.AV_SETUP_WAIT_CYCLES           (0),
		.AV_DATA_HOLD_CYCLES            (0)
	) tcm_s1_translator (
		.clk                    (clk_0_clk_clk),                                                                                        //                      clk.clk
		.reset                  (nios2_qsys_0_reset_n_reset_bridge_in_reset_reset),                                                     //                    reset.reset
		.uav_address            (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_address),       // avalon_universal_slave_0.address
		.uav_burstcount         (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_burstcount),    //                         .burstcount
		.uav_read               (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_read),          //                         .read
		.uav_write              (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_write),         //                         .write
		.uav_waitrequest        (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_waitrequest),   //                         .waitrequest
		.uav_readdatavalid      (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_readdatavalid), //                         .readdatavalid
		.uav_byteenable         (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_byteenable),    //                         .byteenable
		.uav_readdata           (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_readdata),      //                         .readdata
		.uav_writedata          (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_writedata),     //                         .writedata
		.uav_lock               (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_lock),          //                         .lock
		.uav_debugaccess        (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_debugaccess),   //                         .debugaccess
		.uav_clken              (nios2_qsys_0_tightly_coupled_instruction_master_0_translator_avalon_universal_master_0_clken),         //                         .clken
		.av_address             (TCM_s1_address),                                                                                       //      avalon_anti_slave_0.address
		.av_write               (TCM_s1_write),                                                                                         //                         .write
		.av_readdata            (TCM_s1_readdata),                                                                                      //                         .readdata
		.av_writedata           (TCM_s1_writedata),                                                                                     //                         .writedata
		.av_byteenable          (TCM_s1_byteenable),                                                                                    //                         .byteenable
		.av_chipselect          (TCM_s1_chipselect),                                                                                    //                         .chipselect
		.av_clken               (TCM_s1_clken),                                                                                         //                         .clken
		.av_read                (),                                                                                                     //              (terminated)
		.av_begintransfer       (),                                                                                                     //              (terminated)
		.av_beginbursttransfer  (),                                                                                                     //              (terminated)
		.av_burstcount          (),                                                                                                     //              (terminated)
		.av_readdatavalid       (1'b0),                                                                                                 //              (terminated)
		.av_waitrequest         (1'b0),                                                                                                 //              (terminated)
		.av_writebyteenable     (),                                                                                                     //              (terminated)
		.av_lock                (),                                                                                                     //              (terminated)
		.av_debugaccess         (),                                                                                                     //              (terminated)
		.av_outputenable        (),                                                                                                     //              (terminated)
		.uav_response           (),                                                                                                     //              (terminated)
		.av_response            (2'b00),                                                                                                //              (terminated)
		.uav_writeresponsevalid (),                                                                                                     //              (terminated)
		.av_writeresponsevalid  (1'b0)                                                                                                  //              (terminated)
	);

endmodule