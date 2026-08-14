#include "lcd_ili9341_min.h"

extern SPI_HandleTypeDef hspi5;
extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;

volatile LCD_State_t lcd_state = LCD_STATE_READY;

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

//PRIVATE FUNCTIONS prototypes
static void LCD_IO_Init(void);
static void LCD_WriteCommand(uint8_t cmd);
static void LCD_WriteCommand(uint8_t cmd);
static void LCD_WriteData(uint8_t data);
static void LCD_WriteDataN(const uint8_t *data, uint32_t len);
static uint32_t RGB565_To_DMA2DColor(uint16_t c);
static bool LCD_BeginTransfer(void);
static void LCD_EndTransfer(void);
static bool LCD_DMA2D_ConfigR2M(uint32_t outputOffset);
static bool LCD_DMA2D_ConfigM2M_RGB565(uint32_t inputOffset, uint32_t outputOffset);

//CALLBACKS prototypes
static void LCD_DMA2D_TransferComplete(DMA2D_HandleTypeDef *hdma2d);
static void LCD_DMA2D_TransferError(DMA2D_HandleTypeDef *hdma2d);

//PRIVATE FUNCTIONS declarations
static void LCD_IO_Init(void)
{
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

static uint32_t RGB565_To_DMA2DColor(uint16_t c)
{
    uint32_t r = (uint32_t)((c >> 11) & 0x1FU);
    uint32_t g = (uint32_t)((c >> 5)  & 0x3FU);
    uint32_t b = (uint32_t)(c & 0x1FU);

    r = (r * 255U) / 31U;
    g = (g * 255U) / 63U;
    b = (b * 255U) / 31U;

    return (r << 16) | (g << 8) | b;   // 0x00RRGGBB
}

static bool LCD_BeginTransfer(void)
{
    if (lcd_state != LCD_STATE_READY)
        return false;

    lcd_state = LCD_STATE_BUSY;
    return true;
}

static void LCD_EndTransfer(void)
{
    lcd_state = LCD_STATE_READY;
}

static bool LCD_DMA2D_ConfigR2M(uint32_t outputOffset)
{
    hdma2d.Init.Mode = DMA2D_R2M;
    MODIFY_REG(hdma2d.Instance->CR, DMA2D_CR_MODE, DMA2D_R2M);

    WRITE_REG(hdma2d.Instance->OOR, outputOffset);

    return true;
}

static bool LCD_DMA2D_ConfigM2M_RGB565(uint32_t inputOffset, uint32_t outputOffset)
{
    hdma2d.Init.Mode = DMA2D_M2M;
    MODIFY_REG(hdma2d.Instance->CR, DMA2D_CR_MODE, DMA2D_M2M);

    hdma2d.LayerCfg[DMA2D_FOREGROUND_LAYER].InputColorMode = DMA2D_INPUT_RGB565;

    hdma2d.LayerCfg[DMA2D_FOREGROUND_LAYER].InputOffset = inputOffset;

    if (HAL_DMA2D_ConfigLayer(&hdma2d, DMA2D_FOREGROUND_LAYER) != HAL_OK)
    {
        lcd_state = LCD_STATE_ERROR;
        return false;
    }

    WRITE_REG(hdma2d.Instance->OOR, outputOffset);

    return true;
}

//PUBLIC FUNCTIONS declarations

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

    hdma2d.XferCpltCallback = LCD_DMA2D_TransferComplete;
    hdma2d.XferErrorCallback = LCD_DMA2D_TransferError;
}

bool LCD_IsReady()
{
	return (lcd_state == LCD_STATE_READY);
}

LCD_State_t LCD_GetState(void)
{
	return lcd_state;
}

void LCD_FillRGB565(uint16_t color)
{
    volatile uint16_t *fb = (volatile uint16_t *)LCD_FB_ADDR;
    for (uint32_t i = 0; i < (LCD_W * LCD_H); i++)
    {
        fb[i] = color;
    }
}

bool LCD_FillRGB565_DMA(uint16_t color)
{
    if (!LCD_BeginTransfer())
    	return false;

    uint32_t dma2d_color = RGB565_To_DMA2DColor(color);

    LCD_DMA2D_ConfigR2M(0);

    if (HAL_DMA2D_Start_IT(&hdma2d, dma2d_color, LCD_FB_ADDR, LCD_W, LCD_H) != HAL_OK)
    {
    	lcd_state = LCD_STATE_ERROR;
        return false;
    }
    return true;
}

