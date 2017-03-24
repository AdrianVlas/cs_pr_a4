#include "header.h"

/*****************************************************/
//Запустити передачу і прийом по SPI
/*****************************************************/
void start_exchange_via_spi(int index_chip, unsigned int number_bytes_transfer)
{
  //Фіксуємо скільки байт ми будем передавати (це потрібно на випадок винекнення помилки - щоб можна було повторно запустити цю операцію)
  number_bytes_transfer_spi_df = number_bytes_transfer;
  
  //Зупиняємо потік DMA на прийом даних якщо він запущений
  if ((DMA_StreamSPI_DF_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamSPI_DF_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Rx->NDTR = number_bytes_transfer;
  //Зупиняємо потік DMA на передачу даних якщо він запущений
  if ((DMA_StreamSPI_DF_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamSPI_DF_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Tx->NDTR = number_bytes_transfer;
  
  //Очищаємо прапореці, що сигналізує про завершення прийом/передачі даних для DMA1 по каналу SPI_DF_Rx і SPI_DF_Tx
  DMA_ClearFlag(DMA_StreamSPI_DF_Rx, DMA_FLAG_TCSPI_DF_Rx | DMA_FLAG_HTSPI_DF_Rx | DMA_FLAG_TEISPI_DF_Rx | DMA_FLAG_DMEISPI_DF_Rx | DMA_FLAG_FEISPI_DF_Rx);
  DMA_ClearFlag(DMA_StreamSPI_DF_Tx, DMA_FLAG_TCSPI_DF_Tx | DMA_FLAG_HTSPI_DF_Tx | DMA_FLAG_TEISPI_DF_Tx | DMA_FLAG_DMEISPI_DF_Tx | DMA_FLAG_FEISPI_DF_Tx);
  
  //Дозволяємо передачу через DMA
  if ((SPI_DF->CR2 & SPI_I2S_DMAReq_Tx) == 0) SPI_DF->CR2 |= SPI_I2S_DMAReq_Tx;
  //Дозволяємо прийом через DMA
  if ((SPI_DF->CR2 & SPI_I2S_DMAReq_Rx) == 0) SPI_DF->CR2 |= SPI_I2S_DMAReq_Rx;

  //Виставляємо chip_select  з встановленням у драйвері повідомлення, що іде обмін
  if (index_chip == INDEX_DATAFLASH_1) GPIO_SPI_DF_TOGGLE->BSRRH = GPIO_SPI_DF_TOGGLE_Pin;//DF_TOGGLE - пін переводимо у 0 
  else if (index_chip == INDEX_DATAFLASH_2)GPIO_SPI_DF_TOGGLE->BSRRL = GPIO_SPI_DF_TOGGLE_Pin;//DF_TOGGLE - пін переводимо у 1
  else
  {
    //Відбцлася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(6);
  }
  driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING;
  GPIO_SPI_DF->BSRRH = GPIO_NSSPin_DF; //Виставляємо Chip_select переводом NSS  у 0

  //Дозволяэмо генерацыю переривань від потоку DMA_StreamSPI_DF_Rx
  DMA_StreamSPI_DF_Rx->CR |= DMA_IT_TC;
  
  //Очищаємо можливі помилкит
  SPI_DF->DR;
  SPI_DF->SR;

  //Запускаємо прийом-передачу 
  DMA_StreamSPI_DF_Rx->CR |= (uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Tx->CR |= (uint32_t)DMA_SxCR_EN;
}
/*****************************************************/

/*****************************************************/
//Запуск зчитування статусу з мікросхеми dataFlash
/*****************************************************/
void dataflash_status_read(int index_chip)
{
  if ((index_chip == INDEX_DATAFLASH_1) || (index_chip == INDEX_DATAFLASH_2))
  {
    driver_spi_df[index_chip].code_operation = CODE_OPERATION_STATUS_READ;
    TxBuffer_SPI_DF[0] = 0xD7;
    start_exchange_via_spi(index_chip, 2);
  }
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(7);
  }
  
}
/*****************************************************/

/*****************************************************/
//Подача команди на переконфігурацію DataFlash на розмір сторінки 256Б
/*****************************************************/
void dataflash_set_pagesize_256(int index_chip)
{
  if ((index_chip == INDEX_DATAFLASH_1) || (index_chip == INDEX_DATAFLASH_2))
  {
    driver_spi_df[index_chip].code_operation = CODE_OPERATION_PAGESIZE_256;
    TxBuffer_SPI_DF[0] = 0x3D;
    TxBuffer_SPI_DF[1] = 0x2A;
    TxBuffer_SPI_DF[2] = 0x80;
    TxBuffer_SPI_DF[3] = 0xA6;
    start_exchange_via_spi(index_chip, 4);
  }
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(8);
  }
  
}
/*****************************************************/

/*****************************************************/
//Подача команди повного стирання мікросхеми
/*****************************************************/
void dataflash_erase(int index_chip)
{
  if ((index_chip == INDEX_DATAFLASH_1) || (index_chip == INDEX_DATAFLASH_2))
  {
    driver_spi_df[index_chip].code_operation = CODE_OPERATION_ERASE;
    TxBuffer_SPI_DF[0] = 0xC7;
    TxBuffer_SPI_DF[1] = 0x94;
    TxBuffer_SPI_DF[2] = 0x80;
    TxBuffer_SPI_DF[3] = 0x9A;
    start_exchange_via_spi(index_chip, 4);
  }
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(9);
  }
  
}
/*****************************************************/

/*****************************************************/
//Запис даних у буфер з подальшим стиранням і перепрограмуванням
/*****************************************************/
void dataflash_mamory_page_program_through_buffer(int index_chip)
{
  unsigned int size_page;
  driver_spi_df[index_chip].code_operation = CODE_OPERATION_WRITE_PAGE_THROUGH_BUFFER;
  TxBuffer_SPI_DF[0] = 0x82;
  
  if (index_chip == INDEX_DATAFLASH_1)
  {
    size_page = SIZE_PAGE_DATAFLASH_1;
  }
  else if (index_chip == INDEX_DATAFLASH_2)
  {
    size_page = SIZE_PAGE_DATAFLASH_2;
  }
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(11);
  }
  
  //Запускаємо процес запису
  start_exchange_via_spi(index_chip, (4 + size_page));
}
/*****************************************************/

/*****************************************************/
//Зчитування даних на швидкості до 66МГц
/*****************************************************/
void dataflash_mamory_read(int index_chip)
{
  driver_spi_df[index_chip].code_operation = CODE_OPERATION_READ_HIGH_FREQ;
  TxBuffer_SPI_DF[0] = 0x0B;

  int temp_value_for_address;
    
  if (index_chip == INDEX_DATAFLASH_1)
  {
    if(false)
    {
    }
    else if (
             (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU ) ||
             (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB  ) ||
             (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_RS485)
            )   
    {
      //Читання даних реєстратора програмних помилок
      unsigned int number_record;
      if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU)
      {
        number_record = number_record_of_pr_err_into_menu;
      }
      else if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB)
      {
        number_record = number_record_of_pr_err_into_USB;
      }
      else
      {
        number_record = number_record_of_pr_err_into_RS485;
      }

      //Визначаємо початкову адресу запису, яку треба зчитати
      temp_value_for_address = info_rejestrator_pr_err.next_address - ((number_record + 1)<<VAGA_SIZE_ONE_RECORD_PR_ERR);
      while (temp_value_for_address < MIN_ADDRESS_PR_ERR_AREA) temp_value_for_address = temp_value_for_address + SIZE_PR_ERR_AREA; 
        
      TxBuffer_SPI_DF[1] = (temp_value_for_address >> 16) & 0x0f; 
      TxBuffer_SPI_DF[2] = (temp_value_for_address >> 8 ) & 0xff; 
      TxBuffer_SPI_DF[3] = (temp_value_for_address      ) & 0xff; 

      //Після адреси має іти один додатковй байт як буфер перед початком отримування реальних даних
        
      //Подальше вмістиме не має значення

      //Запускаємо процес запису
      start_exchange_via_spi(index_chip, (5 + SIZE_ONE_RECORD_PR_ERR));
    }
    else
    {
      //Відбулася невизначена помилка, тому треба піти на перезавантаження
      total_error_sw_fixed(13);
    }
  }
  else if (index_chip == INDEX_DATAFLASH_2)
  {
  }
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(14);
  }
}
/*****************************************************/

