/**
  ******************************************************************************
  * @file    xpd_adc.h
  * @author  Benedek Kupper
  * @version V0.1
  * @date    2016-02-04
  * @brief   STM32 eXtensible Peripheral Drivers Analog Digital Converter Module
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
#ifndef __XPD_ADC_H_
#define __XPD_ADC_H_

#include "xpd_common.h"
#include "xpd_config.h"
#include "xpd_adc_calc.h"
#include "xpd_dma.h"

/** @defgroup ADC
 * @{ */

/** @defgroup ADC_Core ADC Core
 * @{ */

/** @defgroup ADC_Core_Exported_Types ADC Core Exported Types
 * @{ */

/** @brief ADC error types */
typedef enum
{
    ADC_ERROR_NONE      = 0,   /*!< No error */
    ADC_ERROR_OVERRUN   = 1,   /*!< Overrun flag */
    ADC_ERROR_JQOVF     = 2,   /*!< Injected queue overflow flag */
    ADC_ERROR_DMA       = 4,   /*!< DMA transfer error */
}ADC_ErrorType;

/** @brief ADC sample times */
typedef enum
{
    ADC_SAMPLETIME_1p5   = 0, /*!< Sampling during 1.5 clock cycles */
    ADC_SAMPLETIME_2p5   = 1, /*!< Sampling during 2.5 clock cycles */
    ADC_SAMPLETIME_4p5   = 2, /*!< Sampling during 4.5 clock cycles */
    ADC_SAMPLETIME_7p5   = 3, /*!< Sampling during 7.5 clock cycles */
    ADC_SAMPLETIME_19p5  = 4, /*!< Sampling during 19.5 clock cycles */
    ADC_SAMPLETIME_61p5  = 5, /*!< Sampling during 61.5 clock cycles */
    ADC_SAMPLETIME_181p5 = 6, /*!< Sampling during 181.5 clock cycles */
    ADC_SAMPLETIME_601p5 = 7  /*!< Sampling during 601.5 clock cycles */
}ADC_SampleTimeType;

/** @brief ADC conversion resolution */
typedef enum
{
    ADC_RESOLUTION_12BIT = 0, /*!< 12 bit resolution */
    ADC_RESOLUTION_10BIT = 1, /*!< 10 bit resolution */
    ADC_RESOLUTION_8BIT  = 2, /*!< 8 bit resolution */
    ADC_RESOLUTION_6BIT  = 3  /*!< 6 bit resolution */
}ADC_ResolutionType;

/** @brief ADC trigger sources */
typedef enum
{
    ADC_TRIGGER_SOFTWARE   = 16  /*!< Implicit trigger by software on start call */
}ADC_TriggerSourceType;

/** @brief ADC1 and 2 trigger sources */
typedef enum
{
    ADC1_2_TRIGGER_TIM1_CC1   = 0,  /*!< TIM1 Channel 1 */
    ADC1_2_TRIGGER_TIM1_CC2   = 1,  /*!< TIM1 Channel 2 */
    ADC1_2_TRIGGER_TIM1_CC3   = 2,  /*!< TIM1 Channel 3 */
    ADC1_2_TRIGGER_TIM2_CC2   = 3,  /*!< TIM2 Channel 2 */
    ADC1_2_TRIGGER_TIM3_TRGO  = 4,  /*!< TIM3 Trigger Out */
    ADC1_2_TRIGGER_TIM4_CC4   = 5,  /*!< TIM4 Channel 4 */
    ADC1_2_TRIGGER_EXTI11     = 6,  /*!< EXTI Line 11 */
#ifdef HRTIM1
    ADC1_2_TRIGGER_HRTIM_TRG1 = 7,  /*!< HRTIM Trigger 1 */
    ADC1_2_TRIGGER_HRTIM_TRG3 = 8,  /*!< HRTIM Trigger 3 */
#else
    ADC1_2_TRIGGER_TIM8_TRGO  = 7,  /*!< TIM8 Trigger Out */
    ADC1_2_TRIGGER_TIM8_TRGO2 = 8,  /*!< TIM8 Trigger Out 2 */
#endif
    ADC1_2_TRIGGER_TIM1_TRGO  = 9,  /*!< TIM1 Trigger Out */
    ADC1_2_TRIGGER_TIM1_TRGO2 = 10, /*!< TIM1 Trigger Out 2 */
    ADC1_2_TRIGGER_TIM2_TRGO  = 11, /*!< TIM2 Trigger Out */
    ADC1_2_TRIGGER_TIM4_TRGO  = 12, /*!< TIM4 Trigger Out */
    ADC1_2_TRIGGER_TIM6_TRGO  = 13, /*!< TIM6 Trigger Out */
    ADC1_2_TRIGGER_TIM15_TRGO = 14, /*!< TIM15 Trigger Out */
    ADC1_2_TRIGGER_TIM3_CC4   = 15, /*!< TIM3 Channel 4 */
    ADC1_2_TRIGGER_SOFTWARE   = 16  /*!< Implicit trigger by software on start call */
}ADC1_2_TriggerSourceType;

