/**
  ******************************************************************************
  * @file    xpd_rcc_pc.h
  * @author  Benedek Kupper
  * @version V0.1
  * @date    2016-01-16
  * @brief   STM32 eXtensible Peripheral Drivers RCC Peripheral Clocks Module
  *
  *  This file is part of STM32_XPD.
  *
  *  STM32_XPD is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  STM32_XPD is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with STM32_XPD.  If not, see <http://www.gnu.org/licenses/>.
  */

#if   defined(XPD_ADC_API)

/** @addtogroup ADC
 * @{ */

/** @defgroup ADC_Clock_Source ADC Clock Source
 * @{ */

/** @defgroup ADC_Clock_Source_Exported_Types ADC Clock Source Exported Types
 * @{ */

/** @brief ADC clock source types */
#if defined(RCC_CFGR2_ADC1PRES) || defined(RCC_CFGR2_ADCPRE12)
typedef enum
{
    ADC_CLOCKSOURCE_HCLK          = 0x01, /*!< HCLK clock source */
    ADC_CLOCKSOURCE_HCLK_DIV2     = 0x02, /*!< HCLK / 2 clock source */
    ADC_CLOCKSOURCE_HCLK_DIV4     = 0x03, /*!< HCLK / 4 clock source */
    ADC_CLOCKSOURCE_PLLCLK        = 0x10, /*!< PLLCLK clock source */
    ADC_CLOCKSOURCE_PLLCLK_DIV2   = 0x11, /*!< PLLCLK / 2 clock source */
    ADC_CLOCKSOURCE_PLLCLK_DIV4   = 0x12, /*!< PLLCLK / 4 clock source */
    ADC_CLOCKSOURCE_PLLCLK_DIV6   = 0x13, /*!< PLLCLK / 6 clock source */
    ADC_CLOCKSOURCE_PLLCLK_DIV8   = 0x14, /*!< PLLCLK / 8 clock source */
    ADC_CLOCKSOURCE_PLLCLK_DIV10  = 0x15, /*!< PLLCLK / 10 clock source */
    ADC_CLOCKSOURCE_PLLCLK_DIV12  = 0x16, /*!< PLLCLK / 12 clock source */
    ADC_CLOCKSOURCE_PLLCLK_DIV16  = 0x17, /*!< PLLCLK / 16 clock source */
    ADC_CLOCKSOURCE_PLLCLK_DIV32  = 0x18, /*!< PLLCLK / 32 clock source */
    ADC_CLOCKSOURCE_PLLCLK_DIV64  = 0x19, /*!< PLLCLK / 64 clock source */
    ADC_CLOCKSOURCE_PLLCLK_DIV128 = 0x1A, /*!< PLLCLK / 128 clock source */
    ADC_CLOCKSOURCE_PLLCLK_DIV256 = 0x1B  /*!< PLLCLK / 256 clock source */
}ADC_ClockSourceType;
#elif defined(RCC_CFGR_ADCPRE)
typedef enum
{
    ADC_CLOCKSOURCE_PCLK2_DIV2 = 0, /*!< PCLK2 / 2 clock source */
    ADC_CLOCKSOURCE_PCLK2_DIV4 = 1, /*!< PCLK2 / 4 clock source */
    ADC_CLOCKSOURCE_PCLK2_DIV6 = 2, /*!< PCLK2 / 6 clock source */
    ADC_CLOCKSOURCE_PCLK2_DIV8 = 3  /*!< PCLK2 / 8 clock source */
}ADC_ClockSourceType;
#endif
/** @} */

/** @addtogroup ADC_Clock_Source_Exported_Functions
 * @{ */
void            XPD_ADC_ClockConfig         (ADC_ClockSourceType ClockSource);
uint32_t        XPD_ADC_GetClockFreq        (void);

#if defined(RCC_CFGR2_ADCPRE12) && defined(RCC_CFGR2_ADCPRE34)
void            XPD_ADC12_ClockConfig       (ADC_ClockSourceType ClockSource);
uint32_t        XPD_ADC12_GetClockFreq      (void);

void            XPD_ADC34_ClockConfig       (ADC_ClockSourceType ClockSource);
uint32_t        XPD_ADC34_GetClockFreq      (void);
#endif
/** @} */

/** @} */

/** @} */

#elif defined(XPD_CEC_API)

/** @addtogroup CEC
 * @{ */

