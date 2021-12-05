/****************************************************************
 * @brief   implementation of user logic functions.
 * @author  mculover666<2412828003@qq.com>
 * @version 1.0
 ***************************************************************/

#include "mpage.h"
#include "mpage_ui.h"

// 1. add page id here.
enum mpage_id {
    PAGE_WELCOME,
    PAGE1,
    PAGE2,
};

static mpage_ui_msg_t ui_msg;

// 2. add page ui in mpage_ui.c.
// 3. add page logic here.

static int welcom_logic(mpage_ui_msg_t *msg)
{
    return 0;
}

// 4. add page here.
const mpage_t mpage[] = {
    {PAGE_WELCOME, welcom_ui, welcom_logic},
};
