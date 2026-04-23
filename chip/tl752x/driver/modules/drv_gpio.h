/*******************************************************************************************************
 *
 * @file    drv_gpio.h
 *
 * @brief   This is the source file for tl752x
 *
 * @author  ExpanseMicro BSP Team
 * @par     Copyright (C) 2025-2035 Expanse Microelectronics (Shanghai) Co., Ltd
 *
 * @author  Telink Driver Group
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 * @date   2025
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tl_chip.h"

/** @defgroup gpio_port_define
  * @{
  */
#define GPIO_PORT_A 0
#define GPIO_PORT_B 1
#define GPIO_PORT_C 2

/** @defgroup gpio_pins_define
  * @{
  */
#define GPIO_PIN_(n) (1U << n)
#define GPIO_PIN_0   GPIO_PIN_(0)
#define GPIO_PIN_1   GPIO_PIN_(1)
#define GPIO_PIN_2   GPIO_PIN_(2)
#define GPIO_PIN_3   GPIO_PIN_(3)
#define GPIO_PIN_4   GPIO_PIN_(4)
#define GPIO_PIN_5   GPIO_PIN_(5)
#define GPIO_PIN_6   GPIO_PIN_(6)
#define GPIO_PIN_7   GPIO_PIN_(7)
#define GPIO_PIN_8   GPIO_PIN_(8)
#define GPIO_PIN_9   GPIO_PIN_(9)
#define GPIO_PIN_10  GPIO_PIN_(10)
#define GPIO_PIN_11  GPIO_PIN_(11)
#define GPIO_PIN_12  GPIO_PIN_(12)
#define GPIO_PIN_13  GPIO_PIN_(13)
#define GPIO_PIN_14  GPIO_PIN_(14)
#define GPIO_PIN_15  GPIO_PIN_(15)
#define GPIO_PIN_16  GPIO_PIN_(16)
#define GPIO_PIN_17  GPIO_PIN_(17)
#define GPIO_PIN_18  GPIO_PIN_(18)
#define GPIO_PIN_19  GPIO_PIN_(19)
#define GPIO_PIN_20  GPIO_PIN_(20)
#define GPIO_PIN_21  GPIO_PIN_(21)
#define GPIO_PIN_22  GPIO_PIN_(22)
#define GPIO_PIN_23  GPIO_PIN_(23)
#define GPIO_PIN_24  GPIO_PIN_(24)
#define GPIO_PIN_25  GPIO_PIN_(25)
#define GPIO_PIN_26  GPIO_PIN_(26)
#define GPIO_PIN_27  GPIO_PIN_(27)
#define GPIO_PIN_28  GPIO_PIN_(28)
#define GPIO_PIN_29  GPIO_PIN_(29)
#define GPIO_PIN_30  GPIO_PIN_(30)
#define GPIO_PIN_31  GPIO_PIN_(31)
#define GPIO_PIN_MAX 32

/** @defgroup gpio_mode_define
  * @{
  */
#define MODE_INPUT  0x0UL
#define MODE_OUTPUT 0x1UL
#define MODE_AF     0x2UL
#define MODE_FLOAT  0x3UL

/** @defgroup gpio_pull_define
  * @{
  */
#define GPIO_NOPULL   0x00000000U /*!< No Pull-up or Pull-down activation  */
#define GPIO_PULLDOWN 0x00000001U /*!< Pull-down activation                */
#define GPIO_PULLUP   0x00000002U /*!< Pull-up activation                  */

/** @defgroup gpio_electric_define
  * @{
  */
#define GPIO_ELECTRIC_2MA  0x00000000U /*!< 2mA */
#define GPIO_ELECTRIC_4MA  0x00000001U /*!< 4mA */
#define GPIO_ELECTRIC_8MA  0x00000002U /*!< 8mA  */
#define GPIO_ELECTRIC_12MA 0x00000003U /*!< 12mA  */

