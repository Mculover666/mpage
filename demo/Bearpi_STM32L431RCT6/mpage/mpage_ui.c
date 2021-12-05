#include <stdio.h>
#include "mpage.h"
#include "mpage_ui.h"
#include "lcd_spi_drv.h"
#include "girl.h"
#include "girl1.h"
#include "girl2.h"

void welcom_ui(mpage_ui_msg_t *msg)
{
    lcd_show_image(0, 0, 240, 135, gImage_girl);
    
    lcd_clear_rect(0, 136, 240, 240);
    lcd_draw_text(60, 170, "mpage demo", 24);
    lcd_draw_text(0, 220, "Home", 16);
    lcd_draw_text(204, 220, "Next", 16);
}

void page1_ui(mpage_ui_msg_t *msg)
{
    lcd_show_image(0, 0, 240, 135, gImage_girl1);
    
    lcd_clear_rect(0, 136, 240, 240);
    lcd_draw_text(60, 170, "page 1", 24);
    lcd_draw_text(0, 220, "Home", 16);
    lcd_draw_text(204, 220, "Next", 16);
}

void page2_ui(mpage_ui_msg_t *msg)
{
    uint16_t sec;
    char disp_buf[32];
    
    lcd_show_image(0, 0, 240, 135, gImage_girl2);

    sec = *(uint16_t *)msg->msg_ctx;    
    snprintf(disp_buf, sizeof(disp_buf), "page 2(%d)", sec);
    lcd_clear_rect(0, 136, 240, 240);
    lcd_draw_text(60, 170, disp_buf, 24);
    lcd_draw_text(0, 220, "Home", 16);
}