bool LCD_FillRect_RGB565_DMA(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    if ((width == 0U) || (height == 0U))
    {
        return false;
    }

    if ((x >= LCD_W) || (y >= LCD_H))
    {
        return false;
    }

    if (!LCD_BeginTransfer())
    	return false;

    if ((x + width) > LCD_W)
    {
        width = LCD_W - x;
    }

    if ((y + height) > LCD_H)
    {
        height = LCD_H - y;
    }

    uint32_t dma2d_color = RGB565_To_DMA2DColor(color);

    uint32_t first_pixel_addr = LCD_FB_ADDR + (((uint32_t)y * LCD_W + x) * sizeof(uint16_t));

    LCD_DMA2D_ConfigR2M(LCD_W - width);


    if (HAL_DMA2D_Start_IT(&hdma2d, dma2d_color, first_pixel_addr, width, height) != HAL_OK)
        {
    		lcd_state = LCD_STATE_ERROR;
        	return false;
        }
        return true;
}

bool LCD_DrawImage_DMA(uint16_t x, uint16_t y, const LCD_Image_t *image)
{
    if (image == NULL)
    	{
        	return false;
    	}

    if ((image->width == 0U) || (image->height == 0U))
        {
            return false;
        }

    if ((x >= LCD_W) || (y >= LCD_H))
    {
    	return false;
    }

    if (image->data == NULL)
    	return false;

    if (!LCD_BeginTransfer())
    	return false;

    uint16_t width = image->width;
    if ((x + width) > LCD_W)
    {
    	width = LCD_W - x;
    }

    uint16_t height = image->height;
    if ((y + height) > LCD_H)
    {
    	height = LCD_H - y;
    }

    uint32_t first_pixel_addr = LCD_FB_ADDR + (((uint32_t)y * LCD_W + x) * sizeof(uint16_t));

    if (image->format == LCD_IMAGE_RGB565)
    	{
    		if(!LCD_DMA2D_ConfigM2M_RGB565(image->width - width , LCD_W - width))
    		{
    			lcd_state = LCD_STATE_ERROR;
    			return false;
    		}
    	}
    else if (image->format == LCD_IMAGE_ARGB8888)
    	return false;
    else
    	return false;


    if (HAL_DMA2D_Start_IT(&hdma2d, (uint32_t)image->data, first_pixel_addr, width, height) != HAL_OK)
        {
    		lcd_state = LCD_STATE_ERROR;
        	return false;
        }
        return true;
}

bool LCD_DrawImagePart_DMA(uint16_t x_dist, uint16_t y_dist, uint16_t x_src, uint16_t y_src, uint16_t width, uint16_t height, const LCD_Image_t *image)
{
    if (image == NULL)
    	{
        	return false;
    	}

	if ((image->width == 0U) || (image->height == 0U))
		{
			return false;
    	}

	if (((uint32_t)x_dist >= LCD_W) || ((uint32_t)y_dist >= LCD_H))
		{
			return false;
		}

	if (image->data == NULL)
		{
			return false;
		}

	if ((width == 0U) || (height == 0U))
		{
	    	return false;
		}

	if (((uint32_t)x_src >= image->width) || ((uint32_t)y_src >= image->height))
	    {
	       	return false;
	    }

	if (((uint32_t)x_src + width > image->width) || ((uint32_t)y_src + height > image->height))
	    {
	    	return false;
	    }

	if (!LCD_BeginTransfer())
	   	{
			return false;
	   	}

	uint16_t width_dist = width;
	if (((uint32_t)x_dist + width_dist) > LCD_W)
		{
		width_dist = LCD_W - x_dist;
		}

	uint16_t height_dist = height;
	if (((uint32_t)y_dist + height_dist) > LCD_H)
	    {
		height_dist = LCD_H - y_dist;
	    }

	uint32_t source_addr = (uint32_t)(image->data + (uint32_t)y_src * image->width + x_src);
    uint32_t destination_addr = LCD_FB_ADDR + (((uint32_t)y_dist * LCD_W + x_dist) * sizeof(uint16_t));

    if (image->format == LCD_IMAGE_RGB565)
    	{
    		if(!LCD_DMA2D_ConfigM2M_RGB565(image->width - width_dist , LCD_W - width_dist))
    		{
    			lcd_state = LCD_STATE_ERROR;
    			return false;
    		}
    	}
    else if (image->format == LCD_IMAGE_ARGB8888)
    	{
    	 	lcd_state = LCD_STATE_ERROR;
    	 	return false;
    	}

    else
    	{
        	lcd_state = LCD_STATE_ERROR;
        	return false;
        }


    if (HAL_DMA2D_Start_IT(&hdma2d, source_addr, destination_addr, width_dist, height_dist) != HAL_OK)
        {
    		lcd_state = LCD_STATE_ERROR;
        	return false;
        }
        return true;
}

// CALLBACKS declarations
static void LCD_DMA2D_TransferComplete(DMA2D_HandleTypeDef *hdma2d)
{
    (void)hdma2d;
    LCD_EndTransfer();
}

static void LCD_DMA2D_TransferError(DMA2D_HandleTypeDef *hdma2d)
{
    (void)hdma2d;
    lcd_state = LCD_STATE_ERROR;
}




