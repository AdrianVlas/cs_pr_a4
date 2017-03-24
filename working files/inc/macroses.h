#ifndef __MACROSES__
#define __MACROSES__

#define _CHECK_SET_BIT(_array, _number_bit)                                     \
    (_array[_number_bit >> 5] & ( (unsigned int)( 1 << (_number_bit & 0x1f)) ) )                           

#define _SET_BIT(_array, _number_bit)                                           \
      _array[_number_bit >> 5] |= (unsigned int)(1 << (_number_bit & 0x1f))

#define _CLEAR_BIT(_array, _number_bit)                                         \
      _array[_number_bit >> 5] &= (unsigned int)(~(1 << (_number_bit & 0x1f)))

#define _DEVICE_REGISTER(addr,offset)   *(unsigned short int *)(addr + (offset<<1) )

#define _NUMBER_CHANGES_INTO_UNSIGNED_INT_ARRAY(_array1, _array2, _number_items, _rezultat) \
        {                                                                        \
          _rezultat = 0;                                                         \
          for(unsigned int _i = 0; _i < _number_items; _i++)                     \
          {                                                                      \
            unsigned int _temp_value = _array1[_i] ^ _array2[_i];                \
            for(unsigned int _j = 0; _j < 32; _j++)                              \
            {                                                                    \
              if ((_temp_value & (1 << _j)) != 0) _rezultat++;                   \
            }                                                                    \
          }                                                                      \
        }

#define _CONVERT_SIGNAL_TO_GMM(__input_array, __output_array, __input_index_signal, __output_index_signal)                           \
          __output_array[__output_index_signal >> 4] |=                                                                             \
            ((__input_array[__input_index_signal >> 5] >> (__input_index_signal & 0x1f)) & 0x1) << (__output_index_signal & 0xf)  

#define _DELAY_ABOUT_40NS()\
        {                  \
           word_SRAM1 = 1; \
        }

#define _DELAY_ABOUT_10NS()\
        {                  \
           word_SRAM1 = 1; \
        }

//#define _DELAY_ABOUT_40NS()  \
//        {                    \
//          __no_operation();  \
//          __no_operation();  \
//          __no_operation();  \
//          __no_operation();  \
//          __no_operation();  \
//        }
//
//#define _DELAY_ABOUT_10NS()  \
//        {                    \
//          __no_operation();  \
//          __no_operation();  \
//        }

#define _CLEAR_STATE(_output, _output_bit) _output &= (unsigned int)(~(1 << _output_bit))

#define _SET_STATE(_output, _output_bit) _output |= (unsigned int)(1 << _output_bit)

#define _GET_OUTPUT_STATE(_input, _input_bit) ((_input & ((unsigned int)(1 << _input_bit))) != 0)

#define DIV_TO_HIGHER(_N, _M) ((_N / _M) + ((_N % _M) != 0))


#define _INVERTOR(                                         \
                  _input , _input_bit,                     \
                  _output, _output_bit                     \
                 )                                         \
        {                                                  \
          if (_input & (unsigned int)(1 << _input_bit))    \
            _output &= (unsigned int)(~(1 << _output_bit));\
          else                                             \
            _output |= (unsigned int)(1 << _output_bit);   \
        }

#define _AND2(                                                                    \
              _input_1, _input_bit_1,                                             \
              _input_2, _input_bit_2,                                             \
              _output , _output_bit                                               \
             )                                                                    \
        {                                                                         \
          if(                                                                     \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) &&                    \
             (_input_2 & (unsigned int)(1 << _input_bit_2))                       \
            )                                                                     \
            _output |= (unsigned int)(1 << _output_bit);                          \
          else                                                                    \
            _output &= (unsigned int)(~(1 << _output_bit));                       \
        }

#define _AND3(                                                                    \
              _input_1, _input_bit_1,                                             \
              _input_2, _input_bit_2,                                             \
              _input_3, _input_bit_3,                                             \
              _output , _output_bit                                               \
             )                                                                    \
        {                                                                         \
          if(                                                                     \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) &&                    \
             (_input_2 & (unsigned int)(1 << _input_bit_2)) &&                    \
             (_input_3 & (unsigned int)(1 << _input_bit_3))                       \
            )                                                                     \
            _output |= (unsigned int)(1 << _output_bit);                          \
          else                                                                    \
            _output &= (unsigned int)(~(1 << _output_bit));                       \
        }

