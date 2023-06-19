#ifndef 	 	__AUTOGETOFFSET_H_
#define	  	__AUTOGETOFFSET_H_


#include "probe.h"
#include "gcode.h"
#include "endstops.h"
#include "temperature.h"
#include "bedlevel.h"
#include "planner.h"
#include "powerloss.h"
#include "dgus_tft.h"
#include "ui_api.h"


#define NOZZLE_X    60 		  //设置喷嘴的X坐标      62.5 /
#define NOZZLE_Y    242			  //设置喷嘴的Y坐标    244 /
#define WIPE_Z    	-2.0			//擦料下降高度
#define WIPE        0
#define DEVIATION   -0.1      //调平模块校准系数
#define SWTICH_DEVIATION   -0.1 //喷嘴到平台高度系数

#define SWTICH_X_1  35			//设置接近开关探测基准X坐标点1
#define SWTICH_Y_1	205			//设置接近开关探测基准Y坐标点1

#define SWTICH_X_2  40			//设置接近开关探测基准X坐标点2
#define SWTICH_Y_2	190			//设置接近开关探测基准Y坐标点2
 
#define NOZZLE_TEMP 			220 		//喷嘴挤料温度
#define NOZZLE_COOL_TEMP 	140 			//喷嘴校准冷却温度

#define LOAD_LENGTH   		120			//进丝长度
#define LOAD_SPEED				8	   	//进丝速度
#define UNLOAD_LENGTH 		50			//退丝长度
#define UNLOAD_SPEED  		20			//退丝速度

#define RUN_DOWN_MM       -1.2    //校准模块触发后再下压距离
#define MOVE_XY_MM        10
//
#define DOWN_LENGTH  		"G1 F500 Z-2.5"           //擦料下压距离
#define WIPE_LEFT			"G1 F2000 X85 Y240"     //擦料开始座标
#define WIPE_RIGHT  		"G1 F2000 X90 Y250"     //擦料结束座标





typedef struct {
	xyz_pos_t leveing_postion;
}autoprobe_data;



class AutoProbe
{
	public:
		bool sdcard_enabled;
		autoprobe_data postion_data; 
		bool frist_load_config;
		bool need_save_data;
		uint32_t count;
		xyz_pos_t calibration_positon;
		xyz_pos_t home_position;
		float z_offset;
		bool home_flag;
		bool start_leveing;
		bool wait_for_bed;
		bool need_shake;
		
		bool need_home_leveing;
		bool need_home_printing;
		bool need_openFan;
	  bool LeveingFailSattue;
		uint8_t LeveingTipStatus;

		void Shake();
		void write();
		void read();
		void load_config();
	  bool module_calibration();


		static float probe_at_point_test(const xy_pos_t &pos, const ProbePtRaise raise_after, const uint8_t verbose_level=0,  bool probe_relative=true, const bool sanity_check=true) {
      		return probe.probe_at_point(pos.x, pos.y, raise_after, verbose_level, probe_relative, sanity_check);
		}
	private:
		float auto_zoffset;
		bool Wipe_material = true;
		float z1,z2,z3,z4,nozzle_deviation,switch_deviation;
		bool run_calibration_probe();

};

extern AutoProbe autoProbe;
#endif
