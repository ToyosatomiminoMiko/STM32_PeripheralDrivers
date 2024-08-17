/*
 * number.c
 *
 *  Created on: Aug 17, 2024
 *      Author: Administrator
 */
#include <digital_tube.h>
void Show_number(uint8_t n)
{
	switch (n)
	{
	case 0:
		HAL_GPIO_WritePin(Ng_GPIO_Port, Ng_Pin, RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(Ng_GPIO_Port, Ng_Pin, SET);
		break;
	case 1:
		HAL_GPIO_WritePin(Na_GPIO_Port, Na_Pin, RESET);
		HAL_GPIO_WritePin(Nf_GPIO_Port, Nf_Pin, RESET);
		HAL_GPIO_WritePin(Ng_GPIO_Port, Ng_Pin, RESET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, RESET);
		HAL_GPIO_WritePin(Nd_GPIO_Port, Nd_Pin, RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(Na_GPIO_Port, Na_Pin, SET);
		HAL_GPIO_WritePin(Nf_GPIO_Port, Nf_Pin, SET);
		HAL_GPIO_WritePin(Ng_GPIO_Port, Ng_Pin, SET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, SET);
		HAL_GPIO_WritePin(Nd_GPIO_Port, Nd_Pin, SET);
		break;
	case 2:
		HAL_GPIO_WritePin(Nf_GPIO_Port, Nf_Pin, RESET);
		HAL_GPIO_WritePin(Nc_GPIO_Port, Nc_Pin, RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(Nf_GPIO_Port, Nf_Pin, SET);
		HAL_GPIO_WritePin(Nc_GPIO_Port, Nc_Pin, SET);
		break;
	case 3:
		HAL_GPIO_WritePin(Nf_GPIO_Port, Nf_Pin, RESET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(Nf_GPIO_Port, Nf_Pin, SET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, SET);
		break;
	case 4:
		HAL_GPIO_WritePin(Na_GPIO_Port, Na_Pin, RESET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, RESET);
		HAL_GPIO_WritePin(Nd_GPIO_Port, Nd_Pin, RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(Na_GPIO_Port, Na_Pin, SET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, SET);
		HAL_GPIO_WritePin(Nd_GPIO_Port, Nd_Pin, SET);
		break;
	case 5:
		HAL_GPIO_WritePin(Nb_GPIO_Port, Nb_Pin, RESET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(Nb_GPIO_Port, Nb_Pin, SET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, SET);
		break;
	case 6:
		HAL_GPIO_WritePin(Nb_GPIO_Port, Nb_Pin, RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(Nb_GPIO_Port, Nb_Pin, SET);
		break;
	case 7:
		HAL_GPIO_WritePin(Nf_GPIO_Port, Nf_Pin, RESET);
		HAL_GPIO_WritePin(Ng_GPIO_Port, Ng_Pin, RESET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, RESET);
		HAL_GPIO_WritePin(Nd_GPIO_Port, Nd_Pin, RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(Nf_GPIO_Port, Nf_Pin, SET);
		HAL_GPIO_WritePin(Ng_GPIO_Port, Ng_Pin, SET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, SET);
		HAL_GPIO_WritePin(Nd_GPIO_Port, Nd_Pin, SET);
		break;
	case 8:
		HAL_Delay(1);
		break;
	case 9:
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, SET);
		break;
	default:
		HAL_GPIO_WritePin(Na_GPIO_Port, Na_Pin, RESET);
		HAL_GPIO_WritePin(Nb_GPIO_Port, Nb_Pin, RESET);
		HAL_GPIO_WritePin(Nc_GPIO_Port, Nc_Pin, RESET);
		HAL_GPIO_WritePin(Nd_GPIO_Port, Nd_Pin, RESET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, RESET);
		HAL_GPIO_WritePin(Nf_GPIO_Port, Nf_Pin, RESET);
		HAL_GPIO_WritePin(Ng_GPIO_Port, Ng_Pin, RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(Na_GPIO_Port, Na_Pin, SET);
		HAL_GPIO_WritePin(Nb_GPIO_Port, Nb_Pin, SET);
		HAL_GPIO_WritePin(Nc_GPIO_Port, Nc_Pin, SET);
		HAL_GPIO_WritePin(Nd_GPIO_Port, Nd_Pin, SET);
		HAL_GPIO_WritePin(Ne_GPIO_Port, Ne_Pin, SET);
		HAL_GPIO_WritePin(Nf_GPIO_Port, Nf_Pin, SET);
		HAL_GPIO_WritePin(Ng_GPIO_Port, Ng_Pin, SET);
	}
}

void H1_Show(uint8_t num)
{
	HAL_GPIO_WritePin(H1_GPIO_Port, H1_Pin, RESET);
	Show_number(num);
	HAL_GPIO_WritePin(H1_GPIO_Port, H1_Pin, SET);
}
void H2_Show(uint8_t num)
{
	HAL_GPIO_WritePin(H2_GPIO_Port, H2_Pin, RESET);
	Show_number(num);
	HAL_GPIO_WritePin(H2_GPIO_Port, H2_Pin, SET);
}
void H3_Show(uint8_t num)
{
	HAL_GPIO_WritePin(H3_GPIO_Port, H3_Pin, RESET);
	Show_number(num);
	HAL_GPIO_WritePin(H3_GPIO_Port, H3_Pin, SET);
}
void H4_Show(uint8_t num)
{
	HAL_GPIO_WritePin(H4_GPIO_Port, H4_Pin, RESET);
	Show_number(num);
	HAL_GPIO_WritePin(H4_GPIO_Port, H4_Pin, SET);
}
