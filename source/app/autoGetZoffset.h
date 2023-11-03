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
#include "serial.h"

#define NOZZLE_X    62.3 		  //���������X����      62.5 /
#define NOZZLE_Y    239			  //���������Y����    244 /
#define WIPE_Z    	-2.0			//�����½��߶�
#define WIPE        0
#define DEVIATION   -0.1      //��ƽģ��У׼ϵ��
#define SWTICH_DEVIATION   -0.1 //���쵽ƽ̨�߶�ϵ��
 
#define NOZZLE_TEMP 			220 		//���켷���¶�
#define NOZZLE_COOL_TEMP 	140 			//����У׼��ȴ�¶�

#define LOAD_LENGTH   		120			//��˿����
#define LOAD_SPEED				8	   	//��˿�ٶ�
#define UNLOAD_LENGTH 		50			//��˿����
#define UNLOAD_SPEED  		20			//��˿�ٶ�

#define RUN_DOWN_MM       -1.2    //У׼ģ�鴥��������ѹ����
#define MOVE_XY_MM        10



typedef struct {
	xyz_pos_t leveing_postion;
}autoprobe_data;



class AutoProbe
{
	public:
		
		autoprobe_data postion_data; 		
	  	bool sdcard_enabled;						//дLOGʹ��
		bool enable_calibration_module;//ʹ��У׼ģ��
		bool enable_probe_swtich;//ʹ�ܵ�ƽ�ӽ�����
		bool frist_load_config;	//��һ�μ���У׼�������
		bool start_leveing;//��ʼ��ƽ
		bool need_save_data;	//��Ҫ����У׼��������
		bool need_z_down;//��Ҫ�½�
		bool need_move_x;//��Ҫ�ƶ�xy
		bool need_shake;//��Ҫ����
		bool need_close_fan;//��Ҫ�򿪷���
		bool need_home_leveing;//��ƽʱ��Ҫ����
		bool need_home_printing;//��ӡʱ����
	  	bool LeveingFailSattue;	//��ƽʧ��״̬
		bool is_onoff_fan;

		uint8_t LeveingTipStatus;//��ƽ��ʾ״̬
		uint32_t count;
		xyz_pos_t calibration_positon;	//У׼ģ������
		xyz_pos_t home_position;
		float z_offset;


		void Shake();
	  	bool module_calibration();
		static float probe_at_point_test(const xy_pos_t &pos, const ProbePtRaise raise_after, const uint8_t verbose_level=0,  bool probe_relative=true, const bool sanity_check=true) {
      		return probe.probe_at_point(pos.x, pos.y, raise_after, verbose_level, probe_relative, sanity_check);
		}
	private:
		float z3,nozzle_deviation,switch_deviation;

};

extern AutoProbe autoProbe;
#endif