/** @brief ADC3 and 4 trigger sources */
typedef enum
{
    ADC3_4_TRIGGER_TIM3_CC1   = 0,  /*!< TIM3 Channel 1 */
    ADC3_4_TRIGGER_TIM2_CC3   = 1,  /*!< TIM2 Channel 3 */
    ADC3_4_TRIGGER_TIM1_CC3   = 2,  /*!< TIM1 Channel 3 */
    ADC3_4_TRIGGER_TIM8_CC1   = 3,  /*!< TIM8 Channel 1 */
    ADC3_4_TRIGGER_TIM8_TRGO  = 4,  /*!< TIM8 Trigger Out */
    ADC3_4_TRIGGER_EXTI2      = 5,  /*!< EXTI Line 2 */
    ADC3_4_TRIGGER_TIM4_CC1   = 6,  /*!< TIM4 Channel 1 */
    ADC3_4_TRIGGER_TIM2_TRGO  = 7,  /*!< TIM2 Trigger Out */
    ADC3_4_TRIGGER_TIM8_TRGO2 = 8,  /*!< TIM8 Trigger Out 2 */
    ADC3_4_TRIGGER_TIM1_TRGO  = 9,  /*!< TIM1 Trigger Out */
    ADC3_4_TRIGGER_TIM1_TRGO2 = 10, /*!< TIM1 Trigger Out 2 */
    ADC3_4_TRIGGER_TIM3_TRGO  = 11, /*!< TIM3 Trigger Out */
    ADC3_4_TRIGGER_TIM4_TRGO  = 12, /*!< TIM4 Trigger Out */
    ADC3_4_TRIGGER_TIM7_TRGO  = 13, /*!< TIM7 Trigger Out */
    ADC3_4_TRIGGER_TIM15_TRGO = 14, /*!< TIM15 Trigger Out */
    ADC3_4_TRIGGER_TIM2_CC1   = 15, /*!< TIM2 Channel 1 */
    ADC3_4_TRIGGER_SOFTWARE   = 16  /*!< Implicit trigger by software on start call */
}ADC3_4_TriggerSourceType;

/** @brief ADC End of Conversion flag mode */
typedef enum
{
    ADC_EOC_SEQUENCE = 0, /*!< End of Conversion flag is set at the end of a sequence */
    ADC_EOC_SINGLE   = 1  /*!< End of Conversion flag is set at the end of each individual conversion */
}ADC_EOCSelectType;

/** @brief ADC operation types */
typedef enum
{
    ADC_OPERATION_CONVERSION    = ADC_ISR_EOC,  /*!< Regular conversion */
    ADC_OPERATION_INJCONVERSION = ADC_ISR_JEOC, /*!< Injected conversion */
    ADC_OPERATION_WATCHDOG1     = ADC_ISR_AWD1, /*!< Analog watchdog 1 */
    ADC_OPERATION_WATCHDOG2     = ADC_ISR_AWD2, /*!< Analog watchdog 2 */
    ADC_OPERATION_WATCHDOG3     = ADC_ISR_AWD3, /*!< Analog watchdog 3 */
    ADC_OPERATION_OVERRUN       = ADC_ISR_OVR   /*!< Overrun */
}ADC_OperationType;

/** @brief ADC setup structure */
typedef struct
{
    ADC_ResolutionType  Resolution;            /*!< A/D conversion resolution */
    FunctionalState     LeftAlignment;         /*!< ENABLE to left-align converted data, otherwise DISABLE */
    FunctionalState     ContinuousMode;        /*!< Continuous or single mode */
    FunctionalState     ContinuousDMARequests; /*!< Continuous DMA requests, or only for a single EOC flag */
    FunctionalState     ScanMode;              /*!< Scan mode converts all configured channels in sequence */
    uint8_t             DiscontinuousCount;    /*!< If not 0, a subgroup of channels is converted
                                                    on each trigger in loop [0..8] */
    ADC_EOCSelectType   EndFlagSelection;      /*!< Specifies when the EOC flag is set and the conversions stop */
    FunctionalState     LPAutoWait;            /*!< When enabled, new conversion starts only after the user has handled the current conversion. */
    struct {
        ADC_TriggerSourceType Source;          /*!< Source of the conversion trigger */
        EdgeType              Edge;            /*!< Trigger edges that initiate conversion */
    }Trigger;
}ADC_InitType;

