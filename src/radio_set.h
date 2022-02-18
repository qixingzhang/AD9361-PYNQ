/*
 * radio_set.h
 *
 *  Created on: 2018��1��24��
 *      Author: liche
 */

#ifndef SRC_RADIO_SET_H_
#define SRC_RADIO_SET_H_
#include "ad9361_api.h"

/************************ad9361 struct************************************/
static AD9361_InitParam default_init_param = {
	/* Device selection */
	ID_AD9361,	// dev_sel
/* Identification number */
0,		//id_no;
	/* Reference Clock */
	40000000UL,	//reference_clk_rate
	/* Base Configuration */
	1,		//two_rx_two_tx_mode_enable *** adi,2rx-2tx-mode-enable
	1,		//one_rx_one_tx_mode_use_rx_num *** adi,1rx-1tx-mode-use-rx-num
	1,		//one_rx_one_tx_mode_use_tx_num *** adi,1rx-1tx-mode-use-tx-num
	1,		//frequency_division_duplex_mode_enable *** adi,frequency-division-duplex-mode-enable
	0,		//frequency_division_duplex_independent_mode_enable *** adi,frequency-division-duplex-independent-mode-enable
	0,		//tdd_use_dual_synth_mode_enable *** adi,tdd-use-dual-synth-mode-enable
	0,		//tdd_skip_vco_cal_enable *** adi,tdd-skip-vco-cal-enable
	0,		//tx_fastlock_delay_ns *** adi,tx-fastlock-delay-ns
	0,		//rx_fastlock_delay_ns *** adi,rx-fastlock-delay-ns
	0,		//rx_fastlock_pincontrol_enable *** adi,rx-fastlock-pincontrol-enable
	0,		//tx_fastlock_pincontrol_enable *** adi,tx-fastlock-pincontrol-enable
	0,		//external_rx_lo_enable *** adi,external-rx-lo-enable
	0,		//external_tx_lo_enable *** adi,external-tx-lo-enable
	5,		//dc_offset_tracking_update_event_mask *** adi,dc-offset-tracking-update-event-mask
	6,		//dc_offset_attenuation_high_range *** adi,dc-offset-attenuation-high-range
	5,		//dc_offset_attenuation_low_range *** adi,dc-offset-attenuation-low-range
	0x28,	//dc_offset_count_high_range *** adi,dc-offset-count-high-range
	0x32,	//dc_offset_count_low_range *** adi,dc-offset-count-low-range
	0,		//split_gain_table_mode_enable *** adi,split-gain-table-mode-enable
	MAX_SYNTH_FREF,	//trx_synthesizer_target_fref_overwrite_hz *** adi,trx-synthesizer-target-fref-overwrite-hz
	0,		// qec_tracking_slow_mode_enable *** adi,qec-tracking-slow-mode-enable
	/* ENSM Control */
	0,		//ensm_enable_pin_pulse_mode_enable *** adi,ensm-enable-pin-pulse-mode-enable
	0,		//ensm_enable_txnrx_control_enable *** adi,ensm-enable-txnrx-control-enable
	/* LO Control */
	2400000000UL,	//rx_synthesizer_frequency_hz *** adi,rx-synthesizer-frequency-hz
	2400000000UL,	//tx_synthesizer_frequency_hz *** adi,tx-synthesizer-frequency-hz
	/* Rate & BW Control */
	{ 1280000000, 320000000, 160000000, 80000000, 40000000, 40000000 },	//uint32_t	rx_path_clock_frequencies[6] *** adi,rx-path-clock-frequencies
	{ 1280000000, 160000000, 160000000, 80000000, 40000000, 40000000 },	//uint32_t	tx_path_clock_frequencies[6] *** adi,tx-path-clock-frequencies
	20000000,//rf_rx_bandwidth_hz *** adi,rf-rx-bandwidth-hz
	20000000,//rf_tx_bandwidth_hz *** adi,rf-tx-bandwidth-hz
	/* RF Port Control */
	0,		//rx_rf_port_input_select *** adi,rx-rf-port-input-select
	0,		//tx_rf_port_input_select *** adi,tx-rf-port-input-select
	/* TX Attenuation Control */
	20000,	//tx_attenuation_mdB *** adi,tx-attenuation-mdB
	0,		//update_tx_gain_in_alert_enable *** adi,update-tx-gain-in-alert-enable
	/* Reference Clock Control */
	1,		//xo_disable_use_ext_refclk_enable *** adi,xo-disable-use-ext-refclk-enable
	{8, 5920},	//dcxo_coarse_and_fine_tune[2] *** adi,dcxo-coarse-and-fine-tune
	ADC_CLK_DIV_16,	//clk_output_mode_select *** adi,clk-output-mode-select
	/* Gain Control */
	0,		//gc_rx1_mode *** adi,gc-rx1-mode
	0,		//gc_rx2_mode *** adi,gc-rx2-mode
	58,		//gc_adc_large_overload_thresh *** adi,gc-adc-large-overload-thresh
	4,		//gc_adc_ovr_sample_size *** adi,gc-adc-ovr-sample-size
	47,		//gc_adc_small_overload_thresh *** adi,gc-adc-small-overload-thresh
	8192,	//gc_dec_pow_measurement_duration *** adi,gc-dec-pow-measurement-duration
	0,		//gc_dig_gain_enable *** adi,gc-dig-gain-enable
	800,//gc_lmt_overload_high_thresh *** adi,gc-lmt-overload-high-thresh
	704,	//gc_lmt_overload_low_thresh *** adi,gc-lmt-overload-low-thresh
	24,		//gc_low_power_thresh *** adi,gc-low-power-thresh
	15,		//gc_max_dig_gain *** adi,gc-max-dig-gain
	/* Gain MGC Control */
	2,		//mgc_dec_gain_step *** adi,mgc-dec-gain-step
	2,		//mgc_inc_gain_step *** adi,mgc-inc-gain-step
	0,		//mgc_rx1_ctrl_inp_enable *** adi,mgc-rx1-ctrl-inp-enable
	0,		//mgc_rx2_ctrl_inp_enable *** adi,mgc-rx2-ctrl-inp-enable
	0,		//mgc_split_table_ctrl_inp_gain_mode *** adi,mgc-split-table-ctrl-inp-gain-mode
	/* Gain AGC Control */
	10,		//agc_adc_large_overload_exceed_counter *** adi,agc-adc-large-overload-exceed-counter
	2,		//agc_adc_large_overload_inc_steps *** adi,agc-adc-large-overload-inc-steps
	0,		//agc_adc_lmt_small_overload_prevent_gain_inc_enable *** adi,agc-adc-lmt-small-overload-prevent-gain-inc-enable
	10,		//agc_adc_small_overload_exceed_counter *** adi,agc-adc-small-overload-exceed-counter
	4,		//agc_dig_gain_step_size *** adi,agc-dig-gain-step-size
	3,		//agc_dig_saturation_exceed_counter *** adi,agc-dig-saturation-exceed-counter
	1000,	// agc_gain_update_interval_us *** adi,agc-gain-update-interval-us
	0,		//agc_immed_gain_change_if_large_adc_overload_enable *** adi,agc-immed-gain-change-if-large-adc-overload-enable
	0,		//agc_immed_gain_change_if_large_lmt_overload_enable *** adi,agc-immed-gain-change-if-large-lmt-overload-enable
	10,		//agc_inner_thresh_high *** adi,agc-inner-thresh-high
	1,		//agc_inner_thresh_high_dec_steps *** adi,agc-inner-thresh-high-dec-steps
	12,		//agc_inner_thresh_low *** adi,agc-inner-thresh-low
	1,		//agc_inner_thresh_low_inc_steps *** adi,agc-inner-thresh-low-inc-steps
	10,		//agc_lmt_overload_large_exceed_counter *** adi,agc-lmt-overload-large-exceed-counter
	2,		//agc_lmt_overload_large_inc_steps *** adi,agc-lmt-overload-large-inc-steps
	10,		//agc_lmt_overload_small_exceed_counter *** adi,agc-lmt-overload-small-exceed-counter
	5,		//agc_outer_thresh_high *** adi,agc-outer-thresh-high
	2,		//agc_outer_thresh_high_dec_steps *** adi,agc-outer-thresh-high-dec-steps
	18,		//agc_outer_thresh_low *** adi,agc-outer-thresh-low
	2,		//agc_outer_thresh_low_inc_steps *** adi,agc-outer-thresh-low-inc-steps
	1,		//agc_attack_delay_extra_margin_us; *** adi,agc-attack-delay-extra-margin-us
	0,		//agc_sync_for_gain_counter_enable *** adi,agc-sync-for-gain-counter-enable
	/* Fast AGC */
	64,		//fagc_dec_pow_measuremnt_duration ***  adi,fagc-dec-pow-measurement-duration
	260,	//fagc_state_wait_time_ns ***  adi,fagc-state-wait-time-ns
	/* Fast AGC - Low Power */
	0,		//fagc_allow_agc_gain_increase ***  adi,fagc-allow-agc-gain-increase-enable
	5,		//fagc_lp_thresh_increment_time ***  adi,fagc-lp-thresh-increment-time
	1,		//fagc_lp_thresh_increment_steps ***  adi,fagc-lp-thresh-increment-steps
	/* Fast AGC - Lock Level */
	10,		//fagc_lock_level ***  adi,fagc-lock-level
	1,		//fagc_lock_level_lmt_gain_increase_en ***  adi,fagc-lock-level-lmt-gain-increase-enable
	5,		//fagc_lock_level_gain_increase_upper_limit ***  adi,fagc-lock-level-gain-increase-upper-limit
	/* Fast AGC - Peak Detectors and Final Settling */
	1,		//fagc_lpf_final_settling_steps ***  adi,fagc-lpf-final-settling-steps
	1,		//fagc_lmt_final_settling_steps ***  adi,fagc-lmt-final-settling-steps
	3,		//fagc_final_overrange_count ***  adi,fagc-final-overrange-count
	/* Fast AGC - Final Power Test */
	0,		//fagc_gain_increase_after_gain_lock_en ***  adi,fagc-gain-increase-after-gain-lock-enable
	/* Fast AGC - Unlocking the Gain */
	0,		//fagc_gain_index_type_after_exit_rx_mode ***  adi,fagc-gain-index-type-after-exit-rx-mode
	1,		//fagc_use_last_lock_level_for_set_gain_en ***  adi,fagc-use-last-lock-level-for-set-gain-enable
	1,		//fagc_rst_gla_stronger_sig_thresh_exceeded_en ***  adi,fagc-rst-gla-stronger-sig-thresh-exceeded-enable
	5,		//fagc_optimized_gain_offset ***  adi,fagc-optimized-gain-offset
	10,		//fagc_rst_gla_stronger_sig_thresh_above_ll ***  adi,fagc-rst-gla-stronger-sig-thresh-above-ll
	1,		//fagc_rst_gla_engergy_lost_sig_thresh_exceeded_en ***  adi,fagc-rst-gla-engergy-lost-sig-thresh-exceeded-enable
	1,		//fagc_rst_gla_engergy_lost_goto_optim_gain_en ***  adi,fagc-rst-gla-engergy-lost-goto-optim-gain-enable
	10,		//fagc_rst_gla_engergy_lost_sig_thresh_below_ll ***  adi,fagc-rst-gla-engergy-lost-sig-thresh-below-ll
	8,		//fagc_energy_lost_stronger_sig_gain_lock_exit_cnt ***  adi,fagc-energy-lost-stronger-sig-gain-lock-exit-cnt
	1,		//fagc_rst_gla_large_adc_overload_en ***  adi,fagc-rst-gla-large-adc-overload-enable
	1,		//fagc_rst_gla_large_lmt_overload_en ***  adi,fagc-rst-gla-large-lmt-overload-enable
	0,		//fagc_rst_gla_en_agc_pulled_high_en ***  adi,fagc-rst-gla-en-agc-pulled-high-enable
	0,		//fagc_rst_gla_if_en_agc_pulled_high_mode ***  adi,fagc-rst-gla-if-en-agc-pulled-high-mode
	64,		//fagc_power_measurement_duration_in_state5 ***  adi,fagc-power-measurement-duration-in-state5
	/* RSSI Control */
	1,		//rssi_delay *** adi,rssi-delay
	1000,	//rssi_duration *** adi,rssi-duration
	3,		//rssi_restart_mode *** adi,rssi-restart-mode
	0,		//rssi_unit_is_rx_samples_enable *** adi,rssi-unit-is-rx-samples-enable
	1,		//rssi_wait *** adi,rssi-wait
	/* Aux ADC Control */
	256,	//aux_adc_decimation *** adi,aux-adc-decimation
	40000000UL,	//aux_adc_rate *** adi,aux-adc-rate
	/* AuxDAC Control */
	1,		//aux_dac_manual_mode_enable ***  adi,aux-dac-manual-mode-enable
	1600,	//aux_dac1_default_value_mV ***  adi,aux-dac1-default-value-mV
	0,		//aux_dac1_active_in_rx_enable ***  adi,aux-dac1-active-in-rx-enable
	0,		//aux_dac1_active_in_tx_enable ***  adi,aux-dac1-active-in-tx-enable
	0,		//aux_dac1_active_in_alert_enable ***  adi,aux-dac1-active-in-alert-enable
	0,		//aux_dac1_rx_delay_us ***  adi,aux-dac1-rx-delay-us
	0,		//aux_dac1_tx_delay_us ***  adi,aux-dac1-tx-delay-us
	0,		//aux_dac2_default_value_mV ***  adi,aux-dac2-default-value-mV
	0,		//aux_dac2_active_in_rx_enable ***  adi,aux-dac2-active-in-rx-enable
	0,		//aux_dac2_active_in_tx_enable ***  adi,aux-dac2-active-in-tx-enable
	0,		//aux_dac2_active_in_alert_enable ***  adi,aux-dac2-active-in-alert-enable
	0,		//aux_dac2_rx_delay_us ***  adi,aux-dac2-rx-delay-us
	0,		//aux_dac2_tx_delay_us ***  adi,aux-dac2-tx-delay-us
	/* Temperature Sensor Control */
	256,	//temp_sense_decimation *** adi,temp-sense-decimation
	1000,	//temp_sense_measurement_interval_ms *** adi,temp-sense-measurement-interval-ms
	0xCE,	//temp_sense_offset_signed *** adi,temp-sense-offset-signed
	1,		//temp_sense_periodic_measurement_enable *** adi,temp-sense-periodic-measurement-enable
	/* Control Out Setup */
	0xFF,	//ctrl_outs_enable_mask *** adi,ctrl-outs-enable-mask
	0,		//ctrl_outs_index *** adi,ctrl-outs-index
	/* External LNA Control */
	0,		//elna_settling_delay_ns *** adi,elna-settling-delay-ns
	0,		//elna_gain_mdB *** adi,elna-gain-mdB
	0,		//elna_bypass_loss_mdB *** adi,elna-bypass-loss-mdB
	0,		//elna_rx1_gpo0_control_enable *** adi,elna-rx1-gpo0-control-enable
	0,		//elna_rx2_gpo1_control_enable *** adi,elna-rx2-gpo1-control-enable
	0,		//elna_gaintable_all_index_enable *** adi,elna-gaintable-all-index-enable
	/* Digital Interface Control */
	0,		//digital_interface_tune_skip_mode *** adi,digital-interface-tune-skip-mode
	0,		//digital_interface_tune_fir_disable *** adi,digital-interface-tune-fir-disable
	1,		//pp_tx_swap_enable *** adi,pp-tx-swap-enable
	1,		//pp_rx_swap_enable *** adi,pp-rx-swap-enable
	0,		//tx_channel_swap_enable *** adi,tx-channel-swap-enable
	0,		//rx_channel_swap_enable *** adi,rx-channel-swap-enable
	1,		//rx_frame_pulse_mode_enable *** adi,rx-frame-pulse-mode-enable
	0,		//two_t_two_r_timing_enable *** adi,2t2r-timing-enable
	0,		//invert_data_bus_enable *** adi,invert-data-bus-enable
	0,		//invert_data_clk_enable *** adi,invert-data-clk-enable
	0,		//fdd_alt_word_order_enable *** adi,fdd-alt-word-order-enable
	0,		//invert_rx_frame_enable *** adi,invert-rx-frame-enable
	0,		//fdd_rx_rate_2tx_enable *** adi,fdd-rx-rate-2tx-enable
	0,		//swap_ports_enable *** adi,swap-ports-enable
	0,		//single_data_rate_enable *** adi,single-data-rate-enable
	1,		//lvds_mode_enable *** adi,lvds-mode-enable
	0,		//half_duplex_mode_enable *** adi,half-duplex-mode-enable
	0,		//single_port_mode_enable *** adi,single-port-mode-enable
	0,		//full_port_enable *** adi,full-port-enable
	0,		//full_duplex_swap_bits_enable *** adi,full-duplex-swap-bits-enable
	0,		//delay_rx_data *** adi,delay-rx-data
	0,		//rx_data_clock_delay *** adi,rx-data-clock-delay
	4,		//rx_data_delay *** adi,rx-data-delay
	7,		//tx_fb_clock_delay *** adi,tx-fb-clock-delay
	0,		//tx_data_delay *** adi,tx-data-delay
	150,	//lvds_bias_mV *** adi,lvds-bias-mV
	1,		//lvds_rx_onchip_termination_enable *** adi,lvds-rx-onchip-termination-enable
	0,		//rx1rx2_phase_inversion_en *** adi,rx1-rx2-phase-inversion-enable
	0xFF,	//lvds_invert1_control *** adi,lvds-invert1-control
	0x0F,	//lvds_invert2_control *** adi,lvds-invert2-control
	/* GPO Control */
	0,		//gpo0_inactive_state_high_enable *** adi,gpo0-inactive-state-high-enable
	0,		//gpo1_inactive_state_high_enable *** adi,gpo1-inactive-state-high-enable
	0,		//gpo2_inactive_state_high_enable *** adi,gpo2-inactive-state-high-enable
	0,		//gpo3_inactive_state_high_enable *** adi,gpo3-inactive-state-high-enable
	0,		//gpo0_slave_rx_enable *** adi,gpo0-slave-rx-enable
	0,		//gpo0_slave_tx_enable *** adi,gpo0-slave-tx-enable
	0,		//gpo1_slave_rx_enable *** adi,gpo1-slave-rx-enable
	0,		//gpo1_slave_tx_enable *** adi,gpo1-slave-tx-enable
	0,		//gpo2_slave_rx_enable *** adi,gpo2-slave-rx-enable
	0,		//gpo2_slave_tx_enable *** adi,gpo2-slave-tx-enable
	0,		//gpo3_slave_rx_enable *** adi,gpo3-slave-rx-enable
	0,		//gpo3_slave_tx_enable *** adi,gpo3-slave-tx-enable
	0,		//gpo0_rx_delay_us *** adi,gpo0-rx-delay-us
	0,		//gpo0_tx_delay_us *** adi,gpo0-tx-delay-us
	0,		//gpo1_rx_delay_us *** adi,gpo1-rx-delay-us
	0,		//gpo1_tx_delay_us *** adi,gpo1-tx-delay-us
	0,		//gpo2_rx_delay_us *** adi,gpo2-rx-delay-us
	0,		//gpo2_tx_delay_us *** adi,gpo2-tx-delay-us
	0,		//gpo3_rx_delay_us *** adi,gpo3-rx-delay-us
	0,		//gpo3_tx_delay_us *** adi,gpo3-tx-delay-us
	/* Tx Monitor Control */
	37000,	//low_high_gain_threshold_mdB *** adi,txmon-low-high-thresh
	0,		//low_gain_dB *** adi,txmon-low-gain
	24,		//high_gain_dB *** adi,txmon-high-gain
	0,		//tx_mon_track_en *** adi,txmon-dc-tracking-enable
	0,		//one_shot_mode_en *** adi,txmon-one-shot-mode-enable
	511,	//tx_mon_delay *** adi,txmon-delay
	8192,	//tx_mon_duration *** adi,txmon-duration
	2,		//tx1_mon_front_end_gain *** adi,txmon-1-front-end-gain
	2,		//tx2_mon_front_end_gain *** adi,txmon-2-front-end-gain
	48,		//tx1_mon_lo_cm *** adi,txmon-1-lo-cm
	48, 		//tx2_mon_lo_cm *** adi,txmon-2-lo-cm
	/* GPIO definitions */
	0
	};
