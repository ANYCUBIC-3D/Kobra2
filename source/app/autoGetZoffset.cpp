#include "autoGetZoffset.h"
#include "eeprom_api.h"

#define FLASH_AUTOGETZOFFSET_DATA_ADDR   ((uint32_t)0x0009000U)

//2
AutoProbe autoProbe;
#define ADD_DEC  10


void AutoProbe::Shake()
{
	if(need_shake == false) return;
	
	static uint32_t  Shake_time = 0;
	char cmd[64]= {0};
	
	sprintf_P(cmd, PSTR("G1 F3000 Y%f \n G1 F3000 Y%f"), calibration_positon.y-0.3, calibration_positon.y);
	
	Shake_time = millis();
	
	while( READ(Z_MAX_PIN) != Z_MAX_ENDSTOP_INVERTING)
	{		
		if(millis() - Shake_time >5000)
		{
			break;
		}
    	gcode.process_subcommands_now(cmd);

		safe_delay(2);
	}
}

bool AutoProbe::module_calibration()
{
		float z1;
		soft_endstop._enabled = false;// Turn off the software limit
		endstops.z_switch_enabled = true;

		endstops.auto_probe_enabled = true;
		endstops.z_probe_enabled = false;
		need_shake  = true;//
		LeveingFailSattue = true;
				
		do_blocking_move_to_z(current_position.z+5,5);//

		do_blocking_move_to_xy(calibration_positon.x,calibration_positon.y,100);//
		
		if( READ(Z_MAX_PIN) != Z_MAX_ENDSTOP_INVERTING){
				Shake();

		}	
	
		z1 = probe_at_point_test(calibration_positon, PROBE_PT_RAISE, 0,false);
	
		endstops.auto_probe_enabled = false;
		endstops.enable_globally(false);
		endstops.enable_z_probe(false);
		LeveingFailSattue = false;
		endstops.z_switch_enabled = 	false;
		need_shake = false;
		planner.synchronize();

			
		probe.stow();
		soft_endstop._enabled = true;
		
		if (isnan(z1)) return;
		
		thermalManager.set_fan_speed(0, 0);//
		ExtUI::onSetPopUpIndex(25);
}