/** @brief ADC analog watchdog selection */
typedef enum
{
    ADC_AWD_NONE = 0, /*!< No watchdog is used */
    ADC_AWD1     = 1, /*!< AWD1 default watchdog selection
                           @note This watchdog can only monitor a single channel, or whole conversion group(s) */
    ADC_AWD2     = 2, /*!< AWD2 channel-wise watchdog selection */
    ADC_AWD3     = 3, /*!< AWD3 channel-wise watchdog selection */
}ADC_WatchdogType;

/** @brief ADC channel setup structure */
typedef struct
{
    uint8_t            Number;       /*!< Number of the ADC channel [0..18] */
    ADC_SampleTimeType SampleTime;   /*!< Sample time of the channel */
    uint16_t           Offset;       /*!< Offset is subtracted after conversion of channel */
    FunctionalState    Differential; /*!< Channel is differential or single ended */
    ADC_WatchdogType   Watchdog;     /*!< Channel monitoring watchdog selection */
}ADC_ChannelInitType;

/** @brief ADC watchdog setup structure */
typedef struct
{
    uint16_t High;             /*!< Watchdog high threshold */
    uint16_t Low;              /*!< Watchdog low threshold */
}ADC_WatchdogThresholdType;

/** @brief ADC Handle structure */
typedef struct
{
    ADC_TypeDef * Inst;                             /*!< The address of the peripheral instance used by the handle */
#ifdef ADC_BB
    ADC_BitBand_TypeDef * Inst_BB;                  /*!< The address of the peripheral instance in the bit-band region */
#endif
    struct {
        XPD_HandleCallbackType DepInit;             /*!< Callback to initialize module dependencies (GPIOs, IRQs, DMAs) */
        XPD_HandleCallbackType DepDeinit;           /*!< Callback to restore module dependencies (GPIOs, IRQs, DMAs) */
        XPD_HandleCallbackType ConvComplete;        /*!< Conversion(s) complete callback */
        XPD_HandleCallbackType InjConvComplete;     /*!< Injected conversion(s) complete callback */
        XPD_HandleCallbackType Watchdog;            /*!< Watchdog alert callback */
#if defined(USE_XPD_ADC_ERROR_DETECT) || defined(USE_XPD_DMA_ERROR_DETECT)
        XPD_HandleCallbackType Error;
#endif
    }Callbacks;                                     /*   Handle Callbacks */
    struct {
        DMA_HandleType * Conversion;                /*!< DMA handle for update transfer */
    }DMA;                                           /*   DMA handle references */
    uint32_t OffsetUsage;                           /*!< [Internal] Bitflag for offset using channel numbers */
    uint32_t InjectedContextQueue;                  /*!< [Internal] The injected channel context queue */
    uint8_t ConversionCount;                        /*!< ADC number of regular conversions */
    uint8_t EndFlagSelection;                       /*!< [Internal] Stores the EOC configuration */
    volatile ADC_WatchdogType ActiveWatchdog;       /*!< [Internal] The currently active watchdog number */
#if defined(USE_XPD_ADC_ERROR_DETECT) || defined(USE_XPD_DMA_ERROR_DETECT)
    volatile ADC_ErrorType Errors;                  /*!< Conversion errors */
#endif
}ADC_HandleType;

/** @} */

/** @defgroup ADC_Core_Exported_Macros ADC Core Exported Macros
 * @{ */

#if defined(ADC34_COMMON)
/** @brief Number of ADC peripherals */
#define         ADC_COUNT           4

/**
 * @brief  The index of the ADC peripheral managed by the handle.
 * @param  HANDLE: specifies the peripheral handle.
 */
#define         ADC_INDEX(HANDLE)                   \
    ((((((uint32_t)(HANDLE)->Inst) > ADC2_BASE) ?   \
    (((uint32_t)(HANDLE)->Inst) - 0x200) :          \
     ((uint32_t)(HANDLE)->Inst)) >> 8) & 3)

/**
 * @brief  The common ADC registers related to the handle.
 * @param  HANDLE: specifies the peripheral handle.
 */
#define         ADC_COMMON(HANDLE)                  \
    ((ADC_Common_TypeDef *)(((uint32_t)(HANDLE)->Inst) | 0x300))

#elif defined(ADC12_COMMON)

/** @brief Number of ADC peripherals */
#define         ADC_COUNT           2

/**
 * @brief  The index of the ADC peripheral managed by the handle.
 * @param  HANDLE: specifies the peripheral handle.
 */
#define         ADC_INDEX(HANDLE)   \
    (((((uint32_t)(HANDLE)->Inst)) >> 8) & 3)

/**
 * @brief  The common ADC registers related to the handle.
 * @param  HANDLE: specifies the peripheral handle.
 */
#define         ADC_COMMON(HANDLE)  \
    (ADC12_COMMON)

#else
/** @brief Number of ADC peripherals */
#define         ADC_COUNT           1

/**
 * @brief  The index of the ADC peripheral managed by the handle.
 * @param  HANDLE: specifies the peripheral handle.
 */
#define         ADC_INDEX(HANDLE)   \
    0