AD9361_RXFIRConfig rx_fir_config_4_128 = { 3, // rx;
		-6, // rx_gain;
		4, // rx_dec;
		{ -15, -27, -23, -6, 17, 33, 31, 9, -23, -47, -45, -13, 34, 69, 67, 21,
				-49, -102, -99, -32, 69, 146, 143, 48, -96, -204, -200, -69,
				129, 278, 275, 97, -170, -372, -371, -135, 222, 494, 497, 187,
				-288, -654, -665, -258, 376, 875, 902, 363, -500, -1201, -1265,
				-530, 699, 1748, 1906, 845, -1089, -2922, -3424, -1697, 2326,
				7714, 12821, 15921, 15921, 12821, 7714, 2326, -1697, -3424,
				-2922, -1089, 845, 1906, 1748, 699, -530, -1265, -1201, -500,
				363, 902, 875, 376, -258, -665, -654, -288, 187, 497, 494, 222,
				-135, -371, -372, -170, 97, 275, 278, 129, -69, -200, -204, -96,
				48, 143, 146, 69, -32, -99, -102, -49, 21, 67, 69, 34, -13, -45,
				-47, -23, 9, 31, 33, 17, -6, -23, -27, -15 }, // rx_coef[128]
		128, // rx_coef_size
		{ 0, 0, 0, 0, 0, 0 }, //rx_path_clks[6]
		0 // rx_bandwidth
		};