/** @defgroup CEC_Clock_Source CEC Clock Source
 * @{ */

/** @defgroup CEC_Clock_Source_Exported_Types CEC Clock Source Exported Types
 * @{ */

/** @brief CEC clock source types */
typedef enum
{
    CEC_CLOCKSOURCE_HSI_DIV244 = 0, /*!< HSI / 244 clock source */
#ifdef LSE_VALUE
    CEC_CLOCKSOURCE_LSE        = 1  /*!< LSE clock source */
#endif
}CEC_ClockSourceType;
/** @} */

/** @addtogroup CEC_Clock_Source_Exported_Functions
 * @{ */
void            XPD_CEC_ClockConfig         (CEC_ClockSourceType ClockSource);
uint32_t        XPD_CEC_GetClockFreq        (void);
/** @} */

/** @} */

/** @} */

#elif defined(XPD_I2C_API)

/** @addtogroup I2C
 * @{ */

/** @defgroup I2C_Clock_Source I2C Clock Source
 * @{ */

/** @defgroup I2C_Clock_Source_Exported_Types I2C Clock Source Exported Types
 * @{ */

/** @brief I2C clock source types */
typedef enum
{
    I2C_CLOCKSOURCE_HSI     = 0, /*!< HSI clock source */
    I2C_CLOCKSOURCE_SYSCLK  = 1, /*!< SYSCLK clock source */
}I2C_ClockSourceType;
/** @} */

/** @addtogroup I2C_Clock_Source_Exported_Functions
 * @{ */
void            XPD_I2C_ClockConfig         (I2C_HandleType * hi2c, I2C_ClockSourceType ClockSource);
uint32_t        XPD_I2C_GetClockFreq        (I2C_HandleType * hi2c);
/** @} */

/** @} */

/** @} */

#elif defined(XPD_I2S_API)

/** @addtogroup I2S
 * @{ */

/** @defgroup I2S_Clock_Source I2S Clock Source
 * @{ */

#if defined(RCC_CFGR_I2SSRC)
/** @defgroup I2S_Clock_Source_Exported_Types I2S Clock Source Exported Types
 * @{ */

/** @brief I2S clock source types */
typedef enum
{
    I2S_CLOCKSOURCE_SYSCLK = 0, /*!< SYSCLK clock source */
#ifdef EXTERNAL_CLOCK_VALUE
    I2S_CLOCKSOURCE_EXT    = 1, /*!< external clock source */
#endif
}I2S_ClockSourceType;
/** @} */
#endif

/** @addtogroup I2S_Clock_Source_Exported_Functions
 * @{ */
#if defined(RCC_CFGR_I2SSRC)
void            XPD_I2S_ClockConfig         (I2S_ClockSourceType ClockSource);
#endif
uint32_t        XPD_I2S_GetClockFreq        (void);
/** @} */

/** @} */

/** @} */

#elif defined(XPD_RTC_API)
/** @addtogroup RTC
 * @{ */

/** @defgroup RTC_Clock_Source RTC Clock Source
 * @{ */

/** @defgroup RTC_Clock_Source_Exported_Types RTC Clock Source Exported Types
 * @{ */

/** @brief RTC clock source types */
typedef enum
{
    RTC_CLOCKSOURCE_NONE      = 0, /*!< no clock source */
#ifdef LSE_VALUE
    RTC_CLOCKSOURCE_LSE       = 1, /*!< LSE clock source */
#endif
    RTC_CLOCKSOURCE_LSI       = 2, /*!< LSI clock source */
#ifdef HSE_VALUE
    RTC_CLOCKSOURCE_HSE_DIV32 = 3, /*!< HSE / 32 clock source */
#endif
}RTC_ClockSourceType;
/** @} */

/** @addtogroup RTC_Clock_Source_Exported_Functions
 * @{ */
XPD_ReturnType  XPD_RTC_ClockConfig         (RTC_ClockSourceType ClockSource);
uint32_t        XPD_RTC_GetClockFreq        (void);
/** @} */

/** @} */

/** @} */

#elif defined(XPD_SDADC_API)
/** @addtogroup SDADC
 * @{ */

/** @defgroup SDADC_Clock_Source SDADC Clock Source
 * @{ */

/** @defgroup SDADC_Clock_Source_Exported_Types SDADC Clock Source Exported Types
 * @{ */

