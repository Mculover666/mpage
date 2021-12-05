#ifndef _MPAGE_H_
#define _MPAGE_H_

#include <string.h>

#define MPAGE_UI_MSG_LEN_MAX    256

typedef struct mpage_ui_msg_st {
    unsigned int mpage_id_src;
    unsigned int mpage_id_dst;
    unsigned int msg_type;
    unsigned int msg_len;
    unsigned char msg_ctx[MPAGE_UI_MSG_LEN_MAX];
} mpage_ui_msg_t;

typedef struct mpage_ui_msg_buf_st {
    mpage_ui_msg_t mpage_ui_msg;
    int is_empty;
} mpage_ui_msg_buf_t;

typedef struct mpage_st {
    unsigned int page_id;
    void (*page_ui)(mpage_ui_msg_t *msg);
    int (*page_logic)(mpage_ui_msg_t *msg);
} mpage_t;

int mpage_ui_msg_post(mpage_ui_msg_t *msg);
int mpage_start(void);

#endif