AD9361_TXFIRConfig tx_fir_config_4_128 = { 3, // tx;
		0, // tx_gain;
		4, // tx_inc;
		{ -15, -27, -23, -6, 17, 33, 31, 9, -23, -47, -45, -13, 34, 69, 67, 21,
				-49, -102, -99, -32, 69, 146, 143, 48, -96, -204, -200, -69,
				129, 278, 275, 97, -170, -372, -371, -135, 222, 494, 497, 187,
				-288, -654, -665, -258, 376, 875, 902, 363, -500, -1201, -1265,
				-530, 699, 1748, 1906, 845, -1089, -2922, -3424, -1697, 2326,
				7714, 12821, 15921, 15921, 12821, 7714, 2326, -1697, -3424,
				-2922, -1089, 845, 1906, 1748, 699, -530, -1265, -1201, -500,
				363, 902, 875, 376, -258, -665, -654, -288, 187, 497, 494, 222,
				-135, -371, -372, -170, 97, 275, 278, 129, -69, -200, -204, -96,
				48, 143, 146, 69, -32, -99, -102, -49, 21, 67, 69, 34, -13, -45,
				-47, -23, 9, 31, 33, 17, -6, -23, -27, -15 }, // tx_coef[128]
		128, // tx_coef_size
		{ 0, 0, 0, 0, 0, 0 }, // tx_path_clks[6]
		0 // tx_bandwidth
		};