#define _AND4(                                                                    \
              _input_1, _input_bit_1,                                             \
              _input_2, _input_bit_2,                                             \
              _input_3, _input_bit_3,                                             \
              _input_4, _input_bit_4,                                             \
              _output , _output_bit                                               \
             )                                                                    \
        {                                                                         \
          if(                                                                     \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) &&                    \
             (_input_2 & (unsigned int)(1 << _input_bit_2)) &&                    \
             (_input_3 & (unsigned int)(1 << _input_bit_3)) &&                    \
             (_input_4 & (unsigned int)(1 << _input_bit_4))                       \
            )                                                                     \
            _output |= (unsigned int)(1 << _output_bit);                          \
          else                                                                    \
            _output &= (unsigned int)(~(1 << _output_bit));                       \
        }

#define _AND5(                                                                    \
              _input_1, _input_bit_1,                                             \
              _input_2, _input_bit_2,                                             \
              _input_3, _input_bit_3,                                             \
              _input_4, _input_bit_4,                                             \
              _input_5, _input_bit_5,                                             \
              _output , _output_bit                                               \
             )                                                                    \
        {                                                                         \
          if(                                                                     \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) &&                    \
             (_input_2 & (unsigned int)(1 << _input_bit_2)) &&                    \
             (_input_3 & (unsigned int)(1 << _input_bit_3)) &&                    \
             (_input_4 & (unsigned int)(1 << _input_bit_4)) &&                    \
             (_input_5 & (unsigned int)(1 << _input_bit_5))                       \
            )                                                                     \
            _output |= (unsigned int)(1 << _output_bit);                          \
          else                                                                    \
            _output &= (unsigned int)(~(1 << _output_bit));                       \
        }

#define _AND2_INVERTOR(                                                           \
                       _input_1, _input_bit_1,                                    \
                       _input_2, _input_bit_2,                                    \
                       _output , _output_bit                                      \
                      )                                                           \
        {                                                                         \
          if(                                                                     \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) &&                    \
             (_input_2 & (unsigned int)(1 << _input_bit_2))                       \
            )                                                                     \
            _output &= (unsigned int)(~(1 << _output_bit));                       \
          else                                                                    \
            _output |= (unsigned int)(1 << _output_bit);                          \
        }

#define _AND3_INVERTOR(                                                           \
                       _input_1, _input_bit_1,                                    \
                       _input_2, _input_bit_2,                                    \
                       _input_3, _input_bit_3,                                    \
                       _output , _output_bit                                      \
                      )                                                           \
        {                                                                         \
          if(                                                                     \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) &&                    \
             (_input_2 & (unsigned int)(1 << _input_bit_2)) &&                    \
             (_input_3 & (unsigned int)(1 << _input_bit_3))                       \
            )                                                                     \
            _output &= (unsigned int)(~(1 << _output_bit));                       \
          else                                                                    \
            _output |= (unsigned int)(1 << _output_bit);                          \
        }

#define _OR2(                                                  \
             _input_1, _input_bit_1,                           \
             _input_2, _input_bit_2,                           \
             _output , _output_bit                             \
            )                                                  \
        {                                                      \
          if(                                                  \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) || \
             (_input_2 & (unsigned int)(1 << _input_bit_2))    \
            )                                                  \
            _output |= (unsigned int)(1 << _output_bit);       \
          else                                                 \
            _output &= (unsigned int)(~(1 << _output_bit));    \
        }

#define _OR2_INVERTOR(                                         \
                      _input_1, _input_bit_1,                  \
                      _input_2, _input_bit_2,                  \
                      _output , _output_bit                    \
                     )                                         \
        {                                                      \
          if(                                                  \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) || \
             (_input_2 & (unsigned int)(1 << _input_bit_2))    \
            )                                                  \
            _output &= (unsigned int)(~(1 << _output_bit));    \
          else                                                 \
            _output |= (unsigned int)(1 << _output_bit);       \
        }