/*****************************************************/
//Зчитування сторінки пам'яті DataFlash у буфер
/*****************************************************/
void dataflash_mamory_page_into_buffer(int index_chip)
{
  unsigned int address_into_dataflash;
  driver_spi_df[index_chip].code_operation = CODE_OPERATION_READ_PAGE_INTO_BUFFER;
  TxBuffer_SPI_DF[0] = 0x53;
  
  if (index_chip == INDEX_DATAFLASH_1)
  {
    //Формуємо адресу сторінки для зчитування у буфер DataFlash
    address_into_dataflash = info_rejestrator_pr_err.next_address;

    TxBuffer_SPI_DF[1] = (address_into_dataflash >> 16) & 0x0f; 
    TxBuffer_SPI_DF[2] = (address_into_dataflash >> 8 ) & 0xff; 
    TxBuffer_SPI_DF[3] = 0; 
  }
  else if (index_chip == INDEX_DATAFLASH_2)
  {
  }
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(15);
  }

  //Запускаємо процес запису
  start_exchange_via_spi(index_chip, 4);
}
/*****************************************************/

/*****************************************************/
//Запис нових даних у буфер мікрсхеми DataFlash
/*****************************************************/
void dataflash_mamory_write_buffer(int index_chip)
{
  unsigned int size_page;

  driver_spi_df[index_chip].code_operation = CODE_OPERATION_WRITE_BUFFER;
  TxBuffer_SPI_DF[0] = 0x84;

  if (index_chip == INDEX_DATAFLASH_1)
  {
    size_page = SIZE_PAGE_DATAFLASH_1;

    //Запис даних реєстратора програмних подій з останнього свобідного місця і або всі дані, або стільки скільки може вміститися до кінця сторінки
      
    //Формуємо адресу для запису
    unsigned int next_address_into_buffer = info_rejestrator_pr_err.next_address & 0xff;
        
    TxBuffer_SPI_DF[1] = 0; 
    TxBuffer_SPI_DF[2] = 0; 
    TxBuffer_SPI_DF[3] = next_address_into_buffer; 
    
    //Починаємо заповнювати буфер для передачі у буфер мікросхеми DataFlash даними для запису
    number_recods_writing_into_dataflash_now = 0;
    unsigned int head = head_fifo_buffer_pr_err_records, tail = tail_fifo_buffer_pr_err_records;
    while(
          ((next_address_into_buffer + SIZE_ONE_RECORD_PR_ERR - 1) < size_page) &&
          (tail != head)
         )
    {
      //Заповнюємо дальше буфер даними, які треба записати 
      for (unsigned int i = 0; i < SIZE_ONE_RECORD_PR_ERR; i++ )
        TxBuffer_SPI_DF[4 + number_recods_writing_into_dataflash_now*SIZE_ONE_RECORD_PR_ERR + i] =
          buffer_pr_err_records[tail*SIZE_ONE_RECORD_PR_ERR + i];
      
      //Змінюємо контролюючі змінні
      number_recods_writing_into_dataflash_now++;
      next_address_into_buffer += SIZE_ONE_RECORD_PR_ERR;
      tail++;
      if(tail >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) tail = 0;
    }

    //Запускаємо процес запису
    start_exchange_via_spi(index_chip, (4 + number_recods_writing_into_dataflash_now*SIZE_ONE_RECORD_PR_ERR));
  }
  else if (index_chip == INDEX_DATAFLASH_2)
  {
  }
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(16);
  }
}
/*****************************************************/