AD9361_RXFIRConfig rx_fir_config_2_128 = { 3, // rx;
		-6, // rx_gain;
		2, // rx_dec;
		{ -0, 0, 1, -0, -2, 0, 3, -0, -5, 0, 8, -0, -11, 0, 17, -0, -24, 0, 33,
				-0, -45, 0, 61, -0, -80, 0, 104, -0, -134, 0, 169, -0, -213, 0,
				264, -0, -327, 0, 401, -0, -489, 0, 595, -0, -724, 0, 880, -0,
				-1075, 0, 1323, -0, -1652, 0, 2114, -0, -2819, 0, 4056, -0,
				-6883, 0, 20837, 32767, 20837, 0, -6883, -0, 4056, 0, -2819, -0,
				2114, 0, -1652, -0, 1323, 0, -1075, -0, 880, 0, -724, -0, 595,
				0, -489, -0, 401, 0, -327, -0, 264, 0, -213, -0, 169, 0, -134,
				-0, 104, 0, -80, -0, 61, 0, -45, -0, 33, 0, -24, -0, 17, 0, -11,
				-0, 8, 0, -5, -0, 3, 0, -2, -0, 1, 0, -0, 0 }, // rx_coef[128]
		128, // rx_coef_size
		{ 0, 0, 0, 0, 0, 0 }, //rx_path_clks[6]
		0 // rx_bandwidth
		};

