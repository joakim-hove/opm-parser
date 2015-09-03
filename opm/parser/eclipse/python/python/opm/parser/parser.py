import os.path

from ert.cwrap import BaseCClass, CWrapper
from opm import OPM_LIB
from opm.deck import Deck
from opm.parser import ParseMode


class Parser(BaseCClass):
    def __init__(self):
        c_ptr = Parser.cNamespace().alloc()
        super(Parser, self).__init__(c_ptr)

        
    def __contains__(self , kw):
        return Parser.cNamespace().has_keyword(self , kw)
        
        
    def free(self):
        Parser.cNamespace().free( self )

        
    def parseFile(self , filename , parse_mode = None):
        if os.path.isfile( filename ):
            if parse_mode is None:
                parse_mode = ParseMode( )
            return Parser.cNamespace().parse_file(self , filename, parse_mode)
        else:
            raise IOError("No such file:%s" % filename)

    

CWrapper.registerObjectType("parser", Parser)

cwrapper = CWrapper(OPM_LIB)
Parser.cNamespace().alloc = cwrapper.prototype("c_void_p parser_alloc()")
Parser.cNamespace().free  = cwrapper.prototype("void parser_free( parser )") 
Parser.cNamespace().has_keyword = cwrapper.prototype("bool parser_has_keyword( parser , char* )")
Parser.cNamespace().parse_file = cwrapper.prototype("deck_obj parser_parse_file( parser , char* , parse_mode)") 
