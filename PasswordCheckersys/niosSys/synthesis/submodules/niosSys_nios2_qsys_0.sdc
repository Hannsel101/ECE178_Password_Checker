# Legal Notice: (C)2020 Altera Corporation. All rights reserved.  Your
# use of Altera Corporation's design tools, logic functions and other
# software and tools, and its AMPP partner logic functions, and any
# output files any of the foregoing (including device programming or
# simulation files), and any associated documentation or information are
# expressly subject to the terms and conditions of the Altera Program
# License Subscription Agreement or other applicable license agreement,
# including, without limitation, that your use is for the sole purpose
# of programming logic devices manufactured by Altera and sold by Altera
# or its authorized distributors.  Please refer to the applicable
# agreement for further details.

#**************************************************************
# Timequest JTAG clock definition
#   Uncommenting the following lines will define the JTAG
#   clock in TimeQuest Timing Analyzer
#**************************************************************

#create_clock -period 10MHz {altera_reserved_tck}
#set_clock_groups -asynchronous -group {altera_reserved_tck}

#**************************************************************
# Set TCL Path Variables 
#**************************************************************

set 	niosSys_nios2_qsys_0 	niosSys_nios2_qsys_0:*
set 	niosSys_nios2_qsys_0_oci 	niosSys_nios2_qsys_0_nios2_oci:the_niosSys_nios2_qsys_0_nios2_oci
set 	niosSys_nios2_qsys_0_oci_break 	niosSys_nios2_qsys_0_nios2_oci_break:the_niosSys_nios2_qsys_0_nios2_oci_break
set 	niosSys_nios2_qsys_0_ocimem 	niosSys_nios2_qsys_0_nios2_ocimem:the_niosSys_nios2_qsys_0_nios2_ocimem
set 	niosSys_nios2_qsys_0_oci_debug 	niosSys_nios2_qsys_0_nios2_oci_debug:the_niosSys_nios2_qsys_0_nios2_oci_debug
set 	niosSys_nios2_qsys_0_wrapper 	niosSys_nios2_qsys_0_jtag_debug_module_wrapper:the_niosSys_nios2_qsys_0_jtag_debug_module_wrapper
set 	niosSys_nios2_qsys_0_jtag_tck 	niosSys_nios2_qsys_0_jtag_debug_module_tck:the_niosSys_nios2_qsys_0_jtag_debug_module_tck
set 	niosSys_nios2_qsys_0_jtag_sysclk 	niosSys_nios2_qsys_0_jtag_debug_module_sysclk:the_niosSys_nios2_qsys_0_jtag_debug_module_sysclk
set 	niosSys_nios2_qsys_0_oci_path 	 [format "%s|%s" $niosSys_nios2_qsys_0 $niosSys_nios2_qsys_0_oci]
set 	niosSys_nios2_qsys_0_oci_break_path 	 [format "%s|%s" $niosSys_nios2_qsys_0_oci_path $niosSys_nios2_qsys_0_oci_break]
set 	niosSys_nios2_qsys_0_ocimem_path 	 [format "%s|%s" $niosSys_nios2_qsys_0_oci_path $niosSys_nios2_qsys_0_ocimem]
set 	niosSys_nios2_qsys_0_oci_debug_path 	 [format "%s|%s" $niosSys_nios2_qsys_0_oci_path $niosSys_nios2_qsys_0_oci_debug]
set 	niosSys_nios2_qsys_0_jtag_tck_path 	 [format "%s|%s|%s" $niosSys_nios2_qsys_0_oci_path $niosSys_nios2_qsys_0_wrapper $niosSys_nios2_qsys_0_jtag_tck]
set 	niosSys_nios2_qsys_0_jtag_sysclk_path 	 [format "%s|%s|%s" $niosSys_nios2_qsys_0_oci_path $niosSys_nios2_qsys_0_wrapper $niosSys_nios2_qsys_0_jtag_sysclk]
set 	niosSys_nios2_qsys_0_jtag_sr 	 [format "%s|*sr" $niosSys_nios2_qsys_0_jtag_tck_path]

#**************************************************************
# Set False Paths
#**************************************************************

set_false_path -from [get_keepers *$niosSys_nios2_qsys_0_oci_break_path|break_readreg*] -to [get_keepers *$niosSys_nios2_qsys_0_jtag_sr*]
set_false_path -from [get_keepers *$niosSys_nios2_qsys_0_oci_debug_path|*resetlatch]     -to [get_keepers *$niosSys_nios2_qsys_0_jtag_sr[33]]
set_false_path -from [get_keepers *$niosSys_nios2_qsys_0_oci_debug_path|monitor_ready]  -to [get_keepers *$niosSys_nios2_qsys_0_jtag_sr[0]]
set_false_path -from [get_keepers *$niosSys_nios2_qsys_0_oci_debug_path|monitor_error]  -to [get_keepers *$niosSys_nios2_qsys_0_jtag_sr[34]]
set_false_path -from [get_keepers *$niosSys_nios2_qsys_0_ocimem_path|*MonDReg*] -to [get_keepers *$niosSys_nios2_qsys_0_jtag_sr*]
set_false_path -from *$niosSys_nios2_qsys_0_jtag_sr*    -to *$niosSys_nios2_qsys_0_jtag_sysclk_path|*jdo*
set_false_path -from sld_hub:*|irf_reg* -to *$niosSys_nios2_qsys_0_jtag_sysclk_path|ir*
set_false_path -from sld_hub:*|sld_shadow_jsm:shadow_jsm|state[1] -to *$niosSys_nios2_qsys_0_oci_debug_path|monitor_go