/**
 * @brief  The common ADC registers related to the handle.
 * @param  HANDLE: specifies the peripheral handle.
 */
#define         ADC_COMMON(HANDLE)  \
    (ADC1_COMMON)

#endif /* ADC34_COMMON */
#ifdef ADC_BB
/**
 * @brief  ADC Handle initializer macro
 * @param  INSTANCE: specifies the ADC peripheral instance.
 * @param  INIT_FN: specifies the dependency initialization function to call back.
 * @param  DEINIT_FN: specifies the dependency deinitialization function to call back.
 */
#define         NEW_ADC_HANDLE(INSTANCE,INIT_FN,DEINIT_FN)      \
    {.Inst = (INSTANCE), .Inst_BB = ADC_BB(INSTANCE),           \
     .Callbacks.DepInit   = (INIT_FN),                          \
     .Callbacks.DepDeinit = (DEINIT_FN)}

/**
 * @brief ADC register bit accessing macro
 * @param HANDLE: specifies the peripheral handle.
 * @param REG: specifies the register name.
 * @param BIT: specifies the register bit name.
 */
#define         ADC_REG_BIT(HANDLE, REG_NAME, BIT_NAME)         \
    ((HANDLE)->Inst_BB->REG_NAME.BIT_NAME)

/**
 * @brief ADC common register bit accessing macro
 * @param HANDLE: specifies the peripheral handle.
 * @param REG: specifies the register name.
 * @param BIT: specifies the register bit name.
 */
#define         ADC_COMMON_REG_BIT(HANDLE, REG_NAME, BIT_NAME)  \
    (ADC_COMMON_BB->REG_NAME.BIT_NAME)

#else
/**
 * @brief  ADC Handle initializer macro
 * @param  INSTANCE: specifies the ADC peripheral instance.
 * @param  INIT_FN: specifies the dependency initialization function to call back.
 * @param  DEINIT_FN: specifies the dependency deinitialization function to call back.
 */
#define         NEW_ADC_HANDLE(INSTANCE,INIT_FN,DEINIT_FN)      \
    {.Inst = (INSTANCE),                                        \
     .Callbacks.DepInit   = (INIT_FN),                          \
     .Callbacks.DepDeinit = (DEINIT_FN)}

/**
 * @brief ADC register bit accessing macro
 * @param HANDLE: specifies the peripheral handle.
 * @param REG: specifies the register name.
 * @param BIT: specifies the register bit name.
 */
#define         ADC_REG_BIT(HANDLE, REG_NAME, BIT_NAME)         \
    ((HANDLE)->Inst->REG_NAME.b.BIT_NAME)

/**
 * @brief ADC common register bit accessing macro
 * @param HANDLE: specifies the peripheral handle.
 * @param REG: specifies the register name.
 * @param BIT: specifies the register bit name.
 */
#define         ADC_COMMON_REG_BIT(HANDLE, REG_NAME, BIT_NAME)  \
    (ADC_COMMON(HANDLE)->REG_NAME.b.BIT_NAME)

#endif /* ADC_BB */

/**
 * @brief  Enable the specified ADC interrupt.
 * @param  HANDLE: specifies the ADC Handle.
 * @param  IT_NAME: specifies the interrupt to enable.
 *         This parameter can be one of the following values:
 *            @arg ADRDY:   A/D converter ready
 *            @arg EOSMP:   End of sampling
 *            @arg EOC:     End of regular conversion
 *            @arg EOS:     End of regular sequence
 *            @arg OVR:     Overrun
 *            @arg JEOC:    End of injected conversion
 *            @arg JEOS:    End of injected sequence
 *            @arg AWD1:    Analog watchdog 1
 *            @arg AWD2:    Analog watchdog 2
 *            @arg AWD3:    Analog watchdog 3
 *            @arg JQOVF:   Injected queue overflow
 */
