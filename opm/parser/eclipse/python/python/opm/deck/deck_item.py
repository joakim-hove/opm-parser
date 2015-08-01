from ert.cwrap import BaseCClass, CWrapper
from opm import OPM_LIB
from opm.deck import ItemType


class DeckItem(BaseCClass):

    def __init__(self):
        raise NotImplementedError("Can not create instantiate record directly")

    
    def __len__(self):
        """
        Returns the number of values in the item.
        """
        return DeckItem.cNamespace().size( self )
    

    def assertType(self):
        if not hasattr(self,"value_type"):
            self.value_type = DeckItem.cNamespace().get_type( self )
            if self.value_type == ItemType.INTEGER:
                self.iget = DeckItem.cNamespace().iget_int
            elif self.value_type == ItemType.DOUBLE:
                self.iget = DeckItem.cNamespace().iget_double
            elif self.value_type == ItemType.STRING:
                self.iget = DeckItem.cNamespace().iget_string
            else:
                raise Exception("What the ??")
                

            
    def __getitem__(self , index):
        """
        Will return value corresponding to @index.
        """
        self.assertType()
        if isinstance(index , int):
            if index < 0:
                index += len(self)
            if 0 <= index < len(self):
                return self.iget( self , index )
            else:
                raise IndexError("Invalid index:%d  -valid range [0,%d)" % (index , len(self)))
        else:
            raise TypeError("Expected integer index")

        

CWrapper.registerObjectType("deck_item", DeckItem)

cwrapper = CWrapper(OPM_LIB)
DeckItem.cNamespace().size      = cwrapper.prototype("int  deck_item_get_size( deck_item )")
DeckItem.cNamespace().get_type  = cwrapper.prototype("item_type_enum deck_item_get_type( deck_item )")
DeckItem.cNamespace().iget_int  = cwrapper.prototype("int deck_item_iget_int( deck_item , int)")
DeckItem.cNamespace().iget_double  = cwrapper.prototype("double deck_item_iget_double( deck_item , int)")
DeckItem.cNamespace().iget_string  = cwrapper.prototype("char* deck_item_iget_string( deck_item , int)")