#define _OR3(                                                  \
             _input_1, _input_bit_1,                           \
             _input_2, _input_bit_2,                           \
             _input_3, _input_bit_3,                           \
             _output , _output_bit                             \
            )                                                  \
        {                                                      \
          if(                                                  \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) || \
             (_input_2 & (unsigned int)(1 << _input_bit_2)) || \
             (_input_3 & (unsigned int)(1 << _input_bit_3))    \
            )                                                  \
            _output |= (unsigned int)(1 << _output_bit);       \
          else                                                 \
            _output &= (unsigned int)(~(1 << _output_bit));    \
        }

#define _OR3_INVERTOR(                                         \
             _input_1, _input_bit_1,                           \
             _input_2, _input_bit_2,                           \
             _input_3, _input_bit_3,                           \
             _output , _output_bit                             \
            )                                                  \
        {                                                      \
          if(                                                  \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) || \
             (_input_2 & (unsigned int)(1 << _input_bit_2)) || \
             (_input_3 & (unsigned int)(1 << _input_bit_3))    \
            )                                                  \
            _output &= (unsigned int)(~(1 << _output_bit));    \
          else                                                 \
            _output |= (unsigned int)(1 << _output_bit);       \
        }

#define _OR4(                                                  \
             _input_1, _input_bit_1,                           \
             _input_2, _input_bit_2,                           \
             _input_3, _input_bit_3,                           \
             _input_4, _input_bit_4,                           \
             _output , _output_bit                             \
            )                                                  \
        {                                                      \
          if(                                                  \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) || \
             (_input_2 & (unsigned int)(1 << _input_bit_2)) || \
             (_input_3 & (unsigned int)(1 << _input_bit_3)) || \
             (_input_4 & (unsigned int)(1 << _input_bit_4))    \
            )                                                  \
            _output |= (unsigned int)(1 << _output_bit);       \
          else                                                 \
            _output &= (unsigned int)(~(1 << _output_bit));    \
        }

#define _OR4_INVERTOR(                                         \
             _input_1, _input_bit_1,                           \
             _input_2, _input_bit_2,                           \
             _input_3, _input_bit_3,                           \
             _input_4, _input_bit_4,                           \
             _output , _output_bit                             \
            )                                                  \
        {                                                      \
          if(                                                  \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) || \
             (_input_2 & (unsigned int)(1 << _input_bit_2)) || \
             (_input_3 & (unsigned int)(1 << _input_bit_3)) || \
             (_input_4 & (unsigned int)(1 << _input_bit_4))    \
            )                                                  \
            _output &= (unsigned int)(~(1 << _output_bit));    \
          else                                                 \
            _output |= (unsigned int)(1 << _output_bit);       \
        }

#define _OR5(                                                  \
             _input_1, _input_bit_1,                           \
             _input_2, _input_bit_2,                           \
             _input_3, _input_bit_3,                           \
             _input_4, _input_bit_4,                           \
             _input_5, _input_bit_5,                           \
             _output , _output_bit                             \
            )                                                  \
        {                                                      \
          if(                                                  \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) || \
             (_input_2 & (unsigned int)(1 << _input_bit_2)) || \
             (_input_3 & (unsigned int)(1 << _input_bit_3)) || \
             (_input_4 & (unsigned int)(1 << _input_bit_4)) || \
             (_input_5 & (unsigned int)(1 << _input_bit_5))    \
            )                                                  \
            _output |= (unsigned int)(1 << _output_bit);       \
          else                                                 \
            _output &= (unsigned int)(~(1 << _output_bit));    \
        }

#define _OR6(                                                  \
             _input_1, _input_bit_1,                           \
             _input_2, _input_bit_2,                           \
             _input_3, _input_bit_3,                           \
             _input_4, _input_bit_4,                           \
             _input_5, _input_bit_5,                           \
             _input_6, _input_bit_6,                           \
             _output , _output_bit                             \
            )                                                  \
        {                                                      \
          if(                                                  \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) || \
             (_input_2 & (unsigned int)(1 << _input_bit_2)) || \
             (_input_3 & (unsigned int)(1 << _input_bit_3)) || \
             (_input_4 & (unsigned int)(1 << _input_bit_4)) || \
             (_input_5 & (unsigned int)(1 << _input_bit_5)) || \
             (_input_6 & (unsigned int)(1 << _input_bit_6))    \
            )                                                  \
            _output |= (unsigned int)(1 << _output_bit);       \
          else                                                 \
            _output &= (unsigned int)(~(1 << _output_bit));    \
        }

