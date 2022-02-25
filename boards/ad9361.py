from ctypes import *
from pynq import Overlay

SHORT128 = c_short * 128
UINT6 = c_uint * 6
ProfileValues = c_ubyte * 16
UINT7 = c_uint * 7

class RFRssi(Structure):
    _fields_ = [
        ("ant", c_uint),
        ("symbol", c_uint),
        ("preamble", c_uint),
        ("multiplier", c_int),
        ("duration", c_ubyte)
    ]
    def print(self):
        print("rssi.ant:", self.ant)
        print("rssi.symbol:", self.symbol)
        print("rssi.preamble:", self.preamble)
        print("rssi.multiplier:", self.multiplier)
        print("rssi.duration:", self.duration)
        
class RXFIRConfig(Structure):
    _fields_ = [
        ("rx", c_uint),
        ("rx_gain", c_int),
        ("rx_dec", c_uint),
        ("rx_coef", SHORT128),
        ("rx_coef_size", c_ubyte),
        ("rx_path_clks", UINT6),
        ("rx_bandwidth", c_uint)
    ]
    def print(self):
        print("fir_config.rx:", self.rx)
        print("fir_config.rx_gain:", self.rx_gain)
        print("fir_config.rx_dec:", self.rx_dec)
        print("fir_config.rx_coef:", type(self.rx_coef))
        print("fir_config.rx_coef_size:", self.rx_coef_size)
        print("fir_config.rx_path_clks:", type(self.rx_path_clks))
        print("fir_config.rx_bandwidth:", self.rx_bandwidth)
        
class TXFIRConfig(Structure):
    _fields_ = [
        ("tx", c_uint),
        ("tx_gain", c_int),
        ("tx_dec", c_uint),
        ("tx_coef", SHORT128),
        ("tx_coef_size", c_ubyte),
        ("tx_path_clks", UINT6),
        ("tx_bandwidth", c_uint)
    ]
    def print(self):
        print("fir_config.tx:", self.tx)
        print("fir_config.tx_gain:", self.tx_gain)
        print("fir_config.tx_dec:", self.tx_dec)
        print("fir_config.tx_coef:", type(self.tx_coef))
        print("fir_config.tx_coef_size:", self.tx_coef_size)
        print("fir_config.tx_path_clks:", type(self.tx_path_clks))
        print("fir_config.tx_bandwidth:", self.tx_bandwidth)

