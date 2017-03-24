#include "header.h"
#include "../inc/libraries.h"


/**************************************/
//ӥ񲳢ᮭ󠧮㭳𭼮ߠSRAM
/**************************************/
inline void test_external_SRAM(void)
{
  //è讠ภ۬ԫ𪳱򼠤㯵⡩򨵠񫳢
  unsigned int size_SRAM_word = (((unsigned int)&__ICFEDIT_region_RAM1_size__) + 1) >> 1;
  
  //è讠󠺬롧Ԣ ௷ᳮꡧԸߠﰥ𠲨㮮ߠ࡬'󲳍
   unsigned short int *point = ((unsigned short int *)&__ICFEDIT_region_RAM1_start__);
  
  //Ƞ௢󸏦믬԰볠询񞁻􈀥𠲨㮮ߠ࡬'󲳠߿ ᥰ沮򍊠 for (unsigned int i = 0; i < size_SRAM_word; i++) *point++ = (unsigned short int)(i & 0xffff);
  
  //Х𥢳𿺬󨲳㡭, 󨠳 㱳񠪮촰롵 ౮ੱ᭳ 򳠷鲫ଠ󪳠򘏯汥宼ᰨ񠫨
  unsigned int error = 0, i = 0;
  point = ((unsigned short int *)&__ICFEDIT_region_RAM1_start__);
  while((i < size_SRAM_word) && (error == 0))
  {
    if ((*point) == ((unsigned short int)(i & 0xffff)))
    {
      //ӥ񲠤ᮮߠ믬԰먠౮깮⡢填      i++;
      *point++ = 0;
    }
    else
    {
      //ӥ񲠤ᮮߠ믬԰먠౮깮⡢填      
      error = 0xff;
      //è񲠢쿺󸏢Ԥﭫ殭󠯰ﭨ쫳 򥱲󠧮㭳𼮿 ﰥ𠲨㮮ߠ࡬'󲳍
      _SET_BIT(set_diagnostyka, ERROR_EXTERNAL_SRAM_BIT);
    }
  }
}
/**************************************/







#ifdef __cplusplus
extern "C" {
#endif

#pragma language=extended

__interwork int __low_level_init(void);

__interwork int __low_level_init(void)
{
  /*==================================*/
  /*  Initialize hardware.            */
  /*==================================*/
FSMC_SRAM_Init();
  /**********************/
  //Π񲰮򢠭ﴭԢ ౮򥱮𠍊  /**********************/
  GPIO_InitTypeDef GPIO_InitStructure;

GPIO_InitStructure.GPIO_Pin = GPIO_PIN_EXTERNAL_WATCHDOG;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIO_EXTERNAL_WATCHDOG, &GPIO_InitStructure);
  /* ȭԬ໬ԭ 询񞍮䮠Watchdog */
  GPIO_ResetBits(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG);
    /**********************/
  //ӥ񲳺󸏢񞎠SRAM
  /**********************/
  test_external_SRAM();
  /**********************/
  
  //Ȭԭ򺬮 񲠭 ᴲ󠧮㭳𭼮䮠Watchdog ౮򨫥箨鍊
  GPIO_WriteBit(
                GPIO_EXTERNAL_WATCHDOG,
                GPIO_PIN_EXTERNAL_WATCHDOG,
                (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
               );
    
  /*==================================*/
  /* Choose if segment initialization */
  /* should be done or not.           */
  /* Return: 0 to omit seg_init       */
  /*         1 to run seg_init        */
  /*==================================*/
  return 1;
}

#pragma language=default

#ifdef __cplusplus
}
#endif