AD9361_TXFIRConfig tx_fir_config_2_128 = { 3, // tx;
		0, // tx_gain;
		2, // tx_inc;
		{ -0, 0, 1, -0, -2, 0, 3, -0, -5, 0, 8, -0, -11, 0, 17, -0, -24, 0, 33,
				-0, -45, 0, 61, -0, -80, 0, 104, -0, -134, 0, 169, -0, -213, 0,
				264, -0, -327, 0, 401, -0, -489, 0, 595, -0, -724, 0, 880, -0,
				-1075, 0, 1323, -0, -1652, 0, 2114, -0, -2819, 0, 4056, -0,
				-6883, 0, 20837, 32767, 20837, 0, -6883, -0, 4056, 0, -2819, -0,
				2114, 0, -1652, -0, 1323, 0, -1075, -0, 880, 0, -724, -0, 595,
				0, -489, -0, 401, 0, -327, -0, 264, 0, -213, -0, 169, 0, -134,
				-0, 104, 0, -80, -0, 61, 0, -45, -0, 33, 0, -24, -0, 17, 0, -11,
				-0, 8, 0, -5, -0, 3, 0, -2, -0, 1, 0, -0, 0 }, // tx_coef[128]
		128, // tx_coef_size
		{ 0, 0, 0, 0, 0, 0 }, // tx_path_clks[6]
		0 // tx_bandwidth
		};
