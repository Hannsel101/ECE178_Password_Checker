	component niosSys is
		port (
			hex_0_export    : out   std_logic_vector(6 downto 0);                     -- export
			hex_1_export    : out   std_logic_vector(6 downto 0);                     -- export
			hex_2_export    : out   std_logic_vector(6 downto 0);                     -- export
			hex_3_export    : out   std_logic_vector(6 downto 0);                     -- export
			hex_4_export    : out   std_logic_vector(6 downto 0);                     -- export
			hex_5_export    : out   std_logic_vector(6 downto 0);                     -- export
			hex_6_export    : out   std_logic_vector(6 downto 0);                     -- export
			hex_7_export    : out   std_logic_vector(6 downto 0);                     -- export
			key_0_export    : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			ledg_export     : out   std_logic_vector(7 downto 0);                     -- export
			leds_export     : out   std_logic_vector(17 downto 0);                    -- export
			ref_clk_clk     : in    std_logic                     := 'X';             -- clk
			ref_reset_reset : in    std_logic                     := 'X';             -- reset
			sd_b_SD_cmd     : inout std_logic                     := 'X';             -- b_SD_cmd
			sd_b_SD_dat     : inout std_logic                     := 'X';             -- b_SD_dat
			sd_b_SD_dat3    : inout std_logic                     := 'X';             -- b_SD_dat3
			sd_o_SD_clock   : out   std_logic;                                        -- o_SD_clock
			sdram_addr      : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_ba        : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_cas_n     : out   std_logic;                                        -- cas_n
			sdram_cke       : out   std_logic;                                        -- cke
			sdram_cs_n      : out   std_logic;                                        -- cs_n
			sdram_dq        : inout std_logic_vector(31 downto 0) := (others => 'X'); -- dq
			sdram_dqm       : out   std_logic_vector(3 downto 0);                     -- dqm
			sdram_ras_n     : out   std_logic;                                        -- ras_n
			sdram_we_n      : out   std_logic;                                        -- we_n
			sdram_clk_clk   : out   std_logic;                                        -- clk
			switches_export : in    std_logic_vector(17 downto 0) := (others => 'X'); -- export
			lcd_DATA        : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- DATA
			lcd_ON          : out   std_logic;                                        -- ON
			lcd_BLON        : out   std_logic;                                        -- BLON
			lcd_EN          : out   std_logic;                                        -- EN
			lcd_RS          : out   std_logic;                                        -- RS
			lcd_RW          : out   std_logic                                         -- RW
		);
	end component niosSys;

	u0 : component niosSys
		port map (
			hex_0_export    => CONNECTED_TO_hex_0_export,    --     hex_0.export
			hex_1_export    => CONNECTED_TO_hex_1_export,    --     hex_1.export
			hex_2_export    => CONNECTED_TO_hex_2_export,    --     hex_2.export
			hex_3_export    => CONNECTED_TO_hex_3_export,    --     hex_3.export
			hex_4_export    => CONNECTED_TO_hex_4_export,    --     hex_4.export
			hex_5_export    => CONNECTED_TO_hex_5_export,    --     hex_5.export
			hex_6_export    => CONNECTED_TO_hex_6_export,    --     hex_6.export
			hex_7_export    => CONNECTED_TO_hex_7_export,    --     hex_7.export
			key_0_export    => CONNECTED_TO_key_0_export,    --     key_0.export
			ledg_export     => CONNECTED_TO_ledg_export,     --      ledg.export
			leds_export     => CONNECTED_TO_leds_export,     --      leds.export
			ref_clk_clk     => CONNECTED_TO_ref_clk_clk,     --   ref_clk.clk
			ref_reset_reset => CONNECTED_TO_ref_reset_reset, -- ref_reset.reset
			sd_b_SD_cmd     => CONNECTED_TO_sd_b_SD_cmd,     --        sd.b_SD_cmd
			sd_b_SD_dat     => CONNECTED_TO_sd_b_SD_dat,     --          .b_SD_dat
			sd_b_SD_dat3    => CONNECTED_TO_sd_b_SD_dat3,    --          .b_SD_dat3
			sd_o_SD_clock   => CONNECTED_TO_sd_o_SD_clock,   --          .o_SD_clock
			sdram_addr      => CONNECTED_TO_sdram_addr,      --     sdram.addr
			sdram_ba        => CONNECTED_TO_sdram_ba,        --          .ba
			sdram_cas_n     => CONNECTED_TO_sdram_cas_n,     --          .cas_n
			sdram_cke       => CONNECTED_TO_sdram_cke,       --          .cke
			sdram_cs_n      => CONNECTED_TO_sdram_cs_n,      --          .cs_n
			sdram_dq        => CONNECTED_TO_sdram_dq,        --          .dq
			sdram_dqm       => CONNECTED_TO_sdram_dqm,       --          .dqm
			sdram_ras_n     => CONNECTED_TO_sdram_ras_n,     --          .ras_n
			sdram_we_n      => CONNECTED_TO_sdram_we_n,      --          .we_n
			sdram_clk_clk   => CONNECTED_TO_sdram_clk_clk,   -- sdram_clk.clk
			switches_export => CONNECTED_TO_switches_export, --  switches.export
			lcd_DATA        => CONNECTED_TO_lcd_DATA,        --       lcd.DATA
			lcd_ON          => CONNECTED_TO_lcd_ON,          --          .ON
			lcd_BLON        => CONNECTED_TO_lcd_BLON,        --          .BLON
			lcd_EN          => CONNECTED_TO_lcd_EN,          --          .EN
			lcd_RS          => CONNECTED_TO_lcd_RS,          --          .RS
			lcd_RW          => CONNECTED_TO_lcd_RW           --          .RW
		);

