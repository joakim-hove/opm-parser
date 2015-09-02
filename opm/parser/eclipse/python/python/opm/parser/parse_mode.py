from ert.cwrap import BaseCClass, CWrapper
from opm import OPM_LIB

class ParseMode(BaseCClass):
    def __init__(self):
        c_ptr = ParseMode.cNamespace().alloc()
        super(ParseMode, self).__init__(c_ptr)

        
    def free(self):
        ParseMode.cNamespace().free( self )


    def update(self , var , action):
        ParseMode.cNamespace().update( self , var , action )

CWrapper.registerObjectType("parse_mode", ParseMode)

cwrapper = CWrapper(OPM_LIB)
ParseMode.cNamespace().alloc  = cwrapper.prototype("c_void_p parse_mode_alloc()")
ParseMode.cNamespace().free   = cwrapper.prototype("void parse_mode_free( parse_mode )")
ParseMode.cNamespace().update = cwrapper.prototype("void parse_mode_update( parse_mode , char* , error_action_enum)")