#define _OR8(                                                  \
             _input_1, _input_bit_1,                           \
             _input_2, _input_bit_2,                           \
             _input_3, _input_bit_3,                           \
             _input_4, _input_bit_4,                           \
             _input_5, _input_bit_5,                           \
             _input_6, _input_bit_6,                           \
             _input_7, _input_bit_7,                           \
             _input_8, _input_bit_8,                           \
             _output , _output_bit                             \
            )                                                  \
        {                                                      \
          if(                                                  \
             (_input_1 & (unsigned int)(1 << _input_bit_1)) || \
             (_input_2 & (unsigned int)(1 << _input_bit_2)) || \
             (_input_3 & (unsigned int)(1 << _input_bit_3)) || \
             (_input_4 & (unsigned int)(1 << _input_bit_4)) || \
             (_input_5 & (unsigned int)(1 << _input_bit_5)) || \
             (_input_6 & (unsigned int)(1 << _input_bit_6)) || \
             (_input_7 & (unsigned int)(1 << _input_bit_7)) || \
             (_input_8 & (unsigned int)(1 << _input_bit_8))    \
            )                                                  \
            _output |= (unsigned int)(1 << _output_bit);       \
          else                                                 \
            _output &= (unsigned int)(~(1 << _output_bit));    \
        }

#define _XOR_INVERTOR(                                                  \
                      _input_1, _input_bit_1,                           \
                      _input_2, _input_bit_2,                           \
                      _output , _output_bit                             \
                     )                                                  \
        {                                                               \
          if(                                                           \
             ((_input_1 & ((unsigned int)(1 << _input_bit_1))) != 0) ^  \
             ((_input_2 & ((unsigned int)(1 << _input_bit_2))) != 0)    \
            )                                                           \
            _output &= (unsigned int)(~(1 << _output_bit));             \
          else                                                          \
            _output |= (unsigned int)(1 << _output_bit);                \
        }

        
#define _TIMER_T_0_LOCK(                                                \
                   _index_timer,                                        \
                   _max_count,                                          \
                   _input, _input_bit,                                  \
                   _output, _output_bit                                 \
                  )                                                     \
        {                                                               \
          if ((_input & (unsigned int)(1 << _input_bit)) == 0)          \
            global_timers[_index_timer] = -1;                           \
          else                                                          \
          {                                                             \
            if (global_timers[_index_timer] < 0)                        \
              global_timers[_index_timer] = 0;                          \
          }                                                             \
                                                                        \
          if(global_timers[_index_timer] >= _max_count)                 \
            _output |= (unsigned int)(1 << _output_bit);                \
          else                                                          \
          {                                                             \
            if (global_timers[_index_timer] == -1)                      \
              _output &= (unsigned int)(~(1 << _output_bit));           \
          }                                                             \
        }
        
#define _TIMER_T_0(                                                     \
                   _index_timer,                                        \
                   _max_count,                                          \
                   _input, _input_bit,                                  \
                   _output, _output_bit                                 \
                  )                                                     \
        {                                                               \
          if ((_input & (unsigned int)(1 << _input_bit)) == 0)          \
            global_timers[_index_timer] = -1;                           \
          else                                                          \
          {                                                             \
            if (global_timers[_index_timer] < 0)                        \
              global_timers[_index_timer] = 0;                          \
          }                                                             \
                                                                        \
          if(global_timers[_index_timer] >= _max_count)                 \
            _output |= (unsigned int)(1 << _output_bit);                \
          else                                                          \
            _output &= (unsigned int)(~(1 << _output_bit));             \
        }

#define _TIMER_0_T(                                                     \
                   _index_timer,                                        \
                   _max_count,                                          \
                   _input, _input_bit,                                  \
                   _output, _output_bit                                 \
                  )                                                     \
        {                                                               \
          if ((_input & (unsigned int)(1 << _input_bit)) != 0)          \
          {                                                             \
            global_timers[_index_timer] = 0;                            \
          }                                                             \
          else                                                          \
          {                                                             \
            if (global_timers[_index_timer] >= _max_count)              \
              global_timers[_index_timer] = -1;                         \
          }                                                             \
                                                                        \
          if(global_timers[_index_timer] >= 0)                          \
            _output |= (unsigned int)(1 << _output_bit);                \
          else                                                          \
            _output &= (unsigned int)(~(1 << _output_bit));             \
        }