AD9361_RXFIRConfig rx_fir_config_2_96 = { 3, // rx;
		-6, // rx_gain;
		2, // rx_dec;
		{ -4, 0, 8, -0, -14, 0, 23, -0, -36, 0, 52, -0, -75, 0, 104, -0, -140,
				0, 186, -0, -243, 0, 314, -0, -400, 0, 505, -0, -634, 0, 793,
				-0, -993, 0, 1247, -0, -1585, 0, 2056, -0, -2773, 0, 4022, -0,
				-6862, 0, 20830, 32767, 20830, 0, -6862, -0, 4022, 0, -2773, -0,
				2056, 0, -1585, -0, 1247, 0, -993, -0, 793, 0, -634, -0, 505, 0,
				-400, -0, 314, 0, -243, -0, 186, 0, -140, -0, 104, 0, -75, -0,
				52, 0, -36, -0, 23, 0, -14, -0, 8, 0, -4, 0 }, // rx_coef[128]
		96, // rx_coef_size
		{ 0, 0, 0, 0, 0, 0 }, //rx_path_clks[6]
		0 // rx_bandwidth
		};

AD9361_TXFIRConfig tx_fir_config_2_96 = { 3, // tx;
		0, // tx_gain;
		2, // tx_inc;
		{ -4, 0, 8, -0, -14, 0, 23, -0, -36, 0, 52, -0, -75, 0, 104, -0, -140,
				0, 186, -0, -243, 0, 314, -0, -400, 0, 505, -0, -634, 0, 793,
				-0, -993, 0, 1247, -0, -1585, 0, 2056, -0, -2773, 0, 4022, -0,
				-6862, 0, 20830, 32767, 20830, 0, -6862, -0, 4022, 0, -2773, -0,
				2056, 0, -1585, -0, 1247, 0, -993, -0, 793, 0, -634, -0, 505, 0,
				-400, -0, 314, 0, -243, -0, 186, 0, -140, -0, 104, 0, -75, -0,
				52, 0, -36, -0, 23, 0, -14, -0, 8, 0, -4, 0 }, // tx_coef[128]
		96, // tx_coef_size
		{ 0, 0, 0, 0, 0, 0 }, // tx_path_clks[6]
		0 // tx_bandwidth
		};