#define         XPD_ADC_EnableIT(  HANDLE,  IT_NAME)            \
    (ADC_REG_BIT((HANDLE),IER,IT_NAME ## IE) = 1)

/**
 * @brief  Disable the specified ADC interrupt.
 * @param  HANDLE: specifies the ADC Handle.
 * @param  IT_NAME: specifies the interrupt to enable.
 *         This parameter can be one of the following values:
 *            @arg ADRDY:   A/D converter ready
 *            @arg EOSMP:   End of sampling
 *            @arg EOC:     End of regular conversion
 *            @arg EOS:     End of regular sequence
 *            @arg OVR:     Overrun
 *            @arg JEOC:    End of injected conversion
 *            @arg JEOS:    End of injected sequence
 *            @arg AWD1:    Analog watchdog 1
 *            @arg AWD2:    Analog watchdog 2
 *            @arg AWD3:    Analog watchdog 3
 *            @arg JQOVF:   Injected queue overflow
 */
#define         XPD_ADC_DisableIT( HANDLE,  IT_NAME)            \
    (ADC_REG_BIT((HANDLE),IER,IT_NAME ## IE) = 0)

/**
 * @brief  Get the specified ADC flag.
 * @param  HANDLE: specifies the ADC Handle.
 * @param  FLAG_NAME: specifies the flag to return.
 *         This parameter can be one of the following values:
 *            @arg ADRDY:   A/D converter ready
 *            @arg EOSMP:   End of sampling
 *            @arg EOC:     End of regular conversion
 *            @arg EOS:     End of regular sequence
 *            @arg OVR:     Overrun
 *            @arg JEOC:    End of injected conversion
 *            @arg JEOS:    End of injected sequence
 *            @arg AWD1:    Analog watchdog 1
 *            @arg AWD2:    Analog watchdog 2
 *            @arg AWD3:    Analog watchdog 3
 *            @arg JQOVF:   Injected queue overflow
 */
#define         XPD_ADC_GetFlag(  HANDLE, FLAG_NAME)            \
    (ADC_REG_BIT((HANDLE),ISR,FLAG_NAME))

/**
 * @brief  Clear the specified ADC flag.
 * @param  HANDLE: specifies the ADC Handle.
 * @param  FLAG_NAME: specifies the flag to return.
 *         This parameter can be one of the following values:
 *            @arg ADRDY:   A/D converter ready
 *            @arg EOSMP:   End of sampling
 *            @arg EOC:     End of regular conversion
 *            @arg EOS:     End of regular sequence
 *            @arg OVR:     Overrun
 *            @arg JEOC:    End of injected conversion
 *            @arg JEOS:    End of injected sequence
 *            @arg AWD1:    Analog watchdog 1
 *            @arg AWD2:    Analog watchdog 2
 *            @arg AWD3:    Analog watchdog 3
 *            @arg JQOVF:   Injected queue overflow
 */
#define         XPD_ADC_ClearFlag(HANDLE, FLAG_NAME)            \
    ((HANDLE)->Inst->ISR.w = ADC_ISR_##FLAG_NAME)

/* Compatibility macros */
#define ADC_TRIGGER_TIM1_CC1   (ADC1_2_TRIGGER_TIM1_CC1)
#define ADC_TRIGGER_TIM1_CC2   (ADC1_2_TRIGGER_TIM1_CC2)
#define ADC_TRIGGER_TIM1_CC3   (ADC1_2_TRIGGER_TIM1_CC3)
#define ADC_TRIGGER_TIM2_CC2   (ADC1_2_TRIGGER_TIM2_CC2)
#define ADC_TRIGGER_TIM3_TRGO  (ADC1_2_TRIGGER_TIM3_TRGO)
#define ADC_TRIGGER_TIM4_CC4   (ADC1_2_TRIGGER_TIM4_CC4)
#define ADC_TRIGGER_EXTI11     (ADC1_2_TRIGGER_EXTI11)
#ifdef HRTIM1
#define ADC_TRIGGER_HRTIM_TRG1 (ADC1_2_TRIGGER_HRTIM_TRG1)
#define ADC_TRIGGER_HRTIM_TRG3 (ADC1_2_TRIGGER_HRTIM_TRG3)
#else
#define ADC_TRIGGER_TIM8_TRGO  (ADC1_2_TRIGGER_TIM8_TRGO)
#define ADC_TRIGGER_TIM8_TRGO2 (ADC1_2_TRIGGER_TIM8_TRGO2)
#endif
#define ADC_TRIGGER_TIM1_TRGO  (ADC1_2_TRIGGER_TIM1_TRGO)
#define ADC_TRIGGER_TIM1_TRGO2 (ADC1_2_TRIGGER_TIM1_TRGO2)
#define ADC_TRIGGER_TIM2_TRGO  (ADC1_2_TRIGGER_TIM2_TRGO)
#define ADC_TRIGGER_TIM4_TRGO  (ADC1_2_TRIGGER_TIM4_TRGO)
#define ADC_TRIGGER_TIM6_TRGO  (ADC1_2_TRIGGER_TIM6_TRGO)
#define ADC_TRIGGER_TIM15_TRGO (ADC1_2_TRIGGER_TIM15_TRGO)
#define ADC_TRIGGER_TIM3_CC4   (ADC1_2_TRIGGER_TIM3_CC4)

/** @} */

/** @defgroup ADC_Core_Exported_Functions ADC Core Exported Functions
 * @{ */
XPD_ReturnType  XPD_ADC_Init                (ADC_HandleType * hadc, const ADC_InitType * Config);
XPD_ReturnType  XPD_ADC_Deinit              (ADC_HandleType * hadc);
void            XPD_ADC_ChannelConfig       (ADC_HandleType * hadc, const ADC_ChannelInitType * Channels,
                                             uint8_t ChannelCount);

void            XPD_ADC_Start               (ADC_HandleType * hadc);
void            XPD_ADC_Stop                (ADC_HandleType * hadc);
XPD_ReturnType  XPD_ADC_PollStatus          (ADC_HandleType * hadc, ADC_OperationType Operation,
                                             uint32_t Timeout);

void            XPD_ADC_Start_IT            (ADC_HandleType * hadc);
void            XPD_ADC_Stop_IT             (ADC_HandleType * hadc);
void            XPD_ADC_IRQHandler          (ADC_HandleType * hadc);

XPD_ReturnType  XPD_ADC_Start_DMA           (ADC_HandleType * hadc, void * Address);
void            XPD_ADC_Stop_DMA            (ADC_HandleType * hadc);

void            XPD_ADC_WatchdogConfig      (ADC_HandleType * hadc, ADC_WatchdogType Watchdog,
                                             const ADC_WatchdogThresholdType * Config);
ADC_WatchdogType XPD_ADC_WatchdogStatus     (ADC_HandleType * hadc);

/**
 * @brief Return the result of the last ADC regular conversion.
 * @param hadc: pointer to the ADC handle structure
 * @return The conversion result
 */
__STATIC_INLINE uint16_t XPD_ADC_GetValue(ADC_HandleType * hadc)
{
    return (uint16_t)hadc->Inst->DR;
}

/** @} */

/** @} */

/** @defgroup ADC_Injected ADC Injected Conversions
 * @{ */

/** @defgroup ADC_Injected_Exported_Types ADC Injected Exported Types
 * @{ */

/** @brief ADC injected trigger sources */
typedef enum
{
    ADC_INJTRIGGER_SOFTWARE  = 16  /*!< Implicit trigger by software on start call */
}ADC_InjTriggerSourceType;

/** @brief ADC1 and 2 injected trigger sources */
typedef enum
{
    ADC1_2_INJTRIGGER_TIM1_TRGO  = 0,  /*!< TIM1 Trigger Out */
    ADC1_2_INJTRIGGER_TIM1_CC4   = 1,  /*!< TIM1 Channel 4 */
    ADC1_2_INJTRIGGER_TIM2_TRGO  = 2,  /*!< TIM2 Trigger Out */
    ADC1_2_INJTRIGGER_TIM2_CC1   = 3,  /*!< TIM2 Channel 1 */
    ADC1_2_INJTRIGGER_TIM3_CC4   = 4,  /*!< TIM3 Channel 4 */
    ADC1_2_INJTRIGGER_TIM4_TRGO  = 5,  /*!< TIM4 Trigger Out */
    ADC1_2_INJTRIGGER_EXTI15     = 6,  /*!< EXTI Line 15 */
    ADC1_2_INJTRIGGER_TIM8_CC4   = 7,  /*!< TIM8 Channel 4 */
    ADC1_2_INJTRIGGER_TIM1_TRGO2 = 8,  /*!< TIM1 Trigger Out 2 */
#ifdef HRTIM1
    ADC1_2_INJTRIGGER_HRTIM_TRG2 = 9,  /*!< HRTIM Trigger 2 */
    ADC1_2_INJTRIGGER_HRTIM_TRG4 = 10, /*!< HRTIM Trigger 4 */
#else
    ADC1_2_INJTRIGGER_TIM8_TRGO  = 9,  /*!< TIM8 Trigger Out */
    ADC1_2_INJTRIGGER_TIM8_TRGO2 = 10, /*!< TIM8 Trigger Out 2 */
#endif
    ADC1_2_INJTRIGGER_TIM3_CC3   = 11, /*!< TIM3 Channel 3 */
    ADC1_2_INJTRIGGER_TIM3_TRGO  = 12, /*!< TIM3 Trigger Out */
    ADC1_2_INJTRIGGER_TIM3_CC1   = 13, /*!< TIM3 Channel 1 */
    ADC1_2_INJTRIGGER_TIM6_TRGO  = 14, /*!< TIM6 Trigger Out */
    ADC1_2_INJTRIGGER_TIM15_TRGO = 15, /*!< TIM15 Trigger Out */
    ADC1_2_INJTRIGGER_SOFTWARE   = 16  /*!< Implicit trigger by software on start call */
}ADC1_2_InjTriggerSourceType;

/** @brief ADC3 and 4 injected trigger sources */
typedef enum
{
    ADC3_4_INJTRIGGER_TIM1_TRGO  = 0,  /*!< TIM1 Trigger Out */
    ADC3_4_INJTRIGGER_TIM1_CC4   = 1,  /*!< TIM1 Channel 4 */
    ADC3_4_INJTRIGGER_TIM4_CC3   = 2,  /*!< TIM4 Channel 3 */
    ADC3_4_INJTRIGGER_TIM8_CC2   = 3,  /*!< TIM8 Channel 2 */
    ADC3_4_INJTRIGGER_TIM8_CC3   = 4,  /*!< TIM8 Channel 3 */
    ADC3_4_INJTRIGGER_TIM8_CC4   = 5,  /*!< TIM8 Channel 4 */
    ADC3_4_INJTRIGGER_TIM4_CC4   = 6,  /*!< TIM4 Channel 4 */
    ADC3_4_INJTRIGGER_TIM4_TRGO  = 7,  /*!< TIM4 Trigger Out */
    ADC3_4_INJTRIGGER_TIM1_TRGO2 = 8,  /*!< TIM1 Trigger Out 2 */
    ADC3_4_INJTRIGGER_TIM8_TRGO  = 9,  /*!< TIM8 Trigger Out */
    ADC3_4_INJTRIGGER_TIM8_TRGO2 = 10, /*!< TIM8 Trigger Out 2 */
    ADC3_4_INJTRIGGER_TIM1_CC3   = 11, /*!< TIM1 Channel 3 */
    ADC3_4_INJTRIGGER_TIM3_TRGO  = 12, /*!< TIM3 Trigger Out */
    ADC3_4_INJTRIGGER_TIM2_TRGO  = 13, /*!< TIM2 Trigger Out */
    ADC3_4_INJTRIGGER_TIM7_TRGO  = 14, /*!< TIM7 Trigger Out */
    ADC3_4_INJTRIGGER_TIM15_TRGO = 15, /*!< TIM15 Trigger Out */
    ADC3_4_INJTRIGGER_SOFTWARE   = 16  /*!< Implicit trigger by software on start call */
}ADC3_4_InjTriggerSourceType;

/** @brief ADC injected channel setup structure */
typedef struct
{
    FunctionalState    AutoInjection;       /*!< Automatic injected conversion after regular group
                                                 @note External triggers must be disabled */
    FunctionalState    DiscontinuousMode;   /*!< Sets discontinuous mode
                                                 @note Cannot be used with auto injection */
    struct {
        ADC_InjTriggerSourceType InjSource; /*!< Source of the conversion trigger */
        EdgeType                 Edge;      /*!< Trigger edges that initiate conversion */
    }Trigger;
    FunctionalState    ContextQueue;        /*!< Context queue feature */
}ADC_Injected_InitType;

/** @} */

/* Compatibility macros */
#define ADC_INJTRIGGER_TIM1_TRGO  (ADC_INJTRIGGER_TIM1_TRGO)
#define ADC_INJTRIGGER_TIM1_CC4   (ADC_INJTRIGGER_TIM1_CC4)
#define ADC_INJTRIGGER_TIM2_TRGO  (ADC_INJTRIGGER_TIM2_TRGO)
#define ADC_INJTRIGGER_TIM2_CC1   (ADC_INJTRIGGER_TIM2_CC1)
#define ADC_INJTRIGGER_TIM3_CC4   (ADC_INJTRIGGER_TIM3_CC4)
#define ADC_INJTRIGGER_TIM4_TRGO  (ADC_INJTRIGGER_TIM4_TRGO)
#define ADC_INJTRIGGER_EXTI15     (ADC_INJTRIGGER_EXTI15)
#define ADC_INJTRIGGER_TIM8_CC4   (ADC_INJTRIGGER_TIM8_CC4)
#define ADC_INJTRIGGER_TIM1_TRGO2 (ADC_INJTRIGGER_TIM1_TRGO2)
#ifdef HRTIM1
#define ADC_INJTRIGGER_HRTIM_TRG2 (ADC_INJTRIGGER_HRTIM_TRG2)
#define ADC_INJTRIGGER_HRTIM_TRG4 (ADC_INJTRIGGER_HRTIM_TRG4)
#else
#define ADC_INJTRIGGER_TIM8_TRGO  (ADC_INJTRIGGER_TIM8_TRGO)
#define ADC_INJTRIGGER_TIM8_TRGO2 (ADC_INJTRIGGER_TIM8_TRGO2)
#endif
#define ADC_INJTRIGGER_TIM3_CC3   (ADC_INJTRIGGER_TIM3_CC3)
#define ADC_INJTRIGGER_TIM3_TRGO  (ADC_INJTRIGGER_TIM3_TRGO)
#define ADC_INJTRIGGER_TIM3_CC1   (ADC_INJTRIGGER_TIM3_CC1)
#define ADC_INJTRIGGER_TIM6_TRGO  (ADC_INJTRIGGER_TIM6_TRGO)
#define ADC_INJTRIGGER_TIM15_TRGO (ADC_INJTRIGGER_TIM15_TRGO)

/** @addtogroup ADC_Injected_Exported_Functions
 * @{ */
void            XPD_ADC_Injected_Init       (ADC_HandleType * hadc, const ADC_Injected_InitType * Config);
void            XPD_ADC_Injected_ChannelConfig(ADC_HandleType*hadc, const ADC_ChannelInitType * Channels,
                                             uint8_t ChannelCount);

void            XPD_ADC_Injected_Start      (ADC_HandleType * hadc);
void            XPD_ADC_Injected_Stop       (ADC_HandleType * hadc);

void            XPD_ADC_Injected_Start_IT   (ADC_HandleType * hadc);
void            XPD_ADC_Injected_Stop_IT    (ADC_HandleType * hadc);

/**
 * @brief Return the result of an ADC injected conversion.
 * @param hadc: pointer to the ADC handle structure
 * @param Index: index of channel on injected ADC conversion sequence (0-indexed)
 * @return The conversion result
 */
__STATIC_INLINE uint16_t XPD_ADC_Inject_GetValue(ADC_HandleType * hadc, uint8_t Index)
{
    /* clear the flag for injected end of conversion */
    XPD_ADC_ClearFlag(hadc, JEOC);

    return (uint16_t)((&hadc->Inst->JDR1)[Index]);
}

/** @} */

/** @} */

#ifdef ADC12_COMMON
/** @defgroup ADC_MultiMode Multi ADC Mode Conversions
 * @{ */

/** @defgroup ADC_MultiMode_Exported_Types Multi ADC Mode Exported Types
 * @{ */

/** @brief Multi ADC modes */
typedef enum
{
/* all three ADCs operate independently */
    ADC_MULTIMODE_SINGE                        = 0, /*!< The ADCs operate independently */
/* ADC 1 and 2 common operation */
    ADC_MULTIMODE_DUAL_REGSIMULT               = 6, /*!< ADC1+2 regular simultaneous mode */
    ADC_MULTIMODE_DUAL_INJECSIMULT             = 5, /*!< ADC1+2 injected simultaneous mode */
    ADC_MULTIMODE_DUAL_REGSIMULT_ALTTRIGGER    = 2, /*!< ADC1+2 regular simultaneous, alternate trigger mode */
    ADC_MULTIMODE_DUAL_REGSIMULT_INJECSIMULT   = 1, /*!< ADC1+2 regular simultaneous + injected simultaneous mode */
    ADC_MULTIMODE_DUAL_REGINTERL_INJECSIMULT   = 3, /*!< ADC1+2 regular interleaved + injected simultaneous mode */
    ADC_MULTIMODE_DUAL_ALTTRIGGER              = 9, /*!< ADC1+2 alternate trigger mode */
    ADC_MULTIMODE_DUAL_INTERLEAVED             = 7, /*!< ADC1+2 interleaved mode */
}ADC_MultiModeType;

/** @brief ADC DMA access modes */
typedef enum
{
    ADC_DMAACCESSMODE_DISABLED   = 0, /*!< DMA mode disabled, each ADC uses its own DMA channel */
    ADC_DMAACCESSMODE_12_10_BITS = 2, /*!< DMA of ADC master is used, for 12 and 10 bit resolutions */
    ADC_DMAACCESSMODE_8_6_BITS   = 3, /*!< DMA of ADC master is used, for 8 and 6 bit resolutions */
}ADC_DMAAccessModeType;

/** @brief Multi ADC setup structure */
typedef struct
{
    ADC_MultiModeType     Mode;               /*!< Multi-mode operation type configuration */
    ADC_DMAAccessModeType DMAAccessMode;      /*!< DMA access mode configuration */
    uint8_t               InterSamplingDelay; /*!< Delay between 2 sampling phases [1..12] */
}ADC_MultiMode_InitType;

/** @} */

/** @addtogroup ADC_MultiMode_Exported_Functions
 * @{ */
void            XPD_ADC_MultiMode_Config    (ADC_HandleType * hadc, const ADC_MultiMode_InitType * Config);
XPD_ReturnType  XPD_ADC_MultiMode_Start_DMA (ADC_HandleType * hadc, void * Address);
void            XPD_ADC_MultiMode_Stop_DMA  (ADC_HandleType * hadc);

/**
 * @brief Return the result of the last common ADC regular conversions.
 * @return A pair of conversion results in a single word
 */
__STATIC_INLINE uint32_t XPD_ADC_MultiMode_GetValues(ADC_HandleType * hadc)
{
    /* return the multi mode conversion values */
    return ADC_COMMON(hadc)->CDR.w;
}

/** @} */

/** @} */
#endif

/** @defgroup ADC_Calibration ADC Calibration
 * @{ */

/** @addtogroup ADC_Calibration_Exported_Functions
 * @{ */
XPD_ReturnType  XPD_ADC_Calibrate           (ADC_HandleType * hadc, boolean_t Differential);
/** @} */

/** @} */

/** @} */

#define XPD_ADC_API
#include "xpd_rcc_pc.h"
#undef XPD_ADC_API

#endif /* __XPD_ADC_H_ */