/** @defgroup gpio_alternate_function_selection
  * @{
  */
#define GPIO_ALTERNATE_DEFAULT 0
#define GPIO_ALTERNATE_FUNC_1  1
#define GPIO_ALTERNATE_FUNC_2  2
#define GPIO_ALTERNATE_FUNC_3  3
#define GPIO_ALTERNATE_FUNC_4  4
#define GPIO_ALTERNATE_FUNC_5  5
#define GPIO_ALTERNATE_FUNC_6  6
#define GPIO_ALTERNATE_FUNC_7  7
#define GPIO_ALTERNATE_FUNC_8  8
#define GPIO_ALTERNATE_FUNC_9  9
#define GPIO_ALTERNATE_FUNC_10 10
#define GPIO_ALTERNATE_FUNC_11 11
#define GPIO_ALTERNATE_FUNC_12 12
#define GPIO_ALTERNATE_FUNC_13 13
#define GPIO_ALTERNATE_FUNC_14 14
#define GPIO_ALTERNATE_FUNC_15 15

typedef enum {
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET = 1,
} gpio_pinstate_t;

typedef enum {
    GPIO_INTR_DISABLE = 0, /*!< GPIO interrupt type : disable edge                 */
    GPIO_INTR_POSEDGE,     /*!< GPIO interrupt type : rising edge                  */
    GPIO_INTR_NEGEDGE,     /*!< GPIO interrupt type : falling edge                 */
    GPIO_INTR_MAX,
} gpio_int_type_t;

typedef struct {
    uint32_t port;             /*!< Specifies the GPIO pins to be configured.
                           This parameter can be any value of @ref gpio_port_define */
    uint32_t pin;              /*!< Specifies the GPIO pins to be configured.
                           This parameter can be any value of @ref gpio_pins_define */
    uint32_t mode;             /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref gpio_mode_define */
    uint32_t pull;             /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref gpio_pull_define */
    uint32_t electric;         /*!< Specifies the speed for the selected pins.
                           This parameter can be a value of @ref gpio_electric_define */
    uint32_t alternate;        /*!< Peripheral to be connected to the selected pins.
                            This parameter can be a value of @ref gpio_alternate_function_selection */
    gpio_int_type_t intr_type; /*!< Specifies the interrupt type for the selected pins. This parameter can be a value of @ref gpio_int_type */
} gpio_init_t;

/**
  * @brief  Initializes the GPIO peripheral according to the specified parameters in the GPIO_Init.
  * @param  gpiox is GPIO
  * @param  gpio_init pointer to a gpio_init_t structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
extern void drv_gpio_init(gpio_init_t *gpio_init);

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  gpiox is GPIO
  * @param  gpio_port specifies the port to be written.can be GPIO_PORT_A,GPIO_PORT_B,GPIO_PORT_C
  * @param  gpio_pin specifies the port bit to be written.can be GPIO_PIN_0 - GPIO_PIN_31.
  * @param  pinstate specifies the value to be written to the selected bit.
  *          This parameter can be one of the GPIO_PinState enum values:
  *            @arg GPIO_PIN_RESET: to clear the port pin
  *            @arg GPIO_PIN_SET: to set the port pin
  * @retval None
  */
extern void drv_gpio_writepin(uint16_t gpio_port, uint32_t gpio_pin, gpio_pinstate_t pinstate);

/**
  * @brief  Reads the specified input port pin.
  * @param  gpiox is GPIO
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B,GPIO_PORT_C
  * @param  GPIO_Pin specifies the port bit to read. can be GPIO_PIN_0 - GPIO_PIN_31.
  * @retval The input port pin value.
  */
extern gpio_pinstate_t drv_gpio_readpin(uint16_t gpio_port, uint32_t gpio_pin);

/**
  * @brief  Reads the specified input port pin.
  * @param  gpiox is GPIO
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B,GPIO_PORT_C
  * @retval The input port value.
  */
