from ert.cwrap import BaseCClass, CWrapper
from opm import OPM_LIB

class Deck(BaseCClass):
    def __init__(self):
        c_ptr = Deck.cNamespace().alloc( )
        super(Deck , self).__init__( c_ptr )

        
    def __len__(self):
        """
        Will return the number of keywords in the deck.
        """
        return Deck.cNamespace().size(self)


    def __contains__(self , keyword):
        """
        Will return True if the deck has at least one occurence of @keword.
        """
        return Deck.cNamespace().has_keyword(self , keyword)


    def numKeywords(self , keyword):
        """
        Will count the number of occurences of @keyword.
        """
        return Deck.cNamespace().num_keywords(self , keyword)


    def __igetKeyword(self , index):
        keyword = Deck.cNamespace().iget_keyword( self , index )
        keyword.setParent( self )
        return keyword

    
    def __igetNamedKeyword(self , name , index):
        keyword = Deck.cNamespace().iget_named_keyword( self , name , index )
        keyword.setParent( self )
        return keyword
        

    def __getitem__(self, index):
        """Implements the [] operator for the deck.

        The @index variable can be either an integegr, i.e. deck[2]
        will return the third keyword in the deck. The integer based
        indexing supports slicing; in that case a normal Python list
        of keywords will be returned.

        Alternatively the @index can be a string: deck["PORO"] will
        return a Python list of all the PORO keywords in the deck.
        """
        if isinstance(index , int):
            if index < 0:
                index += len(self)

            if 0 <= index < len(self):
                return self.__igetKeyword( index )
            else:
                raise IndexError
        elif isinstance(index , slice):
            (start , step, stop) = index.indices( len(self) )
            keyword_list = []
            print start,stop,step
            for i in range(start,stop,step):
                keyword_list.append( self.__igetKeyword( i ))
            return keyword_list
        else:
            if isinstance(index , str):
                if index in self:
                    keyword_list = []
                    for i in range(self.numKeywords( index )):
                        keyword_list.append( self.__igetNamedKeyword(index , i))
                    return keyword_list
                else:
                    raise KeyError("No %s keyword in deck" % index)
            else:
                raise TypeError("Index must integer or string")

        
    def free(self):
        Deck.cNamespace().free( self )


        
#-----------------------------------------------------------------

                                             

CWrapper.registerObjectType("deck", Deck)

cwrapper = CWrapper(OPM_LIB)
Deck.cNamespace().alloc = cwrapper.prototype("c_void_p deck_alloc(  )") 
Deck.cNamespace().free  = cwrapper.prototype("void deck_free( deck )") 
Deck.cNamespace().size  = cwrapper.prototype("int deck_size( deck )")
Deck.cNamespace().iget_keyword = cwrapper.prototype("deck_keyword_ref deck_iget_keyword( deck , int)")
Deck.cNamespace().iget_named_keyword = cwrapper.prototype("deck_keyword_ref deck_iget_named_keyword( deck , char* , int)")
Deck.cNamespace().has_keyword = cwrapper.prototype("bool deck_has_keyword( deck , char*)")
Deck.cNamespace().num_keywords = cwrapper.prototype("int deck_num_keywords( deck , char*)")
