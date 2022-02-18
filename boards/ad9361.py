from ctypes import *
from pynq import Overlay

SHORT128 = c_short * 128
UINT6 = c_uint * 6
ProfileValues = c_ubyte * 16

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

class AD9361():
    def __init__(self):
        self.ol = Overlay('./overlay/axi_quad_spi.bit')
        self.lib = cdll.LoadLibrary("./lib/libad9361_drv.so")
        self.spifd = self.lib.open_spi()
        assert self.spifd > 0, 'spi open error'
        assert self.lib.init_ad9361(self.spifd) == 0, 'ad9361 initialization failed'
        print('ad9361 successfully initialized')
        ret = self.lib.config_ad9361()
        assert ret > 0, 'ad9361 config failed'
        print('product ID: 0x%X' % ret)
                
    def set_en_state_machine_mode(self, mode):
        self.lib._ad9361_set_en_state_machine_mode.argtypes = [c_uint]
        return self.lib._ad9361_set_en_state_machine_mode(mode)
    
    def get_en_state_machine_mode(self):
        self.lib._ad9361_get_en_state_machine_mode.argtypes = [POINTER(c_uint)]
        mode = c_uint(0)
        self.lib._ad9361_get_en_state_machine_mode(mode)
        return mode.value
    
    def set_rx_rf_gain(self, ch, gain_db):
        self.lib._ad9361_set_rx_rf_gain.argtypes = [c_ubyte, c_int]
        return self.lib._ad9361_set_rx_rf_gain(ch, gain_db)
    
    def get_rx_rf_gain(self, ch):
        self.lib._ad9361_get_rx_rf_gain.argtypes = [c_ubyte, POINTER(c_int)]
        gain_db = c_int(0)
        self.lib._ad9361_get_rx_rf_gain(ch, gain_db)
        return gain_db.value

    def set_rx_rf_bandwidth(self, bandwidth_hz):
        self.lib._ad9361_set_rx_rf_bandwidth.argtypes = [c_uint]
        return self.lib._ad9361_set_rx_rf_bandwidth(bandwidth_hz)
    
    def get_rx_rf_bandwidth(self):
        self.lib._ad9361_get_rx_rf_bandwidth.argtypes = [POINTER(c_uint)]
        bandwidth_hz = c_uint(0)
        self.lib._ad9361_get_rx_rf_bandwidth(bandwidth_hz)
        return bandwidth_hz.value
    
    def set_rx_sampling_freq(self, sampling_freq_hz):
        self.lib._ad9361_set_rx_sampling_freq.argtypes = [c_uint]
        return self.lib._ad9361_set_rx_sampling_freq(sampling_freq_hz)
    
    def get_rx_sampling_freq(self):
        self.lib._ad9361_get_rx_sampling_freq.argtypes = [POINTER(c_uint)]
        sampling_freq_hz = c_uint(0)
        self.lib._ad9361_get_rx_sampling_freq(sampling_freq_hz)
        return sampling_freq_hz.value
    
    def set_rx_lo_freq(self, lo_freq_hz):
        self.lib._ad9361_set_rx_lo_freq.argtypes = [c_ulonglong]
        return self.lib._ad9361_set_rx_lo_freq(lo_freq_hz)
    
    def get_rx_lo_freq(self):
        self.lib._ad9361_get_rx_lo_freq.argtypes = [POINTER(c_ulonglong)]
        lo_freq_hz = c_ulonglong(0)
        self.lib._ad9361_get_rx_lo_freq(lo_freq_hz)
        return lo_freq_hz.value
    
    def set_rx_lo_int_ext(self, int_ext):
        self.lib._ad9361_get_en_state_machine_mode.argtypes = [c_ubyte]
        return self.lib._ad9361_set_rx_lo_int_ext(int_ext)
    
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
    