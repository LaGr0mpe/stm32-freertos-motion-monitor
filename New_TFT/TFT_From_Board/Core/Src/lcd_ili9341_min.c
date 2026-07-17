#include "lcd_ili9341_min.h"

extern SPI_HandleTypeDef hspi5;
extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;
extern volatile bool lcd_fill_done;

#define LCD_W 240U
#define LCD_H 320U
#define LCD_FB_ADDR 0xD0000000U

#define LCD_CS_LOW()    HAL_GPIO_WritePin(CSX_GPIO_Port, CSX_Pin, GPIO_PIN_RESET)
#define LCD_CS_HIGH()   HAL_GPIO_WritePin(CSX_GPIO_Port, CSX_Pin, GPIO_PIN_SET)
#define LCD_WRX_LOW()   HAL_GPIO_WritePin(WRX_DCX_GPIO_Port, WRX_DCX_Pin, GPIO_PIN_RESET)
#define LCD_WRX_HIGH()  HAL_GPIO_WritePin(WRX_DCX_GPIO_Port, WRX_DCX_Pin, GPIO_PIN_SET)
#define LCD_RDX_LOW()   HAL_GPIO_WritePin(RDX_GPIO_Port, RDX_Pin, GPIO_PIN_RESET)
#define LCD_RDX_HIGH()  HAL_GPIO_WritePin(RDX_GPIO_Port, RDX_Pin, GPIO_PIN_SET)

#define LCD_SWRESET         0x01
#define LCD_SLEEP_OUT       0x11
#define LCD_DISPLAY_ON      0x29
#define LCD_GRAM            0x2C
#define LCD_COLUMN_ADDR     0x2A
#define LCD_PAGE_ADDR       0x2B
#define LCD_MAC             0x36
#define LCD_PIXEL_FORMAT    0x3A
#define LCD_POWER1          0xC0
#define LCD_POWER2          0xC1
#define LCD_VCOM1           0xC5
#define LCD_VCOM2           0xC7
#define LCD_POWERA          0xCB
#define LCD_POWERB          0xCF
#define LCD_PRC             0xF7
#define LCD_DTCA            0xE8
#define LCD_DTCB            0xEA
#define LCD_POWER_SEQ       0xED
#define LCD_3GAMMA_EN       0xF2
#define LCD_RGB_INTERFACE   0xB0
#define LCD_FRMCTR1         0xB1
#define LCD_DFC             0xB6
#define LCD_GAMMA           0x26
#define LCD_PGAMMA          0xE0
#define LCD_NGAMMA          0xE1
#define LCD_INTERFACE       0xF6

static void LCD_IO_Init(void)
{
    /* The pins are already configured by CubeMX in MX_GPIO_Init().
       We only force a safe idle state here. */
    LCD_CS_HIGH();
    LCD_WRX_HIGH();
    LCD_RDX_HIGH();
}

