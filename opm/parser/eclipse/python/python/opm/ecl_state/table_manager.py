import os.path

from ert.cwrap import BaseCClass, CWrapper
from opm import OPM_LIB


class TableManager(BaseCClass):
    def __init__(self , deck):
        c_ptr = TableManager.cNamespace().alloc(deck)
        super(TableManager, self).__init__(c_ptr)


    def free(self):
        TableManager.cNamespace().free( self )

    
        
CWrapper.registerObjectType("table_manager", TableManager)

cwrapper = CWrapper(OPM_LIB)
TableManager.cNamespace().alloc = cwrapper.prototype("c_void_p table_manager_alloc(deck)")
TableManager.cNamespace().free  = cwrapper.prototype("void table_manager_free( table_manager )") 
        
