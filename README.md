# mpage
嵌入式多页显示界面框架

# mpage ui msg 设计

ui msg 用来在界面间传递消息：
```c
typedef struct mpage_ui_msg_st {
    unsigned int mpage_id_src;
    unsigned int mpage_id_dst;
    unsigned int msg_type;
    unsigned int msg_len;
    unsigned char msg_ctx[MPAGE_UI_MSG_LEN_MAX];
} mpage_ui_msg_t;
```

- mpage_id_src：发出该消息的页面 id（可选）
- mpage_id_dst：要接收消息的页面 id（必填）
- msg_type：可用于指明该消息类型，用于ui界面判断（可选）
- msg_len：消息内容长度，单位Byte（可选）
- msg_ctx：消息内容（可选），最大长度可由 MPAGE_UI_MSG_LEN_MAX 指定，默认256.

# 使用方法

1. 在枚举类型中添加page id（WELCOME只是默认页，可删除）,mpage通过指定 page id 来跳转到对应的页。
```c
enum mpage_id {
    PAGE_WELCOME,
    // ...
};
```

2. 在`mpage_ui.c`中添加该页对应的 ui 逻辑，添加后在`mpage_ui.h`中声明：

```c
void welcom_ui(mpage_ui_msg_t *msg)
{
    
}
```
前端界面函数被调用时会传入ui_msg，用户可通过ui_msg拿到需要显示的信息。

3. 在`mpage_logic.c`中添加该页对应的后台逻辑。
```c
static int welcom_logic(mpage_ui_msg_t *msg)
{

    return 0;
}
```
后端逻辑函数中，用户可利用 ui_msg 全局变量封装消息，使用下面的 API 发送 ui_msg 并跳转到对应界面：
```c
int mpage_ui_msg_post(mpage_ui_msg_t *msg);
```

4. 前后端函数各自完成后，将{<页面id>，<页面ui函数>, <页面后台逻辑函数>} 注册到 mpage 中。
```c
const mpage_t mpage[] = {
    {PAGE_WELCOME, welcom_ui, welcom_logic},
};
```