extern uint32_t drv_gpio_readport(uint16_t gpio_port);

/**
 * @brief  gpio toggle in output mode.
 * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B,GPIO_PORT_C
 * @retval none.
 */
extern void drv_gpio_toggle(uint16_t gpio_port, uint32_t gpio_pin);

/**
  * @brief  GPIO interrupt setting
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B
  * @param  GPIO_Pin specifies the port bit to read. can be GPIO_PIN_0 - GPIO_PIN_31.
  * @retval None
  */
extern void drv_gpio_irq_set(uint16_t gpio_port, uint32_t gpio_pin, gpio_int_type_t type);

/**
  * @brief  GPIO interrupt read
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B
  * @retval None
  */
extern uint32_t drv_gpio_irq_read(uint16_t gpio_port);

/**
  * @brief  GPIO interrupt clear
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B
  * @param  GPIO_Pin specifies the port bit to read. can be GPIO_PIN_0 - GPIO_PIN_31.
  * @retval None
  */
extern void drv_gpio_irq_clear(uint16_t gpio_port, uint32_t gpio_pin);

/**
  * @brief  GPIO pull set
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B,GPIO_PORT_C
  * @param  GPIO_Pin specifies the port bit to read. can be GPIO_PIN_0 - GPIO_PIN_31.
  * @param  pull @defgroup gpio_pull_define
  * @retval None
  */
extern void drv_gpio_set_pull(uint16_t gpio_port, uint32_t gpio_pin, uint32_t pull);

/**
  * @brief  GPIO mode set
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B,GPIO_PORT_C
  * @param  GPIO_Pin specifies the port bit to read. can be GPIO_PIN_0 - GPIO_PIN_31.
  * @param  dir  ,MODE_INPUT or MODE_OUTPUT
  * @retval None
  */
extern void drv_gpio_set_dir(uint16_t gpio_port, uint32_t gpio_pin, uint32_t dir);

/**
  * @brief  GPIO ie set
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B,GPIO_PORT_C
  * @param  GPIO_Pin specifies the port bit to read. can be GPIO_PIN_0 - GPIO_PIN_31.
  * @param  status ,DRV_SET(ie connect) or DRV_RESET(ie disconnect)
  * @retval None
  */
extern void drv_gpio_set_ie(uint16_t gpio_port, uint32_t gpio_pin, drv_flag_status_t status);

/**
  * @brief  GPIO output electric set
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B,GPIO_PORT_C
  * @param  GPIO_Pin specifies the port bit to read. can be GPIO_PIN_0 - GPIO_PIN_31.
  * @param  electric @defgroup gpio_electric_define
  * @retval None
  */
extern void drv_gpio_set_output_electric(uint16_t gpio_port, uint32_t gpio_pin, uint32_t electric);

/**
  * @brief  GPIO alternate set
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B,GPIO_PORT_C
  * @param  GPIO_Pin specifies the port bit to read. can be GPIO_PIN_0 - GPIO_PIN_31.
  * @param  alternate @defgroup gpio_alternate_function_selection
  * @retval None
  */
extern void drv_gpio_set_alternate(uint16_t gpio_port, uint32_t gpio_pin, uint32_t alternate);
/**
 * @brief  Sets or clears the selected data port bit.
 * @param  gpio_pin specifies the port bit to be written.can be GPIO_PIN_0 - GPIO_PIN_13.
 * @param  pinstate specifies the value to be written to the selected bit.
 *          This parameter can be one of the GPIO_PinState enum values:
 *            @arg GPIO_PIN_RESET: to clear the port pin
 *            @arg GPIO_PIN_SET: to set the port pin
 * @retval None
 */
extern void drv_gpio_retention(uint32_t gpio_pin, gpio_pinstate_t pinstate);

/**
 * @brief  GPIO shutdown configuration
 * @param  None
 * @retval None
 */
extern void drv_gpio_shutdown(void);
#ifdef __cplusplus
}
#endif

#endif