static void LCD_WriteByte(uint8_t value)
{
    if (HAL_SPI_Transmit(&hspi5, &value, 1, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }
}

static void LCD_WriteCommand(uint8_t cmd)
{
    LCD_WRX_LOW();
    LCD_CS_LOW();
    LCD_WriteByte(cmd);
    LCD_CS_HIGH();
}

static void LCD_WriteData(uint8_t data)
{
    LCD_WRX_HIGH();
    LCD_CS_LOW();
    LCD_WriteByte(data);
    LCD_CS_HIGH();
}

static void LCD_WriteDataN(const uint8_t *data, uint32_t len)
{
    LCD_WRX_HIGH();
    LCD_CS_LOW();
    while (len-- != 0U)
    {
        LCD_WriteByte(*data++);
    }
    LCD_CS_HIGH();
}

void LCD_Init(void)
{
    LCD_IO_Init();

    LCD_WriteCommand(LCD_SWRESET);
    HAL_Delay(5);

    LCD_WriteCommand(0xCA);
    LCD_WriteData(0xC3);
    LCD_WriteData(0x08);
    LCD_WriteData(0x50);

    LCD_WriteCommand(LCD_POWERB);
    LCD_WriteData(0x00);
    LCD_WriteData(0xC1);
    LCD_WriteData(0x30);

    LCD_WriteCommand(LCD_POWER_SEQ);
    LCD_WriteData(0x64);
    LCD_WriteData(0x03);
    LCD_WriteData(0x12);
    LCD_WriteData(0x81);

    LCD_WriteCommand(LCD_DTCA);
    LCD_WriteData(0x85);
    LCD_WriteData(0x00);
    LCD_WriteData(0x78);

    LCD_WriteCommand(0xC0);
    LCD_WriteData(0x39);
    LCD_WriteData(0x2C);
    LCD_WriteData(0x00);
    LCD_WriteData(0x34);
    LCD_WriteData(0x02);

    LCD_WriteCommand(LCD_PRC);
    LCD_WriteData(0x20);

    LCD_WriteCommand(LCD_DTCB);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);

    LCD_WriteCommand(LCD_FRMCTR1);
    LCD_WriteData(0x00);
    LCD_WriteData(0x1B);

    LCD_WriteCommand(LCD_DFC);
    LCD_WriteData(0x0A);
    LCD_WriteData(0xA2);

    LCD_WriteCommand(LCD_POWER1);
    LCD_WriteData(0x10);

    LCD_WriteCommand(LCD_POWER2);
    LCD_WriteData(0x10);

    LCD_WriteCommand(LCD_VCOM1);
    LCD_WriteData(0x45);
    LCD_WriteData(0x15);

    LCD_WriteCommand(LCD_VCOM2);
    LCD_WriteData(0x90);

    LCD_WriteCommand(LCD_MAC);
    LCD_WriteData(0xC8);

    LCD_WriteCommand(LCD_PIXEL_FORMAT);
    LCD_WriteData(0x55);

    LCD_WriteCommand(LCD_3GAMMA_EN);
    LCD_WriteData(0x00);

    LCD_WriteCommand(LCD_RGB_INTERFACE);
    LCD_WriteData(0xC2);

    LCD_WriteCommand(LCD_DFC);
    LCD_WriteData(0x0A);
    LCD_WriteData(0xA7);
    LCD_WriteData(0x27);
    LCD_WriteData(0x04);

    LCD_WriteCommand(LCD_COLUMN_ADDR);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0xEF);

    LCD_WriteCommand(LCD_PAGE_ADDR);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0x3F);

    LCD_WriteCommand(LCD_INTERFACE);
    LCD_WriteData(0x01);
    LCD_WriteData(0x00);
    LCD_WriteData(0x06);

    LCD_WriteCommand(LCD_GRAM);
    HAL_Delay(200);

    LCD_WriteCommand(LCD_GAMMA);
    LCD_WriteData(0x01);

    LCD_WriteCommand(LCD_PGAMMA);
    LCD_WriteData(0x0F);
    LCD_WriteData(0x29);
    LCD_WriteData(0x24);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x0E);
    LCD_WriteData(0x09);
    LCD_WriteData(0x4E);
    LCD_WriteData(0x78);
    LCD_WriteData(0x3C);
    LCD_WriteData(0x09);
    LCD_WriteData(0x13);
    LCD_WriteData(0x05);
    LCD_WriteData(0x17);
    LCD_WriteData(0x11);
    LCD_WriteData(0x00);

    LCD_WriteCommand(LCD_NGAMMA);
    LCD_WriteData(0x00);
    LCD_WriteData(0x16);
    LCD_WriteData(0x1B);
    LCD_WriteData(0x04);
    LCD_WriteData(0x11);
    LCD_WriteData(0x07);
    LCD_WriteData(0x31);
    LCD_WriteData(0x33);
    LCD_WriteData(0x42);
    LCD_WriteData(0x05);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x0A);
    LCD_WriteData(0x28);
    LCD_WriteData(0x2F);
    LCD_WriteData(0x0F);

    LCD_WriteCommand(LCD_SLEEP_OUT);
    HAL_Delay(200);

    LCD_WriteCommand(LCD_DISPLAY_ON);
    LCD_WriteCommand(LCD_GRAM);

    __HAL_LTDC_LAYER_ENABLE(&hltdc, 0);
    __HAL_LTDC_RELOAD_CONFIG(&hltdc);
}

void LCD_FillRGB565(uint16_t color)
{
    volatile uint16_t *fb = (volatile uint16_t *)LCD_FB_ADDR;
    for (uint32_t i = 0; i < (LCD_W * LCD_H); i++)
    {
        fb[i] = color;
    }
}

void LCD_FillRGB565_DMA(uint16_t color)
{
    lcd_fill_done = false;

    uint32_t dma2d_color = RGB565_To_DMA2DColor(color);

    if (HAL_DMA2D_Start_IT(&hdma2d, dma2d_color, LCD_FB_ADDR, LCD_W, LCD_H) != HAL_OK)
    {
        Error_Handler();
    }
}

uint32_t RGB565_To_DMA2DColor(uint16_t c)
{
    uint32_t r = (uint32_t)((c >> 11) & 0x1FU);
    uint32_t g = (uint32_t)((c >> 5)  & 0x3FU);
    uint32_t b = (uint32_t)(c & 0x1FU);

    r = (r * 255U) / 31U;
    g = (g * 255U) / 63U;
    b = (b * 255U) / 31U;

    return (r << 16) | (g << 8) | b;   // 0x00RRGGBB
}

