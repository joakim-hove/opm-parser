from unittest import TestCase

from ert.test import TestAreaContext

from opm.parser import Parser



class ParserTest(TestCase):
    def test_parse(self):
        p = Parser()
        with self.assertRaises(IOError):
            p.parseFile("does/not/exist")

        with TestAreaContext("parse-test"):
            with open("test.DATA", "w") as fileH:
                fileH.write("RUNSPEC\n")
                fileH.write("DIMENS\n")
                fileH.write(" 10 10 10 /\n")
        
            deck = p.parseFile( "test.DATA")
            self.assertEqual( len(deck) , 2 )


            
