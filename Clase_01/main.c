/*
 * STM32F405RGT6
 * Descripción: Este codigo tiene la finalidad de explicar el funcionamiento
 * de los registros en el microcontrolador y la creación de las direcciones de
 * "registros asignados a memoria"
*/
#include <stdint.h>
#define RCC_AHB1ENR_GPIOAEN 	(0x00000001UL)

#define	__IO					volatile

#define PERIPH_BASE				(0x40000000UL)				// Dirección base de los perifericos
#define AHB_OFFSET				(0x00020000UL)				// Offset del bus AHB pag. 76
#define AHB1PERIPH_BASE         (PERIPH_BASE + AHB_OFFSET)	// Primera dirección de AHB1

// PAG 74
#define GPIOA_OFFSET			(0x0000UL)
#define GPIOB_OFFSET			(0x0400UL)
#define GPIOC_OFFSET			(0x0800UL)
#define GPIOD_OFFSET			(0x0C00UL)
#define GPIOE_OFFSET			(0x1000UL)
#define GPIOF_OFFSET			(0x1400UL)
#define GPIOG_OFFSET			(0x1800UL)
#define GPIOH_OFFSET			(0x1C00UL)
#define GPIOI_OFFSET			(0x2000UL)
#define RCC_OFFSET				(0x3800UL)


#define GPIOA_BASE            (AHB1PERIPH_BASE + GPIOA_OFFSET)
#define GPIOB_BASE            (AHB1PERIPH_BASE + GPIOB_OFFSET)
#define GPIOC_BASE            (AHB1PERIPH_BASE + GPIOC_OFFSET)
#define GPIOD_BASE            (AHB1PERIPH_BASE + GPIOD_OFFSET)
#define GPIOE_BASE            (AHB1PERIPH_BASE + GPIOE_OFFSET)
#define GPIOF_BASE            (AHB1PERIPH_BASE + GPIOF_OFFSET)
#define GPIOG_BASE            (AHB1PERIPH_BASE + GPIOG_OFFSET)
#define GPIOH_BASE            (AHB1PERIPH_BASE + GPIOH_OFFSET)
#define GPIOI_BASE            (AHB1PERIPH_BASE + GPIOI_OFFSET)

#define RCC_BASE              (AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH               ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOI               ((GPIO_TypeDef *) GPIOI_BASE)

#define RCC                 ((RCC_TypeDef *) RCC_BASE)

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t PLLCFGR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t AHB1RSTR;
  __IO uint32_t AHB2RSTR;
  __IO uint32_t AHB3RSTR;
  uint32_t      RESERVED0;
  __IO uint32_t APB1RSTR;
  __IO uint32_t APB2RSTR;
  uint32_t      RESERVED1[2];
  __IO uint32_t AHB1ENR;
  __IO uint32_t AHB2ENR;
  __IO uint32_t AHB3ENR;
  uint32_t      RESERVED2;
  __IO uint32_t APB1ENR;
  __IO uint32_t APB2ENR;
  uint32_t      RESERVED3[2];
  __IO uint32_t AHB1LPENR;
  __IO uint32_t AHB2LPENR;
  __IO uint32_t AHB3LPENR;
  uint32_t      RESERVED4;
  __IO uint32_t APB1LPENR;
  __IO uint32_t APB2LPENR;
  uint32_t      RESERVED5[2];
  __IO uint32_t BDCR;
  __IO uint32_t CSR;
  uint32_t      RESERVED6[2];
  __IO uint32_t SSCGR;
  __IO uint32_t PLLI2SCFGR;
} RCC_TypeDef;

typedef struct
{
  __IO uint32_t MODER;
  __IO uint32_t OTYPER;
  __IO uint32_t OSPEEDR;
  __IO uint32_t PUPDR;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t LCKR;
  __IO uint32_t AFR[2];
} GPIO_TypeDef;
void delay(volatile uint32_t t);

int main()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &= ~0x00000C00;
	GPIOA->MODER |=  0x00000400;


	while(1)
	{
		GPIOA->ODR ^= (1 << 5);  // toggle PA5
		delay(100);
	}
}
void delay(volatile uint32_t t)
{
    while (t--)
    {
        for (volatile int i = 0; i < 1000; i++);
    }
}

