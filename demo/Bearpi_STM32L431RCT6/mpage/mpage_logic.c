#include "mpage.h"
#include "mpage_ui.h"
#include "gpio.h"

// 1. add page id here.
enum mpage_id {
    PAGE_WELCOME,
    PAGE1,
    PAGE2,
};

static mpage_ui_msg_t ui_msg;

static int get_key()
{
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET) {
        return 1;
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET) {
        return 2;
    }
    
    return 0;
}

// 2. add page ui in mpage_ui.c.
// 3. add page logic here.

static int welcom_logic(mpage_ui_msg_t *msg)
{
    int ret = get_key();
    
    if (ret == 2) {
        memset(&ui_msg, 0, sizeof(mpage_ui_msg_t));
        ui_msg.mpage_id_src = PAGE_WELCOME;
        ui_msg.mpage_id_dst = PAGE1;
        mpage_ui_msg_post(&ui_msg);
    }
   
    return 0;
}

static int page1_logic(mpage_ui_msg_t *msg)
{
    int ret = get_key();
    
    if (ret == 1) {
        memset(&ui_msg, 0, sizeof(mpage_ui_msg_t));
        ui_msg.mpage_id_src = PAGE1;
        ui_msg.mpage_id_dst = PAGE_WELCOME;
        mpage_ui_msg_post(&ui_msg);
    } else if (ret == 2) {
        memset(&ui_msg, 0, sizeof(mpage_ui_msg_t));
        ui_msg.mpage_id_src = PAGE1;
        ui_msg.mpage_id_dst = PAGE2;
        mpage_ui_msg_post(&ui_msg);
    }
   
    return 0;
}

static int page2_logic(mpage_ui_msg_t *msg)
{
    static uint32_t start_time;
    static uint16_t sec;
    uint32_t cur_time;
    
    int ret = get_key();
 
    if (ret == 1) {
        memset(&ui_msg, 0, sizeof(mpage_ui_msg_t));
        ui_msg.mpage_id_src = PAGE2;
        ui_msg.mpage_id_dst = PAGE_WELCOME;
        mpage_ui_msg_post(&ui_msg);
    }
    
    if (msg->mpage_id_src == PAGE1) {
        start_time = HAL_GetTick();
        sec = 5;
        
        memset(&ui_msg, 0, sizeof(mpage_ui_msg_t));
        ui_msg.mpage_id_src = PAGE2;
        ui_msg.mpage_id_dst = PAGE2;
        ui_msg.msg_len = sizeof(uint16_t);
        memcpy(ui_msg.msg_ctx, &sec, sizeof(uint16_t));
        mpage_ui_msg_post(&ui_msg);
    } else if (msg->mpage_id_src == PAGE2) {
        cur_time = HAL_GetTick();
        if (cur_time - start_time >= 1000) {
            sec--;
            start_time = HAL_GetTick();
            
            memset(&ui_msg, 0, sizeof(mpage_ui_msg_t));
            ui_msg.mpage_id_src = PAGE2;
            if (sec) {
                ui_msg.mpage_id_dst = PAGE2;
                ui_msg.msg_len = sizeof(uint16_t);
                memcpy(ui_msg.msg_ctx, &sec, sizeof(uint16_t));
                mpage_ui_msg_post(&ui_msg);
            } else {
                 ui_msg.mpage_id_src = PAGE2;
                 ui_msg.mpage_id_dst = PAGE_WELCOME;
                 mpage_ui_msg_post(&ui_msg);
            }
        }
    }

    return 0;
}

// 4. add page here.
const mpage_t mpage[] = {
    {PAGE_WELCOME, welcom_ui, welcom_logic},
    {PAGE1, page1_ui, page1_logic},
    {PAGE2, page2_ui, page2_logic},
};
