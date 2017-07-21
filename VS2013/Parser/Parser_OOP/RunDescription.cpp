#include "RunDescription.h"

using namespace std;


//---------------------------------------------
//July 13 2017

/*Cd*/
//63000 events
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_2200dVGEM_20kV_49VSiPM_Cd\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_2200dVGEM_20kV_49VSiPM_Cd\\";
//const int start_run_number = 191;
//const int stop_run_number = 254;
//
//68000 events
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_2200dVGEM_20kV_Cd\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_2200dVGEM_20kV_Cd\\";
//const int start_run_number = 122;
//const int stop_run_number = 190;
//
//101000 events
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_2200dVGEM_20kV_49VSiPM_Cd_2mmCol\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_2200dVGEM_20kV_49VSiPM_Cd_2mmCol\\";
//const int start_run_number = 255;
//const int stop_run_number = 355;
//
//44000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_18kV_Cd\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_18kV_Cd\\";
//const int start_run_number = 77;
//const int stop_run_number = 121;

/*X-ray*/
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_20kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_20kV\\";
//const int start_run_number = 55;
//const int stop_run_number = 56;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_20kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_20kV_ped\\";
//const int start_run_number = 57;
//const int stop_run_number = 58;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_18kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_18kV\\";
//const int start_run_number = 49;
//const int stop_run_number = 50;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_18kV_again2\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_18kV_again2\\";
//const int start_run_number = 53;
//const int stop_run_number = 54;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_18kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_18kV_ped\\";
//const int start_run_number = 51;
//const int stop_run_number = 52;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_16kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_16kV\\";
//const int start_run_number = 59;
//const int stop_run_number = 60;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_16kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_16kV_ped\\";
//const int start_run_number = 61;
//const int stop_run_number = 62;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_14kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_14kV\\";
//const int start_run_number = 63;
//const int stop_run_number = 64;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_14kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_14kV_ped\\";
//const int start_run_number = 65;
//const int stop_run_number = 66;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_12kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_12kV\\";
//const int start_run_number = 67;
//const int stop_run_number = 68;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_12kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_12kV_ped\\";
//const int start_run_number = 69;
//const int stop_run_number = 70;
//
//3000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_10kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_10kV\\";
//const int start_run_number = 71;
//const int stop_run_number = 73;
//
//3000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_10kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_10kV_ped\\";
//const int start_run_number = 74;
//const int stop_run_number = 76;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_20kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_20kV\\";
//const int start_run_number = 27;
//const int stop_run_number = 28;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_20kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_20kV_ped\\";
//const int start_run_number = 29;
//const int stop_run_number = 30;
//
//5000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_18kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_18kV\\";
//const int start_run_number = 21;
//const int stop_run_number = 25;
//
//1000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_18kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_18kV_ped\\";
//const int start_run_number = 26;
//const int stop_run_number = 26;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_18kV_again2\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_18kV_again2\\";
//const int start_run_number = 33;
//const int stop_run_number = 34;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_18kV_ped_again2\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_18kV_ped_again2\\";
//const int start_run_number = 31;
//const int stop_run_number = 32;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_16kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_16kV\\";
//const int start_run_number = 35;
//const int stop_run_number = 36;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_16kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_16kV_ped\\";
//const int start_run_number = 37;
//const int stop_run_number = 38;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_14kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_14kV\\";
//const int start_run_number = 39;
//const int stop_run_number = 40;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_14kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_14kV_ped\\";
//const int start_run_number = 41;
//const int stop_run_number = 42;
//
//2000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_10kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_10kV\\";
//const int start_run_number = 43;
//const int stop_run_number = 44;
//
//3000 events
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_10kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_10kV_ped\\";
//const int start_run_number = 46;
//const int stop_run_number = 48;

//---------------------------------------------



//---------------------------------------------
//June 22 2017

/*Cd*/
//10 events
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_20_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_20_thmV\\";
//const int start_run_number = 1888;
//const int stop_run_number = 1888;
//
//2230 events
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_20_th400mV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_20_th400mV\\";
//const int start_run_number = 1889;
//const int stop_run_number = 2111;
//
//1620 events
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_18_th300mV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_18_th300mV\\";
//const int start_run_number = 1722;
//const int stop_run_number = 1883;
//
//17180 events
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_18_th190mV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_18_th190mV\\";
//const int start_run_number = 4;
//const int stop_run_number = 1721;
//
//1860 events
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_16_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_16_thmV\\";
//const int start_run_number = 2112;
//const int stop_run_number = 2297;
//
//1980 events
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_14_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_14_thmV\\";
//const int start_run_number = 2298;
//const int stop_run_number = 2495;


/*X-ray*/
//330 events
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_20_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_20_thmV\\";
//const int start_run_number = 2749;
//const int stop_run_number = 2782;
//
//4180 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x_ray_18_2mmColl\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x_ray_18_2mmColl\\";
//const int start_run_number = 3537;
//const int stop_run_number = 3955;
//
//270 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_18_small_2\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_18_small_2\\";
//const int start_run_number = 2721;
//const int stop_run_number = 2748;
//
//700 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_16_thmV\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_16_thmV\\";
//const int start_run_number = 2783;
//const int stop_run_number = 2853;
//
//600 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_14_thmV\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_14_thmV\\";
//const int start_run_number = 2854;
//const int stop_run_number = 2914;
//
//380 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_12_thmV\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_12_thmV\\";
//const int start_run_number = 2915;
//const int stop_run_number = 2953;
//
//790 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_10_thmV\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_10_thmV\\";
//const int start_run_number = 2954;
//const int stop_run_number = 3033;
//
//330 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_10_thmV_recalib\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_10_thmV_recalib\\";
//const int start_run_number = 3034;
//const int stop_run_number = 3067;
//
//400 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_9_thmV\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_9_thmV\\";
//const int start_run_number = 3068;
//const int stop_run_number = 3108;
//
//590 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_8_thmV\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_8_thmV\\";
//const int start_run_number = 3109;
//const int stop_run_number = 3168;
//
//570 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_7_thmV\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_7_thmV\\";
//const int start_run_number = 3169;
//const int stop_run_number = 3226;
//
//640 events
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_6_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_6_thmV\\";
//const int start_run_number = 3227;
//const int stop_run_number = 3291;
//
//1030 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_5_thmV\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_5_thmV\\";
//const int start_run_number = 3292;
//const int stop_run_number = 3395;
//
//1400 events
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_4_thmV\\";
//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_4_thmV\\";
//const int start_run_number = 3396;
//const int stop_run_number = 3536;


//---------------------------------------------