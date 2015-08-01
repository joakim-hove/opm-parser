from ert.cwrap import BaseCClass, CWrapper
from opm import OPM_LIB

class DeckRecord(BaseCClass):

    def __init__(self):
        raise NotImplementedError("Can not create instantiate record directly")
    
    def __len__(self):
        """Returns the number of items in the keyword; observe that an item
        can consist of several input values. Observe that the count
        will include items with a default, which are not specified in
        the deck, i.e. for a input item like:

          DATES
             10 'MAY' 2012 /
          /
        
          dates_kw = deck["DATES"][0]
          record = dates_kw[0]
          length = len(record)

        The length variable will have the value 4 - because the DATES
        item has an optional fourth item 'TIME' with a default value.
        """
        return DeckRecord.cNamespace().size( self )


    def __contains__(self , item):
        return DeckRecord.cNamespace().has_item( self , item )
    
    
    def __getitem__(self , index):
        """
        Will return DeckItem corresponding to @index.
        """
        if isinstance(index , int):
            if index < 0:
                index += len(self)

            if 0 <= index < len(self):
                item = DeckRecord.cNamespace().iget_item( self , index )
                item.setParent( self )
                return item
            else:
                raise IndexError("Invalid index:%d  -valid range [0,%d)" % (index , len(self)))
        elif isinstance(index,str):
            if index in self:
                item = DeckRecord.cNamespace().get_item( self , index )
                item.setParent( self )
                return item
            else:
                raise KeyError("Not recognized item key:%s" % index)

            

CWrapper.registerObjectType("deck_record", DeckRecord)

cwrapper = CWrapper(OPM_LIB)
DeckRecord.cNamespace().size      = cwrapper.prototype("int  deck_record_get_size( deck_record )")
DeckRecord.cNamespace().has_item  = cwrapper.prototype("bool deck_record_has_item( deck_record , char* )")
DeckRecord.cNamespace().get_item  = cwrapper.prototype("deck_item_ref deck_record_get_item( deck_record , char* )")
DeckRecord.cNamespace().iget_item  = cwrapper.prototype("deck_item_ref deck_record_iget_item( deck_record , int )")
