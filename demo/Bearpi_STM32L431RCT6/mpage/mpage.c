#include "mpage.h"
#include "mpage_ui.h"

extern const mpage_t mpage[];

static mpage_ui_msg_t s_mpage_msg_last = {0};
static mpage_ui_msg_t s_mpage_msg_cur = {0};
static mpage_ui_msg_buf_t mpage_ui_msg_buf;

static int mpage_init()
{
    mpage_ui_msg_buf.is_empty = 1;
    return 0;
}

static int mpage_ui_msg_pend(mpage_ui_msg_t *msg)
{
    if (!mpage_ui_msg_buf.is_empty) {
        memset(msg, 0, sizeof(mpage_ui_msg_t));
        memcpy(msg, &mpage_ui_msg_buf.mpage_ui_msg, sizeof(mpage_ui_msg_t));
        mpage_ui_msg_buf.is_empty++;
        return 0;
    }
    
    return -1;
}

int mpage_ui_msg_post(mpage_ui_msg_t *msg)
{
    memset(&mpage_ui_msg_buf.mpage_ui_msg, 0, sizeof(mpage_ui_msg_t));
    memcpy(&mpage_ui_msg_buf.mpage_ui_msg, msg, sizeof(mpage_ui_msg_t));
    mpage_ui_msg_buf.is_empty--;
    return 0;
}

int mpage_start()
{
    int ret;
    
    mpage_init();
   
    mpage[0].page_ui(&s_mpage_msg_cur);
    mpage[0].page_logic(&s_mpage_msg_cur);
    
    while (1) {
        ret = mpage_ui_msg_pend(&s_mpage_msg_cur);
        if (ret == 0) {
            memcpy(&s_mpage_msg_last, &s_mpage_msg_cur, sizeof(mpage_ui_msg_t));
            mpage[s_mpage_msg_last.mpage_id_dst].page_ui(&s_mpage_msg_last);
        }
        memset(&s_mpage_msg_cur, 0, sizeof(s_mpage_msg_cur));
        mpage[s_mpage_msg_last.mpage_id_dst].page_logic(&s_mpage_msg_last);
    }
}

