    #***
  #*********************************************************************
#*************************************************************************
#*** 
#*** GizmoDaemon Config Script v3:0
#*** 	LIRCUtil config
#***
#*****************************************
  #*****************************************
    #***

############################
# Imports
##########################

from GizmoDaemon import *

############################
# LIRCUtil Class definition
##########################

class LIRCUtil:
	"""
	LIRCUtil Class
	"""
	
	############################
	# Public Functions
	##########################
	
	def doesCodeMatch(self, ReferenceCode, ActualCode):
		"""
		Does the specified ActualCode match the ReferenceCode with a given Tolerance factor
		"""
		
		TotalDifferent = 0
		for Index in range(len(ReferenceCode)):
			TotalDifferent += Gizmod.bitDifference(ReferenceCode[Index], ord(ActualCode[Index]))
		for Index in range(len(ReferenceCode), len(ActualCode)):
			TotalDifferent += Gizmod.bitDifference(ActualCode, 0)
		print TotalDifferent
		
		return False
		
	############################
	# Private Functions
	##########################

	def __init__(self, Tolerance):
		""" 
		Default Constructor
		"""
		
		self.Tolerance = Tolerance

############################
# LIRCUtil class end
##########################
