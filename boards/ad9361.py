from ctypes import *
from pynq import Overlay

class StructRfrssi(Structure):
    _fields_ = [
        ("ant", c_uint),
        ("symbol", c_uint),
        ("preamble", c_uint),
        ("multiplier", c_int),
        ("duration", c_ubyte)
    ]

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
        func.argtypes = [c_ubyte, POINTER(StructRfrssi)]
        rssi = StructRfrssi()
        ret = func(ch, byref(rssi))
        return rssi
        
        
        
        
        
        
        
        