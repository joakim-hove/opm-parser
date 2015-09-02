from ert.cwrap import BaseCEnum
from opm import OPM_LIB


class ErrorAction(BaseCEnum):
    ALL_ACTIVE = None
    INACTIVE = None
    PARTLY_ACTIVE = None


ErrorAction.addEnum("THROW_EXCEPTION", 0)
ErrorAction.addEnum("WARN", 1)
ErrorAction.addEnum("IGNORE", 2)
ErrorAction.registerEnum(OPM_LIB, "error_action_enum")
