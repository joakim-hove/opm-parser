from ert.cwrap import BaseCClass, CWrapper
from opm import OPM_LIB

class DeckKeyword(BaseCClass):
    def __init__(self):
        raise NotImplementedError("Class can not be instantiated directly!")

    

CWrapper.registerObjectType("deck_keyword", DeckKeyword)

cwrapper = CWrapper(OPM_LIB)