/** @brief SDADC clock source types */
typedef enum
{
    SDADC_CLOCKSOURCE_SYSCLK       = 0x00, /*!< SYSCLK clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV2  = 0x10, /*!< SYSCLK / 2 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV4  = 0x11, /*!< SYSCLK / 4 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV6  = 0x12, /*!< SYSCLK / 6 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV8  = 0x13, /*!< SYSCLK / 8 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV10 = 0x14, /*!< SYSCLK / 10 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV12 = 0x15, /*!< SYSCLK / 12 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV14 = 0x16, /*!< SYSCLK / 14 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV16 = 0x17, /*!< SYSCLK / 16 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV20 = 0x18, /*!< SYSCLK / 20 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV24 = 0x19, /*!< SYSCLK / 24 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV28 = 0x1A, /*!< SYSCLK / 28 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV32 = 0x1B, /*!< SYSCLK / 32 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV36 = 0x1C, /*!< SYSCLK / 36 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV40 = 0x1D, /*!< SYSCLK / 40 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV44 = 0x1E, /*!< SYSCLK / 44 clock source */
    SDADC_CLOCKSOURCE_SYSCLK_DIV48 = 0x1F, /*!< SYSCLK / 48 clock source */
}SDADC_ClockSourceType;
/** @} */

/** @addtogroup SDADC_Clock_Source_Exported_Functions
 * @{ */
void            XPD_SDADC_ClockConfig       (SDADC_ClockSourceType ClockSource);
uint32_t        XPD_SDADC_GetClockFreq      (void);
/** @} */

/** @} */

/** @} */

#elif defined(XPD_TIM_API)

/** @addtogroup TIM
 * @{ */

/** @defgroup TIM_Clock_Source TIM Clock Source
 * @{ */

/** @defgroup TIM_Clock_Source_Exported_Types TIM Clock Source Exported Types
 * @{ */

/** @brief TIM clock source types */
typedef enum
{
    TIM_CLOCKSOURCE_PCLKx        = 0, /*!< default clock source */
    TIM_CLOCKSOURCE_PLLCLK_MUL2  = 1, /*!< clock source is PLL clock * 2 */
}TIM_ClockSourceType;
/** @} */

/** @addtogroup TIM_Clock_Source_Exported_Functions
 * @{ */
void            XPD_TIM_ClockConfig         (TIM_HandleType * htim, TIM_ClockSourceType ClockSource);
uint32_t        XPD_TIM_GetClockFreq        (TIM_HandleType * htim);
/** @} */

/** @} */

/** @} */

#elif defined(XPD_USART_API)

/** @addtogroup USART
 * @{ */

/** @defgroup USART_Clock_Source USART Clock Source
 * @{ */

/** @defgroup USART_Clock_Source_Exported_Types USART Clock Source Exported Types
 * @{ */

/** @brief USART clock source types */
typedef enum
{
    USART_CLOCKSOURCE_PCLKx   = 0, /*!< default clock source */
    USART_CLOCKSOURCE_SYSCLK  = 1, /*!< SYSCLK clock source */
#ifdef LSE_VALUE
    USART_CLOCKSOURCE_LSE     = 2, /*!< LSE clock source */
#endif
    USART_CLOCKSOURCE_HSI     = 3, /*!< HSI clock source */
}USART_ClockSourceType;
/** @} */

/** @addtogroup USART_Clock_Source_Exported_Functions
 * @{ */
void            XPD_USART_ClockConfig       (USART_HandleType * husart, USART_ClockSourceType ClockSource);
uint32_t        XPD_USART_GetClockFreq      (USART_HandleType * husart);
/** @} */

/** @} */

/** @} */

#elif defined(XPD_USB_API)

/** @addtogroup USB
 * @{ */

/** @defgroup USB_Clock_Source USB Clock Source
 * @{ */

/** @defgroup USB_Clock_Source_Exported_Types USB Clock Source Exported Types
 * @{ */

/** @brief USB clock source types */
typedef enum
{
    USB_CLOCKSOURCE_PLL         = 1, /*!< PLL clock source */
    USB_CLOCKSOURCE_PLL_DIV1p5  = 0, /*!< PLL * 2 / 3 clock source */
}USB_ClockSourceType;
/** @} */

/** @addtogroup USB_Clock_Source_Exported_Functions
 * @{ */
void            XPD_USB_ClockConfig         (USB_ClockSourceType ClockSource);
/** @} */

/** @} */

/** @} */
#endif