class AD9361():
    def __init__(self):
        self.lib = cdll.LoadLibrary("./lib/libad9361_drv.so")
        self.spifd = self.lib.open_spi()
        assert self.spifd > 0, 'spi open error'
        assert self.lib.init_ad9361(self.spifd) == 0, 'ad9361 initialization failed'
        print('ad9361 successfully initialized')
        ret = self.lib.config_ad9361()
        assert ret > 0, 'ad9361 config failed'
        print('product ID: 0x%X' % ret)
                
    def set_en_state_machine_mode(self, mode):
        func = self.lib._ad9361_set_en_state_machine_mode
        func.argtypes = [c_uint]
        return func(mode)
    
    def get_en_state_machine_mode(self):
        func = self.lib._ad9361_get_en_state_machine_mode
        func.argtypes = [POINTER(c_uint)]
        mode = c_uint(0)
        func(mode)
        return mode.value
    
    def set_rx_rf_gain(self, ch, gain_db):
        func = self.lib._ad9361_set_rx_rf_gain
        func.argtypes = [c_ubyte, c_int]
        return func(ch, gain_db)
    
    def get_rx_rf_gain(self, ch):
        func = self.lib._ad9361_get_rx_rf_gain
        func.argtypes = [c_ubyte, POINTER(c_int)]
        gain_db = c_int(0)
        func(ch, gain_db)
        return gain_db.value

    def set_rx_rf_bandwidth(self, bandwidth_hz):
        func = self.lib._ad9361_set_rx_rf_bandwidth
        func.argtypes = [c_uint]
        return func(bandwidth_hz)
    
    def get_rx_rf_bandwidth(self):
        func = self.lib._ad9361_get_rx_rf_bandwidth
        func.argtypes = [POINTER(c_uint)]
        bandwidth_hz = c_uint(0)
        ret = func(bandwidth_hz)
        return bandwidth_hz.value
    
    def set_rx_sampling_freq(self, sampling_freq_hz):
        func = self.lib._ad9361_set_rx_sampling_freq
        func.argtypes = [c_uint]
        return func(sampling_freq_hz)
    
    def get_rx_sampling_freq(self):
        func = self.lib._ad9361_get_rx_sampling_freq
        func.argtypes = [POINTER(c_uint)]
        sampling_freq_hz = c_uint(0)
        func(sampling_freq_hz)
        return sampling_freq_hz.value
    
    def set_rx_lo_freq(self, lo_freq_hz):
        func = self.lib._ad9361_set_rx_lo_freq
        func.argtypes = [c_ulonglong]
        return func(lo_freq_hz)
    
    def get_rx_lo_freq(self):
        func = self.lib._ad9361_get_rx_lo_freq
        func.argtypes = [POINTER(c_ulonglong)]
        lo_freq_hz = c_ulonglong(0)
        func(lo_freq_hz)
        return lo_freq_hz.value
    
    def set_rx_lo_int_ext(self, int_ext):
        func = self.lib._ad9361_set_rx_lo_int_ext
        func.argtypes = [c_ubyte]
        return func(int_ext)
    
    def get_rx_rssi(self, ch):
        func = self.lib._ad9361_get_rx_rssi
        func.argtypes = [c_ubyte, POINTER(RFRssi)]
        rssi = RFRssi()
        ret = func(ch, byref(rssi))
        return rssi
    
    def set_rx_gain_control_mode(self, ch, gc_mode):
        func = self.lib._ad9361_set_rx_gain_control_mode
        func.argtypes = [c_ubyte, c_ubyte]
        return func(ch, gc_mode)
    
    def get_rx_gain_control_mode(self, ch):
        func = self.lib._ad9361_get_rx_gain_control_mode
        func.argtypes = [c_ubyte, POINTER(c_ubyte)]
        mode = c_ubyte(0)
        ret = func(ch, mode)
        return mode.value
    
    def set_rx_fir_config(self, fir_config):
        func = self.lib._ad9361_set_rx_fir_config
        func.argtypes = [RXFIRConfig]
        return func(fir_config)
    
    def get_rx_fir_config(self, ch):
        func = self.lib._ad9361_get_rx_fir_config
        func.argtypes = [c_ubyte, POINTER(RXFIRConfig)]
        fir_config = RXFIRConfig()
        ret = func(ch, byref(fir_config))
        return fir_config
        
    def set_rx_fir_en_dis(self, en_dis):
        func = self.lib._ad9361_set_rx_fir_en_dis
        func.argtypes = [c_ubyte]
        return func(en_dis)
    
    def get_rx_fir_en_dis(self):
        func = self.lib._ad9361_get_rx_fir_en_dis
        func.argtypes = [POINTER(c_ubyte)]
        en_dis = c_ubyte(0)
        ret = func(en_dis)
        return en_dis.value

    def set_rx_rfdc_track_en_dis(self, en_dis):
        func = self.lib._ad9361_set_rx_rfdc_track_en_dis
        func.argtypes = [c_ubyte]
        return func(en_dis)
    
    def get_rx_rfdc_track_en_dis(self):
        func = self.lib._ad9361_get_rx_rfdc_track_en_dis
        func.argtypes = [POINTER(c_ubyte)]
        en_dis = c_ubyte(0)
        ret = func(en_dis)
        return en_dis.value
    
    def set_rx_bbdc_track_en_dis(self, en_dis):
        func = self.lib._ad9361_set_rx_bbdc_track_en_dis
        func.argtypes = [c_ubyte]
        return func(en_dis)
    
    def get_rx_bbdc_track_en_dis(self):
        func = self.lib._ad9361_get_rx_bbdc_track_en_dis
        func.argtypes = [POINTER(c_ubyte)]
        en_dis = c_ubyte(0)
        ret = func(en_dis)
        return en_dis.value
    
    def set_rx_quad_track_en_dis(self, en_dis):
        func = self.lib._ad9361_set_rx_quad_track_en_dis
        func.argtypes = [c_ubyte]
        return func(en_dis)
    
    def get_rx_quad_track_en_dis(self):
        func = self.lib._ad9361_get_rx_quad_track_en_dis
        func.argtypes = [POINTER(c_ubyte)]
        en_dis = c_ubyte(0)
        ret = func(en_dis)
        return en_dis.value
    
    def set_rx_rf_port_input(self, mode):
        func = self.lib._ad9361_set_rx_rf_port_input
        func.argtypes = [c_uint]
        return func(mode)
    
    def get_rx_rf_port_input(self):
        func = self.lib._ad9361_get_rx_rf_port_input
        func.argtypes = [POINTER(c_uint)]
        mode = c_uint(0)
        ret = func(mode)
        return mode.value
    
    def rx_fastlock_store(self, profile):
        func = self.lib._ad9361_rx_fastlock_store
        func.argtypes = [c_uint]
        return func(profile)

    def rx_fastlock_recall(self, profile):
        func = self.lib._ad9361_rx_fastlock_recall
        func.argtypes = [c_uint]
        return func(profile)
    
    def rx_fastlock_load(self, profile, values):
        func = self.lib._ad9361_rx_fastlock_load
        func.argtypes = [c_uint, POINTER(ProfileValues)]
        c_values = ProfileValues()
        for i in range(16):
            c_values[i] = values[i]
        return func(profile, byref(c_values))
        
    def rx_fastlock_save(self, profile):
        func = self.lib._ad9361_rx_fastlock_save
        func.argtypes = [c_uint, POINTER(ProfileValues)]
        c_values = ProfileValues()
        ret = func(profile, byref(c_values))
        values = list(c_values)
        return values
    
    def set_rx_lo_powerdown(self, pd):
        func = self.lib._ad9361_set_rx_lo_powerdown
        func.argtypes = [c_ubyte]
        return func(pd)
    
    def get_rx_lo_powerdown(self):
        func = self.lib._ad9361_get_rx_lo_powerdown
        func.argtypes = [POINTER(c_ubyte)]
        pd = c_ubyte(0)
        ret = func(pd)
        return pd.value 

    def set_tx_attenuation(self, ch, attenuation_mdb):
        func = self.lib._ad9361_set_tx_attenuation
        func.argtypes = [c_ubyte, c_uint]
        return func(ch, attenuation_mdb)
    
    def get_tx_attenuation(self, ch):
        func = self.lib._ad9361_get_tx_attenuation
        func.argtypes = [c_ubyte, POINTER(c_uint)]
        attenuation_mdb = c_uint(0)
        ret = func(ch, attenuation_mdb)
        return attenuation_mdb.value
   
    def set_tx_rf_bandwidth(self, bandwidth_hz):
        func = self.lib._ad9361_set_tx_rf_bandwidth
        func.argtypes = [c_uint]
        return func(bandwidth_hz)
    
    def get_tx_rf_bandwidth(self):
        func = self.lib._ad9361_get_tx_rf_bandwidth
        func.argtypes = [POINTER(c_uint)]
        bandwidth_hz = c_uint(0)
        ret = func(bandwidth_hz)
        return bandwidth_hz.value
    
    def set_tx_sampling_freq(self, sampling_freq_hz):
        func = self.lib._ad9361_set_tx_sampling_freq
        func.argtypes = [c_uint]
        return func(sampling_freq_hz)
    
    def get_tx_sampling_freq(self):
        func = self.lib._ad9361_get_tx_sampling_freq
        func.argtypes = [POINTER(c_uint)]
        sampling_freq_hz = c_uint(0)
        func(sampling_freq_hz)
        return sampling_freq_hz.value
    
    def set_tx_lo_freq(self, lo_freq_hz):
        func = self.lib._ad9361_set_tx_lo_freq
        func.argtypes = [c_ulonglong]
        return func(lo_freq_hz)
    
    def get_tx_lo_freq(self):
        func = self.lib._ad9361_get_tx_lo_freq
        func.argtypes = [POINTER(c_ulonglong)]
        lo_freq_hz = c_ulonglong(0)
        func(lo_freq_hz)
        return lo_freq_hz.value
    
    def set_tx_lo_int_ext(self, int_ext):
        func = self.lib._ad9361_set_tx_lo_int_ext
        func.argtypes = [c_ubyte]
        return func(int_ext)
    
    def set_tx_fir_config(self, fir_config):
        func = self.lib._ad9361_set_tx_fir_config
        func.argtypes = [TXFIRConfig]
        return func(fir_config)
    
    def get_tx_fir_config(self, ch):
        func = self.lib._ad9361_get_tx_fir_config
        func.argtypes = [c_ubyte, POINTER(TXFIRConfig)]
        fir_config = TXFIRConfig()
        ret = func(ch, byref(fir_config))
        return fir_config
        
    def set_tx_fir_en_dis(self, en_dis):
        func = self.lib._ad9361_set_tx_fir_en_dis
        func.argtypes = [c_ubyte]
        return func(en_dis)
    
    def get_tx_fir_en_dis(self):
        func = self.lib._ad9361_get_tx_fir_en_dis
        func.argtypes = [POINTER(c_ubyte)]
        en_dis = c_ubyte(0)
        ret = func(en_dis)
        return en_dis.value
    
    def get_tx_rssi(self, ch):
        func = self.lib._ad9361_get_tx_rssi
        func.argtypes = [c_ubyte, POINTER(c_uint)]
        rssi_db_x_1000 = c_uint(0)
        ret = func(ch, rssi_db_x_1000)
        return rssi_db_x_1000.value
        
    def set_tx_rf_port_output(self, mode):
        func = self.lib._ad9361_set_tx_rf_port_output
        func.argtypes = [c_uint]
        return func(mode)
    
    def get_tx_rf_port_output(self):
        func = self.lib._ad9361_get_tx_rf_port_output
        func.argtypes = [POINTER(c_uint)]
        mode = c_uint(0)
        ret = func(mode)
        return mode.value
    
    def set_tx_auto_cal_en_dis(self, en_dis):
        func = self.lib._ad9361_set_tx_auto_cal_en_dis
        func.argtypes = [c_ubyte]
        return func(en_dis)
    
    def get_tx_auto_cal_en_dis(self):
        func = self.lib._ad9361_get_tx_auto_cal_en_dis
        func.argtypes = [POINTER(c_ubyte)]
        en_dis = c_ubyte(0)
        ret = func(en_dis)
        return en_dis.value
    
    def tx_fastlock_store(self, profile):
        func = self.lib._ad9361_tx_fastlock_store
        func.argtypes = [c_uint]
        return func(profile)

    def tx_fastlock_recall(self, profile):
        func = self.lib._ad9361_tx_fastlock_recall
        func.argtypes = [c_uint]
        return func(profile)
    
    def tx_fastlock_load(self, profile, values):
        func = self.lib._ad9361_tx_fastlock_load
        func.argtypes = [c_uint, POINTER(ProfileValues)]
        c_values = ProfileValues()
        for i in range(16):
            c_values[i] = values[i]
        return func(profile, byref(c_values))
        
    def tx_fastlock_save(self, profile):
        func = self.lib._ad9361_tx_fastlock_save
        func.argtypes = [c_uint, POINTER(ProfileValues)]
        c_values = ProfileValues()
        ret = func(profile, byref(c_values))
        values = list(c_values)
        return values
    
    def set_tx_lo_powerdown(self, pd):
        func = self.lib._ad9361_set_tx_lo_powerdown
        func.argtypes = [c_ubyte]
        return func(pd)
    
    def get_tx_lo_powerdown(self):
        func = self.lib._ad9361_get_tx_lo_powerdown
        func.argtypes = [POINTER(c_ubyte)]
        pd = c_ubyte(0)
        ret = func(pd)
        return pd.value 
    
    #################################################
    def set_trx_path_clks(self, rx_path_clks, tx_path_clks):
        func = self.lib._ad9361_set_trx_path_clks
        func.argtypes = [POINTER(UINT7), POINTER(UINT7)]
        c_rx_path_clks = UINT7()
        c_tx_path_clks = UINT7()
        for i in range(7):
            c_rx_path_clks[i] = rx_path_clks[i]
            c_tx_path_clks[i] = tx_path_clks[i]
        return func(byref(c_rx_path_clks), byref(c_tx_path_clks))
    
    def get_trx_path_clks(self):
        func = self.lib._ad9361_set_trx_path_clks
        func.argtypes = [POINTER(UINT7), POINTER(UINT7)]
        c_rx_path_clks = UINT7()
        c_tx_path_clks = UINT7()
        ret = func(byref(c_rx_path_clks), byref(c_tx_path_clks))
        rx_path_clks = list(c_rx_path_clks)
        tx_path_clks = list(c_tx_path_clks)
        return rx_path_clks, tx_path_clks
    
    def set_trx_lo_powerdown(self, pd_rx, pd_tx):
        func = self.lib._ad9361_set_trx_lo_powerdown
        func.argtypes = [c_ubyte, c_ubyte]
        return func(pd_rx, pd_tx)
    
    def set_no_ch_mode(self, no_ch_mode):
        func = self.lib._ad9361_set_no_ch_mode
        func.argtypes = [c_ubyte]
        return func(no_ch_mode)
    
    def set_trx_fir_en_dis(self, en_dis):
        func = self.lib._ad9361_set_trx_fir_en_dis
        func.argtypes = [c_ubyte]
        return func(en_dis)
    
    def set_trx_rate_gov(self, rate_gov):
        func = self.lib._ad9361_set_trx_rate_gov
        func.argtypes = [c_uint]
        return func(rate_gov)
    
    def get_trx_rate_gov(self):
        func = self.lib._ad9361_get_trx_rate_gov
        func.argtypes = [POINTER(c_uint)]
        rate_gov = c_uint(0)
        ret = func(rate_gov)
        return rate_gov.value
    
    def do_calib(self, cal, arg):
        func = self.lib._ad9361_do_calib
        func.argtypes = [c_uint, c_int]
        return func(cal, arg)
    
    def trx_load_enable_fir(self, rx_fir_cfg, tx_fir_cfg):
        func = self.lib._ad9361_trx_load_enable_fir
        func.argtypes = [RXFIRConfig, TXFIRConfig]
        return func(rx_fir_cfg, tx_fir_cfg)
    
    def do_dcxo_tune_coarse(self, coarse):
        func = self.lib._ad9361_do_dcxo_tune_coarse
        func.argtypes = [c_uint]
        return func(coarse)
    
    def do_dcxo_tune_fine(self, fine):
        func = self.lib._ad9361_do_dcxo_tune_fine
        func.argtypes = [c_uint]
        return func(fine)
    
    def get_temp(self):
        return self.lib._ad9361_get_temp()