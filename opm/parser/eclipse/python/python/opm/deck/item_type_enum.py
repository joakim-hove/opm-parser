from ert.cwrap import BaseCEnum
from opm import OPM_LIB


class ItemType(BaseCEnum):
    INTEGER = None
    STRING = None
    DOUBLE = None


ItemType.addEnum("INTEGER", 1)
ItemType.addEnum("STRING", 2)
ItemType.addEnum("DOUBLE", 3)

ItemType.registerEnum(OPM_LIB, "item_type_enum")
