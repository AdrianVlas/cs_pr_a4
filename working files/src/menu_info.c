#include "header.h"

/*****************************************************/
//������� ����� ����������� ���������� �� ���� ����������� ������������ � ���� ����� ���'��
/*****************************************************/
void make_ekran_info()
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_INFO_M2][MAX_COL_LCD + 1] = 
  {
    {
      "   ������ ��    ",
      "   ������ ��    "
    },
    {
      "   ����� ��    ",
      "   ����� ��    "
    },
    {
      "   VER.of F/W   ",
      "   VER.of MM    "
    },
    {
      "   ������ ��    ",
      "   ������ ��    "
    }
  };

  int index_language = index_language_in_array(settings_fix_prt.language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned char value_str[MAX_COL_LCD + 1] = "                ";
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  unsigned int index_in_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  int first_char_row1, last_chat_row1;
  
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    if (index_in_ekran < (MAX_ROW_INFO_M2 << 1))//�������� �� ��� ��������� MAX_ROW_INFO_M2 ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran>>1][j];
        
        if ((index_in_ekran >> 1) == INDEX_INFO_M2_FIWMWARE)
        {
          unsigned int index_tmp = 0;

#if VERSIA_PZ > 9
          value_str[index_tmp++] = (VERSIA_PZ / 10) + 0x30;
          value_str[index_tmp++] = (VERSIA_PZ % 10) + 0x30;
#else
          value_str[index_tmp++] = VERSIA_PZ + 0x30;
#endif

          value_str[index_tmp++] = '.';
          
#if MODYFIKACIA_VERSII_PZ > 9
          value_str[index_tmp++] = (MODYFIKACIA_VERSII_PZ / 10) + 0x30;
          value_str[index_tmp++] = (MODYFIKACIA_VERSII_PZ % 10) + 0x30;
#else
          value_str[index_tmp++] = MODYFIKACIA_VERSII_PZ + 0x30;
#endif

          value_str[index_tmp++] = '.';
          
#if ZBIRKA_VERSII_PZ > 9
          value_str[index_tmp++] = (ZBIRKA_VERSII_PZ / 10) + 0x30;
          value_str[index_tmp++] = (ZBIRKA_VERSII_PZ % 10) + 0x30;
#else
          value_str[index_tmp++] = ZBIRKA_VERSII_PZ + 0x30;
#endif
          unsigned int shift = (MAX_COL_LCD - index_tmp) >> 1;
          first_char_row1 = shift;
          last_chat_row1 = first_char_row1 + index_tmp;
          index_tmp--;
          for (int k = index_tmp; k >= 0; k-- ) 
          {
            value_str[k + shift] = value_str[k];
            value_str[k] = ' ';
          }
          
        }
        else if ((index_in_ekran>>1) == INDEX_INFO_M2_MEMORY_MAP)
        {
#if VERSIA_GMM > 9
          value_str[COL_INFO_BEGIN_2 + 0] = (VERSIA_GMM / 10) + 0x30;
          value_str[COL_INFO_BEGIN_2 + 1] = (VERSIA_GMM % 10) + 0x30;
#else
          value_str[COL_INFO_BEGIN_2 + 0] = ' ';
          value_str[COL_INFO_BEGIN_2 + 1] = VERSIA_GMM + 0x30;
#endif

          value_str[COL_INFO_BEGIN_2 + 2] = '.';
          
#if MODYFIKACIA_VERSII_GMM > 9
          value_str[COL_INFO_BEGIN_2 + 3] = (MODYFIKACIA_VERSII_GMM / 10) + 0x30;
          value_str[COL_INFO_BEGIN_2 + 4] = (MODYFIKACIA_VERSII_GMM % 10) + 0x30;
#else
          value_str[COL_INFO_BEGIN_2 + 3] = MODYFIKACIA_VERSII_GMM + 0x30;
          value_str[COL_INFO_BEGIN_2 + 4] = ' ';
#endif
        }
        
      }
      else
      {
        //� ������� ����� ����� �������� ��������
        for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = value_str[j];
      }
    }
    else
      for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_in_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_state_menu2.position_cursor_y = ((position_temp << 1) + 1) & (MAX_ROW_LCD - 1);
  int last_position_cursor_x = MAX_COL_LCD;

  if (current_state_menu2.index_position == INDEX_INFO_M2_FIWMWARE)
  {
    current_state_menu2.position_cursor_x = first_char_row1;
    last_position_cursor_x = last_chat_row1;
  }
  else
  {
    current_state_menu2.position_cursor_x = COL_INFO_BEGIN_2;
    last_position_cursor_x = COL_END_END_2;
  }

  //ϳ������� ������ �� ������� �������
  while (((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x + 1]) == ' ') && 
         (current_state_menu2.position_cursor_x < (last_position_cursor_x -1))) current_state_menu2.position_cursor_x++;

  //������ ������� ���, ��� �� ��� ����� ������
  if (((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x]) != ' ') && 
      (current_state_menu2.position_cursor_x > 0)) current_state_menu2.position_cursor_x--;

  //������ �������
  current_state_menu2.cursor_on = 1;
  //������ �� ����
  current_state_menu2.cursor_blinking_on = 0;
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ��� ���� � ���� ��������
/*****************************************************/
void make_ekran_date_time_pz(void)
{
  uint8_t name_string[2*MAX_ROW_FOR_DATE_TIME_PZ][MAX_COL_LCD + 1] = 
  {
    "   XX-XX-20XX   ",
    "     XX:XX      "
  };
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  /******************************************/
  //���������� ���� ���������� �������
  /******************************************/
  //����
  name_string[0][3 ] = (DAY_VER >>  4) + 0x30;
  name_string[0][4 ] = (DAY_VER & 0xf) + 0x30;

  //̳����
  name_string[0][6 ] = (MONTH_VER >>  4) + 0x30;
  name_string[0][7 ] = (MONTH_VER & 0xf) + 0x30;

  //г�
  name_string[0][11] = (YEAR_VER >>  4) + 0x30;
  name_string[0][12] = (YEAR_VER & 0xf) + 0x30;

  //������
  name_string[1][5 ] = (HOUR_VER >>  4) + 0x30;
  name_string[1][6 ] = (HOUR_VER & 0xf) + 0x30;

  //�������
  name_string[1][8 ] = (MINUTE_VER >>  4) + 0x30;
  name_string[1][9 ] = (MINUTE_VER & 0xf) + 0x30;
  /******************************************/
  
  //�������  ����� � ������� �����
  for (size_t i = 0; i< MAX_ROW_LCD; i++)
  {
    //������� ����� ����� ���������, �� �� ����� ����������
    for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (index_in_ekran < (2*MAX_ROW_FOR_DATE_TIME_PZ)) ? name_string[index_in_ekran][j] : ' ';

    index_in_ekran++;
  }

  //������ �� ���������� ������� �� ������ �������
  current_state_menu2.position_cursor_x = 0;
  //³���������� ������ �� �������� � 0
  current_state_menu2.position_cursor_y = 0;
  current_state_menu2.position_cursor_y = 0;
  //������ ���������
  current_state_menu2.cursor_on = 0;
  //������ �� ����
  current_state_menu2.cursor_blinking_on = 0;
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