AD9361_RXFIRConfig rx_fir_config_2_64 = { 3, // rx;
		-6, // rx_gain;
		2, // rx_dec;
		{ -58, 0, 83, -0, -127, 0, 185, -0, -262, 0, 361, -0, -488, 0, 648, -0,
				-853, 0, 1117, -0, -1466, 0, 1954, -0, -2689, 0, 3960, -0,
				-6825, 0, 20818, 32767, 20818, 0, -6825, -0, 3960, 0, -2689, -0,
				1954, 0, -1466, -0, 1117, 0, -853, -0, 648, 0, -488, -0, 361, 0,
				-262, -0, 185, 0, -127, -0, 83, 0, -58, 0 }, // rx_coef[128]
		64, // rx_coef_size
		{ 0, 0, 0, 0, 0, 0 }, //rx_path_clks[6]
		0 // rx_bandwidth
		};

AD9361_TXFIRConfig tx_fir_config_2_64 = { 3, // tx;
		0, // tx_gain;
		2, // tx_inc;
		{ -58, 0, 83, -0, -127, 0, 185, -0, -262, 0, 361, -0, -488, 0, 648, -0,
				-853, 0, 1117, -0, -1466, 0, 1954, -0, -2689, 0, 3960, -0,
				-6825, 0, 20818, 32767, 20818, 0, -6825, -0, 3960, 0, -2689, -0,
				1954, 0, -1466, -0, 1117, 0, -853, -0, 648, 0, -488, -0, 361, 0,
				-262, -0, 185, 0, -127, -0, 83, 0, -58, 0 }, // tx_coef[128]
		64, // tx_coef_size
		{ 0, 0, 0, 0, 0, 0 }, // tx_path_clks[6]
		0 // tx_bandwidth
		};
#endif /* SRC_RADIO_SET_H_ */