/*****************************************************/
//Запис буфер DataFlash у пам'ять мікросхеми DataFlash
/*****************************************************/
void dataflash_mamory_buffer_into_memory(int index_chip)
{
  //Запис внутрішнбього буферу (буферу 1) пам'ять DataFlash
  driver_spi_df[index_chip].code_operation = CODE_OPERATION_WRITE_BUFFER_INTO_MEMORY_WITH_ERASE;
  TxBuffer_SPI_DF[0] = 0x83;

  if (index_chip == INDEX_DATAFLASH_1)
  {
    //У структурі по інформації стану реєстраторів виставляємо повідомлення, що почався запис і ще не закінчився
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
    info_rejestrator_pr_err.saving_execution = 1;
    
    //Формуємо адресу для запису
    unsigned int address_into_dataflash = info_rejestrator_pr_err.next_address;
        
    TxBuffer_SPI_DF[1] = (address_into_dataflash >> 16) & 0x0f; 
    TxBuffer_SPI_DF[2] = (address_into_dataflash >> 8 ) & 0xff; 
    TxBuffer_SPI_DF[3] = 0; 
  }
  else if (index_chip == INDEX_DATAFLASH_2)
  {
  }
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(17);
  }

  //Запускаємо процес запису
  start_exchange_via_spi(index_chip, 4);
}
/*****************************************************/


