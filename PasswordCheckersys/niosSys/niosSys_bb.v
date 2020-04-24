
module niosSys (
	hex_0_export,
	hex_1_export,
	hex_2_export,
	hex_3_export,
	hex_4_export,
	hex_5_export,
	hex_6_export,
	hex_7_export,
	key_0_export,
	ledg_export,
	leds_export,
	ref_clk_clk,
	ref_reset_reset,
	sd_b_SD_cmd,
	sd_b_SD_dat,
	sd_b_SD_dat3,
	sd_o_SD_clock,
	sdram_addr,
	sdram_ba,
	sdram_cas_n,
	sdram_cke,
	sdram_cs_n,
	sdram_dq,
	sdram_dqm,
	sdram_ras_n,
	sdram_we_n,
	sdram_clk_clk,
	switches_export,
	lcd_DATA,
	lcd_ON,
	lcd_BLON,
	lcd_EN,
	lcd_RS,
	lcd_RW);	

	output	[6:0]	hex_0_export;
	output	[6:0]	hex_1_export;
	output	[6:0]	hex_2_export;
	output	[6:0]	hex_3_export;
	output	[6:0]	hex_4_export;
	output	[6:0]	hex_5_export;
	output	[6:0]	hex_6_export;
	output	[6:0]	hex_7_export;
	input	[3:0]	key_0_export;
	output	[7:0]	ledg_export;
	output	[17:0]	leds_export;
	input		ref_clk_clk;
	input		ref_reset_reset;
	inout		sd_b_SD_cmd;
	inout		sd_b_SD_dat;
	inout		sd_b_SD_dat3;
	output		sd_o_SD_clock;
	output	[12:0]	sdram_addr;
	output	[1:0]	sdram_ba;
	output		sdram_cas_n;
	output		sdram_cke;
	output		sdram_cs_n;
	inout	[31:0]	sdram_dq;
	output	[3:0]	sdram_dqm;
	output		sdram_ras_n;
	output		sdram_we_n;
	output		sdram_clk_clk;
	input	[17:0]	switches_export;
	inout	[7:0]	lcd_DATA;
	output		lcd_ON;
	output		lcd_BLON;
	output		lcd_EN;
	output		lcd_RS;
	output		lcd_RW;
endmodule
