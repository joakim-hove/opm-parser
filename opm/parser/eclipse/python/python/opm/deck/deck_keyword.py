from ert.cwrap import BaseCClass, CWrapper
from opm import OPM_LIB

class DeckKeyword(BaseCClass):

    def __init__(self , kw):
        c_ptr = DeckKeyword.cNamespace().alloc( kw )
        super(DeckKeyword, self).__init__(c_ptr)

    def __len__(self):
        """
        Returns the number of records in the keyword.
        """
        return DeckKeyword.cNamespace().size( self )

    def __getitem__(self , index):
        """
        Will return DeckRecord corresponding to @index.
        """
        if index < 0:
            index += len(self)
            
        if 0 <= index < len(self):
            record = DeckKeyword.cNamespace().iget_record( self , index )
            record.setParent( self )
            return record
        else:
            raise IndexError("Invalid index:%d  -valid range [0,%d)" % (index , len(self)))

    def __str__(self):
        return self.name()

    def name(self):
        return DeckKeyword.cNamespace().get_name( self )

    
    def free(self):
        DeckKeyword.cNamespace().free( self )
    

CWrapper.registerObjectType("deck_keyword", DeckKeyword)

cwrapper = CWrapper(OPM_LIB)
DeckKeyword.cNamespace().get_name  = cwrapper.prototype("char* deck_keyword_get_name( deck_keyword )")
DeckKeyword.cNamespace().size  = cwrapper.prototype("int deck_keyword_get_size( deck_keyword )")
DeckKeyword.cNamespace().alloc  = cwrapper.prototype("c_void_p deck_keyword_alloc( char* )")
DeckKeyword.cNamespace().free  = cwrapper.prototype("void deck_keyword_free( deck_keyword )") 
DeckKeyword.cNamespace().iget_record = cwrapper.prototype("deck_record_ref deck_keyword_iget_record( deck_keyword , int)") 
