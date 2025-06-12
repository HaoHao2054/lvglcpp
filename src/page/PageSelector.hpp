// file: PageSelector.hpp (优化后)
#pragma once

#include <string>
#include "lvgl.h"

// 向前声明 PageManager，避免在头文件中互相包含导致循环依赖
// 实际的调用在 .cpp 文件中进行，那里会包含完整的 PageManager.hpp
namespace ui {
    class PageManager;
}

namespace ui {

    // 向前声明类，给友元函数使用
    class PageSelector;

    // 向前声明C风格的静态回调函数
    // 这样在PageSelector类中声明它为友元时，编译器就知道它的存在
    static void event_roller_cb_trampoline(lv_event_t *e);

    class PageSelector {
    private:
        lv_obj_t *m_roller = nullptr;

        // 事件处理成员函数
        void on_roller_value_changed(lv_event_t *e);

        // 设为友元，允许静态的C回调函数访问私有成员
        friend void event_roller_cb_trampoline(lv_event_t *e);

    public:
        // 构造函数现在是公开的，但我们仍然通过单例访问
        PageSelector();
        ~PageSelector();

        PageSelector(const PageSelector &) = delete;
        PageSelector &operator=(const PageSelector &) = delete;

        static PageSelector &instance();

        /**
         * @brief 从PageManager同步页面列表，并更新Roller的选项。
         * 这是实现解耦的关键方法。
         */
        void syncWithPageManager();

        // --- 控制和配置API ---
        void align(lv_align_t align, int x_ofs, int y_ofs);
        void show();
        void hide();
    };


} // namespace ui