#define _TIMER_IMPULSE(                                                 \
                       _index_timer,                                    \
                       _max_count,                                      \
                       _input, _input_bit,                              \
                       _INPUT, _INPUT_BIT,                              \
                       _OUTPUT, _OUTPUT_BIT                             \
                      )                                                 \
        {                                                               \
          unsigned int _c, _C;                                          \
                                                                        \
          _c =  _GET_OUTPUT_STATE(_input, _input_bit);                  \
          _C =  _GET_OUTPUT_STATE(_INPUT, _INPUT_BIT);                  \
                                                                        \
          if (_c ^ _C)                                                  \
          {                                                             \
            if (_C) _input |= (unsigned int)(1 << _input_bit);          \
            else _input &= (unsigned int)(~(1 << _input_bit));          \
                                                                        \
            if (_C == 1) global_timers[_index_timer] = 0;               \
          }                                                             \
                                                                        \
          if (global_timers[_index_timer] >= _max_count)                \
            global_timers[_index_timer] = -1;                           \
                                                                        \
          if(global_timers[_index_timer] >= 0)                          \
            _OUTPUT |= (unsigned int)(1 << _OUTPUT_BIT);                \
          else                                                          \
            _OUTPUT &= (unsigned int)(~(1 << _OUTPUT_BIT));             \
        }

#define _D_TRIGGER(                                                \
                   _D,                                             \
                   _SET,                                           \
                   _CLR,                                           \
                   _synchro, _synchro_bit,                         \
                   _SYNCHRO, _SYNCHRO_BIT,                         \
                   _output , _output_bit                           \
                  )                                                \
      {                                                            \
        unsigned int _c, _C, _changing;                            \
                                                                   \
        _c =  _GET_OUTPUT_STATE(_synchro, _synchro_bit);           \
        _C =  _GET_OUTPUT_STATE(_SYNCHRO, _SYNCHRO_BIT);           \
                                                                   \
        if (_changing = (_c ^ _C))                                 \
        {                                                          \
          if (_C) _synchro |= (unsigned int)(1 << _synchro_bit);   \
          else _synchro &= (unsigned int)(~(1 << _synchro_bit));   \
        }                                                          \
                                                                   \
        if (_CLR) _output &= (unsigned int)(~(1 << _output_bit));  \
        else if (_SET) _output |= (unsigned int)(1 << _output_bit);\
        else                                                       \
        {                                                          \
          if (_changing && _C)                                     \
          {                                                        \
            if (_D) _output |= (unsigned int)(1 << _output_bit);   \
            else _output &= (unsigned int)(~(1 << _output_bit));   \
          }                                                        \
        }                                                          \
      }

#define _COUNTER(                                                               \
                   _R,                                                          \
                   _input, _input_bit,                                          \
                   _INPUT, _INPUT_BIT,                                          \
                   _count,                                                      \
                   _max_count,                                                  \
                   _output , _output_bit                                        \
                  )                                                             \
      {                                                                         \
        unsigned int _c, _C;                                                    \
                                                                                \
        _c =  _GET_OUTPUT_STATE(_input, _input_bit);                            \
        _C =  _GET_OUTPUT_STATE(_INPUT, _INPUT_BIT);                            \
                                                                                \
        if (_c ^ _C)                                                            \
        {                                                                       \
          if (_C) _input |= (unsigned int)(1 << _input_bit);                    \
          else _input &= (unsigned int)(~(1 << _input_bit));                    \
        }                                                                       \
                                                                                \
        if (_R/* || (_max_count == 0)*/)                                        \
        {                                                                       \
          _count = 0;                                                           \
          _output &= (unsigned int)(~(1 << _output_bit));                       \
        }                                                                       \
        else                                                                    \
        {                                                                       \
          if ((_c == 1) && (_C == 0) && (_count < _max_count)) _count++;        \
                                                                                \
          if (_count >= _max_count) _output |= (unsigned int)(1 << _output_bit);\
          else _output &= (unsigned int)(~(1 << _output_bit));                  \
        }                                                                       \
      }

#endif 


