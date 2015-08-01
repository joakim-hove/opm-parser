import ctypes
from ert.cwrap.clib import lib_name

lib_path = None
try:
    import __opm_lib_path
    lib_path = __opm_lib_path.lib_path
except ImportError:
    pass


lib_file = lib_name( "libcopmparser" , path = lib_path )
OPM_LIB = ctypes.CDLL( lib_file , ctypes.RTLD_GLOBAL )