/*****************************************************/
//аналіз отриманих даних після запиту
/*****************************************************/
inline void analize_received_data_dataflash(int index_chip)
{
  switch (driver_spi_df[index_chip].code_operation)
  {
  case CODE_OPERATION_STATUS_READ:
    {
      if ((index_chip == INDEX_DATAFLASH_1) || (index_chip == INDEX_DATAFLASH_2))
      {
        //Виконувалася операція зчитування статусу мікросхеми DataFlash
        if ((RxBuffer_SPI_DF[1] & (1<< 7)) != 0) dataflash_not_busy |= (1 << index_chip);
        else dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
        
        driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
        driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      }
      else
      {
        //Відбулася невизначена помилка, тому треба піти на перезавантаження
        total_error_sw_fixed(26);
      }
      break;
    }
  case CODE_OPERATION_ERASE:
    {
      //Подана команда повного стирання мікросхеми
     
      //Знімаємо з черги запуск повного стирання
      if (index_chip == INDEX_DATAFLASH_1) control_tasks_dataflash &= (unsigned int)(~TASK_ERASE_DATAFLASH_1);
      else if (index_chip == INDEX_DATAFLASH_2) control_tasks_dataflash &= (unsigned int)(~TASK_ERASE_DATAFLASH_2);
      else
      {
        //Відбулася невизначена помилка, тому треба піти на перезавантаження
        total_error_sw_fixed(18);
      }

      //Зараз іде стирання, яке займає певний проміжок часу, тому помічаємо, що мікросхема є зайнятою і регістром статусу визначаємо, коли ця операція повністю закінчиться
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  case CODE_OPERATION_WRITE_PAGE_THROUGH_BUFFER:
    {
      if (index_chip == INDEX_DATAFLASH_1)
      {
      }
      else if (index_chip == INDEX_DATAFLASH_2)
      {
      }
      else
      {
        //Відбулася невизначена помилка, тому треба піти на перезавантаження
        total_error_sw_fixed(27);
      }
       
      //Зараз іде процес запису, який займає певний проміжок часу, тому помічаємо, що мікросхема є зайнятою і регістром статусу визначаємо, коли ця операція повністю закінчиться
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  case CODE_OPERATION_READ_HIGH_FREQ:
    {
      //Копіюємо прочитані дані у буфер
      unsigned char *point_buffer;
      unsigned int number_byte_copy_into_target_buffer;
//      unsigned int size_page;

      if (index_chip == INDEX_DATAFLASH_1)
      {
//        size_page = SIZE_PAGE_DATAFLASH_1;
//        unsigned int *point_part_reading;

        if (
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU )||
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB  )||
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_RS485)
           )   
        {
          if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU)
            point_buffer = (unsigned char *)(buffer_for_manu_read_record);
          else if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB)
            point_buffer = (unsigned char *)(buffer_for_USB_read_record_pr_err);
          else
            point_buffer = (unsigned char *)(buffer_for_RS485_read_record_pr_err);
          
          number_byte_copy_into_target_buffer = SIZE_ONE_RECORD_PR_ERR;
        }
        
        if (
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU ) ||
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB  ) ||  
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_RS485)  
           )
        {
          //По ідеї ця умова завжди має виконуватися
          for (unsigned int i = 0; i < number_byte_copy_into_target_buffer; i++ )
            *(point_buffer + i) = RxBuffer_SPI_DF[5 + i];
        }
        else
        {
          //Теоретично цього ніколи не мало б бути
          total_error_sw_fixed(46);
        }

        if (
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU ) ||
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB  ) ||  
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_RS485)  
           )
        {
          //Відбувалося зчитування реєстратора програмних подій
          //Знімаємо з черги запуск зчитування запису реєстратора програмних подій
          if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU)
          {
            control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU);

            /*Подаємо команду на обновлення екрану на LCD, хоч він десь за 
            час <= 1c обновиться автоматично, бо система меню чекає, поки
            буде зчитано запис
            */
            new_state_keyboard |= (1<<BIT_REWRITE);
          }
          else if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB)
            control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB);
          else
            control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485);
        }
      }
      else if (index_chip == INDEX_DATAFLASH_2)
      {
      }
      else
      {
        //Відбулася невизначена помилка, тому треба піти на перезавантаження
        total_error_sw_fixed(33);
      }
          
       
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  case CODE_OPERATION_READ_PAGE_INTO_BUFFER:
    {
      //Завершилося подача команди зчитування пам'яті програм у буфер мікросхеми DataFlash
      unsigned int *label_to_etap_writing;
      if (index_chip == INDEX_DATAFLASH_1) label_to_etap_writing = &etap_writing_pr_err_into_dataflash;
      else if (index_chip == INDEX_DATAFLASH_2){}
      else
      {
        //Відбулася невизначена помилка, тому треба піти на перезавантаження
        total_error_sw_fixed(28);
      }
      
      //Переводимо режим запису відповідного реєстратора у запис нових значень
      if (*label_to_etap_writing == ETAP_READ_MEMORY_INTO_BUFFER)
        *label_to_etap_writing = ETAP_HAVE_READ_MEMORY_INTO_BUFFER;
      else 
        *label_to_etap_writing = ETAP_ERROR_BEFALLEN;
      
      //Зараз іде процес зчитування у буфер, який займає певний проміжок часу, тому помічаємо, що мікросхема є зайнятою і регістром статусу визначаємо, коли ця операція повністю закінчиться
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  case CODE_OPERATION_WRITE_BUFFER:
    {
      //Завершилося передача даних у буфер мікросхеми DataFlash
      unsigned int *label_to_etap_writing;
      if (index_chip == INDEX_DATAFLASH_1) label_to_etap_writing = &etap_writing_pr_err_into_dataflash;
      else if (index_chip == INDEX_DATAFLASH_2){}
      else
      {
        //Відбулася невизначена помилка, тому треба піти на перезавантаження
        total_error_sw_fixed(29);
      }
      
      //Переводимо режим запису у запершення модифікації фуферу DataFlah
      if (*label_to_etap_writing == ETAP_MODIFY_AND_WRITE_BUFFER)
        *label_to_etap_writing = ETAP_MODIFIED_AND_WRITTEN_BUFFER;
      else 
        *label_to_etap_writing = ETAP_ERROR_BEFALLEN;
      
      //Помічаємо, що мікросхема є зайнятою і регістром статусу визначаємо, коли ця операція повністю закінчиться
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  case CODE_OPERATION_WRITE_BUFFER_INTO_MEMORY_WITH_ERASE:
    {
      if (index_chip == INDEX_DATAFLASH_1)
      {
        if (etap_writing_pr_err_into_dataflash == ETAP_WRITE_BUFFER_INTO_MEMORY)
        {
          //Виставляємо команду запису структури реєстратора програмних подій у EEPROM
          _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
          //Визначаємо нову адресу наступного запису, нову кількість записів і знімаємо сигналізацію, що зараз іде запис
          unsigned int temp_value_for_address = (info_rejestrator_pr_err.next_address + number_recods_writing_into_dataflash_now*SIZE_ONE_RECORD_PR_ERR);
          while (temp_value_for_address > MAX_ADDRESS_PR_ERR_AREA) temp_value_for_address = temp_value_for_address - SIZE_PR_ERR_AREA; 
          info_rejestrator_pr_err.next_address = temp_value_for_address;
          info_rejestrator_pr_err.saving_execution = 0;
          if ((info_rejestrator_pr_err.number_records + number_recods_writing_into_dataflash_now) <= MAX_NUMBER_RECORDS_INTO_PR_ERR) info_rejestrator_pr_err.number_records += number_recods_writing_into_dataflash_now;
          else info_rejestrator_pr_err.number_records = MAX_NUMBER_RECORDS_INTO_PR_ERR;
        
          //Змінюємо індекси буферу типу FIFO 
          tail_fifo_buffer_pr_err_records += number_recods_writing_into_dataflash_now;
          while(tail_fifo_buffer_pr_err_records >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) tail_fifo_buffer_pr_err_records -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
          number_recods_writing_into_dataflash_now = 0;
        
          if (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) != 0)
          {
            //Треба спробувати зняти повідомлення про переповнення буферу FIFO програмних подій
            _SET_BIT(clear_diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT);
          }

          //Знімаємо з черги запуск запису у реєстратор програмних подій
          etap_writing_pr_err_into_dataflash = ETAP_NONE;
          control_tasks_dataflash &= (unsigned int)(~TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH);
        }
        else 
          etap_writing_pr_err_into_dataflash = ETAP_ERROR_BEFALLEN;
      }
      else if (index_chip == INDEX_DATAFLASH_2)
      {
      }
      else
      {
        //Відбулася невизначена помилка, тому треба піти на перезавантаження
        total_error_sw_fixed(30);
      }
       
      //Зараз іде процес запису, який займає певний проміжок часу, тому помічаємо, що мікросхема є зайнятою і регістром статусу визначаємо, коли ця операція повністю закінчиться
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  default:
    {
      //По ідеї, сюди програма ніколи не мала б попадати. 
      //Якщо ми сюди попали, то треба виставити повідомлення, що не знаєм чи мікросхема є вільною і скидаємо всі опреації
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Основна функція обробки даних по управлінню DataFlash (обробка прийнятих даних)
/*****************************************************/
void main_function_for_dataflash_resp(int index_chip)
{
  if ((index_chip >= INDEX_DATAFLASH_1) && (index_chip <= INDEX_DATAFLASH_2))
  {
    if(driver_spi_df[index_chip].state_execution == TRANSACTION_EXECUTED_WAIT_ANALIZE)
    {
      //Виконуємо функцію обробки даних по завершення трансакції
      analize_received_data_dataflash(index_chip);
    }
  }
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(19);
  }
}
/*****************************************************/

/*****************************************************/
//Основна функція обробки даних по управлінню DataFlash (подача нової команди даних)
/*****************************************************/
void main_function_for_dataflash_req(int index_chip)
{
  if ((index_chip >= INDEX_DATAFLASH_1) && (index_chip <= INDEX_DATAFLASH_2))
  {
    if (driver_spi_df[index_chip].state_execution == TRANSACTION_EXECUTING_NONE)
    {
      //Якщо зараз не запущено ніякрої операції, то можна при потребі нову трансакцію
      if((dataflash_not_busy & (1 << index_chip)) == 0)
      {
        //Попередній раз прийшло повідомлення про те, що мікросхема є занятою, тому треба повторно зчитувати статус поки вона не зтане незанятою
        dataflash_status_read(index_chip);
      }
      else
      {
        //мікросхема зараз є вільною. тому можна запускати при необхідності нові трансакції
        unsigned int tasks_register;
        if (index_chip == INDEX_DATAFLASH_1) tasks_register = control_tasks_dataflash & 0xffff;
        else tasks_register = control_tasks_dataflash & 0xffff0000;
        
        if (tasks_register !=0)
        {
          //Зараз стоять у черзці операції, які треба виконати
          if (
              ((tasks_register & TASK_ERASE_DATAFLASH_1) !=0) ||
              ((tasks_register & TASK_ERASE_DATAFLASH_2) !=0)
             )
          {
            //Треба виконати команду повного стирання мікросхеми
            dataflash_erase(index_chip);
          }
          else if ((tasks_register & TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH) !=0 )
          {
            //Треба виконати команди: зчитування у буфер, зміна буферу, запис буферу зпопереднім його стиранням для реєстратора програмних подій
            if (etap_writing_pr_err_into_dataflash > ETAP_ERROR_BEFALLEN)
              etap_writing_pr_err_into_dataflash = ETAP_ERROR_BEFALLEN;
            
            switch (etap_writing_pr_err_into_dataflash)
            {
            case ETAP_NONE:
              {
                etap_writing_pr_err_into_dataflash = ETAP_READ_MEMORY_INTO_BUFFER;
                dataflash_mamory_page_into_buffer(index_chip);
                break;
              }
            case ETAP_HAVE_READ_MEMORY_INTO_BUFFER:
              {
                //Переходимо у режим запису даних у буфер
                etap_writing_pr_err_into_dataflash = ETAP_MODIFY_AND_WRITE_BUFFER;
                //Треба виконати команду запису даних реєстратора програмних подій у буфер мыкросхеми
                dataflash_mamory_write_buffer(index_chip);
                break;
              }
            case ETAP_MODIFIED_AND_WRITTEN_BUFFER:
              {
                //Переходимо у режим запису даних з буферу у пам'ять мікросхеми DataFlash
                etap_writing_pr_err_into_dataflash = ETAP_WRITE_BUFFER_INTO_MEMORY;
                //Треба виконати команду запису даних реєстратора програмних подій у буфер мыкросхеми
                dataflash_mamory_buffer_into_memory(index_chip);
                break;
              }
            default:
              {
                /*
                Сюди може зайти програма, якщо якась виникла помилка, 
                тоді знімаємо режим запису реєстратора програмних помилок і переводимо все у висхідний стан
                запис має початися з наступного разу  
                */
                etap_writing_pr_err_into_dataflash = ETAP_NONE;
                //Знімаємо з черги запуск запису у реєстратор програмних подій
                control_tasks_dataflash &= (unsigned int)(~TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH);
                
                break;
              }
            }   
          }   
          else if ((tasks_register & TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR) !=0)
          {
            //Треба виконати команду запису даних у сторінку через буфер з попереднім стиранням
            dataflash_mamory_page_program_through_buffer(index_chip);
          }
          else if (
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU ) !=0 ) ||
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB  ) !=0 ) ||
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485) !=0 )
                  )   
          {
            
            //Може виконуватися тільки одна операція для одної мікросхеми DataFlash(причому більi пріоритетна може переривати менш пріоритетну, якщо задача виконується у декілька етапів)
            //DataFlash1
            if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB) !=0 )
              what_we_are_reading_from_dataflash_1 = READING_PR_ERR_FOR_USB;//Читання для USB завжди має більший пріоритет порівняно з читанням для RS-485 і меню
            else if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485) !=0 )
              what_we_are_reading_from_dataflash_1 = READING_PR_ERR_FOR_RS485;//Читання для RS-485 завжди має більший пріоритет порівняно з читанням для меню
            else if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU) !=0 )
              what_we_are_reading_from_dataflash_1 = READING_PR_ERR_FOR_MENU;
            
            //Треба виконати команду читання даних
            dataflash_mamory_read(index_chip);
          }
        }
      }
    }
  }
  else
  {
    //Відбулася невизначена помилка, тому треба піти на перезавантаження
    total_error_sw_fixed(24);
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
