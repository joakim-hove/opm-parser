from ert.cwrap import BaseCClass, CWrapper
from opm import OPM_LIB

from opm.log import MessageType

class OpmLog(BaseCClass):
    def __init__(self):
        raise Exception("Can not instantiate - just use class methods")

    @classmethod
    def addStdoutLog(cls , message_mask = MessageType.DEFAULT):
        OpmLog.cNamespace().add_stdout_log(message_mask)


    @classmethod
    def addStderrLog(cls , message_mask = MessageType.DEFAULT):
        OpmLog.cNamespace().add_stderr_log(message_mask)


    @classmethod
    def addFileLog(cls , filename , message_mask = MessageType.DEFAULT):
        OpmLog.cNamespace().add_file_log(filename , message_mask)

        
    @classmethod
    def addMessage(cls , message_type , message):
        OpmLog.cNamespace().add_message(message_type , message)
    


cwrapper = CWrapper(OPM_LIB)
OpmLog.cNamespace().add_file_log = cwrapper.prototype("void add_file_log( char* , int64 )")
OpmLog.cNamespace().add_stderr_log = cwrapper.prototype("void add_stderr_log( int64 )")
OpmLog.cNamespace().add_stdout_log = cwrapper.prototype("void add_stdout_log( int64 )")
OpmLog.cNamespace().add_message = cwrapper.prototype("void log_add_message( int64 , char* )")
    
