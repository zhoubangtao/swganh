#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *	

def create(kernel):
	result = Tangible()

	result.template = "object/tangible/terminal/shared_terminal_elevator_down.iff"
	result.attribute_template_id = -1
	result.stfName("terminal_name","terminal_elevator")		
	
	#### BEGIN MODIFICATIONS ####
	result.setStringAttribute("radial_filename", "radials.elevator")
	result.setIntAttribute("elevator_can_go_down", 0)
	####  END MODIFICATIONS  ####
	
	return result